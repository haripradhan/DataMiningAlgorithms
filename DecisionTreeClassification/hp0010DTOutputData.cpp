/* -------------------
** hp0010DTOutputData.cpp
** Hari Pradhan
** 09/22/2012
** ------------------*/

#include "hp0010DTOutputData.h"
#include <vector>
using namespace std;

/**
* Sets minimum and maximum value of an attribute
* @param minmaxvals Vector containing min and max value of an attribute
* Index 0 : min value
* Index 1: max value
*/
void OutputData::setMinMax(vector<double> minmaxvals){
	minmax = minmaxvals;
}

/**
* Sets normalized values of an attribute
* @param normalizedvals Vector containing normalized values of an attribute
*/
void OutputData::setNormalizedData(vector<double> normalizedvals){
	normalizedData = normalizedvals;
}

/**
* Gets minimum and maximum value of an attribute
* @return Vector containing min and max value of an attribute 
*/
vector <double> OutputData::getMinMax(){
	return minmax;
}

/**
* Gets normalized values of an attribute
* @return Vector containing normalized values of an attribute
*/
vector <double> OutputData::getNormalizedData(){
	return normalizedData;
}


