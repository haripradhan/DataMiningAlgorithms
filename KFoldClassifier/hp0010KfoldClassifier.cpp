/* -------------------
** hp0010KfoldClassfier.cpp
** Hari Pradhan
** 11/17/2012
** ------------------*/

#include "hp0010KfoldClassifier.h"

/**
* Default Constructor
*/
Classifier::Classifier(){

}

/**
* Test classififier
* @param classAttribute Class attribute 
*/
void Classifier::testClassifier(Attribute classAttribute){
	vector<double> p_result;
	for(size_t i =0; i< testData.size(); i ++){
		testData[i].push_back(testClassifierForSingleData(classAttribute,testData[i]));
	}
}

/**
* Test classifier for single record
* @param classAttribute Class attribute
* @param data 1D data record
* @return int predicted class label
*/
int Classifier::testClassifierForSingleData(Attribute classAttribute,vector<double> data){
	vector<double> p_result;
	double p;
	for(size_t i =0; i< classAttribute.possibleValues.size(); i ++){
		p=1;
		for(size_t j =0 ; j< data.size() - 1; j++){
			p *= attributeList[j].probability[(int)data[j]][i];
		}
		p_result.push_back(p);
	}

	//find max
	double maxProb = p_result[0];
	int maxIndex = 0;
	for(size_t i =1; i< p_result.size(); i ++){
		if(p_result[i] > maxProb){
			maxProb = p_result[i];
			maxIndex = i;
		}
	}

	return classAttribute.possibleValues[maxIndex];
}

/**
* Train classififier with trained data
* @param classAttribute Class attribute 
*/
void Classifier::trainClassifier(Attribute classAttribute){
	vector<double> countPerGroupInClassAttibute;
	
	for(size_t i =0; i < attributeList.size(); i++){
		for(size_t j = 0 ; j < attributeList[i].possibleValues.size(); j++){
			attributeList[i].count.push_back(count(classAttribute,attributeList[i].key,attributeList[i].possibleValues[j],trainedData));
		}
	}

	for(size_t i =0; i < attributeList[0].count[0].size(); i++){
		double count =0.0;
		for(size_t j = 0 ; j < attributeList[0].count.size(); j++){
				count += attributeList[0].count[j][i];
		}
		//cout<<"count: "<< count<<endl;
		countPerGroupInClassAttibute.push_back(count);
	}

	for(size_t i =0; i < attributeList.size(); i++){
		for(size_t j = 0 ; j < attributeList[i].possibleValues.size(); j++){
			attributeList[i].probability.push_back(probability(attributeList[i].count[j],countPerGroupInClassAttibute));
		}
	}

	//for(size_t i =0; i < attributeList.size(); i++){
	//	for(size_t j = 0 ; j < attributeList[i].possibleValues.size(); j++){
	//		cout<<attributeList[i].probability[j][0]<<"\t"<<attributeList[i].probability[j][1]<<endl;
	//	}
	//	cout<<endl;
	//}
}

/**
* Count of record having same attribute value and class value
* @param classAttribute Class attribute 
* @param attrKey attribute id (key) 
* @param attrValue attibute value
* @param data 2D data
* @return vector<int> count of record with attribute value = attrvalue for attrribute = attrkey
*/
vector<int> Classifier::count(Attribute classAttribute,int attrKey,double attrValue,vector<vector<double> > data){
	vector<int> count;
	vector<int> possibleVal = classAttribute.possibleValues;
	for(size_t i = 0; i < possibleVal.size(); i++){
		count.push_back(0);
	}

	for(size_t i = 0 ; i < data.size(); i ++){
		if(data[i][attrKey] == attrValue){
			for(size_t j = 0; j < possibleVal.size(); j++){
				if(data[i][classAttribute.key] == possibleVal[j]){
					count[j] ++;
				}
			}
		}
	}
	return count;
}
/**
* Probability having same attribute value and class value
* @param count 1D count vector
* @param countPerGroupInClassAttibute count per group in class attribute
* @return vector<double> probability
*/
vector<double> Classifier::probability(vector<int> count,vector<double> countPerGroupInClassAttibute){
	double m = 3;
	double p = 0.5;
	vector<double> prob;
	for(size_t i =0; i < count.size(); i++){
		prob.push_back(double(count[i]  + m * p )/(countPerGroupInClassAttibute[i] + m));
	}
	return prob;

}

/**
* Sets 2D test data
* @param data 2D test data
*/
void Classifier::setTestData(vector<vector<double> > data){
	testData = data;
}
/**
* Sets 2D trained data
* @param data 2D trained data
*/
void Classifier::setTrainedData(vector<vector<double> > data){
	trainedData = data;
}

/**
* Gets 2D test data
* @return vector<vector<double> > 2D test data
*/
vector<vector<double> > Classifier::getTestData(){
	return testData;
}

/**
* Gets 2D trained data
* @return vector<vector<double> > 2D trained data
*/
vector<vector<double> > Classifier::getTrainedData(){
	return trainedData;
}

/**
* Gets attribute list
* @return vector<Attribute> list of attribute
*/
vector<Attribute> Classifier::getattributeList(){
	return attributeList;
}

/**
* Sets attribute list
* @param attrList attribute list
*/
void Classifier::setAttributeList(vector<Attribute> attrList){
	attributeList = attrList;
}
