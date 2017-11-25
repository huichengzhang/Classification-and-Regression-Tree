/* Pseudocode for CART (C++)
*  This file contains and explains psedocode for the CART (C++).
*  Pseudocode for CART
*/






class node
{
  node* left;
  node* right;
  int featureId;
  float splitValue;
  float classResult;
  node()
  {
    left=NULL;
    right=NULL;
    featureId=-1;
    splitValue=NULL;
    classResult=NULL;
  };
  ~node()
  { 
	  
  }

}

Class CART
{
protected:
  node* root;
  vector< vector<float> > trainData;
  vector< vector<float> > testData;
  vector< int > trainIndexSet;
  vector< int > testIndexSet;
  set< int > classSet;
  set< int > featureSet;
protected:
  float Calculate_classResult(vector< vector<float> >& data, vector< int >& dataIndex);

  
   
public:
  CART();
  ~CART();
//
  void Read_sampleFile(string sampleFile,vector< vector<float> >& trainData, vector< vector<float> >& testData);
//
  void Learn(root,trainSet);
  void Evaluate(root,testSet);
  float Predict(root,data);
}

// Pseudocode for Learn
void Learn(root,trainIndexSet)
{
// Input: root,traindataset
// Output: 
// Function: build CART
  int BuildTree(root,trainIndexSet);
}

// Pseudocode for BuildTree
int BuildTree(node,dataIndexSet)
{
// Input: node,dataSet
// Output: 
// Function: build CART
if StopCriterion(dataIndexSet)
{
   Calculate_classResult(node,dataIndexSet);
   return 0;
}else{
   node->left=new node();
   node->right=new node();
   Split(node,dataIndexSet,left_dataIndexSet,right_dataIndexSet);
   BuildTree(node->left,left_dataIndexSet);
   BuildTree(node->right,right_dataIndexSet);
}
return 0;
}
// Pseudocode for Stop
bool StopCriterion()
{
/***************************************************** 
*  Input: 
*  Output:
*  Function: 
* 	Constraints for tree construction:
* 	1. Tree depth;
* 	2. 
*
*******************************************************/

    
}
// Pseudocode for Split
void Split(node,dataSet,left_dataIndexSet,right_dataIndexSet)
{
/***************************************************** 
*  Input: node,dataSet,left_dataSet,right_dataSet
*  Output:
*  Function: 
* 	update node;
*	split dataSet into left_dataSet and right_dataSet
******************************************************/
	float miniGini=1;
	float gini
	float splitValue;
	for featureId in featureIds
	{
	    GetGini(featureId,dataSet,gini,splitValue,tmp_left,tmp_right);
	    if gini<miniGini
	    {
	       miniGini=gini;
	       node->featureId=featureId;
	       node->splitValue=splitValue;
	       left_dataSet=tmp_left;
	       right_dataSet=tmp_right;	       
	    }
	}	
}
// Pseudocode for GetGini
void GetGini(featureId,dataSet,miniGini,splitValue,leftIndexSet,rightIndexSet)
{
/* Input: 
*       featureId 
*       dataSet 
*       splitValue 
*       gini
*       tmp_left 
*       tmp_right
*  Output:
*  Function: 
* 	calculate mini gini from dataSet based on featureId 
*	split dataSet into left_dataSet and right_dataSet
*
*/
        sort(dataSet.begin(),dataSet.end(),[trainData](int i, int j){return trainData[i]<trainData[j];});
	map<int,int> plk,prk;
	for (size_t i=0;i<dataSet.size();i++)
	{	    
	    splitValue_tmp=trainData[index];
	    int Pl=i+1;
	    int Pr=dataSet.size()-Pl;
	    plk[trainData[index][]]+=1
	    prk[trainData[index][]]-=1
	    for(auto val:plk)
	    {
		int giniLeft+=val.second*val.second;
	    }
	    for(auto val:prk)
	    {
		int giniRight+=val.second*val.second;
	    }	    
	}

	for splitValue in splitValues
	{
	    Pl=;
	    Pr=;
	    giniLeft=0.0;
            giniRight=0.0;
	    for k in classes
	    {
		giniLeft+=plk*plk;
		giniRight+=prk*prk;
	    }
	    gini=Pl*giniLeft+Pr*giniRight;
	    if gini<miniGini
	    {
	       miniGini=gini;
	       splitValue=splitValue;
	       tmp_left=;
	       tmp_right=;
	    }
	    
	}
}




