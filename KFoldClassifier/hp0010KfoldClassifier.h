/* -------------------
** hp0010KfoldClassfier.h
** Hari Pradhan
** 11/17/2012
** ------------------*/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include<iostream>
#include<vector>
#include "hp0010KfoldParser.h"
using namespace std;

/**
* Data Structure for holding trained and test data
*/
struct KFold{
	vector<vector<double> > trainedData;
	vector<vector<double> > testData;
};

/**
This Class belongs to Naive Bayes classifier
*/
class Classifier{

private:
	vector<vector<double> > trainedData;  // 2D trained data
	vector<vector<double> > testData;	  // 2D test data	
	vector<Attribute> attributeList;      // List of attribute

public:

	//Default Constructor
	Classifier();
	
	//Train classififier with trained data
	void trainClassifier(Attribute classAttribute);
	
	//Test classififier
	void testClassifier(Attribute classAttribute);
	
	//Test classifier for single record
	int testClassifierForSingleData(Attribute classAttribute,vector<double> data);
	
	//Count of record having same attribute value and class value
	vector<int> count(Attribute,int,double,vector<vector<double> >);
	
	//Probability having same attribute value and class value
	vector<double> probability(vector<int>,vector<double>);
	
	//Sets 2D test data
	void setTestData(vector<vector<double> >);
	
	//Sets 2D trained data
	void setTrainedData(vector<vector<double> >);
	
	//Sets attribute list
	void setAttributeList(vector<Attribute>);
	
	//Gets 2D trained data
	vector<vector<double> > getTrainedData();
	
	//Gets 2D test data
	vector<vector<double> > getTestData();
	
	//Gets attribute list
	vector<Attribute> getattributeList();
	
};
#endif
