/* -------------------
** hp0010ClusterFileWriter.cpp
** Hari Pradhan
** 09/22/2012
** ------------------*/

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
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

};

#endif
