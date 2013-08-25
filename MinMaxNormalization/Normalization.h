/* -------------------
** Normalization.h
** Hari pradhan
** 09/12/2012
** ------------------*/

#include <iostream>
#ifndef NORMALIZATION_H
#define NORMALIZATION_H
#include<vector>
#include "OutputData.h"
#include "Parser.h"
using namespace std;

class Normalization{

private:
	vector<OutputData> output;
	string headerContentOutput;
	bool isTrainData;
	bool isTestData;
public:
	//Default Constructor
	Normalization(){}

	//Destructor
	~Normalization(){}

	//Start normalization of the data
	void startNormalization(vector<Attribute>attributes,string);

	//Finds minimum and maximum value of the attribute 	
	vector<double> findMinMax(vector< vector<double> >, int);

	//Normalize the data using Min-Max Normalization
	vector<double> findMinMaxNormalization(vector<vector <double> >, int, double , double , double , double );

	//Get output data containing normalized data and min max values
	OutputData getOutputData(Parser, int, double, double, bool);

	//Gets the output data containing normalized data and min-max values
	vector<OutputData> getOuput();

	//Gets the header content to be written in the output file
	string getHeaderContentOutput();
};

#endif
