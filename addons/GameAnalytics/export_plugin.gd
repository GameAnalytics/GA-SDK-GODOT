@tool
extends EditorPlugin

# A class member to hold the editor export plugin during its lifecycle.
var export_plugin : GameAnalyticsExportPlugin

func _enter_tree():
	# Initialization of the plugin goes here.
	export_plugin = GameAnalyticsExportPlugin.new()
	add_export_plugin(export_plugin)

func _exit_tree():
	# Clean-up of the plugin goes here.
	remove_export_plugin(export_plugin)
	export_plugin = null

class GameAnalyticsExportPlugin extends EditorExportPlugin:
	# Plugin's name.
	var _plugin_name = "GameAnalytics"

	const JS_PATH := "res://addons/GameAnalytics/web/GameAnalytics.js"
	const AAR_PATH := "res://addons/GameAnalytics/bin/android/godotgameanalytics.aar"

	func _export_begin(features, is_debug, path, flags):
		print("Exporting plugin for GA")
		var isWeb = features.has("web")
		
		if not isWeb:
			return
		
		print("Export GameAnalytics for web")
		
		if not FileAccess.file_exists(JS_PATH):
			print("GameAnalytics file not found")
			return
		
		var data = FileAccess.get_file_as_bytes(JS_PATH)
		
		var where : String = path.get_base_dir() + '/GameAnalytics.js'
		print('Copy file to:' + where)
		
		var out : FileAccess = FileAccess.open(where, FileAccess.WRITE)
		out.store_buffer(data)
		out.close()

	func _supports_platform(platform):
		return true

	# Return the paths of the plugin's AAR binaries relative to the 'addons' directory.
	func _get_android_libraries(platform, debug):
		print("add aar")
		return PackedStringArray([AAR_PATH])
	
	func _get_android_dependencies_maven_repos(platform, debug):
		print("add maven repos")
		return PackedStringArray(["https://maven.gameanalytics.com/release"])
	
	func _get_android_dependencies(platform, debug):
		print("add android dependencies")
		return PackedStringArray(["com.gameanalytics.sdk:gameanalytics-android:7.0.1"])

	# Return the plugin's name.
	func _get_name():
		return _plugin_name
