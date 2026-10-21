extends Node

# Temporary on-device smoke check for the Android wrapper.
#
# CI only runs the headless suite on linux, so the JNI path is never exercised
# on a real runtime. This scene drives the calls that resolve Java classes and
# methods, so a bad descriptor or a missing class shows up in logcat.
#
# Offline on purpose: without init() the Java side rejects the events, but the
# class/method lookups in GAWrapperAndroid still run, which is where the bugs are.

const TAG := "GA_SMOKE"

func _ready() -> void:
	var ok := true

	if not Engine.has_singleton("GameAnalytics"):
		print("%s FAIL singleton not registered" % TAG)
		get_tree().quit(1)
		return
	print("%s PASS singleton registered" % TAG)

	var ga: Object = Engine.get_singleton("GameAnalytics")

	ga.setEnabledInfoLog(true)
	ga.setEnabledVerboseLog(true)

	# plain business event, the pre-existing path
	ga.addBusinessEvent("USD", 100, "smoke_type", "smoke_id", "smoke_cart", {})
	print("%s PASS addBusinessEvent (no token) returned" % TAG)

	# the validated path: product_id + purchase_token resolve ReceiptInfo over JNI
	ga.addBusinessEvent("USD", 999, "gold_pack", "1000_gold", "shop", {
		"product_id": "com.gameanalytics.smoke.gold1000",
		"purchase_token": "smoke-purchase-token-abc123",
	})
	print("%s PASS addBusinessEvent (purchase_token) returned" % TAG)

	# transaction_id should land in the same token slot
	ga.addBusinessEvent("USD", 499, "gem_pack", "500_gems", "shop", {
		"transaction_id": "smoke-transaction-id-xyz789",
	})
	print("%s PASS addBusinessEvent (transaction_id) returned" % TAG)

	# explicit store override
	ga.addBusinessEvent("USD", 199, "starter", "starter_pack", "shop", {
		"store": "google_play_store",
		"product_id": "com.gameanalytics.smoke.starter",
		"purchase_token": "smoke-token-explicit-store",
	})
	print("%s PASS addBusinessEvent (explicit store) returned" % TAG)

	# a couple of other JNI call sites, to catch collateral damage from the 7.2.0 bump
	ga.addDesignEvent("smoke:design", {})
	ga.addErrorEvent("info", "smoke error", {})
	print("%s PASS design + error events returned" % TAG)
	print("%s elapsed=%d" % [TAG, ga.getElapsedSessionTime()])

	print("%s DONE ok=%s" % [TAG, ok])
	await get_tree().create_timer(2.0).timeout
	get_tree().quit(0)
