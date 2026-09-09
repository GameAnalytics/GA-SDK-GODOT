extends Control

# GameAnalytics example app.
#
# Left side sends every event type the Godot SDK supports, right side shows the
# identifiers and remote configs the SDK exposes. Remote configs are kept up to
# date through the `remote_configs_updated` signal rather than by polling.

# the previous example scene initialized on launch; keep that behaviour so a fresh
# install starts a session without user interaction. Set to false to fill in the
# setup panel and initialize by hand.
const AUTO_INITIALIZE := true

const GAME_KEY := "[INSERT YOUR KEY HERE]"
const SECRET_KEY := "[INSERT YOUR KEY HERE]"

# configured before init() and reused by the event forms below
const CURRENCIES := ["gold", "gems"]
const ITEM_TYPES := ["boost", "lives"]
const DIMENSIONS_01 := ["ninja", "samurai"]
const DIMENSIONS_02 := ["whale", "dolphin"]
const DIMENSIONS_03 := ["horde", "alliance"]

# only the values the SDK maps to an enum, see GameAnalytics::addAdEvent
const AD_ACTIONS := ["clicked", "show", "failed_show", "reward_received"]
const AD_TYPES := ["video", "rewarded_video", "playable", "interstitial", "offer_wall", "banner"]
const AD_REASONS := ["unknown", "offline", "no_fill", "internal_error", "invalid_request", "unable_to_precache"]
const SEVERITIES := ["debug", "info", "warning", "error", "critical"]

var ga: Object = null
var _initialized := false

var _status_label: Label
var _init_button: Button
var _game_key_edit: LineEdit
var _secret_key_edit: LineEdit
var _build_edit: LineEdit
var _user_id_edit: LineEdit
var _ext_user_id_edit: LineEdit

var _fields_edit: LineEdit
var _merge_fields_check: CheckBox

var _needs_sdk: Array[Control] = []   # disabled until the SDK is loaded
var _needs_init: Array[Control] = []  # disabled until init() has run

var _info_labels := {}
var _configs_view: TextEdit
var _config_key_edit: LineEdit
var _config_default_edit: LineEdit
var _config_result: TextEdit
var _log_view: RichTextLabel


# enableFpsHistogram takes a Callable that the SDK polls for the current frame rate
func fpsTracker() -> float:
	return Engine.get_frames_per_second()


func _ready() -> void:
	_build_ui()

	if Engine.has_singleton("GameAnalytics"):
		ga = Engine.get_singleton("GameAnalytics")
		_status_label.text = "SDK loaded — enter your keys and press Initialize"
		_status_label.modulate = Color(0.65, 0.85, 1.0)
		ga.remote_configs_updated.connect(_on_remote_configs_updated)
		_log("GameAnalytics singleton found")
	else:
		_status_label.text = "GameAnalytics extension not loaded — build the plugin and run: python copy_binaries.py debug"
		_status_label.modulate = Color(1.0, 0.5, 0.5)
		_log("[color=#ff8080]GameAnalytics singleton not found[/color]")

	_set_enabled(_needs_sdk, ga != null)
	_set_enabled(_needs_init, false)
	_refresh_info()

	if AUTO_INITIALIZE and ga != null and not GAME_KEY.begins_with("["):
		_on_initialize_pressed()


# ---------------------------------------------------------------- SDK actions

func _on_initialize_pressed() -> void:
	if ga == null or _initialized:
		return

	ga.setEnabledInfoLog(true)
	ga.setEnabledVerboseLog(false)

	# everything that configures the SDK has to happen before init()
	ga.configureAvailableCustomDimensions01(DIMENSIONS_01)
	ga.configureAvailableCustomDimensions02(DIMENSIONS_02)
	ga.configureAvailableCustomDimensions03(DIMENSIONS_03)
	ga.configureAvailableResourceCurrencies(CURRENCIES)
	ga.configureAvailableResourceItemTypes(ITEM_TYPES)
	ga.configureAutoDetectAppVersion(false)
	ga.configureBuild(_build_edit.text)

	if not _user_id_edit.text.is_empty():
		ga.configureUserId(_user_id_edit.text)

	# the C++ SDK refuses this after init ("a custom user id must be set before
	# SDK is initialized"), so it belongs here rather than in a runtime setter
	if not _ext_user_id_edit.text.is_empty():
		ga.setExternalUserId(_ext_user_id_edit.text)

	ga.enableSDKInitEvent(true)
	ga.enableMemoryHistogram(true)
	ga.enableHealthHardwareInfo(true)
	ga.enableFpsHistogram(fpsTracker)

	ga.init(_game_key_edit.text, _secret_key_edit.text)

	_initialized = true
	_status_label.text = "Initialized — remote configs arrive on the remote_configs_updated signal"
	_status_label.modulate = Color(0.6, 1.0, 0.7)
	_init_button.disabled = true
	_set_enabled(_needs_init, true)
	_log("init(%s)" % _game_key_edit.text)
	_refresh_info()


