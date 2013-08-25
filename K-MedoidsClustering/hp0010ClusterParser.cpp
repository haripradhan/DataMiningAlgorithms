/* -------------------
** hp0010ClusterParser.cpp
** Hari Pradhan
** 09/22/2012
** ------------------*/

#include "hp0010ClusterParser.h"
#include<iostream>
#include <vector>
#include<algorithm>
#include <string>
#include <sstream>
#include <fstream>

/**
* Default Constructor
*/
Parser::Parser()
{
}

/**
* Set the size of the Vector
* @param rows - number of rows
* @param cols - number of columns
*/
void Parser::setSize(int rows,int cols)
{	
	data.resize(rows);
	for(int i = 0; i < rows; i++)
		data[i].resize(cols);
}

/**
* Reads the file to parse
* @param fileName - name of file
*/
void Parser::read(string fileName){
	ifstream inputFile;
	int attrCount =0; //Counts the number of attibutes
	int lineNum =0;   //Counts the line read
	string val;
	string line;
	vector<double> temp; //Holds each line of data

	//Opens the arff file to read the data
	inputFile.open(fileName.c_str());
	//Checks whether the file is open
	if(inputFile.is_open()){
		//Loop until EOF
		while(!inputFile.eof())
		{
			//Gets the single line from the file
			getline(inputFile,line);
			lineNum++;
			if(line.find ( "@data" ) != 0){
				headerContent += line +"\n";
			}			
			//Check for "@relation"
			if(line.find("@relation")==0){
				relation_name = line.substr(line.find_first_of(" "));
			}
			//Check for "@attribute"
			else if(line.find("@attribute")==0){
				line = line.substr (line.find_first_of ( " \t" ) + 1 );
				string attrName = line.substr ( 0, line.find_first_of ( " \t" ) );
				attribute_name.push_back ( attrName );
				line = line.substr ( attrName.size() );
				string value = line.substr ( line.find_first_not_of ( " \t" ) );
				attribute_type.push_back(value);
				attrCount++;	
			}
			//Check for "@data"
			else if (line.find ( "@data" ) == 0 )
			{
				headerContent += line;
				while ( !inputFile.eof() )
				{
					getline ( inputFile, line );
					lineNum++;
					temp.reserve(attrCount);

					if ( line.find ( "%" ) != 0 && line != "" )
					{
						//Iterate thru all attributes and push the parsed attributes value 
						//back to the vector temp
						for ( int i = 0; i < attrCount; i++ )
						{	
							line= line.substr(line.find_first_not_of(" "));
							val = line.substr(0,line.find_first_of(" "));
							line =line.substr(line.find_first_of(" ")+1);
							temp.push_back(stringToDouble(val));
						}
						data.push_back(temp);
						temp.clear();
					}
				}
			}

		}
	}else{
		cout << "Error::The specified file can not be opened";
	}

	attributeCount = attrCount;
}

/**
* Converts string into double
* @param s -string 
* @return double of the numeric string
*/
double Parser::stringToDouble( const string& s )
{
	istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
}

/**
* Gets the data which contains values of parsed data
* @return 2D vector of parsed data
*/
vector< vector<double> > Parser::getData(){
	return data;
}

/**
* Gets the count of attributes
* @return Count of attribute
*/
int Parser::getAttributeCount(){
	return attributeCount;
}

/**
* Gets the name of attributes
* @return Vector of attributes name
*/
vector<string> Parser::getAttributeName(){
	return attribute_name;
}

/**
* Gets the type of attributes
* @return Vector of attributes type
*/
vector<string> Parser::getAttributeType(){
	return attribute_type;
}

/**
* Gets the index of class attribute
* @return Index of class attribute
*/
int Parser::getClassAttributeIndex(){
	int i;
	for(i =0;i< (int)attribute_name.size();i++){
		if(attribute_name[i]=="class"){
			return i;
		}
	}
	return i;
}
