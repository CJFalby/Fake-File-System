#include "file.h"

//file constructor
file::file(string objName, tm objDate, double Newsize) : item(objName, objDate), size(Newsize) {

}

file::~file()
{
	cout << name << "\n";
}
double file::getSize()
{
	return size;
}