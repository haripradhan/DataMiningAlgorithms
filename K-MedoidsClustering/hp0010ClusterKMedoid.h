/* -------------------
** hp0010ClusterKMedoid.h
** Hari Pradhan
** 09/20/2012
** ------------------*/
#ifndef ClUSTER_H
#define ClUSTER_H

#include<iostream>
#include<vector>
using namespace std;

typedef struct{
	vector<double> objectData;
	vector<double> distance;
	int clusterID;
	int tempClusterID;
	bool isMedoid;
	double minDistance;
	int originalId;

}ClusterData;

typedef struct{
	int originalMediodID;
	int replacementMediodID;
	double cost;
	bool isReplaced;
}Statistic;

class Cluster{
private: 
	//Size of data objects
	int size;
public:
	//Finds Euclidean distance between two data object
	double findDistance(vector<double> , vector<double>);

	//Forms cluster using the given medoid
	void formCluster(ClusterData*);

	//Gives Sum of cost of the clustering
	double sumOfCost(ClusterData*);

	//Gets detail information about the medoid
	vector<vector<double> > getMediodInfo(ClusterData[]);
	vector<vector<double> > getMediodInfo(ClusterData*,vector<vector<double> > originalData);

	//Gets clustering output
	vector<vector<double> > getClusterOutput(ClusterData[]);
	vector<vector<double> > getClusterOutput(ClusterData*,vector<vector<double> > originalData);

	//Sets size of data objects
	void setSize(int);

	//Gets size of data objects
	int getSize();
};

#endif
