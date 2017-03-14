#include "sysinc.h"
#include "qtinc.h"
#include "globals.h"
#include "common.h"
#include "mainwindow.h"
#include "tools.h"
#include "error_dialog.h"

MainWindow* mainwindow_ptr;
QApplication* app;
ItemList* char_list;
ItemList* map_list;
ErrorDialog* err_dialog;

int main(int c, char*p[])
{
	try
	{
		app = new QApplication(c, p);
		mainwindow_ptr = new MainWindow;
		ReadSettings(mainwindow_ptr);
		mainwindow_ptr->show();
		return app->exec();
	}
	catch(int& e)
	{
		switch(e)
		{
			case MainWindow::TooManyChars:
				{
					err_dialog = new ErrorDialog(QString("Too many player characters. The maximum is %1").arg(max_number_chars));
					err_dialog->exec();
					break;
				};
			case MainWindow::TooManyMaps:
				{
					err_dialog = new ErrorDialog(QString("Too many player maps. The maximum is %1").arg(max_number_maps));
					err_dialog->exec();
					break;
				};
		};
	}
}
