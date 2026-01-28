#include "GameAnalytics.h"
#include <godot_cpp/classes/engine.hpp>

#if __EMSCRIPTEN__
    #define WEB_PLATFORM
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
        #define IOS_PLATFORM
    #else
        #define DESKTOP_PLATFORM
    #endif
#elif defined(__ANDROID__)
    #define ANDROID_PLATFORM
#elif defined(_WIN32) || defined(WIN32)
    #define DESKTOP_PLATFORM
#elif defined(__linux__) || defined(__unix__) || defined(__unix) || defined(unix)
    #define DESKTOP_PLATFORM
#endif

#define GA_VERSION "godot 3.0.0"

#ifdef IOS_PLATFORM
    #include "GAWrapperIOS.h"
    using GAWrapperImpl = gameanalytics::GAWrapperIOS;
#elif defined(ANDROID_PLATFORM)
    #include "GAWrapperAndroid.h"
    using GAWrapperImpl = gameanalytics::GAWrapperAndroid;
#elif defined(DESKTOP_PLATFORM)
    #include "GAWrapperCpp.h"
    using GAWrapperImpl = gameanalytics::GAWrapperCpp;
#elif defined(WEB_PLATFORM)
    #include "GAWebWrapper.h"
    using GAWrapperImpl = gameanalytics::GAWrapperWeb;
#else
    #error unsupported platform
#endif

inline std::string ToStdString(godot::String const& s)
{
    return std::string(s.utf8().get_data(), s.length());
}

std::vector<std::string> ToStringVector(const godot::PackedStringArray &arr)
{
    std::vector<std::string> v;
    v.reserve(arr.size());

    for(const godot::String& s : arr)
    {
        v.push_back(ToStdString(s));
    }

    return v;
}

template<typename T>
T GetOptionalValue(godot::Dictionary const& d, godot::String const& key, T const& defValue)
{
    if(d.has(key))
    {
        godot::Variant v = d.get(key, defValue);
        return static_cast<T>(v);
    }

    return defValue;
}

GameAnalytics::GameAnalytics()
{
    godot::print_line("Initializing GameAnalytics");
    _impl = std::make_unique<GAWrapperImpl>();
}

GameAnalytics::~GameAnalytics()
{
    if(_impl && _wasInitialized)
    {
        _impl->OnQuit();
    }
}

void GameAnalytics::configureAvailableCustomDimensions01(const PackedStringArray &customDimensions)
{
    if(_impl)
    {
        return _impl->SetAvailableCustomDimensions01(ToStringVector(customDimensions));
    }
}

void GameAnalytics::configureAvailableCustomDimensions02(const PackedStringArray &customDimensions)
{
    if(_impl)
    {
        return _impl->SetAvailableCustomDimensions02(ToStringVector(customDimensions));
    }
}

void GameAnalytics::configureAvailableCustomDimensions03(const PackedStringArray &customDimensions)
{
    if(_impl)
    {
        return _impl->SetAvailableCustomDimensions03(ToStringVector(customDimensions));
    }
}

void GameAnalytics::configureAvailableResourceCurrencies(const PackedStringArray &resourceCurrencies)
{
    if(_impl)
    {
        return _impl->SetAvailableResourceCurrencies(ToStringVector(resourceCurrencies));
    }
}

void GameAnalytics::configureAvailableResourceItemTypes(const PackedStringArray &types)
{
    if(_impl)
    {
        return _impl->SetAvailableResourceCurrencies(ToStringVector(types));
    }
}

void GameAnalytics::configureBuild(const String &build)
{
    if(_impl)
    {
        return _impl->SetBuild(ToStdString(build));
    }
}

void GameAnalytics::configureAutoDetectAppVersion(bool flag)
{
    if(_impl)
    {
        return _impl->SetAutoDetectAppVersion(flag);
    }
}

void GameAnalytics::configureUserId(const String &userId)
{
    if(_impl)
    {
        return _impl->SetCustomUserId(ToStdString(userId));
    }
}

void GameAnalytics::configureSdkGameEngineVersion(const String &version)
{
    if(_impl)
    {
        return _impl->SetSDKVersion(ToStdString(version));
    }
}

