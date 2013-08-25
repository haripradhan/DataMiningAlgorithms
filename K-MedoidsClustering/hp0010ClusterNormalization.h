/* -------------------
** hp0010ClusterNormalization.h
** Hari Pradhan
** 09/22/2012
** ------------------*/


#ifndef NORMALIZATION_H
#define NORMALIZATION_H
#include <iostream>
#include<vector>
#include "hp0010ClusterOutputData.h"
#include "hp0010ClusterParser.h"
using namespace std;

class Normalization{

private:
	vector<OutputData> output;
	vector<vector<double> > normalizedOutput;
	vector<vector<double> > minMax;
	
public:
	//Default Constructor
	Normalization(){}

	//Destructor
	~Normalization(){}

	//Start normalization of the data
	void startNormalization(vector<Attribute>,string);

	void startNormalization(Parser ,vector<vector<double> >,vector <Attribute>,bool);
	//Finds minimum and maximum value of the attribute 	
	vector<double> findMinMax(int );

	//Normalize the data using Min-Max Normalization
	void findMinMaxNormalization(int , double  ,double ,double ,double );

	//Gets the output data containing normalized data and min-max values
	void getOutputData(int ,double , double , bool );

	//Gets normalized output
	vector<vector<double> > getNormalizedOutput();

};

#endif 
