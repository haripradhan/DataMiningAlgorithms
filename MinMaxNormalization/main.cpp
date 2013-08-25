/* -------------------
** main.cpp
** Hari pradhan
** 09/12/2012
** Purpose: Normalize the sample data sets using the min-max normalization algorithm
** ------------------*/

#include "Parser.h"
#include "Normalization.h"
#include "FileWriter.h"
#include <string>
#include <stdlib.h>
#define MAXVALUE 1
#define MINVALUE 0
#define minmaxFile "hp0010MinMax"
#define outFile "hp0010Normalize"
using namespace std;

bool isInteger(string);
void callForNormalization(vector <Attribute>,string);

/**
* Checks whether string is numeric or not
* @param str String
* @return true if string is numeric else false
*/
bool isInteger(string str){
	bool flag=false;
	//cout<<"test"<<str<<endl;
	for(int i=0;i< (int)str.length();i++){ 
		if(((int)str[i] >= 48)  && ((int)str[i] <= 57)){ //comparing ASCII value of digits (48 - 57)
			flag = true;
		}else{
			flag = false; 
			break;
		}
	}

	//cout<<"check"<<str<<"\t"<<flag<<endl;
	return flag;
}

/**
* Starts normalization
* @param attributes Vector containing the attributes detail (name, min-value, max-value, class -True/False information)
* @param inputFile Name of input file
*/
void callForNormalization(vector <Attribute> attributes,string inputFile){
	//Vector containing min max values of each attributes
	//minmaxVector[i][0] - minimum value of (i+1)th attribute
	//minmaxVector[i][1] - maximum value of (i+1)th attribute
	vector< vector <double> > minmaxVector;
	//Vector containing normalized values of each attributes
	//normalizedDataVector[i][..] - normalized data of (i+1)th attribute
	vector<vector<double> > normalizedDataVector;
	//Temp Vector containing normalized data of an attribute
	//output[0....rowcount-1] - normalized data of an attribute
	vector<OutputData> output;

	Normalization norm;
	norm.startNormalization(attributes,inputFile);
	output= norm.getOuput();

	//Loop thru the size of output (number of rows) to push the min-max value and normalized values of each attribute 
	//into 2D vector minmaxVector and normalizedDataVector respectively
	for(int i =0;i< (int)output.size();i++){
		minmaxVector.push_back(output[i].getMinMax());
		normalizedDataVector.push_back(output[i].getNormalizedData());
	}

	FileWriter fileWriter;
	//Opens min max file and writes the values for output
	fileWriter.openFile(minmaxFile + inputFile);
	fileWriter.writeFile(minmaxVector,norm.getHeaderContentOutput());

	//Opens normalized file and writes the values for output
	fileWriter.openFile(outFile + inputFile);
	fileWriter.writeFile(normalizedDataVector,norm.getHeaderContentOutput());

}

int main(int argc, char* argv[])
{
	vector <Attribute> attributes;
	char* inputFile;
	Attribute attr;
	string attributeName;
	
	if (argc < 5) {
		cerr << "Usage: InputFile -c classattribute "<<
			"-attribute1 newminVal1 newmaxVal1 -attribute2 newminVal2 newmaxVal2 ..."; // Inform the user of how to use the program
		cin.get();
		exit(0);
	} else {
		int i=1;
		inputFile = argv[i];
		while(i +1 <argc){
			i++;
			/*if (string(argv[i]) == "-i") {
				//next argument *should* be the filename:
				i++;
				inputFile = argv[i++];

			}
			else if (string(argv[i]) == "-o") {
				i++;
				outFile = argv[i++];
			} else if (string(argv[i]) == "-m") {
				i++;
				minmaxFile = argv[i++];
			}*/
			if (string(argv[i]) == "-c"){
				i++;
				attr.name = argv[i];
				attr.minVal=0;
				attr.maxVal=0;
				attr.isClass=true;
				attributes.push_back(attr);
				
			}else if (string(argv[i]).find("-")==0){

				attributeName = argv[i];
				attr.name = attributeName.substr(1);
				if( (i + 1) < argc){ 
					if(isInteger(string(argv[i+1]).c_str()) && isInteger(string(argv[i+2]).c_str())){
						i++;
						attr.minVal= atof(argv[i]);
						i++;
						attr.maxVal =atof(argv[i]);
					}else{
						attr.minVal= MINVALUE;
						attr.maxVal =MAXVALUE;
					}
				}else{
					attr.minVal= MINVALUE;
					attr.maxVal =MAXVALUE;
				}
				//cout<<attr.name<<"\t"<<attr.minVal<<"\t"<<attr.maxVal<<endl;

				attr.isClass = false;
				attributes.push_back(attr);
			}else{
				cout << "Invalid arguments\n";
				exit(0);
			}
		}
		
	}

	callForNormalization(attributes,inputFile);
	return 0;
}
