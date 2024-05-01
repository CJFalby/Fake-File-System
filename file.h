#pragma once
#include "item.h"
class file : public item
{
public:
	file(string objName, tm objDate, double size);
	~file();
	virtual void displaySelf();
	double getSize();
protected:

private:
	double size;
};

//print out the information about a file
inline void file::displaySelf()
{
	cout << date.tm_mday << "/" << date.tm_mon + 1 << "/" << date.tm_year + 1900 << "   " << date.tm_hour << ":" << date.tm_min << ":" << date.tm_sec << "   " << name << "   " << size << "\n";
}