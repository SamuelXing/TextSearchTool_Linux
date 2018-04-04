//////////////////////////////////////////////////////////////
// FileMgr.h - IFileMgr interface implementation            //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
///////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* The implementations of IFileMgr.
*
* Required Files:
* ---------------
* Cpp11-BlockingQueue.h
* FileSystem.h"
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2017
* - first release
*
*/


#pragma once
#ifndef FILEMGR_H
#define FILEMGR_H

#include<iostream>
#include "IFileMgr.h"
#include "Cpp11-BlockingQueue.h"
#include "FileSystem.h"

class FileMgr : public IFileMgr 
{
	using path = std::string;
	using patterns = std::vector<std::string>;
public:
	FileMgr();
        virtual ~FileMgr() {}
        // -------<for the given path, find the files the match the given patterns>---------
	virtual void traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns);
        // -------<overloading of traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns)>---------
        virtual void traverseAndEnQ();
        // -------<add a file pattern>-------------
        void addPattern(const std::string& pattern);
        // -------<set the searching path>-------------
	void setPath(const std::string& path);
        // -------<retrieve a result from the blockingQueue>-------------
	virtual std::array<std::string, 2> get();
	
private:
	BlockingQueue<std::array<std::string, 2>> q_;
	path path_;
	patterns patterns_;
        // -------<traverse helper function>-------------
	void traverseHelper(const std::string& path, const std::vector<std::string>& filePatterns);
        static int FileCount;
};
#endif // !FILEMGR_H

