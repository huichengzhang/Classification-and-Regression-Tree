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

#define version        "V1.0"
#define version_date   "2017-11-25"

using namespace std;

struct CART_data
{
       vector< vector<float> > trainData;
       vector< vector<float> > testData;
       int featureNum;
//      members for the classification tree
//       unordered_set<int> classSet;
//       unordered_map<int,int> classCount; 
};

class CART
{
protected:
//	node* root;
	CART_data data;	
//      CART settings:
        const float TEST_RATIO=0.2;
public:
	CART();
	~CART();
	int Read_sampleFile(string sampleFile);
protected:
	void OutputData(CART_data& data);


//	void Learn();
//	void Evaluate();
//	float Predict();
};

