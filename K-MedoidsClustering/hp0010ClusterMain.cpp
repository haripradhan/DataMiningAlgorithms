///* -------------------
//** hp0010ClusterMain.cpp
//** Hari Pradhan
//** 09/22/2012
//** Purpose: Cluster the sample data sets using the basic K-Medoids algorithm
//** ------------------*/
#include <time.h>
#include "hp0010ClusterParser.h"
#include "hp0010ClusterNormalization.h"
#include "hp0010ClusterFileWriter.h"
#include "hp0010ClusterKMedoid.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#define MAXVALUE 1
#define MINVALUE 0
#define clusterCenterFile "hp0010ClusterCenter"
#define clusterOutputFile "hp0010Clustering"
#define clusterStatisticFile "hp0010ClusterStatistics"
#define initialMinDistance 1.7E308
using namespace std;

string convertIntToString(int);
bool isInteger(string);
vector<vector<double> > callForNormalization(Parser, vector<Attribute>);
void clustering(ClusterData[], int i,Cluster &,ofstream &);
void callForClustering(Parser,vector <vector<double> >,vector <vector<double> >,string, int, bool);

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
* Starts clustering process
* @param attributes Attributes information
* @param normalize True if clustering is to be done for normalized data else False
* @param numOfCluster Number of cluster 
* @param inputFile  -Name of input file
*/
void startClustering(vector <Attribute> attributes,bool normalize,int numOfCluster,string inputFile){
	Parser parser;
	//Reads file and start parsing
	parser.read(inputFile);
	vector<vector<double> > Originaldata;
	vector<vector<double> > normalizedDataVector;
	Originaldata = parser.getData();
	normalizedDataVector = Originaldata;
	if(normalize){
		normalizedDataVector=callForNormalization(parser,attributes);
	}
	callForClustering(parser,normalizedDataVector, Originaldata,inputFile,numOfCluster,attributes[0].isClass);

}

/**
* Starts normalization as per needed
* @param attributes Vector containing the attributes detail (name, min-value, max-value, class -True/False information)
* @param parser Object of Parser
* @return 2D vector containing the output of normalization
*/
vector<vector<double> > callForNormalization(Parser parser, vector<Attribute> attributes){
	
	//Vector containing min max values of each attributes
	//minmaxVector[i][0] - minimum value of (i+1)th attribute
	//minmaxVector[i][1] - maximum value of (i+1)th attribute
	//vector< vector <double> > minmaxVector;
	//Vector containing normalized values of each attributes
	//normalizedDataVector[i][..] - normalized data of (i+1)th attribute
	vector<vector<double> > normalizedDataVector = parser.getData();
	Normalization norm;
	norm.startNormalization(parser, normalizedDataVector,attributes, attributes[0].isClass);
	normalizedDataVector = norm.getNormalizedOutput();

	FileWriter fileWriter;
	//Opens min max file and writes the values for output
	//fileWriter.openFile(minmaxFile + inputFile);
	//fileWriter.writeFile(minmaxVector,norm.getHeaderContentOutput());

	//Opens normalized file and writes the values for output
	//fileWriter.openFile("Normalize.txt");
	//fileWriter.writeFile(normalizedDataVector,"test");

	return normalizedDataVector;
}

