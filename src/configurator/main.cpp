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

using namespace std;

QApplication* app;
MainWindow* mainwindow_ptr;

Item* Item::first_item = 0;
Item* Item::last_item = 0;


MainWindow::MainWindow()
{
    setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_QuitOnClose);
    setWindowTitle("Configurator");

    char_scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setStyleSheet("QLineEdit[readOnly=\"true\"] {"
            "color: #808080;"
            "background-color: #F0F0F0;"
            "border: 1px solid #B0B0B0;"
            "border-radius: 2px;}");

    connect(quitButton, SIGNAL(clicked()), this, SLOT(QuitClicked()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(SaveSettings()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::QuitClicked()
{
    mainwindow_ptr->close();
    app->quit();
}

void MainWindow::ReadSettings()
{
    QSettings settings("settings", QSettings::NativeFormat);
    int nb_chars = 0;

    settings.beginGroup("Characters");
    nb_chars = settings.value("nb_chars").toInt();
    if (nb_chars > max_number_chars)
    {
        status_label->setText("Error in config file, too many characters");
        return;
    }
    for (int i = 0; i < nb_chars; i++)
    {
        Item* item = new Item;
        item->img_edit->setText(settings.value(QString("char_image%1").arg(i)).toString());
        item->model_edit->setText(settings.value(QString("char_model%1").arg(i)).toString());
        item->name_edit->setText(settings.value(QString("char_name%1").arg(i)).toString());
        item->UpdateImage();
        item->Show();
    }
    settings.endGroup();

}

void MainWindow::SaveSettings()
{
    QSettings settings("settings", QSettings::NativeFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup("Characters");
    settings.setValue("nb_chars", Item::LastItem()->index + 1);
    for (Item* c = Item::FirstItem(); c; c = c->NextItem())
    {
        settings.setValue(QString("char_name%1").arg(c->index), c->name_edit->text());
        settings.setValue(QString("char_image%1").arg(c->index), c->img_edit->text());
        settings.setValue(QString("char_model%1").arg(c->index), c->model_edit->text());
    }
    settings.endGroup();

    status_label->setText("Settings Saved!");
}

void MainWindow::on_add_char_button_clicked()
{
    Item* item = new Item;
    item->Show();

    if (item->LastItem()->index == max_number_chars - 1)
        add_char_button->setEnabled(false);
    ScrollBarToBottom();
}

void MainWindow::ScrollBarToBottom()
{
    QScrollBar* p = char_scroll_area->verticalScrollBar();
    p->setValue(p->maximum());
}

Item::Item()
{
    next_item = 0;
    prev_item = last_item;

    if (!first_item)
    {
        first_item = this;
        index = 0;
    }
    else
    {
        last_item->next_item = this;
        index = prev_item->index + 1;
    }
    last_item = this;

    group_box = new QGroupBox();
    group_box->setFixedSize(618, 150);

    label = new QLabel(group_box);
    label->setText(QString("Character #%1").arg(index + 1));
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

    mainwindow_ptr->char_vert_layout->addWidget(group_box);

    connect(delete_button, SIGNAL(clicked()), this, SLOT(DeleteClicked()));
    connect(img_button, SIGNAL(clicked()), this, SLOT(ImgButtonClicked()));
    connect(model_button, SIGNAL(clicked()), this, SLOT(ModelButtonClicked()));
    connect(img_edit, SIGNAL(textChanged(QString)), this, SLOT(UpdateImage()));
}

Item::~Item()
{
    if (next_item)
        next_item->prev_item = prev_item;
    else
        last_item = prev_item;

    if (prev_item)
        prev_item->next_item = next_item;
    else
        first_item = next_item;
    NumberElements();
    if (last_item->index <= max_number_chars - 1)
        mainwindow_ptr->add_char_button->setEnabled(true);
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
    c = first_item;
    while (c)
    {
        c->index = i;
        c->label->setText(QString("Character #%1").arg(i + 1));
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

int main(int c, char*p[])
{
    app = new QApplication(c, p);
    mainwindow_ptr = new MainWindow;
    mainwindow_ptr->ReadSettings();
    mainwindow_ptr->show();
    return app->exec();
}
