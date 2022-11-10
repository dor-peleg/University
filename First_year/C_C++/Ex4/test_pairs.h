#ifndef _TEST_PAIRS_H_
#define _TEST_PAIRS_H_

#include <stdlib.h>
#include "pair.h"

//  {char:int}
/**
 * Copies the char key of the pair.
 */
void *char_key_cpy (const_keyT key)
{
  char *new_char = malloc (sizeof (char));
  *new_char = *((char *) key);
  return new_char;
}
/**
 * Copies the int value of the pair.
 */
void *int_value_cpy (const_valueT value)
{
  int *new_int = malloc (sizeof (int));
  *new_int = *((int *) value);
  return new_int;
}
/**
 * Compares the char key of the pair.
 */
int char_key_cmp (const_keyT key_1, const_keyT key_2)
{
  return *(char *) key_1 == *(char *) key_2;
}
/**
 * Compares the int value of the pair.
 */
int int_value_cmp (const_valueT val_1, const_valueT val_2)
{
  return *(int *) val_1 == *(int *) val_2;
}
/**
 * Frees the char key of the pair.
 */
void char_key_free (keyT* key)
{
  if (key && *key)
    {
      free (*key);
      *key = NULL;
    }
}
/**
 * Frees the int value of the pair.
 */
void int_value_free (valueT *val)
{
  if (val && *val)
    {
      free (*val);
      *val = NULL;
    }
}
/**
 * @param elem pointer to a char (keyT of pair_char_int)
 * @return 1 if the char represents a digit, else - 0
 */
int is_digit (const_keyT elem)
{
  char c = *((char *) elem);
  return (c > 47 && c < 58);
}
/**
 * doubles the value pointed to by the given pointer
 * @param elem pointer to an integer (valT of pair_char_int)
 */
void double_value (valueT elem)
{
  *((int *) elem) *= 2;
}

////////////////////////////////////////////////////////////////

//  {int:int}
/**
 * Copies the int key of the pair.
 */
void *int_key_cpy (const_keyT key)
{
  int *new_int = malloc (sizeof (int));
  *new_int = *((int *) key);
  return new_int;
}

/**
 * Compares the int key of the pair.
 */
int int_key_cmp (const_keyT key_1, const_keyT key_2)
{
  return *(int *) key_1 == *(int *) key_2;
}

/**
 * Frees the int key of the pair.
 */
void int_key_free (keyT* key)
{
  if (key && *key)
    {
      free (*key);
      *key = NULL;
    }
}

/**
 * @param elem pointer to a int (keyT of pair_char_int)
 * @return 1 if the int is even, else - 0
 */
int is_even (const_keyT elem)
{
  int c = *((int *) elem);
  return (c % 2 == 0);
}
/**
 * adds one to the value pointed to by the given pointer
 * @param elem pointer to an integer (valT of pair_char_int)
 */
void add_one_value (valueT elem)
{
  *((int *) elem) += 1;
}


//////////////////////////////////////////////////////////////////////////

//    {unsigned long:double}
/**
 * Copies the long key of the pair.
 */
void *long_key_cpy (const_keyT key)
{
  unsigned long *new_double = malloc (sizeof (unsigned long));
  *new_double = *((unsigned long *) key);
  return new_double;
}

/**
 * Copies the double value of the pair.
 */
void *double_value_cpy (const_valueT value)
{
  double *new_char = malloc (sizeof (double));
  *new_char = *((double *) value);
  return new_char;
}

/**
 * Compares the long key of the pair.
 */
int long_key_cmp (const_keyT key_1, const_keyT key_2)
{
  return *(unsigned long *) key_1 == *(unsigned long *) key_2;
}

/**
 * Compares the double value of the pair.
 */
int double_value_cmp (const_valueT val_1, const_valueT val_2)
{
  return *(double *) val_1 == *(double *) val_2;
}

/**
 * Frees the long key of the pair.
 */
void long_key_free (keyT* key)
{
  if (key && *key)
    {
      free (*key);
      *key = NULL;
    }
}

/**
 * Frees the double value of the pair.
 */
void double_value_free (valueT *val)
{
  if (val && *val)
    {
      free (*val);
      *val = NULL;
    }
}

/**
 * @param elem pointer to a long keyT
 * @return 1 if the long bigger then 10, else - 0
 */
int bigger_than_ten (const_keyT elem)
{
  unsigned long c = *((unsigned long *) elem);
  return (c > 10);
}

/**
 * divide the value pointed to by the given pointer by 3.
 * @param elem pointer to an double
 */
void divide_by_three (valueT elem)
{
  *((double *) elem) /= 3;
}


#endif //_TEST_PAIRS_H_
