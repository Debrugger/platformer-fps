#include "../include/qtinc.h"
#include "../../build/save_dialog_ui.genh"

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
};
