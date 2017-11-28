/*********************************************************************
*
* 	Classification and Regression Tree (CART) V1.0
* 
* 	Author: Lingbo Zhang
*	11/22/2017 at Massachusetts Institute of Technology
*	Email: lingboz2015@gmail.com
* 
**********************************************************************/
#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<math.h>
#include<cstdlib>
#include<utility>

#define version        "V1.0"
#define version_date   "2017-11-25"

using namespace std;

class Node{	
public:	
	Node* left;
	Node* right;
	int depth;
	int featureIndex;
	float splitValue;
	float classResult;
	vector<int> indexArray;
	//default constructor
	Node(){
		left=nullptr;
		right=nullptr;
		depth=0;
		featureIndex=-1;
		splitValue=0;
		classResult=0;
	}
	Node(int d){
		depth=d;
		left=nullptr;
		right=nullptr;
		depth=0;
		featureIndex=-1;
		splitValue=0;
		classResult=0;
	}
	// destructor
};


struct CART_data{
	
       vector< vector<float> > trainData;
       vector< vector<float> > testData;
       int featureNum;
       int trainDataSize;
       int testDataSize;
//      members for the classification tree
//       unordered_set<int> classSet;
//       unordered_map<int,int> classCount; 
};

struct CART_settings{
	int treeType;   // treeType 0: classification tree
	                //          1: regression tree
	float test_ratio;
	int maxDepth;
	int minCount;
	int featSplitNum;
	CART_settings(){
		treeType=0;
		test_ratio=0.2;
		maxDepth=10;
		minCount=1;
		featSplitNum=10;
	}
};

class CART{
	
protected:
	Node* root=new Node(0);
// CART data
	CART_data data;	
// CART settings
	CART_settings settings;
	
public:
	CART();
	~CART();
//	void Set_configurations();
	int Read_sampleFile(string sampleFile);
	void Learn();
//	void Evaluate();
//	float Predict();
	
protected:
	void  OutputData(CART_data& data);
	int   BuildTree(Node* node,CART_data& data);
	bool  StopCriterion(Node* node,CART_data& data);
	void  Calculate_classResult(Node* node,CART_data& data,int treeType);
	void  Split(Node* node,CART_data& data);
	float Calculate_GiniIndex(int fIndex,float splitValue,Node* node,CART_data& data);
	int   deleteTree(Node* node);

};

