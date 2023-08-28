#include "GameAnalytics.h"
#include "core/config/engine.h"

#if __EMSCRIPTEN__
#define WEB_PLATFORM
// Uncomment to use with Godot 3.3 or lower
// #include "api/javascript_eval.h"
// Godot 3.4+
#include "api/javascript_singleton.h"
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define IOS_PLATFORM
#include "ios/src/GameAnalyticsCpp.h"
#else
#define OSX_PLATFORM
#include "cpp/src/GameAnalyticsExtern.h"
#endif
#elif defined(_WIN32) || defined(WIN32)
#define WINDOWS_PLATFORM
#include "cpp/src/GameAnalyticsExtern.h"
#elif defined(__linux__) || defined(__unix__) || defined(__unix) || defined(unix)
#define LINUX_PLATFORM
#include "cpp/src/GameAnalyticsExtern.h"
#endif

#define VERSION "godot 2.4.0"

GameAnalytics *GameAnalytics::instance = NULL;

GameAnalytics::GameAnalytics()
{
    ERR_FAIL_COND(instance != NULL); //<< SUCCESS!!! FIRST
    instance = this;
}

GameAnalytics *GameAnalytics::get_singleton()
{
    return instance;
}

GameAnalytics::~GameAnalytics()
{
    if (instance == this)
    {
        instance = NULL;
   }
}

