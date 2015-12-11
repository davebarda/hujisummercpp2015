// Instrumental.h
#ifndef INSTRUMENTAL_H_
#define INSTRUMENTAL_H_

#include "Song.h"

/**
 * A class that represents an instrumental song.
 */
class Instrumental : Song
{
	public:
		/**
		 * The default ctor.
		 * @param title the title of the song.
		 * @param tagsValue the value of tags related to the song.
		 * @param instruments instruments used to create the song.
		 * @param performedBy the performer of the instrumental song.
		 * @param bpm the beats per minute of the song.
		 */
		Instrumental(const std::string &title, 
					 const std::map<std::string, int> &tagsValue,
					 const std::set<std::string> &instruments, 
					 const std::string &performedBy, int bpm = BPM_UNDEFINED);

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
		bool isInstrumentUsed(const std::string &instrument) const;

		/**
		 * A method that is used to get the beats per minute of the song.
		 * @return the bpm of the song.
		 */
		int getBpm() const;

		/**
		 * A method that is used to get the performer of the song.
		 * @return a string of the format "performed by: <performer>"
		 */
		std::string getCreator() const;

	private:
		std::set<std::string> _instruments; /**< a set contains the instruments used in the song*/
		std::string _performedBy; /**< a string contains the song performer name*/
		int _bpm; /**< the beats per minute of the song */
};

#endif // INSTRUMENTAL_H_
