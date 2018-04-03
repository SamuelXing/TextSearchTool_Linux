#include "FileMgrFactory.h"

IFileMgr* FileMgrFactory::CreateFileMgr() 
{
	return new FileMgr();
}

IFileMgr* CreateFileMgr() 
{
	return new FileMgr();
}

#ifdef TEST_FILEMGR
int main()
{
	std::cout << "  DEMO FILE MANAGER \n";
	std::cout << "=====================\n";

	IFileMgr* fm = FileMgrFactory::CreateFileMgr();


	std::vector<std::string> filePatterns;
	filePatterns.push_back("*.cpp");

	fm->traverseAndEnQ(".", filePatterns);
	return 0;
}
#endif // TEST_FILEMGR
