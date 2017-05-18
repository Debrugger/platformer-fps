#ifndef __ITEM_H
#define __ITEM_H

#include "qtinc.h"
#include "mainwindow.h"
#include "tools.h"

class ItemList;

class Item : public QWidget
{
	Q_OBJECT;
	Item* prev_item;
	Item* next_item;
	ItemList* parent_list;
	int index;

	QGroupBox*			group_box;
	QLabel*				label;
	QLabel*           name_label;
	QLabel*           img_label;
	QPushButton*		img_button;
	QLineEdit*	      img_edit;
	QLabel*           model_label;
	QPushButton*		model_button;
	QLineEdit*	      model_edit;
	QLineEdit*			name_edit;
	QToolButton*	  	delete_button;
	QGraphicsView*    g_view;
	QGraphicsScene*   g_scene;
	QPixmap*          pixmap;

	public:
	Item(ItemList*, MainWindow*, bool, ItemType);
	~Item();
	bool created_from_settings;
	MainWindow* parent_window;

	ItemType type;

	Item* PrevItem()				{ return prev_item;				};
	Item* NextItem()				{ return next_item;				};
	QString Name()					{ return name_edit->text();	};
	QString Model()				{ return model_edit->text();	};
	QString Image()				{ return img_edit->text();		};
	int Index()						{ return index;					};

	void ConnectSettingsSlots();
	void SetupUi();
	void Show();
	void NumberElements();   

	void SetImgText(QString s)		{ img_edit->setText(s);		};
	void SetNameText(QString s)  	{ name_edit->setText(s);	};
	void SetModelText(QString s)	{ model_edit->setText(s);	};

	public slots:
	void DeleteClicked();
	void ImgButtonClicked();
	void ModelButtonClicked();
	void UpdateImage();
	void SettingChanged();
};

class Weapon : public Item
{
	public:
	Weapon(ItemList*, MainWindow*, bool, ItemType);
	~Weapon();
}

#endif //__ITEM_H
