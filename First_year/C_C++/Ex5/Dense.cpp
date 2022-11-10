#include "Dense.h"

/**
 * the Dense constructor, create a Dense instance that is a layer
 * of the network network
 * @param input_w wight Matrix
 * @param input_bias bias matrix
 * @param input_act activity function (ReLU/Softmax)
 */
Dense::Dense (const Matrix& input_w, const Matrix& input_bias,
              ActivationType input_act)
{
  w = input_w;
  bias = input_bias;
  act = input_act;
}

/**
 * returns the array of the weight matrices
 * @return array of the weight matrices
 */
const Matrix& Dense::get_weights() const {return w;}

/**
 * returns the array of the bias matrices
 * @return array of the bias matrices
 */
const Matrix& Dense::get_bias() const {return bias;}

/**
 * creates Activation instance with the relevant function
 * according to the layer.
 * @return Activation instance
 */
Activation Dense::get_activation() const
{
  Activation activ = Activation(act);
  return activ;
}

/**
 * Applies the layer on matrix
 * @param m the input matrix
 * @return new matrix after the layer was applied on it
 */
Matrix Dense::operator() (Matrix& m) const
{
  Matrix a = (w * m) + bias;
  Activation activ = get_activation();
  Matrix b = activ(a);
  return b;
}