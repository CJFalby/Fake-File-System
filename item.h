#pragma once
#include <string>
#include <iostream>

using namespace std;

//the item object contains the attributes that both directory and file share
class item
{
public:
	item(string objName, tm objDate);
	string getName();
	//virtual as it will be used in both file and directory, in slighlty different forms
	virtual void displaySelf() = 0;
private:

protected:
	string name;
	tm date;
};

//inlining getName as its used many times in the program, and is small
inline string item::getName()
{
	return name;
}