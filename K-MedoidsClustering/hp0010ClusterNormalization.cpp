/* -------------------
** hp0010ClusterNormalization.cpp
** Hari Pradhan
** 09/22/2012
** ------------------*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "hp0010ClusterNormalization.h"
//#include "hp0010ClusterParser.h"
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
	//Finding the max min value of each attribute
	int attributeCol=-1;
	//Loops thru all rows (attributes.size()) for each attribute
	for(int i =0;i< (int) parser.getAttributeName().size();i++){
		attributeCol++;
		for( int j = 0;j< (int) attributes.size();j++){
			//Checks whether attribute is class or not
			if(attributes[j].name == parser.getAttributeName()[i]){//  && !attributes[j].isClass){
				//output.push_back(getOutputData(parser,attributeCol, attributes[j].minVal ,attributes[j].maxVal, attributes[j].isClass));
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
* Imposes normalization for the data
* @param parser Parser object
* @param data 2D data which is to be normalized 
* @param isClass True if class attribute is not to be considered for normalization
* @param attributes Attributes 
*/
void Normalization::startNormalization(Parser parser, vector<vector<double> > data, vector <Attribute> attributes,bool isClass){
	normalizedOutput = data;
	//Finding the max min value of each attribute
	int attributeCol=-1;
	string attName="";
	int classAttributeIndex = parser.getClassAttributeIndex();
	//Loops thru all rows (attributes.size()) for each attribute
	for(int i =0;i< (int) parser.getAttributeName().size();i++){
			attributeCol++;
			if(!(i == classAttributeIndex && isClass == true)){
				getOutputData(attributeCol, 0 ,1, false);
			}else{
				getOutputData(attributeCol, 0 ,1, true);
			}
		}
	
	

	//if(!attributes.empty()){
	//	for(int i =0;i< (int) parser.getAttributeName().size();i++){
	//		attributeCol++;
	//		bool isClass = false;
	//		if(parser.getAttributeName()[i] == attributes[0].name){
	//			//Checks whether attribute is class or not
	//			isClass = true;
	//		}
	//		getOutputData(attributeCol, 0 ,1, isClass);
	//	}
	//}
	//else{
	
}


/**
* Finds min and max of an attribute
* @param col Column index of attribute
* @return Vector containing the min and max value of an attribute
*/
vector<double> Normalization::findMinMax(int col){
	vector<double> coldata;
	vector<double> min_max_value;

	for(int i =0;i< (int)normalizedOutput.size();i++){
		coldata.push_back(normalizedOutput[i][col]);
	}
	sort(coldata.begin(),coldata.end());
	min_max_value.push_back(coldata[0]);
	min_max_value.push_back(coldata[coldata.size()-1]);
	coldata.clear();
	return min_max_value;

}

/**
* Gets output data containing normalized data and min max values
* @param attributeNum Attribute number
* @param newminVal New min value
* @param newmaxVal New max value
* @param isClass true if attribute is class attribute else false
*/

void Normalization::getOutputData(int attributeNum,double newminVal,double newmaxVal, bool isClass){

	vector<double> minMaxForAttribute;
	minMaxForAttribute=findMinMax(attributeNum);
	double min = minMaxForAttribute[0];
	double max = minMaxForAttribute[1];
	if(isClass){
		newminVal = min;
		newmaxVal = max;
	}
	findMinMaxNormalization(attributeNum, newminVal , newmaxVal, min, max);

}


/**
* Normalization using the formula: new_value = (new_max - new_min)/(old_max - old_min) * (old_value - old_min) + new_min
* @param col Column index
* @param new_min New min value
* @param new_max New max value 
* @param min Old min value
* @param max Old max value
*/
void Normalization::findMinMaxNormalization(int col, double new_min ,double new_max,double min,double max){

	//Loop thru all values to find new value using normalization formula:
	//new_value = (new_max - new_min)/(old_max - old_min) * (old_value - old_min) + new_min
	for(int i = 0;i < (int)normalizedOutput.size(); i++){
		normalizedOutput[i][col] = (new_max-new_min)/(max-min) * (normalizedOutput[i][col] - min) + new_min;
	}

}


/**
* Gets normalized output
* @return 2D vector of normalized data
*/
vector<vector<double> > Normalization::getNormalizedOutput(){
	return normalizedOutput;
}