void GameAnalytics::configureAvailableCustomDimensions01(const PackedStringArray &customDimensions)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureAvailableCustomDimensions01(customDimensions);
#elif defined(WEB_PLATFORM)
    String arrayString = "";
    if (customDimensions.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < customDimensions.size(); ++i)
        {
            String entry = customDimensions[i];
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
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableCustomDimensions01(JSON.parse('" + arrayString + "'))");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    String arrayString = "";

    if(customDimensions.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < customDimensions.size(); ++i)
        {
            String entry = customDimensions[i];
            if(i > 0)
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
    ::configureAvailableCustomDimensions01(arrayString.utf8().get_data());
#endif
}

void GameAnalytics::configureAvailableCustomDimensions02(const PackedStringArray &customDimensions)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureAvailableCustomDimensions02(customDimensions);
#elif defined(WEB_PLATFORM)
    String arrayString = "";
    if (customDimensions.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < customDimensions.size(); ++i)
        {
            String entry = customDimensions[i];
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
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableCustomDimensions02(JSON.parse('" + arrayString + "'))");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    String arrayString = "";

    if(customDimensions.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < customDimensions.size(); ++i)
        {
            String entry = customDimensions[i];
            if(i > 0)
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
    ::configureAvailableCustomDimensions02(arrayString.utf8().get_data());
#endif
}

void GameAnalytics::configureAvailableCustomDimensions03(const PackedStringArray &customDimensions)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureAvailableCustomDimensions03(customDimensions);
#elif defined(WEB_PLATFORM)
    String arrayString = "";
    if (customDimensions.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < customDimensions.size(); ++i)
        {
            String entry = customDimensions[i];
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
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableCustomDimensions03(JSON.parse('" + arrayString + "'))");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    String arrayString = "";

    if(customDimensions.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < customDimensions.size(); ++i)
        {
            String entry = customDimensions[i];
            if(i > 0)
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
    ::configureAvailableCustomDimensions03(arrayString.utf8().get_data());
#endif
}

void GameAnalytics::configureAvailableResourceCurrencies(const PackedStringArray &resourceCurrencies)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureAvailableResourceCurrencies(resourceCurrencies);
#elif defined(WEB_PLATFORM)
    String arrayString = "";
    if (resourceCurrencies.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < resourceCurrencies.size(); ++i)
        {
            String entry = resourceCurrencies[i];
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
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableResourceCurrencies(JSON.parse('" + arrayString + "'))");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    String arrayString = "";

    if(resourceCurrencies.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < resourceCurrencies.size(); ++i)
        {
            String entry = resourceCurrencies[i];
            if(i > 0)
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
    ::configureAvailableResourceCurrencies(arrayString.utf8().get_data());
#endif
}

void GameAnalytics::configureAvailableResourceItemTypes(const PackedStringArray &resourceItemTypes)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureAvailableResourceItemTypes(resourceItemTypes);
#elif defined(WEB_PLATFORM)
    String arrayString = "";
    if (resourceItemTypes.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < resourceItemTypes.size(); ++i)
        {
            String entry = resourceItemTypes[i];
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
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureAvailableResourceItemTypes(JSON.parse('" + arrayString + "'))");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    String arrayString = "";

    if(resourceItemTypes.size() > 0)
    {
        arrayString += "[\"";
        for (int i = 0; i < resourceItemTypes.size(); ++i)
        {
            String entry = resourceItemTypes[i];
            if(i > 0)
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
    ::configureAvailableResourceItemTypes(arrayString.utf8().get_data());
#endif
}

void GameAnalytics::configureBuild(const String &build)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureBuild(build.utf8().get_data());
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureBuild('" + build + "')");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::configureBuild(build.utf8().get_data());
#endif
}

void GameAnalytics::configureAutoDetectAppVersion(bool flag)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureAutoDetectAppVersion(flag);
#elif defined(WEB_PLATFORM)
    // TODO: add implementation
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    // Do nothing
#endif
}

void GameAnalytics::configureUserId(const String &userId)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureUserId(userId.utf8().get_data());
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureBuild('" + userId + "')");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::configureUserId(userId.utf8().get_data());
#endif
}

void GameAnalytics::configureSdkGameEngineVersion(const String &version)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureSdkGameEngineVersion(version.utf8().get_data());
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureSdkGameEngineVersion('" + version + "')");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::configureSdkGameEngineVersion(version.utf8().get_data());
#endif
}

void GameAnalytics::configureGameEngineVersion(const String &version)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureGameEngineVersion(version.utf8().get_data());
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.configureGameEngineVersion('" + version + "')");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::configureGameEngineVersion(version.utf8().get_data());
#endif
}

void GameAnalytics::init(const String &gameKey, const String &secretKey)
{
    Dictionary versionInfo = Engine::get_singleton()->get_version_info();
    String major = *(versionInfo.getptr("major"));
    String minor = *(versionInfo.getptr("minor"));
    String patch = *(versionInfo.getptr("patch"));
    String engineVersion = "godot " + major + "." + minor + "." + patch;
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::configureGameEngineVersion(engineVersion.utf8().get_data());
    GameAnalyticsCpp::configureSdkGameEngineVersion(VERSION);
    GameAnalyticsCpp::initialize(gameKey.utf8().get_data(), secretKey.utf8().get_data());
#elif defined(WEB_PLATFORM)
    configureGameEngineVersion(engineVersion);
    configureSdkGameEngineVersion(VERSION);
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.initialize('%s', '%s')", gameKey, secretKey));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::configureGameEngineVersion(engineVersion.utf8().get_data());
    ::configureSdkGameEngineVersion(VERSION);
    ::initialize(gameKey.utf8().get_data(), secretKey.utf8().get_data());
#endif
}

void GameAnalytics::addBusinessEvent(const Dictionary &options)
{
    String currency = "";
    int amount = 0;
    String itemType = "";
    String itemId = "";
    String cartType = "";
    String receipt = "";
    bool autoFetchReceipt = false;
    String fields = "{}";
    bool mergeFields = false;

    Array keys = options.keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        Variant key = keys[i];

        if(key == "currency")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                currency = *v;
            }
        }
        else if(key == "amount")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::INT)
            {
                amount = *v;
            }
        }
        else if(key == "itemType")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                itemType = *v;
            }
        }
        else if(key == "itemId")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                itemId = *v;
            }
        }
        else if(key == "cartType")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                cartType = *v;
            }
        }
        else if(key == "receipt")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                receipt = *v;
            }
        }
        else if(key == "autoFetchReceipt")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::BOOL)
            {
                autoFetchReceipt = *v;
            }
        }
        else if (key == "customFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                fields = *v;
            }
        }
        else if (key == "mergeFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::BOOL)
            {
                mergeFields = *v;
            }
        }
    }