func _on_remote_configs_updated(configs: String) -> void:
	_log("[color=#8fd98f]remote_configs_updated[/color] (%d bytes)" % configs.length())
	_show_configs(configs)
	_refresh_info()


func _send_business(currency: OptionButton, amount: SpinBox, item_type: LineEdit, item_id: LineEdit,
		cart_type: LineEdit, receipt: LineEdit, auto_fetch: CheckBox) -> void:
	var options := _base_options()
	options["autoFetchReceipt"] = auto_fetch.button_pressed
	if not receipt.text.is_empty():
		options["receipt"] = receipt.text

	ga.addBusinessEvent(_selected(currency), int(amount.value), item_type.text, item_id.text, cart_type.text, options)
	_log("addBusinessEvent(%s, %d, %s, %s, %s) %s" % [_selected(currency), int(amount.value),
			item_type.text, item_id.text, cart_type.text, _describe(options)])


func _send_resource(flow: OptionButton, currency: OptionButton, amount: SpinBox,
		item_type: OptionButton, item_id: LineEdit) -> void:
	var options := _base_options()

	ga.addResourceEvent(_selected(flow), _selected(currency), amount.value, _selected(item_type), item_id.text, options)
	_log("addResourceEvent(%s, %s, %s, %s, %s) %s" % [_selected(flow), _selected(currency),
			amount.value, _selected(item_type), item_id.text, _describe(options)])


func _send_progression(status: OptionButton, p1: LineEdit, p2: LineEdit, p3: LineEdit,
		send_score: CheckBox, score: SpinBox, use_convenience: CheckBox) -> void:
	# the convenience overload always sends a score and takes no options dictionary
	if use_convenience.button_pressed:
		ga.addProgressionEventWithScore(_selected(status), p1.text, p2.text, p3.text, int(score.value))
		_log("addProgressionEventWithScore(%s, %s, %s, %s, %d)" % [_selected(status),
				p1.text, p2.text, p3.text, int(score.value)])
		return

	var options := _base_options()
	if send_score.button_pressed:
		options["score"] = int(score.value)

	ga.addProgressionEvent(_selected(status), p1.text, p2.text, p3.text, options)
	_log("addProgressionEvent(%s, %s, %s, %s) %s" % [_selected(status), p1.text, p2.text, p3.text, _describe(options)])


func _send_design(event_id: LineEdit, send_value: CheckBox, value: SpinBox,
		use_convenience: CheckBox) -> void:
	# the convenience overload always sends a value and takes no options dictionary
	if use_convenience.button_pressed:
		ga.addDesignEventWithValue(event_id.text, value.value)
		_log("addDesignEventWithValue(%s, %s)" % [event_id.text, value.value])
		return

	var options := _base_options()
	if send_value.button_pressed:
		options["value"] = value.value

	ga.addDesignEvent(event_id.text, options)
	_log("addDesignEvent(%s) %s" % [event_id.text, _describe(options)])


func _send_error(severity: OptionButton, message: LineEdit) -> void:
	var options := _base_options()

	ga.addErrorEvent(_selected(severity), message.text, options)
	_log("addErrorEvent(%s, %s) %s" % [_selected(severity), message.text, _describe(options)])


func _send_ad(action: OptionButton, ad_type: OptionButton, sdk_name: LineEdit, placement: LineEdit,
		mode: OptionButton, duration: SpinBox, reason: OptionButton) -> void:
	var options := _base_options()

	# the SDK sends either a duration or a no-ad reason, never both
	if _selected(mode) == "duration":
		options["duration"] = int(duration.value)
	else:
		options["reason"] = _selected(reason)

	ga.addAdEvent(_selected(action), _selected(ad_type), sdk_name.text, placement.text, options)
	_log("addAdEvent(%s, %s, %s, %s) %s" % [_selected(action), _selected(ad_type),
			sdk_name.text, placement.text, _describe(options)])


