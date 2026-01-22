//
// GA-SDK-CPP
// Copyright 2018 GameAnalytics C++ SDK. All rights reserved.
//

#pragma once

#include "GameAnalytics/GATypes.h"

namespace gameanalytics
{
    class GameAnalytics
    {
     public:

         /**
          * @brief: sets the available custom dimensions for index 1, needs to be called before initialization
          * 
          * @param customDimensions: valid values to be used as customDimension0
          */
         static void configureAvailableCustomDimensions01(const StringVector &customDimensions);

         /**
          * @brief: sets the available custom dimensions for index 2, needs to be called before initialization
          * 
          * @param customDimensions: valid values
          */
         static void configureAvailableCustomDimensions02(const StringVector &customDimensions);

         /**
          * @brief: sets the available custom dimensions for index 3, needs to be called before initialization
          * 
          * @param customDimensions: valid values to be used as customDimension3
          */
         static void configureAvailableCustomDimensions03(const StringVector &customDimensions);

         /**
          * @brief 
          * 
          * @param resourceCurrencies 
          */
         static void configureAvailableResourceCurrencies(const StringVector &resourceCurrencies);
         static void configureAvailableResourceItemTypes(const StringVector &resourceItemTypes);

         static void configureBuild(std::string const& build);
         static void configureWritablePath(std::string const& writablePath);
         static void configureBuildPlatform(std::string const& platform);
         static void configureCustomLogHandler(const LogHandler &logHandler);
         static void disableDeviceInfo();
         static void configureDeviceModel(std::string const& deviceModel);
         static void configureDeviceManufacturer(std::string const& deviceManufacturer);

         // the version of SDK code used in an engine. Used for sdk_version field.
         // !! if set then it will override the SdkWrapperVersion.
         // example "unity 4.6.9"
         static void configureSdkGameEngineVersion(std::string const& sdkGameEngineVersion);
         // the version of the game engine (if used and version is available)
         static void configureGameEngineVersion(std::string const& engineVersion);

         static void configureUserId(std::string const& uId);
        
         static void configureExternalUserId(std::string const& extId);

         // initialize - starting SDK (need configuration before starting)
         static void initialize(std::string const& gameKey, std::string const& gameSecret);

         // add events
         static void addBusinessEvent(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& customFields = "", bool mergeFields = false);

         static void addResourceEvent(EGAResourceFlowType flowType, std::string const& currency, float amount, std::string const& itemType, std::string const& itemId, std::string const& customFields = "", bool mergeFields = false);

         static void addProgressionEvent(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02 = "", std::string const& progression03 = "", std::string const& customFields = "", bool mergeFields = false);
         static void addProgressionEvent(EGAProgressionStatus progressionStatus, int score, std::string const& progression01, std::string const& progression02 = "", std::string const& progression03 = "", std::string const& customFields = "", bool mergeFields = false);

         static void addDesignEvent(std::string const& eventId, std::string const& customFields = "", bool mergeFields = false);
         static void addDesignEvent(std::string const& eventId, double value, std::string const& customFields = "", bool mergeFields = false);

         static void addErrorEvent(EGAErrorSeverity severity, std::string const& message, std::string const& customFields = "", bool mergeFields = false);

         // set calls can be changed at any time (pre- and post-initialize)
         // some calls only work after a configure is called (setCustomDimension)
         static void setEnabledInfoLog(bool flag);
         static void setEnabledVerboseLog(bool flag);
         static void setEnabledManualSessionHandling(bool flag);
         static void setEnabledErrorReporting(bool flag);
         static void setEnabledEventSubmission(bool flag);
         static void setCustomDimension01(std::string const& dimension01);
         static void setCustomDimension02(std::string const& dimension02);
         static void setCustomDimension03(std::string const& dimension03);

         /////////// HEALTH EVENT

         static void enableSDKInitEvent(bool value = true);
         static void enableMemoryHistogram(bool value = true);
         static void enableFPSHistogram(FPSTracker fpsTracker, bool value = true);
         static void enableHardwareTracking(bool value = true);

         ///////////

         static void setGlobalCustomEventFields(std::string const& customFields);

         static void startSession();
         static void endSession();

         static std::string getRemoteConfigsValueAsString(std::string const& key, std::string const& defaultValue = "");
         static std::string getRemoteConfigsValueAsJson(std::string const& key);


         static bool        isRemoteConfigsReady();
         static void        addRemoteConfigsListener(const std::shared_ptr<IRemoteConfigsListener> &listener);
         static void        removeRemoteConfigsListener(const std::shared_ptr<IRemoteConfigsListener> &listener);
         
         static std::string getRemoteConfigsContentAsString();

         static std::string getUserId();
         static std::string getExternalUserId();

         static std::string getABTestingId();
         static std::string getABTestingVariantId();

         static int64_t getElapsedSessionTime();
         static int64_t getElapsedTimeFromAllSessions();
         static int64_t getElapsedTimeForPreviousSession();

         // game state changes
         // will affect how session is started / ended
         static void onResume();
         static void onSuspend();
         static void onQuit();

         static bool isThreadEnding();

     private:

        static bool _endThread;
        static bool isSdkReady(bool needsInitialized, bool warn = true, std::string const& message = "");
    };

} // namespace gameanalytics
