#!/usr/bin/env python
import os
import sys
from glob import glob

env = SConscript("godot-cpp/SConstruct")

sources = Glob("src/gameanalytics/*.cpp")

platform_path = 'src'
libname = ''

target = 'debug'

if env['target'] == 'template_release':
    target = 'release'

binpath = 'bin/{}/{}'.format(env['platform'], target)
libpath = "src/libs"

################################

# iphone
if env['platform'] == 'ios':
    sources.append("src/ios/GAWrapperIOS.mm")
    libname = '{}/libGodotGameAnalytics{}'.format(binpath, env["SHLIBSUFFIX"])
    platform_path = os.path.join(platform_path, 'ios')
    # Use the appropriate framework path based on arch
    framework_path = "src/libs/iOS/GameAnalytics.xcframework/ios-arm64"
    env.Append(LINKFLAGS=["-framework", "GameAnalytics", "-F", framework_path])

# android
if env['platform'] == 'android':
    sources.append("src/android/GAWrapperAndroid.cpp")
    libname = '{}/libGodotGameAnalytics{}'.format(binpath, env["SHLIBSUFFIX"])
    platform_path = os.path.join(platform_path, 'android')
    env.Append(LINKFLAGS=["-llog"])

# desktop
if env["platform"] == "windows" or env["platform"] == "macos" or env["platform"] == "osx" or env["platform"] == "linux":
    sources.append("src/desktop/GAWrapperCpp.cpp")
    libname = '{}/libGodotGameAnalytics{}'.format(binpath, env["SHLIBSUFFIX"])
    platform_path = os.path.join(platform_path, 'desktop')

    env.Append(LIBS=["GameAnalytics", "curl", "ssl"])

    libpath = os.path.join(libpath, env['platform'])

    if(env["platform"] == "windows"):
        env.Append(LIBS=[
            "user32",
            "kernel32",
            "advapi32",
            "ws2_32",
            "bcrypt",
            "crypt32",
            "secur32",
            "shell32",
            "Ole32",
            "eay32",
            "ssleay32"
        ])

    if(env['platform'] == 'linux'):
        env.Append(LIBS=["crypto"])

    if(env["platform"] == "macos"):
        env.Append(LINKFLAGS=[
            "-framework", "CoreFoundation",
            "-framework", "Foundation",
            "-framework", "CoreServices",
            "-framework", "SystemConfiguration",
            "-framework", "Metal",
            "-framework", "MetalKit"
            ])
        env.Append(LIBS=["crypto"])

# web
if env["platform"] == "web":
    sources.append("src/web/GAWrapperWeb.cpp")
    libname = '{}/libGodotGameAnalytics{}'.format(binpath, env["SHLIBSUFFIX"])
    platform_path = os.path.join(platform_path, 'web')

#################################

env.Append(CPPPATH=["src/gameanalytics",
    platform_path,
    'godot-cpp/godot_headers/', 
    'godot-cpp/include/', 
    'godot-cpp/include/core/', 
    'godot-cpp/include/gen/'])

env.Append(LIBPATH=[libpath, os.path.join(libpath, '3rdParty')])

library = env.SharedLibrary(
    libname,
    source=sources,
)

Default(library)
