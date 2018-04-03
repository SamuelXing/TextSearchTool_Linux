/* 
 * File:   main.cpp
 * Author: parallels
 *
 * Created on April 2, 2018, 3:50 PM
 */

#include<iostream>
#include<thread>
#include "../TextSearchComp/ISearch.h"

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
        std::cout << "\n***********************\n";
        std::cout << "main thread " << this_id << " is running" <<std::endl;
        std::cout << "***********************\n\n";
        
	IFileMgr* IfileMgr = FileMgrFactory::CreateFileMgr();
	ISearch* searchInstance = SearchCompFactory::CreateSearchComp();
	searchInstance->setFileMgr(IfileMgr);
	searchInstance->put(path, filePatterns, regStr);

	std::cout << "\n\n  Results: \n";
	std::cout << "=========================\n";
	std::string msg;
	do
	{
            msg = searchInstance->get();
            std::cout << msg << std::endl;
	} while (msg != "END");

	return 0;
}

