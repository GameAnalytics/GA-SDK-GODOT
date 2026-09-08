#include "GAWrapperWeb.h"

#include "godot_cpp/variant/callable_method_pointer.hpp"

#include <vector>
#include <string>

#include <iostream>

extern std::string ToStdString(godot::String const& s);

namespace gameanalytics
{
    using namespace godot;

    inline godot::String BoolToStr(bool v)
    {
        return v ? "true" : "false";
    }

    inline godot::String ToGodotString(std::string const& s)
    {
        return godot::String::utf8(s.c_str(), s.size());
    }

    // an empty fields string would leave a hole in the argument list of the
    // eval'd call, so it has to become a real object literal first
    inline godot::String JsFields(std::string const& fields)
    {
        return fields.empty() ? godot::String("{}") : ToGodotString(fields);
    }

    godot::String MakeJSArray(const std::vector<std::string>& list)
    {
        godot::String arrayString = "[";

        if (list.size() > 0)
        {
            const size_t last = list.size() - 1;
            for (int i = 0; i < list.size(); ++i)
            {
                godot::String entry = ToGodotString(list[i]);
                arrayString += '\"' + entry + '\"';

                if(i < last)
                {
                    arrayString += ",";
                }
            }
        }
        
        arrayString += "]";
        return arrayString;
    }

    static RemoteConfigsListener webRemoteConfigsListener;

    // callbacks made with JavaScriptBridge.create_callback receive a single array holding the
    // arguments the javascript side passed
    static void OnRemoteConfigsUpdatedFromJS(godot::Array args)
    {
        if(webRemoteConfigsListener)
        {
            godot::String configs = args.size() > 0 ? godot::String(args[0]) : godot::String("{}");
            webRemoteConfigsListener(ToStdString(configs));
        }
    }

    bool GAWrapperWeb::InitJavascript()
    {
        if(!_jsBridge)
        {
            _jsBridge = godot::Engine::get_singleton()->get_singleton("JavaScriptBridge");
        }
        
        return _jsBridge;
    }

    godot::Variant GAWrapperWeb::Eval(godot::String const& code)
    {
        if(!_jsBridge)
        {
            InitJavascript();
        }

        if(_jsBridge)
        {
            return _jsBridge->call("eval", code, true);
        }

        return {};
    }

    GAWrapperWeb::GAWrapperWeb()
    {
    }

    void GAWrapperWeb::SetAvailableCustomDimensions01(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        Eval(vformat("gameanalytics.GameAnalytics.configureAvailableCustomDimensions01(%s)", arrayString));
    }

    void GAWrapperWeb::SetAvailableCustomDimensions02(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        Eval(vformat("gameanalytics.GameAnalytics.configureAvailableCustomDimensions02(%s)", arrayString));
    }

    void GAWrapperWeb::SetAvailableCustomDimensions03(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        Eval(vformat("gameanalytics.GameAnalytics.configureAvailableCustomDimensions03(%s)", arrayString));
    }

    void GAWrapperWeb::SetAvailableResourceCurrencies(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        Eval(vformat("gameanalytics.GameAnalytics.configureAvailableResourceCurrencies(%s)", arrayString));
    }

    void GAWrapperWeb::SetAvailableResourceItemTypes(const std::vector<std::string>& list) 
    {
        String arrayString = MakeJSArray(list);
        Eval(vformat("gameanalytics.GameAnalytics.configureAvailableResourceItemTypes(%s)", arrayString));
    }

    void GAWrapperWeb::SetBuild(std::string const& build) {
        Eval(vformat("gameanalytics.GameAnalytics.configureBuild('%s')", ToGodotString(build)));
    }

    void GAWrapperWeb::SetAutoDetectAppVersion(bool flag) {
        (void)flag;
    }

    void GAWrapperWeb::SetCustomUserId(std::string const& userId) {
        Eval(vformat("gameanalytics.GameAnalytics.configureUserId('%s')", ToGodotString(userId)));
    }

    void GAWrapperWeb::SetSDKVersion(std::string const& gameEngineSdkVersion) {
        Eval(vformat("gameanalytics.GameAnalytics.configureSdkGameEngineVersion('%s')", ToGodotString(gameEngineSdkVersion)));
    }

    void GAWrapperWeb::SetGameEngineVersion(std::string const& gameEngineVersion) {
       Eval(vformat("gameanalytics.GameAnalytics.configureGameEngineVersion('%s')", ToGodotString(gameEngineVersion)));
    }

    void GAWrapperWeb::Initialize(std::string const& gameKey, std::string const& gameSecret) {
        Eval(vformat("gameanalytics.GameAnalytics.initialize('%s', '%s')", ToGodotString(gameKey), ToGodotString(gameSecret)));
    }