func _base_options() -> Dictionary:
	var options := {}
	var fields := _fields_edit.text.strip_edges()

	if not fields.is_empty():
		if JSON.parse_string(fields) == null:
			_log("[color=#ffb347]custom fields are not valid JSON, sending without them[/color]")
		else:
			options["fields"] = fields
			options["mergeFields"] = _merge_fields_check.button_pressed

	return options


# ------------------------------------------------------------- info panel

func _refresh_info() -> void:
	if ga == null:
		return

	_info_labels["user_id"].text = ga.getUserId()
	_info_labels["ext_user_id"].text = ga.getExternalUserId()
	_info_labels["ab_id"].text = _or_dash(ga.getABTestingId())
	_info_labels["ab_variant_id"].text = _or_dash(ga.getABTestingVariantId())
	_info_labels["configs_ready"].text = "yes" if ga.isRemoteConfigsReady() else "no"
	_info_labels["session_time"].text = "%d s" % ga.getElapsedSessionTime()
	_info_labels["all_sessions_time"].text = "%d s" % ga.getElapsedTimeFromAllSessions()

	if ga.isRemoteConfigsReady() and _configs_view.text.is_empty():
		_show_configs(ga.getRemoteConfigsContentAsString())


func _show_configs(configs: String) -> void:
	var parsed = JSON.parse_string(configs)
	_configs_view.text = JSON.stringify(parsed, "  ") if parsed != null else configs


func _on_lookup_pressed() -> void:
	var key := _config_key_edit.text
	var as_string: String = ga.getRemoteConfigsValueAsString(key, _config_default_edit.text)
	var as_json = ga.getRemoteConfigsValueAsJSON(key)

	_config_result.text = "getRemoteConfigsValueAsString: %s\ngetRemoteConfigsValueAsJSON: %s" % [
			as_string, JSON.stringify(as_json) if as_json != null else "<null>"]
	_log("remote config lookup '%s' -> %s" % [key, as_string])


func _on_apply_dimensions_pressed(global_fields: LineEdit,
		d1: OptionButton, d2: OptionButton, d3: OptionButton) -> void:
	ga.setCustomDimension01(_selected(d1))
	ga.setCustomDimension02(_selected(d2))
	ga.setCustomDimension03(_selected(d3))

	var fields := global_fields.text.strip_edges()
	if not fields.is_empty():
		ga.setGlobalCustomEventFields(fields)

	_log("applied custom dimensions (%s, %s, %s)" % [_selected(d1), _selected(d2), _selected(d3)])
	_refresh_info()


# ------------------------------------------------------------------- helpers

func _log(message: String) -> void:
	var stamp := Time.get_time_string_from_system()
	_log_view.append_text("[%s] %s\n" % [stamp, message])
	print("[%s] %s" % [stamp, message])


func _selected(option: OptionButton) -> String:
	return option.get_item_text(option.selected) if option.selected >= 0 else ""


func _describe(options: Dictionary) -> String:
	return "" if options.is_empty() else str(options)


func _or_dash(value: String) -> String:
	return value if not value.is_empty() else "—"


func _set_enabled(controls: Array[Control], enabled: bool) -> void:
	for control in controls:
		if control is BaseButton:
			control.disabled = not enabled
		else:
			control.editable = enabled


# ----------------------------------------------------------------- ui layout

func _build_ui() -> void:
	set_anchors_preset(Control.PRESET_FULL_RECT)

	var root := VBoxContainer.new()
	root.set_anchors_preset(Control.PRESET_FULL_RECT)
	root.add_theme_constant_override("separation", 8)
	root.offset_left = 12
	root.offset_top = 12
	root.offset_right = -12
	root.offset_bottom = -12
	add_child(root)

	_build_header(root)

	var columns := HSplitContainer.new()
	columns.size_flags_vertical = Control.SIZE_EXPAND_FILL
	columns.split_offset = 620
	root.add_child(columns)

	_build_events_panel(columns)
	_build_info_panel(columns)
	_build_log(root)


