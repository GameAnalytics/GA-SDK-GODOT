def can_build(env, platform):
    return platform == "iphone" or platform == "android" or platform == "windows" or platform == "osx"  # or platform == "x11"


def configure(env):
    if (env["platform"] == "android"):
        env.android_add_maven_repository("url 'https://maven.gameanalytics.com/release'")
        env.android_add_dependency("implementation 'com.gameanalytics.sdk:gameanalytics-android:5.2.5'")
        env.android_add_java_dir("android/src/")
        env.disable_module()

    if (env["platform"] == "iphone"):
        env.Append(FRAMEWORKPATH=[
            '#modules/gameanalytics/ios/lib'
        ])

        env.Append(CPPPATH=['#core'])

        env.Append(LINKFLAGS=[
            '-ObjC',
            '-framework', 'AdSupport',
            '-framework', 'SystemConfiguration',
            '-framework', 'GameAnalytics',
            '-l', 'sqlite3',
            '-l', 'z'
        ])

    if env["platform"] == "windows":
        if env["bits"] == "32":
            env.Append(LIBPATH=["#modules/gameanalytics/cpp/lib/win32"])
            env.Append(LINKFLAGS=["GameAnalytics.lib"])
        else:
            env.Append(LIBPATH=["#modules/gameanalytics/cpp/lib/win64"])
            env.Append(LINKFLAGS=["GameAnalytics.lib"])

    elif env["platform"] == "osx":
        env.Append(LIBPATH=["#modules/gameanalytics/cpp/lib/osx"])
        env.Append(LIBS=["libGameAnalytics.dylib"])

    elif env["platform"] == "x11":
        env.Append(LIBPATH=["#modules/gameanalytics/cpp/lib/linux"])
        env.Append(LINKFLAGS=["libGameAnalytics.so"])