void GameAnalytics::configureGameEngineVersion(const String &version)
{
    if(_impl)
    {
        return _impl->SetGameEngineVersion(ToStdString(version));
    }
}

void GameAnalytics::init(const String &gameKey, const String &secretKey)
{
    Dictionary versionInfo = godot::Engine::get_singleton()->get_version_info();
    String major = versionInfo.get("major", "1");
    String minor = versionInfo.get("minor", "0");
    String patch = versionInfo.get("patch", "0");
    String engineVersion = "godot " + major + "." + minor + "." + patch;

    if(_impl)
    {
        configureGameEngineVersion(engineVersion);
        configureSdkGameEngineVersion(GA_VERSION);
        
        _impl->Initialize(ToStdString(gameKey), ToStdString(secretKey));
        _wasInitialized = true;
    }
}

void GameAnalytics::addBusinessEvent(const String& currency, 
                          int amount, 
                          const String& itemType, 
                          const String& itemId, 
                          const String& cartType,
                          const Dictionary &options)
{
    String receipt = GetOptionalValue<String>(options, "receipt", "");
    bool autoFetchReceipt = GetOptionalValue<bool>(options, "autoFetchReceipt", false);
    String fields = GetOptionalValue<String>(options, "fields", "{}");;
    bool mergeFields = GetOptionalValue<bool>(options, "mergeFields", false);

    if(_impl)
    {
        if(autoFetchReceipt)
        {
            _impl->AddBusinessEventAndAutoFetchReceipt(currency.utf8().get_data(), amount, itemType.utf8().get_data(), itemId.utf8().get_data(), cartType.utf8().get_data(), fields.utf8().get_data(), mergeFields);
        }
        else
        {
            _impl->AddBusinessEvent(currency.utf8().get_data(), amount, itemType.utf8().get_data(), itemId.utf8().get_data(), cartType.utf8().get_data(), receipt.utf8().get_data(), fields.utf8().get_data(), mergeFields);
        }
    }
}

void GameAnalytics::addResourceEvent(const String& flow, 
                          const String& currency, 
                          float amount, 
                          const String& itemType, 
                          const String& itemId, 
                          const Dictionary &options)
{
    EGAResourceFlowType flowType = flow.to_lower() == "sink" ? EGAResourceFlowType::sink : EGAResourceFlowType::source;
    String fields = GetOptionalValue<String>(options, "fields", "{}");;
    bool mergeFields = GetOptionalValue<bool>(options, "mergeFields", false);

    if(_impl)
    {
        _impl->AddResourceEvent(flowType, ToStdString(currency), amount, ToStdString(itemType), ToStdString(itemId), ToStdString(fields), mergeFields);
    }
}

void GameAnalytics::addProgressionEventWithScore(const String& status,
                             const String& progression1,
                             const String& progression2,
                             const String& progression3,
                             int score)
{
    Dictionary opts;
    opts.set("score", score);
    
    return addProgressionEvent(status, progression1, progression2, progression3, opts);
}

void GameAnalytics::addProgressionEvent(const String& status,
                             const String& progression1,
                             const String& progression2,
                             const String& progression3,
                             const Dictionary &options)
{
    EGAProgressionStatus progressionStatus = EGAProgressionStatus::undefined;

    String strStatus = status.to_lower();

    if(strStatus == "start")
        progressionStatus = EGAProgressionStatus::start;

    else if(strStatus == "fail")
        progressionStatus = EGAProgressionStatus::fail;

    else if(strStatus == "complete")
        progressionStatus = EGAProgressionStatus::complete;

    else
    {
        godot::print_error("GameAnalytics: Invalid status string for progression event (allowed values: start, fail, complete)");
        return;
    }

    int score = GetOptionalValue<int>(options, "score", 0);
    bool sendScore = options.has("score");
    String fields = GetOptionalValue<String>(options, "fields", "");
    bool mergeFields = false;

    if(_impl)
    {
        if(sendScore)
        {
            _impl->AddProgressionEventWithScore(progressionStatus, ToStdString(progression1), ToStdString(progression2), ToStdString(progression3), score, ToStdString(fields), mergeFields);
        }
        else
        {
            _impl->AddProgressionEvent(progressionStatus, ToStdString(progression1), ToStdString(progression2), ToStdString(progression3), ToStdString(fields), mergeFields);
        }
    }
}

