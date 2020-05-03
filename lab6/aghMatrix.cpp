#include "aghMatrix.h"


// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>>& mat) 
{
  matrix.resize(mat.size());
  for (unsigned i = 0; i < mat.size(); i++) 
  {
    matrix[i].resize(mat[i].size());
    for(unsigned j = 0; j < mat[i].size(); j++)
    {
      matrix[i][j] = mat[i][j];
    }
  }
  rows = matrix.size();
  cols = matrix[1].size();
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial) 
{
  matrix.resize(_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T>& rhs) 
{
  matrix = rhs.matrix;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned AGHMatrix<T>::get_rows() const 
{
  return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned AGHMatrix<T>::get_cols() const 
{
  return this->cols;
}

// Assignment Operator                                                                                                                                                        
template<typename T>
AGHMatrix<T>& AGHMatrix<T>::operator=(const AGHMatrix<T>& rhs) 
{
  if (&rhs == this)
    return *this;

  unsigned new_rows = rhs.get_rows();
  unsigned new_cols = rhs.get_cols();

  matrix.resize(new_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++) 
  {
    for (unsigned j=0; j<new_cols; j++) 
    {
      matrix[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) 
{
  return this->matrix[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) const 
{
  return this->matrix[row][col];
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T>& rhs) 
{
  if (this -> rows != rhs.get_rows() || this -> cols != rhs.get_cols() )
    throw std::invalid_argument("Matrices have diffrent sizes - cannot add");

  AGHMatrix<T> resMatrix(rhs);
  
  for (unsigned i=0; i < rows; i++)
    for (unsigned j=0; j < cols; j++)
      resMatrix.matrix[i][j] += this -> matrix[i][j];

  return resMatrix;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T>& rhs) 
{
  if ( this -> cols != rhs.get_rows() )
    throw std::invalid_argument("Matrices have diffrent sizes - cannot multiply");

  unsigned new_rows = this -> rows;
  unsigned new_cols = rhs.get_cols();
  const T _initial{};
  AGHMatrix<T> resMatrix (new_rows, new_cols, _initial);

  unsigned mul_count = this -> cols;

  for (unsigned i=0; i < new_rows; i++)
    for (unsigned j=0; j < new_cols; j++)
      for (unsigned k=0; k < mul_count; k++)
        resMatrix.matrix[i][j] += this -> matrix[i][k] * rhs(k, j);
  return resMatrix;
}

// Printing matrix                                                                                                                        
template<typename T>
std::ostream& operator<<(std::ostream& stream, const AGHMatrix<T>& matrix) 
{
  for (unsigned i=0; i<matrix.get_rows(); i++) 
  { 
    for (unsigned j=0; j<matrix.get_cols(); j++) 
    {
        stream << matrix(i,j) << ", ";
    }
    stream << std::endl;
  }
    stream << std::endl;
  return stream;
}

template<typename T>
bool AGHMatrix<T>::operator==(const AGHMatrix<T>& rhs) const{
  if( this->rows != rhs.get_rows() || this->cols != rhs.get_cols() ) 
    return false;

  for(unsigned i=0; i < rows; i++)
    for(unsigned j=0; j < cols; j++)
      if(this->matrix[i][j] != rhs(i, j))
        return false;

  return true;
}

template<typename T>
bool AGHMatrix<T>::almost_eq(const AGHMatrix<double>& rhs) const{
  if( this->rows != rhs.get_rows() || this->cols != rhs.get_cols() ) 
    return false;

double abs_err = 1e-10;
  for(unsigned i=0; i < rows; i++)
    for(unsigned j=0; j < cols; j++)
      if( abs(this->matrix[i][j] - rhs(i, j) > abs_err ))
        return false;

  return true;
}

// Zadanie 2
//////////////////////////////////

// Access whole row (added)
template<typename T>
const std::vector<T>& AGHMatrix<T>::get_whole_row(const unsigned& row) const{
  return this -> matrix[row];
}

// Swap two rows (added)
template<typename T>
void AGHMatrix<T>::swap_rows(const unsigned& i, const unsigned& j){
  std::vector<T> tmp = this -> matrix[i];
  this -> matrix[i] = this -> matrix[j];
  this -> matrix[j] = tmp;
}

// Checking if matrix is symmetric
template<typename T>
bool AGHMatrix<T>::is_symmetric() const{
  if(this->rows != this->cols)    // Jesli nie jest kwadratowa to nie moze byc symetryczna
    return false;

  for (unsigned i = 0; i < rows; i++)
    for (unsigned j = 0; j < i; j++)
      if (this -> matrix[i][j] != this -> matrix[j][i])   
        return false;

  return true;
}

// Determinant
template<typename T>
T AGHMatrix<T>::det() const{
  if (rows != cols) 
    throw std::logic_error("Cannot calculate determinant - matrix is not square!");

  AGHMatrix<T> duplicate(*this);
  int sign = gaussian_elimination(duplicate);
  
  T det{};
  det += 1;

  for (unsigned i=0; i < rows; i++)
    det *= duplicate.matrix[i][i];

  return sign*det;
}

// Transposition
template<typename T>
AGHMatrix<T>& AGHMatrix<T>::transpose(){
  unsigned trans_rows = cols;
  unsigned trans_cols = rows;

  AGHMatrix<T> prevMatrix (*this);

  matrix.resize(trans_rows);
  for (unsigned i=0; i < trans_rows; i++){
    matrix[i].resize(trans_cols);
    for (unsigned j=0; j < trans_cols; j++)
      this -> matrix[i][j] = prevMatrix(j, i);
  }
  this -> rows = trans_rows;
  this -> cols = trans_cols;
  return *this;
}
///////////////////////////////////////////

// Eliminacja Gaussa (zadanie 5)
///////////////////////// 
template <typename T>
int gaussian_elimination(AGHMatrix<T>& mat){
  unsigned rows = mat.get_rows();
  unsigned cols = mat.get_cols();
  int sign = 1;
  for(unsigned i=0; i < cols; i++)
  {
    unsigned j=i;
    T max_val{};
    if (i >= rows)  break;
    for(unsigned k=i; k < rows; k++)
      if(std::abs(mat(k, i)) > std::abs(max_val)){
        max_val = mat(k, i);
        j = k;
      }
    
    std::vector<T> eliminating_row = mat.get_whole_row(j);
    if (i != j){                                // Jesli musimy wziac inny wiersz niz i-ty, zamieniamy go (bierzemy ten, ktory ma najwiekszy)
      mat.swap_rows(i, j);
      sign = -sign;
    }

    for(j=i+1; j < rows && mat(j, i) == 0; j++)      // Przeskakujemy te, ktorych nie trzeba zerowac
    if(j >= rows) continue;                     // Jesli cala kolumna jest wyzerowana to pomijamy krok eliminacji dla tej kolumny

    for(; j < rows; j++)                     
    {
      T mul_coeff = mat(j, i) / eliminating_row[i];   // Wspolczynnik dla danego wiersza, by wyzerowac i-ta kolumne
      for(unsigned k=i; k < cols; k++)                // Dokonujaca eliminacji tak, by wyzerowac i-ta kolumne
        mat(j, k) -= mul_coeff * eliminating_row[k];
    }
  }
  
  return sign;
}