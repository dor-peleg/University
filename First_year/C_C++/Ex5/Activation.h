//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

/**
 * Activation class, stores the activation functions
 * and the type of the activation
 */
class Activation
{
 public:
  /**
   * Activation constructor, create instance according to the
   * ActivationType it gets
   * @param act the ActivationType (the activation function to use)
   */
  explicit Activation(ActivationType act);
  /**
   * return the ActivationType (the activation function to use)
   * @return the ActivationType (the activation function to use)
   */
  ActivationType get_activation_type() const;
  /**
   * gets a matrix and Applies activation function on it according to the
   * ActivationType
   * @param m the matrix to apply the function on.
   * @return new matrix that is the input matrix after apply the function on.
   */
  Matrix operator()(const Matrix& m) const;
 private:
  ActivationType act;
  /**
   * ReLU activation function, gets a matrix and for every cell, if value < 0,
   * the function change it to 0.
   * @param m matrix
   * @return A new matrix which is the input matrix after
   * the function has been activated on it
   */
  static Matrix relu(const Matrix& m);
  /**
   * Softmax activation function, gets a matrix and normalizes it
   * into a probability distribution.
   * @param m the matrix
   * @return A new matrix which is the input matrix after
   * the function has been activated on it.
   */
  static Matrix softmax(const Matrix& m);
};

#endif //ACTIVATION_H