void GameAnalytics::addDesignEventWithValue(const String& eventId, float value)
{
    if(_impl)
    {
        _impl->AddDesignEventWithValue(ToStdString(eventId), value, "", false);
    }
}

void GameAnalytics::addDesignEvent(const String& eventId, const Dictionary &options)
{
    float value = GetOptionalValue<float>(options, "value", 0.0f);
    bool sendValue = options.has("value");
    String fields = GetOptionalValue<String>(options, "fields", "");
    bool mergeFields = GetOptionalValue<bool>(options, "mergeFields", false);

    if(_impl)
    {
        if(sendValue)
        {
            _impl->AddDesignEventWithValue(ToStdString(eventId), value, ToStdString(fields), mergeFields);
        }
        else
        {
            _impl->AddDesignEvent(ToStdString(eventId), ToStdString(fields), mergeFields);
        }
    }
}

void GameAnalytics::addErrorEvent(const String& errSeverity, const String& message, const Dictionary &options)
{
    EGAErrorSeverity severity = EGAErrorSeverity::undefined;

    String severityStr = errSeverity.to_lower();

    if (severityStr == "debug")
        severity = EGAErrorSeverity::debug;

    else if (severityStr == "info")
        severity = EGAErrorSeverity::info;

    else if (severityStr == "warning")
        severity = EGAErrorSeverity::warning;

    else if (severityStr == "error")
        severity = EGAErrorSeverity::error;

    else if (severityStr == "critical")
        severity = EGAErrorSeverity::critical;

    else
    {
        godot::print_error("GameAnalytics: Invalid error severity for an error event (allowed values: debug, info, warning, error, critical)");
        return;
    }

    String fields = GetOptionalValue<String>(options, "fields", "");
    bool mergeFields = GetOptionalValue<bool>(options, "mergeFields", false);

    if(_impl)
    {
        _impl->AddErrorEvent(severity, ToStdString(message), ToStdString(fields), mergeFields);
    }
}

void GameAnalytics::addAdEvent(
    const String& action,
    const String& type,
    const String& adSdkName,
    const String& adPlacement,
    const Dictionary &options)
{
    EGAAdAction adAction = EGAAdAction::undefined;
    EGAAdType adType = EGAAdType::undefined;
    EGAAdError noAdReason = EGAAdError::unknown;

    String noShowReason = GetOptionalValue<String>(options, "reason", "");
    bool sendDuration = options.has("duration");
    int duration = GetOptionalValue<int>(options, "duration", 0);
    String fields = GetOptionalValue<String>(options, "fields", "");;
    bool mergeFields = GetOptionalValue<int>(options, "mergeFields", false);;

    //////////////////////////////  get action enum

    String enumStr = action.to_lower();
    if (enumStr == "clicked")
    {
        adAction = EGAAdAction::clicked;
    }
    else if (enumStr == "show")
    {
        adAction = EGAAdAction::show;
    }
    else if (enumStr == "failed_show")
    {
        adAction = EGAAdAction::failedshow;
    }
    else if (enumStr == "reward_received")
    {
        adAction = EGAAdAction::rewardreceived;
    }

    ////////////////////////////// get type enum

    enumStr = type.to_lower();
    if (enumStr == "video")
    {
        adType = EGAAdType::video;
    }
    else if (enumStr == "rewarded_video")
    {
        adType = EGAAdType::rewardedvideo;
    }
    else if (enumStr == "playable")
    {
        adType = EGAAdType::playable;
    }
    else if (enumStr == "interstitial")
    {
        adType = EGAAdType::interstitial;
    }
    else if (enumStr == "offer_wall")
    {
        adType = EGAAdType::offerwall;
    }
    else if (enumStr == "banner")
    {
        adType = EGAAdType::banner;
    }

    ////////////////////////////// get no show reason enum

    enumStr = noShowReason.to_lower();
    if (enumStr == "unknown")
    {
        noAdReason = EGAAdError::unknown;
    }
    else if (enumStr == "offline")
    {
        noAdReason = EGAAdError::offline;
    }
    else if (enumStr == "no_fill")
    {
        noAdReason = EGAAdError::nofill;
    }
    else if (enumStr == "internal_error")
    {
        noAdReason = EGAAdError::internalerror;
    }
    else if (enumStr == "invalid_request")
    {
        noAdReason = EGAAdError::invalidrequest;
    }
    else if (enumStr == "unable_to_precache")
    {
        noAdReason = EGAAdError::unabletoprecache;
    }

    //////////////////////////////

    if(_impl)
    {
        if(sendDuration)
        {
            _impl->AddAdEventWithDuration(adAction, adType, ToStdString(adSdkName), ToStdString(adPlacement), duration, ToStdString(fields), mergeFields);
        }
        else
        {
            _impl->AddAdEventWithReason(adAction, adType, ToStdString(adSdkName), ToStdString(adPlacement), noAdReason, ToStdString(fields), mergeFields);
        }
    }
}

