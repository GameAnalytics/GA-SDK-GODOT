package com.gameanalytics.godotgameanalytics;

import android.util.Log;

import com.gameanalytics.sdk.GameAnalytics;
import com.gameanalytics.sdk.IRemoteConfigsListener;

public class NativeRemoteConfigsListener implements IRemoteConfigsListener
{
    private native void onRemoteConfigsUpdatedNative(String remoteConfigs);

    @Override
    public void onRemoteConfigsUpdated()
    {
        try
        {
            // the configs are read here rather than from the native callback: this runs on the
            // sdk's own thread, which the vm owns, and where the native jni helper must not
            // attach and later detach
            onRemoteConfigsUpdatedNative(GameAnalytics.getRemoteConfigsContentAsString());
        }
        catch(Throwable e)
        {
            Log.e("GameAnalytics", "Failed to find the native remote configs listener implementation!");
        }
    }
}
