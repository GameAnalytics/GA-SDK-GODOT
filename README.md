# GA-SDK-GODOT
GameAnalytics SDK for Godot.

For Android, iOS and OSX you can also get the SDK via Nativelib like described [here](https://github.com/GameAnalytics/godot-gameanalytics).

Documentation is located [here](https://gameanalytics.com/docs/item/godot-sdk).

If you have any issues or feedback regarding the SDK, please contact our friendly support team [here](https://gameanalytics.com/contact).

> :information_source:
>
> The Godot SDK include support for **iOS**, **Android**, **Web**, **Windows**, **Mac** and **Linux** platforms
>
> Requirements:
> * **Godot:** 3.1+  &nbsp;

Changelog
---------
<!--(CHANGELOG_TOP)-->
**2.3.1**
* changed tagret sdk to 30 instead of 31 for android

**2.3.0**
* added ad events for Android and iOS

**2.2.3**
* removed imei identifiers and other alternative identifiers from user identifier logic (android)

**2.2.2**
* added error events to be sent for invalid custom event fields used
* added optional mergeFields argument to event methods to merge with global custom fields instead of overwrite them

**2.2.1**
* fixed missing custom event fields for when trying to fix missing session end events

**2.2.0**
* added global custom event fields function to allow to add custom fields to events sent automatically by the SDK

**2.1.1**
* added functionality to force a new user in a/b testing without having to uninstall app first, simply use custom user id function to set a new user id which hasn't been used yet

**2.1.0**
* added custom event fields feature

**2.0.0**
* Changed user identifier logic in preparation for Google changes to GAID. User id for a new install is now a randomised GUID. Existing installs that update SDK will continue using previous identifier logic. It is recommended to update as soon as possible to reduce impact on calculated metrics.

**1.3.6**
* small fix

**1.3.5**
* republished plugin on NativeLib due to malformed urls

**1.3.4**
* ios nativelib fixes

**1.3.3**
* fixed ios nativelib errors

**1.3.1**
* small fixes

**1.3.0**
* added distribution via nativelib for android, ios and osx

**1.2.9**
* fixed android bugs

**1.2.8**
* fixed VerifyError for Android for Godot 3.3
* fixed mutex compile error for Godot 3.3

**1.2.7**
* added idfa consent status to evnts (ios)

**1.2.6**
* fixed linux dependencies

**1.2.5**
* added missing libs for linux

**1.2.4**
* fixed dependencies iOS (min. XCode 12 required)

**1.2.3**
* removed memory info from automatic crash reports

**1.2.2**
* fixed crash when closing editor and GA module was loaded

**1.2.1**
* fixed compiling using mingw

**1.2.0**
* added support for web

**1.1.0**
* added support for Linux

**1.0.4**
* corrected overwritten fix

**1.0.3**
* small correction for compile error on ios
* native libs updated

**1.0.2**
* improved user identifier flow for ios (ios)

**1.0.1**
* updated ga android native lib to avoid allowbackup build error

**1.0.0**
* initial version
