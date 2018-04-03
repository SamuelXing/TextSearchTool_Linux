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
	{};
        std::vector<int> scanner(const std::string& fileSpec, const std::string& reg);
private:
};

#endif /* SEARCH_H */

