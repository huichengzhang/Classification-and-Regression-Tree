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

using namespace std;

class Node{	
public:	
	Node* left;
	Node* right;
	int depth;
	int featureIndex;
	float splitValue;
	float classResult;
	vector< vector<float> > dataSet;
	//default constructor
	Node();
	Node(int d);
	// destructor
};

