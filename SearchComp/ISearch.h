/* 
 * File:   ISearch.h
 * Author: parallels
 *
 * Created on April 3, 2018, 8:52 AM
 */

#ifndef ISEARCH_H
#define ISEARCH_H

#include<string>
#include<vector>

class  ISearch
{
public:
	ISearch() {}
	virtual ~ISearch() {}
	virtual std::vector<int> scanner(const std::string& fileSpec, const std::string& text) = 0;
private:

};

class SearchCompFactory
{
public:
	static ISearch* CreateSearchComp();
};

extern "C" {
    ISearch* CreateSearchComp();    
}


#endif /* ISEARCH_H */

