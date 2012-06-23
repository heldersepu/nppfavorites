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
#include "GoToLineDlg.h"


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


TCHAR iniFilePath[MAX_PATH] = TEXT("::");
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
	
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{
	configFileInit();
	TCHAR FileName[MAX_PATH];	
	::GetPrivateProfileString(sectionName, TEXT("favFile0"), TEXT(""), FileName, MAX_PATH, iniFilePath);
	setCommand(0, FileName, OpenFile0, NULL, false);
	::GetPrivateProfileString(sectionName, TEXT("favFile1"), TEXT(""), FileName, MAX_PATH, iniFilePath);
	setCommand(1, FileName, OpenFile1, NULL, false);
	::GetPrivateProfileString(sectionName, TEXT("favFile2"), TEXT(""), FileName, MAX_PATH, iniFilePath);
	setCommand(2, FileName, OpenFile2, NULL, false);
	::GetPrivateProfileString(sectionName, TEXT("favFile3"), TEXT(""), FileName, MAX_PATH, iniFilePath);
	setCommand(3, FileName, OpenFile3, NULL, false);
	::GetPrivateProfileString(sectionName, TEXT("favFile4"), TEXT(""), FileName, MAX_PATH, iniFilePath);
	setCommand(4, FileName, OpenFile4, NULL, false);
	::GetPrivateProfileString(sectionName, TEXT("favFile5"), TEXT(""), FileName, MAX_PATH, iniFilePath);
	setCommand(5, FileName, OpenFile5, NULL, false);
																			   
	setCommand(nbFunc-2, TEXT("---"), NULL, NULL, false);
	// Shortcut : // bind to the shortcut Alt-F
	ShortcutKey *shKey = new ShortcutKey;
	shKey->_isAlt = true;
	shKey->_isCtrl = false;
	shKey->_isShift = false;
	shKey->_key = 0x46; //VK_F
	setCommand(nbFunc-1, TEXT("Manage Favorites"), ManageFavorites, shKey, false);	
}

void configFileInit()
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
	if (PathFileExists(configFileName) == FALSE)
	{
		::WritePrivateProfileString(sectionName, TEXT("favFile0"), TEXT("C:\\Windows\\System32\\drivers\\etc\\hosts"), iniFilePath);
		::WritePrivateProfileString(sectionName, TEXT("favFile1"), TEXT("C:\\xampp\\php\\php.ini"), iniFilePath);
		::WritePrivateProfileString(sectionName, TEXT("favFile2"), TEXT(""), iniFilePath);
		::WritePrivateProfileString(sectionName, TEXT("favFile3"), TEXT(""), iniFilePath);
		::WritePrivateProfileString(sectionName, TEXT("favFile4"), TEXT(""), iniFilePath);
		::WritePrivateProfileString(sectionName, TEXT("favFile5"), TEXT(""), iniFilePath);	
	}
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

void OpenFile0() { OpenFavFile(TEXT("favFile0")); }
void OpenFile1() { OpenFavFile(TEXT("favFile1")); }
void OpenFile2() { OpenFavFile(TEXT("favFile2")); }
void OpenFile3() { OpenFavFile(TEXT("favFile3")); }
void OpenFile4() { OpenFavFile(TEXT("favFile4")); }
void OpenFile5() { OpenFavFile(TEXT("favFile5")); }

void OpenFavFile(TCHAR* keyName)
{
	try {
		TCHAR FileName[MAX_PATH];
		::GetPrivateProfileString(sectionName, keyName, TEXT(""), FileName, MAX_PATH, iniFilePath);	
		::SendMessage(nppData._nppHandle, NPPM_DOOPEN, 0, (LPARAM)FileName);
	} catch (...) {}
}


//Open the config file
void ManageFavorites()
{
	::SendMessage(nppData._nppHandle, NPPM_DOOPEN, 0, (LPARAM)iniFilePath);
}

