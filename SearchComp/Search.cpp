//////////////////////////////////////////////////////////////
// Search.cpp - Search class implementation                 //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
//////////////////////////////////////////////////////////////

#include "Search.h"
#include<regex>
#include<exception>
#include<fstream>
#include<algorithm>

// -----<factory method>------
ISearch*  SearchCompFactory::CreateSearchComp()
{
    return new Search();
}

// -----<factory method>------
ISearch* CreateSearchComp()
{
    return new Search();
}

// ---<for the given file, find the regular expression existed or not>------
std::vector<int> Search::scanner(const std::string& fileSpec, const std::string& reg) 
{
	int lineCnt = 1;
	std::regex r(reg);
	std::ifstream ifs(fileSpec);
        std::vector<int> rst;
	if (ifs.good())
	{
		std::string fileContent((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		fileContent.erase(std::remove(fileContent.begin(),fileContent.end(),'\0'), fileContent.end());
		std::istringstream f(fileContent);
		std::string line;
		while (std::getline(f, line)) {
			if (std::regex_search(line, r))
			{
                                rst.push_back(lineCnt);
			}
			lineCnt++;
		}
	}
        return rst;
}

// -----<test stub>-------
#ifdef TEST_SEARCHCOMP
int main()
{
	std::cout << "  TEST SEARCH COMPONENT\n";
	std::cout << "=========================\n";
	std::vector<std::string> result;
	std::string regStr = "(.*?)FileSys(.*?)";
	ISearch* searchInstance = new Search();
	result = searchInstance->scanner("Specify a filename", regStr);
	for (int i = 0; i < result.size(); i++) 
	{
		std::cout << result << std::endl;
	}
	return 0;
}
#endif // TEST_SEARCHCOMP


