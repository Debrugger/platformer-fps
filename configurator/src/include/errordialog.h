#ifndef __ERROR_DIALOG_H
#define __ERROR_DIALOG_H

#include "../include/qtinc.h"
#include "../../build/error_dialog_ui.genh"

class ErrorDialog : public QDialog, public Ui::ErrorDialog
{
	Q_OBJECT;

	public:
	ErrorDialog(QString);
	virtual ~ErrorDialog();

	public slots:
	void on_quit_button_clicked();
	void RepairConfigFile();
	void DeleteConfigFile();
};

#endif //__ERROR_DIALOG_H
