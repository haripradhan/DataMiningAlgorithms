/* -------------------
** Parser.h
** Hari pradhan
** 09/12/2012
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
};
/**
This Class parses .arff file
*/
class Parser
{
private:
	vector< vector<double> > data; //2D vector that holds the values of attributes
	string relation_name;  //Name of relation
	vector<string> attribute_name; //Attribute name
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

	//Returns the name of attributes
	vector<string> getAttributeName();

	//Returns the content of header including (@relation, @attribute and @data)
	string getHeaderContent();
};

#endif
