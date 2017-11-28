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

CART :: CART()
{

}

CART :: ~CART()
{
//delete tree

}
void CART :: Learn(){
/******************************************
*  Input:
*     implicit:
*     	1. root;
*     	2. data;
*  Output:
*     void;
*  Function:
*     Build the decision tree 
*******************************************/
	//Build and initialization boolIndexArray
	//Update indexArray
	for (int i=0;i<data.trainDataSize;i++)
		root->indexArray.push_back(i);
	BuildTree(root,data);
}

int CART :: BuildTree(Node* node,CART_data& data){
/******************************************
*  Input:
*     explicit:
*	1. node;
*	2. data;
*  Output:
*     void;
*  Function:
*     Build the decision tree 
*******************************************/
	if (StopCriterion(node)){
		Calculate_classResult(node,data,settings.treeType);
		return 0;
	}else{
		Split(node,data);
//
		BuildTree(node->left,data);
		BuildTree(node->right,data);
	}
	return 0;
}




void CART :: Split(Node* node,CART_data& data){
/******************************************
*  Input:
*     explicit:
*     	1. node;
*     	2. data;
*  Output:
*     void;
*  Function:
*  	1. Split dataSet according to the impurity function
*  		classification tree: Gini index;
*  		regression tree:  sum of square error;
*  	2. Update node:
*  		1. Update featureIndex, splitValue;
*  		2. Generate left and right nodes;	
*******************************************/
	float splitValue;
	int featureIndex;
	float Gini_index;


	for(size_t i=0;i<data.featureNum;i++){
				

		for(size_t j=0;j<node->indexArray.size();j++){
		   	
		}		
	}
}




bool CART :: StopCriterion(Node* node){
/******************************************
*  Input:
*     explicit:
*     	1. node
*  Output:
*  	1. boolean value: 1. true:  this is a terminal node
*  			  2. false: this is not a terminal node
*  Function:
*  	Determine if whether to stop the split proces: 
*  		True:  stop
*  		False: continue
*******************************************/
	//Criterion I: node depth
	if (node->depth>settings.maxDepth)
		return true;
	if (node->indexArray.size()<=settings.minCount)
		return true;
	return false;
}

void CART :: Calculate_classResult(Node* node,CART_data& data,int treeType){
/**************************************************************
*  Input:
*     explicit:
*     	1. node;
*     	2. data;
*     	3. treeType;
*  Output:
*  	void;
*  Function:
*  	Calculate the leaf class result based on the treeType	
**************************************************************/
	if (treeType==0){
		unordered_map<int,int> hashtable;
		int count=0,index;
		for (auto ele:node->indexArray){
			hashtable[data.trainData[ele].back()]++;
			if (count<hashtable[data.trainData[ele].back()]) {
				count=hashtable[data.trainData[ele].back()];
				node.classResult=data.trainData[ele].back();
			}		
		}	
		
	}else{
		// for regression tree;
	}
}


int CART :: Read_sampleFile(string sampleFile)
{
/******************************************
*  Input:
*     explicit:
*        1. Sample file;
*     implicit: 
*        1. CART data; 
*  Output:
*     1. boolean value;   
*  Function:
*     Read data from sample file; 
*     Update data:
*     	1. trainData
*     	2. testData
*     	3. featureNum
*     	4. trainDataSize
*     	5. testDataSize
*     Output data for checking purpose;
******************************************/	
	ifstream fin(sampleFile.c_str());
	if(fin.is_open()){
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
			if(rand()%10<=settings.test_ratio*10){
				data.testData.push_back(lineVector);	
			}else{
				data.trainData.push_back(lineVector);
			}
		}
		//  update featureNum
		data.featureNum=data.trainData[0].size()-1;
		data.trainDataSize=data.trainData.size();
		data.testDataSize=data.testData.size();
		// CheckInputs
		OutputData(data);
		return 0;
	}else{
		cerr<<"Error opening file: "<<sampleFile<<endl;
		return 1;
	}	
	fin.close();
}

void CART :: OutputData(CART_data& data){
/******************************************
*  Input:
*     explicit:
*        1. CART data;; 
*  Output:
*     1. void;   
*  Function:
*  	Output the data stored in data.trainData...
*  	for checking purpose;
******************************************/	
	ofstream fout("Check.txt",ofstream::out|ofstream::trunc);
	if (fout.is_open()){
		int output_line_num;
		output_line_num=10<data.trainData.size()?10:data.trainData.size();
		fout<<"Number of features: "<<data.featureNum<<";";
		fout<<"Size of the trainData: "<<data.trainDataSize<<";";
		fout<<"Size of the testData: "<<data.testDataSize<<endl<<endl;

		for (int i=0;i<output_line_num;i++){
			for (auto ele:data.trainData[i]){
				fout<<ele<<",";
			}
			fout<<endl;				
		}
	}
	fout.close();
}

