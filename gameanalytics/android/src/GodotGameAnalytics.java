package org.godotengine.godot;

import android.app.Activity;
import com.gameanalytics.sdk.GameAnalytics;
import com.gameanalytics.sdk.GAResourceFlowType;
import com.gameanalytics.sdk.GAProgressionStatus;
import com.gameanalytics.sdk.GAErrorSeverity;
import com.gameanalytics.sdk.GAAdAction;
import com.gameanalytics.sdk.GAAdType;
import com.gameanalytics.sdk.GAAdError;
import java.util.Hashtable;
import android.util.Log;
import java.util.Set;

public class GodotGameAnalytics extends Godot.SingletonBase
{
    private Activity activity = null;
    private static final String VERSION = "godot 2.4.0";

    static public Godot.SingletonBase initialize(Activity activity)
    {
        return new GodotGameAnalytics(activity);
    }

    public GodotGameAnalytics(Activity activity)
    {
        this.activity = activity;
        registerClass("GameAnalytics", new String[]
        {
            "configureAvailableCustomDimensions01",
            "configureAvailableCustomDimensions02",
            "configureAvailableCustomDimensions03",
            "configureAvailableResourceCurrencies",
            "configureAvailableResourceItemTypes",
            "configureBuild",
            "configureAutoDetectAppVersion",
            "configureUserId",
            "init",
            "addBusinessEvent",
            "addResourceEvent",
            "addProgressionEvent",
            "addDesignEvent",
            "addErrorEvent",
            "addAdEvent",
            "setEnabledInfoLog",
            "setEnabledVerboseLog",
            "setEnabledManualSessionHandling",
            "setEnabledErrorReporting",
            "setEnabledEventSubmission",
            "setCustomDimension01",
            "setCustomDimension02",
            "setCustomDimension03",
            "setGlobalCustomEventFields",
            "getRemoteConfigsValueAsString",
            "isRemoteConfigsReady",
            "getRemoteConfigsContentAsString",
            "startSession",
            "endSession"
        });
    }

    public void configureAvailableCustomDimensions01(String[] customDimensions)
    {
        GameAnalytics.configureAvailableCustomDimensions01(customDimensions);
    }

    public void configureAvailableCustomDimensions02(String[] customDimensions)
    {
        GameAnalytics.configureAvailableCustomDimensions02(customDimensions);
    }

    public void configureAvailableCustomDimensions03(String[] customDimensions)
    {
        GameAnalytics.configureAvailableCustomDimensions03(customDimensions);
    }

    public void configureAvailableResourceCurrencies(String[] resourceCurrencies)
    {
        GameAnalytics.configureAvailableResourceCurrencies(resourceCurrencies);
    }

    public void configureAvailableResourceItemTypes(String[] resourceItemTypes)
    {
        GameAnalytics.configureAvailableResourceItemTypes(resourceItemTypes);
    }

    public void configureBuild(String build)
    {
        GameAnalytics.configureBuild(build);
    }

    public void configureAutoDetectAppVersion(boolean flag)
    {
        GameAnalytics.configureAutoDetectAppVersion(flag);
    }

    public void configureUserId(String uId)
    {
        GameAnalytics.configureUserId(uId);
    }

    public void init(String gameKey, String secretKey)
    {
        GameAnalytics.configureSdkGameEngineVersion(VERSION);
        GameAnalytics.initialize(this.activity, gameKey, secretKey);
    }

