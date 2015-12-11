// Vocal.h
#ifndef VOCAL_H_
#define VOCAL_H_

#include "Song.h"

/**
 * A class that represents a vocal song.
 */
class Vocal : Song
{
	public:

		/**
		 * The default ctor.
		 * @param title the title of the song.
		 * @param tagsValue the value of tags related to the song.
		 * @param lyrics the lyrics of the song.
		 * the song
		 * @param lyricsBy the writer of the song lyrics.
		 */
		Vocal(const std::string &title, const std::map<std::string, int> &tagsValue,
			  const std::vector<std::string> &lyrics, const std::string &lyricsBy);

		/**
		 * A method used to return the lyrics of the song.
		 * @return vector that contains the lyrics of the song. 
		 */
		std::vector<std::string> getLyrics() const;

		/**
		 * A method that is used to determine if an instrument used at the creation of the song.
		 * @param instrument the instrument to check.
		 * @return true iff the instrument was used to create the song.
		 */
		bool isInstrumentUsed(const std::string&) const;

		/**
		* A method that is used to get the beats per minute of the song.
		* @return the bpm of the song.
		*/
		int getBpm() const;

		/**
		* A method that is used to get the name of the one who wrote the lyrics of the song.
		* @return a string of the format "lyricsBy by: <writer>"
		*/
		std::string getCreator() const;

	private:
		std::map<std::string, int> _wordsOccurence; /**< a map contains every word occur in the 
													  lyrics and the number of times it occures. */
		std::vector<std::string> _lyrics; /**< a vector contains the lyrics of the song */
		std::string _lyricsBy; /**< a string contains the name of the one who wrote the song 
								 lyrics */
};

#endif // VOCAL_H_
