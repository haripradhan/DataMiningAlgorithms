///* -------------------
//** hp0010DTMain.cpp
//** Hari Pradhan
//** Purpose: Perform supervised pattern classification using decision trees
//** 09/22/2012
//** ------------------*/
#include "hp0010DTParser.h"
#include "hp0010DTFileWriter.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <vector>
#define decisionTreeFile "hp0010DTTraining"
#define applicationModeFile "hp0010DTApplication"
#define confusionMatrixFile "hp0010DTAccuracy"
#define ACCURACY_PERCENT 90.00
using namespace std;

Attribute classAttribute;
//vector<vector <int>> attributevalue;
//int attributecount = 9;
//int classattributeindex = 9;

string convertIntToString(int);
bool isInteger(string);
string convertIntToString(int);
bool isInteger(string);
int getCount(vector<vector<double> >,int, int, double, double );
vector<vector<double> > getConfusionMatrix(vector<vector<double> >, vector<int>, int, int);
double calculateEntropy(vector<vector<double> >, int);
bool stoppingCondition(vector<vector<double> >, node*);
bool sameAttributeValues(vector<vector<double> >, node*);
vector<vector<double> > getSubset(vector<vector<double> >, int, int);
void buildDecisionTree(node*&, vector<Attribute>);
vector<double> classify(vector<double>,node*);
void startDecisionTree(string, double, string);

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
* Calculates entropy of the given data
* @param data 2D vector of data
* @param attributendex Index of attribute whose entropy is to be calculated
* @return Entropy of the given data
*/
double calculateEntropy(vector<vector<double> > data, int attributeindex){

	int numdata = (int) data.size();

	//if (numdata == 0) return ;
	int numvalues = classAttribute.possibleValues.size();
	double sum = 0;
	for(int i =0 ; i <numvalues; i++){
		int count =0;
		for(int j =0; j< (int) data.size() ; j ++){
			if(data[j][classAttribute.key] == classAttribute.possibleValues[i])
				count++;
		}
		double probability = (double)count/numdata;

		if(count > 0){
			sum += (-probability*log(probability) * 1/log(2.0) );
		}else{
			return 0;
		}
	}

	return sum;
}

/**
* Checks stopping condition of the recursive function call
* @param data 2D vector of data
* @param *n node of tree which is checked for leaf
* @return true if the node is leaf
*/
bool stoppingCondition(vector<vector<double> > data, node* n){
	int size = (int) data.size();

	vector<int> count; //count of data with same classlabel
	vector<double> percent; //percent of data with same classlabel
	int totalcount=0;      //total count of data with different/same classlabel

	//Check empty data set
	if(n->data.size() == 0){
		n->isNotLeaf = false;
		n->classValue = n->parent->majorityClass;
		return true ;
	}
	//Check singleton data set
	if(n->data.size() == 1){
		n->isNotLeaf = false;
		n->classValue =(int)n->data[0][n->data[0].size()-1];
		return true;
	}

	//Check if data have set class label
	//Initialize count and percent to 0
	for(int j = 0; j < (int)classAttribute.possibleValues.size(); j++){
		count.push_back(0);
		percent.push_back(0);
	}
	//Finding count and totalcount
	for(int i = 0 ; i < size ; i ++){
		for(int j = 0; j <(int)classAttribute.possibleValues.size(); j++){
			if(data[i][classAttribute.key] == classAttribute.possibleValues[j]){
				count[j]++;
				totalcount++;
			}
		}
	}

	int maxCount = count[0];
	int maxIndex=0;
	for(int i = 1 ; i < (int)count.size(); i ++){
		if(count[i]>maxCount){
			maxCount = count[i];
			maxIndex = i;
		}
	}
	n->majorityClass = (int)classAttribute.possibleValues[maxIndex];

	//for(int i =0 ; i < count.size();i++){
	//	cout<<"count of "<<classAttribute.possibleValues[i]<<" "<<count[i]<<endl;
	//}
	//Finding the percent of data with same classlabel
	for(int i =0 ; i < (int)count.size();i++){
		percent[i] =(double) count[i]/totalcount * 100;
	}

	//Finding maximum percent and index of percent with maximum percent
	int indexOfMaxPercent = 0;
	double maxPercent = percent[indexOfMaxPercent];
	for(int i = 1; i < (int)percent.size(); i++){
		if(percent[i] >= maxPercent){
			maxPercent = percent[i];
			indexOfMaxPercent = i;
		}
	}

	//cout<<ACCURACY_PERCENT<<endl;
	//Returns true (stopping condition = true) if maxpercent is greater than 80
	if(maxPercent >= ACCURACY_PERCENT){
		n->classValue = (int) classAttribute.possibleValues[indexOfMaxPercent];
		return true;
	}

	return false;
}

