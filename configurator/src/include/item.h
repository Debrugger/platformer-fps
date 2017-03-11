#ifndef __ITEM_H
#define __ITEM_H

#include "../include/qtinc.h"
#include "../include/mainwindow.h"

class Item : public QWidget

class ItemList;
{
	Q_OBJECT;
	Item* prev_item;
	Item* next_item;
	ItemList* parent_list;

	public:
	Item(ItemList*, MainWindow*, bool, ItemType);
	~Item();
	int index;
	bool created_from_settings;
	MainWindow* parent_window;

	ItemType type;
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

	Item* PrevItem()				{ return prev_item;	};
	Item* NextItem()				{ return next_item;	};

	void SetupUi();
	void Show();
	void NumberElements();   

	public slots:
	void DeleteClicked();
	void ImgButtonClicked();
	void ModelButtonClicked();
	void UpdateImage();
	void SettingChanged();
};

#endif //__ITEM_H
