#pragma once
#include <string>
#include "item.h"
//this is bad encapsulation, but this is only used for the sizeOrderChildren 
//and nameOrderChildren funstions
//i did this as i ran out of time to find a better way to complete these functions
#include "file.h"
#include <list>

using namespace std;

class directory : public item
{
public:
	directory(string objName, tm objDate);
	directory(string objName, tm objDate, directory* NewParent);
	~directory();

	void addChildren(item* newChild);
	virtual void displaySelf();

	void displayChildren();
	directory* getParent();

	item* containsItem(string name);
	void removeChildren(string name);

	void sizeOrderChildren();
	void nameOrderChildren();
private:
	list<item*> dirChildren;
	directory* Parent = this;
};

//prints out the information about a directory
inline void directory::displaySelf()
{
	cout << date.tm_mday << "/" << date.tm_mon + 1 << "/" << date.tm_year + 1900 << "   " << date.tm_hour << ":" << date.tm_min << ":" << date.tm_sec << "   " << name << "\n";
}
inline void directory::displayChildren()
{
	for (item* currentChild : dirChildren)
	{
		currentChild->displaySelf();
	}
}
inline directory* directory::getParent()
{
	return Parent;
}