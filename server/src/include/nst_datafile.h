#ifndef __DATA_FILE_H
#define __DATA_FILE_H


namespace DataFile 
{
	struct ErrOpenFile { String file; ErrOpenFile(String f) : file(f) {}; };
	struct BadValue { String val; BadValue(String v) : val(v) {}; };

   struct ConfigValue;
	typedef Hashmap<ConfigValue> ConfigBlock;
	typedef std::vector<ConfigBlock*> ConfigBlockList;

	ConfigBlock ParseNextBlock(FileReader& fr);
	ConfigBlockList ParseNextSection(FileReader& fr);
}

struct DataFile::ConfigValue
{
	String val;
	
public:
	void Set(String s)         { val = s; };
	String GetString()        { return val; };
	int GetInt() const         { return atoi(val.CStr()); };
	double GetDouble() const   { return atof(val.CStr()); };
	int* GetIntArr() const;
	double* GetDoubleArr() const;

	void operator=(String s)   { val = s; };
};

#endif //__DATA_FILE_H
