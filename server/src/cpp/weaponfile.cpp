#include "sysinc.h"
#include "filereader.h"
#include "weaponfile.h"

#define MAX_WEAPON_DAMAGE		300
#define MAX_WEAPON_MAGAZINE	500
#define MAX_WEAPON_COOLDOWN	10000
#define MAX_WEAPON_RELOAD		10000

//weapon file contents:
//name=
//damage=
//magazine=
//cooldown= (between shots)
//reload= (time)

void WeaponFile::Load(char* filename)
{
	FileReader fr;
	char buffer[FILEREADER_MAX_LINE_LENGTH];
	int line = 0;
	char* eq;
	TempWeapon w;

	try
	{
		if (!fr.Open(filename)) throw ErrorOpeningFile();
		while (fr.ReadLine(buffer))
		{
			line++;
			if (!(eq = strchr(buffer, '=')))
				throw MissingEq();

			switch (buffer[0])
			{
				case 'n':
					//create new weapon or whatever if everything necessary was read
					snprintf(w.name, max_name_length, "%s", ++eq);
					printf("Name of weapon: %s\n", w.name);
					break;
				case 'd':
					if (!(w.damage = atof(++eq)) || w.damage < 0 || w.damage > MAX_WEAPON_DAMAGE) throw BadDamage();
					break;
				case 'm':
					if (!(w.magazine = atof(++eq)) || w.magazine < 0 || w.magazine > MAX_WEAPON_MAGAZINE) throw BadMagazine();
					break;
				case 'c':
					if (!(w.cooldown = atof(++eq)) || w.cooldown < 0 || w.cooldown > MAX_WEAPON_COOLDOWN) throw BadCooldown();
					break;
				case 'r':
					if (!(w.reload = atof(++eq)) || w.reload < 0 || w.reload > MAX_WEAPON_RELOAD) throw BadReload();
					break;
			}
		}
	}
	catch (ErrorOpeningFile& e) { printf("Could not open weapon file %s. Exiting", filename); exit(1); }
	catch (MissingEq& e) { printf("Bad line %d in weapon file %s. Exiting because shit is probably broken.", line, filename); exit(1); }
	catch (BadDamage& e) { printf("Bad damage value in weapon file %s:%d. Exiting because shit is probably broken.", filename, line); exit(1); }
	catch (BadMagazine& e) { printf("Bad magazine value in weapon file %s:%d. Exiting because shit is probably broken.", filename, line); exit(1); }
	catch (BadCooldown& e) { printf("Bad reload value in weapon file %s:%d. Exiting because shit is probably broken.", filename, line); exit(1); }
	catch (BadReload& e) { printf("Bad reload value in weapon file %s:%d. Exiting because shit is probably broken.", filename, line); exit(1); }
}
