#include "sysinc.h"
#include "qtinc.h"

#include "common.h"
#include "lobby_dialog.h"
#include "item.h"
#include "gl_window.h"


std::vector<Item*> characters;
std::vector<Item*> maps;
int nb_chars = 0;
int nb_maps = 0;

LobbyDialog::LobbyDialog()
{
	setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose);
	setWindowTitle("Lobby");
   
	connect(characterList, SIGNAL(currentRowChanged(int)), this, SLOT(OnCharListChanged()));
	connect(mapList, SIGNAL(currentRowChanged(int)), this, SLOT(OnMapListChanged()));

	characterView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /*no scroll bars in the image*/
	characterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /*no scroll bars in the image*/
	mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	map_edit->setReadOnly(true);
	character_edit->setReadOnly(true);
	log_edit->setReadOnly(true);
	chat_edit->setReadOnly(true);

   char_view_scene = new QGraphicsScene(QRectF(0, 0, characterView->geometry().width(), characterView->geometry().height()), 0);
   map_view_scene = new QGraphicsScene(QRectF(0, 0, mapView->geometry().width(), mapView->geometry().height()), 0);
	try
	{
		ReadSettings();

		for (int i = 0; i < nb_chars; i++)
		{
			characterList->addItem(characters.at(i)->name);
		}

		for (int i = 0; i < nb_maps; i++)
		{
			mapList->addItem(maps.at(i)->name);
		}

		characterList->setCurrentRow(0);
		mapList->setCurrentRow(0);
		std::cout << "b" << std::endl;
	}
	catch(int& i)
	{
		if(i == BrokenConfig)	//20
		{
			LogPrint("Config file is corrupt. Error code 20");
			close();
		}
		throw(FailedToBuild);
	}

}

LobbyDialog::~LobbyDialog()
{
}

void LobbyDialog::resizeEvent(QResizeEvent* ev)
{
	QMainWindow::resizeEvent(ev);

	std::cout << "Resized" << std::endl;
	delete char_view_scene;
	delete map_view_scene;
   char_view_scene = new QGraphicsScene(QRectF(0, 0, characterView->geometry().width(), characterView->geometry().height()), 0);
   map_view_scene = new QGraphicsScene(QRectF(0, 0, mapView->geometry().width(), mapView->geometry().height()), 0);

	UpdateImage(mapView, map_view_scene, map_pixmap, maps.at(mapList->currentRow())->image_path);
	UpdateImage(characterView, char_view_scene, char_pixmap, characters.at(characterList->currentRow())->image_path);

}

void LobbyDialog::LogPrint(const QString& msg)
{
	QDebug db = qDebug();
	db.noquote();
	log_edit->append(msg);
	log_edit->verticalScrollBar()->setValue(log_edit->verticalScrollBar()->maximum());
	db << msg;
}

void LobbyDialog::on_quitButton_clicked()
{
	close();
	static_cast<QApplication *>(QApplication::instance())->quit();
}

void LobbyDialog::UpdateImage(QGraphicsView*& view, QGraphicsScene*& scene, QPixmap& pixmap, QString& path)
{
	scene->clear();
	pixmap.load(path);

	/*make image fit in graphics view*/
	qDebug() << "scene " << path << " width: " << (int)scene->width() << " height " << (int)scene->height();
scene->addPixmap(pixmap.scaled(QSize((int)scene->width(), (int)scene->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	//characterView->fitInView(char_view_scene->itemsBoundingRect(), Qt::KeepAspectRatio); /*scaling works w/o this, with this the image is not scaled properly the first time*/
	view->setScene(scene);
}

void LobbyDialog::OnCharListChanged()
{
	UpdateImage(characterView, char_view_scene, char_pixmap, characters.at(characterList->currentRow())->image_path);
}

void LobbyDialog::OnMapListChanged()
{
	UpdateImage(mapView, map_view_scene, map_pixmap, maps.at(mapList->currentRow())->image_path);
}

void LobbyDialog::ReadSettings()
{
	QSettings settings(config_file_name, QSettings::NativeFormat);
	settings.setIniCodec("UTF-8");

	settings.beginGroup("Characters");
   nb_chars = settings.value("nb").toInt();

	if (nb_chars <= max_number_chars)
	{
		std::cout << nb_chars << std::endl;

		characters.resize(nb_chars);
		for (int i = 0; i < nb_chars; i++)
		{
			characters.at(i) = new Item;
			characters.at(i)->name = settings.value(QString("name%1").arg(i)).toString();
			characters.at(i)->image_path = settings.value(QString("image%1").arg(i)).toString();
			LogPrint("Loaded character " + characters.at(i)->name + " with image " + characters.at(i)->image_path);
		}
	}
	else
	{
		LogPrint(QString("Too many characters in config file, maximum is %1").arg(max_number_chars));
		throw(BrokenConfig);
	}
	settings.endGroup();

	settings.beginGroup("Maps");
   nb_maps = settings.value("nb").toInt();


	if (nb_maps <= max_number_maps)
	{
		maps.resize(nb_maps);
		for (int i = 0; i < nb_maps; i++)
		{
			maps.at(i) = new Item;
			maps.at(i)->name = settings.value(QString("name%1").arg(i)).toString();
			maps.at(i)->image_path = settings.value(QString("image%1").arg(i)).toString();
			LogPrint("Loaded map " + maps.at(i)->name + " with image " + maps.at(i)->image_path);
		}
	}
	else
	{
		LogPrint(QString("Too many maps in config file, maximum is %1").arg(max_number_maps));
		throw(BrokenConfig);
	}
	settings.endGroup();
}

void LobbyDialog::on_gl_button_clicked()
{
	MainWindow*	gl_window;
	gl_window = new MainWindow;
	gl_window->show();
}
