/*
 * ----------------------------------------------------------------
 * This file contains the implementation of the Vocal class methods
 * ----------------------------------------------------------------
 */
#include "Vocal.h"

/**
* The default ctor.
* @param title the title of the song.
* @param tagsValue the value of tags related to the song.
* @param wordsOccurence contains mapping between words and the number of time it occures inn
* the song
* @param lyricsBy the writer of the song lyrics.
*/
Vocal::Vocal(const std::string &title, const std::map<std::string, int> &tagsValue,
			 const std::vector<std::string> &lyrics,
			 const std::string &lyricsBy) : Song::Song(title, tagsValue), 
			  _lyrics(lyrics), _lyricsBy(lyricsBy)
{
}

/**
 * A method used to return the lyrics of the song.
 * @return vector that contains the lyrics of the song. 
 */
std::vector<std::string> Vocal::getLyrics() const
{
	return _lyrics;
}

/**
* A method that is used to determine if an instrument used at the creation of the song.
* @param instrument the instrument to check.
* @return true iff the instrument was used to create the song.
*/
bool Vocal::isInstrumentUsed(const std::string&) const
{
	return NO_INSTRUMENTS_USED;
}

/**
* A method that is used to get the beats per minute of the song.
* @return the bpm of the song.
*/
int Vocal::getBpm() const
{
	return 0;
}

/**
* A method that is used to get the name of the one who wrote the lyrics of the song.
* @return a string of the format "lyricsBy by: <writer>"
*/
std::string Vocal::getCreator() const
{
	return "lyrics by: " + _lyricsBy;
}
