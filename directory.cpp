#include "directory.h"
#include <iostream>
#include <string>

using namespace std;

//we have two constructors as directory can have no parent...
directory::directory(string objName, tm objDate) : item(objName, objDate)
{

}
//... or have a parent (although almost all directories will have a parent)
directory::directory(string objName, tm objDate, directory* NewParent) : item(objName, objDate), Parent(NewParent)
{

}
directory::~directory()
{
	cout << name << "\n";
	for (item* child : dirChildren) 
	{
		if (dynamic_cast<directory*>(child) == nullptr) 
		{
			delete (dynamic_cast<file*>(child));
		}
		else
		{
			delete (dynamic_cast<directory*>(child));
		}
	}
}
//children of directory are item pointers of a directory or file
//this adds them to 'dirChildren'
//i didnt inline this as it is not called too often
void directory::addChildren(item* newChild)
{
	dirChildren.push_back(newChild);
}

//i also didn't inline the functions below, as they're not called too often
item* directory::containsItem(string name)
{
	for (item* currentChild : dirChildren)
	{
		if (currentChild->getName() == name)
		{
			return currentChild;
		}
	}
	return nullptr;
}
void directory::removeChildren(string name)
{
	for (item* currentChild : dirChildren)
	{
		if (currentChild->getName() == name)
		{
			dirChildren.remove(currentChild);
			return;
		}
	}
}
//i didn't inline the functions below as i deemed them to be too long
//this function does not work correctly
void directory::sizeOrderChildren()
{
	file* fileSortArray1[100];
	list<file*> fileSortList2;

	for (item* currentChild : dirChildren)
	{
		directory* currentChildTemp = dynamic_cast<directory*>(currentChild);
		int count = 0;
		if (currentChildTemp == nullptr)
		{
			//adds file to list/array
			file* currentChildFile = dynamic_cast<file*>(currentChild);
			fileSortArray1[count] = currentChildFile;
			fileSortList2.push_back(currentChildFile);
			count++;
		}
		else
		{
			//its a directory
			dirChildren.push_front(currentChildTemp);
		}
		dirChildren.remove(currentChild);
	}
	/*for (file* currentFile : fileSortList)
	{
		currentFile->getSize();
	}*/
	//here i'm using bubblesort to sort the data
	int i, j;
	int n = fileSortList2.size();
	bool swapValue;
	for (i = 0; i < n - 1; i++) {
		swapValue = false;
		for (j = 0; j < n - i - 1; j++) 
		{
			//cannot access getSize()?
			if (fileSortArray1[j]->getSize() > fileSortArray1[j + 1]->getSize())
			{
				file* temp = fileSortArray1[j];
				fileSortArray1[j] = fileSortArray1[j + 1];
				fileSortArray1[j + 1] = temp;
				swapValue = true;
			}
		}
		if (swapValue == false)
		{ 
			break;
		}
	}
	for (file* fileChild : fileSortArray1) 
	{
		dirChildren.push_back(fileChild);
	}
}
//this function is incomplete and does not work
void directory::nameOrderChildren()
{
	//char x = 'x';
	//cout << (int)x;

	//for (item* currentChild : dirChildren)
	//{
	//	for (char l)
	//	string currentName = currentChild->getName();
	//	//names.push_back(currentName);
	//}
	file* fileSortArray1[100];
	int letterValues1[20];
	int letterValues2[20];
	list<file*> fileSortList2;

	for (item* currentChild : dirChildren)
	{
		directory* currentChildTemp = dynamic_cast<directory*>(currentChild);
		int count = 0;
		if (currentChildTemp == nullptr)
		{
			//adds file to list/array
			file* currentChildFile = dynamic_cast<file*>(currentChild);
			fileSortArray1[count] = currentChildFile;
			fileSortList2.push_back(currentChildFile);
			count++;
		}
		else
		{
			//its a directory
			dirChildren.push_front(currentChildTemp);
		}
		dirChildren.remove(currentChild);
	}
	int i, j;
	int n = fileSortList2.size();
	bool swapValue;
	for (i = 0; i < n - 1; i++) {
		swapValue = false;
		for (j = 0; j < n - i - 1; j++)
		{
			int count = 0;
			for (char letter : (fileSortArray1[j]->getName()))
			{
				//gives the ASCII value of letter
				letterValues1[count] = ((int)letter);
			}
			for (char letter : (fileSortArray1[j + 1]->getName()))
			{
				//gives the ASCII value of letter
				letterValues2[count] = ((int)letter);
			}
			if (letterValues1[j] > letterValues2[j + 1])
			{
				file* temp = fileSortArray1[j];
				fileSortArray1[j] = fileSortArray1[j + 1];
				fileSortArray1[j + 1] = temp;
				swapValue = true;
			}
		}
		if (swapValue == false)
		{
			break;
		}
	}
	for (file* fileChild : fileSortArray1)
	{
		dirChildren.push_back(fileChild);
	}
}