    void GAWrapperWeb::AddBusinessEvent(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& fields, bool mergeFields) 
    {
        (void)receipt;
        Eval(vformat("gameanalytics.GameAnalytics.addBusinessEvent('%s', %d, '%s', '%s', '%s', %s, %s)", ToGodotString(currency), amount, ToGodotString(itemType), ToGodotString(itemId), ToGodotString(cartType), JsFields(fields), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddBusinessEventWithReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& store, std::string const& signature, std::string const& fields, bool mergeFields) 
    {
        (void)store;
        (void)signature;
        return AddBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, fields, mergeFields);
    }

    void GAWrapperWeb::AddBusinessEventAndAutoFetchReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& fields, bool mergeFields) {
        return AddBusinessEvent(currency, amount, itemType, itemId, cartType, "", fields, mergeFields);
    }

    void GAWrapperWeb::AddResourceEvent(::EGAResourceFlowType flowType, std::string const& currency, float amount, std::string const& itemType, std::string const& itemId, std::string const& fields, bool mergeFields) 
    {    
        Eval(vformat("gameanalytics.GameAnalytics.addResourceEvent(%d, '%s', %f, '%s', '%s', %s, %s)", (int)flowType, ToGodotString(currency), amount, ToGodotString(itemType), ToGodotString(itemId), JsFields(fields), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddProgressionEvent(::EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, std::string const& fields, bool mergeFields) {
        // `undefined` in the score slot is what makes the JS SDK set sendScore = false
        Eval(vformat("gameanalytics.GameAnalytics.addProgressionEvent(%d, '%s', '%s', '%s', undefined, %s, %s)", (int)progressionStatus, ToGodotString(progression01), ToGodotString(progression02), ToGodotString(progression03), JsFields(fields), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddProgressionEventWithScore(::EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, int score, std::string const& fields, bool mergeFields) {
        Eval(vformat("gameanalytics.GameAnalytics.addProgressionEvent(%d, '%s', '%s', '%s', %d, %s, %s)", (int)progressionStatus, ToGodotString(progression01), ToGodotString(progression02), ToGodotString(progression03), score, JsFields(fields), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddDesignEvent(std::string const& eventId, std::string const& fields, bool mergeFields) {
        // `undefined` in the value slot is what makes the JS SDK set sendValue = false
        Eval(vformat("gameanalytics.GameAnalytics.addDesignEvent('%s', undefined, %s, %s)", ToGodotString(eventId), JsFields(fields), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddDesignEventWithValue(std::string const& eventId, float value, std::string const& fields, bool mergeFields) {
        Eval(vformat("gameanalytics.GameAnalytics.addDesignEvent('%s', %f, %s, %s)", ToGodotString(eventId), value, JsFields(fields), BoolToStr(mergeFields)));
    }

    void GAWrapperWeb::AddErrorEvent(::EGAErrorSeverity severity, std::string const& message, std::string const& fields, bool mergeFields) {
        Eval(vformat("gameanalytics.GameAnalytics.addErrorEvent(%d, '%s', %s, %s)", (int)severity, ToGodotString(message), JsFields(fields), BoolToStr(mergeFields)));
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
        Eval(vformat("gameanalytics.GameAnalytics.setEnabledInfoLog(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::SetVerboseLog(bool flag) {
        Eval(vformat("gameanalytics.GameAnalytics.setEnabledVerboseLog(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::SetEnabledManualSessionHandling(bool flag) {
        Eval(vformat("gameanalytics.GameAnalytics.setEnabledManualSessionHandling(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::SetEnabledErrorReporting(bool flag) {
    }

    void GAWrapperWeb::SetEnabledEventSubmission(bool flag, bool doCache) {
    }

    void GAWrapperWeb::SetCustomDimension01(std::string const& customDimension) {
        Eval(vformat("gameanalytics.GameAnalytics.setCustomDimension01('%s')", ToGodotString(customDimension)));
    }

    void GAWrapperWeb::SetCustomDimension02(std::string const& customDimension) {
        Eval(vformat("gameanalytics.GameAnalytics.setCustomDimension02('%s')", ToGodotString(customDimension)));
    }

    void GAWrapperWeb::SetCustomDimension03(std::string const& customDimension) {
        Eval(vformat("gameanalytics.GameAnalytics.setCustomDimension03('%s')", ToGodotString(customDimension)));
    }

    void GAWrapperWeb::StartSession() {
        Eval("gameanalytics.GameAnalytics.startSession()");
    }

    void GAWrapperWeb::EndSession() {
        Eval("gameanalytics.GameAnalytics.endSession()");
    }

    std::string GAWrapperWeb::GetRemoteConfigsValueAsString(std::string const& key, std::string const& defaultValue) {
        godot::String s = Eval(vformat("gameanalytics.GameAnalytics.getRemoteConfigsValueAsString('%s', '%s')", ToGodotString(key), ToGodotString(defaultValue)));
        return ToStdString(s);
    }

    double GAWrapperWeb::GetRemoteConfigsValueAsNumber(std::string const& key, double defaultValue) {
        return defaultValue;
    }

    std::string GAWrapperWeb::GetRemoteConfigsValueAsJson(std::string const& key) {
        // will be parsed to json by the GA <> Godot interface
        godot::String s = Eval(vformat("gameanalytics.GameAnalytics.getRemoteConfigsValueAsString('%s', '')", ToGodotString(key)));
        return ToStdString(s);
    }

    bool GAWrapperWeb::IsRemoteConfigsReady() {
        return Eval("gameanalytics.GameAnalytics.isRemoteConfigsReady()");
    }

    std::string GAWrapperWeb::GetRemoteConfigsContentAsString() {
        godot::String s = Eval("gameanalytics.GameAnalytics.getRemoteConfigsContentAsString()");
        return ToStdString(s);
    }

    std::string GAWrapperWeb::GetABTestingId() {
        godot::String s = Eval("gameanalytics.GameAnalytics.getABTestingId()");
        return ToStdString(s);
    }

    std::string GAWrapperWeb::GetABTestingVariantId() {
        godot::String s = Eval("gameanalytics.GameAnalytics.getABTestingVariantId()");
        return ToStdString(s);
    }

    void GAWrapperWeb::RegisterRemoteConfigsListener(RemoteConfigsListener listener) {
        if(!InitJavascript())
        {
            return;
        }

        webRemoteConfigsListener = std::move(listener);

        _remoteConfigsJsCallback = _jsBridge->call("create_callback", callable_mp_static(&OnRemoteConfigsUpdatedFromJS));

        godot::Variant window = _jsBridge->call("get_interface", "window");
        if(godot::Object* windowObj = window)
        {
            windowObj->set("godotGameAnalyticsOnRemoteConfigs", _remoteConfigsJsCallback);
        }

        Eval("gameanalytics.GameAnalytics.addRemoteConfigsListener({onRemoteConfigsUpdated: function() {"
             "  window.godotGameAnalyticsOnRemoteConfigs(gameanalytics.GameAnalytics.getRemoteConfigsContentAsString());"
             "}})");
    }

    void GAWrapperWeb::EnableAdvertisingId(bool value) {
        (void)value; // for desktop advertising ids are not collected
    }

    void GAWrapperWeb::EnableSDKInitEvent(bool flag) {
        Eval(vformat("gameanalytics.GameAnalytics.enableHealthEvent(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::EnableFpsHistogram(FPSTracker tracker, bool flag) {
        (void)tracker; // javascript SDK uses its own tracker
        Eval(vformat("gameanalytics.GameAnalytics.enableHealthEvent(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::EnableMemoryHistogram(bool flag) {
        Eval(vformat("gameanalytics.GameAnalytics.enableHealthEvent(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::EnableHealthHardwareInfo(bool flag) {
        Eval(vformat("gameanalytics.GameAnalytics.enableHealthEvent(%s)", BoolToStr(flag)));
    }

    void GAWrapperWeb::OnQuit() {
    }

    void GAWrapperWeb::SetWritablePath(std::string const& path) {
    }

    std::string GAWrapperWeb::GetExternalUserId() {
        godot::String s = Eval("gameanalytics.GameAnalytics.getExtUserId()");
        return ToStdString(s);
    }

    void GAWrapperWeb::SetExternalUserId(const std::string &extUserId) {
        Eval(vformat("gameanalytics.GameAnalytics.setExtUserId('%s')", ToGodotString(extUserId)));
    }

    std::string GAWrapperWeb::GetUserId() {
        godot::String s = Eval("gameanalytics.GameAnalytics.getUserId()");
        return ToStdString(s);
    }

    void GAWrapperWeb::UseRandomizedId(bool value) {
        (void)value; // the cpp SDK will always use a randomized id
    }

    void GAWrapperWeb::SetGlobalCustomEventFields(const std::string &customFields) {
        Eval(vformat("gameanalytics.GameAnalytics.setGlobalCustomEventFields(JSON.parse('%s'))", !customFields.empty() ? ToGodotString(customFields) : "{}"));
    }

    int64_t GAWrapperWeb::GetElapsedSessionTime() {
        return 0;
    }

    int64_t GAWrapperWeb::GetElapsedTimeForPreviousSession() {
        return 0;
    }
        
    int64_t GAWrapperWeb::GetElapsedTimeFromAllSessions() {
        return 0;
    }
}
