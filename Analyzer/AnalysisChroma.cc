#include <cmath>
#include "AnalysisChroma.h"

AnalysisChroma::AnalysisChroma()
{
	makeNoteFreqTable();
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

int AnalysisChroma::process(double *samples, int size, int sampleRate)
{
	return 1;
}
