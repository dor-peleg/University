#ifndef _VL_VECTOR_H_
#define _VL_VECTOR_H_
#include <cstddef>
#include <cstring>
#include <iterator>
#include <cmath>
#include <iostream>

#define DEF_STATIC_CAP 16
#define OUT_OF_RANGE_ERR "index is out of range"

enum memtype {STACK, HEAP};

/**
 * generates vl_vector that contains elements of type T
 * and can store C element in the STACK
 * @tparam T Type of the elements
 * @tparam C maximum num of elements that will be stored in the STACK.
 */
template<typename T, size_t C=DEF_STATIC_CAP>
class vl_vector {
 protected:
  size_t _size;
  size_t _capacity;
  memtype _mem_type;
  T *_data;
  T _stack_data[C];

  /**
   * called after adding or deleting elements from vl_vector,
   * checks if ths number of elements is bigger than the capacity
   * and change the capacity accordingly.
   * and checks if num of elements is lower than C
   * and move them to static memory.
   */
  void resize ();
  /**
   * transfer the elements from dynamic storage to static storage.
   */
  void heap_to_stack ();
  /**
   * transfer the elements from static storage to dynamic storage
   */
  void stack_to_heap ();
  /**
   * calculates new capacity value.
   * @return the new capacity value.
   */
  size_t capc();

 public:

  typedef T *iterator;
  typedef const T *const_iterator;
  typedef std::reverse_iterator<T *> reverse_iterator;
  typedef std::reverse_iterator<const T *> const_reverse_iterator;

  iterator begin ()
  { return _data; }
  iterator end ()
  { return _data + _size; }
  const_iterator cbegin ()
  { return _data; }
  const_iterator cend ()
  { return _data + _size; }
  const_iterator begin () const
  { return _data; }
  const_iterator end () const
  { return _data + _size; }

  reverse_iterator rbegin ()
  { return std::make_reverse_iterator (end ()); }
  reverse_iterator rend ()
  { return std::make_reverse_iterator (begin ()); }
  const_reverse_iterator crbegin () const
  { return std::make_reverse_iterator (end ()); }
  const_reverse_iterator crend () const
  { return std::make_reverse_iterator (begin ()); }
  const_reverse_iterator rbegin () const
  { return std::make_reverse_iterator (end ()); }
  const_reverse_iterator rend () const
  { return std::make_reverse_iterator (begin ()); }

  /**
   * default constructor
   */
  vl_vector ()
      : _size (0), _capacity (C), _mem_type (STACK), _data (_stack_data)
  { }

  /**
   * copy constructor, gets existing vl_vector and creates identical vl_vector.
   * @param vec
   */
  vl_vector (const vl_vector& vec)
      : _size (vec._size), _capacity (vec._capacity),
        _mem_type (vec._mem_type)
  {
    if (_mem_type == HEAP)
      _data = new T[vec._capacity];
    else
      _data = _stack_data;

    memcpy (_data, vec._data, sizeof (T) * _size);
  }


  template<class InputIterator>
  /**
   * constuctor that gets a sequence and crates new vl_vector that
   * contains that sequence
   * @tparam InputIterator InputIterator
   * @param first the beginning of the sequence
   * @param last the end of the sequence.
   */
  vl_vector (InputIterator first, InputIterator last)
  {
    size_t num_of_elem = std::distance (first, last);
    if (num_of_elem > C)
      {
        _size = num_of_elem;
        _mem_type = HEAP;
        _capacity = capc();
        _data = new T[_capacity];
      }
    else
      {
        _size = num_of_elem;
        _capacity = C;
        _mem_type = STACK;
        _data = _stack_data;
      }
    memcpy (_data, first, sizeof (T) * num_of_elem);
  }

  /**
   * constructor that gets a number n and a value,
   * and creates new vl_vector that contains the value n times.
   * @param count number of elements 'val' to store
   * @param val the value
   */
  vl_vector (size_t count, T val)
  {
    if (count > C)
      {
        _size = count;
        _capacity = capc();
        _mem_type = HEAP;
        _data = new T[_capacity];
      }
    else
      {
        _size = count;
        _capacity = C;
        _mem_type = STACK;
        _data = _stack_data;
      }
    for (size_t i = 0; i < count; i++)
      _data[i] = val;
  }

  /**
   * vl_vector destructor, if the vector use dynamic memory,
   * the destructor frees it
   */
  ~vl_vector ()
  {
    if (_mem_type == HEAP)
      delete[] _data;
  }

  /**
   * return the num of elements in the vector
   * @return num of elements in the vector
   */
  size_t size () const
  { return _size; }
  /**
   * return the capacity of the vector
   * @return capacity of the vector
   */
  size_t capacity () const
  { return _capacity; }
  /**
   * return whether the vector empty or not
   * @return true if the vector is empty, false otherwise.
   */
  bool empty () const
  { return _size == 0; }

