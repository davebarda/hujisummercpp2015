// Scorer.h
#ifndef SCORER_H_
#define SCORER_H_

#include <cmath>
#include <map>
#include <string>
#include "Song.h"

const int NO_INSTRUMENT_SCORE = 0;
const int BPM_SCORE_POWER_CONST = 2;
const int  BPM_SCORE_DIVISOR_CONST = 2;

/**
 * A class that defines a scorer used to score songs by a given query.
 */
class Scorer
{
	public:
		/**
		 * An enum that defines the scoring parameters.
		 */
		enum ScoreParameters
		{
			TAGS,
			LYRICS,
			INSTRUMENTS,
			BPM
		};

		/**
		 * The default ctor used to create a Scorer.
		 * @param scoreWeight the weight of each parameter in the end score.
		 * @param knownKeywords key words that was previously learned and check to get better
		 * results.
		 */
		Scorer(const std::map<ScoreParameters, int> &scoreWeight,
			   const std::map<std::string, std::pair<double, double> > &knownKeywords);
		/**
		 * A method that returns the score of a given song and query.
		 * @param song a song to score.
		 * @param query a query to score.
		 * @return the total matching score of the song with the given query.
		 */
		int getScore(const Song &song, const std::string &query) const;

	private:
		/**
		 * A methd that calculates the score gained from matched tags.
		 * @param song a song to score.
		 * @param tag a tag to score.
		 * @return the score gained if the tag match.
		 */
		int _tagsMatchScore(const Song &song, const std::string &tag) const;

		/**
		 * A method that calculates the score gained by a word occurence int the lyrics.
		 * @param song a song to score.
		 * @param word a word to score.
		 * @return the score gained by the number of occurence of the word in the lyrics.
		 */
		int _wordOccurenceScore(const Song &song, const std::string &word) const;

		/**
		 * A method that calculates the score gained if a given instrument is used.
		 * @param song a song to score.
		 * @param instrument an instrument to score.
		 * @return the score gained if the instrument is used.
		 */
		int _instrumentUsedScore(const Song &song, const std::string &instrument) const;

		/**
		 * A method that calculates the score gained by bpm compatibility with a knownWord.
		 * @param song a song to score.
		 * @param knownWord a word to check
		 * @return the score gained by bpm compatability with the knownWord.
		 */
		int _bpmScore(const Song &song, const std::string &knownWord) const;

		std::map<ScoreParameters, int> _scoreWeight; /**< a map of the score of each parameter */
		std::map<std::string, std::pair<double, double> > _knownWords; /**< a map that store the bpm
																		 information of 
																		 known words */
};
#endif // Scorer_H_
