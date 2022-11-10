#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"

/**
 * this class generate the layers of the network network
 */
class Dense
{
 public:
  /**
   * the Dense constructor, create a Dense instance that is a layer
   * of the network network
   * @param input_w wight Matrix
   * @param input_bias bias matrix
   * @param input_act activity function (ReLU/Softmax)
   */
  Dense(const Matrix& input_w, const Matrix& input_bias,
        ActivationType input_act);
  /**
   * returns the array of the weight matrices
   * @return array of the weight matrices
   */
  const Matrix& get_weights() const;
  /**
   * returns the array of the bias matrices
   * @return array of the bias matrices
   */
  const Matrix& get_bias() const;
  /**
   * creates Activation instance with the relevant function
   * according to the layer.
   * @return Activation instance
   */
  Activation get_activation() const;
  /**
   * Applies the layer on matrix
   * @param m the input matrix
   * @return new matrix after the layer was applied on it
   */
  Matrix operator()(Matrix& m) const;

 private:
  Matrix w;
  Matrix bias;
  ActivationType act;
};

#endif //C___PROJECT_DENSE_H
