#include "GAWrapperWeb.h"
#include "GameAnalytics/GameAnalytics.h"

#include "api/javascript_singleton.h"

namespace gameanalytics
{
    inline constexpr const char* BoolToStr(bool v)
    {
        return v ? "true" : "false";
    }

    String MakeJSArray(const std::vector<std::string>& list)
    {
        String arrayString = "";
        if (customDimensions.size() > 0)
        {
            arrayString += "[\"";
            for (int i = 0; i < customDimensions.size(); ++i)
            {
                String entry = customDimensions[i].c_str();
                if (i > 0)
                {
                    arrayString += "\",\"";
                }
                arrayString += entry;
            }
            arrayString += "\"]";
        }
        else
        {
            arrayString = "[]";
        }

        return arrayString;
    }

    void GAWrapperWeb::SetAvailableCustomDimensions01(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableCustomDimensions01(JSON.parse('" + arrayString + "'))");
    }

    void GAWrapperWeb::SetAvailableCustomDimensions02(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableCustomDimensions02(JSON.parse('" + arrayString + "'))");
    }

    void GAWrapperWeb::SetAvailableCustomDimensions03(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableCustomDimensions03(JSON.parse('" + arrayString + "'))");
    }

    void GAWrapperWeb::SetAvailableResourceCurrencies(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableResourceCurrencies(JSON.parse('" + arrayString + "'))");
    }

    void GAWrapperWeb::SetAvailableResourceItemTypes(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableResourceItemTypes(JSON.parse('" + arrayString + "'))");
    }

    void GAWrapperWeb::SetBuild(std::string const& build) {
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureBuild('" + build.c_str() + "')");
    }

    void GAWrapperWeb::SetAutoDetectAppVersion(bool flag) {
        (void)flag;
    }

    void GAWrapperWeb::SetCustomUserId(std::string const& userId) {
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureBuild('" + userId.c_str() + "')");
    }

    void GAWrapperWeb::SetSDKVersion(std::string const& gameEngineSdkVersion) {
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureSdkGameEngineVersion('" + version + "')");
    }

    void GAWrapperWeb::SetGameEngineVersion(std::string const& gameEngineVersion) {
       JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureGameEngineVersion('" + version + "')");
    }

