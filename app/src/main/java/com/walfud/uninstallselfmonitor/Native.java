package com.walfud.uninstallselfmonitor;

/**
 * Created by walfud on 7/30/15.
 */
public class Native {

    static {
        System.loadLibrary("app");
    }

    public static native void init();

}
