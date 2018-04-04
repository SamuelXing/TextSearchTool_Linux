//////////////////////////////////////////////////////////////
// ISearch.h - TextSearch Component Interface               //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
//////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package describe the interfaces of TextSearch component
*
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2017
* - first release
*
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
        // ---<for the given file, find the regular expression existed or not>------
	virtual std::vector<int> scanner(const std::string& fileSpec, const std::string& text) = 0;
private:

};

////////////////////////////////////////////////
// Class Definition: 
//  - Factory Methods to create an instance of SearchComp
class SearchCompFactory
{
public:
	static ISearch* CreateSearchComp();
};

extern "C" {
    ISearch* CreateSearchComp();    
}


#endif /* ISEARCH_H */