void GameAnalytics::setEnabledInfoLog(bool flag)
{
    if(_impl)
    {
        return _impl->SetInfoLog(flag);
    }
}

void GameAnalytics::setEnabledVerboseLog(bool flag)
{
    if(_impl)
    {
        return _impl->SetVerboseLog(flag);
    }
}

void GameAnalytics::setEnabledManualSessionHandling(bool flag)
{
    if(_impl)
    {
        return _impl->SetEnabledManualSessionHandling(flag);
    }
}

void GameAnalytics::setEnabledErrorReporting(bool flag)
{
    if(_impl)
    {
        return _impl->SetEnabledErrorReporting(flag);
    }
}

void GameAnalytics::setEnabledEventSubmission(bool flag)
{
    if(_impl)
    {
        return _impl->SetEnabledEventSubmission(flag, true);
    }
}

void GameAnalytics::setCustomDimension01(const String &dimension)
{
    if(_impl)
    {
        _impl->SetCustomDimension01(ToStdString(dimension));
    }
}

void GameAnalytics::setCustomDimension02(const String &dimension)
{
    if(_impl)
    {
        _impl->SetCustomDimension02(ToStdString(dimension));
    }
}

void GameAnalytics::setCustomDimension03(const String &dimension)
{
    if(_impl)
    {
        _impl->SetCustomDimension03(ToStdString(dimension));
    }
}

void GameAnalytics::setGlobalCustomEventFields(const String &customFields)
{
    if(_impl)
    {
        _impl->SetGlobalCustomEventFields(ToStdString(customFields));
    }
}

void GameAnalytics::startSession()
{
    if(_impl)
    {
        _impl->StartSession();
    }
}

void GameAnalytics::endSession()
{
    if(_impl)
    {
        _impl->EndSession();
    }
}

void GameAnalytics::onQuit()
{
    if(_impl)
    {
        _impl->OnQuit();
    }
}

godot::String GameAnalytics::getRemoteConfigsValueAsString(const String& key, const String& defaultValue)
{
    if(_impl)
    {
        std::string config = _impl->GetRemoteConfigsValueAsString(ToStdString(key), ToStdString(defaultValue));
        return String(config.c_str());
    }

    return defaultValue;
}

bool GameAnalytics::isRemoteConfigsReady()
{
    if(_impl)
    {
        return _impl->IsRemoteConfigsReady();
    }

    return false;
}

godot::String GameAnalytics::getRemoteConfigsContentAsString()
{
    if(_impl)
    {
        std::string remoteConfigs = _impl->GetRemoteConfigsContentAsString();
        return String(remoteConfigs.c_str());
    }

    return "";
}

godot::String GameAnalytics::getUserId() const
{
    if(_impl)
    {
        std::string uid = _impl->GetUserId();
        return String(uid.c_str());
    }

    return "";
}

godot::String GameAnalytics::getExternalUserId() const
{
    if(_impl)
    {
        std::string id = _impl->GetExternalUserId();
        return String(id.c_str());
    }

    return "";
}

void GameAnalytics::setExternalUserId(godot::String const& extId)
{
    if(_impl)
    {
        _impl->SetExternalUserId(ToStdString(extId));
    }
} 

godot::String GameAnalytics::getABTestingId() const
{
    if(_impl)
    {
        std::string id = _impl->GetABTestingId();
        return String(id.c_str());
    }

    return "";
}

