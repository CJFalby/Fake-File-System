#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <filesystem>  // file system needs cpp standard 17 or above.  This is enabled in this project, but if you recreated from scratch, set -std=c++17 flags
#include "item.h"
#include "directory.h" 
#include "file.h"

using namespace std;

const tm convertTime(const filesystem::file_time_type& timestamp)
{
	using namespace chrono;  // just for this function, use chrono to save us prefixing chrono:: everywhere
	system_clock::time_point delta = time_point_cast<system_clock::duration>(timestamp - filesystem::file_time_type::clock::now() + system_clock::now());
	time_t conversion = system_clock::to_time_t(delta);

	tm result;
	localtime_s(&result, &conversion);
	return result;
}
//gets all directories/files from path
directory* const fileEnumerator()
{
	//gets current time
	tm currentTime;
	time_t current = time(NULL);
	localtime_s(&currentTime, &current);

	//creates our 'Root' directory called Drive which is where the start of our fake file system 
	//will be held (aka the intial directories and files start point)
	directory* Root = new directory("Drive", currentTime);

	//root path to enumerate
	const char* path = "C:\\Users\\charl\\OneDrive\\Desktop\\Term 1\\Advanced programming\\Coursework\\File Starting Point";

	// use an implicit iterator to enumerate the path
	for (const filesystem::directory_entry& item : filesystem::directory_iterator(path))
	{
		string name = item.path().filename().string();
		tm timestamp = convertTime(item.last_write_time());
		if (item.is_directory()) // check if this is a directory
		{
			//adds the new directory at the 'starting point' to a list in the root directory
			Root->addChildren(new directory(name, timestamp, Root));
		}
		else
		{
			// get the size of the file - __int64 is just an integer value, but using 64 bits to store it (8 bytes)
			__int64 filesize = item.file_size();
			//adds the new file at the 'starting point' to a list in the root file
			Root->addChildren(new file(name, timestamp, filesize));
		}
	}
	return Root;
}
//display all value in the current directory
void DIR(directory* currentDir)
{
	currentDir->displayChildren();
	cout << "\n";
}
// sort by file size
void sortBySIZE(directory* currentRoot)
{
	currentRoot->sizeOrderChildren();
}
//sort alphabetically by name
void sortByNAME(directory* currentRoot)
{
	currentRoot->nameOrderChildren();
}
//change directory we are 'looking' at 'cd'
directory* changeDIR(directory* currentRoot, string name)
{
	if (name == "\\")
	{
		//while the current directory is not "Drive" get parent
		//until it reaches "Drive" which is our starting directory
		while (currentRoot != currentRoot->getParent())
		{
			currentRoot = currentRoot->getParent();
		}
		return currentRoot;
	}
	else if (name == "..")
	{
		//gets parent of current directory and returns it
		//so we go back a single directory
		return currentRoot->getParent();
	}
	else
	{
		//finds the name the users looking for, if it is a file or doesn't
		//exist they will get an error message, if its a directory it will move to that directory
		item* tempItem = currentRoot->containsItem(name);
		if (tempItem != nullptr)
		{
			directory* tempDir = dynamic_cast<directory*>(tempItem);
			if (tempDir == nullptr)
			{
				cout << "the directory name is invalid.\n";
				return currentRoot;
			}
			return tempDir;
		}
		cout << "the directory name is invalid.\n";
		return currentRoot;
	}
}
//create directory
void makeDIR(directory* currentRoot, string name)
{
	//gets current time
	tm currentTime;
	time_t current = time(NULL);
	localtime_s(&currentTime, &current);

	//create new directory and a pointer to it called newDIR
	directory* newDIR = new directory(name, currentTime, currentRoot);

	currentRoot->addChildren(newDIR);
	//delete newDIR;
}
//create file
void makeFILE(directory* currentRoot, string name)
{
	//gets current time
	tm currentTime;
	time_t current = time(NULL);
	localtime_s(&currentTime, &current);

	//create new directory and a pointer to it called newDIR
	int random = rand() % 10001;
	file* newFILE = new file(name, currentTime, random);

	currentRoot->addChildren(newFILE);
}
//delete file or directory function
void deleteITEM(directory* currentRoot, string name)
{
	currentRoot->removeChildren(name);
}

//main function
int main()
{
#ifdef _DEBUG
	_onexit(_CrtDumpMemoryLeaks);
	//_CrtSetBreakAlloc(292);
#endif
	string userCmd = "";
	directory* currentDir = fileEnumerator();
	list<string> currentpath;
	while (userCmd != "exit")
	{
		directory* currentDirTemp = currentDir;
		string parentName = "";
		//finds the name of all directories within the current path to print out
		while (currentDirTemp != currentDirTemp->getParent())
		{
			currentDirTemp = currentDirTemp->getParent();
			currentpath.push_back(currentDirTemp->getName());
		}

		currentpath.push_back(currentDir->getName());
		cout << "C:";
		for (string dirName : currentpath)
		{
			cout << "\\" << dirName;
		}
		cout << ">";
		getline(cin, userCmd);
		cout << "\n";
		currentpath.clear();

		string cmd = "";
		string name = "";
		bool spaceFound = false;

		//seperates the command and the name
		for (char letter : userCmd)
		{
			if (letter == ' ' && spaceFound == false)
			{
				spaceFound = true;
			}
			else if (spaceFound == false)
			{
				cmd += letter;
			}
			else if (spaceFound = true)
			{
				name += letter;
			}
		}

		//based on the command it will call a different function
		if (cmd == "dir")
		{
			DIR(currentDir);
		}
		else if (cmd == "sortsize")
		{
			sortBySIZE(currentDir);
		}
		else if (cmd == "sortname")
		{
			sortByNAME(currentDir);
		}
		else if (cmd == "cd")
		{
			currentDir = changeDIR(currentDir, name);
		}
		else if (cmd == "mkdir")
		{
			makeDIR(currentDir, name);
		}
		else if (cmd == "mkfile")
		{
			makeFILE(currentDir, name);
		}
		else if (cmd == "del")
		{
			deleteITEM(currentDir, name);
		}
		else if (cmd == "exit")
		{
			delete currentDir;
		}
		else
		{
			//if the command is not valid they get an error message
			cout << "'" << cmd << "'" << " is not a valid command, please try again.\n";
		}
	}
	return 0;
}