  /**
   * gets index and checks if the index is within vector range.
   * if so, returns the value at this index, if not, throws an exception.
   * @param idx the index
   * @return the value at the index.
   */
  T at (int idx) const
  {
    if (idx < 0 || idx >= (int) size ())
      throw std::out_of_range (OUT_OF_RANGE_ERR);
    return _data[idx];
  }

  /**
   * gets index and checks if the index is within vector range.
   * if so, returns the value at this index, if not, throws an exception.
   * @param idx the index
   * @return the value at the index.
   */
  T& at(int idx)
  {
    if (idx < 0 || idx >= (int) size ())
      throw std::out_of_range (OUT_OF_RANGE_ERR);
    return _data[idx];
  }

  /**
   * adds an alement to the end of the vector
   * @param val the value of the element.
   */
  void push_back (T val)
  {
    _size++;
    resize ();
    (*this)[size () - 1] = val;
  }

  /**
   * removes the value at the end of the vector
   */
  void pop_back ()
  {
    _size--;
    resize ();
  }

  /**
   * removes all the elements from the vector
   */
  void clear() {erase (begin(), end());}

  /**
   * returns a pointer to the data of the vector
   * @return a pointer to the data of the vector
   */
  T *data() const { return _data; }

  /**
   * gets a value, and checks if this value is in the vector
   * @param val the value
   * @return true if the value is in the vector, false otherwise
   */
  bool contains (T val) const
  {
    for (size_t i = 0; i < _size; i++)
      if (_data[i] == val)
        return true;
    return false;
  }

  /**
   * gets iterator and a vlaue,
   * and insert that value to the vector where the iterator points to
   * @param it iterator to an element in the vector
   * @param val the value to insert
   * @return iterator to the new element that was inserted.
   */
  iterator insert (const_iterator it, T val)
  {
    size_t dist_from_begin = std::distance (cbegin (), it);
    _size++;
    resize ();
    iterator start = begin () + dist_from_begin;
    iterator iter = end () - 2;
    while (iter >= start)
      {
        *(iter + 1) = *(iter);
        iter--;
      }
    *start = val;
    return start;
  }

  /**
   * gets an iterator to location in the vector,
   * and two iterators to the beginning and end of a sequence.
   * and insert the sequence to vector at the location of the iterator.
   * @tparam ForwordIterator ForwordIterator
   * @param it iterator to location in the vector
   * @param first beginning of the sequence
   * @param last end of the sequence
   * @return iterator to the location of the insertion/
   */
  template<class ForwordIterator>
  iterator
  insert (const_iterator it, const ForwordIterator first,
          const ForwordIterator last)
  {
    size_t dist_from_begin = it - begin ();
    size_t num_of_elems = std::distance (first, last);
    _size += num_of_elems;
    resize ();
    iterator start = begin () + dist_from_begin;
    iterator iter = end () - num_of_elems - 1;
    while (iter >= start)
      {
        *(iter + num_of_elems) = *(iter);
        iter--;
      }
    std::copy (first, last, start);
    return start;
  }

  /**
   * gets an iterator to location in the vector,
   * and deletes the element in that location
   * @param it iterator to location in the vector
   * @return iterator to the same location (but to the next element)
   */
  iterator erase (const_iterator it)
  {
    size_t dist_from_begin = std::distance (cbegin (), it);
    iterator start = begin () + dist_from_begin + 1;
    while (start < end ())
      {
        *(start - 1) = *start;
        start++;
      }
    _size--;
    resize ();
    return begin() + dist_from_begin;
  }

  /**
   * gets tow iterators to positions in the vector,
   * and deletes all the elements between those iterators
   * @param first first iterator
   * @param last second iterator
   * @return iterator to the next element that wasn't deleted.
   */
  iterator erase (const_iterator first, const_iterator last)
  {
    size_t num_of_elems = std::distance (first, last);
    size_t dist_from_begin = std::distance (cbegin (), first);
    iterator start = begin () + dist_from_begin;
    iterator iter = start + num_of_elems;
    while (iter != end ())
      {
        *(iter - num_of_elems) = *iter;
        iter++;
      }
    _size -= num_of_elems;
    resize ();
    return begin () + dist_from_begin;
  }

