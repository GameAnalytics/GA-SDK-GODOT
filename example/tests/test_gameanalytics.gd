extends SceneTree

# Headless test suite for the GameAnalytics GDExtension.
#
#   godot --headless --path example --script res://tests/test_gameanalytics.gd
#
# Exits non-zero on the first failed assertion, so CI can gate on it.
#
# NO KEYS ARE HARDCODED. The suite runs in two modes:
#
#   offline (default)  no credentials, init() is never called, nothing leaves the machine.
#                      Still exercises the whole binding surface AND the platform wrapper:
#                      event calls are forwarded to GAWrapperWeb / GAWrapperAndroid / the
#                      desktop SDK, which is where the argument-slot and JNI bugs live.
#                      The SDK rejects them internally for want of a session.
#
#   online             set GA_TEST_GAME_KEY and GA_TEST_SECRET_KEY to additionally verify
#                      init, remote configs and event submission. Use a throwaway sandbox
#                      game, never a production key.

const EXPECTED_METHODS := [
	"init", "configureBuild", "configureUserId", "configureAutoDetectAppVersion",
	"configureAvailableCustomDimensions01", "configureAvailableCustomDimensions02",
	"configureAvailableCustomDimensions03", "configureAvailableResourceCurrencies",
	"configureAvailableResourceItemTypes",
	"addBusinessEvent", "addResourceEvent", "addProgressionEvent", "addDesignEvent",
	"addErrorEvent", "addAdEvent", "addDesignEventWithValue", "addProgressionEventWithScore",
	"setCustomDimension01", "setCustomDimension02", "setCustomDimension03",
	"setEnabledInfoLog", "setEnabledVerboseLog", "setEnabledManualSessionHandling",
	"setGlobalCustomEventFields", "setExternalUserId",
	"startSession", "endSession", "onQuit",
	"getUserId", "getExternalUserId", "getABTestingId", "getABTestingVariantId",
	"getRemoteConfigsValueAsString", "getRemoteConfigsContentAsString",
	"getRemoteConfigsValueAsJSON", "isRemoteConfigsReady", "registerRemoteConfigsListener",
	"enableSDKInitEvent", "enableFpsHistogram", "enableMemoryHistogram",
	"enableHealthHardwareInfo",
	"getElapsedSessionTime", "getElapsedTimeFromAllSessions",
]

const EXPECTED_SIGNALS := ["remote_configs_updated"]

var _failures := 0
var _checks := 0
var _skipped := 0
var _ga: Object = null
var _configs_fired := false

var _game_key := ""
var _secret_key := ""


func _initialize() -> void:
	_game_key = OS.get_environment("GA_TEST_GAME_KEY")
	_secret_key = OS.get_environment("GA_TEST_SECRET_KEY")

	print("=== GameAnalytics headless test suite ===")
	print("mode: %s" % ("online (credentials supplied)" if _is_online() else "offline (no credentials, no network)"))
	_run()


func _is_online() -> bool:
	return _game_key != "" and _secret_key != ""


func _run() -> void:
	_test_singleton_present()
	if _ga == null:
		_finish()
		return

	_test_bindings_exist()
	_test_signals_exist()
	_test_getters_before_init()
	_test_event_calls_reach_the_wrapper()
	_test_elapsed_time()

	if _is_online():
		await _test_init_and_session()
		await _test_remote_configs()
		_test_event_calls_reach_the_wrapper()
	else:
		_skip("init() + session", "GA_TEST_GAME_KEY / GA_TEST_SECRET_KEY not set")
		_skip("remote configs fetch", "no credentials")
		_skip("event submission", "no credentials")

	_finish()


# ---------------------------------------------------------------- offline tests

func _test_singleton_present() -> void:
	# catches: api_version mismatch, unsigned dylib, extension failing to load at all
	_check(Engine.has_singleton("GameAnalytics"), "GameAnalytics singleton is registered")
	if Engine.has_singleton("GameAnalytics"):
		_ga = Engine.get_singleton("GameAnalytics")
		_check(_ga != null, "singleton resolves to an object")


func _test_bindings_exist() -> void:
	# catches: a bound method silently disappearing on an engine or godot-cpp bump
	for method in EXPECTED_METHODS:
		_check(_ga.has_method(method), "method bound: %s" % method)


func _test_signals_exist() -> void:
	# catches: the exact "Invalid access to property 'remote_configs_updated'" failure
	for sig in EXPECTED_SIGNALS:
		_check(_ga.has_signal(sig), "signal declared: %s" % sig)


