//////////////////////////////////////////////////////////////
// IFileMgr.h - FileMgr Component Interface                 //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
///////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package describe the interfaces of FileMgr component
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2017
* - first release
*
*/

#pragma once
#ifndef IFILEMGR_H
#define IFILEMGR_H
#include<string>
#include<vector>
#include<array>

class IFileMgr
{
public:
	IFileMgr() {}
	virtual ~IFileMgr() {}
        // -------<for the given path, find the files the match the given patterns>---------
	virtual void traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns) = 0;
	// -------<overloading of traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns)>---------
        virtual void traverseAndEnQ() = 0;
	// -------<set the searching path>-------------
        virtual void setPath(const std::string&) = 0;
        // -------<add a file pattern>-------------
	virtual void addPattern(const std::string&) = 0;
        // -------<retrieve a result from the blockingQueue>-------------
	virtual std::array<std::string, 2> get() = 0;
private:

};

#endif // !IFILEMGR_H

