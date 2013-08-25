/* -------------------
** hp0010DTParser.h
** Hari Pradhan
** 09/22/2012
** ------------------*/

#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<vector>
using namespace std;
/**
* Data Structure for holding minimum, maximum , name of the attribute
* Also includes whether attribute is a class attribute or not
*/
struct Attribute{

	double maxVal;
	double minVal;
	string name;
	bool isClass;
	vector<int> possibleValues;
	int key;
};


struct node{
	double entropy;
	vector<vector<double> > data;
	Attribute decomposeAttribute;
	int size;
	vector<node*> child;
	int level;
	node* parent;
	bool isNotLeaf;
	int classValue;
	int majorityClass;
};


/**
This Class parses .arff file
*/
class Parser
{
private:
	vector< vector<double> > data; //2D vector that holds the values of attributes
	string relation_name;  //Name of relation
	vector<Attribute> attributes;
	vector<string> attribute_name; //Attribute name
	vector<string> attribute_type; //Attribute Type
	int classAttributeIndex; //Identifies the class attibute
	string headerContent; //Content of header
	int attributeCount; //Count the number of attribute

public:
	//Default Constructor
	Parser();

	// Destructor
	~Parser() {}

	//Sets the size of the array or vector
	void setSize(int rows, int cols);

	//Reads file to create the data vector
	void read(string filename);

	//Writes the output to the file
	void write(string filename);

	//Converts string into double
	double stringToDouble( const std::string& s ); 

	//Returns the data vector
	vector< vector<double> > getData();

	//Returns the count of attributes
	int getAttributeCount();

	//Returns the index of class attribute
	int getClassAttributeIndex();
	
	//Returns class attribute
	Attribute getClassAttribute(string);

	//Returns the name of attributes
	vector<string> getAttributeName();

	//Returns vector of attribute struct
	vector<Attribute> getAttributes();

	//Returns the type of attributes
	vector<string> getAttributeType();

	//Returns relation name
	string getRelationName();
	

};

#endif
