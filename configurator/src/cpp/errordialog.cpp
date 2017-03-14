#include "error_dialog.h"

ErrorDialog::ErrorDialog(QString msg)
{
	setupUi(this);
	msg_label->setText(msg);

	connect(repair_button, SIGNAL(clicked()), this, SLOT(RepairConfigFile()));
	connect(delete_button, SIGNAL(clicked()), this, SLOT(DeleteConfigFile()));
}

ErrorDialog::~ErrorDialog()
{
}

void ErrorDialog::on_quit_button_clicked()
{
	close();
}

void ErrorDialog::RepairConfigFile()
{
}

void ErrorDialog::DeleteConfigFile()
{
	QFile config("settings");
	config.remove();
}
