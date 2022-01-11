#import "GameAnalyticsCpp.h"
#import <GameAnalytics/GameAnalytics.h>
#include <string.h>
#include <stdio.h>

static bool isStringNullOrEmpty(const char* s)
{
    return s == NULL || strlen(s) == 0;
}

void GameAnalyticsCpp::configureAvailableCustomDimensions01(const PoolStringArray& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (int i = 0; i < list.size(); ++i)
    {
        String entry = list[i];
        [tmpary addObject: [NSString stringWithUTF8String: entry.utf8().get_data()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableCustomDimensions01:list_array];
}

void GameAnalyticsCpp::configureAvailableCustomDimensions02(const PoolStringArray& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (int i = 0; i < list.size(); ++i)
    {
        String entry = list[i];
        [tmpary addObject: [NSString stringWithUTF8String: entry.utf8().get_data()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableCustomDimensions02:list_array];
}

void GameAnalyticsCpp::configureAvailableCustomDimensions03(const PoolStringArray& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (int i = 0; i < list.size(); ++i)
    {
        String entry = list[i];
        [tmpary addObject: [NSString stringWithUTF8String: entry.utf8().get_data()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableCustomDimensions03:list_array];
}

void GameAnalyticsCpp::configureAvailableResourceCurrencies(const PoolStringArray& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (int i = 0; i < list.size(); ++i)
    {
        String entry = list[i];
        [tmpary addObject: [NSString stringWithUTF8String: entry.utf8().get_data()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableResourceCurrencies:list_array];
}

void GameAnalyticsCpp::configureAvailableResourceItemTypes(const PoolStringArray& list) {
    NSMutableArray * tmpary = [[NSMutableArray alloc] initWithCapacity: list.size()];
    for (int i = 0; i < list.size(); ++i)
    {
        String entry = list[i];
        [tmpary addObject: [NSString stringWithUTF8String: entry.utf8().get_data()]];
    }
    NSArray *list_array = tmpary;
    [GameAnalytics configureAvailableResourceItemTypes:list_array];
}

void GameAnalyticsCpp::configureBuild(const char *build) {
    NSString *buildString = !isStringNullOrEmpty(build) ? [NSString stringWithUTF8String:build] : nil;
    [GameAnalytics configureBuild:buildString];
}

void GameAnalyticsCpp::configureAutoDetectAppVersion(bool flag) {
    [GameAnalytics configureAutoDetectAppVersion:flag];
}

void GameAnalyticsCpp::configureUserId(const char *userId) {
    NSString *userIdString = !isStringNullOrEmpty(userId) ? [NSString stringWithUTF8String:userId] : nil;
    [GameAnalytics configureUserId:userIdString];
}

void GameAnalyticsCpp::configureSdkGameEngineVersion(const char *gameEngineSdkVersion) {
    NSString *gameEngineSdkVersionString = !isStringNullOrEmpty(gameEngineSdkVersion) ? [NSString stringWithUTF8String:gameEngineSdkVersion] : nil;
    [GameAnalytics configureSdkVersion:gameEngineSdkVersionString];
}

void GameAnalyticsCpp::configureGameEngineVersion(const char *gameEngineVersion) {
    NSString *gameEngineVersionString = !isStringNullOrEmpty(gameEngineVersion) ? [NSString stringWithUTF8String:gameEngineVersion] : nil;
    [GameAnalytics configureEngineVersion:gameEngineVersionString];
}

void GameAnalyticsCpp::initialize(const char *gameKey, const char *gameSecret) {
    NSString *gameKeyString = !isStringNullOrEmpty(gameKey) ? [NSString stringWithUTF8String:gameKey] : nil;
    NSString *gameSecretString = !isStringNullOrEmpty(gameSecret) ? [NSString stringWithUTF8String:gameSecret] : nil;

    [GameAnalytics initializeWithGameKey:gameKeyString gameSecret:gameSecretString];
}

void GameAnalyticsCpp::addBusinessEvent(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *receipt, const char *fields, bool mergeFields) {
    NSString *currencyString = !isStringNullOrEmpty(currency) ? [NSString stringWithUTF8String:currency] : nil;
    NSInteger amountInteger = (NSInteger)amount;
    NSString *itemTypeString = !isStringNullOrEmpty(itemType) ? [NSString stringWithUTF8String:itemType] : nil;
    NSString *itemIdString = !isStringNullOrEmpty(itemId) ? [NSString stringWithUTF8String:itemId] : nil;
    NSString *cartTypeString = !isStringNullOrEmpty(cartType) ? [NSString stringWithUTF8String:cartType] : nil;
    NSString *receiptString = !isStringNullOrEmpty(receipt) ? [NSString stringWithUTF8String:receipt] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
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

void GameAnalyticsCpp::addBusinessEventAndAutoFetchReceipt(const char *currency, int amount, const char *itemType, const char *itemId, const char *cartType, const char *fields, bool mergeFields) {
    NSString *currencyString = !isStringNullOrEmpty(currency) ? [NSString stringWithUTF8String:currency] : nil;
    NSInteger amountInteger = (NSInteger)amount;
    NSString *itemTypeString = !isStringNullOrEmpty(itemType) ? [NSString stringWithUTF8String:itemType] : nil;
    NSString *itemIdString = !isStringNullOrEmpty(itemId) ? [NSString stringWithUTF8String:itemId] : nil;
    NSString *cartTypeString = !isStringNullOrEmpty(cartType) ? [NSString stringWithUTF8String:cartType] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addBusinessEventWithCurrency:currencyString
                                         amount:amountInteger
                                       itemType:itemTypeString
                                         itemId:itemIdString
                                       cartType:cartTypeString
                               autoFetchReceipt:TRUE
                               customFields:fields_dict
                               mergeFields:mergeFields];
}

void GameAnalyticsCpp::addResourceEvent(int flowType, const char *currency, float amount, const char *itemType, const char *itemId, const char *fields, bool mergeFields) {
    NSString *currencyString = !isStringNullOrEmpty(currency) ? [NSString stringWithUTF8String:currency] : nil;
    NSNumber *amountNumber = [NSNumber numberWithFloat:amount];
    NSString *itemTypeString = !isStringNullOrEmpty(itemType) ? [NSString stringWithUTF8String:itemType] : nil;
    NSString *itemIdString = !isStringNullOrEmpty(itemId) ? [NSString stringWithUTF8String:itemId] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
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

void GameAnalyticsCpp::addProgressionEvent(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, const char *fields, bool mergeFields) {
    NSString *progression01String = !isStringNullOrEmpty(progression01) ? [NSString stringWithUTF8String:progression01] : nil;
    NSString *progression02String = !isStringNullOrEmpty(progression02) ? [NSString stringWithUTF8String:progression02] : nil;
    NSString *progression03String = !isStringNullOrEmpty(progression03) ? [NSString stringWithUTF8String:progression03] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
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

void GameAnalyticsCpp::addProgressionEventWithScore(int progressionStatus, const char *progression01, const char *progression02, const char *progression03, int score, const char *fields, bool mergeFields) {
    NSString *progression01String = !isStringNullOrEmpty(progression01) ? [NSString stringWithUTF8String:progression01] : nil;
    NSString *progression02String = !isStringNullOrEmpty(progression02) ? [NSString stringWithUTF8String:progression02] : nil;
    NSString *progression03String = !isStringNullOrEmpty(progression03) ? [NSString stringWithUTF8String:progression03] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
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

void GameAnalyticsCpp::addDesignEvent(const char *eventId, const char *fields, bool mergeFields) {
    NSString *eventIdString = !isStringNullOrEmpty(eventId) ? [NSString stringWithUTF8String:eventId] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addDesignEventWithEventId:eventIdString value:nil customFields:fields_dict mergeFields:mergeFields];
}

void GameAnalyticsCpp::addDesignEventWithValue(const char *eventId, float value, const char *fields, bool mergeFields) {
    NSString *eventIdString = !isStringNullOrEmpty(eventId) ? [NSString stringWithUTF8String:eventId] : nil;
    NSNumber *valueNumber = [NSNumber numberWithFloat:value];
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addDesignEventWithEventId:eventIdString value:valueNumber customFields:fields_dict mergeFields:mergeFields];
}

void GameAnalyticsCpp::addErrorEvent(int severity, const char *message, const char *fields, bool mergeFields) {
    NSString *messageString = !isStringNullOrEmpty(message) ? [NSString stringWithUTF8String:message] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addErrorEventWithSeverity:(GAErrorSeverity)severity message:messageString customFields:fields_dict mergeFields:mergeFields];
}

void GameAnalyticsCpp::addAdEvent(int adAction, int adType, const char *adSdkName, const char *adPlacement, const char *fields, bool mergeFields)
{
    NSString *adSdkNameString = !isStringNullOrEmpty(adSdkName) ? [NSString stringWithUTF8String:adSdkName] : nil;
    NSString *adPlacementString = !isStringNullOrEmpty(adPlacement) ? [NSString stringWithUTF8String:adPlacement] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addAdEventWithAction:(GAAdAction)adAction adType:(GAAdType)adType adSdkName:adSdkNameString adPlacement:adPlacementString customFields:fields_dict mergeFields:mergeFields];
}

void GameAnalyticsCpp::addAdEventWithDuration(int adAction, int adType, const char *adSdkName, const char *adPlacement, int duration, const char *fields, bool mergeFields)
{
    NSString *adSdkNameString = !isStringNullOrEmpty(adSdkName) ? [NSString stringWithUTF8String:adSdkName] : nil;
    NSString *adPlacementString = !isStringNullOrEmpty(adPlacement) ? [NSString stringWithUTF8String:adPlacement] : nil;
    NSInteger durationInteger = (NSInteger)duration;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addAdEventWithAction:(GAAdAction)adAction adType:(GAAdType)adType adSdkName:adSdkNameString adPlacement:adPlacementString duration:durationInteger customFields :fields_dict mergeFields:mergeFields];
}

void GameAnalyticsCpp::addAdEventWithNoAdReason(int adAction, int adType, const char *adSdkName, const char *adPlacement, int noAdReason, const char *fields, bool mergeFields)
{
    NSString *adSdkNameString = !isStringNullOrEmpty(adSdkName) ? [NSString stringWithUTF8String:adSdkName] : nil;
    NSString *adPlacementString = !isStringNullOrEmpty(adPlacement) ? [NSString stringWithUTF8String:adPlacement] : nil;
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }

    [GameAnalytics addAdEventWithAction:(GAAdAction)adAction adType:(GAAdType)adType adSdkName:adSdkNameString adPlacement:adPlacementString noAdReason:(GAAdError)noAdReason customFields:fields_dict mergeFields:mergeFields];
}

void GameAnalyticsCpp::setEnabledInfoLog(bool flag) {
    [GameAnalytics setEnabledInfoLog:flag];
}

void GameAnalyticsCpp::setEnabledVerboseLog(bool flag) {
    [GameAnalytics setEnabledVerboseLog:flag];
}

void GameAnalyticsCpp::setEnabledManualSessionHandling(bool flag) {
    [GameAnalytics setEnabledManualSessionHandling:flag];
}

void GameAnalyticsCpp::setEnabledEventSubmission(bool flag) {
    [GameAnalytics setEnabledEventSubmission:flag];
}

void GameAnalyticsCpp::setEnabledErrorReporting(bool flag) {
    [GameAnalytics setEnabledErrorReporting:flag];
}

void GameAnalyticsCpp::setCustomDimension01(const char *dimension) {
    NSString *dimensionString = !isStringNullOrEmpty(dimension) ? [NSString stringWithUTF8String:dimension] : nil;
    [GameAnalytics setCustomDimension01:dimensionString];
}

void GameAnalyticsCpp::setCustomDimension02(const char *dimension) {
    NSString *dimensionString = !isStringNullOrEmpty(dimension) ? [NSString stringWithUTF8String:dimension] : nil;
    [GameAnalytics setCustomDimension02:dimensionString];
}

void GameAnalyticsCpp::setCustomDimension03(const char *dimension) {
    NSString *dimensionString = !isStringNullOrEmpty(dimension) ? [NSString stringWithUTF8String:dimension] : nil;
    [GameAnalytics setCustomDimension03:dimensionString];
}

void GameAnalyticsCpp::setGlobalCustomEventFields(const char *fields) {
    NSString *fieldsString = fields != NULL ? [NSString stringWithUTF8String:fields] : nil;
    NSDictionary *fields_dict = nil;
    if (fieldsString) {
        fields_dict = [NSJSONSerialization JSONObjectWithData:[fieldsString dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:nil];
    }
    [GameAnalytics setGlobalCustomEventFields:fields_dict];
}

void GameAnalyticsCpp::startSession() {
    [GameAnalytics startSession];
}

void GameAnalyticsCpp::endSession() {
    [GameAnalytics endSession];
}

const String GameAnalyticsCpp::getRemoteConfigsValueAsString(const char *key) {
    NSString *keyString = key != NULL ? [NSString stringWithUTF8String:key] : nil;
    NSString *returnValue = [GameAnalytics getRemoteConfigsValueAsString:keyString];

    if(returnValue != nil)
    {
        return String([returnValue UTF8String]);
    }
    return String();
}

const String GameAnalyticsCpp::getRemoteConfigsValueAsString(const char *key, const char *defaultValue) {
    NSString *keyString = key != NULL ? [NSString stringWithUTF8String:key] : nil;
    NSString *defaultValueString = key != NULL ? [NSString stringWithUTF8String:defaultValue] : nil;
    NSString *returnValue = [GameAnalytics getRemoteConfigsValueAsString:keyString defaultValue:defaultValueString];

    if(returnValue != nil)
    {
        return String([returnValue UTF8String]);
    }
    return String();
}

bool GameAnalyticsCpp::isRemoteConfigsReady() {
    return [GameAnalytics isRemoteConfigsReady] ? true : false;
}

const String GameAnalyticsCpp::getRemoteConfigsContentAsString() {
    NSString *returnValue = [GameAnalytics getRemoteConfigsContentAsString];

    if(returnValue != nil)
    {
        return String([returnValue UTF8String]);
    }
    return String();
}
