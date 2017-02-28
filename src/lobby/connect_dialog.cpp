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

#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QLineEdit>

#include <QGraphicsView>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFileDialog>
using namespace std;

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
