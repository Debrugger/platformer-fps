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
const int max_number_maps = 5;

class Item;
class ItemList;

enum ItemType
{
	character,
	map
};

class MainWindow : public QMainWindow, public Ui::ConfiguratorMainWindow  /*Ui:: has to be same as window/widget name in qtcreator .ui file*/
{
    Q_OBJECT;
    public:
    MainWindow();
    virtual ~MainWindow();

    void ReadSettings();
    void ScrollBarToBottom(QScrollBar*);
    QPixmap char_pixmap;
    bool settings_saved;

    public slots:
    void QuitClicked();
    void SaveClicked();
    void on_add_char_button_clicked();
	 void on_add_map_button_clicked();

};

class Item : public QWidget
{
	Q_OBJECT;
	Item* prev_item;
	Item* next_item;
	ItemList* parent_list;
	ItemType type;

	public:
	Item(ItemList*, MainWindow*, bool, ItemType);
	~Item();
	int index;
	bool created_from_settings;
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

class ItemList
{
	Item* first_item;
	Item* last_item;

	public:
	ItemList();
	~ItemList();
	inline Item* FirstItem()	{ return first_item; };
	inline Item* LastItem()		{ return last_item; };
	void SetLastItem(Item*);
	void SetFirstItem(Item*);
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

