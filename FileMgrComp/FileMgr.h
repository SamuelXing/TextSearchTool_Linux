/* 
 * File:   FileMgr.h
 * Author: parallels
 *
 * Created on April 2, 2018, 4:35 PM
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
	virtual void traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns);
        void addPattern(const std::string& pattern);
	void setPath(const std::string& path);
        virtual void traverseAndEnQ();
	virtual std::array<std::string, 2> get();
	
private:
	BlockingQueue<std::array<std::string, 2>> q_;
	path path_;
	patterns patterns_;
	void traverseHelper(const std::string& path, const std::vector<std::string>& filePatterns);
};
#endif // !FILEMGR_H

