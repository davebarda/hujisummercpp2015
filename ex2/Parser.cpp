/*
 * -----------------------------------------------------------------------------
 * This file contains the parser module.
 * -----------------------------------------------------------------------------
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include "Parser.h"
#include "Instrumental.h"
#include "Vocal.h"
#include "Scorer.h"

/**
 * A function that is used to wrap the getline function so it will skip empty lines.
 * @param instream the stream to read from.
 * @param line the line to save to.
 */
void Parser::getlineSkipEmpty(std::ifstream &instream, std::string &line)
{
	while(instream.good() && instream.peek() == NEW_LINE)
	{
		instream.ignore();
	}
	if (instream.good())
	{
		getline(instream, line);
	}
}

/**
 * A function that is used to remove curly brackets surrounding text.
 * @param str the surounded string.
 * @return a copy of the string without the surounding brackets.
 */
std::string removeReduntantBrackets(const std::string &str)
{
	size_t pos1 = str.find_first_of(TAGS_OPEN_SYMBOL);
	size_t pos2 = str.find_last_of(TAGS_CLOSE_SYMBOL);
	return str.substr(pos1 + 1, (pos2 - pos1) - 1);
}

/**
 * A function that is used to parse tags given in a songs file.
 * @param tags the tags and values as a string.
 * @return a map from tag to value.
 */
std::map<std::string, int> parseTagValues(const std::string &tags)
{
	std::map<std::string, int> tagsValue;
	std::istringstream iss(removeReduntantBrackets(tags));

	std::string tag;
	int value;
	while (iss >> tag >> value)
	{
		tagsValue[tag] = value;	
	}

	return tagsValue;
}

/**
 * A function that is used to parse the insruments given in the songs file.
 * @param instrumentStr a string represents the instruments used in the song.
 * @return a set of used instruments.
 */
std::set<std::string> parseInstruments(const std::string &instrumentsStr)
{
	std::set<std::string> instruments;
	std::istringstream iss(removeReduntantBrackets(instrumentsStr));

	std::string instrument;
	while (iss >> instrument)
	{
		instruments.insert(instrument);
	}

	return instruments;
}

/**
 * A function that is used to parse the lyrics of a song give in the songs file.
 * @param lyricsStr a string representation of the lyrics.
 * @return a vector of the lyrics
 */
std::vector<std::string> parseLyrics(const std::string &lyricsStr)
{
	std::vector<std::string> lyrics;
	std::istringstream iss(removeReduntantBrackets(lyricsStr));
	std::string word;

	while(iss >> word)
	{
		lyrics.push_back(word);
	}

	return lyrics;
}

/**
 * A function that is used to parse the songs file.
 * @param songsFilename the songs file name.
 * @param songs a vector to fill with songs, it is the user responsibility to free the song
 * dynamically assigned memory.
 * @return true iff the parsing succeeded and the data structures filled correctly.
 */
