#ifndef ANALYSISCHROMA_H_
#define ANALYSISCHROMA_H_

#include <vector>

class AnalysisChroma
{
public:
    AnalysisChroma(int sampleSize, int sampleRate);
    ~AnalysisChroma();
    
    int process(double *samples);

private:
    void makeNoteFreqTable();
    void makeFFTWindow(int size);
    void makeBuffer(int size);
    void downSample(const std::vector<double> &samples, int factor);

protected:
    int m_sampleSize, m_sampleRate;
    double m_noteFreqs[12];
    std::vector<double> m_fftWindow;
    std::vector<double> m_buffer, m_dsBuffer;
    std::vector<double> m_spectrum;
    std::vector<double> m_chromaVector;
};

#endif // ANALYSISCHROMA_H_
