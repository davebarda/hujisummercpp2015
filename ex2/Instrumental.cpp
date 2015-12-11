/*
 * -----------------------------------------------------------------------
 * This file contains the implementation of the Instrumental class methods
 * -----------------------------------------------------------------------
 */
#include <set>
#include "Instrumental.h"

/**
* The default ctor.
* @param title the title of the song.
* @param tagsValue the value of tags related to the song.
* @param instruments instruments used to create the song.
* @param performedBy the performer of the instrumental song.
* @param bpm the beats per minute of the song.
*/
Instrumental::Instrumental(const std::string &title, const std::map<std::string, int> &tagsValue,
						   const std::set<std::string> &instruments, 
						   const std::string &performedBy, int bpm) : Song::Song(title, tagsValue),
						   _instruments(instruments), _performedBy(performedBy), _bpm(bpm)
{
		
}

/**
 * A method used to return the lyrics of the song.
 * @return vector that contains the lyrics of the song. 
 */
std::vector<std::string> Instrumental::getLyrics() const
{
	// return an empty vector cause no lyrics exist in an instrumental song.
	return std::vector<std::string>();
}

/**
* A method that is used to determine if an instrument used at the creation of the song.
* @param instrument the instrument to check.
* @return true iff the instrument was used to create the song.
*/
bool Instrumental::isInstrumentUsed(const std::string &instrument) const 
{
	return (_instruments.find(instrument) != _instruments.end());
}


/**
* A method that is used to get the beats per minute of the song.
* @return the bpm of the song.
*/
int Instrumental::getBpm() const
{
	return _bpm;
}

/**
* A method that is used to get the performer of the song.
* @return a string of the format "performed by: <performer>"
*/
std::string Instrumental::getCreator() const
{
	return "performed by: " +  _performedBy;
}
