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

   const int max_number_chars = 30;
 	void ReadSettings();

	QPixmap char_pixmap;
public slots:
	void QuitClicked();
	void ButtonClicked(int);
	void SaveSettings();
	void on_add_char_button_clicked();
	void ScrollBarToBottom(int, int);
	
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

	QGroupBox* 		group_box;
	QLabel*			label;
	QLineEdit*		img_edit;
	QLineEdit*		model_edit;
	QPushButton*	img_button;
	QPushButton*	model_button;
	QToolButton*	delete_button;
	static Character* FirstCharacter()	{ return first_character;	};
	static Character* LastCharacter()	{ return last_character;	};
	Character* PrevCharacter()				{ return prev_character;	};
	Character* NextCharacter()				{ return last_character;	};

	void Show()
	{
		group_box->show();
		label->show();
		delete_button->show();
		img_edit->show();    
		model_edit->show();  
		img_button->show();    
		model_button->show();                           
	};                       

	void NumberElements();   

public slots:
	void DeleteClicked();
};

#endif // __MAIN_H

