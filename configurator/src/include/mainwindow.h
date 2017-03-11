#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "../include/qtinc.h"
#include "../include/mainwindow_ui.h"

class MainWindow : public QMainWindow, public Ui::ConfiguratorMainWindow  /*Ui:: has to be same as window/widget name in qtcreator .ui file*/
{
    Q_OBJECT;

    public:
    MainWindow();
    virtual ~MainWindow();

    void ReadSettings();
    void ScrollBarToBottom(QScrollBar*);
    QPixmap char_pixmap;
    bool settings_saved;

	 static const int TooManyChars = 31;
	 static const int TooManyMaps = 32;

    public slots:
    void QuitClicked();
    void SaveClicked();
    void on_add_char_button_clicked();
	 void on_add_map_button_clicked();

};

#endif //__MAINWINDOW_H
