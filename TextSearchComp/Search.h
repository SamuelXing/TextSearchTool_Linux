#pragma once
/* 
 * File:   Search.h
 * Author: parallels
 *
 * Created on April 2, 2018, 5:55 PM
 */

#ifndef SEARCH_H
#define SEARCH_H
#include "ISearch.h"

class Search :public ISearch
{
public:
	Search() {}
	virtual ~Search()
	{
            if (!pFileMgr)
		delete pFileMgr;
	};
	void setText(const std::string&);
        void scanner(const std::string& fileSpec, const std::string& reg);
	void setFileMgr(IFileMgr* IfileMgr);
	void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg);
	void search();
        bool done();
        std::string get();
private:
        BlockingQueue<std::string> q_;
	IFileMgr * pFileMgr;
	std::string text_;
        std::thread* t_;
};

#endif /* SEARCH_H */

