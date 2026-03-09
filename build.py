import subprocess
import argparse

from copy_binaries import copy_binaries

parser = argparse.ArgumentParser()
parser.add_argument("platform", choices=["ios", "android", "windows", "linux", "macos", "web"])
parser.add_argument("config", choices=["debug", "release"])
args = parser.parse_args()

config = args.config
platform = args.platform

def run(cmd):
    r = subprocess.run(cmd)
    print(r.stdout)
    print(r.stderr)

print('Building for platform: {}-{}'.format(platform, config))

if platform == "ios":
    run(['sh', 'build_ios.sh', 'template_{}'.format(config)])
else:
    run(['scons', 'platform={}'.format(platform), 'target=template_{}'.format(config)])
    copy_binaries(config)