#if defined(IOS_PLATFORM)
    if(autoFetchReceipt)
    {
        GameAnalyticsCpp::addBusinessEventAndAutoFetchReceipt(currency.utf8().get_data(), amount, itemType.utf8().get_data(), itemId.utf8().get_data(), cartType.utf8().get_data(), fields.utf8().get_data(), mergeFields);
    }
    else
    {
        GameAnalyticsCpp::addBusinessEvent(currency.utf8().get_data(), amount, itemType.utf8().get_data(), itemId.utf8().get_data(), cartType.utf8().get_data(), receipt.utf8().get_data(), fields.utf8().get_data(), mergeFields);
    }
#elif defined(WEB_PLATFORM)
    String lastPart = vformat("'%s', JSON.parse('%s'), %s", cartType, fields, mergeFields ? "true" : "false");
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addBusinessEvent('%s', %d, '%s', '%s', %s)", currency, amount, itemType, itemId, lastPart));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::addBusinessEvent(currency.utf8().get_data(), amount, itemType.utf8().get_data(), itemId.utf8().get_data(), cartType.utf8().get_data(), fields.utf8().get_data(), mergeFields);
#endif
}

void GameAnalytics::addResourceEvent(const Dictionary &options)
{
    int flowType = 0;
    String currency = "";
    float amount = 0;
    String itemType = "";
    String itemId = "";
    String fields = "{}";
    bool mergeFields = false;

    Array keys = options.keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        Variant key = keys[i];

        if(key == "flowType")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                String s = *v;
                if(s == "Source")
                {
                    flowType = 1;
                }
                else if(s == "Sink")
                {
                    flowType = 2;
                }
            }
        }
        else if(key == "currency")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                currency = *v;
            }
        }
        else if(key == "amount")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && (v->get_type() == Variant::Type::INT || v->get_type() == Variant::Type::FLOAT))
            {
                amount = *v;
            }
        }
        else if(key == "itemType")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                itemType = *v;
            }
        }
        else if(key == "itemId")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                itemId = *v;
            }
        }
        else if (key == "customFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                fields = *v;
            }
        }
        else if (key == "mergeFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::BOOL)
            {
                mergeFields = *v;
            }
        }
    }
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::addResourceEvent(flowType, currency.utf8().get_data(), amount, itemType.utf8().get_data(), itemId.utf8().get_data(), fields.utf8().get_data(), mergeFields);
#elif defined(WEB_PLATFORM)
    String lastPart = vformat("'%s', JSON.parse('%s'), %s", itemId, fields, mergeFields ? "true" : "false");
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addResourceEvent(%d, '%s', %f, '%s', %s)", flowType, currency, amount, itemType, lastPart));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::addResourceEvent(flowType, currency.utf8().get_data(), amount, itemType.utf8().get_data(), itemId.utf8().get_data(), fields.utf8().get_data(), mergeFields);
#endif
}

void GameAnalytics::addProgressionEvent(const Dictionary &options)
{
    int progressionStatus = 0;
    String progression01 = "";
    String progression02 = "";
    String progression03 = "";
    int score = 0;
    bool sendScore = false;
    String fields = "{}";
    bool mergeFields = false;

    Array keys = options.keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        Variant key = keys[i];

        if(key == "progressionStatus")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                String s = *v;
                if(s == "Start")
                {
                    progressionStatus = 1;
                }
                else if(s == "Complete")
                {
                    progressionStatus = 2;
                }
                else if(s == "Fail")
                {
                    progressionStatus = 3;
                }
            }
        }
        else if(key == "progression01")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                progression01 = *v;
            }
        }
        else if(key == "progression02")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                progression02 = *v;
            }
        }
        else if(key == "progression03")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                progression03 = *v;
            }
        }
        else if(key == "score")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::INT)
            {
                score = *v;
                sendScore = true;
            }
        }
        else if (key == "customFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                fields = *v;
            }
        }
        else if (key == "mergeFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::BOOL)
            {
                mergeFields = *v;
            }
        }
    }
