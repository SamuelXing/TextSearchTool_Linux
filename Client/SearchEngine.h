///////////////////////////////////////////////////////////////
// SearchEngine.h - The Client of the TextSearchTool         //
// ver 1.0                                                   //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018      //
///////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* - This package contains the TextSearchEngine class that talks 
* the FileMgr component and the TextSearch component
* - This package contains the main entry of this project
*
* Required Files:
* ---------------
* ../SearchComp/ISearch.h
* ../FileMgrComp/FileMgrFactory.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2018
* - first release
*
*/

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "../SearchComp/ISearch.h"
#include "../FileMgrComp/FileMgrFactory.h"


//////////////////////////////////////////////////////
// Class Definition:
// - define the SearchEngine interface
// Public interfaces:
// =================
// void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg)
// -  start the searching process
class ISearchEngine
{
public:
    ISearchEngine(){}
    virtual ~ISearchEngine(){}
    // ------<start the searching process>-------
    virtual void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) = 0;
    // ------<notify the main thread that the searching process is done>--------
    virtual bool done() = 0;
};

//////////////////////////////////////////////////////
// Class Definition:
// - the definition of SearchEngine class
class SearchEngine: public ISearchEngine {
public:
    SearchEngine()
    {
        pFileMgr = FileMgrFactory::CreateFileMgr();
        pSearch = SearchCompFactory::CreateSearchComp();
    }
    
    virtual ~SearchEngine()
    {
        if (!pFileMgr)
            delete pFileMgr;
        if (!pSearch)
            delete pSearch;
    }

    // ------<start the searching process>-------
    void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) 
    {
	try 
	{
                this->setText(reg);
                t_ = new std::thread(&SearchEngine::search, this);
		this->pFileMgr->traverseAndEnQ(path, filePatterns);
	}
	catch (std::string err) 
	{
		std::cout << err << std::endl;
	}
    }
    
    // ----------<operation that executed with working thread>-----------
    void search() 
    {
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "\nworking thread " << this_id << " is running" <<std::endl;
        std::cout << "========================================\n\n";
	std::array<std::string, 2> record;
	do
	{
            record = this->pFileMgr->get();
            if(record[1]=="EOF")
                break;
            std::cout << "\ncall TextSearch Component given input: " <<record[0] << ", " << text_ << std::endl;
             std::cout << "========================================\n";
            std::vector<int> rst = pSearch->scanner(record[0], text_);
            std::cout << "Output of TextSearch Component:\n";
            if(rst.size() == 0)
                std::cout << "no line matched\n";
            for(int i=0; i< rst.size(); i++)
                std::cout << "matched line: " << rst[i] << "\n";
            std::cout << "\n";

        } while (record[1] != "EOF");
        this->q_.enQ("EOF");
    }
    
    // ------<notify the main thread that the searching process is done>--------
    bool done()
    {
        std::string notify = this->q_.deQ();
        if( notify == "EOF")
            return true;
        else
            return false;
    }
    
private:
    // ----<set the regular expression>-----
    void setText(const std::string& text) 
    {
	text_ = text;
    }
    
private:
    BlockingQueue<std::string> q_;
    IFileMgr * pFileMgr;
    ISearch * pSearch;
    std::thread* t_;
    std::string text_;
    
};

#endif /* SEARCHENGINE_H */

