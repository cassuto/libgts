#include "com_libgts_JNI.h"
#include "AnalysisChroma.h"
#include "ChordClassifier.h"

static const char *notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
static int root;
static int quality;
static int intervals;

static jstring getJstring(JNIEnv* env, const char* str) {
    return env->NewStringUTF(str);
}

static double* short2DoubleArray(short* in, size_t len, bool scale) {
    const double maxShort = 32767.0;
    double* result = new double[len * sizeof(double))];
    double* curOut = result;
    for (size_t i = 0; i < len; i++) {
        *curOut = *in;
        if (scale)
            *curOut /= maxShort;
        curOut++;
        in++;
    }
    return result;
}


JNIEXPORT jboolean JNICALL Java_com_libgts_JNI_analysisAudioClip(JNIEnv *env, jobject obj, jbyteArray buf, jint sampleSize)
{
    jbyte *bytes = env->GetByteArrayElements(buf, 0);
    jsize len = env->GetArrayLength(buf);
    double *samples = short2DoubleArray((short *)bytes, (size_t)sampleSize, 1.0);
	const int sampleRate = 44100;
    
    AnalysisChroma c(sampleSize, sampleRate);

    int retval = c.process(samples);
    if (!retval)
    {
        const double *chroma = c.chromaVector();

        ChordClassifier classifier;
        classifier.classify(chroma);

        root = classifier.root();
        quality = classifier.quality();
        intervals = classifier.intervals();
    }
    
    delete [] samples;
    
    return retval==0 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jint JNICALL Java_com_libgts_JNI_getRoot(JNIEnv *env, jobject obj)
{
    return root;
}
JNIEXPORT jstring JNICALL Java_com_libgts_JNI_getRootName(JNIEnv *env, jobject obj)
{
    return getJstring(env, notes[root]);
}

JNIEXPORT jint JNICALL Java_com_libgts_JNI_getQuality(JNIEnv *, jobject)
{
    return quality;
}

JNIEXPORT jstring JNICALL Java_com_libgts_JNI_getQualityName(JNIEnv *env, jobject obj)
{
    return getJstring(env, ChordLibrary::qualityName[quality]);
}

JNIEXPORT jint JNICALL Java_com_libgts_JNI_getInterval(JNIEnv *, jobject)
{
    return intervals;
}
