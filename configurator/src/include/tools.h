#ifndef __TOOLS_H
#define __TOOLS_H

#include "itemlist.h"
#include "mainwindow.h"

enum ItemType
{
	character,
	map
};

class ItemList;

bool SaveSettings(MainWindow*);
void ReadSettings(MainWindow*);
bool SearchForDuplicates(ItemList*);
bool SearchForEmpty(ItemList*);

#endif //__TOOLS_H
