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
	//Update dataSet
	root->dataSet=data.trainData;
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
		int flag=Split(node,data);
		if(!flag){
			BuildTree(node->left,data);
			BuildTree(node->right,data);
		}
	}
	return 0;
}


int CART :: Split(Node* node,CART_data& data){
/******************************************
*  Input:
*     explicit:
*     	1. node;
*     	2. data;
*  Output:
*     	1. Stop splitting, skip building node.left and node.right, return;
*     	0. Continue splitting;
*  Function:
*  	1. Split dataSet according to the impurity function
*  		classification tree: Gini index;
*  		regression tree:  sum of square error;
*  	2. Update node:
*  		1. Update featureIndex, splitValue;
*  		2. Generate left and right nodes;	
*******************************************/
	int classCount;
	
	for(int fIndex=0;fIndex<data.featureNum;fIndex++){
		float splitValue;
		float Gini_index_min=1,Gini_index_tmp;
	
		sort(node->dataSet.begin(),node->dataSet.end(),
		     [fIndex](vector<float> rowi,vector<float> rowj){
		     return rowi[fIndex]<rowj[fIndex];
		     }
		);
		
		if (settings.treeType==0){
			vector< vector<float> >::iterator it;
			unordered_map<float,int> classSet_left,classSet_right;
			for (auto ele:node->dataSet){
				classSet_right[ele.back()]++;
			}	
			int count=1;		
			for (it=node->dataSet.begin();it!=node->dataSet.end();it++,count++){
				splitValue=(*it)[fIndex];
				// Calculate GiniIndex
				float PL,PR,scoreL,scoreR;
				PL=(float)count/float(node->dataSet.size());
				PR=1.0-PL;
				classSet_left[(*it).back()]++;
				classSet_right[(*it).back()]--;
				scoreL=0.0;
				for (auto ele:classSet_left){
					scoreL+=ele.second*ele.second;
				}
				scoreL=scoreL/count/count;
				scoreR=0.0;
				for (auto ele:classSet_right){
					scoreR+=ele.second*ele.second;
				}
				if (count==node->dataSet.size()){
					scoreR=0.0;
				}else{
					scoreR=scoreR/(node->dataSet.size()-count)/(node->dataSet.size()-count);
				}
				Gini_index_tmp=PL*(1.0-scoreL)+PR*(1.0-scoreR);
				//
				if(Gini_index_tmp<Gini_index_min){
					Gini_index_min=Gini_index_tmp;
					node->featureIndex=fIndex;
					node->splitValue=splitValue;
					classCount=count;
				}
			}

		}else{
			// for regression tree;
			
		}	
	}
	if (classCount==node->dataSet.size())
		return 1;
	node->left=new Node(node->depth+1);				
	node->right=new Node(node->depth+1);
	for (auto ele:node->dataSet){
		if (ele[node->featureIndex]<=node->splitValue){
			node->left->dataSet.push_back(ele);
		}else{
			node->right->dataSet.push_back(ele);
		}
	}	
	node->dataSet.clear();
	return 0;
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
	unordered_map<float,int> classTable;
	for (auto ele:node->dataSet){
		classTable[ele.back()]++;
	}
	if (classTable.size()==1)
		return true;
	//Criterion I: node depth
	if (node->depth>settings.maxDepth)
		return true;
	//Criterion II: class count
	if (node->dataSet.size()<=settings.minCount)
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
		unordered_map<float,int> classTable;
		int count=0;
		for (auto ele:node->dataSet){
			classTable[ele.back()]++;
			if (count<classTable[ele.back()]) {
				count=classTable[ele.back()];
				node->classResult=ele.back();
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