/**
* Checks whether attribute values for set of records are same (one of the stopping condition)
* @param data 2D vector of data
* @param *n node of tree which is checked for leaf
* @return true if the node is leaf
*/
bool sameAttributeValues(vector<vector<double> > data, node* n){
	int count =0;
	bool isSameAttribute = true;

	int size = (int) data.size(); //size of the data
	int subsize = data[0].size(); //number of atttributes in record

	//Loop through all the record to check whether the records have same attribute values or not
	int maxCount = 0;
	for(int k = 0 ; k < size ; k++)
		for(int i = 0;i < size; i++){
			if(k !=i){
				for(int j = 0;j < subsize-1; j++){
					if(data[k][j] != data[i][j]){
						isSameAttribute = false;
						break;
					}	
				}
				if(isSameAttribute){
					count++;
				}

				if(count > maxCount){
					maxCount = count;
				}
			}
		}

		if((double)maxCount/size * 100 >= ACCURACY_PERCENT){
			n->classValue = n->parent->majorityClass;
			return true;
		}else{
			return false;
		}

}


/**
* Gets the filtered data set
* @param data 2D vector of data
* @param attributeIndex Index of attribute
* @param attributeValue Value of attribute indexed by attributeIndex
* @return 2D filtered data set
*/
vector<vector<double> > getSubset(vector<vector<double> > data, int attributeIndex,int attributeValue){
		vector<vector<double> > subsetData;
		for(int i = 0 ; i < (int) data.size(); i++){
			if(data[i][attributeIndex] == attributeValue){
				subsetData.push_back(data[i]);
			}
		}
		return subsetData;
	}

/**
* Generates decision tree recursively
* @param *n Root node of the tree
* @param attributeList Sets of attributes which has not been splitted yet
*/
void buildDecisionTree(node *&n, vector<Attribute> attributeList){
	int size = n->data.size();
	vector<vector<double> > temp;
	double minentropy = 1000;
	n->size = size;
	n->level = n->parent->level+1;
	if(attributeList.size() == 1){
		n->classValue = n->parent->majorityClass;
		n->isNotLeaf = false;
		return;
	}
	if(stoppingCondition(n->data,n)){
		n->isNotLeaf = false;
		return ;
	}
	if(sameAttributeValues(n->data,n)){
		n->isNotLeaf = false;
		return;
	}

	int attrbindex;
	int bestindex;
	for(attrbindex = 0 ; attrbindex < (int)attributeList.size(); attrbindex++){
		double entropy = 0;		
		int attribuniquesvaluescount = attributeList[attrbindex].possibleValues.size();
		for(int attribuniqueindex= 0 ; attribuniqueindex < attribuniquesvaluescount ; attribuniqueindex++){
				temp= getSubset(n->data,attributeList[attrbindex].key,attributeList[attrbindex].possibleValues[attribuniqueindex]);
				double indEntropy =calculateEntropy(temp,attributeList[attrbindex].key);
				entropy += (double) temp.size()/size * indEntropy;
		}
		//cout<<"x"<<attributeList[attrbindex].key<<"  "<<entropy<<endl;
		if(entropy <= minentropy){
			n->decomposeAttribute = attributeList[attrbindex];
			minentropy = entropy;
			bestindex = attrbindex;

		}
	}	


	//cout<<"Best Attribute: x"<<n->decomposeAttribute.key<<endl;
	//cout<<"---------------------------"<<endl<<endl;

	vector<Attribute>::iterator position = attributeList.begin() + bestindex;
	attributeList.erase(position);

	vector<int> possibleValues;
	possibleValues = n->decomposeAttribute.possibleValues;

	node* child;
	//n.child = new node[attributevalue[bestattribute].size()];
	for(int j = 0; j < (int) possibleValues.size(); j++){
		child = new node;
		child->parent = n;
		child->isNotLeaf = true;
		child->data = getSubset(n->data,n->decomposeAttribute.key,possibleValues[j]);
		child->decomposeAttribute = n->decomposeAttribute;
		n->child.push_back(child);

	}

	for(int k =0; k < (int)possibleValues.size(); k++){
		//cout<<"Attribute"<<n->decomposeAttribute<<"=="<<attributevalue[bestattribute][k]<<endl;
		buildDecisionTree(n->child[k],attributeList);
	}

}

/**
* Print decison tree recursively
* @param *n Root node of the tree
* @param level Level of the node (For root node initially it is 0)
*/
void printtree(node *nd,int level){
	if(!nd->isNotLeaf){
		cout<<"  "<<nd->classValue<<endl;
		return;
	}

	cout<<endl;
	vector<int> possibleValues;
	possibleValues = nd->decomposeAttribute.possibleValues;

	for(int k = 0 ; k< (int)possibleValues.size(); k++){
		for(int j = 0;j < level;j++){
			cout<<"|  ";
		}
		cout<<nd->decomposeAttribute.name<<"["<<nd->level<<","<<nd->data.size()<<"]"<<" ="<<possibleValues[k];
		printtree(nd->child[k],nd->child[k]->level);
	}
}

