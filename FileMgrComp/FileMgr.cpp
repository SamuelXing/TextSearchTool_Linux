//////////////////////////////////////////////////////////////
// FileMgr.cpp - FileMgr class implementation               //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
//////////////////////////////////////////////////////////////

#include "FileMgr.h"
#include<exception>

using namespace FileSystem;

struct EmptyPath : public std::exception {
	const char* what() const throw() {
		return "path is null";
	}
};

FileMgr::FileMgr() {

}

int FileMgr::FileCount = 0;

// -------<traverse helper function>-------------
void FileMgr::traverseHelper(const std::string& path, const std::vector<std::string>& filePatterns) 
{
	for (size_t i = 0; i < filePatterns.size(); i++)
	{
		std::vector<std::string> matchedFileNames = Directory::getFiles(path, filePatterns[i]);
		for (size_t j = 0; j < matchedFileNames.size(); j++)
		{
			std::string filePath = Path::fileSpec(path, matchedFileNames[j]);
                        std::array<std::string, 2> record = {filePath, "FILE"};
			this->q_.enQ(record);
                        FileCount += 1;
			std::cout << "FileMgrComp found: " << filePath << std::endl;
		}
	}

	std::vector<std::string> dirs = Directory::getDirectories(path, "*");
	for (size_t i = 0; i < dirs.size(); i++)
	{
		if (dirs[i] == "." || dirs[i] == "..")
			continue;
		std::string fullDirPath = Path::fileSpec(path, dirs[i]);
		traverseHelper(fullDirPath, filePatterns);
	}

	return;
}

// -------<for the given path, find the files the match the given patterns>---------
void FileMgr::traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns) 
{
	std::cout << "Call FileManager Component given inputs:\n";
        std::cout << "path:" << path << std::endl;
        for(int i=0; i<filePatterns.size(); i++)
            std::cout << "pattern:" << filePatterns[i] << std::endl;
        std::cout << "\nOutput of FileManager Component:" <<std::endl;
	traverseHelper(path, filePatterns);
	std::cout << "-------------------------------------------------\n";
	std::cout << "Total: " << FileCount << " files matched\n\n\n";
        std::array<std::string, 2> record = {"", "EOF"};
	this->q_.enQ(record);
	return;
}

// -------<overloading of traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns)>---------
// -- call Path:
// -- 1, setPath()
// -- 2, addPattern()
// ---3, traverseAndEnQ()
void FileMgr::traverseAndEnQ() 
{
	try 
	{
		if (this->path_ == "")
			throw EmptyPath();
		if (this->patterns_.size() == 0)
			this->addPattern("*.*");
		this->traverseAndEnQ(path_, patterns_);
	}
	catch (EmptyPath& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) 
	{
		std::cout << e.what() << std::endl;
	}
}

// -------<set the searching path>-------------
void FileMgr::setPath(const std::string& path) 
{
	this->path_ = path;
}

// -------<add a file pattern>-------------
void FileMgr::addPattern(const std::string& pattern) 
{
	this->patterns_.push_back(pattern);
}

// -------<retrieve a result from the blockingQueue>-------------
std::array<std::string, 2> FileMgr::get() 
{
	return this->q_.deQ();
}