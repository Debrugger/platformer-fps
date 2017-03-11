#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "../include/sysinc.h"
#include "../include/qtinc.h"
#include "../include/mainwindow.h"
#include "../include/itemlist.h"
#include "../include/errordialog.h"

QApplication* app;
MainWindow* mainwindow_ptr;

ItemList* char_list;
ItemList* map_list;

ErrorDialog* err_dialog;

#endif //__GLOBALS_H
