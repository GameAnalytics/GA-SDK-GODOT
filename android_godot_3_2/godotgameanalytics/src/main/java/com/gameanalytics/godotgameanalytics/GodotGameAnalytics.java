package com.gameanalytics.godotgameanalytics;

import android.app.Activity;
import android.util.Log;

import com.gameanalytics.sdk.GAErrorSeverity;
import com.gameanalytics.sdk.GAProgressionStatus;
import com.gameanalytics.sdk.GAResourceFlowType;
import com.gameanalytics.sdk.GameAnalytics;

import org.godotengine.godot.Dictionary;
import org.godotengine.godot.Godot;
import org.godotengine.godot.plugin.GodotPlugin;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class GodotGameAnalytics extends GodotPlugin
{
    private Activity activity = null;
    private static final String VERSION = "godot 1.3.4";

    public GodotGameAnalytics(Godot godot)
    {
        super(godot);
        this.activity = godot.getActivity();
    }

    @Override
    public String getPluginName()
    {
        return "GameAnalytics";
    }

    @Override
    public List<String> getPluginMethods()
    {
        List<String> methods = new ArrayList<>();

        methods.add("configureAvailableCustomDimensions01");
        methods.add("configureAvailableCustomDimensions02");
        methods.add("configureAvailableCustomDimensions03");
        methods.add("configureAvailableResourceCurrencies");
        methods.add("configureAvailableResourceItemTypes");
        methods.add("configureBuild");
        methods.add("configureAutoDetectAppVersion");
        methods.add("configureUserId");
        methods.add("init");
        methods.add("addBusinessEvent");
        methods.add("addResourceEvent");
        methods.add("addProgressionEvent");
        methods.add("addDesignEvent");
        methods.add("addErrorEvent");
        methods.add("setEnabledInfoLog");
        methods.add("setEnabledVerboseLog");
        methods.add("setEnabledManualSessionHandling");
        methods.add("setEnabledErrorReporting");
        methods.add("setEnabledEventSubmission");
        methods.add("setCustomDimension01");
        methods.add("setCustomDimension02");
        methods.add("setCustomDimension03");
        methods.add("getRemoteConfigsValueAsString");
        methods.add("isRemoteConfigsReady");
        methods.add("getRemoteConfigsContentAsString");
        methods.add("startSession");
        methods.add("endSession");

        return methods;
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
            }
        }
        GameAnalytics.addBusinessEvent(currency, amount, itemType, itemId, cartType, receipt, store, signature);
    }

    public void addResourceEvent(Dictionary options)
    {
        GAResourceFlowType flowType = GAResourceFlowType.Undefined;
        String currency = "";
        float amount = 0;
        String itemType = "";
        String itemId = "";

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
            }
        }

        GameAnalytics.addResourceEvent(flowType, currency, amount, itemType, itemId);
    }

    public void addProgressionEvent(Dictionary options)
    {
        GAProgressionStatus progressionStatus = GAProgressionStatus.Undefined;
        String progression01 = "";
        String progression02 = "";
        String progression03 = "";
        Double score = null;

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
            }
        }

        if(score != null)
        {
            GameAnalytics.addProgressionEvent(progressionStatus, progression01, progression02, progression03, score.doubleValue());
        }
        else
        {
            GameAnalytics.addProgressionEvent(progressionStatus, progression01, progression02, progression03);
        }
    }

    public void addDesignEvent(Dictionary options)
    {
        String eventId = "";
        Double value = null;

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
            }
        }

        if(value != null)
        {
            GameAnalytics.addDesignEvent(eventId, value.doubleValue());
        }
        else
        {
            GameAnalytics.addDesignEvent(eventId);
        }
    }

    public void addErrorEvent(Dictionary options)
    {
        GAErrorSeverity severity = GAErrorSeverity.Undefined;
        String message = "";

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
            }
        }

        GameAnalytics.addErrorEvent(severity, message);
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
