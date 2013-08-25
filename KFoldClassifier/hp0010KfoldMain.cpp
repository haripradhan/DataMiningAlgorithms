///* -------------------
//** hp0010KfoldMain.cpp
//** Hari Pradhan
//** 09/22/2012
//** ------------------*/
#include "hp0010KfoldParser.h"
#include "hp0010KfoldFileWriter.h"
#include "hp0010KfoldClassifier.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <vector>
#define KFoldClassificationFile "hp0010KFoldClassification"
#define confusionMatrixFile "hp0010KFoldConfusion"
using namespace std;

Attribute classAttribute;

string convertIntToString(int);
bool isInteger(string);
string convertIntToString(int);
bool isInteger(string);
vector<vector<double> > getConfusionMatrix(vector<vector<double> >, vector<int>, int, int);
vector<KFold> createKFold(vector<vector<double> >, int);
int getCount(vector<vector<double> >, int, int, double, double);
vector<vector<double> > getConfusionMatrix(vector<vector<double> >, vector<int>, int, int); 
void startFoldClassifier(string, string, int);

/**
* Converts integer into string
* @param number integer to be converted to string
* @return string equivalent string of integer
*/
string convertIntToString(int number)
{
	stringstream sStream;
	sStream << number;
	return sStream.str();
}

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
	return flag;
}

/**
* Creates K fold
* @param data 2D data
* @param k number of folds
* @return vector<KFold> vector of KFolds
*/
vector<KFold> createKFold(vector<vector<double> > data , int k){
	vector<KFold> dataGroup;
	vector<vector<double> > testDataForGroup;
	vector<vector<double> > trainedDataForGroup;
	KFold temp;

	int groupLength = data.size()/k;
	int i;
	size_t j;
	for(int l =0 ; l< k; l++){
		for(i =0 ;i < k; i++){
			if(i == l){
				for(j = i * groupLength ; j < (size_t) (i+1) * groupLength; j ++){
					testDataForGroup.push_back(data[j]);
				}

			}else{
				for(j = i * groupLength ; j < (size_t) (i+1) * groupLength; j ++){
					trainedDataForGroup.push_back(data[j]);
				}
			}

		}

		while(j<data.size()){
			if(i -1 == l){
				testDataForGroup.push_back(data[j]);
			}else{
				trainedDataForGroup.push_back(data[j]);
			}
			j ++; 
		}
		temp.testData = testDataForGroup;
		temp.trainedData = trainedDataForGroup;
		dataGroup.push_back(temp);
		testDataForGroup.clear();
		trainedDataForGroup.clear();

	}
	return dataGroup;

}

/**
* Gets the count of data where data[..][actualClassIndex] = actualClassValue and data[..][predictedClassIndex] = predictedClassValue
* @param data 2D vector of data
* @param actualClassIndex Index of actual class attribute
* @param predictedClassIndex Index of predicted class attribute
* @param actualClassValue Value of actual class attribute
* @param predictedClassValue Value of predicted class attribute
* @return int count
*/
int getCount(vector<vector<double> > data,int actualClassIndex, int predictedClassIndex,
	double actualClassValue, double predictedClassValue){
		int count=0;
		for(int i =0 ; i < (int) data.size(); i++){
			if(data[i][actualClassIndex] == actualClassValue && data[i][predictedClassIndex] == predictedClassValue){
				count++;
			}
		}
		return count;

}
/**
* Gets confusion matrix
* @param data 2D vector of data
* @param rangeOfClass Possible values of class
* @param actualClassIndex Index of actual class attribute
* @param predictedClassIndex Index of predicted class attribute
* @return 2D vector of confusion matrix
*/
vector<vector<double> > getConfusionMatrix(vector<vector<double> > data, vector<int> rangeOfClass,
	int actualClassIndex, int predictedClassIndex){
		vector<vector<double> > confusionMatrixData; 
		vector<double> singleConfusionRow;
		for(int i = 0 ; i < (int)rangeOfClass.size(); i ++){
			for(int j =0; j < (int)rangeOfClass.size(); j++){
				singleConfusionRow.push_back(getCount(data,actualClassIndex,predictedClassIndex,rangeOfClass[i],rangeOfClass[j]));
			}
			confusionMatrixData.push_back(singleConfusionRow);
			singleConfusionRow.clear();
		}
		return confusionMatrixData;
}


