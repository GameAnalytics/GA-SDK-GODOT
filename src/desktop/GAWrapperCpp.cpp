#include "GAWrapperCpp.h"
#include "GameAnalytics/GameAnalytics.h"

namespace gameanalytics
{
    void GAWrapperCpp::SetAvailableCustomDimensions01(const std::vector<std::string>& list) {
        GameAnalytics::configureAvailableCustomDimensions01(list);
    }

    void GAWrapperCpp::SetAvailableCustomDimensions02(const std::vector<std::string>& list) {
        GameAnalytics::configureAvailableCustomDimensions02(list);
    }

    void GAWrapperCpp::SetAvailableCustomDimensions03(const std::vector<std::string>& list) {
        GameAnalytics::configureAvailableCustomDimensions03(list);
    }

    void GAWrapperCpp::SetAvailableResourceCurrencies(const std::vector<std::string>& list) {
        GameAnalytics::configureAvailableResourceCurrencies(list);
    }

    void GAWrapperCpp::SetAvailableResourceItemTypes(const std::vector<std::string>& list) {
        GameAnalytics::configureAvailableResourceItemTypes(list);
    }

    void GAWrapperCpp::SetBuild(std::string const& build) {
        GameAnalytics::configureBuild(build);
    }

    void GAWrapperCpp::SetAutoDetectAppVersion(bool flag) {
        (void)flag;
        return;
    }

    void GAWrapperCpp::SetCustomUserId(std::string const& userId) {
        GameAnalytics::configureUserId(userId);
    }

    void GAWrapperCpp::SetSDKVersion(std::string const& gameEngineSdkVersion) {
        GameAnalytics::configureSdkGameEngineVersion(gameEngineSdkVersion);
    }

    void GAWrapperCpp::SetGameEngineVersion(std::string const& gameEngineVersion) {
        GameAnalytics::configureGameEngineVersion(gameEngineVersion);
    }

    void GAWrapperCpp::Initialize(std::string const& gameKey, std::string const& gameSecret) {
        GameAnalytics::initialize(gameKey, gameSecret);
    }

    void GAWrapperCpp::AddBusinessEvent(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& fields, bool mergeFields) {
        (void)receipt;
        GameAnalytics::addBusinessEvent(currency, amount, itemType, itemId, cartType, fields, mergeFields);
    }