    void GAWrapperWeb::Initialize(std::string const& gameKey, std::string const& gameSecret) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.initialize('%s', '%s')", gameKey.c_str(), secretKey.c_str()));
    }

    void GAWrapperWeb::AddBusinessEvent(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& fields, bool mergeFields) 
    {
        (void)receipt;
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addBusinessEvent('%s', %d, '%s', '%s', %s, '%s', '%s', %s)", currency.c_str(), amount, itemType.c_str(), itemId.c_str(), cartType.c_str(), fields.c_str(), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddBusinessEventWithReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& store, std::string const& signature, std::string const& fields, bool mergeFields) 
    {
        (void)store;
        (void)signature;
        return AddBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, fields, mergeFields);
    }

    void GAWrapperWeb::AddBusinessEventAndAutoFetchReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& fields, bool mergeFields) {
        return AddBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, fields, mergeFields);
    }

    void GAWrapperWeb::AddResourceEvent(::EGAResourceFlowType flowType, std::string const& currency, float amount, std::string const& itemType, std::string const& itemId, std::string const& fields, bool mergeFields) 
    {    
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addResourceEvent(%d, '%s', %f, '%s', %s)", (int)flowType, currency.c_str(), amount, itemType.c_str(), lastPart));
    }

    void GAWrapperWeb::AddProgressionEvent(::EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, std::string const& fields, bool mergeFields) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addProgressionEvent(%d, '%s', '%s', '%s', %s, %d, \'%s\', %s)", (int)progressionStatus, progression01.c_str(), progression02.c_str(), progression03.c_str(), value, fields.c_str(), mergeFields));
    }

    void GAWrapperWeb::AddProgressionEventWithScore(::EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, int score, std::string const& fields, bool mergeFields) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addProgressionEvent(%d, '%s', '%s', '%s', %s, \'%s\', %s)", (int)progressionStatus, progression01.c_str(), progression02.c_str(), progression03.c_str(), fields.c_str(), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddDesignEvent(std::string const& eventId, std::string const& fields, bool mergeFields) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addDesignEvent('%s', '%s', %s)", eventId.c_str(), fields.c_str(), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddDesignEventWithValue(std::string const& eventId, float value, std::string const& fields, bool mergeFields) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addDesignEvent('%s', %f, '%s', %s)", eventId.c_str(), value, fields.c_str(), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddErrorEvent(::EGAErrorSeverity severity, std::string const& message, std::string const& fields, bool mergeFields) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addErrorEvent(%d, '%s', '%s', %s", (int)severity, message.c_str(), fields.c_str(), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddAdEvent(::EGAAdAction action, ::EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, std::string const& fields, bool mergeFields) {
        return; // ad events are not supported
    }

    void GAWrapperWeb::AddAdEventWithDuration(::EGAAdAction action, ::EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, int64_t duration, std::string const& fields, bool mergeFields) {
        return; // ad events are not supported
    }

    void GAWrapperWeb::AddAdEventWithReason(::EGAAdAction adAction, ::EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, ::EGAAdError noAdReason, std::string const& fields, bool mergeFields) {
        return; // ad events are not supported
    }

    void GAWrapperWeb::SetInfoLog(bool flag) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setEnabledInfoLog(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::SetVerboseLog(bool flag) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setEnabledVerboseLog(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::SetEnabledManualSessionHandling(bool flag) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setEnabledManualSessionHandling(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::SetEnabledErrorReporting(bool flag) {
        GameAnalytics::setEnabledErrorReporting(flag);
    }

    void GAWrapperWeb::SetEnabledEventSubmission(bool flag, bool doCache) {
        (void)doCache;
        GameAnalytics::setEnabledErrorReporting(flag);
    }

    void GAWrapperWeb::SetCustomDimension01(std::string const& customDimension) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setCustomDimension01('%s')", customDimension.c_str()));
    }

    void GAWrapperWeb::SetCustomDimension02(std::string const& customDimension) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setCustomDimension02('%s')", customDimension.c_str()));
    }

    void GAWrapperWeb::SetCustomDimension03(std::string const& customDimension) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setCustomDimension03('%s')", customDimension.c_str()));
    }

    void GAWrapperWeb::StartSession() {
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.startSession()");
    }

    void GAWrapperWeb::EndSession() {
        JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.endSession()");
    }

    std::string GAWrapperWeb::GetRemoteConfigsValueAsString(std::string const& key, std::string const& defaultValue) {
        return JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.getRemoteConfigsValueAsString('%s', '%s')", key.c_str(), defaultValue.c_str()));
    }

    double GAWrapperWeb::GetRemoteConfigsValueAsNumber(std::string const& key, double defaultValue) {
        return defaultValue;
    }

    std::string GAWrapperWeb::GetRemoteConfigsValueAsJson(std::string const& key) {
        return ""; //return GameAnalytics::getRemoteConfigsValueAsJson(key);
    }

    bool GAWrapperWeb::IsRemoteConfigsReady() {
        return JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.isRemoteConfigsReady()");
    }

    std::string GAWrapperWeb::GetRemoteConfigsContentAsString() {
        return JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.getRemoteConfigsContentAsString()");
    }

    std::string GAWrapperWeb::GetABTestingId() {
        return GameAnalytics::getABTestingId();
    }

    std::string GAWrapperWeb::GetABTestingVariantId() {
        return GameAnalytics::getABTestingVariantId();
    }

    void GAWrapperWeb::EnableAdvertisingId(bool value) {
        (void)value; // for desktop advertising ids are not collected
    }

    void GAWrapperWeb::EnableSDKInitEvent(bool value) {
        (void)value;
    }

    void GAWrapperWeb::EnableFpsHistogram(FPSTracker tracker, bool value) {
        (void)tracker;
        (void)value;
    }

    void GAWrapperWeb::EnableMemoryHistogram(bool value) {
        (void)value;
    }

    void GAWrapperWeb::EnableHealthHardwareInfo(bool value) {
        (void)value;
    }

    void GAWrapperWeb::OnQuit() {
    }

    void GAWrapperWeb::SetWritablePath(std::string const& path) {
        GameAnalytics::configureWritablePath(path);
    }

    std::string GAWrapperWeb::GetExternalUserId() {
        return GameAnalytics::getExternalUserId();
    }

    void GAWrapperWeb::SetExternalUserId(const std::string &extUserId) {
        return GameAnalytics::configureExternalUserId(extUserId);
    }

    std::string GAWrapperWeb::GetUserId() {
        return GameAnalytics::getUserId();
    }

    void GAWrapperWeb::UseRandomizedId(bool value) {
        (void)value; // the cpp SDK will always use a randomized id
    }

    void GAWrapperWeb::SetGlobalCustomEventFields(const std::string &customFields) {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setGlobalCustomEventFields(JSON.parse('%s'))", !customFields.empty() ? customFields.c_str() : "{}"));
    }
}
