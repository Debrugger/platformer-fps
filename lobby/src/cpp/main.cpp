#include "sysinc.h"
#include "qtinc.h"

#include "lobby_dialog.h"
#include "connect_dialog.h"
#include "main.h"
#include "common.h"

//todo: verify character and map names for duplicates, check if maximum char and map count are exceeded
QApplication* app;
LobbyDialog* lobby_dialog_ptr;
ConnectDialog* connect_dialog_ptr;

void SetStyle(QApplication* a)
{
	a->setStyle(QStyleFactory::create("Fusion"));

	/* stylesheet gist by QuantumCD https://gist.github.com/QuantumCD/6245215 */
	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53,53,53));
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(25,25,25));
	darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Button, QColor(53,53,53));
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

	darkPalette.setColor(QPalette::Highlight, QColor(255, 130, 0));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	a->setPalette(darkPalette);

	a->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

int main(int argc, char *argv[])
{
	try
	{
		app = new QApplication(argc, argv);
		app->setOrganizationName("Platformer FPS");
		app->setApplicationName("Shooter with platforms");

		SetStyle(app); 

		lobby_dialog_ptr = new LobbyDialog;
		connect_dialog_ptr = new ConnectDialog;
		lobby_dialog_ptr->show();
		connect_dialog_ptr->exec();
		return app->exec();
	}
	catch(int& e)
	{
		switch(e)
		{
			case LobbyDialog::FailedToBuild:
				{
					app->quit();
					break;
				}
		}
	}
}
