/* -------------------
** hp0010KfoldFileWriter.h
** Hari Pradhan
** 09/22/2012
** ------------------*/

#include "hp0010KfoldFileWriter.h"
#include "hp0010KfoldParser.h"
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
	for(int j = 0;j<(int)val.size();j++){
		for(int i =0;i<(int)val[0].size();i++){
			outStream<<setw(12)<<fixed<<setprecision (5)<<val[j][i];
		}
		outStream<<endl;
	}
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
	for(int j = 0;j<(int)val.size();j++){
		for(int i =0;i<(int)val[0].size();i++){
			outStream<<setw(3)<<fixed<<setprecision(3)<<(int)val[j][i];
		}
		outStream<<endl;
	}
}

/**
* Writes Confusion matrix to the file along with some header contents
* @param val Values to be written into the file
* @param content Header-content to be written into the file
*/
void FileWriter::writeConfusionMatrix(vector< vector<double> > val,vector<int> rangeOfClass){
	//Check whether file can't be opened
	double totalPrediction=0;
	double correctPrediction=0;
	int widthOfCell = 15;
	int numberOfCells = (rangeOfClass.size() + 1);
	
	outStream <<"\n\n";
	outStream<<getStar(numberOfCells * widthOfCell).c_str()<<"\n";
	outStream<<getBlankSpace(widthOfCell).c_str()<<setw((numberOfCells-2)*widthOfCell)<<"Confusion Matrix"<<
				getBlankSpace(widthOfCell).c_str()<<"\n";
	outStream<<getStar(numberOfCells * widthOfCell).c_str()<<"\n\n";

	outStream << '|'<<getLine(numberOfCells * widthOfCell + numberOfCells *1-1).c_str()<<'|';
	outStream << "\n";
	outStream<<'|'<< getBlankSpace(widthOfCell).c_str();
	outStream << '|' << setw((numberOfCells-1)*widthOfCell +1) << "Predicted Class" << '|'<<"\n";
	for(int i = 0 ; i<numberOfCells; i++){
		outStream << '|'<<getLine(widthOfCell).c_str();
	}
	outStream<<'|'<<"\n";
	outStream <<  '|' << setw(widthOfCell) << "Actual Class";
	if( !outStream ) {
		cerr << "Error: Could not open the file" << endl;
		//exit(1);
	}
	for(int j = 0;j<(int)val.size();j++){
		outStream<<'|'<<setw(widthOfCell)<<rangeOfClass[j];
	}
	outStream << '|'<<"\n";
	for(int i = 0 ; i<numberOfCells; i++){
		outStream << '|'<<getLine(widthOfCell).c_str();
	}
	outStream<<'|'<<"\n";
	for(int j = 0;j<(int)val.size();j++){
		outStream<<'|'<<setw(widthOfCell)<<rangeOfClass[j]<<'|';
		for(int i =0;i<(int)val[0].size();i++){
			if(j == i){
				correctPrediction += (int) val[j][i];
			}
			totalPrediction += (int) val[j][i];
			outStream<<setw(widthOfCell)<<(int)val[j][i]<<'|';
		}
		outStream<<"\n";
		for(int i = 0 ; i<numberOfCells; i++){
			outStream << '|'<<getLine(widthOfCell).c_str();
		}
		outStream<<'|'<<"\n";
		
	}
	outStream<<"\n";
	outStream<<"\n";
	outStream<<"Accuracy of classification: "<< (double)correctPrediction/totalPrediction;
	outStream<<"\n\n";

}

/**
* Writes Decision tree to the file
* @param *nd pointer to the root node
* @param level Level of root node in the tree
*/

void FileWriter::writeTree(node *nd,int level){
	//Check whether file can't be opened
	if( !outStream) {
		cerr << "Error: Could not open the file" << endl;
		//exit(1);
	}
	//cout<<"is not leaf "<<nd->isNotLeaf<<endl;
	if(!nd->isNotLeaf){
		outStream<<"  "<<nd->classValue<<endl;
		//cout<<"  "<<nd->classValue<<endl;
		return;
	}
	outStream<<endl;
	//cout<<endl;
	vector<int> possibleValues;
	possibleValues = nd->decomposeAttribute.possibleValues;

	for(int k = 0 ; k< (int)possibleValues.size(); k++){
		for(int j = 0;j <level;j++){
			outStream<<"|  ";
			//cout<<"|  ";
		}
		outStream<<nd->decomposeAttribute.name.c_str()<<" ="<<possibleValues[k];
		//cout<<nd->decomposeAttribute.name.c_str()<<"["<<nd->decomposeAttribute.key<<"]"<<" ="<<possibleValues[k];
		writeTree(nd->child[k],nd->child[k]->level);
	}
	
}

/**
* Closes the output stream
*/
void FileWriter::closeStream(){
	if(outStream.is_open()){
		outStream.close();
	}
}

/**
* Gets the line of fixed width
* @param width width of the line
*/

string FileWriter::getLine(int width){
	string line="";
	for(int i = 0 ; i < width ; i ++){
		line += "-";
	}
	return line;
}

/**
* Gets the star of fixed width
* @param width width of the line
*/

string FileWriter::getStar(int width){
	string line="";
	for(int i = 0 ; i < width ; i ++){
		line += "*";
	}
	return line;
}

/**
* Gets the blank space of fixed width
* @param width width of the line
*/

string FileWriter::getBlankSpace(int width){
	string line="";
	for(int i = 0 ; i < width ; i ++){
		line += " ";
	}
	return line;
}
