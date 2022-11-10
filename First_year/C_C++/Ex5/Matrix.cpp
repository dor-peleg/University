#include "Matrix.h"
#include <iostream>
#include <cstring>
#include <cmath>

/**
 * Matrix Constructor, creates a new rows X cols matrix,
 * Inits all elements to 0.
 * @param rows number of rows in the new matrix.
 * @param cols number of columns in the new matrix.
 */
Matrix::Matrix (int rows, int cols)
{
  _rows = rows;
  _cols = cols;
  total_size = _rows * _cols;
  data = new float[total_size]();
}

/**
 * Matrix Constructor, creates 1 X 1 matrix, Inits the single element to 0.
 */
Matrix::Matrix()
{
  _rows = 1;
  _cols = 1;
  total_size = _rows * _cols;
  data = new float[total_size]();
}

/**
 * Matrix copy-Constructor, creates a new matrix identical to a given matrix.
 * @param other matrix that get copied to the new matrix.
 */
Matrix::Matrix(const Matrix& other)
{
  _rows = other._rows;
  _cols = other._cols;
  total_size = _rows * _cols;
  data = new float[total_size];
  std::memcpy(data, other.data, total_size * sizeof (float));
}

/**
 * Matrix Destructor, free all the memory used by the matrix.
 */
Matrix::~Matrix ()
{
  delete[] data;
}

/**
 * return the numbers of rows in a matrix
 * @return numbers of rows in a matrix
 */
int Matrix::get_rows () const
{return _rows;}

/**
 * return the numbers of columns in a matrix
 * @return numbers of columns in a matrix
 */
int Matrix::get_cols () const
{return _cols; }

/**
 * Transforms a matrix into its transpose matrix.
 * @return the transposed matrix
 */
Matrix& Matrix::transpose()
{
  auto *trans = new float[total_size];
  for (int i=0; i<this->get_rows(); i++)
    for (int j=0; j<this->get_cols(); j++)
      trans[j * this->get_rows() + i] = (*this)(i,j);
  delete[] data;
  data = trans;
  int temp = get_rows();
  _rows = get_cols();
  _cols = temp;
  return *this;
}

/**
 * Transforms a matrix into a column vector.
 * @return the vector created from the matrix
 */
Matrix& Matrix::vectorize()
{
  _rows = total_size;
  _cols = 1;
  return *this;
}

/**
 * Prints matrix elements.
 */
void Matrix::plain_print() const
{
  for (int i = 0; i < get_rows (); i++)
    {
      for (int j = 0; j < get_cols (); j++)
        std::cout << (*this)(i,j) << " ";
      std::cout << std::endl;
    }
}

/**
 * creates a new matrix that is a dot product of this matrix and
 * another matrix
 * @param b the other matrix
 * @return the new matrix that is a dot product of this matrix and
 *         matrix b.
 */
Matrix Matrix::dot(const Matrix& b) const
{
  if (this->get_rows() != b.get_rows() || this->get_cols() != b.get_cols())
    {
      std::cerr << UNMATCHING_MATRICES_ERR << std::endl;
      exit(1);
    }
  Matrix dot_mat = Matrix(this->get_rows(), this->get_cols());
  for (int i=0; i<total_size; i++)
    dot_mat[i] = ((*this)[i] * b[i]);
  return dot_mat;
}

/**
 * Calculates and Returns the Frobenius norm of the matrix
 * @return the Frobenius norm of the matrix
 */
float Matrix::norm() const
{
  float norm = 0;
  for (int i=0; i<total_size; i++)
    norm += (powf ((*this)[i], 2));
  return sqrtf(norm);
}

/**
 * Sums this matrix with another matrix
 * @param b a matrix
 * @return A new matrix which is the sum of the two matrices
 */
Matrix Matrix::operator+(const Matrix& b) const
{
    if (this->get_rows() != b.get_rows() || this->get_cols() != b.get_cols())
    {
      std::cerr << UNMATCHING_MATRICES_ERR << std::endl;
      exit(1);
    }
    Matrix result(_rows, _cols);
    for (int i=0; i<total_size; i++)
      result.data[i] = this->data[i] + b.data[i];
    return result;
}

/**
 * assign all the data from other matrix to this matrix
 * @param b another matrix
 * @return Matrix that identical to Matrix b
 */
Matrix& Matrix::operator = (const Matrix& b)
{
  if (this == &b)
    {
      return *this;
    }
  this->_rows = b._rows;
  this->_cols = b._cols;
  this->total_size = b.total_size;
  delete[] this->data;
  this->data = new float[total_size];
  std::memcpy(this->data, b.data, total_size * sizeof (float));
  return *this;
}

/**
 * multiply this matrix with another matrix
 * @param b a matrix
 * @return A new matrix which is the multiplication of the two matrices
 */