/**
* K-medoid Clustering process
* @param parser Object of parser which reads the input file
* @param normalizedDataVector 2D vector of normalized data
* @param Originaldata 2D vector of original data before normalization
* @param inputFile Name of input file
* @param isClass True if class attibute is not considered for clustering else False
* @param k  Number of cluster
*/
void callForClustering(Parser parser,vector <vector<double> > normalizedDataVector,vector <vector<double> > Originaldata,string inputFile, int k, bool isClass){

	int size = normalizedDataVector.size();
	vector<double> distance;
	ClusterData* clusterData = new ClusterData[size];
	double dis;
	int classAttributeIndex=parser.getClassAttributeIndex();  //Gets the index of class attribute; ignore it for clustering
	
	////Displays the time
	//time_t rawtime;
	//struct tm * timeinfo;
	//time ( &rawtime );
	//timeinfo = localtime ( &rawtime );
	//printf ( "Current local time and date: %s", asctime (timeinfo) );

	for(int i =0;i< size;i++){
		clusterData[i].objectData = normalizedDataVector[i];
		clusterData[i].clusterID = i+1;
		clusterData[i].tempClusterID = i+1;
		clusterData[i].originalId = i+1;
		clusterData[i].minDistance = initialMinDistance;
		clusterData[i].isMedoid = false;
		for(int j = 0;j< size;j++){
			dis=0;
			for(int k =0;k< (int)normalizedDataVector[0].size();k++){
				if(!(k == classAttributeIndex && isClass == true)){
					dis += (normalizedDataVector[i][k] - normalizedDataVector[j][k])*(normalizedDataVector[i][k] - normalizedDataVector[j][k]);
				}
			}
			dis = sqrt(dis);
			distance.push_back(dis);
		}
		clusterData[i].distance = distance;
		distance.clear();
	}
	//ofstream OutStream;
	//OutStream.open("distance.txt");
	//for(int i=0;i<normalizedDataVector.size();i++){
	//	
	//	for(int j=0;j<clusterData[0].distance.size();j++){
	//		OutStream <<setw(10)<<fixed<<clusterData[i].distance[j]<<"\t";
	//	}
	//	OutStream<<"\n";
	//}
	//OutStream.close();

	//time ( &rawtime );
	//timeinfo = localtime ( &rawtime );
	//printf ( "Current local time and date: %s", asctime (timeinfo) );
	//int clusterGap = normalizedDataVector.size()/k;
	int clusterCount = 1;
	int clusterIndex = 0;
	
	while(clusterCount <= k){
		clusterIndex = rand()%normalizedDataVector.size();
		clusterData[clusterIndex].isMedoid = true;
		clusterCount++;
		//clusterIndex ++;
	}

	Cluster cl;
	cl.setSize(normalizedDataVector.size());
	//Forming header contents for statistic output
	string headerContentForStatistics="";
	headerContentForStatistics += "@relation ClusterStatistics_" + inputFile.substr(0, inputFile.length() - 5) +"\n\n";
	headerContentForStatistics += "@attribute originalmedoid real\n@attribute randommedoid real\n@attribute computations real\n@attribute cost real\n@attribute replacement Boolean\n\n@data\n";
	
	//Crearting output stream for statistic ouput
	ofstream statisticOutStream;
	statisticOutStream.open((clusterStatisticFile + convertIntToString(k) + inputFile).c_str());
	statisticOutStream << headerContentForStatistics;
	//Check whether file can't be opened
	if( !statisticOutStream ) { 
		cerr << "Error: Could not open the file" << endl;
	}
	//time ( &rawtime );
	//timeinfo = localtime ( &rawtime );
	//printf ( "Current local time and date: %s", asctime (timeinfo) );
	int y;

	
	for(y =0;y<100;y++){
		for(int i =0; i< size ;i++){
			if(clusterData[i].isMedoid){
				clustering(clusterData, i,cl,statisticOutStream);
			}
		}
	}
	
	statisticOutStream.close();
	
	//Creating header contents for mediod and clustering output
	string headerContentForMediod="";
	string headerContentForOutput="";
	headerContentForMediod += "@relation ClusterCenter_" + inputFile.substr(0, inputFile.length() - 5) +"\n\n";
	headerContentForOutput += "@relation Clustering_" + inputFile.substr(0, inputFile.length() - 5) +"\n\n";
	
	vector<string> attributeName = parser.getAttributeName();
	vector<string> attributeType = parser.getAttributeType();
	//Loop thru the list of attributes to appaend in the header content
	for(int i = 0;i < (int)attributeName.size();i++){
		headerContentForMediod += "@attribute " + attributeName[i] + " "+ attributeType[i] +"\n";
		headerContentForOutput += "@attribute " + attributeName[i] + " "+ attributeType[i] +"\n";
	}
	
	headerContentForMediod +="@attribute id real\n";
	headerContentForOutput +="@attribute id real\n";
	headerContentForOutput += "@attribute cluster real\n";
	headerContentForMediod +="\n@data\n";
	headerContentForOutput +="\n@data\n";
	
	
	//Creating FileWriter to write medoid and clustering output to the file
	FileWriter fileWriter;
	fileWriter.openFile(clusterCenterFile + convertIntToString(k) + inputFile);
	fileWriter.writeFile(cl.getMediodInfo(clusterData,Originaldata),headerContentForMediod);

	fileWriter.openFile(clusterOutputFile + convertIntToString(k) +inputFile);
	fileWriter.writeFile(cl.getClusterOutput(clusterData,Originaldata),headerContentForOutput);
	delete[] clusterData;
	//time ( &rawtime );
	//timeinfo = localtime ( &rawtime );
	//printf ( "Current local time and date: %s", asctime (timeinfo) );
}

