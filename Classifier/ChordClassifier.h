#ifndef CHORDCLASSIFIER_H_
#define CHORDCLASSIFIER_H_

class ChordClassifier
{
public:
	ChordClassifier();

private:
	void makeBitmask();

protected:
	double m_bitmask[108][12];
};

#endif // CHORDCLASSIFIER_H_
