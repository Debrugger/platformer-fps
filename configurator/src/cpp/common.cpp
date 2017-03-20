#include "sysinc.h"
#include "qtinc.h"
#include "common.h"
#include "globals.h"

QString ConfigFile()
{
	try
	{
		QString homedir = QString::fromStdString(std::getenv("HOME"));

		if (homedir == "")
			throw(no_home_env);

		QSettings s(homedir + "/.platformer-fps", QSettings::NativeFormat);
		if (!s.contains("location"))
		{
			throw(no_home_config);
		}
		return s.value("location").toString() + "/" + config_file_name; 
	}

	catch(int& e)
	{
		switch(e)
		{
			case no_home_config:
				{
					QDebug db = qDebug();
					db.noquote();

					db << "Config file in home directory broken or nonexistent. Please run install.sh to create one.";
					app->quit();
					break;
				};
			case no_home_env:
				{
					QDebug db = qDebug();
					db.noquote();

					db << "There was an error getting you $HOME environment variable. Either you don't have one or something went wrong.";
					app->quit();
					break;
				};
		};
	}
}
