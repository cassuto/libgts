#include <string>
#include <cstdio>
#include "AnalysisChroma.h"

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
	std::vector<double> buffer;

	for (int s = 0; s < num_smpls; s += frameSize) {
		int len = std::min(int(num_smpls - s), frameSize);
		AnalysisChroma c(len, sampleRate);

		buffer.assign(smpl+s, smpl+s+len);
		int rc = c.process(buffer);
		if (!rc)
		{
			const std::vector<double> &chroma = c.chromaVector();

			for (size_t i = 0; i < chroma.size(); ++i) {
				printf("%lf ", chroma[i]);
			}
			printf("\n");
		}
	}
}