#if defined(IOS_PLATFORM)
    if(sendScore)
    {
        GameAnalyticsCpp::addProgressionEventWithScore(progressionStatus, progression01.utf8().get_data(), progression02.utf8().get_data(), progression03.utf8().get_data(), score, fields.utf8().get_data(), mergeFields);
    }
    else
    {
        GameAnalyticsCpp::addProgressionEvent(progressionStatus, progression01.utf8().get_data(), progression02.utf8().get_data(), progression03.utf8().get_data(), fields.utf8().get_data(), mergeFields);
    }
#elif defined(WEB_PLATFORM)
    if (sendScore)
    {
        String lastPart = vformat("%d, JSON.parse('%s'), %s", score, fields, mergeFields ? "true" : "false");
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addProgressionEvent(%d, '%s', '%s', '%s', %s)", progressionStatus, progression01, progression02, progression03, lastPart));
    }
    else
    {
        String lastPart = vformat("JSON.parse('%s'), %s", fields, mergeFields ? "true" : "false");
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addProgressionEvent(%d, '%s', '%s', '%s', %s)", progressionStatus, progression01, progression02, progression03, lastPart));
    }
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    if(sendScore)
    {
        ::addProgressionEventWithScore(progressionStatus, progression01.utf8().get_data(), progression02.utf8().get_data(), progression03.utf8().get_data(), score, fields.utf8().get_data(), mergeFields);
    }
    else
    {
        ::addProgressionEvent(progressionStatus, progression01.utf8().get_data(), progression02.utf8().get_data(), progression03.utf8().get_data(), fields.utf8().get_data(), mergeFields);
    }
#endif
}

void GameAnalytics::addDesignEvent(const Dictionary &options)
{
    String eventId = "";
    float value = 0;
    bool sendValue = false;
    String fields = "{}";
    bool mergeFields = false;

    Array keys = options.keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        Variant key = keys[i];

        if(key == "eventId")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                eventId = *v;
            }
        }
        else if(key == "value")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && (v->get_type() == Variant::Type::INT || v->get_type() == Variant::Type::FLOAT))
            {
                value = *v;
                sendValue = true;
            }
        }
        else if (key == "customFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                fields = *v;
            }
        }
        else if (key == "mergeFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::BOOL)
            {
                mergeFields = *v;
            }
        }
    }
#if defined(IOS_PLATFORM)
    if(sendValue)
    {
        GameAnalyticsCpp::addDesignEventWithValue(eventId.utf8().get_data(), value, fields.utf8().get_data(), mergeFields);
    }
    else
    {
        GameAnalyticsCpp::addDesignEvent(eventId.utf8().get_data(), fields.utf8().get_data(), mergeFields);
    }
#elif defined(WEB_PLATFORM)
    if (sendValue)
    {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addDesignEvent('%s', %f, JSON.parse('%s'), %s)", eventId, value, fields, mergeFields ? "true" : "false"));
    }
    else
    {
        JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addDesignEvent('%s', JSON.parse('%s'), %s)", eventId, fields, mergeFields ? "true" : "false"));
    }
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    if(sendValue)
    {
        ::addDesignEventWithValue(eventId.utf8().get_data(), value, fields.utf8().get_data(), mergeFields);
    }
    else
    {
        ::addDesignEvent(eventId.utf8().get_data(), fields.utf8().get_data(), mergeFields);
    }
#endif
}

