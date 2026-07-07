import subprocess
import argparse
import os
import glob
import shutil

from copy_binaries import copy_binaries

parser = argparse.ArgumentParser()
parser.add_argument("platform", choices=["ios", "android", "windows", "linux", "macos", "web"])
parser.add_argument("config", choices=["debug", "release"])
parser.add_argument("--clean", action="store_true", help="Delete all cached build data (SCons cache, object files, generated bindings, bin output) before building")
parser.add_argument("--arch", choices=["universal", "x86_64", "arm64"], default=None, help="Architecture to build for on macOS (default: universal). Ignored for other platforms.")
args = parser.parse_args()

config = args.config
platform = args.platform

def run(cmd):
    r = subprocess.run(cmd)
    print(r.stdout)
    print(r.stderr)

def clean():
    print('Deleting cached build data...')
    for sconsign in ['.sconsign.dblite', os.path.join('godot-cpp', '.sconsign.dblite')]:
        if os.path.isfile(sconsign):
            os.remove(sconsign)
    for path in ['bin', os.path.join('godot-cpp', 'bin'), os.path.join('godot-cpp', 'gen')]:
        if os.path.isdir(path):
            shutil.rmtree(path)
    for pattern in ['**/__pycache__', '**/*.o', '**/*.os', '**/*.d']:
        for match in glob.glob(pattern, recursive=True):
            if os.path.isdir(match):
                shutil.rmtree(match)
            else:
                os.remove(match)

if args.clean:
    clean()

print('Building for platform: {}-{}'.format(platform, config))

if platform == "ios":
    run(['sh', 'build_ios.sh', 'template_{}'.format(config)])
else:
    scons_cmd = ['scons', 'platform={}'.format(platform), 'target=template_{}'.format(config)]
    if platform == "macos" and args.arch is not None:
        scons_cmd.append('arch={}'.format(args.arch))
    run(scons_cmd)
    copy_binaries(config)



