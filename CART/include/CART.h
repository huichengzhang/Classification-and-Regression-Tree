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
#include<limits>
#include<cstdlib>
#include<utility>
#include"Node.h"

#define version        "V1.0"
#define version_date   "2017-11-25"

using namespace std;

struct CART_data{
	
       vector< vector<float> > trainData;
       vector< vector<float> > testData;
       int featureNum;
       int trainDataSize;
       int testDataSize;
};

struct CART_settings{
	int treeType;   // treeType 0: classification tree
	                //          1: regression tree
	float test_ratio;
	int maxDepth;
	int minCount;
// regression tree
	CART_settings(){
		treeType=0;
		test_ratio=0.2;
		maxDepth=8;
		minCount=2;
//  regression tree
	}
};

class CART{
	
protected:
	Node* root;
// CART data
	CART_data data;	
// CART settings
	CART_settings settings;
	
public:
	CART();
	~CART();
//	void Set_configurations();
	void Configure_Set_depth(int depth);
	int  Read_sampleFile(string sampleFile);
	void Learn();
	void Evaluate();
	void Predict(vector<float>& dataRow);
	
protected:
	void  OutputData(CART_data& data);
	int   BuildTree(Node* node);
	bool  StopCriterion(Node* node);
	void  Calculate_classResult(Node* node,int treeType);
	int   Split(Node* node);	
//	int   DeleteTree(Node* node);
	int   PrintTree(Node* node);
};

