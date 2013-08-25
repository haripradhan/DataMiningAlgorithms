/* -------------------
** FileWriter.h
** Hari pradhan
** 09/12/2012
** ------------------*/

#include "FileWriter.h"
#include <fstream>
#include <ostream>
#include <iomanip>
using namespace std;

/**
* Default Constructor
*/
FileWriter::FileWriter(){  

}

/**
* Opens the specified file
* @param fname Filename
*/
void FileWriter::openFile(string fname){
	fileName= fname;
	outStream.open(fileName.c_str());
}

/**
* Writes contents to the file
* @param val Values to be written into the file
*/
void FileWriter::writeFile(vector< vector<double> > val){
	//Check whether file can't be opened
	if( !outStream ) { 
		cerr << "Error: Could not open the file" << endl;
		//exit(1);
	}
	for(int j = 0;j<(int)val[0].size();j++){
		for(int i =0;i<(int)val.size();i++){
			outStream<<setw(12)<<fixed<<setprecision (5)<<val[i][j];
		}
		outStream<<endl;
	}
	outStream.close();
}

/**
* Writes contents to the file along with some header contents
* @param val Values to be written into the file
* @param content Header-content to be written into the file
*/
void FileWriter::writeFile(vector< vector<double> > val, string content){
	//Check whether file can't be opened
	if( !outStream ) {
		cerr << "Error: Could not open the file" << endl;
		//exit(1);
	}
	outStream<<content.c_str()<<endl;
	for(int j = 0;j<(int)val[0].size();j++){
		for(int i =0;i<(int)val.size();i++){
			outStream<<setw(12)<<fixed<<setprecision (5)<<val[i][j];
		}
		outStream<<endl;
	}
	outStream.close();
}

