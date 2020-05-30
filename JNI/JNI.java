package com.libgts;

public class JNI {
    public native boolean analysisAudioClip(byte []buf, int sampleSize);
	static{
        System.loadLibrary("gts");
    }
}
