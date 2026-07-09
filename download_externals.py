import os
import sys
import zipfile
import shutil
import urllib.request
import urllib.error
import json

def download_and_update_sdk(sdk_info):
    """
    Downloads the specified version of the GameAnalytics C++ SDK from sdk_info,
    extracts it, and updates the headers and binaries in the plugin directory.

    :param sdk_info: A dictionary containing 'name', 'version', and 'url' of the SDK.
    """
    # Determine the root directory and plugin directory relative to this script
    root_dir = os.path.dirname(os.path.abspath(__file__))
    plugin_dir = os.path.join(root_dir, "src")

    version = sdk_info["version"]
    base_url = sdk_info["url"]

    # Construct the download URL
    version_tag = f"v{version}"
    zip_filename = f"ga-sdk-static-{version_tag}.zip"
    download_url = f"{base_url}releases/download/{version_tag}/{zip_filename}"

    # Download the zip file
    print(f"Downloading {download_url}...")
    zip_path = os.path.join(os.getcwd(), zip_filename)
    try:
        with urllib.request.urlopen(download_url) as response, open(zip_path, 'wb') as f:
            shutil.copyfileobj(response, f)
    except urllib.error.URLError as e:
        print(f"Error downloading file: {e}")
        sys.exit(1)

    # Extract the zip file
    extract_dir = os.path.join(os.getcwd(), f"ga-sdk-static-{version_tag}")
    print(f"Extracting {zip_path} to {extract_dir}...")
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(extract_dir)

    final_release_dir = os.path.join(extract_dir, "static-release")

    # Update headers
    include_src = os.path.join(final_release_dir, 'include')
    include_dst = os.path.join(plugin_dir, 'desktop')

    print(f"Copying headers from {include_src} to {include_dst}...")
    shutil.copytree(include_src, include_dst, dirs_exist_ok=True)

    # Update binaries per platform
    platforms = [
        ('macOS-latest-clang-Release', 'libGameAnalytics.a', 'macos'),
        ('ubuntu-latest-clang-Release', 'libGameAnalytics.a', 'linux'),
        ('windows-latest-cl-Release', 'GameAnalytics.lib', 'windows'),
    ]

    for folder_name, lib_name, platform_name in platforms:
        lib_src = os.path.join(final_release_dir, folder_name, lib_name)
        lib_dst_dir = os.path.join(plugin_dir, 'libs', platform_name)
        lib_dst = os.path.join(lib_dst_dir, lib_name)
        print(f"Copying {lib_src} to {lib_dst}...")
        if not os.path.exists(lib_dst_dir):
            os.makedirs(lib_dst_dir)
        shutil.copy2(lib_src, lib_dst)

    # Clean up
    print("Cleaning up...")
    os.remove(zip_path)
    shutil.rmtree(extract_dir)
    print("Update complete.")

def download_and_update_js_sdk(sdk_info):
    """
    Downloads the specified version of the GameAnalytics JavaScript SDK from sdk_info
    and updates GameAnalytics.js in the plugin's web directory.

    :param sdk_info: A dictionary containing 'name', 'version', and 'url' of the SDK.
    """
    # Determine the root directory and web directory relative to this script
    root_dir = os.path.dirname(os.path.abspath(__file__))
    web_dir = os.path.join(root_dir, "src", "web")

    version = sdk_info["version"]
    base_url = sdk_info["url"]

    # Construct the download URL for the built dist file at the release tag.
    # Use the "construct" bundle, which inlines CryptoJS, since this plugin
    # evals the file standalone rather than loading it through a module bundler.
    version_tag = f"v{version}"
    raw_base_url = base_url.replace("github.com", "raw.githubusercontent.com").rstrip("/")
    download_url = f"{raw_base_url}/{version_tag}/dist/GameAnalytics.construct.js"

    # Download GameAnalytics.js directly into the web directory
    dest_path = os.path.join(web_dir, "GameAnalytics.js")
    print(f"Downloading {download_url}...")
    try:
        with urllib.request.urlopen(download_url) as response, open(dest_path, 'wb') as f:
            shutil.copyfileobj(response, f)
    except urllib.error.URLError as e:
        print(f"Error downloading file: {e}")
        sys.exit(1)

    print(f"Updated {dest_path}.")
    print("Update complete.")

def process_dependencies():
    """
    Processes dependencies listed in Dependencies.json.
    For GA-SDK-CPP, it downloads and updates the C++ SDK.
    For GA-SDK-JAVASCRIPT, it downloads and updates the JavaScript SDK.
    For other dependencies, it prints that they are not implemented yet.
    """
    # Determine the root directory
    root_dir = os.path.dirname(os.path.abspath(__file__))

    # Load dependencies from Dependencies.json
    dependencies_file = os.path.join(root_dir, 'Dependencies.json')
    try:
        with open(dependencies_file, 'r') as f:
            dependencies = json.load(f)
    except FileNotFoundError:
        print(f"Dependencies.json not found in {root_dir}")
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"Error parsing Dependencies.json: {e}")
        sys.exit(1)

    # Process each dependency
    for sdk_info in dependencies:
        sdk_name = sdk_info.get("name", "")
        if sdk_name == "GA-SDK-CPP":
            print(f"Processing dependency: {sdk_name}")
            download_and_update_sdk(sdk_info)
        elif sdk_name == "GA-SDK-JAVASCRIPT":
            print(f"Processing dependency: {sdk_name}")
            download_and_update_js_sdk(sdk_info)
        else:
            print(f"Dependency '{sdk_name}' is not implemented yet.")

if __name__ == "__main__":
    process_dependencies()