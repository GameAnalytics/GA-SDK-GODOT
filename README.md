# GA-SDK-GODOT
GameAnalytics SDK for Godot.

Documentation is located [here](https://gameanalytics.com/docs/item/godot-sdk).

If you have any issues or feedback regarding the SDK, please contact our friendly support team [here](https://gameanalytics.com/contact).

## Supported Platforms

- Windows
- MacOS
- Linux
- Android
- iOS
- Web

## Requirements

- Godot 4.5 or newer
- SCons
- Python 3.6 or newer

## Compilation

Run the following command in the trunk of the cloned repository with the desired platform and configuration:

```sh
python ./build.py [platform] [debug or release]
```

Afterwards, you can open the `example/project.godot` project. The resulting `.gdextension` can be found in `example/addons/GameAnalytics`.

## Usage

After building the gdextension for your platform, you can copy the `example/addons/GameAnalytics` folder to your own project `your_project/addons/GameAnalytics`.

Inisde `Project Settings -> Plugins` enable the `GameAnalytics` plugin.

### Windows, Linux and MacOS

No additional steps are necessary, the plugin can also be used directly from within the editor.

### iOS

Export the project for iOS.

### Android

In the `Project` menu run `Install Android Build Template...`. Afterwards you will be able to export the plugin to Android.

### Web

In the `Export` dialog, add the following line in `HTML -> Head Include`:

```js
<script src="GameAnalytics.js"></script>
```

### Example app

`example/` sends every supported event type and displays the SDK's live state: user id, external
user id, A/B testing id and variant, and the remote configs (refreshed through the
`remote_configs_updated` signal). Open `example/project.godot` in Godot and press `Initialize`.

`python copy_binaries.py <debug|release>` (which `build.py` runs for you) fills in
`example/addons/GameAnalytics/bin` with the binaries you have built.

Two things behave differently per platform, and the app says so where it matters: ad events are
dropped on desktop (the C++ SDK does not implement them), and the external user id is only
accepted before `init`, so it lives in the setup panel rather than in a runtime setter.

The design and progression tabs each carry a toggle that routes the call through the
`addDesignEventWithValue` / `addProgressionEventWithScore` convenience overloads instead of the
options dictionary, so both code paths are exercised from the UI.

### Remote Configs

To be notified when remote configs have been fetched, connect to the `remote_configs_updated`
signal before calling `init`:

```gdscript
func _on_remote_configs_updated(configs: String) -> void:
	var data: Dictionary = JSON.parse_string(configs)
	print("remote configs: ", data)

func _ready():
	var ga = Engine.get_singleton("GameAnalytics")
	ga.remote_configs_updated.connect(_on_remote_configs_updated)
	ga.init(GAME_KEY, SECRET_KEY)
```

The signal carries the same payload as `getRemoteConfigsContentAsString()` and is always emitted
on the main thread. `registerRemoteConfigsListener(callable)` does the same thing for a single
`Callable`:

```gdscript
	ga.registerRemoteConfigsListener(_on_remote_configs_updated)
```

<br/>

## Changelog
---------

See [CHANGELOG.md](CHANGELOG.md).
