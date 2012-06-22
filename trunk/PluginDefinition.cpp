//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "PluginDefinition.h"
#include "menuCmdID.h"

//
// put the headers you need here
//
#include <stdlib.h>
#include <time.h>
#include <shlwapi.h>
#include "GoToLineDlg.h"

const TCHAR sectionName[] = TEXT("Insert Extesion");
const TCHAR keyName[] = TEXT("doCloseTag");
const TCHAR configFileName[] = TEXT("NppFavorites.ini");

DemoDlg _goToLine;

#ifdef UNICODE 
	#define generic_itoa _itow
#else
	#define generic_itoa itoa
#endif

FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;


TCHAR iniFilePath[MAX_PATH];
bool doCloseTag = false;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
	// Initialize dockable demo dialog
	_goToLine.init((HINSTANCE)hModule, NULL);
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
	::WritePrivateProfileString(sectionName, keyName, doCloseTag?TEXT("1"):TEXT("0"), iniFilePath);
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

	// get path of plugin configuration
	::SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)iniFilePath);

	// if config path doesn't exist, we create it
	if (PathFileExists(iniFilePath) == FALSE)
	{
		::CreateDirectory(iniFilePath, NULL);
	}

	// make your plugin config file full file path name
	PathAppend(iniFilePath, configFileName);

	// get the parameter value from plugin config
	doCloseTag = (::GetPrivateProfileInt(sectionName, keyName, 0, iniFilePath) != 0);

	setCommand(0, TEXT("Hello 0"), OpenFile0, NULL, false);
	setCommand(1, TEXT("Hello 1"), OpenFile1, NULL, false);
	setCommand(2, TEXT("Hello 2"), OpenFile2, NULL, false);
	setCommand(3, TEXT("Hello 3"), OpenFile3, NULL, false);
	setCommand(4, TEXT("Hello 4"), OpenFile4, NULL, false);
	setCommand(5, TEXT("Hello 5"), OpenFile5, NULL, false);
	setCommand(6, TEXT("Hello 6"), OpenFile6, NULL, false);
	setCommand(7, TEXT("Hello 7"), OpenFile7, NULL, false);
	setCommand(8, TEXT("Hello 8"), OpenFile8, NULL, false);
	setCommand(9, TEXT("Hello 9"), OpenFile9, NULL, false);
	setCommand(10, TEXT("Hello 10"), OpenFile10, NULL, false);
	setCommand(11, TEXT("Hello 11"), OpenFile11, NULL, false);
	setCommand(12, TEXT("Hello 12"), OpenFile12, NULL, false);
	setCommand(13, TEXT("Hello 13"), OpenFile13, NULL, false);

	setCommand(nbFunc-2, TEXT("---"), NULL, NULL, false);
	// Shortcut : // bind to the shortcut Alt-F
	ShortcutKey *shKey = new ShortcutKey;
	shKey->_isAlt = true;
	shKey->_isCtrl = false;
	shKey->_isShift = false;
	shKey->_key = 0x46; //VK_F
	setCommand(nbFunc-1, TEXT("Manage Favorites"), ManageFavorites, shKey, false);
}


//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcuts here
	delete funcItem[nbFunc-1]._pShKey;
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

void OpenFile0() { OpenFile(0); }
void OpenFile1() { OpenFile(1); }
void OpenFile2() { OpenFile(2); }
void OpenFile3() { OpenFile(3); }
void OpenFile4() { OpenFile(4); }
void OpenFile5() { OpenFile(5); }
void OpenFile6() { OpenFile(6); }
void OpenFile7() { OpenFile(7); }
void OpenFile8() { OpenFile(8); }
void OpenFile9() { OpenFile(9); }
void OpenFile10() { OpenFile(10); }
void OpenFile11() { OpenFile(11); }
void OpenFile12() { OpenFile(12); }
void OpenFile13() { OpenFile(13); }

void OpenFile(int FileNum)
{
	_goToLine.setParent(nppData._nppHandle);	
}

//Open the config file
void ManageFavorites()
{
	_goToLine.setParent(nppData._nppHandle);	
}

