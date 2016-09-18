#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "main.h"
#include "AppDelegate.h"
#include <platform\CCFileUtils.h>

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance); 
    UNREFERENCED_PARAMETER(lpCmdLine);

	// dirty hack from turtle
	std::string original = FileUtils::getInstance()->getSearchPaths()[0];
	size_t start = original.size() - 7;
	original.replace(start, 7, "/resources/");
	FileUtils::getInstance()->setSearchPaths({ original });

    // create the application instance
	AppDelegate app;
    return Application::getInstance()->run();
}
