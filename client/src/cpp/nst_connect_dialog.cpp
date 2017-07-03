#include "qtinc.h"
#include "connect_dialog.h"

ConnectDialog::ConnectDialog()
{
	setupUi(this); 
	setWindowTitle("Connect to server");
	resize(281, 174);
}

ConnectDialog::~ConnectDialog()
{
}

void ConnectDialog::on_cancel_button_clicked()
{
	close();
}