/**
* 
* @param clusterData* Pointer that points to the ClusterData
* @param i Medoid number
* @param cl Object of Cluster class
* @param statisticOutStream Output Stream to write statistics of clustering
*/
void clustering(ClusterData* clusterData, int i, Cluster &cl, ofstream &statisticOutStream){

	Statistic statistic;
	int id=0;
	double sumCost1 = 0.0;		//Initial cost clustering 
	double sumCost2 = 0.0;		//Cost after swapping any of the medoid objects with random object
	ClusterData temp;
	int size = cl.getSize();
	//Initialize minimum distance and temporaray cluster Id 
	for(int k =0; k< size;k++){
		clusterData[k].minDistance = initialMinDistance;
		clusterData[k].tempClusterID = clusterData[k].clusterID;
	}
	//Form clustering with the given mediod and find cost
	cl.formCluster(clusterData);
	sumCost1 = cl.sumOfCost(clusterData);
	//Set cluster ID with temporaray cluster Id
	for(int x =0;x<size;x++){
		clusterData[x].clusterID = clusterData[x].tempClusterID;
	}
	id++;
	int j = 0;
	
	//Swap medoid object with non-mediod object which is selected randomly
	//for(int j =0; j < size;j++){
	while(true){
		for(int k =0; k< size;k++){
			clusterData[k].minDistance = initialMinDistance;
		}
		j = rand()% size;
		if(!clusterData[j].isMedoid){
			clusterData[j].tempClusterID = clusterData[i].clusterID;
			clusterData[i].isMedoid = false;
			clusterData[j].isMedoid = true;
			clusterData[i].minDistance = initialMinDistance;
			clusterData[j].minDistance = initialMinDistance;
			//Form cluster with the given medoidd replaced by non-medoid and find the cost
			cl.formCluster(clusterData);
			sumCost2 = cl.sumOfCost(clusterData);
		
			statistic.originalMediodID = clusterData[i].originalId;
			statistic.replacementMediodID = clusterData[j].originalId;
			statistic.cost = (sumCost2-sumCost1);
			//Swap given medoid and non-medoid if cost is negative (i.e. sumCost2 < sumCost1)
			if(sumCost2 < sumCost1){
				clusterData[j].clusterID = clusterData[j].tempClusterID;
				clusterData[i].clusterID = clusterData[i].tempClusterID;
				temp = clusterData[j];
				clusterData[j]= clusterData[i];
				clusterData[i] = temp;
				sumCost1 = sumCost2;
				statistic.isReplaced = true;
				
			}else{
				clusterData[i].isMedoid = true;
				clusterData[j].isMedoid = false;
				statistic.isReplaced = false;
			}
			statisticOutStream<<setw(5)<<statistic.originalMediodID <<setw(5)<<statistic.replacementMediodID<<
				setw(12)<<fixed<<setprecision(5)<<sumCost2<<setw(12)<<fixed<<setprecision(5)<<
				statistic.cost<<setw(10)<<(statistic.isReplaced == 1 ? "true":"false")<<endl;
			break;
		}
	}
}

int main(int argc,char* argv[])
{
	vector <Attribute> attributes;
	char* inputFile;
	int k;
	bool useNormalize=false;
	Attribute attr;
	string attributeName;
	
	//inputFile = "mesocyclone.arff";
	//k = 4;
	attr.name = "class";
	attr.minVal=0;
	attr.maxVal=0;
	attr.isClass=false;
	attributes.push_back(attr);

	if (argc < 5) {
		cerr << "Usage: -i <Input FileName> -K <Number of Cluster> [-c classAttribute] [-normalize]"; // Inform the user of how to use the program
		cin.get();
		exit(0);
	} else {
		int i=1;
		while(i <argc){
			if (string(argv[i]) == "-i") {
				//next argument should be the filename:
				i++;
				inputFile = argv[i++];
			
			}else if (string(argv[i]) == "-K" || string(argv[i]) == "-k") {
				i++;
				k =  atoi(argv[i++]);
			} else if (string(argv[i]) == "-c"){
				i++;
				attr.name = argv[i++];
				attr.minVal=0;
				attr.maxVal=0;
				attr.isClass=true;
				attributes.push_back(attr);
			}else if (string(argv[i]) == "-normalize"){
				useNormalize = true;
				i++;
			}
			else{
				cout << "Invalid arguments\n";
				exit(0);
			}
		}
		
	}

	startClustering(attributes,useNormalize,k,inputFile);
	return 0;
}
