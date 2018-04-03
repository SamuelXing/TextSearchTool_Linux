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

void Search::setFileMgr(IFileMgr* IfileMgr) {
	pFileMgr = IfileMgr;
}

void Search::put(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) 
{
	try 
	{
		if (!this->pFileMgr)
			throw "empty fileMgr pointer";
                this->setText(reg);
                t_ = new std::thread(&Search::search, this);
		this->pFileMgr->traverseAndEnQ(path, filePatterns);
	}
	catch (std::string err) 
	{
		std::cout << err << std::endl;
	}
}

std::string Search::get()
{
	return this->q_.deQ();
}

void Search::put(const std::string& rst) 
{
	this->q_.enQ(rst);
	return;
}

void Search::setText(const std::string& text) 
{
	text_ = text;
}

void Search::search() 
{
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "\n***********************\n";
        std::cout << "working thread " << this_id << " is running" <<std::endl;
        std::cout << "***********************\n\n";
	std::string fileSpec;
	do
	{
            fileSpec = this->pFileMgr->get();
            scanner(fileSpec, text_);
	} while (fileSpec != "EOF");
	this->q_.enQ("END");
}

void Search::scanner(const std::string& fileSpec, const std::string& reg) 
{
	int lineCnt = 1;
	std::regex r(reg);
	std::ifstream ifs(fileSpec);
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
				this->q_.enQ(fileSpec + ", line " + std::to_string(lineCnt) + ", " + line);
			}
			lineCnt++;
		}
	}
}

void Search::scanner(const std::string& fileSpec)
{
    int lineCnt = 1;
	std::regex r(text_);
	std::ifstream ifs(fileSpec);
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
				this->q_.enQ(fileSpec + ", line " + std::to_string(lineCnt) + ", " + line);
			}
			lineCnt++;
		}
	}
}


void Search::done() 
{
	this->q_.enQ("END");
}

#ifdef TEST_SEARCHCOMP
int main()
{
	std::cout << "  TEST SEARCH COMPONENT\n";
	std::cout << "=========================\n";
	std::vector<std::string> filePatterns;
	filePatterns.push_back("*.h");
	filePatterns.push_back("*.cpp");
	std::string regStr = "(.*?)BlockingQueue(.*?)";
        
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "\n***********************\n";
        std::cout << "main thread " << this_id << " is running" <<std::endl;
        std::cout << "***********************\n\n";
        
	IFileMgr* IfileMgr = FileMgrFactory::CreateFileMgr();
	ISearch* searchInstance = SearchCompFactory::CreateSearchComp();
	searchInstance->setFileMgr(IfileMgr);
	searchInstance->put(".", filePatterns, regStr);

	std::cout << "\n\n Results: \n";
	std::cout << "=========================\n";
	std::string msg;
	do
	{
            msg = searchInstance->get();
            std::cout << msg << std::endl;
	} while (msg != "END");

	return 0;
}
#endif // TEST_SEARCHCOMP


