#import "GameAnalytics/GameAnalytics.h"
#import "GAWrapperIOS.h"

// Objective-C++ wrapper for FPSTracker
@interface GAHealthMetricsProvider : NSObject <GAHealthMetricsDelegate>
{
    std::function<float()> fpsTracker;
}
- (instancetype)initWithFPSTracker:(const std::function<float()>&)tracker;
@end

@implementation GAHealthMetricsProvider
- (instancetype)initWithFPSTracker:(const std::function<float()>&)tracker {
    self = [super init];
    if (self) {
        fpsTracker = tracker;
    }
    return self;
}
- (double)provideCurrentFPS {
    if (fpsTracker) {
        return (double)fpsTracker();
    }
    return -1.0;
}
@end

namespace gameanalytics
{
    NSString* ToNSString(std::string const& str)
    {
        NSString *s = (!str.empty()) ? [NSString stringWithUTF8String:str.c_str()] : nil;
        return s;
    }

    std::string FromNSString(NSString* str)
    {
        std::string s = (str != nil) ? [str UTF8String] : "";
        return s;
    }

    void GAWrapperIOS::SetAvailableCustomDimensions01(const std::vector<std::string>& list) 
    {
        NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
        for (const std::string& s : list)
        {
            [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
        }
        NSArray *list_array = tmpary;
        [GameAnalytics configureAvailableCustomDimensions01:list_array];
    }

    void GAWrapperIOS::SetAvailableCustomDimensions02(const std::vector<std::string>& list) {
        NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
        for (const std::string& s : list)
        {
            [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
        }
        NSArray *list_array = tmpary;
        [GameAnalytics configureAvailableCustomDimensions02:list_array];
    }

    void GAWrapperIOS::SetAvailableCustomDimensions03(const std::vector<std::string>& list) {
        NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
        for (const std::string& s : list)
        {
            [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
        }
        NSArray *list_array = tmpary;
        [GameAnalytics configureAvailableCustomDimensions03:list_array];
    }

    void GAWrapperIOS::SetAvailableResourceCurrencies(const std::vector<std::string>& list) {
        NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
        for (const std::string& s : list)
        {
            [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
        }
        NSArray *list_array = tmpary;
        [GameAnalytics configureAvailableResourceCurrencies:list_array];
    }

    void GAWrapperIOS::SetAvailableResourceItemTypes(const std::vector<std::string>& list) {
        NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
        for (const std::string& s : list)
        {
            [tmpary addObject: [NSString stringWithUTF8String: s.c_str()]];
        }
        NSArray *list_array = tmpary;
        [GameAnalytics configureAvailableResourceItemTypes:list_array];
    }

    void GAWrapperIOS::SetBuild(std::string const& build) {
        NSString *buildString = ToNSString(build);
        [GameAnalytics configureBuild:buildString];
    }

    void GAWrapperIOS::SetAutoDetectAppVersion(bool flag) {
        [GameAnalytics configureAutoDetectAppVersion:flag];
    }

    void GAWrapperIOS::SetCustomUserId(std::string const& userId) {
        NSString *userIdString = ToNSString(userId);
        [GameAnalytics configureUserId:userIdString];
    }

    void GAWrapperIOS::SetGameEngineVersion(std::string const& gameEngineSdkVersion) {
        NSString *gameEngineSdkVersionString = ToNSString(gameEngineSdkVersion);
        [GameAnalytics configureSdkVersion:gameEngineSdkVersionString];
    }

    void GAWrapperIOS::SetSDKVersion(std::string const& sdkVersion) {
        NSString *sdkVersionString = ToNSString(sdkVersion);
        [GameAnalytics configureSdkVersion:sdkVersionString];
    }

    void GAWrapperIOS::SetGlobalCustomEventFields(std::string const& fields) {

        NSString *jsonString = ToNSString(fields);
        NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];

        NSError *error = nil;
        NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:&error];

        if (!error)
        {
            [GameAnalytics setGlobalCustomEventFields:jsonDict];
        }
    }

    void GAWrapperIOS::Initialize(std::string const& gameKey, std::string const& gameSecret) {
        NSString *gameKeyString = ToNSString(gameKey);
        NSString *gameSecretString = ToNSString(gameSecret);

        [GameAnalytics initializeWithGameKey:gameKeyString gameSecret:gameSecretString];
    }

    void GAWrapperIOS::AddBusinessEvent(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& fields, bool mergeFields) {
        NSString *currencyString = ToNSString(currency);
        NSInteger amountInteger = (NSInteger)amount;
        NSString *itemTypeString = ToNSString(itemType);
        NSString *itemIdString = ToNSString(itemId);
        NSString *cartTypeString = ToNSString(cartType);
        NSString *receiptString = ToNSString(receipt);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }

        [GameAnalytics addBusinessEventWithCurrency:currencyString
                                            amount:amountInteger
                                        itemType:itemTypeString
                                            itemId:itemIdString
                                        cartType:cartTypeString
                                            receipt:receiptString
                                    customFields:fields_dict
                                        mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddBusinessEventWithReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& receipt, std::string const& store, std::string const& signature, std::string const& fields, bool mergeFields)
    {
        return AddBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, fields, mergeFields);
    }

    void GAWrapperIOS::AddBusinessEventAndAutoFetchReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& fields, bool mergeFields) {
        NSString *currencyString = ToNSString(currency);
        NSInteger amountInteger = (NSInteger)amount;
        NSString *itemTypeString = ToNSString(itemType);
        NSString *itemIdString = ToNSString(itemId);
        NSString *cartTypeString = ToNSString(cartType);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }

