#ifndef __SAVE_DIALOG_H
#define __SAVE_DIALOG_H

#include "qtinc.h"
#include "build/save_dialog.ui.h"
#include "mainwindow.h"

class SaveDialog: public QDialog, public Ui::SaveDialog
{
    Q_OBJECT;
    public:
        SaveDialog(MainWindow*);
        ~SaveDialog();
        MainWindow* parent_window;
    public slots:
        void SaveClicked();
        void DiscardClicked();
		  void on_cancel_button_clicked();
};

#endif //__SAVE_DIALOG_H
