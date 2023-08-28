extends Node
var ga
const GAME_KEYS = {
	"Android": "c6cfc80ff69d1e7316bf1e0c8194eda6",
	"iOS"    : "c6cfc 80ff69d1e7316bf1e0c8194eda6",
	"OSX"    : "c6cfc80ff69d1e7316bf1e0c8194eda6",
	"macOS"  : "c6cfc80ff69d1e7316bf1e0c8194eda6",
	"Windows": "c6cfc80ff69d1e7316bf1e0c8194eda6",
	"X11"    : "c6cfc80ff69d1e7316bf1e0c8194eda6",
	"HTML5"  : "c6cfc80ff69d1e7316bf1e0c8194eda6"
}

const SECRET_KEYS = {
	"Android": "e0ae4809f70e2fa96916c7060f417ae53895f18d",
	"iOS"    : "e0ae4809f70e2fa96916c7060f417ae53895f18d",
	"macOS"  : "e0ae4809f70e2fa96916c7060f417ae53895f18d",
	"Windows": "e0ae4809f70e2fa96916c7060f417ae53895f18d",
	"X11"    : "e0ae4809f70e2fa96916c7060f417ae53895f18d",
	"HTML5"  : "e0ae4809f70e2fa96916c7060f417ae53895f18d"
}

var platform_os = OS.get_name()

func _notification(what):
	if what == NOTIFICATION_WM_CLOSE_REQUEST :
		ga.onQuit()

func _ready():
	if(Engine.has_singleton("GameAnalytics")):
		ga = Engine.get_singleton("GameAnalytics")

		ga.setEnabledInfoLog(true)
		ga.setEnabledVerboseLog(true)

		ga.configureAvailableCustomDimensions01(["ninja", "samurai"])
		ga.configureAvailableCustomDimensions02(["whale", "dolphin"])
		ga.configureAvailableCustomDimensions03(["horde", "alliance"])
		ga.configureAvailableResourceCurrencies(["gold", "gems"])
		ga.configureAvailableResourceItemTypes(["boost", "lives"])

		ga.configureBuild("0.1.0")
		ga.configureAutoDetectAppVersion(true)
		ga.configureUserId("my_custom_id")

		ga.init(GAME_KEYS[platform_os], SECRET_KEYS[platform_os])
	get_node("Button").connect("pressed", Callable(self, "_on_Button_pressed"))


func _on_Button_pressed():
	if GameAnalytics != null:
		GameAnalytics.addBusinessEvent({
			"currency": "USD",
			"amount": 100,
			"itemType": "gold",
			"itemId": "bigGold",
			"cartType": "shop",
			"receipt": "[RECEIPT]",
			"signature": "[SIGNATURE]"
		})

		GameAnalytics.addBusinessEvent({
			"currency": "USD",
			"amount": 100,
			"itemType": "gold",
			"itemId": "bigGold",
			"cartType": "shop",
			"autoFetchReceipt": true
		})

		GameAnalytics.addResourceEvent({
			"flowType": "Source",
			"currency": "gold",
			"amount": 50.5,
			"itemType": "boost",
			"itemId": "superBoost"
		})

		GameAnalytics.addResourceEvent({
			"flowType": "Sink",
			"currency": "gold",
			"amount": 50.5,
			"itemType": "boost",
			"itemId": "superBoost"
		})

		GameAnalytics.addProgressionEvent({
			"progressionStatus": "Start",
			"progression01": "world1",
			"progression02": "area1",
			"progression03": "level1"
		})

		GameAnalytics.addProgressionEvent({
			"progressionStatus": "Complete",
			"progression01": "world1",
			"progression02": "area1",
			"progression03": "level1",
			"score": 666.66
		})

		GameAnalytics.addProgressionEvent({
			"progressionStatus": "Start",
			"progression01": "world1",
			"progression02": "area1"
		})

		GameAnalytics.addProgressionEvent({
			"progressionStatus": "Fail",
			"progression01": "world1",
			"progression02": "area1",
			"score": 666.66
		})

		GameAnalytics.addProgressionEvent({
			"progressionStatus": "Start",
			"progression01": "world1"
		})

		GameAnalytics.addProgressionEvent({
			"progressionStatus": "Complete",
			"progression01": "world1",
			"score": 666.66
		})

		GameAnalytics.addDesignEvent({
			"eventId": "my:event"
		})

		GameAnalytics.addDesignEvent({
			"eventId": "my:event",
			"value": 666.66
		})

		GameAnalytics.addErrorEvent({
			"severity": "Error",
			"message": "THIS IS AN ERROR!!!"
		})

		print("/GameAnalytics: " + str(GameAnalytics.isRemoteConfigsReady()))
		print("/GameAnalytics: " + GameAnalytics.getRemoteConfigsContentAsString())
		print("/GameAnalytics: " + GameAnalytics.getRemoteConfigsValueAsString({"key": "ga_test", "defaultValue": "my_defaultValue"}))
