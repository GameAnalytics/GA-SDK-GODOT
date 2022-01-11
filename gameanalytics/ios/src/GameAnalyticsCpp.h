#pragma once

#include "core/array.h"
#include "core/variant.h"

class GameAnalyticsCpp {
public:
    static void configureAvailableCustomDimensions01(const PoolStringArray& list);
    static void configureAvailableCustomDimensions02(const PoolStringArray& list);
    static void configureAvailableCustomDimensions03(const PoolStringArray& list);

    static void configureAvailableResourceCurrencies(const PoolStringArray &list);
    static void configureAvailableResourceItemTypes(const PoolStringArray &list);

    static void configureBuild(const char *build);
    static void configureAutoDetectAppVersion(bool flag);
    static void configureUserId(const char *userId);
    static void configureSdkGameEngineVersion(const char *version);
    static void configureGameEngineVersion(const char *version);

    static void initialize(const char *gameKey, const char *gameSecret);

    static void addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *fields, bool mergeFields);
    static void addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *fields, bool mergeFields);
    static void addResourceEvent(int flowType, const char *currency, float amount, const char *itemType, const char *itemId, const char *fields, bool mergeFields);
    static void addProgressionEvent(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, const char *fields, bool mergeFields);
    static void addProgressionEventWithScore(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const char *fields, bool mergeFields);
    static void addDesignEvent(const char *eventId, const char *fields, bool mergeFields);
    static void addDesignEventWithValue(const char *eventId, float value, const char *fields, bool mergeFields);
    static void addErrorEvent(int severity, const char *message, const char *fields, bool mergeFields);
    static void addAdEvent(int adAction, int adType, const char *adSdkName, const char *adPlacement, const char *fields, bool mergeFields);
    static void addAdEventWithDuration(int adAction, int adType, const char *adSdkName, const char *adPlacement, int duration, const char *fields, bool mergeFields);
    static void addAdEventWithNoAdReason(int adAction, int adType, const char *adSdkName, const char *adPlacement, int noAdReason, const char *fields, bool mergeFields);

    static void setEnabledInfoLog(bool flag);
    static void setEnabledVerboseLog(bool flag);
    static void setEnabledManualSessionHandling(bool flag);
    static void setEnabledErrorReporting(bool flag);
    static void setEnabledEventSubmission(bool flag);

    static void setCustomDimension01(const char *dimension);
    static void setCustomDimension02(const char *dimension);
    static void setCustomDimension03(const char *dimension);

    static void setGlobalCustomEventFields(const char *customFields);

    static void startSession();
    static void endSession();

    static const String getRemoteConfigsValueAsString(const char *key);
    static const String getRemoteConfigsValueAsString(const char *key, const char *defaultValue);
    static bool isRemoteConfigsReady();
    static const String getRemoteConfigsContentAsString();
};
