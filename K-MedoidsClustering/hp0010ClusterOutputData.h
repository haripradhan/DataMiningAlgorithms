/* -------------------
** hp0010ClusterOutputData.h
** Hari Pradhan
** 09/22/2012
** ------------------*/

#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#include <iostream>
#include <vector>
using namespace std;

class OutputData{

private:
	vector <double > minmax;        //Vector containing min and max of an attribute
	vector <double> normalizedData; //Vector containing normalized data of an attribute
public:
	//Default Constructor
	OutputData(){}

	//Destructor
	~OutputData(){}

	//Sets minimum and maximum value of an attribute
	void setMinMax(vector<double>);

	//Sets normalized values of an attribute
	void setNormalizedData(vector<double>);

	//Gets minimum and maximum value of an attribute
	vector <double> getMinMax();

	//Gets normalized values of an attribute
	vector <double> getNormalizedData();

};

#endif
