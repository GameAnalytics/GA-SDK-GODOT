#pragma once

#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/classes/json.hpp"

#include "GAWrapper.h"

class GameAnalytics : public godot::Object
{
    GDCLASS(GameAnalytics, godot::Object);

    using String = godot::String;
    using Dictionary = godot::Dictionary;
    using PackedStringArray = godot::PackedStringArray;
    using Object = godot::Object;
    using Variant = godot::Variant;
    using Array = godot::Array;

protected:
    static void _bind_methods();

    bool _wasInitialized = false;
    std::unique_ptr<gameanalytics::GAWrapper> _impl;

public:
    static GameAnalytics* get_singleton();
    GameAnalytics();
    ~GameAnalytics();

    void configureAvailableCustomDimensions01(const PackedStringArray &customDimensions);
    void configureAvailableCustomDimensions02(const PackedStringArray &customDimensions);
    void configureAvailableCustomDimensions03(const PackedStringArray &customDimensions);

    void configureAvailableResourceCurrencies(const PackedStringArray &resourceCurrencies);
    void configureAvailableResourceItemTypes(const PackedStringArray &resourceItemTypes);

    void configureBuild(const String &build);
    void configureAutoDetectAppVersion(bool flag);
    void configureUserId(const String &userId);
    void configureSdkGameEngineVersion(const String &version);
    void configureGameEngineVersion(const String &version);

    String getUserId() const;
    String getExternalUserId() const;
    String getABTestingId() const;
    String getABTestingVariantId() const;

    void setExternalUserId(String const& extId);

    void useRandomizedId(bool value);

    void init(const String &gameKey, const String &secretKey);

    void addBusinessEvent(const String& currency, 
                          int amount, 
                          const String& itemType, 
                          const String& itemId, 
                          const String& cartType, 
                          const Dictionary& options = {});
    
    void addResourceEvent(const String& flow, 
                          const String& currency, 
                          float amount, 
                          const String& itemType, 
                          const String& itemId, 
                          const Dictionary& options = {});
    
    void addProgressionEvent(const String& status,
                             const String& progression1,
                             const String& progression2,
                             const String& progression3,
                             const Dictionary &options = {});

    void addProgressionEventWithScore(const String& status,
                             const String& progression1,
                             const String& progression2,
                             const String& progression3,
                             int score);

    void addDesignEvent(const String& eventId, 
                        const Dictionary &options = {});

    void addDesignEventWithValue(const String& eventId, 
                                 float value);
    
    void addErrorEvent(const String& severity, 
                       const String& message, 
                       const Dictionary &options);
    
    void addAdEvent(const String& adAction,
                    const String& adType,
                    const String& adSdkName,
                    const String& adPlacement,
                    const Dictionary &options);

    void setEnabledInfoLog(bool flag);
    void setEnabledVerboseLog(bool flag);
    void setEnabledManualSessionHandling(bool flag);
    void setEnabledErrorReporting(bool flag);
    void setEnabledEventSubmission(bool flag);

    void setCustomDimension01(const String &dimension);
    void setCustomDimension02(const String &dimension);
    void setCustomDimension03(const String &dimension);

    void setGlobalCustomEventFields(const String &customFields);

    void startSession();
    void endSession();
    void onQuit();

    String getRemoteConfigsValueAsString(String const& key, String const& defaultValue);
    godot::Variant getRemoteConfigsValueAsJSON(String const& key);
    
    bool isRemoteConfigsReady();
    String getRemoteConfigsContentAsString();

    void enableSDKInitEvent(bool flag);
    void enableFpsHistogram(godot::Callable tracker);
    void enableMemoryHistogram(bool flag);
    void enableHealthHardwareInfo(bool flag);

    void setWritablePath(String const& path);
};