    void GAWrapperCpp::AddBusinessEventWithReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& store, std::string const& signature, std::string const& fields, bool mergeFields) {
        (void)receipt;
        (void)store;
        (void)signature;
        GameAnalytics::addBusinessEvent(currency, amount, itemType, itemId, cartType, fields, mergeFields);
    }

    void GAWrapperCpp::AddBusinessEventAndAutoFetchReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& fields, bool mergeFields) {
        GameAnalytics::addBusinessEvent(currency, amount, itemType, itemId, cartType, fields, mergeFields);
    }

    void GAWrapperCpp::AddResourceEvent(::EGAResourceFlowType flowType, std::string const& currency, float amount, std::string const& itemType, std::string const& itemId, std::string const& fields, bool mergeFields) {
        GameAnalytics::addResourceEvent((gameanalytics::EGAResourceFlowType)flowType, currency, amount, itemType, itemId, fields, mergeFields);
    }

    void GAWrapperCpp::AddProgressionEvent(::EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, std::string const& fields, bool mergeFields) {
        GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)progressionStatus, progression01, progression02, progression03, fields, mergeFields);
    }

    void GAWrapperCpp::AddProgressionEventWithScore(::EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, int score, std::string const& fields, bool mergeFields) {
        GameAnalytics::addProgressionEvent((gameanalytics::EGAProgressionStatus)progressionStatus, score, progression01, progression02, progression03, fields, mergeFields);
    }

    void GAWrapperCpp::AddDesignEvent(std::string const& eventId, std::string const& fields, bool mergeFields) {
        GameAnalytics::addDesignEvent(eventId, fields, mergeFields);
    }

    void GAWrapperCpp::AddDesignEventWithValue(std::string const& eventId, float value, std::string const& fields, bool mergeFields) {
        GameAnalytics::addDesignEvent(eventId, value, fields, mergeFields);
    }

    void GAWrapperCpp::AddErrorEvent(::EGAErrorSeverity severity, std::string const& message, std::string const& fields, bool mergeFields){
        GameAnalytics::addErrorEvent(static_cast<EGAErrorSeverity>(severity), message, fields, mergeFields);
    }

    void GAWrapperCpp::AddAdEvent(::EGAAdAction action, ::EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, std::string const& fields, bool mergeFields) {
        return; // ad events are not supported on desktop
    }

    void GAWrapperCpp::AddAdEventWithDuration(::EGAAdAction action, ::EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, int64_t duration, std::string const& fields, bool mergeFields) {
        return; // ad events are not supported on desktop
    }

    void GAWrapperCpp::AddAdEventWithReason(::EGAAdAction adAction, ::EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, ::EGAAdError noAdReason, std::string const& fields, bool mergeFields) {
        return; // ad events are not supported on desktop
    }

    void GAWrapperCpp::SetInfoLog(bool flag) {
        GameAnalytics::setEnabledInfoLog(flag);
    }

    void GAWrapperCpp::SetVerboseLog(bool flag) {
        GameAnalytics::setEnabledVerboseLog(flag);
    }

    void GAWrapperCpp::SetEnabledManualSessionHandling(bool flag) {
        GameAnalytics::setEnabledManualSessionHandling(flag);
    }

    void GAWrapperCpp::SetEnabledErrorReporting(bool flag) {
        GameAnalytics::setEnabledErrorReporting(flag);
    }

    void GAWrapperCpp::SetEnabledEventSubmission(bool flag, bool doCache) {
        (void)doCache;
        GameAnalytics::setEnabledErrorReporting(flag);
    }

    void GAWrapperCpp::SetCustomDimension01(std::string const& customDimension) {
        GameAnalytics::setCustomDimension01(customDimension);
    }

    void GAWrapperCpp::SetCustomDimension02(std::string const& customDimension) {
        GameAnalytics::setCustomDimension02(customDimension);
    }

    void GAWrapperCpp::SetCustomDimension03(std::string const& customDimension) {
        GameAnalytics::setCustomDimension03(customDimension);
    }

    void GAWrapperCpp::StartSession() {
        GameAnalytics::startSession();
    }

    void GAWrapperCpp::EndSession() {
        GameAnalytics::endSession();
    }

    std::string GAWrapperCpp::GetRemoteConfigsValueAsString(std::string const& key, std::string const& defaultValue) {
        return GameAnalytics::getRemoteConfigsValueAsString(key, defaultValue);
    }

    double GAWrapperCpp::GetRemoteConfigsValueAsNumber(std::string const& key, double defaultValue) {
        return defaultValue; //return GameAnalytics::getRemoteConfigsValueAsNumber(key, defaultValue);
    }

    std::string GAWrapperCpp::GetRemoteConfigsValueAsJson(std::string const& key) {
        return ""; //return GameAnalytics::getRemoteConfigsValueAsJson(key);
    }

    bool GAWrapperCpp::IsRemoteConfigsReady() {
        return GameAnalytics::isRemoteConfigsReady();
    }

    std::string GAWrapperCpp::GetRemoteConfigsContentAsString() {
        return GameAnalytics::getRemoteConfigsContentAsString();
    }

    std::string GAWrapperCpp::GetABTestingId() {
        return GameAnalytics::getABTestingId();
    }

    std::string GAWrapperCpp::GetABTestingVariantId() {
        return GameAnalytics::getABTestingVariantId();
    }

    void GAWrapperCpp::EnableAdvertisingId(bool value) {
        (void)value; // for desktop advertising ids are not collected
    }

    void GAWrapperCpp::EnableSDKInitEvent(bool value) {
        GameAnalytics::enableSDKInitEvent(value);
    }

    void GAWrapperCpp::EnableFpsHistogram(FPSTracker tracker, bool value) {
        GameAnalytics::enableFPSHistogram(tracker, value);
    }

    void GAWrapperCpp::EnableMemoryHistogram(bool value) {
        GameAnalytics::enableMemoryHistogram(value);
    }

    void GAWrapperCpp::EnableHealthHardwareInfo(bool value) {
        GameAnalytics::enableHardwareTracking(value);
    }

    void GAWrapperCpp::OnQuit() {
        GameAnalytics::onQuit();
    }

    void GAWrapperCpp::SetWritablePath(std::string const& path) {
        GameAnalytics::configureWritablePath(path);
    }

    std::string GAWrapperCpp::GetExternalUserId() {
        return GameAnalytics::getExternalUserId();
    }

    void GAWrapperCpp::SetExternalUserId(const std::string &extUserId) {
        return GameAnalytics::configureExternalUserId(extUserId);
    }

    std::string GAWrapperCpp::GetUserId() {
        return GameAnalytics::getUserId();
    }

    void GAWrapperCpp::UseRandomizedId(bool value) {
        (void)value; // the cpp SDK will always use a randomized id
    }

    void GAWrapperCpp::SetGlobalCustomEventFields(const std::string &customFields) {
        GameAnalytics::setGlobalCustomEventFields(customFields);
    }
}
