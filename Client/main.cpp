//////////////////////////////////////////////////////////////
// main.cpp - main entry                                    //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
//////////////////////////////////////////////////////////////

#include<iostream>
#include<thread>
#include "SearchEngine.h"

// ------<main entry>--------
int main(int argc, char** argv) 
{
	std::cout << "TextSearchComponent Demonstration\n";
	std::cout << "=================================\n";
        std::string path;
	std::vector<std::string> filePatterns;
	std::string regStr;
        // command line argument parsing
        if(argc < 3){
            std::cout << "Invalid arguments! Usage: client [reg_expression] [path] [patterns] ...\n";
            exit(0);
        }
        else  
        {
            regStr = argv[1];
            path = argv[2];
            for(int i=3; i<argc; i++)
                filePatterns.push_back(argv[i]);
        }
        
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "main thread " << this_id << " is running" <<std::endl;
        std::cout << "========================================\n";
        
	ISearchEngine* pSearchEngine = new SearchEngine();
        pSearchEngine->startSearching(path, filePatterns, regStr);
        
        while(!pSearchEngine->done()){}
        std::cout << "\n\n=================\nend of processing\n";
	return 0;
}