        [GameAnalytics addBusinessEventWithCurrency:currencyString
                                            amount:amountInteger
                                        itemType:itemTypeString
                                            itemId:itemIdString
                                        cartType:cartTypeString
                                autoFetchReceipt:true
                                            customFields:fields_dict
                                            mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddResourceEvent(EGAResourceFlowType flowType, std::string const& currency, float amount, std::string const& itemType, std::string const& itemId, std::string const& fields, bool mergeFields) {
        NSString *currencyString = ToNSString(currency);
        NSNumber* amountNumber = [NSNumber numberWithFloat:amount];;
        NSString *itemTypeString = ToNSString(itemType);
        NSString *itemIdString = ToNSString(itemId);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }

        [GameAnalytics addResourceEventWithFlowType:(GAResourceFlowType)flowType
                                        currency:currencyString
                                            amount:amountNumber
                                        itemType:itemTypeString
                                            itemId:itemIdString
                                            customFields:fields_dict
                                            mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddProgressionEvent(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, std::string const& fields, bool mergeFields) {
        NSString *progression01String = ToNSString(progression01);
        NSString *progression02String = ToNSString(progression02);
        NSString *progression03String = ToNSString(progression03);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }

        [GameAnalytics addProgressionEventWithProgressionStatus:(GAProgressionStatus)progressionStatus
                                                progression01:progression01String
                                                progression02:progression02String
                                                progression03:progression03String
                                                        customFields:fields_dict
                                                        mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddProgressionEventWithScore(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, int score, std::string const& fields, bool mergeFields) {
        NSString *progression01String = ToNSString(progression01);
        NSString *progression02String = ToNSString(progression02);
        NSString *progression03String = ToNSString(progression03);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }

        [GameAnalytics addProgressionEventWithProgressionStatus:(GAProgressionStatus)progressionStatus
                                                progression01:progression01String
                                                progression02:progression02String
                                                progression03:progression03String
                                                        score:score
                                                        customFields:fields_dict
                                                        mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddDesignEvent(std::string const& eventId, std::string const& fields, bool mergeFields) {
        NSString *eventIdString = ToNSString(eventId);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }

        [GameAnalytics addDesignEventWithEventId:eventIdString value:nil customFields:fields_dict mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddDesignEventWithValue(std::string const& eventId, float value, std::string const& fields, bool mergeFields) {
        NSString *eventIdString = ToNSString(eventId);
        NSNumber *valueNumber = [NSNumber numberWithFloat:value];
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }

        [GameAnalytics addDesignEventWithEventId:eventIdString value:valueNumber customFields:fields_dict mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddErrorEvent(EGAErrorSeverity severity, std::string const& message, std::string const& fields, bool mergeFields) {
        NSString *messageString = ToNSString(message);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }

        [GameAnalytics addErrorEventWithSeverity:(GAErrorSeverity)severity message:messageString customFields:fields_dict mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddAdEvent(EGAAdAction action, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, std::string const& fields, bool mergeFields) {
        NSString *adSdkNameString = ToNSString(adSdkName);
        NSString *adPlacementString = ToNSString(adPlacement);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }
        [GameAnalytics addAdEventWithAction:(GAAdAction)action
                                    adType:(GAAdType)adType
                                adSdkName:adSdkNameString
                                adPlacement:adPlacementString
                                customFields:fields_dict
                                mergeFields:mergeFields];
    }
    void GAWrapperIOS::AddAdEventWithDuration(EGAAdAction action, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, int64_t duration, std::string const& fields, bool mergeFields) {
        NSString *adSdkNameString = ToNSString(adSdkName);
        NSString *adPlacementString = ToNSString(adPlacement);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }
        [GameAnalytics addAdEventWithAction:(GAAdAction)action
                                    adType:(GAAdType)adType
                                adSdkName:adSdkNameString
                                adPlacement:adPlacementString
                                duration:(NSInteger)duration
                                customFields:fields_dict
                                mergeFields:mergeFields];
    }

    void GAWrapperIOS::AddAdEventWithReason(::EGAAdAction action, ::EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, ::EGAAdError noAdReason, std::string const& fields, bool mergeFields) {
        NSString *adSdkNameString = ToNSString(adSdkName);
        NSString *adPlacementString = ToNSString(adPlacement);
        NSString *fieldsString = ToNSString(fields);
        NSDictionary *fields_dict = nil;
        if (fieldsString) {
            fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
        }
        [GameAnalytics addAdEventWithAction:(GAAdAction)action
                                    adType:(GAAdType)adType
                                adSdkName:adSdkNameString
                                adPlacement:adPlacementString
                                noAdReason:(GAAdError)noAdReason
                                customFields:fields_dict
                                mergeFields:mergeFields];
    }

    void GAWrapperIOS::SetInfoLog(bool flag) {
        [GameAnalytics setEnabledInfoLog:flag];
    }

    void GAWrapperIOS::SetVerboseLog(bool flag) {
        [GameAnalytics setEnabledVerboseLog:flag];
    }

    void GAWrapperIOS::SetEnabledManualSessionHandling(bool flag) {
        [GameAnalytics setEnabledManualSessionHandling:flag];
    }

    void GAWrapperIOS::SetEnabledErrorReporting(bool flag) {
        [GameAnalytics setEnabledErrorReporting:flag];
    }

    void GAWrapperIOS::SetEnabledEventSubmission(bool flag, bool doOfflineCache) {
        [GameAnalytics setEnabledEventSubmission:flag];
    }

    void GAWrapperIOS::SetCustomDimension01(std::string const& customDimension) {
        NSString *customDimensionString = ToNSString(customDimension);
        [GameAnalytics setCustomDimension01:customDimensionString];
    }

    void GAWrapperIOS::SetCustomDimension02(std::string const& customDimension) {
        NSString *customDimensionString = ToNSString(customDimension);
        [GameAnalytics setCustomDimension02:customDimensionString];
    }

    void GAWrapperIOS::SetCustomDimension03(std::string const& customDimension) {
        NSString *customDimensionString = ToNSString(customDimension);
        [GameAnalytics setCustomDimension03:customDimensionString];
    }

    void GAWrapperIOS::StartSession() {
        [GameAnalytics startSession];
    }

    void GAWrapperIOS::EndSession() {
        [GameAnalytics endSession];
    }

    std::string GAWrapperIOS::GetRemoteConfigsValueAsString(std::string const& key, std::string const& defaultValue) {
        NSString *keyString = ToNSString(key);
        NSString *result = [GameAnalytics getRemoteConfigsValueAsString:keyString];

        std::string s = result != nil ? [result UTF8String] : defaultValue;
        return s;
    }

    double GAWrapperIOS::GetRemoteConfigsValueAsNumber(std::string const& key, double defaultValue) {
        return defaultValue;
    }

    std::string GAWrapperIOS::GetRemoteConfigsValueAsJson(std::string const& key) {
        return "";
    }

    bool GAWrapperIOS::IsRemoteConfigsReady() {
        return [GameAnalytics isRemoteConfigsReady] ? true : false;
    }

    std::string GAWrapperIOS::GetRemoteConfigsContentAsString() {
        NSString *result = [GameAnalytics getRemoteConfigsContentAsString];

        std::string s = FromNSString(result);
        return s;
    }

    std::string GAWrapperIOS::GetUserId() {
        NSString* uid = [GameAnalytics getUserId];
        return FromNSString(uid);
    }

    std::string GAWrapperIOS::GetExternalUserId() {
        NSString* uid = [GameAnalytics getExternalUserId];
        return FromNSString(uid);
    }

    void GAWrapperIOS::SetExternalUserId(std::string const& id) {
        NSString* uid = ToNSString(id);
        [GameAnalytics configureExternalUserId:uid];
    }

    std::string GAWrapperIOS::GetABTestingId() {
        NSString *result = [GameAnalytics getABTestingId];

        std::string s = FromNSString(result);
        return s;
    }

    std::string GAWrapperIOS::GetABTestingVariantId() {
        NSString *result = [GameAnalytics getABTestingVariantId];

        std::string s = FromNSString(result);
        return s;
    }

    void GAWrapperIOS::EnableAdvertisingId(bool value)
    {
        // Note: This method is deprecated and has no effect.
    }

    void GAWrapperIOS::EnableSDKInitEvent(bool value)
    {
        [GameAnalytics enableSDKInitEvent:value];
    }



    void GAWrapperIOS::EnableFpsHistogram(FPSTracker tracker, bool value)
    {
        if (value)
        {
            // Always create a new delegate with the latest tracker
            GAHealthMetricsProvider *provider = [[GAHealthMetricsProvider alloc] initWithFPSTracker:tracker];
            [GameAnalytics setHealthMetricsDelegate:provider];
        }
        else
        {
            [GameAnalytics setHealthMetricsDelegate:nil];
        }
		
        [GameAnalytics enableFpsHistogram:value];
    }

    int64_t GAWrapperIOS::GetElapsedSessionTime()
    {
        // Returns the elapsed time for the current session in seconds
        return (int64_t)[GameAnalytics getElapsedSessionTime];
    }

    int64_t GAWrapperIOS::GetElapsedTimeForPreviousSession()
    {
        // Returns the elapsed time for the previous session in seconds
        return (int64_t)[GameAnalytics getElapsedTimeForPreviousSession];
    }

    int64_t GAWrapperIOS::GetElapsedTimeFromAllSessions()
    {
        // Returns the total elapsed time from all sessions in seconds
        return (int64_t)[GameAnalytics getElapsedTimeFromAllSessions];
    }

    void GAWrapperIOS::EnableMemoryHistogram(bool value)
    {
        [GameAnalytics enableMemoryHistogram:value];
    }

    void GAWrapperIOS::EnableHealthHardwareInfo(bool value)
    {
        [GameAnalytics enableHealthHardwareInfo:value];
    }

    void GAWrapperIOS::OnQuit()
    {

    }

    void GAWrapperIOS::SetWritablePath(std::string const& path)
    {
        (void)path;
    }

    void GAWrapperIOS::UseRandomizedId(bool flag)
    {
        (void)flag;
    }

}