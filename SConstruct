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
if env['platform'] == 'iphone':
    sources.append("src/ios/GAWrapperIOS.mm")
    libname = '{}/libGodotGameAnalytics.{}'.format(binpath, env["SHLIBSUFFIX"])
    platform_path = os.path.join(platform_path, 'ios')

# android
if env['platform'] == 'android':
    sources.append("src/android/GAWrapperAndroid.cpp")
    libname = '{}/libGodotGameAnalytics{}'.format(binpath, env["SHLIBSUFFIX"])
    platform_path = os.path.join(platform_path, 'android')
    env.Append(LINKFLAGS=["-llog"])

# desktop
if env["platform"] == "windows" or env["platform"] == "macos" or env["platform"] == "osx" or env["platform"] == "x11":
    sources.append("src/desktop/GAWrapperCpp.cpp")
    libname = '{}/libGodotGameAnalytics{}'.format(binpath, env["SHLIBSUFFIX"])
    platform_path = os.path.join(platform_path, 'desktop')

    env.Append(LIBS=["GameAnalytics"])
    
    if(env["platform"] == "macos"):
        libpath = os.path.join(libpath, 'Mac')
        env.Append(LINKFLAGS=[
            "-framework", "CoreFoundation",
            "-framework", "Foundation",
            "-framework", "CoreServices",
            "-framework", "SystemConfiguration",
            "-framework", "Metal",
            "-framework", "MetalKit"
        ])

        env.Append(LIBS=["crypto", "curl", "ssl"])

# web
if env["platform"] == "javascript":
    sources.append("src/javascript/GAWrapperWeb.cpp")
    libname = '{}/libGodotGameAnalytics{}'.format(binpath, env["SHLIBSUFFIX"])
    platform_path = os.path.join(platform_path, 'javascript')

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