func _build_header(parent: Node) -> void:
	var panel := _titled_panel(parent, "Setup")

	var grid := GridContainer.new()
	grid.columns = 4
	panel.add_child(grid)

	_label(grid, "Game key")
	_game_key_edit = _line_edit(grid, GAME_KEY, 320)
	_label(grid, "Build")
	_build_edit = _line_edit(grid, "1.0.0", 120)

	_label(grid, "Secret key")
	_secret_key_edit = _line_edit(grid, SECRET_KEY, 320)
	_label(grid, "Custom user id")
	_user_id_edit = _line_edit(grid, "sample_user", 160)

	_label(grid, "External user id")
	_ext_user_id_edit = _line_edit(grid, "sample_ext_user", 320)
	_label(grid, "")
	_label(grid, "")

	for edit in [_game_key_edit, _secret_key_edit, _build_edit, _user_id_edit, _ext_user_id_edit]:
		_needs_sdk.append(edit)

	var row := HBoxContainer.new()
	panel.add_child(row)

	_init_button = Button.new()
	_init_button.text = "Initialize"
	_init_button.pressed.connect(_on_initialize_pressed)
	row.add_child(_init_button)
	_needs_sdk.append(_init_button)

	_status_label = Label.new()
	_status_label.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	row.add_child(_status_label)


func _build_events_panel(parent: Node) -> void:
	var column := VBoxContainer.new()
	column.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	parent.add_child(column)

	var tabs := TabContainer.new()
	tabs.size_flags_vertical = Control.SIZE_EXPAND_FILL
	column.add_child(tabs)

	_build_business_tab(tabs)
	_build_resource_tab(tabs)
	_build_progression_tab(tabs)
	_build_design_tab(tabs)
	_build_error_tab(tabs)
	_build_ad_tab(tabs)
	_build_session_tab(tabs)
	_build_dimensions_tab(tabs)

	# applied to every event that accepts them
	var footer := _titled_panel(column, "Custom fields (all events)")
	var grid := GridContainer.new()
	grid.columns = 2
	footer.add_child(grid)

	_label(grid, "fields (JSON)")
	_fields_edit = _line_edit(grid, '{"my_key":"my_value"}', 420)
	_label(grid, "mergeFields")
	_merge_fields_check = _check_box(grid, false)
	_needs_init.append(_fields_edit)
	_needs_init.append(_merge_fields_check)


func _build_business_tab(tabs: TabContainer) -> void:
	var grid := _tab_grid(tabs, "Business")

	var currency := _option(grid, "currency", ["USD", "EUR"])
	var amount := _spin(grid, "amount (cents)", 999, 1, 1, 1000000)
	var item_type := _labelled_edit(grid, "itemType", "gold_pack")
	var item_id := _labelled_edit(grid, "itemId", "gold_pack_large")
	var cart_type := _labelled_edit(grid, "cartType", "shop")
	var receipt := _labelled_edit(grid, "receipt (optional)", "")
	var auto_fetch := _labelled_check(grid, "autoFetchReceipt", false)

	_send_button(grid, "Send business event", func(): _send_business(
			currency, amount, item_type, item_id, cart_type, receipt, auto_fetch))


func _build_resource_tab(tabs: TabContainer) -> void:
	var grid := _tab_grid(tabs, "Resource")

	var flow := _option(grid, "flowType", ["source", "sink"])
	var currency := _option(grid, "currency", CURRENCIES)
	var amount := _spin(grid, "amount", 100, 0.5, 0.5, 1000000)
	var item_type := _option(grid, "itemType", ITEM_TYPES)
	var item_id := _labelled_edit(grid, "itemId", "level_reward")

	_send_button(grid, "Send resource event", func(): _send_resource(
			flow, currency, amount, item_type, item_id))


func _build_progression_tab(tabs: TabContainer) -> void:
	var grid := _tab_grid(tabs, "Progression")

	var status := _option(grid, "status", ["start", "complete", "fail"])
	var p1 := _labelled_edit(grid, "progression01", "world1")
	var p2 := _labelled_edit(grid, "progression02", "stage3")
	var p3 := _labelled_edit(grid, "progression03", "boss")
	var send_score := _labelled_check(grid, "send score", false)
	var score := _spin(grid, "score", 1000, 1, 0, 100000000)
	var convenience := _labelled_check(grid, "use addProgressionEventWithScore", false)

	_note(grid, "addProgressionEventWithScore always sends the score and takes no options, so the custom fields below are ignored for it.")

	_send_button(grid, "Send progression event", func(): _send_progression(
			status, p1, p2, p3, send_score, score, convenience))


