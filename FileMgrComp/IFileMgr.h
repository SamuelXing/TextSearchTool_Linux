/* 
 * File:   IFileMgr.h
 * Author: parallels
 *
 * Created on April 2, 2018, 4:33 PM
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
	virtual void traverseAndEnQ(const std::string& path, const std::vector<std::string>& filePatterns) = 0;
	virtual void traverseAndEnQ() = 0;
	virtual void setPath(const std::string&) = 0;
	virtual void addPattern(const std::string&) = 0;
	virtual std::array<std::string, 2> get() = 0;
private:

};

#endif // !IFILEMGR_H

