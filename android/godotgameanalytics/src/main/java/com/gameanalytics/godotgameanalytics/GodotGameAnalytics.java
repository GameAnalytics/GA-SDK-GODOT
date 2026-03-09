package com.gameanalytics.godotgameanalytics;

import android.app.Activity;
import android.util.Log;
import android.view.View;

import androidx.annotation.NonNull;

import org.godotengine.godot.Godot;
import org.godotengine.godot.plugin.GodotPlugin;

import com.gameanalytics.sdk.GameAnalytics;

public class GodotGameAnalytics extends GodotPlugin
{
    static {
        // we only need to grab the JNIEnv* in C++
        System.loadLibrary("GodotGameAnalytics");
    }

    public GodotGameAnalytics(Godot godot) {
        super(godot);
    }

    @Override
    public View onMainCreate(Activity activity)
    {
        setActivityNative(activity);
        return null;
    }

    @NonNull
    @Override
    public String getPluginName() {
        return "GodotGameAnalytics";
    }

    public native void setActivityNative(Activity activity);
}
