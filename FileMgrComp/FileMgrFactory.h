/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileMgrFactory.h
 * Author: parallels
 *
 * Created on April 2, 2018, 5:12 PM
 */

#pragma once
#ifndef FILEMGRFACTORY_H
#define FILEMGRFACTORY_H
#include "FileMgr.h"

class FileMgrFactory
{
public:
	static IFileMgr* CreateFileMgr();
};

extern "C" 
{
    IFileMgr* CreateFileMgr();
}
#endif // !FILEMGRFACTORY_H




