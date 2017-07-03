#ifndef __CONNECT_DIALOG_H
#define __CONNECT_DIALOG_H

#include "qtinc.h"
#include "build/connect_dialog.ui.h"

class ConnectDialog : public QDialog, public Ui::ConnectDialog
{
	Q_OBJECT;
public:
	ConnectDialog();
	virtual ~ConnectDialog();
public slots:
	void on_cancel_button_clicked();
};

#endif //__CONNECT_DIALOG_H
