#include <cstring>
#include <cassert>
#include "ChordLibrary.h"
#include "ChordClassifier.h"

ChordClassifier::ChordClassifier()
{
	makeBitmask();
}

void ChordClassifier::makeBitmask()
{
	const double v1 = 1, v2 = 1, v3 = 1;

	std::memset(m_bitmask, sizeof m_bitmask, 0);

	int p = 0;
	for (int n = 0; n < ChordLibrary::chordsCount; ++n) {
		const ChordLibrary::ChordBase *chd = ChordLibrary::chords[n];
		for (int i = 0; i < 12; i++) {
			switch (chd->type()) {
			case 3: {
				const ChordLibrary::Chord3 *chd3 = static_cast<const ChordLibrary::Chord3 *>(chd);
				m_bitmask[p][(i + chd3->root) % 12] = v1;
				m_bitmask[p][(i + chd3->third) % 12] = v2;
				m_bitmask[p][(i + chd3->fifth) % 12] = v3;
				p++;
				break;
			}
			case 7: {
				const ChordLibrary::Chord7 *chd7 = static_cast<const ChordLibrary::Chord7 *>(chd);
				m_bitmask[p][(i + chd7->root) % 12] = v1;
				m_bitmask[p][(i + chd7->third) % 12] = v2;
				m_bitmask[p][(i + chd7->fifth) % 12] = v3;
				m_bitmask[p][(i + chd7->seventh) % 12] = v3;
				p++;
				break;
			}
			default:
				assert(0);
			}
		}
	}
}
