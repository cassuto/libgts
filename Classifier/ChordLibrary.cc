#include "ChordLibrary.h"

namespace ChordLibrary
{

const ChordBase *chords[] = {
	new Chord3("maj",0, 0,4,7),
	new Chord3("min",0, 0,3,7),
	new Chord3("dim",0, 0,3,6),
	new Chord3("aug",0, 0,4,8),
	new Chord3("sus",2, 0,2,7), // sus2
	new Chord3("sus",4, 0,5,7), // sus4
	new Chord7("maj",7, 0,4,7,11), // maj7
	new Chord7("min",7, 0,3,7,10), // min7
	new Chord7("dom",7, 0,4,7,10), // dom7
};

const int chordsCount = 9;

}
