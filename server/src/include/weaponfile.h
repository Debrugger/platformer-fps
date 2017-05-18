#ifndef __WEAPONFILE_H
#define __WEAPONFILE_H

#define FILEREADER_MAX_LINE_LENGTH 8192

namespace WeaponFile
{
	const int max_name_length = 32;
	void Load(char* filename);
	struct TempWeapon
	{
		char name[max_name_length];
		short damage;
		short magazine;
		short cooldown;
		short reload;
	};

	class ErrorOpeningFile {};
	class MissingEq {};
	class BadDamage {};
	class BadMagazine {};
	class BadCooldown {};
	class BadReload {};
}

#endif //__WEAPONFILE_H
