#pragma once
/* 
 * File:   ISearch.h
 * Author: parallels
 *
 * Created on April 2, 2018, 4:40 PM
 */

#ifndef ISEARCH_H
#define ISEARCH_H
#include<string>
#include<vector>
#include "../FileMgrComp/FileMgrFactory.h"

class  ISearch
{
public:
	ISearch() {}
	virtual ~ISearch() {}
        virtual void setFileMgr(IFileMgr* IfileMgr) = 0;
	virtual void setText(const std::string& reg) = 0;
	virtual void scanner(const std::string& fileSpec, const std::string& text) = 0;
	virtual void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) = 0;
        virtual bool done() = 0;
        virtual std::string get() = 0;
private:

};

class SearchCompFactory
{
public:
	static ISearch* CreateSearchComp();
};

extern "C" 
{
    ISearch* CreateSearchComp();
}

#endif /* ISEARCH_H */

