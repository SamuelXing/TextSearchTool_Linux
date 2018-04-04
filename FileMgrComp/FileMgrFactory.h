//////////////////////////////////////////////////////////////
// FileMgrFactory.h - Factory Method			            //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
///////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* Factory Methods to create an instance of FileMgr.
*
* Required Files:
* ---------------
* "FileMgr.h"
*
* Maintenance History:
* --------------------
* ver 1.0 : 03 Apr 2017
* - first release
*
*/
#pragma once
#ifndef FILEMGRFACTORY_H
#define FILEMGRFACTORY_H
#include "FileMgr.h"

class FileMgrFactory
{
public:
        // -------<factory method>------
	static IFileMgr* CreateFileMgr();
};

extern "C" 
{
    IFileMgr* CreateFileMgr();
}
#endif // !FILEMGRFACTORY_H




