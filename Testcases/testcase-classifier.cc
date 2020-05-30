#include <string>
#include <cstdio>
#include "AnalysisChroma.h"
#include "ChordClassifier.h"

static const char *notes[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

static char *read_pcm(const char *filename, size_t *size_out)
{
    FILE *fp=fopen(filename, "rb");
    if(!fp)
        return 0;

    fseek(fp,0,SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);
    if(size_out)
        *size_out = size;

    char *buff = new char[size];
    size_t len = fread(buff,1,size,fp);
    fclose(fp);
    return buff;
}

double* short2DoubleArray(short* in, size_t len, bool scale) {
    const double maxShort = 32767.0;

    double* result = static_cast<double*>(malloc(len * sizeof(double)));
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

#define DUMP_CHROMA

int main()
{
	size_t len;
	char *buff = read_pcm("waves/g.pcm", &len);
	if(!buff) {
		perror("open input");
		return 1;
	}
	size_t num_smpls = len/2;

	const int sampleRate = 44100;
	const int frameSize = 8192;

	printf("total %d samples, frameTime = %lf\n", num_smpls, double(frameSize) / sampleRate);

	double *smpl = short2DoubleArray((short*)buff, num_smpls, 0); // LittleEndian only

#ifdef DUMP_CHROMA
	FILE *out = fopen("chroma.csv", "w");
#endif

	for (int s = 0; s < num_smpls; s += frameSize) {
		int len = std::min(int(num_smpls - s), frameSize);
		AnalysisChroma c(len, sampleRate);

		int rc = c.process(smpl+s);
		if (!rc)
		{
			const double *chroma = c.chromaVector();

			ChordClassifier classifier;
			classifier.classify(chroma);

			double ts = double(s) / sampleRate;

#ifdef DUMP_CHROMA
			fprintf(out, "%lf ", ts);
			for(int i=0;i<12;++i) {
				fprintf(out, "%lf ", chroma[i]);
			}
			fprintf(out, "\n");
#endif
			printf("%lf %s %s %d\n", ts, notes[classifier.root()], ChordLibrary::qualityName[classifier.quality()], classifier.intervals());
		}
	}

#ifdef DUMP_CHROMA
	fclose(out);
#endif
}
