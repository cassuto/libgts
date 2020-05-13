#ifndef ANALYSISCHROMA_H_
#define ANALYSISCHROMA_H_

#include <vector>
#include "kiss_fft.h"

class AnalysisChroma
{
public:
    AnalysisChroma(int sampleSize=8192, int sampleRate=44100, int step=4096);
    ~AnalysisChroma();
    
    /**
     * @brief Input and process samples
     * @param samples	Target samples
     * @return status code.
     */
    int process(const std::vector<double> &samples);

private:
    void makeNoteFreqTable();
    void makeFFTWindow(int size);
    void makeBuffer(int size);
    const std::vector<double> &downSample(const std::vector<double> &samples, int factor);

protected:
    int m_bufferSize, m_sampleRate;
    size_t m_samplesRecv;
    size_t m_step;
    double m_noteFreqs[12];
    std::vector<double> m_fftWindow;
    std::vector<double> m_dsBuffer;
    std::vector<double> m_spectrum;
    std::vector<double> m_chromaVector;

    kiss_fft_cfg m_fftCfg;
	kiss_fft_cpx* m_fftIn;
	kiss_fft_cpx* m_fftOut;
};

#endif // ANALYSISCHROMA_H_
