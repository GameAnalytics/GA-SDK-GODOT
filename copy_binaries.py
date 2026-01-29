import os
import shutil

src = './bin'
dst = './example/addons/GameAnalytics/bin'

config = 'debug'
libname = 'libGodotGameAnalytics'

android_path = 'example/addons/GameAnalyticsAndroid'

def get_lib_path(platform: str, ext: str):
    return os.path.join(platform, config, '{}.{}'.format(libname, ext))

def copy_android_aar(config : str):
    aar_path = 'android/godotgameanalytics/build/outputs/aar/godotgameanalytics-{}.aar'.format(config)
    plugin_path = os.path.join(android_path, 'godotgameanalytics.aar')

    if not os.path.exists(aar_path):
        print("Android aar not found, skipping step...")
        return

    print('copying android plugin from', aar_path, 'to', plugin_path)
    shutil.copyfile(aar_path, plugin_path)

platforms    = ['macos', 'windows', 'linux', 'android', 'ios', 'web']
exts         = ['dylib', 'dll', 'so', 'so', '.framework', 'wasm']

num_libs = len(platforms)

copy_android_aar(config)

for i in range(0, num_libs):
    platform = platforms[i]
    ext = exts[i]
    lib = get_lib_path(platform, ext)
    binary = '{}.{}'.format(libname, ext)

    src_bin = os.path.join(src, lib)
    dst_bin = os.path.join(dst, platform, binary)

    if(os.path.exists(src_bin)):
        print('copying binary:', dst_bin, 'from path', src_bin)
        os.makedirs(os.path.dirname(dst_bin), exist_ok=True)
        shutil.copy(src_bin, dst_bin)