#include "qtinc.h"
#include "common.h"
#include "globals.h"
#include "item.h"
#include "itemlist.h"
#include "mainwindow.h"
#include "tools.h"

void ReadSettings(MainWindow* mw)
{
	QSettings settings(config_file_name, QSettings::NativeFormat);
	int nb_chars = 0;
	int nb_maps = 0;

	settings.beginGroup("Characters");
	nb_chars = settings.value("nb_chars").toInt();

	if (nb_chars > max_number_chars)
	{
		throw(MainWindow::TooManyChars);
		return;
	}
	for (int i = 0; i < nb_chars; i++)
	{
		Item* item = new Item(char_list, mw, true, character);
		item->img_edit->setText(settings.value(QString("image%1").arg(i)).toString());
		item->model_edit->setText(settings.value(QString("model%1").arg(i)).toString());
		item->name_edit->setText(settings.value(QString("name%1").arg(i)).toString());

		Item::connect(item->img_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
		Item::connect(item->model_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
		Item::connect(item->name_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
    
		item->UpdateImage();
		item->Show();
	}
	settings.endGroup();

	settings.beginGroup("Maps");
	nb_maps = settings.value("nb_maps").toInt();

	if (nb_maps > max_number_maps)
	{
		throw(MainWindow::TooManyMaps);
		return;
	}
	for (int i = 0; i < nb_maps; i++)
	{
		Item* item = new Item(map_list, mw, true, map);
		item->img_edit->setText(settings.value(QString("image%1").arg(i)).toString());
		item->model_edit->setText(settings.value(QString("model%1").arg(i)).toString());
		item->name_edit->setText(settings.value(QString("name%1").arg(i)).toString());

		Item::connect(item->img_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
		Item::connect(item->model_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
		Item::connect(item->name_edit, SIGNAL(textChanged(QString)), item, SLOT(SettingChanged()));
    
		item->UpdateImage();
		item->Show();
	}
	settings.endGroup();

}

bool SearchForDuplicates(Item* i, QSettings& s)
{
	//this not working, never returning false
	std::cout << "dupes called" << std::endl;

	switch(i->type)
	{
		case character:
			{
				s.beginGroup("Characters");
				std::cout << "chars" << std::endl; break;
			}
		case map:
			s.beginGroup("Maps"); break;
	}

	std::cout<< s.value("nb").toInt() << std::endl;
	for (int j = 0; j < s.value("nb").toInt(); j++)
	{
		std::cout << j << std::endl;
		if (i->name_edit->text() == s.value(QString("name%1").arg(j)))
			return false;
		if (i->img_edit->text() == s.value(QString("image%1").arg(j)))
			return false;
		if (i->model_edit->text() == s.value(QString("model%1").arg(j)))
			return false;
	}	

	s.endGroup();
	return true;
}

void SaveSettings(MainWindow* mw)
{
	const int dupes_c = 1;
	const int dupes_m = 2;

	QSettings settings(config_file_name, QSettings::NativeFormat);
	settings.setIniCodec("UTF-8");
   Item* c;
   Item* m;

   try
	{
		settings.beginGroup("Characters");
		int nb_chars;
		if (char_list->LastItem())
			nb_chars = char_list->LastItem()->index + 1;
		else
			nb_chars = 0;
		int nb_maps;
		if (map_list->LastItem())
			nb_maps = map_list->LastItem()->index + 1;
		else
			nb_maps = 0;

		settings.setValue("nb", nb_chars);
		settings.endGroup();
		for (c = char_list->FirstItem(); c; c = c->NextItem())
		{
			if (!SearchForDuplicates(c, settings))
				throw(dupes_c);
			settings.beginGroup("Characters");
			settings.setValue(QString("name%1").arg(c->index), c->name_edit->text());
			settings.setValue(QString("image%1").arg(c->index), c->img_edit->text());
			settings.setValue(QString("model%1").arg(c->index), c->model_edit->text());
			settings.endGroup();
		}

		settings.beginGroup("Maps");
		settings.setValue("nb", nb_maps);
		for (m = map_list->FirstItem(); m; m = m->NextItem())
		{
			if (!SearchForDuplicates(m, settings))
				throw(dupes_m);
			settings.setValue(QString("name%1").arg(m->index), m->name_edit->text());
			settings.setValue(QString("image%1").arg(m->index), m->img_edit->text());
			settings.setValue(QString("model%1").arg(m->index), m->model_edit->text());
		}
		settings.endGroup();

		mw->settings_saved = true;
		mw->status_label->setText("Settings Saved!");
	}
	catch(int e)
	{
		if (e == dupes_c)
		{
			mw->status_label->setText(QString("Character \"%1\" has duplicate attribute").arg(c->name_edit->text()));
			std::cout << "dupes chars" << std::endl;
		}
		else if (e == dupes_m)
		{
			mw->status_label->setText(QString("Map \"%1\" has duplicate attribute").arg(c->name_edit->text()));
			std::cout << "dupes maps" << std::endl;
		}
		else 
			mw->status_label->setText("Unknown Error");
	}

}