func _build_design_tab(tabs: TabContainer) -> void:
	var grid := _tab_grid(tabs, "Design")

	var event_id := _labelled_edit(grid, "eventId", "sample:button:pressed")
	var send_value := _labelled_check(grid, "send value", true)
	var value := _spin(grid, "value", 42, 0.5, -1000000, 1000000)
	var convenience := _labelled_check(grid, "use addDesignEventWithValue", false)

	_note(grid, "addDesignEventWithValue always sends the value and takes no options, so the custom fields below are ignored for it.")

	_send_button(grid, "Send design event", func(): _send_design(
			event_id, send_value, value, convenience))


func _build_error_tab(tabs: TabContainer) -> void:
	var grid := _tab_grid(tabs, "Error")

	var severity := _option(grid, "severity", SEVERITIES)
	var message := _labelled_edit(grid, "message", "Something went wrong in the sample")

	_send_button(grid, "Send error event", func(): _send_error(severity, message))


func _build_ad_tab(tabs: TabContainer) -> void:
	var grid := _tab_grid(tabs, "Ad")

	var action := _option(grid, "adAction", AD_ACTIONS)
	var ad_type := _option(grid, "adType", AD_TYPES)
	var sdk_name := _labelled_edit(grid, "adSdkName", "sample_ad_sdk")
	var placement := _labelled_edit(grid, "adPlacement", "rewarded_placement")
	var mode := _option(grid, "send", ["duration", "no ad reason"])
	var duration := _spin(grid, "duration (s)", 30, 1, 0, 100000)
	var reason := _option(grid, "reason", AD_REASONS)

	_note(grid, "Desktop builds drop ad events — GAWrapperCpp does not implement them. Run on Android or iOS to see them.")

	_send_button(grid, "Send ad event", func(): _send_ad(
			action, ad_type, sdk_name, placement, mode, duration, reason))


func _build_session_tab(tabs: TabContainer) -> void:
	var grid := _tab_grid(tabs, "Session")

	var manual := _labelled_check(grid, "manual session handling", false)
	manual.toggled.connect(func(pressed: bool):
		ga.setEnabledManualSessionHandling(pressed)
		_log("setEnabledManualSessionHandling(%s)" % pressed))

	_send_button(grid, "Start session", func():
		ga.startSession()
		_log("startSession()"))
	_send_button(grid, "End session", func():
		ga.endSession()
		_log("endSession()"))


func _build_dimensions_tab(tabs: TabContainer) -> void:
	var grid := _tab_grid(tabs, "Dimensions")

	var global_fields := _labelled_edit(grid, "global custom fields (JSON)", '{"sample":"true"}')
	var d1 := _option(grid, "custom dimension 01", DIMENSIONS_01)
	var d2 := _option(grid, "custom dimension 02", DIMENSIONS_02)
	var d3 := _option(grid, "custom dimension 03", DIMENSIONS_03)

	_note(grid, "The external user id is set in Setup: the SDK only accepts it before init().")

	_send_button(grid, "Apply", func(): _on_apply_dimensions_pressed(global_fields, d1, d2, d3))


func _build_info_panel(parent: Node) -> void:
	var column := VBoxContainer.new()
	column.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	parent.add_child(column)

	var panel := _titled_panel(column, "Identifiers")
	var grid := GridContainer.new()
	grid.columns = 2
	panel.add_child(grid)

	for entry in [["user_id", "User id"], ["ext_user_id", "External user id"],
			["ab_id", "A/B testing id"], ["ab_variant_id", "A/B variant id"],
			["configs_ready", "Remote configs ready"], ["session_time", "Elapsed session time"],
			["all_sessions_time", "Elapsed time, all sessions"]]:
		_label(grid, entry[1])
		var value := Label.new()
		value.text = "—"
		value.size_flags_horizontal = Control.SIZE_EXPAND_FILL
		grid.add_child(value)
		_info_labels[entry[0]] = value

	var configs_panel := _titled_panel(column, "Remote configs")
	configs_panel.size_flags_vertical = Control.SIZE_EXPAND_FILL

	_configs_view = TextEdit.new()
	_configs_view.editable = false
	_configs_view.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_configs_view.custom_minimum_size = Vector2(0, 160)
	_configs_view.placeholder_text = "waiting for remote_configs_updated…"
	configs_panel.add_child(_configs_view)

	var lookup := GridContainer.new()
	lookup.columns = 2
	configs_panel.add_child(lookup)

	_label(lookup, "key")
	_config_key_edit = _line_edit(lookup, "legacy_test", 220)
	_label(lookup, "default value")
	_config_default_edit = _line_edit(lookup, "fallback", 220)
	_needs_init.append(_config_key_edit)
	_needs_init.append(_config_default_edit)

	var lookup_button := Button.new()
	lookup_button.text = "Look up value"
	lookup_button.pressed.connect(_on_lookup_pressed)
	configs_panel.add_child(lookup_button)
	_needs_init.append(lookup_button)

	_config_result = TextEdit.new()
	_config_result.editable = false
	_config_result.custom_minimum_size = Vector2(0, 60)
	configs_panel.add_child(_config_result)

	# the identifiers change over time (session length, ids assigned after init)
	var timer := Timer.new()
	timer.wait_time = 1.0
	timer.autostart = true
	timer.timeout.connect(_refresh_info)
	add_child(timer)


