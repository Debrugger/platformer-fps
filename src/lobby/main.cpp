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

#include <QApplication>

#include "main.h"
#include "../../build/lobby/lobby_dialog_ui.h"
#include "../../build/lobby/connect_dialog_ui.h"

using namespace std;

QApplication* app;

LobbyDialog* lobby_dialog_ptr;
ConnectDialog* connect_dialog_ptr;

int main(int c, char *p[])
{
	app = new QApplication(c, p);
   app->setOrganizationName("Platformer FPS");
	app->setApplicationName("Shooter with platforms");

	lobby_dialog_ptr = new LobbyDialog;
	connect_dialog_ptr = new ConnectDialog;
	lobby_dialog_ptr->show();
	connect_dialog_ptr->exec();
	app->exec();
	return 0;
}