    public void addBusinessEvent(Dictionary options)
    {
        String currency = "";
        int amount = 0;
        String itemType = "";
        String itemId = "";
        String cartType = "";
        String receipt = "";
        String store = "";
        String signature = "";
        String fields = "";
        boolean mergeFields = false;

        if(options != null)
        {
            Set<String> keys = options.keySet();
            for(String key : keys)
            {
                if(key.equals("currency"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        currency = value + "";
                    }
                }
                else if(key.equals("amount"))
                {
                    Object value = options.get(key);
                    if(value instanceof Number)
                    {
                        Number n = (Number)value;
                        amount = n.intValue();
                    }
                    else
                    {
                        Log.d("GameAnalytics", "'" + key + "' value has the wrong type: " + value.getClass());
                    }
                }
                else if(key.equals("itemType"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        itemType = value + "";
                    }
                }
                else if(key.equals("itemId"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        itemId = value + "";
                    }
                }
                else if(key.equals("cartType"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        cartType = value + "";
                    }
                }
                else if(key.equals("receipt"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        receipt = value + "";
                        store = "google_play";
                    }
                }
                else if(key.equals("signature"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        signature = value + "";
                    }
                }
                else if (key.equals("customFields"))
                {
                    Object value = options.get(key);
                    if (value != null)
                    {
                        fields = value + "";
                    }
                }
                else if (key.equals("mergeFields")) {
                    Object value = options.get(key);
                    if (value instanceof Boolean) {
                        Boolean b = (Boolean) value;
                        mergeFields = b.booleanValue();
                    }
                }
            }
        }
        GameAnalytics.addBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, store, signature, fields,
                mergeFields);
    }

    public void addResourceEvent(Dictionary options)
    {
        GAResourceFlowType flowType = GAResourceFlowType.Undefined;
        String currency = "";
        float amount = 0;
        String itemType = "";
        String itemId = "";
        String fields = "";
        boolean mergeFields = false;

        if(options != null)
        {
            Set<String> keys = options.keySet();
            for(String key : keys)
            {
                if(key.equals("flowType"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        if(value.equals("Source"))
                        {
                            flowType = GAResourceFlowType.Source;
                        }
                        else if(value.equals("Sink"))
                        {
                            flowType = GAResourceFlowType.Sink;
                        }
                    }
                }
                else if(key.equals("currency"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        currency = value + "";
                    }
                }
                else if(key.equals("amount"))
                {
                    Object value = options.get(key);
                    if(value instanceof Number)
                    {
                        Number n = (Number)value;
                        amount = n.floatValue();
                    }
                    else
                    {
                        Log.d("GameAnalytics", "'" + key + "' value has the wrong type: " + value.getClass());
                    }
                }
                else if(key.equals("itemType"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        itemType = value + "";
                    }
                }
                else if(key.equals("itemId"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        itemId = value + "";
                    }
                }
                else if (key.equals("customFields"))
                {
                    Object value = options.get(key);
                    if (value != null)
                    {
                        fields = value + "";
                    }
                }
                else if (key.equals("mergeFields")) {
                    Object value = options.get(key);
                    if (value instanceof Boolean) {
                        Boolean b = (Boolean) value;
                        mergeFields = b.booleanValue();
                    }
                }
            }
        }

        GameAnalytics.addResourceEvent(flowType.ordinal(), currency, amount, itemType, itemId, fields, mergeFields);
    }

    public void addProgressionEvent(Dictionary options)
    {
        GAProgressionStatus progressionStatus = GAProgressionStatus.Undefined;
        String progression01 = "";
        String progression02 = "";
        String progression03 = "";
        Double score = null;
        String fields = "";
        boolean mergeFields = false;

        if(options != null)
        {
            Set<String> keys = options.keySet();
            for(String key : keys)
            {
                if(key.equals("progressionStatus"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        if(value.equals("Start"))
                        {
                            progressionStatus = GAProgressionStatus.Start;
                        }
                        else if(value.equals("Complete"))
                        {
                            progressionStatus = GAProgressionStatus.Complete;
                        }
                        else if(value.equals("Fail"))
                        {
                            progressionStatus = GAProgressionStatus.Fail;
                        }
                    }
                }
                else if(key.equals("progression01"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        progression01 = value + "";
                    }
                }
                else if(key.equals("progression02"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        progression02 = value + "";
                    }
                }
                else if(key.equals("progression03"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        progression03 = value + "";
                    }
                }
                else if(key.equals("score"))
                {
                    Object value = options.get(key);
                    if(value instanceof Number)
                    {
                        Number n = (Number)value;
                        score = n.doubleValue();
                    }
                    else
                    {
                        Log.d("GameAnalytics", "'" + key + "' value has the wrong type: " + value.getClass());
                    }
                }
                else if (key.equals("customFields"))
                {
                    Object value = options.get(key);
                    if (value != null)
                    {
                        fields = value + "";
                    }
                }
                else if (key.equals("mergeFields")) {
                    Object value = options.get(key);
                    if (value instanceof Boolean) {
                        Boolean b = (Boolean) value;
                        mergeFields = b.booleanValue();
                    }
                }
            }
        }

        if(score != null)
        {
            GameAnalytics.addProgressionEvent(progressionStatus.ordinal(), progression01, progression02, progression03, score.doubleValue(), fields,
                    mergeFields);
        }
        else
        {
            GameAnalytics.addProgressionEvent(progressionStatus.ordinal(), progression01, progression02, progression03,
                    fields, mergeFields);
        }
    }

    public void addDesignEvent(Dictionary options)
    {
        String eventId = "";
        Double value = null;
        String fields = "";
        boolean mergeFields = false;

        if(options != null)
        {
            Set<String> keys = options.keySet();
            for(String key : keys)
            {
                if(key.equals("eventId"))
                {
                    Object v = options.get(key);
                    if(v != null)
                    {
                        eventId = v + "";
                    }
                }
                else if(key.equals("value"))
                {
                    Object v = options.get(key);
                    if(v instanceof Number)
                    {
                        Number n = (Number)v;
                        value = n.doubleValue();
                    }
                    else
                    {
                        Log.d("GameAnalytics", "'" + key + "' value has the wrong type: " + value.getClass());
                    }
                }
                else if (key.equals("customFields"))
                {
                    Object v = options.get(key);
                    if (v != null)
                    {
                        fields = v + "";
                    }
                }
                else if (key.equals("mergeFields")) {
                    Object v = options.get(key);
                    if (v instanceof Boolean) {
                        Boolean b = (Boolean) v;
                        mergeFields = b.booleanValue();
                    }
                }
            }
        }

        if(value != null)
        {
            GameAnalytics.addDesignEvent(eventId, value.doubleValue(), fields, mergeFields);
        }
        else
        {
            GameAnalytics.addDesignEvent(eventId, fields, mergeFields);
        }
    }

    public void addErrorEvent(Dictionary options)
    {
        GAErrorSeverity severity = GAErrorSeverity.Undefined;
        String message = "";
        String fields = "";
        boolean mergeFields = false;

        if(options != null)
        {
            Set<String> keys = options.keySet();
            for(String key : keys)
            {
                if(key.equals("severity"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        if(value.equals("Debug"))
                        {
                            severity = GAErrorSeverity.Debug;
                        }
                        else if(value.equals("Info"))
                        {
                            severity = GAErrorSeverity.Info;
                        }
                        else if(value.equals("Warning"))
                        {
                            severity = GAErrorSeverity.Warning;
                        }
                        else if(value.equals("Error"))
                        {
                            severity = GAErrorSeverity.Error;
                        }
                        else if(value.equals("Critical"))
                        {
                            severity = GAErrorSeverity.Critical;
                        }
                    }
                }
                else if(key.equals("message"))
                {
                    Object value = options.get(key);
                    if(value != null)
                    {
                        message = value + "";
                    }
                }
                else if (key.equals("customFields"))
                {
                    Object value = options.get(key);
                    if (value != null)
                    {
                        fields = value + "";
                    }
                }
                else if (key.equals("mergeFields")) {
                    Object v = options.get(key);
                    if (v instanceof Boolean) {
                        Boolean b = (Boolean) value;
                        mergeFields = b.booleanValue();
                    }
                }
            }
        }

        GameAnalytics.addErrorEvent(severity.ordinal(), message, fields, mergeFields);
    }

    public void addAdEvent(Dictionary options) {
        GAAdAction adAction = GAAdAction.Undefined;
        GAAdType adType = GAAdType.Undefined;
        GAAdError noAdReason = GAAdError.Undefined;
        String adSdkName = "";
        String adPlacement = "";
        boolean sendDuration = false;
        Long duration = null;
        String fields = "";
        boolean mergeFields = false;

        if (options != null) {
            Set<String> keys = options.keySet();
            for (String key : keys) {
                if (key.equals("adAction")) {
                    Object value = options.get(key);
                    if (value != null) {
                        if (value.equals("Clicked")) {
                            adAction = GAAdAction.Clicked;
                        } else if (value.equals("Show")) {
                            adAction = GAAdAction.Show;
                        } else if (value.equals("FailedShow")) {
                            adAction = GAAdAction.FailedShow;
                        } else if (value.equals("RewardReceived")) {
                            adAction = GAAdAction.RewardReceived;
                        }
                    }
                } else if (key.equals("adType")) {
                    Object value = options.get(key);
                    if (value != null) {
                        if (value.equals("Video")) {
                            adType = GAAdType.Video;
                        } else if (value.equals("RewardedVideo")) {
                            adType = GAAdType.RewardedVideo;
                        } else if (value.equals("Playable")) {
                            adType = GAAdType.Playable;
                        } else if (value.equals("Interstitial")) {
                            adType = GAAdType.Interstitial;
                        } else if (value.equals("OfferWall")) {
                            adType = GAAdType.OfferWall;
                        } else if (value.equals("Banner")) {
                            adType = GAAdType.Banner;
                        }
                    }
                } else if (key.equals("adSdkName")) {
                    Object value = options.get(key);
                    if (value != null) {
                        adSdkName = value + "";
                    }
                } else if (key.equals("adPlacement")) {
                    Object value = options.get(key);
                    if (value != null) {
                        adPlacement = value + "";
                    }
                } else if (key.equals("duration")) {
                    Object v = options.get(key);
                    if (v instanceof Number) {
                        Number n = (Number) v;
                        duration = n.longValue();
                        sendDuration = true;
                    } else {
                        Log.d("GameAnalytics", "'" + key + "' value has the wrong type: " + v.getClass());
                    }
                } else if (key.equals("noAdReason")) {
                    Object value = options.get(key);
                    if (value != null) {
                        if (value.equals("Unknown")) {
                            noAdReason = GAAdError.Unknown;
                        } else if (value.equals("Offline")) {
                            noAdReason = GAAdError.Offline;
                        } else if (value.equals("NoFill")) {
                            noAdReason = GAAdError.NoFill;
                        } else if (value.equals("InternalError")) {
                            noAdReason = GAAdError.InternalError;
                        } else if (value.equals("InvalidRequest")) {
                            noAdReason = GAAdError.InvalidRequest;
                        } else if (value.equals("UnableToPrecache")) {
                            noAdReason = GAAdError.UnableToPrecache;
                        }
                    }
                } else if (key.equals("customFields")) {
                    Object value = options.get(key);
                    if (value != null) {
                        fields = value + "";
                    }
                } else if (key.equals("mergeFields")) {
                    Object value = options.get(key);
                    if (value instanceof Boolean) {
                        Boolean b = (Boolean) value;
                        mergeFields = b.booleanValue();
                    }
                }
            }
        }

        if (sendDuration) {
            GameAnalytics.addAdEvent(adAction.ordinal(), adType.ordinal(), adSdkName, adPlacement, duration, fields,
                    mergeFields);
        } else {
            GameAnalytics.addAdEvent(adAction.ordinal(), adType.ordinal(), adSdkName, adPlacement, noAdReason.ordinal(),
                    fields, mergeFields);
        }
    }

    public void setEnabledInfoLog(boolean flag)
    {
        GameAnalytics.setEnabledInfoLog(flag);
    }

    public void setEnabledVerboseLog(boolean flag)
    {
        GameAnalytics.setEnabledVerboseLog(flag);
    }

    public void setEnabledManualSessionHandling(boolean flag)
    {
        GameAnalytics.setEnabledManualSessionHandling(flag);
    }

    public void setEnabledErrorReporting(boolean flag)
    {
        GameAnalytics.setEnabledErrorReporting(flag);
    }

    public void setEnabledEventSubmission(boolean flag)
    {
        GameAnalytics.setEnabledEventSubmission(flag);
    }

    public void setCustomDimension01(String dimension)
    {
        GameAnalytics.setCustomDimension01(dimension);
    }

    public void setCustomDimension02(String dimension)
    {
        GameAnalytics.setCustomDimension02(dimension);
    }

    public void setCustomDimension03(String dimension)
    {
        GameAnalytics.setCustomDimension03(dimension);
    }

    public void setGlobalCustomEventFields(String customFields)
    {
        GameAnalytics.setGlobalCustomEventFields(customFields);
    }

    public String getRemoteConfigsValueAsString(Dictionary options)
    {
        String key = "";
        String defaultValue = null;

        if(options != null)
        {
            Set<String> keys = options.keySet();
            for(String k : keys)
            {
                if(k.equals("key"))
                {
                    Object value = options.get(k);
                    if(value != null)
                    {
                        key = value + "";
                    }
                }
                else if(k.equals("defaultValue"))
                {
                    Object value = options.get(k);
                    if(value != null)
                    {
                        defaultValue = value + "";
                    }
                }
            }
        }

        if(defaultValue != null)
        {
            return GameAnalytics.getRemoteConfigsValueAsString(key, defaultValue);
        }
        else
        {
            return GameAnalytics.getRemoteConfigsValueAsString(key);
        }
    }

    public boolean isRemoteConfigsReady()
    {
        return GameAnalytics.isRemoteConfigsReady();
    }

    public String getRemoteConfigsContentAsString()
    {
        return GameAnalytics.getRemoteConfigsContentAsString();
    }

    public void startSession()
    {
        GameAnalytics.startSession();
    }

    public void endSession()
    {
        GameAnalytics.endSession();
    }
}
