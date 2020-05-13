#ifndef CHORDLIBRARY_H_
#define CHORDLIBRARY_H_

namespace ChordLibrary
{

enum ChordQuality {
	Chord_Maj,
	Chord_Min,
	Chord_Dim,
	Chord_Aug,
	Chord_Sus,
	Chord_Dom,
	Chord_Quality_Max
};

class ChordBase {
public:
	ChordBase(ChordQuality quality, int intervals, bool ghostNoteFixup)
		: quality(quality),
		  intervals(intervals),
		  ghostNoteFixup(ghostNoteFixup)
	{}
	virtual ~ChordBase() {}
	virtual int type() const {return 3;}
	ChordQuality quality;
	int intervals;
	bool ghostNoteFixup;
};

//
// 3-chord with 3 Component Tones
//
class Chord3 : public ChordBase {
public:
	Chord3(ChordQuality quality, int intervals, int root, int third, int fifth, bool ghostNoteFixup)
		: ChordBase(quality, intervals,ghostNoteFixup),
		  root(root),
		  third(third),
		  fifth(fifth)
	{}
	~Chord3() {}
	int type() const {return 3;}
	int root, third, fifth;
};

//
// 7-chord with 4 Component Tones
//
class Chord7 : public ChordBase {
public:
	Chord7(ChordQuality quality, int intervals, int root, int third, int fifth, int seventh, bool ghostNoteFixup)
		: ChordBase(quality, intervals, ghostNoteFixup),
		  root(root),
		  third(third),
		  fifth(fifth),
		  seventh(seventh)
	{}
	~Chord7() {}
	int type() const {return 7;}
	int root, third, fifth, seventh;
};

extern const int chordEntryCount;
extern const ChordBase *chordEntry[];

extern const char *qualityName[Chord_Quality_Max];
}

#endif // CHORDLIBRARY_H_