godot::String GameAnalytics::getABTestingVariantId() const
{
    if(_impl)
    {
        std::string id = _impl->GetABTestingVariantId();
        return String(id.c_str());
    }

    return "";
}

void GameAnalytics::enableSDKInitEvent(bool flag)
{
    if(_impl)
    {
        _impl->EnableSDKInitEvent(flag);
    }
}

void GameAnalytics::enableFpsHistogram(godot::Callable tracker)
{
    if(_impl)
    {
        if(tracker.is_null())
        {
            _impl->EnableFpsHistogram(gameanalytics::FPSTracker(), false);
            return;
        }

        gameanalytics::FPSTracker fpsTracker =
        [tracker]() -> float
        {
            if(tracker.is_valid())
            {
                Variant result = tracker.call();
                if(result.get_type() == Variant::FLOAT)
                {
                    float fps = result;
                    return fps;
                }
            }
            
            return 0.f;
        };

        _impl->EnableFpsHistogram(fpsTracker, true);
    }
}

void GameAnalytics::enableMemoryHistogram(bool flag)
{
    if(_impl)
    {
        _impl->EnableMemoryHistogram(flag);
    }
}

void GameAnalytics::enableHealthHardwareInfo(bool flag)
{
    if(_impl)
    {
        _impl->EnableHealthHardwareInfo(flag);
    }
}

void GameAnalytics::useRandomizedId(bool flag)
{
    if(_impl)
    {
        _impl->UseRandomizedId(flag);
    }
}

void GameAnalytics::setWritablePath(godot::String const& path)
{
    if(_impl)
    {
        _impl->SetWritablePath(ToStdString(path));
    }
}

godot::Variant GameAnalytics::getRemoteConfigsValueAsJSON(godot::String const& key)
{
    if(_impl)
    {
        std::string json = _impl->GetRemoteConfigsValueAsJson(ToStdString(key));
        if(!json.empty())
        {
            godot::Ref<godot::JSON> j;
            j.instantiate();

            if(j->parse(json.c_str()) != godot::OK)
            {
                return Variant();
            }

            return j->get_data();
        }   
    }

    return Variant();
}

