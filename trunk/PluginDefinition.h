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

#ifndef PLUGINDEFINITION_H
#define PLUGINDEFINITION_H

//
// All difinitions of plugin interface
//
#include "PluginInterface.h"

const TCHAR NPP_PLUGIN_NAME[] = TEXT("NppFavorites");
const int nbFunc = 8;

void pluginInit(HANDLE hModule);
void pluginCleanUp();
void commandMenuInit();
void configFileInit();
void commandMenuCleanUp();
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);


void OpenFile0();
void OpenFile1();
void OpenFile2();
void OpenFile3();
void OpenFile4();
void OpenFile5();

void OpenFile(int FileNum);
void ManageFavorites();


#endif //PLUGINDEFINITION_H
