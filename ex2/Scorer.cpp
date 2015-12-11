#include "Scorer.h"
#include <iostream>
#include <algorithm>

/*
 * -----------------------------------------------------------------
 * This file contains the implementation of the Scorer class methods
 * -----------------------------------------------------------------
 */

/**
 * The default ctor used to create a Scorer.
 * @param scoreWeight the weight of each parameter in the end score.
 * @param knownKeywords key words that was previously learned and check to get better
 * results.
 */
Scorer::Scorer(const std::map<Scorer::ScoreParameters, int> &scoreWeight,
			   const std::map<std::string, std::pair<double, double> > &knownKeywords) :
			   _scoreWeight(scoreWeight), _knownWords(knownKeywords)
{
}

/**
 * A method that returns the score of a given song and query.
 * scores by using inner methods that scores by the ScoreParameters.
 * @param song a song to score.
 * @param query a query to score.
* @return the total matching score of the song with the given query.
 */
int Scorer::getScore(const Song &song, const std::string &query) const
{
	return _tagsMatchScore(song, query) + _wordOccurenceScore(song, query) + 
		   _instrumentUsedScore(song, query) + _bpmScore(song, query);
}

/**
* A methd that calculates the score gained from matched tags.
* @param song a song to score.
* @param tag a tag to score.
* @return the score gained if the tag match.
*/
int Scorer::_tagsMatchScore(const Song &song, const std::string &tag) const
{
	return song.tagValue(tag) * _scoreWeight.at(TAGS);
}

/**
* A method that calculates the score gained by a word occurence int the lyrics.
* @param song a song to score.
* @param word a word to score.
* @return the score gained by the number of occurence of the word in the lyrics.
*/
int Scorer::_wordOccurenceScore(const Song &song, const std::string &word) const
{
	std::vector<std::string> lyrics = song.getLyrics();
	int occurence = std::count (lyrics.begin(), lyrics.end(), word);
	return occurence * _scoreWeight.at(LYRICS);
}

/**
* A method that calculates the score gained if a given instrument is used.
* @param song a song to score.
* @param instrument an instrument to score.
* @return the score gained if the instrument is used.
*/
int Scorer::_instrumentUsedScore(const Song &song, const std::string &instrument) const
{
	return (song.isInstrumentUsed(instrument) ? _scoreWeight.at(INSTRUMENTS) : NO_INSTRUMENT_SCORE);
}

	
/**
 * A function that is used to calculate the following likelihood formula
 * using the likelihood formula floor(BPM_SCORE_WEIGHT * (e^(-((bpm-m)^2 / 2*s^2)) ))
 * @param bpmScoreWeight the score weight for bpm.
 * @param songBpm the beats per minute of the song.
 * @param avarage the pre calculated average for a known word.
 * @param standardDeviation the standard deviation pre pre calculated for a known word.
 */
inline int _likeliHood(int bpmScoreWeight, int songBpm, double average, 
					   double standardDeviation)
{
	return floor(bpmScoreWeight * exp(-(pow((songBpm - average), BPM_SCORE_POWER_CONST) /
										(BPM_SCORE_DIVISOR_CONST * pow(standardDeviation, 
										BPM_SCORE_POWER_CONST)))));
}

/**
* A method that calculates the score gained by bpm compatibility with a knownWord.
* @param song a song to score.
* @param knownWord a word to check
* @return the score gained by bpm compatability with the knownWord.
*/
int Scorer::_bpmScore(const Song &song, const std::string &knownWord) const
{
	if ((_knownWords.find(knownWord) == _knownWords.end()) || (song.getBpm() == BPM_UNDEFINED))
	{
		return 0;
	}
	double average = _knownWords.at(knownWord).first;
	double standardDeviation = _knownWords.at(knownWord).second;

	return _likeliHood(_scoreWeight.at(BPM), song.getBpm(), average, standardDeviation);
}
