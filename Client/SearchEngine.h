/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SearchEngine.h
 * Author: parallels
 *
 * Created on April 3, 2018, 9:11 AM
 */

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "../SearchComp/ISearch.h"
#include "../FileMgrComp/FileMgrFactory.h"

class ISearchEngine
{
public:
    ISearchEngine(){}
    virtual ~ISearchEngine(){}
    virtual void startSearching(const std::string& path, const std::vector<std::string>& filePatterns, const std::string& reg) = 0;
    virtual bool done() = 0;
};

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
    
    void search() 
    {
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "\nworking thread " << this_id << " is running" <<std::endl;
        std::cout << "========================================\n\n";
	std::array<std::string, 2> record;
	do
	{
            record = this->pFileMgr->get();
            std::cout << "\ncall search component given input: " <<record[0] << ", " << text_ << std::endl;
            std::vector<int> rst = pSearch->scanner(record[0], text_);
            std::cout << "searching output:\n";
            if(rst.size() == 0)
                std::cout << "no line matched\n";
            for(int i=0; i< rst.size(); i++)
                std::cout << "matched line: " << rst[i] << "\n";
            std::cout << "\n";

        } while (record[1] != "EOF");
        this->q_.enQ("EOF");
    }
    
    bool done()
    {
        std::string notify = this->q_.deQ();
        if( notify == "EOF")
            return true;
        else
            return false;
    }
    
private:
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

