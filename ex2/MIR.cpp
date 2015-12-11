/*
 * -----------------------------------------------------------------------------
 * This file contains the main program and additional helpful functions used to 
 * print all the songs match to a query by a given arguments.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Song.h"
#include "Scorer.h"
#include "Parser.h"

const int SONGS_FILE_ARG_NUM = 1;
const int PARAMETERS_FILE_ARG_NUM = 2;
const int QUERIES_FILE_ARG_NUM = 3;
const int LEGAL_NUM_OF_ARGS = 4;

/**
 * A comperator used to compare between scoredSongs for std::stable_sort usage.
 * @param firstScore the first score to compare.
 * @param secondScore the second score to compare.
 * @return true iff the first score is greater than the second one.
 */
bool scoredSongsComperator(const std::pair<Song*, int> &firstScore, 
						   const std::pair<Song*, int> &secondScore) 
{
	return (firstScore.second > secondScore.second);
}

/**
 * A function used to free all the songs allocated on the heap by the parser.
 * @param a vector contains the songs to free.
 */
void freeSongs(std::vector<Song*> &songs)
{
	for (std::vector<Song*>::iterator it = songs.begin(); it != songs.end(); ++it)
	{
		delete (*it);
	}
}


/**
 * A function that is used to score songs by its match to a given query.
 * @param songs the songs to score.
 * @param scorer the scorer which defines what score each song should get.
 * @param query the query to get the score of.
 * @return a vector which contains songs and their score with regard to the query.
 */
std::vector<std::pair<Song*, int> > getScores(const std::vector<Song*> &songs, const Scorer &scorer,
											  const std::string &query)
{
	std::vector<std::pair<Song*, int> > res;
	for (std::vector<Song*>::const_iterator it = songs.begin(); it != songs.end(); ++it)
	{
		int score;
		if ((score = scorer.getScore(*(*it), query)))
		{
			res.push_back(std::pair<Song*, int>(*it, score));
		}
	}
	return res;
}

/**
 * The main function.
 * used to print all the songs match to a query by a given arguments.
 * @param argc the number of arguments given from cli.
 * @param argv the arguments was given by the cli.
 */
int main(int argc, char *argv[])
{
	if (argc != LEGAL_NUM_OF_ARGS)
	{
		std::cout << "Usage: MIR < songs file name > < parameters file name > < queries file name >"
				  << std::endl;
		return 1;
	}
	// Declare on the relevant data structures for the songs parser.
	std::string songsFilename(argv[SONGS_FILE_ARG_NUM]);
	std::vector<Song*> songs;

	// Declare on the relevant data structures for the parameters parser.
	std::string parametersFilename(argv[PARAMETERS_FILE_ARG_NUM]);
	std::map<Scorer::ScoreParameters, int> parametersValue;
	std::map<std::string, std::pair<double, double> > knownWords;

	// Parse and check for file handeling problems.
	if (!Parser::parseParameters(parametersFilename, parametersValue, knownWords) || 
		!Parser::parseSongs(songsFilename, songs))
	{
		return 1;
	}

	Scorer scorer(parametersValue, knownWords);
			
	std::ifstream instream(argv[QUERIES_FILE_ARG_NUM]);
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: " << argv[QUERIES_FILE_ARG_NUM] << "." << std::endl;	
		return 1;
	}

	std::string query;
	Parser::getlineSkipEmpty(instream, query);

	while(instream.good())
	{
		// Get scores and stable sort the songs by their scores
		std::vector<std::pair<Song*, int> > scores = getScores(songs, scorer, query);
		std::stable_sort(scores.begin(), scores.end(), scoredSongsComperator);

		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Query word: " << query << "\n" << std::endl;
		for (std::vector<std::pair<Song*, int> >::iterator it = scores.begin();
			 it != scores.end(); ++it)
		{
			std::cout << it->first->getTitle() << "\t" << it->second
					  << "\t" << it->first->getCreator() << std::endl;	
		}
		Parser::getlineSkipEmpty(instream, query);
	}

	freeSongs(songs);
	return 0;
}
