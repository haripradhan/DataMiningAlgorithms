/* -------------------
** hp0010KfoldFileWriter.cpp
** Hari Pradhan
** 09/22/2012
** ------------------*/

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include "hp0010KfoldParser.h"
using namespace std;

/**FileWriter writes the contents to the file
*/
class FileWriter{
private:
	string fileName;        //Name of the file
	ofstream outStream;     //Output stream 
public:
	//Default Constructor
	FileWriter();

	//Destructor
	~FileWriter(){};

	//Opens the specified file
	void openFile(string);

	//Writes contents to the file
	void writeFile(vector< vector<double> >);

	//Writes contents to the file along with some header contents
	void writeFile(vector< vector<double> >, string);

	//Gets line of fixed width
	string getLine(int);

	//Gets star of fixed width
	string getStar(int);

	//Gets blank space of fixed width
	string getBlankSpace(int);

	//Writes decision tree in the file
	void writeTree(node *nd,int level);

	//Closes the file stream
	void closeStream();

	//Writes Confusion Matrix in the file
	void writeConfusionMatrix(vector<vector<double> >,vector<int>);
};

#endif
