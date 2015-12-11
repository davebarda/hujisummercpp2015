#include <iostream>
#include <exception>
#include <sys/stat.h>
#include <cstdio>
#include <climits>
#include <list>
#include <string>
#include <boost/filesystem.hpp>
#include "Matrix.hpp"

const char PATH_SEPERATOR =
#ifdef _WIN32
	'\\';
#else
	'/';
#endif

const std::string SH_PREFIX =
#ifdef _WIN32
	"";
#else
	"./";
#endif

const std::string SCHOOL_EXEC = "SchoolSol/GenericMatrixDriver";
const std::string TESTS_FOLDER = "Tests";
const std::string USER_EXEC = "GenericMatrixDriver";
const std::string USER_SOL_DIR = "UserSol/TestsSol";
const std::string SCHOOL_SOL_DIR = "SchoolSol/TestsSol";
const std::string DIFF_DIR = "SolDiff";

using namespace boost::filesystem;

std::string valgrindCmd = "";

bool testFile(std::string fileName)
{	
	std::string testFile = TESTS_FOLDER + PATH_SEPERATOR + fileName;
	std::string userSol = USER_SOL_DIR + PATH_SEPERATOR + fileName;
	std::string schoolSol = SCHOOL_SOL_DIR + PATH_SEPERATOR + fileName;
	std::string diffCmd = "diff " + schoolSol += std::string(" ") += userSol + std::string(" > ") +
						  DIFF_DIR + PATH_SEPERATOR + fileName;

	int res = system((valgrindCmd + SH_PREFIX + USER_EXEC   + std::string(" < ") + testFile + std::string(" > ") + userSol).c_str());
	res &= system((valgrindCmd + SH_PREFIX + SCHOOL_EXEC + std::string(" < ") + testFile + std::string(" > ") + schoolSol).c_str());
	// In case that the school solution asserted for matrix dimensions
	if (res)
	{
		return true;
	}
	system(diffCmd.c_str());

	return (file_size(DIFF_DIR + PATH_SEPERATOR + fileName) == 0);
}

int main(int argc, char *argv[])
{
	if (argc != 1 && (std::string(argv[1]) == std::string("-v")))
	{
		valgrindCmd = "valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes ";
	}
	// Checks if all the relevant files exists.
	std::list<std::string> files = {SCHOOL_EXEC, USER_EXEC, TESTS_FOLDER};
	for (std::string file : files)
	{
		if (!exists(file))
		{
			std::cout << "Couldnt find path: " << current_path().string() <<  PATH_SEPERATOR 
					  << file << std::endl;
			return 1;
		}
	}
	try
	{
		std::cout << "Creating solutions directories..." << "\n";
		create_directories(USER_SOL_DIR);
		create_directories(SCHOOL_SOL_DIR);
		create_directory(DIFF_DIR);
	}
	catch(filesystem_error e)
	{
		std::cout << e.what() << std::endl;
	}


	int testNum = 1;
	int testPassed = 0;
	// Run through the files at TESTS_FOLDER and test them.
	for (auto file = directory_iterator("./" + TESTS_FOLDER); file != directory_iterator(); file++)
	{
		if (!is_directory(file->path()))
		{
			std::cout << "Running test number: " << testNum << std::endl;
			std::string pathStr = file->path().string();
			std::string fileName = pathStr.substr(pathStr.find_last_of(PATH_SEPERATOR) + 1);
			if (testFile(fileName))
			{
				testPassed++;
				std::cout << "Passed ";
			}
			else 
			{
				std::cout << "Failed ";
			}
			std::cout << "test number: " << testNum << "\tfile: " << fileName << std::endl; 
			testNum++;
		}
	}
		std::cout << "Total tests: " << testNum - 1 << " Passed: " << testPassed << " Failed: " <<
				     testNum -testPassed - 1 << std::endl;
		return 0;
}
