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

#include<vector>
#include<utility>
#include<algorithm>

#define VERSION        "V1.0"
#define VERSION_DATA   "2017-11-22"

using namespace std;


// feature 
class dataSet
{
	// feature set first:feature value; second: feature index
	vector< vector< pair <float,int> > feature_set;
	// class set
	vector<float> class_set;
};

// node 
struct node
{
 node* leftChild;
 node* rightChild;
 int featureId;
 float splitValue;
 float classResult;   // output class
};


class CART
{
protected:

public:
	CART();
	~CART();

protected:
	void create_regression_tree();

};



