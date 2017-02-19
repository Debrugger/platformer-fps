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

#include "configurator.h"
#include "configurator_ui.h"

using namespace std;

QApplication* app;
MainWindow* mainwindow_ptr;

MainWindow::MainWindow()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose);
	setWindowTitle("Configurator");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(QuitClicked()));
}

void MainWindow::QuitClicked()
{
	mainwindow_ptr->close();
	app->quit();
}

MainWindow::~MainWindow()
{
}

int main(int c, char*p[])
{
	app = new QApplication(c, p);

   mainwindow_ptr = new MainWindow;
	mainwindow_ptr->show();
	return app->exec();
}
//also der soll wenns eine gibt die config laden, alles in die felder schreiben
//wenn nich gibt halt nicht
//dann die pfad strings in ne config file schreiben