void GameAnalytics::addErrorEvent(const Dictionary &options)
{
    int severity = 0;
    String message = "";
    String fields = "{}";
    bool mergeFields = false;

    Array keys = options.keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        Variant key = keys[i];

        if(key == "severity")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                String s = *v;
                if(s == "Debug")
                {
                    severity = 1;
                }
                else if(s == "Info")
                {
                    severity = 2;
                }
                else if(s == "Warning")
                {
                    severity = 3;
                }
                else if(s == "Error")
                {
                    severity = 4;
                }
                else if(s == "Critical")
                {
                    severity = 5;
                }
            }
        }
        else if(key == "message")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                message = *v;
            }
        }
        else if (key == "customFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                fields = *v;
            }
        }
        else if (key == "mergeFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::BOOL)
            {
                mergeFields = *v;
            }
        }
    }
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::addErrorEvent(severity, message.utf8().get_data(), fields.utf8().get_data(), mergeFields);
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.addErrorEvent(%d, '%s', JSON.parse('%s'), %s)", severity, message, fields, mergeFields ? "true" : "false"));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::addErrorEvent(severity, message.utf8().get_data(), fields.utf8().get_data(), mergeFields);
#endif
}

void GameAnalytics::addAdEvent(const Dictionary &options)
{
    int adAction = 0;
    int adType = 0;
    int noAdReason = 0;
    String adSdkName = "";
    String adPlacement = "";
    bool sendDuration = false;
    int duration = -1;
    String fields = "{}";
    bool mergeFields = false;

    Array keys = options.keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        Variant key = keys[i];

        if (key == "adAction")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                String s = *v;
                if (s == "Clicked")
                {
                    adAction = 1;
                }
                else if (s == "Show")
                {
                    adAction = 2;
                }
                else if (s == "FailedShow")
                {
                    adAction = 3;
                }
                else if (s == "RewardReceived")
                {
                    adAction = 4;
                }
            }
        }
        else if (key == "adType")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                String s = *v;
                if (s == "Video")
                {
                    adType = 1;
                }
                else if (s == "RewardedVideo")
                {
                    adType = 2;
                }
                else if (s == "Playable")
                {
                    adType = 3;
                }
                else if (s == "Interstitial")
                {
                    adType = 4;
                }
                else if (s == "OfferWall")
                {
                    adType = 5;
                }
                else if (s == "Banner")
                {
                    adType = 6;
                }
            }
        }
        else if (key == "adSdkName")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                adSdkName = *v;
            }
        }
        else if (key == "adPlacement")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                adPlacement = *v;
            }
        }
        else if (key == "duration")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::INT)
            {
                duration = *v;
                sendDuration = true;
            }
        }
        else if (key == "noAdReason")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                String s = *v;
                if (s == "Unknown")
                {
                    noAdReason = 1;
                }
                else if (s == "Offline")
                {
                    noAdReason = 2;
                }
                else if (s == "NoFill")
                {
                    noAdReason = 3;
                }
                else if (s == "InternalError")
                {
                    noAdReason = 4;
                }
                else if (s == "InvalidRequest")
                {
                    noAdReason = 5;
                }
                else if (s == "UnableToPrecache")
                {
                    noAdReason = 6;
                }
            }
        }
        else if (key == "customFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::STRING)
            {
                fields = *v;
            }
        }
        else if (key == "mergeFields")
        {
            const Variant *v = options.getptr(key);
            if (v != NULL && v->get_type() == Variant::Type::BOOL)
            {
                mergeFields = *v;
            }
        }
    }
#if defined(IOS_PLATFORM)
    if(sendDuration)
    {
        GameAnalyticsCpp::addAdEventWithDuration(adAction, adType, adSdkName, adPlacement, duration, fields, mergeFields);
    }
    else
    {
        GameAnalyticsCpp::addAdEventWithNoAdReason(adAction, adType, adSdkName, adPlacement, noAdReason, fields, mergeFields);
    }
