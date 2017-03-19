#include "common.h"
#include "globals.h"
#include "mainwindow.h"
#include "save_dialog.h"
#include "tools.h"

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
	if (SaveSettings(parent_window))
	{
		parent_window->close();
		app->quit();
	}
	else
		close();
}

void SaveDialog::DiscardClicked()
{
	parent_window->close();
	app->quit();
}

void SaveDialog::on_cancel_button_clicked()
{
	close();
}
