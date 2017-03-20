#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "sysinc.h"
#include "qtinc.h"
#include "mainwindow.h"
#include "itemlist.h"
#include "error_dialog.h"

extern QApplication* app;
extern MainWindow* mainwindow_ptr;

extern ItemList* char_list;
extern ItemList* map_list;

extern ErrorDialog* err_dialog;

#endif //__GLOBALS_H