bool Parser::parseSongs(const std::string &songsFilename, std::vector<Song*> &songs)
{
	std::ifstream instream(songsFilename.c_str());
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: " << songsFilename << "." << std::endl;	
		return false;
	}

	std::string line = "";
	Song *song;

	while (instream.good())
	{
		if (line.compare(SEPERATOR) != 0)
		{
			getlineSkipEmpty(instream, line);
			// Case no more songs
			if(line.compare(END_OF_SONGS) == 0)
			{
				break;
			}
		}
		getlineSkipEmpty(instream, line);

		// Expect line of title:..
		size_t pos = TITLE.size() + KEYWORD_VALUE_SEPERATE_LENGTH;
		std::string title = line.substr(pos);

		getlineSkipEmpty(instream, line);
		// Expect a line of "tags: {...}"
		std::map<std::string, int> tagsValue = parseTagValues(line);

		std::string lyrics = "";
		std::string lyricsBy = "";
		std::string instruments = "";
		std::string performedBy = "";
		int bpm = BPM_UNDEFINED;

		getlineSkipEmpty(instream, line);
		// Expect either lyrics or instruments.
		
		// Case vocal song
		if ((line.size() >= LYRICS.size()) && 
			line.substr(0, LYRICS.size()).compare(LYRICS) == 0)
		{
			std::vector<std::string> lyrics = parseLyrics(line);	
			pos = LYRICS_BY.size() + KEYWORD_VALUE_SEPERATE_LENGTH;
			getlineSkipEmpty(instream, line);
			lyricsBy = line.substr(pos);
			song = (Song*)new Vocal(title, tagsValue, lyrics, lyricsBy);
		}
		// Case Instrumental song
		else
		{
			std::set<std::string> instruments = parseInstruments(line);	

			getlineSkipEmpty(instream, line);
			// Expect a line of "performedBy: "
			pos = PERFORMED_BY.size() + KEYWORD_VALUE_SEPERATE_LENGTH;
			performedBy = line.substr(pos);

			// Check if BPM is set
			if (!instream.good())
			{
				break;
			}

			std::streampos sp = instream.tellg();
			getlineSkipEmpty(instream, line);

			// case non empty line is not end of songs and not seperator => its a bpm line!
			if ((line.compare(END_OF_SONGS) != 0) && (line.compare(SEPERATOR) != 0))
			{
				pos = BPM.size() + KEYWORD_VALUE_SEPERATE_LENGTH;
				bpm = std::stoi(line.substr(pos));
			}
			/* if no BPM reverse the getline operation by returning the cursor and set the line to
			   so it wont contain a seperator and avoid the getline in the if statement at the
			   beginning of the loop */
			else
			{
				line = "";
				instream.seekg(sp);
			}
			song = (Song*)new Instrumental(title, tagsValue, instruments, performedBy, bpm);
		}
		
		songs.push_back(song);
	}
	instream.close();
	return true;
}

/**
 * A function that is used to parse the parameter value part in the parameters file.
 * @param parametersValue a map between a Scorer object scoring parameter and an integer with
 * the scoring value.
 * @param instream the input file stream to take the data from.
 * @param parameter the parameter to take the value of.
 */
void parseParamValue(std::map<Scorer::ScoreParameters, int> &parametersValue, 
					 std::ifstream &instream, const Scorer::ScoreParameters &parameter)
{
	std::string line;
	Parser::getlineSkipEmpty(instream, line);
	size_t pos;

	switch(parameter)
	{
		case Scorer::TAGS:
			pos = TAG_MATCH_SCORE.size();
			break;
		case Scorer::LYRICS:
			pos = LYRICS_MATCH_SCORE.size();
			break;
		case Scorer::INSTRUMENTS:
			pos = INSTRUMENT_MATCH_SCORE.size();
			break;
		case Scorer::BPM:
			pos = BPM_LIKELIHOOD_WEIGHT.size();
			break;
	}

	parametersValue[parameter] = std::stoi(line.substr(pos + KEYWORD_VALUE_SEPERATE_LENGTH));
}

/**
 * A function that is used to parse the parameters file.
 * @param parametersFilename the parameters file name.
 * @param parametersValue a map between a Scorer object scoring parameter and an integer with
 * the scoring value.
 * @param knownKeyWords a map between words and their average bpm and standard deviation.
 * @return true iff the parsing succeeded and the data structures filled correctly.
 */
bool Parser::parseParameters(const std::string &parametersFilename, 
							 std::map<Scorer::ScoreParameters, int> &parametersValue,
							 std::map<std::string, std::pair<double, double> > &knownKeywords)
{	
	std::ifstream instream(parametersFilename.c_str());
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: " << parametersFilename << "." << std::endl;	
		return false;
	}
	// Parse the parameters values.
	parseParamValue(parametersValue, instream, Scorer::ScoreParameters::TAGS);
	parseParamValue(parametersValue, instream, Scorer::ScoreParameters::LYRICS);
	parseParamValue(parametersValue, instream, Scorer::ScoreParameters::INSTRUMENTS);
	parseParamValue(parametersValue, instream, Scorer::ScoreParameters::BPM);

	// Parse bpm avarage and standard deviation of known words.
	std::string line;
	std::string parameter;
	char ignoreComma;
	double avarage;
	double standardDeviation;
	while(instream.good())
	{
		getlineSkipEmpty(instream, line);		
		std::istringstream iss(line);
		// An error should occur only if the file ended with empty lines and then the loop will exit
		if (iss >> parameter >> avarage >> ignoreComma >> standardDeviation)
		{
			parameter = parameter.substr(0, parameter.size() - 1);
			knownKeywords[parameter] = std::pair<double, double>(avarage, standardDeviation);
		}
	}
	instream.close();
	return true;
}
