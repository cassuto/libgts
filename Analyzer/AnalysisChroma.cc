#include <cmath>
#include "IIR-Filter.h"
#include "AnalysisChroma.h"

AnalysisChroma::AnalysisChroma(int sampleSize, int sampleRate)
	: m_sampleSize(sampleSize),
	  m_sampleRate(sampleRate)
{
	makeNoteFreqTable();
	makeFFTWindow(sampleSize);
	makeBuffer(sampleSize);
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

void AnalysisChroma::makeBuffer(int size)
{
	// make sample buffer
	m_buffer.resize(size);
	m_dsBuffer.resize(size / 4);
	// make magnitude spectrum
	m_spectrum.resize((size/2)+1);
	// make chroma vector
	m_chromaVector.resize(12);
	std::fill(m_chromaVector.begin(), m_chromaVector.end(), 0.0);

}

/**
 * @brief Downsample Fs to Fs/factor
 */
void AnalysisChroma::downSample(const std::vector<double> &samples, int factor)
{
	size_t size = samples.size();
	std::vector<double> output (size);

	static const float a[3] = {0.0f, -0.0000, 0.1716};
	static const float b[3] = {0.2929, 0.5858, 0.2929};
	IIR_Filter_2ord filter(a,b);
	filter.apply(samples, output, size);

	for (int i = 0; i < size / factor; i++) {
		m_dsBuffer[i] = output[i * factor];
	}
}

int AnalysisChroma::process(double *samples)
{
	return 1;
}
