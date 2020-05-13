#include <cmath>
#include "AnalysisChroma.h"

AnalysisChroma::AnalysisChroma(int sampleSize, int sampleRate)
	: m_sampleSize(sampleSize),
	  m_sampleRate(sampleRate)
{
	makeNoteFreqTable();
	makeFFTWindow(sampleSize);
}
AnalysisChroma::~AnalysisChroma()
{

}

void AnalysisChroma::makeNoteFreqTable()
{
	const double f0 = 130.81278265; // Hz
	// Fp = F0 * 2^(p/12) where p is the note in 12 semitones
	for (int i = 0; i < 12; i++) {
		m_noteFreqs[i] = f0 * std::pow(2,double(i) / 12);
	}
}

void AnalysisChroma::makeFFTWindow(int size)
{
	m_fftWindow.resize (size);
	// Hamming window
	for (int n = 0; n < size;n++) {
		m_fftWindow[n] = 0.54 - 0.46 * cos(2*M_PI * (double(n) / double(size)));
	}
}

int AnalysisChroma::process(double *samples)
{
	return 1;
}
