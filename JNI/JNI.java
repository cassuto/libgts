package com.libgts;

public class JNI {
    public native boolean analysisAudioClip(byte []buf, int sampleSize);
	public native int getRoot();
	public native String getRootName();
	public native int getQuality();
	public native String getQualityName();
	public native int getInterval();
	static{
        System.loadLibrary("gts");
    }
}