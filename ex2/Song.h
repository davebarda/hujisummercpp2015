// Song.h
#ifndef SONG_H_
#define SONG_H_

#include <string>
#include <map>
#include <vector>

const int NO_SUCH_TAG = 0;
const int NO_SUCH_WORD = 0;
const int BPM_UNDEFINED = 0;
const int NO_INSTRUMENTS_USED = 0;

/**
 * An abstract class that represents a song.
 */
class Song
{
	public:
		/**
		 * The default ctor used to create a song.
		 * @param title the song title.
		 * @param tagsValue the values of all the tags related to the song.
		 */
		Song(const std::string &title, const std::map<std::string, int> &tagsValue);
	
		/**
		 * A method that is used to return the title of the song.
		 * @return the song title.
		 */
		std::string getTitle() const;

		/**
		 * A method that returns a given tag value.
		 * @param tag the tag to get the value of.
		 * @return the tag value.
		 */
		int tagValue(const std::string &tag) const;

		/**
		 * A virtual destructor.
		 */
		virtual ~Song();

		/**
		 * A pure virtual method used to return the lyrics of the song.
		 * 
		 */
		virtual std::vector<std::string> getLyrics() const = 0;

		/**
		 * A pure virtual method returns true iff an instrument is used in the song.
		 */
		virtual bool isInstrumentUsed(const std::string&) const = 0;

		/**
		 * A pure virtual method returns the bpm of the song.
		 */
		virtual int getBpm() const = 0;

		/**
		 * A pure virtual method used to get the creator of the song.
		 */
		virtual std::string getCreator() const = 0;
	private:
		std::string _title; /**< a string represents the title of the song */
		std::map<std::string, int> _tagsValue; /**< a map contains tags(as keys) 
												 and their values(as value) */
};

#endif // SONG_H_