func _test_getters_before_init() -> void:
	# must return sane types, not crash, on the uninitialized path
	_check(typeof(_ga.getUserId()) == TYPE_STRING, "getUserId() returns String pre-init")
	_check(typeof(_ga.isRemoteConfigsReady()) == TYPE_BOOL, "isRemoteConfigsReady() returns bool")
	_check(typeof(_ga.getRemoteConfigsContentAsString()) == TYPE_STRING,
			"getRemoteConfigsContentAsString() returns String pre-init")
	_check(typeof(_ga.getABTestingId()) == TYPE_STRING, "getABTestingId() returns String")


func _test_event_calls_reach_the_wrapper() -> void:
	# Each of these is forwarded to the platform wrapper regardless of session state, so
	# this exercises the JS eval strings on web and the JNI lookups on android. Without a
	# session the SDK discards them, which is exactly what we want offline.
	var fields := {"fields": JSON.stringify({"ci": "true"}), "mergeFields": false}

	_ga.addDesignEvent("ci:design:nofields", {})
	_ga.addDesignEvent("ci:design:fields", fields)
	_ga.addDesignEvent("ci:design:value", {"value": 42.0})
	_ga.addDesignEventWithValue("ci:design:withvalue", 7.0)
	_ga.addErrorEvent("info", "ci error event", {})
	_ga.addErrorEvent("warning", "ci error with fields", fields)
	_ga.addResourceEvent("source", "gold", 100.0, "boost", "ci_item", {})
	_ga.addProgressionEvent("start", "w1", "s1", "l1", {})
	_ga.addProgressionEventWithScore("complete", "w1", "s1", "l1", 999)
	_ga.addBusinessEvent("USD", 100, "ci_type", "ci_id", "ci_cart", {})

	# strings that break naive interpolation - the web wrapper pastes these straight into
	# a JavaScript eval, so an apostrophe must not terminate the literal
	_ga.addDesignEvent("ci:it's:quoted", {})
	_ga.addDesignEvent("ci:unicode:日本語", {})

	_check(true, "all event types accepted, including quoted and unicode ids")


func _test_elapsed_time() -> void:
	# catches the malformed "()L" JNI descriptor and the wrong method name
	_check(typeof(_ga.getElapsedSessionTime()) == TYPE_INT, "getElapsedSessionTime() returns int")
	_check(_ga.getElapsedSessionTime() >= 0, "getElapsedSessionTime() is non-negative")
	_check(typeof(_ga.getElapsedTimeFromAllSessions()) == TYPE_INT,
			"getElapsedTimeFromAllSessions() returns int")


# ---------------------------------------------------------------- online tests

func _test_init_and_session() -> void:
	_ga.setEnabledInfoLog(true)
	_ga.configureAvailableResourceCurrencies(["gold", "gems"])
	_ga.configureAvailableResourceItemTypes(["boost", "lives"])
	_ga.configureAvailableCustomDimensions01(["ninja", "samurai"])
	_ga.configureBuild("ci-test")
	_ga.configureUserId("ci_user")

	if _ga.has_signal("remote_configs_updated"):
		_ga.remote_configs_updated.connect(func(_c): _configs_fired = true)

	_ga.init(_game_key, _secret_key)
	await create_timer(3.0).timeout

	_check(_ga.getUserId() != "", "user id assigned after init")


func _test_remote_configs() -> void:
	var waited := 0.0
	while not _ga.isRemoteConfigsReady() and waited < 15.0:
		await create_timer(1.0).timeout
		waited += 1.0

	_check(_ga.isRemoteConfigsReady(), "remote configs became ready within 15s")
	_check(_configs_fired, "remote_configs_updated signal fired")

	var content: String = _ga.getRemoteConfigsContentAsString()
	_check(content.length() > 0, "remote configs content is non-empty")
	_check(JSON.parse_string(content) != null, "remote configs content parses as JSON")


# ---------------------------------------------------------------- harness

func _check(condition: bool, description: String) -> void:
	_checks += 1
	if condition:
		print("  PASS  %s" % description)
	else:
		_failures += 1
		printerr("  FAIL  %s" % description)


func _skip(description: String, reason: String) -> void:
	_skipped += 1
	print("  SKIP  %s (%s)" % [description, reason])


func _finish() -> void:
	if _ga != null and _is_online():
		_ga.onQuit()
		await create_timer(2.0).timeout

	print("=== %d checks, %d failures, %d skipped ===" % [_checks, _failures, _skipped])
	quit(1 if _failures > 0 else 0)
