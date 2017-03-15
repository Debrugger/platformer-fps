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
		item->SetImgText(settings.value(QString("image%1").arg(i)).toString());
		item->SetModelText(settings.value(QString("model%1").arg(i)).toString());
		item->SetNameText(settings.value(QString("name%1").arg(i)).toString());

		item->ConnectSettingsSlots();
    
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
		item->SetImgText(settings.value(QString("image%1").arg(i)).toString());
		item->SetModelText(settings.value(QString("model%1").arg(i)).toString());
		item->SetNameText(settings.value(QString("name%1").arg(i)).toString());

		item->ConnectSettingsSlots();
    
		item->UpdateImage();
		item->Show();
	}
	settings.endGroup();

}

bool SearchForEmpty(ItemList* il)
{
	Item* i;

	for (i = il->FirstItem(); i; i = i->NextItem())
	{
		if (i->Name() == "" || i->Model() == "" || i->Image() == "")
			return false;
	}

	return true;
}

bool SearchForDuplicates(ItemList* il)
{
	//this not working, never returning false
   Item* i1;
	Item* i2;

	std::cout << "SearchForDuplicates called" << std::endl;

   for (i1 = il->FirstItem(); i1; i1 = i1->NextItem())
	{
		qDebug() << "first loop with i1 " << i1->Name();
		for (i2 = il->FirstItem()->NextItem(); i2; i2 = i2->NextItem())
		{
			qDebug() << "second loop with i2 " << i2->Name();

			if (i2 == i1)
			{
				std::cout << "i2 == i1" << std::endl;
				continue;
			}
			
			if (i2->Name() == i1->Name())
			{
				qDebug() << "same names: " << i1->Name() << " and " << i2->Name();
				return false;
			}
			if (i2->Model() == i1->Model())
			{
				qDebug() << "same models: " << i1->Model() << " and " << i2->Model();
				return false;
			}
			if (i2->Image() == i1->Image())
			{
				qDebug() << "same images: " << i1->Image() << " and " << i2->Image();
				return false;
			}
		}
	}
	return true;
}

void SaveSettings(MainWindow* mw)
{
	const int dupes_c = 1;
	const int dupes_m = 2;
	const int empty_c = 3;
	const int empty_m = 4;

	QSettings settings(config_file_name, QSettings::NativeFormat);
	settings.setIniCodec("UTF-8");
   Item* c;
   Item* m;

   try
	{
		settings.beginGroup("Characters");
		int nb_chars;
		if (char_list->LastItem())
			nb_chars = char_list->LastItem()->Index() + 1;
		else
			nb_chars = 0;
		int nb_maps;
		if (map_list->LastItem())
			nb_maps = map_list->LastItem()->Index() + 1;
		else
			nb_maps = 0;

		settings.setValue("nb", nb_chars);
		settings.endGroup();

		if (!SearchForEmpty(char_list))
			throw(empty_c);
		if (!SearchForDuplicates(char_list))
			throw(dupes_c);
		for (c = char_list->FirstItem(); c; c = c->NextItem())
		{
			settings.beginGroup("Characters");
			settings.setValue(QString("name%1").arg(c->Index()), c->Name());
			settings.setValue(QString("image%1").arg(c->Index()), c->Image());
			settings.setValue(QString("model%1").arg(c->Index()), c->Model());
			settings.endGroup();
		}

		settings.beginGroup("Maps");
		settings.setValue("nb", nb_maps);

		if (!SearchForEmpty(map_list))
			throw(empty_m);
		if (!SearchForDuplicates(map_list))
			throw(dupes_m);

		for (m = map_list->FirstItem(); m; m = m->NextItem())
		{
			settings.setValue(QString("name%1").arg(m->Index()), m->Name());
			settings.setValue(QString("image%1").arg(m->Index()), m->Image());
			settings.setValue(QString("model%1").arg(m->Index()), m->Model());
		}
		settings.endGroup();

		mw->settings_saved = true;
		mw->status_label->setText("Settings Saved!");
	}
	catch(int& e)
	{
		if (e == dupes_c)
		{
			mw->status_label->setText(QString("Error: There are characters with duplicate attributes."));
			std::cout << "dupes chars" << std::endl;
		}
		else if (e == dupes_m)
		{
			mw->status_label->setText(QString("Error: There are maps with duplicate attributes."));
			std::cout << "dupes maps" << std::endl;
		}
		else if (e == empty_c)
		{
			mw->status_label->setText("Error: There are empty fields for characters.");
		}
		else if (e == empty_m)
		{
			mw->status_label->setText("Error: There are empty fields for maps.");
		}
		else 
			mw->status_label->setText("Unknown Error");
	}

}
