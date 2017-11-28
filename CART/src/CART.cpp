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
	deleteTree(root);
	cout<<endl;
}

int CART :: deleteTree(Node* node){
/******************************************
*  Input:
*     explicit:
*     	1. node;
*  Output:
*     	1. 0: tree is deleted successfully;
*  Function:
*     Delete the decision tree 
*******************************************/
    if (node == nullptr) 
	    return 0;
 
    deleteTree(node->left);
    deleteTree(node->right);   
//
    cout<<"Deleting node with"<<endl;
    cout<<"      1. Feature Index:  "<<node->featureIndex<<endl;
    cout<<"      2. Split Value:    "<<node->splitValue<<endl;
    delete node;
    node=nullptr;

    return 0;
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
	if (StopCriterion(node,data)){
		Calculate_classResult(node,data,settings.treeType);
		return 0;
	}else{
		Split(node,data);

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
	float Gini_index_min=1,Gini_index_tmp;
	
	for(int fIndex=0;fIndex<data.featureNum;fIndex++){	
		float minEle,maxEle;
		minEle=maxEle=data.trainData[node->indexArray[0]][fIndex];
		for (auto ele:node->indexArray){
			if (minEle>data.trainData[ele][fIndex])
				minEle=data.trainData[ele][fIndex];
			if (maxEle<data.trainData[ele][fIndex])
				maxEle=data.trainData[ele][fIndex];
		}
		for(int j=0;j<=settings.featSplitNum;j++){
			splitValue=minEle+j*(maxEle-minEle)/settings.featSplitNum;
			if (settings.treeType==0){
				Gini_index_tmp=Calculate_GiniIndex(fIndex,splitValue,node,data);
				if(Gini_index_tmp<Gini_index_min){
					Gini_index_min=Gini_index_tmp;
					node->featureIndex=fIndex;
					node->splitValue=splitValue;
				}
			}else{
				// for regression tree;
			}
		
		}		
	}
	node->left=new Node(node->depth+1);				
	node->right=new Node(node->depth+1);
	for (auto ele:node->indexArray){
		if (data.trainData[ele][node->featureIndex]<=node->splitValue){
			node->left->indexArray.push_back(ele);
		}else{
			node->right->indexArray.push_back(ele);
		}
	}	
}

float CART :: Calculate_GiniIndex(int fIndex,float splitValue,Node* node,CART_data& data){
/******************************************
*  Input:
*     explicit:
*     	1. fIndex;
*     	2. splitValue;
*     	3. node;
*     	4. data;
*  Output:
*  	1. Gini_index_tmp;
*  Function:
*	Calculate the GiniIndex of feature fIndex based on the splitValue
*******************************************/
	unordered_map<float,int> groupLeft,groupRight;

	for (auto ele:node->indexArray){
		if (data.trainData[ele][fIndex]<=splitValue){
			groupLeft[data.trainData[ele].back()]++;
		}else{
			groupRight[data.trainData[ele].back()]++;

		}
	}
	float PL,PR;
	float pl=0,pr=0;
	PL=groupLeft.size()/node->indexArray.size();
	PR=groupRight.size()/node->indexArray.size();
	for (auto ele:groupLeft){
		pl+=ele.second*ele.second;
	}
	pl=pl/groupLeft.size()/groupLeft.size();
	for (auto ele:groupRight){
		pr+=ele.second*ele.second;
	}
	pr=pr/groupRight.size()/groupRight.size();
	return PL*(1-pl)+PR*(1-pr);	
}

bool CART :: StopCriterion(Node* node,CART_data& data){
/******************************************
*  Input:
*     explicit:
*     	1. node;
*     	2. data;
*  Output:
*  	1. boolean value: 1. true:  this is a terminal node
*  			  2. false: this is not a terminal node
*  Function:
*  	Determine if whether to stop the split proces: 
*  		True:  stop
*  		False: continue
*******************************************/
	// if class pool is homogeneous
	unordered_map<float,int> group;
	for (auto ele:node->indexArray){
		group[data.trainData[ele].back()]++;
	}
	if (group.size()==1)
		return true;
	//Criterion I: node depth
	if (node->depth>settings.maxDepth)
		return true;
	//Criterion II: class count
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
		unordered_map<float,int> hashtable;
		int count=0;
		for (auto ele:node->indexArray){
			hashtable[data.trainData[ele].back()]++;
			if (count<hashtable[data.trainData[ele].back()]) {
				count=hashtable[data.trainData[ele].back()];
				node->classResult=data.trainData[ele].back();
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
		fout<<"Number of features: "<<data.featureNum<<";"<<endl;
		fout<<"Size of the trainData: "<<data.trainDataSize<<";"<<endl;
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

