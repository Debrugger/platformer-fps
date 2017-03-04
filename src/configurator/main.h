#ifndef __MAIN_H
#define __MAIN_H
#include <QApplication>
#include <QMainWindow>
#include <QDebug>

#include <QSignalMapper>
#include <QWidget>
#include <QLabel>
#include <QSettings>
#include <QPushButton>
#include <QToolButton>
#include <QString>
#include <QLineEdit>
#include <QPixmap>
#include <QFileDialog>
#include <QScrollBar>
#include <QGraphicsView>

#include "configurator_ui.h"
#include "../../build/configurator/save_dialog_ui.h"

const int max_number_chars = 30;

class MainWindow : public QMainWindow, public Ui::ConfiguratorMainWindow  /*Ui:: has to be same as window/widget name in qtcreator .ui file*/
{
    Q_OBJECT;
    public:
    MainWindow();
    virtual ~MainWindow();

    void ReadSettings();
    void ScrollBarToBottom();
    QPixmap char_pixmap;
    bool settings_saved;

    public slots:
    void QuitClicked();
    void SaveClicked();
    void on_add_char_button_clicked();

};

class Item : public QWidget
{
    Q_OBJECT;
    static Item* first_item;
    static Item* last_item;
    Item* prev_item;
    Item* next_item;

    public:
    Item(MainWindow*, bool);
    ~Item();
    int index;
    MainWindow* parent_window;

    QGroupBox* 	        group_box;
    QLabel*		label;
    QLabel*             name_label;
    QLabel*             img_label;
    QPushButton*	img_button;
    QLineEdit*	        img_edit;
    QLabel*             model_label;
    QPushButton*	model_button;
    QLineEdit*	        model_edit;
    QLineEdit*          name_edit;
    QToolButton*	delete_button;
    QGraphicsView*      g_view;
    QGraphicsScene*     g_scene;
    QPixmap*            pixmap;

    static Item* FirstItem()	{ return first_item;	};
    static Item* LastItem()	{ return last_item;	};
    Item* PrevItem()				{ return prev_item;	};
    Item* NextItem()				{ return next_item;	};

    void Show()
    {
        group_box->show();
        label->show();
        name_label->show();
        delete_button->show();
        img_edit->show();    
        model_edit->show();  
        img_button->show();    
        model_button->show();                           
        img_label->show();
        model_label->show();
        name_edit->show();
        g_view->show();
    };                       

    void NumberElements();   

    public slots:
        void DeleteClicked();
        void ImgButtonClicked();
        void ModelButtonClicked();
        void UpdateImage();
        void SettingChanged();
};

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

void SaveSettings(MainWindow*);
#endif // __MAIN_H

