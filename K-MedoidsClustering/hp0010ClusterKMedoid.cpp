#include "hp0010ClusterKMedoid.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/**
* Finds Euclidean distance between two data object
* @param data Data object (x1,y1,z1,....)
* @param medoid Medoid object (x2,y2,z2,...)
* @return distance between two data objects
*/
double Cluster::findDistance(vector<double> data, vector<double> medoid){
	double distance =0.0;
	for(int i = 0; i< (int)data.size(); i++){
		distance += (data[i] - medoid[i])*(data[i] - medoid[i]);
	}
	distance = sqrt(distance);
	return distance;
}
/**
* Sets size of data objects
* @param sz Size of data objects
*/
void Cluster::setSize(int sz){
	size = sz;

}

/**
* Gets size of data objects
* @return Size of data objects
*/
int Cluster::getSize(){
	return size;
}

/**
* Forms cluster using the given medoids
* @param clusterDataVector Data vector to be clustered
*/
void Cluster::formCluster(ClusterData* clusterDataVector){

	double distance;
	//double distance1;
	for(int j = 0;j<size; j++){
		//clusterKey=0;
		if(!clusterDataVector[j].isMedoid){
			for(int i =0; i< size; i++){
				if(clusterDataVector[i].isMedoid){ 
					//clusterKey++;
					//distance = findDistance(clusterDataVector[i].objectData,clusterDataVector[j].objectData);
					distance = clusterDataVector[i].distance[clusterDataVector[j].originalId-1];
					if(distance < clusterDataVector[j].minDistance){
						clusterDataVector[j].minDistance = distance;
						clusterDataVector[j].tempClusterID = clusterDataVector[i].tempClusterID;
					}
				}
			}
		}
	}
}

/**
* Gives Sum of cost of the clustering
* @param clusterDataVector Data vector 
* @return Sum of Cost
*/
double Cluster::sumOfCost(ClusterData* clusterDataVector){
	double sumCost=0.0;
	for(int i =0;i<size;i++){
		if(!clusterDataVector[i].isMedoid){
			sumCost += clusterDataVector[i].minDistance;
		}
	}
	return sumCost;
}

/**
* Gets detail information about the medoid
* @param clusterData Data after clustering
* @return 2D vector containing medoid information
*/
vector<vector<double> > Cluster::getMediodInfo(ClusterData clusterData[]){
	vector<vector<double> > mediodOut;
	vector<double> tempData;
	for(int i = 0;i<size;i++){
		if(clusterData[i].isMedoid){
			for(int j = 0;j< (int)clusterData[i].objectData.size();j++){
				tempData.push_back(clusterData[i].objectData[j]);
			}
			tempData.push_back(clusterData[i].originalId);
			mediodOut.push_back(tempData);
			tempData.clear();
		}
	}
	return mediodOut;
}

/**
* Gets detail information about the medoid
* @param clusterData Data after clustering
* @param originalData Data before normalization and clustering 
* @return 2D vector containing medoid information
*/
vector<vector<double> > Cluster::getMediodInfo(ClusterData* clusterData,vector<vector<double> > originalData){
	vector<vector<double> > mediodOut;
	vector<double> tempData;
	for(int i = 0;i<size;i++){
		if(clusterData[i].isMedoid){
			tempData = (originalData[clusterData[i].originalId-1]);
			tempData.push_back(clusterData[i].originalId);
			mediodOut.push_back(tempData);
			tempData.clear();
		}
	}
	return mediodOut;
}
/**
* Gets clustering output
* @param clusterData Data after clustering
* @param originalData Data before normalization and clustering 
* @return 2D vector containing clustering output
*/
vector<vector<double> > Cluster::getClusterOutput(ClusterData* clusterData,vector<vector<double> > originalData){
	vector<vector<double> > clusterOut;
	vector<double> tempData;
	double id;
	for(int i = 0;i<size;i++){
		id= clusterData[i].clusterID;
		tempData = (originalData[clusterData[i].originalId-1]);
		/*for(int j = 0;j< clusterData[i].objectData.size();j++){
		tempData.push_back(clusterData[i].objectData[j]);
		}*/
		tempData.push_back(clusterData[i].originalId);
		for(int k =0; k<size;k++){
			if(clusterData[k].isMedoid && clusterData[k].clusterID == clusterData[i].clusterID){
				id= clusterData[k].originalId;
			}
		}
		tempData.push_back(id);
		clusterOut.push_back(tempData);
		tempData.clear();	

	}
	return clusterOut;
}

/**
* Gets clustering output
* @param clusterData Data after clustering 
* @return 2D vector containing clustering output
*/
vector<vector<double> > Cluster::getClusterOutput(ClusterData clusterData[]){
	vector<vector<double> > clusterOut;
	vector<double> tempData;
	double id;
	for(int i = 0;i<size;i++){
		id= clusterData[i].clusterID;
		tempData = clusterData[i].objectData;
		/*for(int j = 0;j< clusterData[i].objectData.size();j++){
		tempData.push_back(clusterData[i].objectData[j]);
		}*/
		tempData.push_back(clusterData[i].originalId);
		for(int k =0; k<size;k++){
			if(clusterData[k].isMedoid && clusterData[k].clusterID == clusterData[i].clusterID){
				id= clusterData[k].originalId;
			}
		}
		tempData.push_back(id);
		clusterOut.push_back(tempData);
		tempData.clear();	

	}
	return clusterOut;
}
