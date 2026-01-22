extends Node
var ga

const GAME_KEY 	 = "INSERT YOUR GAME KEY HERE"
const SECRET_KEY = "INSERT YOUR SECRET KEY HERE"

var platform_os = OS.get_name()

func fpsTracker():
	return 60.0

func _ready():
	print(Engine.get_singleton_list())
	
	if(Engine.has_singleton("GameAnalyticsAndroid")):
		print("Running GameAnalytics on android")
	
	if(Engine.has_singleton("GameAnalytics")):
		print("GA singleton found")
		ga = Engine.get_singleton("GameAnalytics")

		ga.setEnabledInfoLog(true)
		ga.setEnabledVerboseLog(true)
		
		ga.enableMemoryHistogram(true)
		ga.enableSDKInitEvent(true)
		ga.enableHealthHardwareInfo(true)
		ga.enableFpsHistogram(fpsTracker)
		
		ga.setExternalUserId("my_ext_uid")

		ga.configureAvailableCustomDimensions01(["ninja", "samurai"])
		ga.configureAvailableCustomDimensions02(["whale", "dolphin"])
		ga.configureAvailableCustomDimensions03(["horde", "alliance"])
		ga.configureAvailableResourceCurrencies(["gold", "gems"])
		ga.configureAvailableResourceItemTypes(["boost", "lives"])

		ga.configureBuild("0.1.0")
		ga.configureAutoDetectAppVersion(true)
		ga.configureUserId("my_custom_id")

		ga.init(GAME_KEY, SECRET_KEY)
	else:
		print("GA singleton not found")
	get_node("Button").connect("pressed", Callable(self, "_on_Button_pressed"))


func _on_Button_pressed():
	if ga != null:
		
		ga.addBusinessEvent("USD", 100, "gold", "gold_premium_pack", "shop", {});
		ga.addResourceEvent("source", "gold", 100, "gold_pile", "gold_pile_big", {})
		ga.addProgressionEventWithScore("start", "act2", "zone2", "level4", 1000)
		ga.addDesignEventWithValue("kill:boss:dragon", 5000)
		ga.addErrorEvent("critical", "Failed to load level", {})

		print("User Id is: " + ga.getUserId() + " and ext user id is: " + ga.getExternalUserId())
		
		print("/GameAnalytics: " + str(ga.isRemoteConfigsReady()))
		print("/GameAnalytics: " + ga.getRemoteConfigsContentAsString())
		print("/GameAnalytics: " + ga.getRemoteConfigsValueAsString("ga_test", "my_defaultValue"))