void GameAnalytics::_bind_methods()
{
    using namespace godot;

    ClassDB::bind_method(D_METHOD("configureAvailableCustomDimensions01", "customDimensions"), &GameAnalytics::configureAvailableCustomDimensions01);
    ClassDB::bind_method(D_METHOD("configureAvailableCustomDimensions02", "customDimensions"), &GameAnalytics::configureAvailableCustomDimensions02);
    ClassDB::bind_method(D_METHOD("configureAvailableCustomDimensions03", "customDimensions"), &GameAnalytics::configureAvailableCustomDimensions03);

    ClassDB::bind_method(D_METHOD("configureAvailableResourceCurrencies", "resourceCurrencies"), &GameAnalytics::configureAvailableResourceCurrencies);
    ClassDB::bind_method(D_METHOD("configureAvailableResourceItemTypes", "resourceItemTypes"), &GameAnalytics::configureAvailableResourceItemTypes);

    ClassDB::bind_method(D_METHOD("configureBuild", "build"), &GameAnalytics::configureBuild);
    ClassDB::bind_method(D_METHOD("configureAutoDetectAppVersion", "flag"), &GameAnalytics::configureAutoDetectAppVersion);
    ClassDB::bind_method(D_METHOD("configureUserId", "userId"), &GameAnalytics::configureUserId);

    ClassDB::bind_method(D_METHOD("init", "gameKey", "secretKey"), &GameAnalytics::init);

    ClassDB::bind_method(D_METHOD("addBusinessEvent", "currency", "amount", "itemType", "itemId", "cartType", "options"), &GameAnalytics::addBusinessEvent);
    ClassDB::bind_method(D_METHOD("addResourceEvent", "flow", "currency", "amount", "itemType", "itemId", "options"), &GameAnalytics::addResourceEvent);
    ClassDB::bind_method(D_METHOD("addProgressionEvent", "status", "progression1", "progression2", "progression3", "options"), &GameAnalytics::addProgressionEvent);
    ClassDB::bind_method(D_METHOD("addDesignEvent", "eventId", "options"), &GameAnalytics::addDesignEvent);
    ClassDB::bind_method(D_METHOD("addErrorEvent", "severity", "message", "options"), &GameAnalytics::addErrorEvent);
    ClassDB::bind_method(D_METHOD("addAdEvent", "adAction", "adType", "adSdkName", "adPlacement", "options"), &GameAnalytics::addAdEvent);
    ClassDB::bind_method(D_METHOD("addDesignEventWithValue", "eventId", "value"), &GameAnalytics::addDesignEventWithValue);
    ClassDB::bind_method(D_METHOD("addProgressionEventWithScore", "status", "progression1", "progression2", "progression3", "score"), &GameAnalytics::addProgressionEventWithScore);

    ClassDB::bind_method(D_METHOD("setEnabledInfoLog", "flag"), &GameAnalytics::setEnabledInfoLog);
    ClassDB::bind_method(D_METHOD("setEnabledVerboseLog", "flag"), &GameAnalytics::setEnabledVerboseLog);
    ClassDB::bind_method(D_METHOD("setEnabledManualSessionHandling", "flag"), &GameAnalytics::setEnabledManualSessionHandling);
    ClassDB::bind_method(D_METHOD("setEnabledErrorReporting", "flag"), &GameAnalytics::setEnabledErrorReporting);
    ClassDB::bind_method(D_METHOD("setEnabledEventSubmission", "flag"), &GameAnalytics::setEnabledEventSubmission);

    ClassDB::bind_method(D_METHOD("setCustomDimension01", "dimension"), &GameAnalytics::setCustomDimension01);
    ClassDB::bind_method(D_METHOD("setCustomDimension02", "dimension"), &GameAnalytics::setCustomDimension02);
    ClassDB::bind_method(D_METHOD("setCustomDimension03", "dimension"), &GameAnalytics::setCustomDimension03);

    ClassDB::bind_method(D_METHOD("setGlobalCustomEventFields", "customFields"), &GameAnalytics::setGlobalCustomEventFields);

    ClassDB::bind_method(D_METHOD("startSession"), &GameAnalytics::startSession);
    ClassDB::bind_method(D_METHOD("endSession"), &GameAnalytics::endSession);
    ClassDB::bind_method(D_METHOD("onQuit"), &GameAnalytics::onQuit);

    ClassDB::bind_method(D_METHOD("getRemoteConfigsValueAsString", "key", "defaultValue"), &GameAnalytics::getRemoteConfigsValueAsString);
    ClassDB::bind_method(D_METHOD("isRemoteConfigsReady"), &GameAnalytics::isRemoteConfigsReady);
    ClassDB::bind_method(D_METHOD("getRemoteConfigsContentAsString"), &GameAnalytics::getRemoteConfigsContentAsString);
    ClassDB::bind_method(D_METHOD("getRemoteConfigsValueAsJSON", "key"), &GameAnalytics::getRemoteConfigsValueAsJSON);

    ClassDB::bind_method(D_METHOD("enableSDKInitEvent", "flag"), &GameAnalytics::enableSDKInitEvent);
    ClassDB::bind_method(D_METHOD("enableFpsHistogram", "tracker"), &GameAnalytics::enableFpsHistogram);
    ClassDB::bind_method(D_METHOD("enableHealthHardwareInfo", "flag"), &GameAnalytics::enableHealthHardwareInfo);
    ClassDB::bind_method(D_METHOD("enableMemoryHistogram", "flag"), &GameAnalytics::enableMemoryHistogram);

    ClassDB::bind_method(D_METHOD("setWritablePath", "path"), &GameAnalytics::setWritablePath);
    ClassDB::bind_method(D_METHOD("setExternalUserId", "id"), &GameAnalytics::setExternalUserId);

    ClassDB::bind_method(D_METHOD("getUserId"), &GameAnalytics::getUserId);
    ClassDB::bind_method(D_METHOD("getExternalUserId"), &GameAnalytics::getExternalUserId);
    ClassDB::bind_method(D_METHOD("getABTestingId"), &GameAnalytics::getABTestingId);
    ClassDB::bind_method(D_METHOD("getABTestingVariantId"), &GameAnalytics::getABTestingVariantId);
    ClassDB::bind_method(D_METHOD("useRandomizedId"), &GameAnalytics::useRandomizedId);
}
