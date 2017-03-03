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

#include "configurator_ui.h"

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

class Character : public QWidget
{
	Q_OBJECT;
	static Character* first_character;
	static Character* last_character;
   Character* prev_character;
	Character* next_character;

public:
	Character();
   ~Character();
	int index;

	QGroupBox* 	group_box;
	QLabel*		label;
        QLabel*         name_label;
        QLabel*         img_label;
	QPushButton*	img_button;
	QLineEdit*	img_edit;
        QLabel*         model_label;
	QPushButton*	model_button;
	QLineEdit*	model_edit;
        QLineEdit*      name_edit;
	QToolButton*	delete_button;
	static Character* FirstCharacter()	{ return first_character;	};
	static Character* LastCharacter()	{ return last_character;	};
	Character* PrevCharacter()				{ return prev_character;	};
	Character* NextCharacter()				{ return next_character;	};

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
	};                       

	void NumberElements();   

public slots:
	void DeleteClicked();
        void ImgButtonClicked();
        void ModelButtonClicked();
};

#endif // __MAIN_H

