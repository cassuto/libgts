#ifndef CHORDCLASSIFIER_H_
#define CHORDCLASSIFIER_H_

#include <vector>
#include "ChordLibrary.h"

#define MAX_N_CHORDS 256

class ChordClassifier
{
public:
	ChordClassifier();

	void classify(std::vector<double> chromaVector);

private:
	void makeBitmaskMatrix();
	double weightChord(const std::vector<double> &chroma,  double bitmask[], double biasToUse, double N);

protected:
	int m_chordCount;
	double m_biasBeta;
	double m_bitmask[MAX_N_CHORDS][12];
	double m_weight[MAX_N_CHORDS];
	int m_root;
	int m_quality;
	int m_intervals;
};

#endif // CHORDCLASSIFIER_H_
