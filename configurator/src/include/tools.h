#ifndef __TOOLS_H
#define __TOOLS_H

enum ItemType
{
	character,
	map
};

void SaveSettings(MainWindow*);
void ReadSettings(MainWindow*);
#endif //__TOOLS_H
