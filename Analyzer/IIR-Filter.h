#ifndef IIR_FILTER_H_
#define IIR_FILTER_H_

#include <vector>

class IIR_Filter_2ord
{
public:
	IIR_Filter_2ord(const double a[3], const double b[3]);
	void apply(const std::vector<double> &samples, std::vector<double> &output, int size);
protected:
	double m_b[3],m_a[3];
};

#endif // IIR_FILTER_H_
