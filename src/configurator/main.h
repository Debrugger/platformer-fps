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
    public slots:
        void QuitClicked();
    void SaveSettings();
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
    Item();
    ~Item();
    int index;

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
//        void ImgTextChanged();
};

class Character: public Item
{
    static Item* first_character;
    static Item* last_character;
    static Item* FirstCharacter()	{ return first_character;	};
    static Item* LastCharacter()	{ return last_character;	};
};

#endif // __MAIN_H

