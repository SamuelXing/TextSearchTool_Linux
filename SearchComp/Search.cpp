#include "Search.h"
#include<regex>
#include<exception>
#include<fstream>
#include<algorithm>

ISearch*  SearchCompFactory::CreateSearchComp()
{
    return new Search();
}

ISearch* CreateSearchComp()
{
    return new Search();
}


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
				//this->q_.enQ(fileSpec + ", line " + std::to_string(lineCnt) + ", " + line);
			}
			lineCnt++;
		}
	}
        return rst;
}

#ifdef TEST_SEARCHCOMP
int main()
{
	std::cout << "  TEST SEARCH COMPONENT\n";
	std::cout << "=========================\n";
	std::vector<std::string> filePatterns;
	filePatterns.push_back("*.h");
	filePatterns.push_back("*.cpp");
	std::string regStr = "(.*?)FileMgrFactory(.*?)";
        
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "\nmain thread " << this_id << " is running" <<std::endl;
        std::cout << "========================================\n\n";
        
	IFileMgr* IfileMgr = FileMgrFactory::CreateFileMgr();
	ISearch* searchInstance = SearchCompFactory::CreateSearchComp();
	searchInstance->setFileMgr(IfileMgr);
	searchInstance->startSearching(".", filePatterns, regStr);
        
        
        std::cout << "\n\nResults: \n";
	std::cout << "=========================\n";
	std::string msg;
	do
	{
            msg = searchInstance->get();
            std::cout << msg << std::endl;
	} while (msg != "EOF");
	return 0;
}
#endif // TEST_SEARCHCOMP


