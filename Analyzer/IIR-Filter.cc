#include "IIR-Filter.h"

/*
 * 2-order IIR Filter
 */
IIR_Filter_2ord::IIR_Filter_2ord(const double a[3], const double b[3])
{
	// setup coefficients
	for(int i=0;i<=2;++i) {
		m_b[i] = b[i];
	}
	for(int i=1;i<=2;++i) {
		m_a[i] = a[i];
	}
}

void IIR_Filter_2ord::apply(const std::vector<double> &samples, std::vector<double> &output, int size)
{
	double x_1=0.0f,x_2=0.0f,y_1=0.0f,y_2=0.0f;

	for (int i = 0; i < size; i++) {
		output[i] = m_b[0]*samples[i] + m_b[1]*x_1 + m_b[2]*x_2 - m_a[1]*y_1 - m_a[2]*y_2;

		// delay
		x_2 = x_1; x_1 = samples[i];
		y_2 = y_1; y_1 = output[i];
	}
}
