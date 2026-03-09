#pragma once

#include <string>
#include <vector>
#include <stdint.h>
#include <functional>

#include "GAEnums.h"

namespace gameanalytics
{
    using FPSTracker = std::function<float()>;
    
    class GAWrapper
    {
        public:

        virtual ~GAWrapper() {};
        
        virtual void SetAvailableCustomDimensions01(std::vector<std::string> const& list) = 0;
        virtual void SetAvailableCustomDimensions02(std::vector<std::string> const& list) = 0;
        virtual void SetAvailableCustomDimensions03(std::vector<std::string> const& list) = 0;

        virtual void SetAvailableResourceCurrencies(std::vector<std::string> const& list) = 0;
        virtual void SetAvailableResourceItemTypes(std::vector<std::string> const& list) = 0;

        virtual void SetSDKVersion(std::string const& version) = 0;

        virtual void SetGameEngineVersion(std::string const& version) = 0;

        virtual void SetBuild(std::string const& build) = 0;
        virtual void SetCustomUserId(std::string const& userId) = 0;
        virtual void SetExternalUserId(std::string const& extUserId) = 0;

        virtual std::string GetUserId() = 0;
        virtual std::string GetExternalUserId() = 0;

        virtual void UseRandomizedId(bool value) = 0;

        virtual void SetAutoDetectAppVersion(bool flag) = 0;

        virtual void Initialize(std::string const& gamekey, std::string const& gamesecret) = 0;

        virtual void SetCustomDimension01(std::string const& customDimension) = 0;
        virtual void SetCustomDimension02(std::string const& customDimension) = 0;
        virtual void SetCustomDimension03(std::string const& customDimension) = 0;

        virtual void SetGlobalCustomEventFields(std::string const& customFields) = 0;
        virtual void SetEnabledManualSessionHandling (bool enabled) = 0;

        virtual void SetEnabledEventSubmission(bool enabled, bool doCache) = 0;
        virtual void SetEnabledErrorReporting(bool flag) = 0;

        virtual void StartSession() = 0;
        virtual void EndSession() = 0;

        virtual void AddBusinessEvent(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const&cartType, std::string const& receipt, std::string const&  fields, bool mergeFields) = 0;
        virtual void AddBusinessEventAndAutoFetchReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const&  fields, bool mergeFields) = 0;
        virtual void AddBusinessEventWithReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& store, std::string const& signature, std::string const& fields, bool mergeFields) = 0;

        virtual void AddResourceEvent(EGAResourceFlowType flowType, std::string const& currency, float amount, std::string const& itemType, std::string const& itemId, std::string const&  fields, bool mergeFields) = 0;

        virtual void AddProgressionEvent(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, std::string const&  fields, bool mergeFields) = 0;
        virtual void AddProgressionEventWithScore(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, int score, std::string const& fields, bool mergeFields) = 0;
        
        virtual void AddDesignEvent(std::string const& eventID, std::string const& fields, bool mergeFields) = 0;
        virtual void AddDesignEventWithValue(std::string const& eventId, float value, std::string const& fields, bool mergeFields) =  0;

        virtual void AddErrorEvent(EGAErrorSeverity severity, std::string const& message, std::string const&  fields, bool mergeFields) = 0;

        virtual void AddAdEventWithDuration(EGAAdAction adAction, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, int64_t duration, std::string const& fields, bool mergeFields) = 0;
        virtual void AddAdEventWithReason(EGAAdAction adAction, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, EGAAdError noAdReason, std::string const& fields, bool mergeFields) = 0;
        virtual void AddAdEvent(EGAAdAction adAction, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, std::string const& fields, bool mergeFields) = 0;

        virtual void SetInfoLog (bool enabled) = 0;
        virtual void SetVerboseLog (bool enabled) = 0;

        // ----------------------- REMOTE CONFIGS ---------------------- //
        virtual std::string GetRemoteConfigsValueAsString(std::string const& key, std::string const& defaultValue) = 0;

        virtual double GetRemoteConfigsValueAsNumber(std::string const& key, double defaultValue) = 0;

        virtual std::string GetRemoteConfigsValueAsJson(std::string const& key) = 0;

        virtual bool IsRemoteConfigsReady() = 0;

        virtual std::string GetRemoteConfigsContentAsString() = 0;

        virtual std::string GetABTestingId() = 0;

        virtual std::string GetABTestingVariantId() = 0;

        /////////////////// HEALTH /////////////////////////

        virtual void EnableSDKInitEvent(bool flag) = 0;

        virtual void EnableFpsHistogram(FPSTracker tracker, bool flag) = 0;

        virtual void EnableMemoryHistogram(bool flag) = 0;

        virtual void EnableHealthHardwareInfo(bool flag) = 0;

        //////////////////////////////////////////////////

        virtual void EnableAdvertisingId(bool enabled) = 0;

        //////////////////

        virtual void OnQuit() = 0;

        virtual void SetWritablePath(std::string const& path) = 0;

        //////////////////

        virtual int64_t GetElapsedSessionTime() = 0;

        virtual int64_t GetElapsedTimeForPreviousSession() = 0;
        
        virtual int64_t GetElapsedTimeFromAllSessions() = 0;

    };
}

