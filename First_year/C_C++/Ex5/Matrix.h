// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

#define PRINT_THRESHOLD 0.1
#define OUT_OF_BOUNDS_ERR "Error: index out of bounds"
#define UNMATCHING_MATRICES_ERR "Error: The matrices should have the same size"
#define MULT_UNMATCHING_MATRICES_ERR "Error: Matrix size does not match"
#define BINARY_FILE_TOO_SHORT_ERR "Error: File is to short"
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * Matrix class, contains all the data and operations can be made on matrices.
 */
class Matrix
{
 public:
  /**
   * Matrix Constructor, creates a new rows X cols matrix,
   * Inits all elements to 0.
   * @param rows number of rows in the new matrix.
   * @param cols number of columns in the new matrix.
   */
  Matrix(int rows, int cols);
  /**
   * Matrix Constructor, creates 1 X 1 matrix, Inits the single element to 0.
   */
  Matrix();
  /**
   * Matrix copy-Constructor, creates a new matrix identical to a given matrix.
   * @param other matrix that get copied to the new matrix.
   */
  Matrix(const Matrix& other);
  /**
   * Matrix Destructor, free all the memory used by the matrix.
   */
  ~Matrix();
  /**
   * return the numbers of rows in a matrix
   * @return numbers of rows in a matrix
   */
  int get_rows() const;
  /**
   * return the numbers of columns in a matrix
   * @return numbers of columns in a matrix
   */
  int get_cols() const;
  /**
   * Transforms a matrix into its transpose matrix.
   * @return the transposed matrix
   */
  Matrix& transpose();
  /**
   * Transforms a matrix into a column vector.
   * @return the vector created from the matrix
   */
  Matrix& vectorize();
  /**
   * Prints matrix elements.
   */
  void plain_print() const;
  /**
   * creates a new matrix that is a dot product of this matrix and
   * another matrix
   * @param b the other matrix
   * @return the new matrix that is a dot product of this matrix and
   *         matrix b.
   */
  Matrix dot(const Matrix& b) const;
  /**
   * Calculates and Returns the Frobenius norm of the matrix
   * @return the Frobenius norm of the matrix
   */
  float norm() const;
  /**
   * Sums this matrix with another matrix
   * @param b a matrix
   * @return A new matrix which is the sum of the two matrices
   */
  Matrix operator+(const Matrix& b) const;
  /**
   * assign all the data from other matrix to this matrix
   * @param b another matrix
   * @return Matrix that identical to Matrix b
   */
  Matrix& operator=(const Matrix& b);
  /**
   * multiply this matrix with another matrix
   * @param b a matrix
   * @return A new matrix which is the multiplication of the two matrices
   */
  Matrix operator*(const Matrix& b) const;
  /**
   * for any (i,j) in the matrices, adds b(i,j) to a(i,j)
   * @param b a matrix
   * @return this matrix after adding the value of matrix b to any cell.
   */
  Matrix& operator+=(const Matrix& b);
  /**
   * For row, col indices, returns the (row,col) element in the matrix
   * @param row number of the row
   * @param col number of the column
   * @return the (row,col) element in the matrix
   */
  float operator()(int row, int col) const;
  /**
   * For row, col indices, returns the (row,col) element in the matrix
   * @param row number of the row
   * @param col number of the column
   * @return the (row,col) element in the matrix
   */
  float& operator()(int row, int col);
  /**
   * for idx index, returns the idx'th element.
   * @param idx an index in the matrix
   * @return the idx'th element in the matrix
   */
  float operator[](int idx) const;
  /**
   * for idx index, returns the idx'th element.
   * @param idx an index in the matrix
   * @return the idx'th element in the matrix
   */
  float& operator[](int idx);

  /**
   * reads data from binary file and fill a matrix with the data.
   * exits with error if the file is to short.
   * @param is the input stream of the file
   * @param m the matrix that gert fill
   */
  friend void read_binary_file(std::istream& is, Matrix& m);
  /**
   * multiply every cell in the matrix by scalar c
   * @param mat the matrix that get multiplied
   * @param c the scalar that multiply the matrix
   * @return new matrix that every cell's value is the original cell's value
   * multiply by scalar c
   */
  friend Matrix operator*(const Matrix& mat, float c);
  /**
   * multiply every cell in the matrix by scalar c
   * @param mat the matrix that get multiplied
   * @param c the scalar that multiply the matrix
   * @return new matrix that every cell's value is the original cell's value
   * multiply by scalar c
   */
  friend Matrix operator*(float c, const Matrix& mat);
  /**
   * Prints the matrix values in such a way as to reproduce the image
   * that the matrix represents
   * @param out out stream
   * @param m the matrix
   * @return the out stream.
   */
  friend std::ostream & operator << (std::ostream &out, const Matrix& m);


 private:
  float* data;
  int _rows;
  int _cols;
  int total_size;
};


#endif //MATRIX_H
