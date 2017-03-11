#include "../include/sysinc.h"
#include "../include/qtinc.h"
#include "../include/globals.h"

#include "../inlude/mainwindow.h"
#include "../inlude/tools.h"
#include "../inlude/errordialog.h"

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
