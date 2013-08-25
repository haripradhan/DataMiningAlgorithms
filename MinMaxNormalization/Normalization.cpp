/* -------------------
** Normalization.cpp
** Hari pradhan
** 09/12/2012
** ------------------*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Normalization.h"
//#include "Parser.h"
using namespace std;

/**
* Imposes normalization for the data
* @param attributes Attributes 
* @param inputFile Name of the file
*/
void Normalization::startNormalization(vector<Attribute>attributes,string inputFile){
	Parser parser;
	//Reads file and start parsing
	parser.read(inputFile);
	//Gets header contents (includes @relation, @attribute, @data)
	headerContentOutput = parser.getHeaderContent();
	//Finding the max min value of each attribute
	int attributeCol=-1;
	//Loops thru all rows (attributes.size()) for each attribute
	for(int i =0;i< (int) parser.getAttributeName().size();i++){
		attributeCol++;
		for( int j = 0;j< (int) attributes.size();j++){
			//Checks whether attribute is class or not
			if(attributes[j].name == parser.getAttributeName()[i]){//  && !attributes[j].isClass){
				output.push_back(getOutputData(parser,attributeCol, attributes[j].minVal ,attributes[j].maxVal, attributes[j].isClass));
			}
		}
	}

	/*for each(string atrName in parser.getAttributeName()){
	attributeCol++;
	for each ( Attribute atr in attributes){
	if(atr.name == atrName && !atr.isClass){
	output.push_back(getOutputData(parser,attributeCol, atr.minVal ,atr.maxVal));
	}
	}
	}*/
}

/**
* Finds min and max of an attribute
* @param value 2D vector containing data values to be normalized
* @param col Column index
* @return Vector containing the min and max value of an attribute
*/
vector<double> Normalization::findMinMax(vector <vector <double> > value, int col){
	vector<double> coldata;
	vector<double> min_max_value;
	for(int i =0;i< (int)value.size();i++){
		coldata.push_back(value[i][col]);
	}
	//Sorts data to find min and max value
	//index 0 - minimum value
	//index 1 - maximum value
	sort(coldata.begin(),coldata.end());
	min_max_value.push_back(coldata[0]);
	min_max_value.push_back(coldata[coldata.size()-1]);
	coldata.clear();
	return min_max_value;
}

/**
* Get output data containing normalized data and min max values
* @param parser Object of parser
* @param attributeNum Attribute number
* @param newminVal New min value
* @param newmaxVal New max value
* @return Output Data containing normalized data and min max values
*/
OutputData Normalization::getOutputData(Parser parser, int attributeNum,double newminVal, double newmaxVal, bool isClass){
	OutputData out;
	//Sets minmax and normalized values of each attribute to Output object
	out.setMinMax(findMinMax(parser.getData(),attributeNum));
	if(isClass){
		newminVal = out.getMinMax()[0];
		newmaxVal= out.getMinMax()[1];
	}
	out.setNormalizedData(findMinMaxNormalization(parser.getData(), attributeNum, newminVal , newmaxVal, out.getMinMax()[0],  out.getMinMax()[1]));
	return out;
}

/**
* Normalization using the formula: new_value = (new_max - new_min)/(old_max - old_min) * (old_value - old_min) + new_min
* @param value 2D Vector containing the original data values
* @param col Column index
* @param new_min New min value
* @param new_max New max value 
* @param min Old min value
* @param max Old max value
* @return Vector containing normalized data of an attribute
*/
vector<double> Normalization::findMinMaxNormalization(vector<vector <double> > value, int col, double new_min, double new_max, double min, double max){
	vector<double> normalize_data;
	double newvalue;
	//Loop thru all values to find new value using normalization formula:
	//new_value = (new_max - new_min)/(old_max - old_min) * (old_value - old_min) + new_min
	for(int i = 0;i < (int)value.size(); i++){
		newvalue = (new_max-new_min)/(max-min) * (value[i][col] - min) + new_min;
		normalize_data.push_back(newvalue);
	}
	return normalize_data;
}

/**
* Gets the output data containing normalized data and min-max values
* @return Vector of output data containing normalized data and min-max values
*/
vector<OutputData> Normalization::getOuput(){
	return output;
}

/**
* Gets the header content to be written in the output file
* @return String of header content
*/
string Normalization::getHeaderContentOutput(){
	return headerContentOutput;
}
