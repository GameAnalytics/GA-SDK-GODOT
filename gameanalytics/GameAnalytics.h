#pragma once

#include "core/object/ref_counted.h"
#include "core/variant/variant.h"

class GameAnalytics : public Object
{
    GDCLASS(GameAnalytics, Object);

protected:
    static void _bind_methods();
    static GameAnalytics *instance;

public:
    static GameAnalytics *get_singleton();
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

    void init(const String &gameKey, const String &secretKey);

    void addBusinessEvent(const Dictionary &options);
    void addResourceEvent(const Dictionary &options);
    void addProgressionEvent(const Dictionary &options);
    void addDesignEvent(const Dictionary &options);
    void addErrorEvent(const Dictionary &options);
    void addAdEvent(const Dictionary &options);

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

    String getRemoteConfigsValueAsString(const Dictionary &options);
    bool isRemoteConfigsReady();
    String getRemoteConfigsContentAsString();
};
