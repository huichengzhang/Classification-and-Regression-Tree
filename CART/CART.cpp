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





void CART :: Read_sampleFile(string sampleFile,CART_data& data)
{
/******************************************
*  Input:
*     1. Sample file; 
*     2. CART data;
*  Output:
*     1. void;   
*  Function:
*     Read data from sample file; 
*     Update data
*     trainData, testData, classSet(classification tree), featureSet...
*     classCount(classification tree);
******************************************/
	
	ifstream fin(sampleFile.c_str());
	if(!fin)
	{
		cerr<<"Error opening file: "<<sampleFile<<endl;
		return 0;
	}else{
		string lineStr;
		while (getlien(fin,lineStr))
		{
			if()
			{

			}else
			}	
		}
	}	



}
