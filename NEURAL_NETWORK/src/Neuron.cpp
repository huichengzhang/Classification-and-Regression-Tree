/*********************************************************************
*
* 	Neural Network V1.0
* 
* 	Author: Lingbo Zhang
*	11/22/2017 at Massachusetts Institute of Technology
*	Email: lingboz2015@gmail.com
* 
**********************************************************************/
#include"Neuron.hpp"
// Constructor
Neuron::Neuron{double val}{
	this->val=val;
	Activate();
	Derive();
// Fast Sigmoid Function
// f(x)=x/(1+|x|)
void Neuron :: Activate(){
	this->activatedVal=this->val/(1.0+abs(this->val));
}
// Derivative for fast sigmoid function
// f'(x)=f(x)*(1-f(x))
void Neuron :: Derive(){
	this->derivedVal=this->activatedVal*(1-this->activatedVal);
}


}
