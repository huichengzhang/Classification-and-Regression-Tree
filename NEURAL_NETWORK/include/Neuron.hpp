/*********************************************************************
*
* 	Neural Network V1.0
* 
* 	Author: Lingbo Zhang
*	11/22/2017 at Massachusetts Institute of Technology
*	Email: lingboz2015@gmail.com
* 
**********************************************************************/
#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <iostream>
#include <math.h>

using namespace std;

class Neuron
{
public:
   Neuron(double val);
   // Fast Sigmoid Function
   // f(x)=x/(1+|x|)
   void Activate();

   // Derivative for fast sigmoid function
   // f'(x)=f(x)*(1-f(x))
   void Derive();

   // Getter
   double GetVal() { return this->val; }
   double GetActivatedVal { return this->activatedVal; }
   double GetDerivedVal() { return this->derivedVal; }

private:
   double val;
   double activatedVal;
   double derivedVal;
};

#endif
