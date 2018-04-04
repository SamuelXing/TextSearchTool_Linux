#pragma once
//////////////////////////////////////////////////////////////
// Search.h - TextSearch Component Interface                //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
//////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* The implementations of TextSearch Component
*
* Required Files:
* ---------------
* "ISearch.h"
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2017
* - first release
*
*/

#ifndef SEARCH_H
#define SEARCH_H
#include "ISearch.h"

class Search :public ISearch
{
public:
	Search() {}
	virtual ~Search(){};
        // ---<for the given file, find the regular expression existed or not>------
        std::vector<int> scanner(const std::string& fileSpec, const std::string& reg);
private:
};

#endif /* SEARCH_H */

