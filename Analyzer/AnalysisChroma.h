#ifndef ANALYSISCHROMA_H_
#define ANALYSISCHROMA_H_

class AnalysisChroma
{
public:
    AnalysisChroma();
    ~AnalysisChroma();
    
    int process(double *samples, int size, int sampleRate);

private:
    void makeNoteFreqTable();

protected:
    double m_noteFreqs[12];
};

#endif // ANALYSISCHROMA_H_
