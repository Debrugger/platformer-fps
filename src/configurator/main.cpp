#include <math.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

/* Qt */
#include <QApplication>

#include "main.h"
#include "configurator_ui.h"
#include "../../build/configurator/save_dialog_ui.h"

QApplication* app;
MainWindow* mainwindow_ptr;

ItemList* char_list;
ItemList* map_list;

MainWindow::MainWindow()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose);
	setWindowTitle("Configurator");

	char_scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	settings_saved = true;

	setStyleSheet("QLineEdit[readOnly=\"true\"] {"
			"color: #808080;"
			"background-color: #F0F0F0;"
			"border: 1px solid #B0B0B0;"
			"border-radius: 2px;}");

	connect(quitButton, SIGNAL(clicked()), this, SLOT(QuitClicked()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(SaveClicked()));

	char_list = new ItemList;
	map_list = new ItemList;
}

MainWindow::~MainWindow()
{
}

void ReadSettings(MainWindow* mw)
{
	QSettings settings("settings", QSettings::NativeFormat);
	int nb_chars = 0;
	int nb_maps = 0;

	settings.beginGroup("Characters");
	nb_chars = settings.value("nb_chars").toInt();

	if (nb_chars > max_number_chars)
	{
		mw->status_label->setText("Error in config file, too many characters");
		return;
	}
	for (int i = 0; i < nb_chars; i++)
	{
		Item* item = new Item(char_list, mw, true, character);
		item->img_edit->setText(settings.value(QString("char_image%1").arg(i)).toString());
		item->model_edit->setText(settings.value(QString("char_model%1").arg(i)).toString());
		item->name_edit->setText(settings.value(QString("char_name%1").arg(i)).toString());

		Item::connect(item->img_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
		Item::connect(item->model_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
		Item::connect(item->name_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
    
		item->UpdateImage();
		item->Show();
	}
	settings.endGroup();

	settings.beginGroup("Maps");
	nb_maps = settings.value("nb_maps").toInt();

	if (nb_maps > max_number_maps)
	{
		mw->status_label->setText("Error in config file, too many maps");
		return;
	}
	for (int i = 0; i < nb_maps; i++)
	{
		Item* item = new Item(map_list, mw, true, map);
		item->img_edit->setText(settings.value(QString("map_image%1").arg(i)).toString());
		item->model_edit->setText(settings.value(QString("map_model%1").arg(i)).toString());
		item->name_edit->setText(settings.value(QString("map_name%1").arg(i)).toString());

		Item::connect(item->img_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
		Item::connect(item->model_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
		Item::connect(item->name_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
    
		item->UpdateImage();
		item->Show();
	}
	settings.endGroup();

}

void MainWindow::SaveClicked()
{
	SaveSettings(this);
}

void MainWindow::QuitClicked()
{   
	if (settings_saved)
	{
		close();
		app->quit();
	}
	else
	{
		SaveDialog* sd;
		sd = new SaveDialog(this);
		sd->exec();
	}
}

void MainWindow::on_add_char_button_clicked()
{
	Item* item = new Item(char_list, this, false, character);
	item->Show();

	if (char_list->LastItem()->index == max_number_chars - 1)
		add_char_button->setEnabled(false);
	ScrollBarToBottom(char_scroll_area->verticalScrollBar());
}

void MainWindow::on_add_map_button_clicked()
{
	Item* item = new Item(map_list, this, false, map);
	item->Show();

	if (map_list->LastItem()->index == max_number_chars - 1)
		add_map_button->setEnabled(false);
	ScrollBarToBottom(map_scroll_area->verticalScrollBar());
}

void MainWindow::ScrollBarToBottom(QScrollBar* p)
{
	p->setValue(p->maximum());
}

Item::Item(ItemList* pl, MainWindow* mw, bool created_from_settings, ItemType _type)
{
	parent_list = pl;
	parent_window = mw;
	type = _type;

	next_item = 0;
	prev_item = parent_list->LastItem();

	if (!parent_list->FirstItem())
	{
		parent_list->SetFirstItem(this);
		index = 0;
	}
	else
	{
		parent_list->LastItem()->next_item = this;
		index = prev_item->index + 1;
	}
	parent_list->SetLastItem(this);
	SetupUi();
}

Item::~Item()
{
	if (next_item)
		next_item->prev_item = prev_item;
	else
		parent_list->SetLastItem(prev_item);

	if (prev_item)
		prev_item->next_item = next_item;
	else
		parent_list->SetFirstItem(next_item);
	NumberElements();
	if (parent_list->LastItem() && parent_list->LastItem()->index <= max_number_chars - 1)
	{
		QPushButton* b;
		switch (type)
		{
			case map: b = parent_window->add_map_button; break;
			case character: b = parent_window->add_char_button; break;
		}
		b->setEnabled(true);
	}
}

void Item::SetupUi()
{
   QBoxLayout* item_layout;
	if (type == character)
		item_layout = parent_window->char_vert_layout;
	else if (type == map)
		item_layout = parent_window->map_vert_layout;

	group_box = new QGroupBox();
	group_box->setFixedSize(618, 150);

	label = new QLabel(group_box);
	label->setText(QString(type == character ? "Character #%1" : "Map #%1").arg(index + 1));
	name_label = new QLabel(group_box);
	name_label->setText("Name:");
	name_label->move(10, 110);

	delete_button = new QToolButton(group_box);
	delete_button->setAutoFillBackground(true);
	delete_button->setGeometry(600, 19, 15, 15);
	delete_button->setIcon(QIcon("rc/img/delete.png"));
	delete_button->setIconSize(QSize(40, 40));

	img_edit = new QLineEdit(group_box);
	img_edit->setGeometry(QRect(100, 40, 400, 21));
	img_edit->setReadOnly(true);

	img_button = new QPushButton("Browse", group_box);
	img_button->move(10, 40);

	img_label = new QLabel(group_box);
	img_label->setText("Preview image:");
	img_label->move(10, 25);

	model_edit = new QLineEdit(group_box);
	model_edit->setGeometry(QRect(100, 80, 400, 21)); 
	model_edit->setReadOnly(true);

	model_button = new QPushButton("Browse", group_box);
	model_button->move(10, 80);

	model_label = new QLabel(group_box);
	model_label->setText("Model for character:");
	model_label->move(10, 65);

	name_edit = new QLineEdit(group_box);
	name_edit->setGeometry(QRect(100, 105, 180, 21));

	g_view = new QGraphicsView(group_box);
	g_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	g_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	g_view->setGeometry(QRect(510, 40, 100, 100));
	g_scene = new QGraphicsScene(QRectF(0, 0, g_view->geometry().width(), g_view->geometry().height()), 0);
	pixmap = new QPixmap;

	item_layout->addWidget(group_box);

	connect(delete_button, SIGNAL(clicked()), this, SLOT(DeleteClicked()));
	connect(img_button, SIGNAL(clicked()), this, SLOT(ImgButtonClicked()));
	connect(model_button, SIGNAL(clicked()), this, SLOT(ModelButtonClicked()));
	connect(img_edit, SIGNAL(textChanged(QString)), this, SLOT(UpdateImage()));

	/*created_from_settings says if this object was created while reading the settings. In ReadSettings(), the texts in the lineedits are changed which would trigger these Signals and set settings_saved to false, so if created from settings, these slots will be connected later*/
	if (!created_from_settings)
	{
		connect(img_edit, SIGNAL(textChanged(QString)), this, SLOT(SettingChanged()));
		connect(model_edit, SIGNAL(textChanged(QString)), this, SLOT(SettingChanged()));
		connect(name_edit, SIGNAL(textChanged(QString)), this, SLOT(SettingChanged()));
	}
}

void Item::Show()
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
}                       

void Item::DeleteClicked()
{
	group_box->hide();
	label->hide();
	delete_button->hide();
	delete this;
}

void Item::NumberElements()
{
	int i = 0;
	Item* c;
	c = parent_list->FirstItem();
	while (c)
	{
		c->index = i;
		if (type == character)
			c->label->setText(QString("Character #%1").arg(i + 1));
		else if (type == map)
			c->label->setText(QString("Map #%1").arg(i + 1));
		c = c->next_item;
		i++;
	}
}

void Item::ImgButtonClicked()
{
	QString filename =  QFileDialog::getOpenFileName(this, tr("Open preview image"), app->applicationDirPath(), tr("PNG Images (*.png)"));
	img_edit->setText(filename);
}

void Item::ModelButtonClicked()
{
	QString filename =  QFileDialog::getOpenFileName(this, tr("Open character model"), app->applicationDirPath(), tr("OBJ Files (*.obj)"));
	model_edit->setText(filename);
}

void Item::UpdateImage()
{
	g_scene->clear();
	pixmap->load(img_edit->text());

	/*make image fit in graphics view*/
	g_scene->addPixmap(pixmap->scaled(QSize((int)g_scene->width(), (int)g_scene->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	g_view->setScene(g_scene);
}

void Item::SettingChanged()
{                                        
	parent_window->settings_saved = false;
}

ItemList::ItemList()
{
	first_item = last_item = 0;
}

ItemList::~ItemList()
{
}

void ItemList::SetLastItem(Item* i)
{
	last_item = i;
}

void ItemList::SetFirstItem(Item* i)
{
	first_item = i;
}

SaveDialog::SaveDialog(MainWindow* mw)
{
	parent_window = mw;
	setupUi(this);
	connect(discard_button, SIGNAL(clicked()), this, SLOT(DiscardClicked()));
	connect(save_button, SIGNAL(clicked()), this, SLOT(SaveClicked()));
}

SaveDialog::~SaveDialog()
{
}

void SaveDialog::SaveClicked()
{
	SaveSettings(parent_window);
	parent_window->close();
	app->quit();
}

void SaveDialog::DiscardClicked()
{
	parent_window->close();
	app->quit();
}

void SaveSettings(MainWindow* mw)
{
	QSettings settings("settings", QSettings::NativeFormat);
	settings.setIniCodec("UTF-8");

	settings.beginGroup("Characters");
	settings.setValue("nb_chars", char_list->LastItem()->index + 1);
	for (Item* c = char_list->FirstItem(); c; c = c->NextItem())
	{
		settings.setValue(QString("char_name%1").arg(c->index), c->name_edit->text());
		settings.setValue(QString("char_image%1").arg(c->index), c->img_edit->text());
		settings.setValue(QString("char_model%1").arg(c->index), c->model_edit->text());
	}
	settings.endGroup();

	settings.beginGroup("Maps");
	settings.setValue("nb_maps", map_list->LastItem()->index + 1);
	for (Item* c = map_list->FirstItem(); c; c = c->NextItem())
	{
		settings.setValue(QString("map_name%1").arg(c->index), c->name_edit->text());
		settings.setValue(QString("map_image%1").arg(c->index), c->img_edit->text());
		settings.setValue(QString("map_model%1").arg(c->index), c->model_edit->text());
	}
	settings.endGroup();

	mw->settings_saved = true;
	mw->status_label->setText("Settings Saved!");
}


int main(int c, char*p[])
{
	app = new QApplication(c, p);
	mainwindow_ptr = new MainWindow;
	ReadSettings(mainwindow_ptr);
	mainwindow_ptr->show();
	return app->exec();
}
