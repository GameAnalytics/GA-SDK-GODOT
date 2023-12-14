def can_build(env, platform):
    return platform == "iphone" or platform == "android" or platform == "windows" or platform == "osx" or platform == "macos" or platform == "x11" or platform == "javascript"


def configure(env):
    if (env["platform"] == "android"):
        env.android_add_maven_repository("url 'https://maven.gameanalytics.com/release'")
        env.android_add_dependency("implementation 'com.gameanalytics.sdk:gameanalytics-android:6.2.9'")
        env.android_add_dependency(
            "implementation 'com.google.android.gms:play-services-appset:16.0.2'")
        env.android_add_java_dir("android/src/")
        env.disable_module()
    elif (env["platform"] == "iphone"):
        env.Append(FRAMEWORKPATH=[
            '#modules/gameanalytics/ios/lib'
        ])

        env.Append(CPPPATH=['#core'])

        env.Append(LINKFLAGS=[
            '-ObjC',
            '-framework', 'AdSupport',
            '-framework', 'SystemConfiguration',
            '-framework', 'AppTrackingTransparency',
            '-framework', 'GameAnalytics',
            '-l', 'sqlite3',
            '-l', 'z'
        ])
    elif env["platform"] == "windows":
        if env["bits"] == "32":
            env.Append(LIBPATH=["#modules/gameanalytics/cpp/lib/win32"])
            if env["use_mingw"]:
                env.Append(LIBS=["GameAnalytics"])
            else:
                env.Append(LINKFLAGS=["GameAnalytics.lib"])
        else:
            env.Append(LIBPATH=["#modules/gameanalytics/cpp/lib/win64"])
            if env["use_mingw"]:
                env.Append(LIBS=["GameAnalytics"])
            else:
                env.Append(LINKFLAGS=["GameAnalytics.lib"])
    elif env["platform"] == "osx" or env["platform"] == "macos":
        print("here!!!")
        env.Append(LIBPATH=["#modules/gameanalytics/cpp/lib/osx"])
        env.Append(LIBS=["libGameAnalytics.dylib"])
        env.Append(RPATH=["."])
    elif env["platform"] == "x11":
        env.Append(LIBPATH=["#modules/gameanalytics/cpp/lib/linux"])
        env.Append(LIBS=["libGameAnalytics.so", "libcurl.so", "libssl.so", "libcrypto.so"])
        env.Append(RPATH=["."])
