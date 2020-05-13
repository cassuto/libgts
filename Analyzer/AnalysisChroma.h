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

protected:
    int m_sampleSize, m_sampleRate;
    double m_noteFreqs[12];
    std::vector<double> m_fftWindow;
};

#endif // ANALYSISCHROMA_H_