  /**
 * for idx index, returns the idx'th element.
 * @param idx an index in the vector
 * @return the idx'th element in the vector
 */
  T operator[] (int idx) const {return _data[idx];}

/**
* for idx index, returns the idx'th element.
* @param idx an index in the vector
* @return the idx'th element in the vector
*/
  T& operator[] (int idx) {return _data[idx];}

/**
 * assign all the data from other vector to this vector
 * @param vec another vector
 * @return vector that identical to vector vec
 */
  vl_vector& operator= (const vl_vector& vec)
  {
    if (this == &vec)
        return *this;
    this->_size = vec.size();
    this->_capacity = vec.capacity();
    if (_mem_type == HEAP && vec._mem_type == HEAP)
      {
        T *temp = new T[_capacity];
        std::copy (vec.begin(), vec.end(), temp);
        delete[] _data;
        _data = temp;
      }
    else if (_mem_type == HEAP && vec._mem_type == STACK)
      {
        delete[] _data;
        _data = _stack_data;
        std::copy (vec.begin(), vec.end(), _data);
        _mem_type = STACK;
      }
    else if (_mem_type == STACK && vec._mem_type == HEAP)
      {
        _data = new T[_capacity];
        std::copy (vec.begin(), vec.end(), _data);
        _mem_type = HEAP;
      }
    else if (_mem_type == STACK && vec._mem_type == STACK)
      {
        std::copy (vec.begin(), vec.end(), _data);
      }
    return *this;
  }

  /**
   * gets two vectors and checks if they are identical
   * @tparam K type of the vector's elements
   * @tparam A  maximum num of elements that will be stored in the STACK.
   * @param vec1 first vector
   * @param vec2 second vector
   * @return true if the vectors identical, false otherwise
   */
  template<typename K, size_t A>
  friend bool
  operator== (const vl_vector<K, A>& vec1, const vl_vector<K, A>& vec2);

  /**
   * gets two vectors and checks if they are identical
   * @tparam K type of the vector's elements
   * @tparam A  maximum num of elements that will be stored in the STACK.
   * @param vec1 first vector
   * @param vec2 second vector
   * @return false if the vectors identical, true otherwise
   */
  template<typename K, size_t A>
  friend bool
  operator!= (const vl_vector<K, A>& vec1, const vl_vector<K, A>& vec2);
};

/**
 * transfer the elements from dynamic storage to static storage.
 * @tparam T type of the vector's elements
 * @tparam C maximum num of elements that will be stored in the STACK.
 */
template<typename T, size_t C>
void vl_vector<T, C>::heap_to_stack ()
{
  memcpy (_stack_data, _data, sizeof(T) * _size);

  delete[] _data;
  _data = _stack_data;
  _mem_type = STACK;
  _capacity = C;
}

/**
 * transfer the elements from static storage to dynamic storage.
 * @tparam T type of the vector's elements
 * @tparam C maximum num of elements that will be stored in the STACK.
 */
template<typename T, size_t C>
void vl_vector<T, C>::stack_to_heap ()
{
  _data = new T[capacity()];
  memcpy (_data, _stack_data, sizeof (T) * _size);
  _mem_type = HEAP;
}

/**
 * called after adding or deleting elements from vl_vector,
 * checks if ths number of elements is bigger than the capacity
 * and change the capacity accordingly.
 * and checks if num of elements is lower than C
 * and move them to static memory.
 * @tparam T type of the vector's elements
 * @tparam C maximum num of elements that will be stored in the STACK.
 */
template<typename T, size_t C>
void vl_vector<T, C>::resize ()
{
  switch (_mem_type)
    {
    case STACK:
      {
        if (size() > C)
          {
            _capacity = capc();
            stack_to_heap();
          }
          break;
      }
    case HEAP:
      {
        if (size() > _capacity)
          {
            size_t new_cap = capc();
            T* temp = new T[new_cap];
            std::copy(begin(), end() -1 , temp);
            delete[] _data;
            _data = temp;
            _capacity = new_cap;
          }

        else if (size() <= C)
          heap_to_stack();
      }
      break;
    }
}
template<typename T, size_t C>

/**
 * calculates new capacity value.
 * @tparam T type of the vector's elements
 * @tparam C maximum num of elements that will be stored in the STACK.
 * @return the new capacity
 */
size_t vl_vector<T, C>::capc ()
{
  return floor((3*size())/2);;
}

/**
 * gets two vectors and checks if they are identical
 * @tparam K type of the vector's elements
 * @tparam A  maximum num of elements that will be stored in the STACK.
 * @param vec1 first vector
 * @param vec2 second vector
 * @return true if the vectors are identical, false otherwise
 */
template<typename K, size_t A>
bool operator== (const vl_vector<K, A>& vec1, const vl_vector<K, A>& vec2)
{
  if( vec1.size() != vec2.size())
    return false;
  for (size_t i=0 ; i<vec1.size(); i++)
    if (vec1[i] != vec2[i])
      return false;
  return true;
}

/**
   * gets two vectors and checks if they are identical
   * @tparam K type of the vector's elements
   * @tparam A  maximum num of elements that will be stored in the STACK.
   * @param vec1 first vector
   * @param vec2 second vector
   * @return false if the vectors are identical, true otherwise
 */
template<typename K, size_t A>
bool operator!= (const vl_vector<K, A>& vec1, const vl_vector<K, A>& vec2)
{
  return !(vec1 == vec2);
}

#endif //_VL_VECTOR_H_
