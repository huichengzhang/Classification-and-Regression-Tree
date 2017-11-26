/*********************************************************************
*
* 	Classification and Regression Tree (CART) V1.0
* 
* 	Author: Lingbo Zhang
*	11/22/2017 at Massachusetts Institute of Technology
*	Email: lingboz2015@gmail.com
* 
**********************************************************************/
#include "CART.h"

CART::CART()
{

}

CART::~CART()
{

}

int CART :: Read_sampleFile(string sampleFile)
{
/******************************************
*  Input:
*     explicit:
*        1. Sample file; 
*     implicit:
*        2. CART data; 
*  Output:
*     1. void;   
*  Function:
*     Read data from sample file; 
*     Update data
*     trainData, testData, classSet(classification tree), featureSet...
*     classCount(classification tree);
******************************************/	
	ifstream fin(sampleFile.c_str());
	if(!fin){
		cerr<<"Error opening file: "<<sampleFile<<endl;
		return 1;
	}else{
		string lineStr;
		while (getline(fin,lineStr)){
			istringstream lineStream(lineStr);
			string field;
			vector<float> lineVector;
			while(getline(lineStream,field,',')){
				float fieldValue=stof(field);
				//
				lineVector.push_back(fieldValue);
				lineStream>>ws;
			}
			if(rand()%10<TEST_RATIO*10){
				data.testData.push_back(lineVector);	
			}else{
				data.trainData.push_back(lineVector);
			}
		}
		return 0;
	}	
}