/**
* Classify the test data using rules (from decision tree)
* @param data 1D vector of data record
* @param *n root node of tree
* @return 1D vector of data (appended with predicted class)
*/
vector<double> classify(vector<double> data,node* n){
	while(true){
		if(n->isNotLeaf){
			n= n->child[(int)data[n->decomposeAttribute.key]];
		}else{
			//cout<<"class is "<<n->classValue;
			data.push_back(n->classValue);
			break;
		}
	}
	return data;
}

/**
* Starts decision tree construction
* @param attrs vector of Attribute
* @param inputFile Filename of input file
* @param percentOfDataForTesting Percent of data used for testing
* @param className Name of class used for classificaation
*/
void startDecisionTree(string inputFile, double percentOfDataForTesting, string className){
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
	
	//Extract filename from input file
	size_t posForDot = inputFile.find_first_of(".");
	string inputFileName = inputFile;
	if(posForDot != string::npos){
		inputFileName = inputFileName.substr(0 , posForDot - 1);
	}
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
	
	//Create Training Data for training mode
	int numberOfRecordForTraining = (int)floor(percentOfDataForTesting * data.size() / 100);
	if(numberOfRecordForTraining <=0){
		cerr<<"Error: No data for training"<<endl;
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < numberOfRecordForTraining; i++){ //586 for test data
		traninigData.push_back(data[i]);
	}
	
	node* parentRoot = new node;
	node* root = new node;
	root->parent = parentRoot;
	root->isNotLeaf = true;
	root ->parent->size = traninigData.size(); 
	root->data = traninigData;
	root->parent->level = -1;
	buildDecisionTree(root,nonClassAttributes);
	//Creating FileWriter to write decision tree to the file
	FileWriter fileWriter;
	fileWriter.openFile(decisionTreeFile + convertIntToString((int)percentOfDataForTesting) +inputFileName + ".dt");
	fileWriter.writeTree(root,0);
	fileWriter.closeStream();
	//printtree(root,0);
	
	//Exit if there is no data for classification
	if(numberOfRecordForTraining >= (int) data.size()){
		cerr<<"Error: No Data for Classification"<<endl;
		exit(EXIT_FAILURE);
	}
	//Create Test Data for application mode
	for(int i = numberOfRecordForTraining; i < (int) data.size(); i++){
		testData.push_back(data[i]);
	}
	
	//Classify the test data
	//Append class label at the end of data record
	for(int i =0; i< (int)testData.size();i++){
		testData[i]=classify(testData[i],root);
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
	headerContentForOutput += "@attribute dtClass real\n\n@data\n";

	fileWriter.openFile(applicationModeFile + convertIntToString((int)percentOfDataForTesting) +inputFile);
	fileWriter.writeFile(testData,headerContentForOutput);
	fileWriter.closeStream();
	//find the class index ( defined in the input from commandline)
	int actualClassIndex = classAttribute.key;
	int predictedClassIndex = testData[0].size() - 1;
	vector<vector<double> > confusionMatrix = getConfusionMatrix(testData,classAttribute.possibleValues,
		actualClassIndex,predictedClassIndex);


	//Write confusion matrix in the file
	fileWriter.openFile(confusionMatrixFile + convertIntToString((int)percentOfDataForTesting) + inputFileName + ".txt");
	fileWriter.writeConfusionMatrix(confusionMatrix,classAttribute.possibleValues );
	fileWriter.closeStream();
}

int main(int argc,char* argv[])
{
	vector <Attribute> attributes;
	char* inputFile;
	double percentOfTestData = 80;
	string className = "class";
	
	inputFile = "bcwdisc.arff";

	if (argc < 6) {
		cerr << "Usage: -i <Input FileName> -c classattribute -P M"<<endl; // Inform the user of how to use the program
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
			}else if (string(argv[i]) == "-P" || string(argv[i]) == "-p") {
				i++;
				percentOfTestData =  atof(argv[i++]);
			}
			else{
				cout << "Invalid arguments\n";
				exit(0);
			}
		}
		
	}
	//Exit if user specify percent greater than 100
	if(percentOfTestData > 100 || percentOfTestData < 0 ){
		cerr<<"Error: Percent greater than 100 or Negative Percent Not Allowed"<<endl;
		exit(EXIT_FAILURE);
	}
	
	//cout<<"input filename "<<inputFile<<endl;
	//cout<<"class "<<className<<endl;
	//cout<<"P "<<percentOfTestData<<endl;

	startDecisionTree(inputFile, percentOfTestData,className);

	return 0;
}
