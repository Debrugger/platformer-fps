#include "sysinc.h"
#include "qtinc.h"
#include "globals.h"
#include "itemlist.h"
#include "common.h"
#include "tools.h"
#include "save_dialog.h"
#include "item.h"

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

	if (char_list->LastItem()->Index() == max_number_chars - 1)
		add_char_button->setEnabled(false);
	ScrollBarToBottom(char_scroll_area->verticalScrollBar());
}

void MainWindow::on_add_map_button_clicked()
{
	Item* item = new Item(map_list, this, false, map);
	item->Show();

	if (map_list->LastItem()->Index() == max_number_chars - 1)
		add_map_button->setEnabled(false);
	ScrollBarToBottom(map_scroll_area->verticalScrollBar());
}

void MainWindow::ScrollBarToBottom(QScrollBar* p)
{
	p->setValue(p->maximum());
}
