#include "MlpNetwork.h"

/**
 * MlpNetwork constructor, Accepts 2 arrays, size 4 each.
 * one for weights and one for biases, constructs the network.
 * @param wights array of weight matrices
 * @param biases array of biases matrices
 */
MlpNetwork::MlpNetwork (const Matrix (&input_wights)[MLP_SIZE],
                        const Matrix (&input_biases)[MLP_SIZE]) :
                        weights(input_wights), biases(input_biases){}

/**
 * Applies the entire network on input matrix
 * @param img the input matrix
 * @return  digit struct with the result and the probability.
 */
digit MlpNetwork::operator() (Matrix& img) const
{

  Dense first_dense = Dense(weights[0],
                            biases[0],
                            RELU);
  Dense second_dense = Dense (weights[1],
                              biases[1],
                              RELU);
  Dense third_dense = Dense (weights[2],
                             biases[2],
                             RELU);
  Dense fourth_dense = Dense (weights[3],
                              biases[3],
                              SOFTMAX);

  Matrix r1 = first_dense(img);
  Matrix r2 = second_dense(r1);
  Matrix r3 = third_dense(r2);
  Matrix r4 = fourth_dense(r3);

  digit result = {0,0};
  for (int i=0; i < r4.get_rows(); i++)
    {
      if (r4[i] > result.probability)
        {
          result.value = i;
          result.probability = r4[i];
        }
    }
  return result;
}