#elif defined(WEB_PLATFORM)
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
#endif
}

void GameAnalytics::setEnabledInfoLog(bool flag)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setEnabledInfoLog(flag);
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setEnabledInfoLog(%s)", flag ? "true" : "false"));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setEnabledInfoLog(flag);
#endif
}

void GameAnalytics::setEnabledVerboseLog(bool flag)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setEnabledVerboseLog(flag);
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setEnabledVerboseLog(%s)", flag ? "true" : "false"));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setEnabledVerboseLog(flag);
#endif
}

void GameAnalytics::setEnabledManualSessionHandling(bool flag)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setEnabledManualSessionHandling(flag);
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setEnabledManualSessionHandling(%s)", flag ? "true" : "false"));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setEnabledManualSessionHandling(flag);
#endif
}

void GameAnalytics::setEnabledErrorReporting(bool flag)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setEnabledErrorReporting(flag);
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setEnabledErrorReporting(%s)", flag ? "true" : "false"));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setEnabledErrorReporting(flag);
#endif
}

void GameAnalytics::setEnabledEventSubmission(bool flag)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setEnabledEventSubmission(flag);
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setEnabledEventSubmission(%s)", flag ? "true" : "false"));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setEnabledEventSubmission(flag);
#endif
}

void GameAnalytics::setCustomDimension01(const String &dimension)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setCustomDimension01(dimension.utf8().get_data());
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setCustomDimension01('%s')", dimension));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setCustomDimension01(dimension.utf8().get_data());
#endif
}

void GameAnalytics::setCustomDimension02(const String &dimension)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setCustomDimension02(dimension.utf8().get_data());
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setCustomDimension02('%s')", dimension));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setCustomDimension02(dimension.utf8().get_data());
#endif
}

void GameAnalytics::setCustomDimension03(const String &dimension)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setCustomDimension03(dimension.utf8().get_data());
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setCustomDimension03('%s')", dimension));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setCustomDimension03(dimension.utf8().get_data());
#endif
}

void GameAnalytics::setGlobalCustomEventFields(const String &customFields)
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::setGlobalCustomEventFields(customFields.utf8().get_data());
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.setGlobalCustomEventFields(JSON.parse('%s'))", !customFields.empty() ? customFields : "{}"));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::setGlobalCustomEventFields(customFields.utf8().get_data());
#endif
}

void GameAnalytics::startSession()
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::startSession();
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.startSession()");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    // Do nothing
#endif
}

void GameAnalytics::endSession()
{
#if defined(IOS_PLATFORM)
    GameAnalyticsCpp::endSession();
#elif defined(WEB_PLATFORM)
    JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.endSession()");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    // Do nothing
#endif
}

void GameAnalytics::onQuit()
{
#if defined(IOS_PLATFORM)
    // Do nothing
#elif defined(WEB_PLATFORM)
    // Do nothing
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    ::onQuit();
#endif
}

String GameAnalytics::getRemoteConfigsValueAsString(const Dictionary &options)
{
    String k = "";
    String defaultValue = "";
    bool useDefaultValue = false;
    Array keys = options.keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        Variant key = keys[i];

        if(key == "key")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                k = *v;
            }
        }
        else if(key == "defaultValue")
        {
            const Variant* v = options.getptr(key);
            if(v != NULL && v->get_type() == Variant::Type::STRING)
            {
                defaultValue = *v;
                useDefaultValue = true;
            }
        }
    }
#if defined(IOS_PLATFORM)
    if(useDefaultValue)
    {
        return GameAnalyticsCpp::getRemoteConfigsValueAsString(k.utf8().get_data(), defaultValue.utf8().get_data());
    }
    else
    {
        return GameAnalyticsCpp::getRemoteConfigsValueAsString(k.utf8().get_data());
    }
