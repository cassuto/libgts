#ifndef ANALYSISCHROMA_H_
#define ANALYSISCHROMA_H_

#include <vector>
#include <cmath>
#include "kiss_fft.h"

class AnalysisChroma
{
public:
    AnalysisChroma(int sampleSize=8192, int sampleRate=44100);
    ~AnalysisChroma();
    
    /**
     * @brief Input and process samples
     * @param samples	Target samples
     * @return status code.
     */
    int process(const double samples[]);

    inline const double *chromaVector() const {
    	return m_chromaVector;
    }

private:
    void makeNoteFreqTable();
    void makeFFTWindow(int size);
    void makeBuffer(int size);
    const std::vector<double> &downSample(const double input[], int size, int factor);

    inline double round (double val) {
        return std::floor(val + 0.5);
    }

protected:
    int m_windowSize, m_sampleRate;
    double m_noteFreqs[12];
    std::vector<double> m_fftWindow;
    std::vector<double> m_dsBuffer;
    std::vector<double> m_spectrum;
    double m_chromaVector[12];

    kiss_fft_cfg m_fftCfg;
	kiss_fft_cpx* m_fftIn;
	kiss_fft_cpx* m_fftOut;
};

#endif // ANALYSISCHROMA_H_
