#include <cmath>
#include <cstring>
#include <cassert>
#include <algorithm>
#include "ChordLibrary.h"
#include "ChordClassifier.h"

ChordClassifier::ChordClassifier()
	: m_biasBeta(1.06) // P87 Section 2.4
{
	m_chordCount = ChordLibrary::chordEntryCount * 12;
	assert(m_chordCount <= MAX_N_CHORDS);

	makeBitmaskMatrix();
}

void ChordClassifier::makeBitmaskMatrix()
{
	std::memset(m_bitmask, sizeof m_bitmask, 0);

	int p = 0;
	for (int n = 0; n < ChordLibrary::chordEntryCount; n++) {
		const ChordLibrary::ChordBase *chd = ChordLibrary::chordEntry[n];
		for (int i = 0; i < 12; i++) {
			switch (chd->type()) {
			case 3: {
				const ChordLibrary::Chord3 *chd3 = static_cast<const ChordLibrary::Chord3 *>(chd);
				m_bitmask[p][(i + chd3->root) % 12] = 1;
				m_bitmask[p][(i + chd3->third) % 12] = 1;
				m_bitmask[p][(i + chd3->fifth) % 12] = 1;
				p++;
				break;
			}
			case 7: {
				const ChordLibrary::Chord7 *chd7 = static_cast<const ChordLibrary::Chord7 *>(chd);
				m_bitmask[p][(i + chd7->root) % 12] = 1;
				m_bitmask[p][(i + chd7->third) % 12] = 1;
				m_bitmask[p][(i + chd7->fifth) % 12] = 1;
				m_bitmask[p][(i + chd7->seventh) % 12] = 1;
				p++;
				break;
			}
			default:
				assert(0);
			}
		}
	}

	assert(p == m_chordCount);
}

double ChordClassifier::weightChord(const std::vector<double> &chroma, double bitmask[], double bias, double N)
{
	double sum = 0;
	for (int i = 0; i < 12; i++) {
		sum = sum + ((1 - bitmask[i]) * (chroma[i]*chroma[i]));
	}
	return std::sqrt (sum) / ((12 - N) * bias); // Formula (3)
}

void ChordClassifier::classify(std::vector<double> chromaVector)
{
	// remove some of the 5th note energy from chroma vector
	for (int i = 0; i < 12; i++) {
		int fifth = (i+7) % 12;
		chromaVector[fifth] -= 0.1 * chromaVector[i];
		chromaVector[fifth] = std::max(0.0, chromaVector[fifth]);
	}

	// compute weights of each chord
	for (int p = 0; p < m_chordCount; ++p) {
		const ChordLibrary::ChordBase *chd = ChordLibrary::chordEntry[p];
		double bias = chd->ghostNoteFixup ? m_biasBeta : 1.0;
		switch (chd->type()) {
		case 3:
			m_weight[p] = weightChord(chromaVector, m_bitmask[p], bias, 3);
			break;
		case 7:
			m_weight[p] = weightChord(chromaVector, m_bitmask[p], bias, 4);
			break;
		default:
			assert(0);
		}
	}

	// select a chord that minimized residual energy
	int ans = 0;
	double minWeight = 1e308;
	for(int i = 0;i < m_chordCount; ++i) {
		if (m_weight[i] < minWeight) {
			minWeight = m_weight[i];
			ans = i;
		}
	}

	// read out chord info
	m_root = ans % 12;
	m_quality = ChordLibrary::chordEntry[ans]->quality;
	m_intervals = ChordLibrary::chordEntry[ans]->intervals;
}
