#ifndef IIR_FILTER_H_
#define IIR_FILTER_H_

#include <vector>

class IIR_Filter_2ord
{
public:
	IIR_Filter_2ord(float a[3], float b[3]);
	void filter(const std::vector<double> &samples, std::vector<double> &output, int size);
protected:
	float m_b[3],m_a[3];
};

#endif // IIR_FILTER_H_