func _build_log(parent: Node) -> void:
	var panel := _titled_panel(parent, "Log")

	_log_view = RichTextLabel.new()
	_log_view.bbcode_enabled = true
	_log_view.scroll_following = true
	_log_view.custom_minimum_size = Vector2(0, 150)
	panel.add_child(_log_view)


# --------------------------------------------------------- ui building blocks

func _titled_panel(parent: Node, title: String) -> VBoxContainer:
	var box := VBoxContainer.new()
	box.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	parent.add_child(box)

	var heading := Label.new()
	heading.text = title
	heading.add_theme_font_size_override("font_size", 18)
	box.add_child(heading)

	return box


func _tab_grid(tabs: TabContainer, title: String) -> GridContainer:
	var margin := MarginContainer.new()
	margin.name = title
	for side in ["margin_left", "margin_top", "margin_right", "margin_bottom"]:
		margin.add_theme_constant_override(side, 10)
	tabs.add_child(margin)

	var grid := GridContainer.new()
	grid.columns = 2
	grid.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	margin.add_child(grid)

	return grid


func _note(parent: Node, text: String) -> Label:
	parent.add_child(Control.new()) # keeps the note in the value column

	var note := Label.new()
	note.text = text
	note.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	note.custom_minimum_size = Vector2(320, 0)
	note.modulate = Color(1.0, 0.8, 0.45)
	parent.add_child(note)

	return note


func _label(parent: Node, text: String) -> Label:
	var label := Label.new()
	label.text = text
	parent.add_child(label)
	return label


func _line_edit(parent: Node, text: String, min_width: int) -> LineEdit:
	var edit := LineEdit.new()
	edit.text = text
	edit.custom_minimum_size = Vector2(min_width, 0)
	parent.add_child(edit)
	return edit


func _labelled_edit(parent: Node, label: String, text: String) -> LineEdit:
	_label(parent, label)
	var edit := _line_edit(parent, text, 260)
	_needs_init.append(edit)
	return edit


func _check_box(parent: Node, pressed: bool) -> CheckBox:
	var check := CheckBox.new()
	check.button_pressed = pressed
	parent.add_child(check)
	return check


func _labelled_check(parent: Node, label: String, pressed: bool) -> CheckBox:
	_label(parent, label)
	var check := _check_box(parent, pressed)
	_needs_init.append(check)
	return check


func _option(parent: Node, label: String, values: Array) -> OptionButton:
	_label(parent, label)

	var option := OptionButton.new()
	for value in values:
		option.add_item(str(value))
	option.selected = 0
	parent.add_child(option)
	_needs_init.append(option)

	return option


func _spin(parent: Node, label: String, value: float, step: float, min_value: float, max_value: float) -> SpinBox:
	_label(parent, label)

	var spin := SpinBox.new()
	spin.min_value = min_value
	spin.max_value = max_value
	spin.step = step
	spin.value = value
	parent.add_child(spin)
	_needs_init.append(spin)

	return spin


func _send_button(parent: Node, text: String, action: Callable) -> Button:
	parent.add_child(Control.new()) # keeps the button in the value column

	var button := Button.new()
	button.text = text
	button.pressed.connect(action)
	parent.add_child(button)
	_needs_init.append(button)

	return button
