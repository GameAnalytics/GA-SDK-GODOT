#pragma once

#include "GAWrapper.h"

#include "godot_cpp/godot.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/classes/engine.hpp"

namespace gameanalytics 
{
    class GAWrapperWeb:
        public GAWrapper
    {
        godot::Object* _jsBridge{nullptr};

        bool InitJavascript();
        godot::Variant Eval(godot::String const& code);

        public:

            GAWrapperWeb();
        
            virtual void SetAvailableCustomDimensions01(std::vector<std::string> const& list) override;
            virtual void SetAvailableCustomDimensions02(std::vector<std::string> const& list) override;
            virtual void SetAvailableCustomDimensions03(std::vector<std::string> const& list) override;

            virtual void SetAvailableResourceCurrencies(std::vector<std::string> const& list) override;
            virtual void SetAvailableResourceItemTypes(std::vector<std::string> const& list) override;

            virtual void SetSDKVersion(std::string const& version) override;

            virtual void SetGameEngineVersion(std::string const& version) override;

            virtual void SetBuild(std::string const& build) override;
            virtual void SetCustomUserId(std::string const& userId) override;
            virtual void SetExternalUserId(std::string const& extUserId) override;

            virtual std::string GetUserId() override;
            virtual std::string GetExternalUserId() override;

            virtual void SetAutoDetectAppVersion(bool flag) override;

            virtual void Initialize(std::string const& gamekey, std::string const& gamesecret) override;

            virtual void SetCustomDimension01(std::string const& customDimension) override;
            virtual void SetCustomDimension02(std::string const& customDimension) override;
            virtual void SetCustomDimension03(std::string const& customDimension) override;

            virtual void SetGlobalCustomEventFields(std::string const& customFields) override;
            virtual void SetEnabledManualSessionHandling(bool enabled) override;
            virtual void SetEnabledEventSubmission(bool enable, bool offlineCaching = true) override;
            virtual void SetEnabledErrorReporting(bool flag) override;

            virtual void StartSession() override;
            virtual void EndSession() override;

            virtual void AddBusinessEvent(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const&cartType, std::string const& receipt, std::string const&  fields, bool mergeFields) override;
            virtual void AddBusinessEventAndAutoFetchReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const&  fields, bool mergeFields) override;
            virtual void AddBusinessEventWithReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& store, std::string const& signature, std::string const&  fields, bool mergeFields) override;

            virtual void AddResourceEvent(EGAResourceFlowType flowType, std::string const& currency, float amount, std::string const& itemType, std::string const& itemId, std::string const&  fields, bool mergeFields) override;

            virtual void AddProgressionEvent(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, std::string const&  fields, bool mergeFields) override;
            virtual void AddProgressionEventWithScore(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, int score, std::string const& fields, bool mergeFields) override;
            
            virtual void AddDesignEvent(std::string const& eventID, std::string const& fields, bool mergeFields) override;
            virtual void AddDesignEventWithValue(std::string const& eventId, float value, std::string const& fields, bool mergeFields) override;

            virtual void AddErrorEvent(EGAErrorSeverity severity, std::string const& message, std::string const&  fields, bool mergeFields) override;
            
            virtual void AddAdEventWithDuration(EGAAdAction adAction, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, int64_t duration, std::string const& fields, bool mergeFields) override;
            virtual void AddAdEventWithReason(EGAAdAction adAction, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, EGAAdError noAdReason, std::string const& fields, bool mergeFields) override;
            virtual void AddAdEvent(EGAAdAction adAction, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, std::string const& fields, bool mergeFields) override;

            virtual void SetInfoLog(bool enabled) override;
            virtual void SetVerboseLog(bool enabled) override;
            

            // ----------------------- REMOTE CONFIGS ---------------------- //

            virtual std::string GetRemoteConfigsValueAsString(std::string const& key, std::string const& defaultValue) override;

            virtual std::string GetRemoteConfigsValueAsJson(std::string const& key) override;

            virtual double GetRemoteConfigsValueAsNumber(std::string const& key, double defaultValue) override;

            virtual bool IsRemoteConfigsReady() override;

            virtual std::string GetRemoteConfigsContentAsString() override;

            virtual std::string GetABTestingId() override;

            virtual std::string GetABTestingVariantId() override;

            ///// HEALTH

            virtual void EnableSDKInitEvent(bool flag) override;

            virtual void EnableFpsHistogram(FPSTracker tracker, bool flag) override;

            virtual void EnableMemoryHistogram(bool flag) override;

            virtual void EnableHealthHardwareInfo(bool flag) override;

            /////

            virtual void EnableAdvertisingId(bool value) override;

            virtual void UseRandomizedId(bool value) override;

            virtual void OnQuit() override;

            virtual void SetWritablePath(std::string const& path) override;

            ///

            virtual int64_t GetElapsedSessionTime() override;

            virtual int64_t GetElapsedTimeForPreviousSession() override;
        
            virtual int64_t GetElapsedTimeFromAllSessions() override;
    };
}