/**
* Starts  K-fold for Naive Bayes Classifier
* @param inputFile input file
* @param className class name
* @param K class name
*/
void startFoldClassifier(string inputFile, string className, int K){
	Parser parser;
	//Reads file and start parsing
	parser.read(inputFile);
	vector<vector<double> > traninigData; //training set of data
	vector<vector<double> > data;		  //Entire set of data
	vector<vector<double> > testData;	  //test set of data
	vector<Attribute> attributes;
	vector<Attribute> nonClassAttributes;
	data = parser.getData();
	attributes = parser.getAttributes();
	nonClassAttributes = attributes;

	//Remove class attributes
	int classIndex = 0;
	for(int i = 0; i < (int)attributes.size(); i ++){
		if(attributes[i].name == className){
			classIndex = i;
			break;
		}
	}
	vector<Attribute>::iterator position = nonClassAttributes.begin() + classIndex;
	nonClassAttributes.erase(position);


	classAttribute = parser.getClassAttribute(className);
	if(classAttribute.name != className){
		cerr<<"Error: Invalid Class Name"<<endl;
		exit(EXIT_FAILURE);
	}

	vector<KFold> KFoldData = createKFold(data,K);
	vector<vector<vector<double> > > classifiedData;
	//cout<<"start"<<endl;
	for(size_t i = 0 ; i < KFoldData.size(); i++){
		Classifier classfier;
		classfier.setAttributeList(nonClassAttributes);
		classfier.setTrainedData(KFoldData[i].trainedData);
		//cout<<"Trained data size " <<KFoldData[i].trainedData.size()<<endl;
		//cout<<"Test data size " <<KFoldData[i].testData.size()<<endl;
		classfier.setTestData(KFoldData[i].testData);
		classfier.trainClassifier(classAttribute);
		classfier.testClassifier(classAttribute);
		classifiedData.push_back(classfier.getTestData());
		//cout<<"*********"<<endl;

	}
	vector<vector<double> > classData;
	for(size_t i = 0 ; i < classifiedData.size(); i ++){
		for(size_t j = 0 ; j < classifiedData[i].size(); j ++){
			classData.push_back(classifiedData[i][j]);
		}
	}

	//vector<Attribute> attributes = parser.getAttributes();	
	string headerContentForOutput;
	headerContentForOutput += "@relation " + parser.getRelationName() + "\n\n";

	//Loop thru the list of attributes to append in the header content
	int i,j;

	for(i = 0;i < (int)attributes.size();i++){
		headerContentForOutput += "@attribute " + attributes[i].name + " {"; 
		for(j = 0; j < (int)attributes[i].possibleValues.size() - 1; j++){
			headerContentForOutput += convertIntToString(attributes[i].possibleValues[j]) +", ";
		}
		headerContentForOutput += convertIntToString(attributes[i].possibleValues[j]);
		headerContentForOutput += "}\n";
	}
	headerContentForOutput += "@attribute bayesClass real\n\n@data\n";
	FileWriter fileWriter;
	fileWriter.openFile(KFoldClassificationFile +inputFile);
	fileWriter.writeFile(classData,headerContentForOutput);
	fileWriter.closeStream();

	//find the class index ( defined in the input from commandline)
	int actualClassIndex = classAttribute.key;
	int predictedClassIndex = classData[0].size() - 1;
	vector<vector<double> > confusionMatrix = getConfusionMatrix(classData,classAttribute.possibleValues,
		actualClassIndex,predictedClassIndex);

	//Extract filename from input file
	size_t posForDot = inputFile.find_first_of(".");
	string inputFileName = inputFile;
	if(posForDot != string::npos){
		inputFileName = inputFileName.substr(0 , posForDot);
	}

	//Write confusion matrix in the file
	fileWriter.openFile(confusionMatrixFile + inputFileName + ".txt");
	fileWriter.writeConfusionMatrix(confusionMatrix,classAttribute.possibleValues );
	fileWriter.closeStream();
	
}


int main(int argc,char* argv[])
{
	vector <Attribute> attributes;
	char* inputFile;
	string className = "class";
	//inputFile = "bcwdisc.arff";
	int K = 10;
	if (argc != 7 && argc != 5) {
		cerr << "Usage: -i <Input FileName> -c <classattribute> -K <value> "<<endl; // Inform the user of how to use the program
		cin.get();
		exit(0);
	} else {
		int i=1;
		while(i <argc){
			if (string(argv[i]) == "-i") {
				//next argument should be the filename:
				i++;
				inputFile = argv[i++];
			
			}else if (string(argv[i]) == "-c"){
				i++;
				className = argv[i++];
			}else if (string(argv[i]) == "-K" || string(argv[i]) == "-k") {
				i++;
				K =  atoi(argv[i++]);
			}
			else{
				cout << "Invalid arguments\n";
				exit(0);
			}
		}
		
	}
	
	//cout<<"input filename "<<inputFile<<endl;
	//cout<<"class "<<className<<endl;
	//cout<<"K "<<K<<endl;

	startFoldClassifier(inputFile,className,K);

	return 0;
}