#elif defined(WEB_PLATFORM)
    if (useDefaultValue)
    {
        return String(JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.getRemoteConfigsValueAsString('%s', '%s')", k, defaultValue)));
    }
    else
    {
        return String(JavaScript::get_singleton()->eval(vformat("gameanalytics.GameAnalytics.getRemoteConfigsValueAsString('%s')", k)));
    }
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    if(useDefaultValue)
    {
        return String(::getRemoteConfigsValueAsStringWithDefaultValue(k.utf8().get_data(), defaultValue.utf8().get_data()));
    }
    else
    {
        return String(::getRemoteConfigsValueAsString(k.utf8().get_data()));
    }
#endif
}

bool GameAnalytics::isRemoteConfigsReady()
{
#if defined(IOS_PLATFORM)
    return GameAnalyticsCpp::isRemoteConfigsReady();
#elif defined(WEB_PLATFORM)
    return JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.isRemoteConfigsReady()");
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    return ::isRemoteConfigsReady();
#endif
}

String GameAnalytics::getRemoteConfigsContentAsString()
{
#if defined(IOS_PLATFORM)
    return GameAnalyticsCpp::getRemoteConfigsContentAsString();
#elif defined(WEB_PLATFORM)
    return String(JavaScript::get_singleton()->eval("gameanalytics.GameAnalytics.getRemoteConfigsContentAsString()"));
#elif defined(OSX_PLATFORM) || defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)
    return String(::getRemoteConfigsContentAsString());
#endif
}

void GameAnalytics::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("configureAvailableCustomDimensions01", "customDimensions"), &GameAnalytics::configureAvailableCustomDimensions01);
    ClassDB::bind_method(D_METHOD("configureAvailableCustomDimensions02", "customDimensions"), &GameAnalytics::configureAvailableCustomDimensions02);
    ClassDB::bind_method(D_METHOD("configureAvailableCustomDimensions03", "customDimensions"), &GameAnalytics::configureAvailableCustomDimensions03);

    ClassDB::bind_method(D_METHOD("configureAvailableResourceCurrencies", "resourceCurrencies"), &GameAnalytics::configureAvailableResourceCurrencies);
    ClassDB::bind_method(D_METHOD("configureAvailableResourceItemTypes", "resourceItemTypes"), &GameAnalytics::configureAvailableResourceItemTypes);

    ClassDB::bind_method(D_METHOD("configureBuild", "build"), &GameAnalytics::configureBuild);
    ClassDB::bind_method(D_METHOD("configureAutoDetectAppVersion", "flag"), &GameAnalytics::configureAutoDetectAppVersion);
    ClassDB::bind_method(D_METHOD("configureUserId", "userId"), &GameAnalytics::configureUserId);

    ClassDB::bind_method(D_METHOD("init", "gameKey", "secretKey"), &GameAnalytics::init);

    ClassDB::bind_method(D_METHOD("addBusinessEvent", "options"), &GameAnalytics::addBusinessEvent);
    ClassDB::bind_method(D_METHOD("addResourceEvent", "options"), &GameAnalytics::addResourceEvent);
    ClassDB::bind_method(D_METHOD("addProgressionEvent", "options"), &GameAnalytics::addProgressionEvent);
    ClassDB::bind_method(D_METHOD("addDesignEvent", "options"), &GameAnalytics::addDesignEvent);
    ClassDB::bind_method(D_METHOD("addErrorEvent", "options"), &GameAnalytics::addErrorEvent);
    ClassDB::bind_method(D_METHOD("addAdEvent", "options"), &GameAnalytics::addAdEvent);

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

    ClassDB::bind_method(D_METHOD("getRemoteConfigsValueAsString", "options"), &GameAnalytics::getRemoteConfigsValueAsString);
    ClassDB::bind_method(D_METHOD("isRemoteConfigsReady"), &GameAnalytics::isRemoteConfigsReady);
    ClassDB::bind_method(D_METHOD("getRemoteConfigsContentAsString"), &GameAnalytics::getRemoteConfigsContentAsString);
}
