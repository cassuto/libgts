#ifndef CHORDLIBRARY_H_
#define CHORDLIBRARY_H_

namespace ChordLibrary
{
class ChordBase {
public:
	ChordBase(const char *quality, int intervals)
		: quality(quality),
		  intervals(intervals)
	{}
	virtual ~ChordBase() {}
	virtual int type() const {return 3;}
	const char *quality;
	int intervals;
};

class Chord3 : public ChordBase {
public:
	Chord3(const char *quality, int intervals, int root, int third, int fifth)
		: ChordBase(quality, intervals),
		  root(root),
		  third(third),
		  fifth(fifth)
	{}
	~Chord3() {}
	int type() const {return 3;}
	int root, third, fifth;
};

class Chord7 : public ChordBase {
public:
	Chord7(const char *quality, int intervals, int root, int third, int fifth, int seventh)
		: ChordBase(quality, intervals),
		  root(root),
		  third(third),
		  fifth(fifth),
		  seventh(seventh)
	{}
	~Chord7() {}
	int type() const {return 7;}
	int root, third, fifth, seventh;
};

extern const int chordsCount;
extern const ChordBase *chords[];

}

#endif // CHORDLIBRARY_H_
