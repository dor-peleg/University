#include "Activation.h"
#include <cmath>

/**
 * Activation constructor, create instance according to the
 * ActivationType it gets
 * @param act the ActivationType (the activation function to use)
 */
Activation::Activation (ActivationType act): act{act}{}

/**
 * return the ActivationType (the activation function to use)
 * @return the ActivationType (the activation function to use)
 */
ActivationType Activation::get_activation_type () const {return act;}

/**
 * ReLU activation function, gets a matrix and for every cell, if value < 0,
 * the function change it to 0.
 * @param m matrix
 * @return A new matrix which is the input matrix after
 * the function has been activated on it
 */
Matrix Activation::relu (const Matrix& m)
{
  Matrix new_mat = m;
  for (int i=0; i<new_mat.get_rows() * new_mat.get_cols(); i++)
    {
      if (m[i]<0)
        new_mat[i] = 0;
    }
  return new_mat;
}

/**
 * Softmax activation function, gets a matrix and normalizes it
 * into a probability distribution.
 * @param m the matrix
 * @return A new matrix which is the input matrix after
 * the function has been activated on it.
 */
Matrix Activation::softmax (const Matrix& m)
{
  Matrix new_mat = m;
  float sum = 0;
  for (int i=0; i<m.get_rows() * m.get_cols(); i++)
    {
      sum += std::exp(m[i]);
    }
  float coefficient = 1/sum;
  for (int i=0; i<m.get_rows() * m.get_cols(); i++)
    {
      new_mat[i] = ((float)exp((double)m[i])) * coefficient;
    }
  return  new_mat;
}

/**
 * gets a matrix and Applies activation function on it according to the
 * ActivationType
 * @param m the matrix to apply the function on.
 * @return new matrix that is the input matrix after apply the function on.
 */
Matrix Activation::operator() (const Matrix& m) const
{
  switch (act)
    {
    case RELU:
      {
        Matrix relu_mat = relu (m);
        return relu_mat;
      }
  case SOFTMAX:
    {
      Matrix softmax_mat = softmax (m);
      return softmax_mat;
    }
    }
    return m;
}
