/* Pseudocode for CART (C++)
*  This file contains and explains psedocode for the CART (C++).
*  Pseudocode for CART
*/
struct node
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
  }
}

Class CART
{
protected:
  node* root;
  trainSet;
  testSet;
public:
  CART();
  ~CART();
//
  void Learn(root,trainSet);
  void Evaluate(root,testSet);
  float Predict(root,data);
}
// Pseudocode for Learn
void Learn(root,trainSet)
{
// Input: root,traindataset
// Output: 
// Function: build CART
  int BuildTree(root,trainSet);
}

// Pseudocode for BuildTree
int BuildTree(node,dataSet)
{
// Input: node,dataSet
// Output: 
// Function: build CART
if Stop(dataSet)
{
   Calculate_classResult(node,dataSet);
   return 0;
}else{
   node->left=new node();
   node->right=new node();
   Split(node,dataSet,left_dataSet,right_dataSet);
   BuildTree(node->left,left_dataSet);
   BuildTree(node->right,right_dataSet);
}
return 0;
}
// Pseudocode for Split
void Split(node,dataSet,left_dataSet,right_dataSet)
{
/* Input: node,dataSet,left_dataSet,right_dataSet
*  Output:
*  Function: 
* 	update node;
*	split dataSet into left_dataSet and right_dataSet
*/
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
void GetGini(featureId,dataSet,gini,splitValue,tmp_left,tmp_right)
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
*/

}




