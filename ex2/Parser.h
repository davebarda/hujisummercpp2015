// Parser.h
#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <map>
#include "Song.h"
#include "Scorer.h"

const std::string SEPERATOR = "=";
const std::string END_OF_SONGS = "***";
const std::string TITLE = "title";
const std::string EMPTY_LINE = "\n";
const std::string TAGS = "tags";
const std::string LYRICS = "lyrics";
const std::string LYRICS_BY = "lyricsBy";
const std::string INSTRUMENTS = "instruments";
const std::string PERFORMED_BY = "performedBy";
const std::string BPM = "bpm";                   
const std::string TAGS_OPEN_SYMBOL = "{";
const std::string TAGS_CLOSE_SYMBOL = "}";
const char NEW_LINE = '\n';
const std::string TAG_MATCH_SCORE = "tagMatchScore";
const std::string LYRICS_MATCH_SCORE = "lyricsMatchScore";
const std::string INSTRUMENT_MATCH_SCORE = "instrumentMatchScore";
const std::string BPM_LIKELIHOOD_WEIGHT = "bpmLikelihoodWeight";
const int KEYWORD_VALUE_SEPERATE_LENGTH = 2;

/**
 * A namespace represents the API of the Parser module.
 */
namespace Parser
{
	/**
	 * A function that is used to parse the songs file.
	 * @param songsFilename the songs file name.
	 * @param songs a vector to fill with songs, it is the user responsibility to free the song
	 * dynamically assigned memory.
	 * @return true iff the parsing succeeded and the data structures filled correctly.
	 */
	bool parseSongs(const std::string &songsFileName, std::vector<Song*> &songs);

	/**
	 * A function that is used to parse the parameters file.
	 * @param parametersFilename the parameters file name.
	 * @param parametersValue a map between a Scorer object scoring parameter and an integer with
	 * the scoring value.
	 * @param knownKeyWords a map between words and their average bpm and standard deviation.
	 * @return true iff the parsing succeeded and the data structures filled correctly.
	 */
	bool parseParameters(const std::string &parametersFilename, 
						 std::map<Scorer::ScoreParameters, int> &parametersValue,
						 std::map<std::string, std::pair<double, double> > &knownKeywords);

	/**
	 * A function that is used to wrap the getline function so it will skip empty lines.
	 * @param instream the stream to read from.
	 * @param line the line to save to.
	 */
	void getlineSkipEmpty(std::ifstream &instream, std::string &line);
}

#endif // PARSER_H_
