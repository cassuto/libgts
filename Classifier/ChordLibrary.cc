#include "ChordLibrary.h"

namespace ChordLibrary
{

const ChordBase *chordEntry[] = {
	new Chord3(Chord_Maj,0, 0,4,7, true),
	new Chord3(Chord_Min,0, 0,3,7, true),
	new Chord3(Chord_Dim,0, 0,3,6, true),
	new Chord3(Chord_Aug,0, 0,4,8, true),
	new Chord3(Chord_Sus,2, 0,2,7, false), // sus2
	new Chord3(Chord_Sus,4, 0,5,7, false), // sus4
	new Chord7(Chord_Maj,7, 0,4,7,11, false), // maj7
	new Chord7(Chord_Min,7, 0,3,7,10, true), // min7
	new Chord7(Chord_Dom,7, 0,4,7,10, true), // dom7
};

const int chordEntryCount = 9;

const char *qualityName[Chord_Quality_Max] = {
	"maj", "min", "dim", "aug", "sus", "dom"
};

}
