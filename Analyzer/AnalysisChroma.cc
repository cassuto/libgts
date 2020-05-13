#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "gts_error.h"
#include "kiss_fft.h"
#include "IIR-Filter.h"
#include "AnalysisChroma.h"

AnalysisChroma::AnalysisChroma(int bufferSize, int sampleRate)
	: m_bufferSize(bufferSize),
	  m_sampleRate(sampleRate)
{
	makeNoteFreqTable();
	makeFFTWindow(bufferSize);
	makeBuffer(bufferSize);

	// create FFT library
	m_fftIn = new kiss_fft_cpx[bufferSize];
	m_fftOut = new kiss_fft_cpx[bufferSize];
	m_fftCfg = kiss_fft_alloc(bufferSize,0,0,0);
}
AnalysisChroma::~AnalysisChroma()
{
	// destroy FFT library
	std::free (m_fftCfg);
	delete [] m_fftIn;
	delete [] m_fftOut;
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
	// W(n,¦Á ) = (1 -¦Á ) - ¦Á cos(2*PI*n/(N-1))£¬0¨Qn¨QN-1
	for (int n = 0; n < size;n++) {
		m_fftWindow[n] = 0.54 - 0.46 * cos(2*M_PI * (double(n) / double(size)));
	}
}

void AnalysisChroma::makeBuffer(int size)
{
	// make sample buffer
	m_dsBuffer.resize(size / 4);
	// make magnitude spectrum
	m_spectrum.resize((size/2)+1);
	// make chroma vector
	m_chromaVector.resize(12);
	std::fill(m_chromaVector.begin(), m_chromaVector.end(), 0.0);
}

/**
 * @brief Downsample Fs to Fs/factor
 * the result is stored in a global buffer.
 * @return reference to the global buffer.
 */
const std::vector<double> &AnalysisChroma::downSample(const std::vector<double> &samples, int factor)
{
	size_t size = samples.size();
	std::vector<double> output (size);

	static const double a[3] = {0.0f, -0.0000, 0.1716};
	static const double b[3] = {0.2929, 0.5858, 0.2929};
	IIR_Filter_2ord filter(a,b);
	filter.apply(samples, output, size);

	for (int i = 0; i < size / factor; i++) {
		m_dsBuffer[i] = output[i * factor];
	}
	return m_dsBuffer;
}

#include <cstdio>
int AnalysisChroma::process(const std::vector<double> &input)
{
	const int fs = 11025; // Hz

	if(input.size() != m_bufferSize) {
		return -E_BUFFER_SIZE;
	}
	const std::vector<double> &samples = downSample(input, m_sampleRate/fs);

	// apply hamming window
	for (int i = 0;i < m_bufferSize; i++) {
		m_fftIn[i].r = samples[i] * m_fftWindow[i];
		m_fftIn[i].i = 0.0;
	}

	//************************************************************
	// calculate magnitude spectrum
	//************************************************************

	kiss_fft(m_fftCfg, m_fftIn, m_fftOut);

	// calculate magnitude values |Fn|
	for (int i = 0; i < (m_bufferSize / 2) + 1; i++) {
		m_spectrum[i] = std::sqrt(std::pow(m_fftOut[i].r, 2) + std::pow(m_fftOut[i].i, 2));
	}

	// square root of magnitude is used to reduce the amplitude difference
	for (int i = 0; i < (m_bufferSize / 2) + 1; i++) {
		m_spectrum[i] = std::sqrt(m_spectrum[i]);
	}

	//************************************************************
	// calculate chroma vector
	//************************************************************

	// dF = Fs/L
	const double dF = double(fs) / double(m_bufferSize);

	for (int n = 0; n < 12; n++) {
		m_chromaVector[n] = 0.0;
		for (int phi = 1; phi <= 2; phi++) {
			for (int h = 1; h <= 2; h++) {
				int kc = round((m_noteFreqs[n] * phi * h) / dF); // (2)
				int k0 = kc - (2*h);
				int k1 = kc + (2*h);

				double m = 0.0;
				for (int k = k0; k < k1; k++) {
					m = std::max(m, m_spectrum[k]);
				}

				m_chromaVector[n] += m / double(h);
			}
		}
	}

	return 0;
}
