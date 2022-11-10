#ifndef _VL_STRING_H_
#define _VL_STRING_H_

#define STR_END '\0'
#include "vl_vector.h"

/**
 * creates a vl_vector that contains char and acts like a string,
 * with the benefits of dynamic and static memory like vl_vector
 * @tparam C
 */
template<size_t C=DEF_STATIC_CAP>
class vl_string : public vl_vector<char, C>
{
 public:
  /**
   * default constructor
   */
  vl_string() : vl_vector<char,C>() {vl_string<C>::push_back (STR_END);}
  /**
   * copy constructor,
   * gets a vl_string and creates a new vl_string identical to it
   * @param str the other vl_string
   */
  vl_string(const vl_string& str) : vl_vector<char,C>(str){}
  /**
   * implicit constructor,
   * gets char* and creates vl_vector with the data that was in it
   * @param str the char* to put in the vl_vector
   */
  vl_string(const char* str ) : vl_vector<char,C>
      (str, str+std::strlen(str) + 1){}

  /**
   * gets a pointer to sequence of chars as char*
   * and check if the sequence that in that char* appears in vl_string
   * @param str the pointer to the chars sequence
   * @return true if the sequence appears in vl_string, false otherwise
   */
  bool contains(const char* str) const
  {
    size_t len = std::strlen (str);
    if (len > this->size())
      return false;
//    char buff;
    auto iter = this->begin();
    while (iter != this->end()-len)
      {
        std::string a = iter;
        std::string p = a.std::string::substr (0, len);
        char* s = &p[0];
        if (std::strcmp(s, str) == 0)
          return true;
        iter++;
      }

    return false;
  }

  /**
   * return the num of chars in the string
   * @return num of chars in the string
   */
  size_t size() const { return this->_size - 1;}
  /**
   * return whether the string empty or not
   * @return true if the string is empty, false otherwise.
   */
  bool empty() const {return this->_size == 1;}
  /**
   * adds a new char to the end of the string
   * @param val the char
   */
  void push_back(char val) {this->insert (this->end()-1, val);}
  /**
   * removes the last char of the string
   */
  void pop_back() { vl_string<C>::erase (this->end()-2);}

  /**
   * gets an iterator to location in the string,
   * and deletes the char in that location
   * @param it iterator to location in the string
   * @return iterator to the same location (but to the next char)
   */
  typename vl_vector<char, C>::iterator erase
  (typename vl_vector<char, C>::const_iterator it)
  {
    if (it==this->end()-1)
      return this->end()-1;
    return vl_vector<char,C>::erase (it);
  }

  /**
   * gets tow iterators to positions in the string,
   * and deletes all the chars between those iterators
   * @param first first iterator
   * @param last second iterator
   * @return iterator to the next char that wasn't deleted.
   */
  typename vl_vector<char, C>::iterator erase
  (typename vl_vector<char, C>::const_iterator first,
   typename vl_vector<char, C>::const_iterator last)
  {return vl_vector<char, C>::erase (first, last);}

  /**
   * deletes all the chars from the string
   */
  void clear() {vl_vector<char, C>::erase (this->begin(), this->end()-1);}


  /**
   * gets other vl_string and adds it to this vl_string
   * @param str the other vl_string
   * @return this vl_string that now contains chaining of the two strings
   */
  vl_string& operator+=(const vl_string& str)
  {
    this->insert (this->end()-1, str.begin(), str.end()-1);
    return *this;
  }
  /**
   * gets char sequence as char* and adds it to this vl_string
   * @param val the char* that points to the chars sequence.
   * @return this vl_string that now contains chaining of the two strings
   */
  vl_string& operator+=(const char* val)
  {
    size_t len = strlen (val);
    this->insert (this->end() -1, val, val+len);
    return *this;
  }

  /**
   * gets a char and adds it to this vl_string
   * @param val the char
   * @return this vl_string that now contains chaining of the
   * original string and the char
   */
  vl_string& operator+=(const char val)
  {
    this->insert (this->end() -1, val);
    return *this;
  }

  /**
   * gets two vl_string and chains them.
   * @param str1 first vl_string
   * @param str2 second vl_stream
   * @return the first vl_stream that now contains chaining of the two strings.
   */
  friend vl_string& operator+(vl_string& str1, const vl_string& str2)
  {
    str1 += str2;
    return str1;
  }
  /**
   * gets a vl_string and a char sequence as char*
   * and chains the sequence to the vl_string
   * @param str1 the vl_string
   * @param val the char* that points to the chars sequence.
   * @return first vl_stream that now contains chaining of the two strings.
   */
  friend  vl_string& operator+(vl_string& str1, const char* val)
  {
    str1 += val;
    return str1;
  }
  /**
   * gets a vl_string and a char and adds the char to the vl_string
   * @param str1 the vl_string
   * @param val the char
   * @return first vl_stream that now contains chaining of the
   * original string and the char
   */
  friend  vl_string& operator+(vl_string& str1, const char val)
  {
    str1 += val;
    return str1;
  }

  /**
   * implicit casting operator to char*
   * @return the data that was in vl_vector as char*.
   */
  operator char*() const {return this->_data;}
};

#endif //_VL_STRING_H_