Matrix Matrix::operator*(const Matrix& B) const
{
  if (this->get_cols() != B.get_rows())
    {
      std::cerr << MULT_UNMATCHING_MATRICES_ERR << std::endl;
      exit(1);
    }
  Matrix mult(this->get_rows(), B.get_cols());
  for (int i=0; i<get_rows(); i++)
    {
      for (int j = 0; j < B.get_cols (); j++)
        {
          mult (i, j) = 0;
          for (int k = 0; k < this->get_cols (); k++)
            mult(i,j) +=
                ((*this)(i, k) * B(k, j));
        }
    }
   return mult;
}

/**
 * for any (i,j) in the matrices, adds b(i,j) to a(i,j)
 * @param b a matrix
 * @return this matrix after adding the value of matrix b to any cell.
 */
Matrix& Matrix::operator+=(const Matrix& b)
{
  if (this->get_rows() != b.get_rows() || this->get_cols() != b.get_cols())
    {
      std::cerr << UNMATCHING_MATRICES_ERR << std::endl;
      exit(1);
    }
  for (int i=0; i<total_size; i++)
    (*this)[i] += b[i];
  return *this;
}

/**
 * For row, col indices, returns the (row,col) element in the matrix
 * @param row number of the row
 * @param col number of the column
 * @return the (row,col) element in the matrix
 */
float Matrix::operator() (int row, int col) const
{
  if (row >= this->get_rows() || col >= this->get_cols() || row < 0 || col < 0)
    {
      std::cerr << OUT_OF_BOUNDS_ERR << std::endl;
      exit(1);
    }
  return this->data[row * _cols + col];
}

/**
 * For row, col indices, returns the (row,col) element in the matrix
 * @param row number of the row
 * @param col number of the column
 * @return the (row,col) element in the matrix
 */
float& Matrix::operator() (int row, int col)
{
  if (row >= _rows || col >= _cols || row < 0 || col < 0)
    {
      std::cerr << OUT_OF_BOUNDS_ERR << std::endl;
      exit(1);
    }
  return this->data[row * _cols + col];
}

/**
 * for idx index, returns the idx'th element.
 * @param idx an index in the matrix
 * @return the idx'th element in the matrix
 */
float Matrix::operator[](int idx) const
{
  if (idx < 0 || idx >= total_size)
    {
      std::cerr << OUT_OF_BOUNDS_ERR << std::endl;
      exit(1);
    }
  return this->data[idx];
}
/**
* for idx index, returns the idx'th element.
* @param idx an index in the matrix
* @return the idx'th element in the matrix
*/
float& Matrix::operator[] (int idx)
{
  if (idx < 0 || idx >= total_size)
  {
    std::cerr << OUT_OF_BOUNDS_ERR << std::endl;
    exit(1);
  }
  return data[idx];
}

/**
 * reads data from binary file and fill a matrix with the data.
 * exits with error if the file is to short.
 * @param is the input stream of the file
 * @param m the matrix that gert fill
 */
void read_binary_file(std::istream& is, Matrix& m)
{
  is.seekg(0, std::istream::end);
  unsigned long file_size = is.tellg();
  if (file_size < (m.total_size * sizeof (float)))
    {
      std::cerr << BINARY_FILE_TOO_SHORT_ERR << std::endl;
      exit(EXIT_FAILURE);
    }
  is.seekg(0, std::istream::beg);
  is.read((char*)m.data, (long)(m.total_size * sizeof(float)));
}

/**
 * multiply every cell in the matrix by scalar c
 * @param mat the matrix that get multiplied
 * @param c the scalar that multiply the matrix
 * @return new matrix that every cell's value is the original cell's value
 * multiply by scalar c
 */
Matrix operator*(const Matrix& mat, float c)
{
  Matrix mult_by_scalar(mat.get_rows(), mat.get_cols());
  for (int i=0; i<mat.total_size; i++)
    mult_by_scalar.data[i] = mat.data[i] * c;
  return mult_by_scalar;
}

/**
 * multiply every cell in the matrix by scalar c
 * @param mat the matrix that get multiplied
 * @param c the scalar that multiply the matrix
 * @return new matrix that every cell's value is the original cell's value
 * multiply by scalar c
 */
Matrix operator*(float c, const Matrix& mat)
{
  Matrix mult_by_scalar(mat.get_rows(), mat.get_cols());
  for (int i=0; i<mat.total_size; i++)
    mult_by_scalar.data[i] = mat.data[i] * c;
  return mult_by_scalar;
}

/**
 * Prints the matrix values in such a way as to reproduce the image
 * that the matrix represents
 * @param out out stream
 * @param m the matrix
 * @return the out stream.
 */
std::ostream & operator << (std::ostream &out, const Matrix& m)
{
  for (int i=0; i<m.get_rows(); i++)
    {
      for (int j=0; j<m.get_cols(); j++)
        {
          if (m(i,j) >= PRINT_THRESHOLD)
            out << ("  ");
          else
            out << ("**");
        }
      out << std::endl;
    }
  return out;
}