/*
 * ---------------------------------------------------------------
 * This file contains the implementation of the Song class methods
 * ---------------------------------------------------------------
 */
#include "Song.h"

/**
* The default ctor used to create a song.
* @param title the song title.
* @param tagsValue the values of all the tags related to the song.
*/
Song::Song(const std::string &title, const std::map<std::string, int> &tagsValue) : 
		   _title(title), _tagsValue(tagsValue)
{
}

/**
 * The default destructor.
 */
Song::~Song()
{
}

/**
* A method that is used to return the title of the song.
* @return the song title.
*/
std::string Song::getTitle() const
{
	return _title;
}

/**
* A method that returns a given tag value.
* @param tag the tag to get the value of.
* @return the tag value.
*/
int Song::tagValue(const std::string &tag) const
{
	return ((_tagsValue.find(tag) != _tagsValue.end()) ? _tagsValue.at(tag) : NO_SUCH_TAG);
}
