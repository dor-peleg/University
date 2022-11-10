//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Digit.h"
#include "Dense.h"

#define MLP_SIZE 4

//
const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork{
 public:
  /**
   * MlpNetwork constructor, Accepts 2 arrays, size 4 each.
   * one for weights and one for biases, constructs the network.
   * @param wights array of weight matrices
   * @param biases array of biases matrices
   */
  MlpNetwork(const Matrix (&wights)[MLP_SIZE],
             const Matrix (&biases)[MLP_SIZE]);
  /**
   * Applies the entire network on input matrix
   * @param img the input matrix
   * @return  digit struct with the result and the probability.
   */
  digit operator() (Matrix& img) const;
 private:
  const Matrix (&weights)[MLP_SIZE];
  const Matrix (&biases)[MLP_SIZE];
};
#endif // MLPNETWORK_H
