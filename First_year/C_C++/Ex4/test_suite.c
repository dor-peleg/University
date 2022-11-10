#include "test_suite.h"
#include "test_pairs.h"
#include "hash_funcs.h"

/**
 * This function checks the hashmap_insert function of the hashmap library.
 * If hashmap_insert fails at some points,
 * the functions exits with exit code 1.
 */
void test_hash_map_insert(void)
{
  hashmap *map = hashmap_alloc (hash_char);

  for (int i = 1; i < 13; i++)
    {
      char key = (char) (i + 48);
      int value = i;
      pair *mypair = pair_alloc (&key, &value, char_key_cpy, int_value_cpy,
                                 char_key_cmp, int_value_cmp,
                                 char_key_free, int_value_free);
      hashmap_insert (map, mypair);
      assert(map->capacity == 16);
      pair_free((void**)&mypair);
    }
  assert(map->size == 12);
  assert(map->capacity == 16);

  char key = (char) (13 + 48);
  int value = 13;
  pair *mypair = pair_alloc (&key, &value, char_key_cpy, int_value_cpy,
                             char_key_cmp, int_value_cmp,
                             char_key_free, int_value_free);
  hashmap_insert (map, mypair);
  assert(map->size == 13);
  assert(map->capacity == 32);
  pair_free((void**)&mypair);

  for (int i = 14; i < 25; i++)
    {
      char char_key = (char) (i + 48);
      int int_value = i;
      pair *my_char_pair = pair_alloc (&char_key, &int_value, char_key_cpy,
                                       int_value_cpy, char_key_cmp,
                                       int_value_cmp, char_key_free,
                                       int_value_free);
      hashmap_insert (map, my_char_pair);
      assert(map->capacity == 32);
      pair_free((void**)&my_char_pair);
    }
  assert(map->size == 24);
  assert(map->capacity == 32);

  key = (char) (25 + 48);
  value = 25;
  mypair = pair_alloc (&key, &value, char_key_cpy, int_value_cpy, char_key_cmp,
                       int_value_cmp, char_key_free, int_value_free);
  hashmap_insert (map, mypair);
  assert(map->size == 25);
  assert(map->capacity == 64);
  pair_free((void**)&mypair);

    // check NULL pointers
  hashmap *null_map = NULL;
  pair *pair_null = NULL;
  assert(hashmap_insert (null_map, mypair) == 0);
  assert(hashmap_insert (map, pair_null) == 0);

  // checks already existing pairs
  for (int i = 1; i < 24; i++)
    {
      char key = (char) (i + 48);
      int value = 1;
      pair *mypair = pair_alloc (&key, &value, char_key_cpy,
                                 int_value_cpy, char_key_cmp,
                                 int_value_cmp, char_key_free, int_value_free);
      hashmap_insert (map, mypair);
      assert(map->size == 25);
      assert(map->capacity == 64);
      pair_free((void**)&mypair);

    }
  hashmap_free (&map);

  hashmap *int_map = hashmap_alloc (hash_int);
  assert(int_map->size == 0);
  assert(int_map->capacity == 16);

  pair* p = NULL;
  assert(hashmap_insert (null_map, p) == 0);
  assert(hashmap_insert (int_map, pair_null) == 0);

  for (int i=0; i<200; i++)
    {
      int int_key = i;
      int int_value = i+1;
      pair *int_pair = pair_alloc (&int_key, &int_value, int_key_cpy,
                                   int_value_cpy, char_key_cmp,
                                 int_value_cmp, char_key_free, int_value_free);
      hashmap_insert (int_map, int_pair);
      pair_free((void**)&int_pair);

    }
  assert(int_map->capacity == 512);
  assert(int_map->size == 200);

  for (int i=0; i<201; i++)
    {
      int int_key = i;
      int int_value = i;
      pair *int_pair = pair_alloc (&int_key, &int_value, int_key_cpy,
                                   int_value_cpy, char_key_cmp,
                                   int_value_cmp, char_key_free,
                                   int_value_free);
      hashmap_insert (int_map, int_pair);
        pair_free((void**)&int_pair);
    }
  assert(int_map->capacity == 512);
  assert(int_map->size == 201);
  hashmap_free (&int_map);
}

/**
 * This function checks the hashmap_at function of the hashmap library.
 * If hashmap_at fails at some points, the functions exits with exit code 1.
 */
void test_hash_map_at(void)
{
  hashmap *int_map = NULL;
  keyT k = 0;
  assert(hashmap_at(int_map, &k) == NULL);
  int_map = hashmap_alloc (hash_int);
  assert(int_map->size == 0);
  assert(int_map->capacity == 16);

    for (int i=0; i<10; i++)
      {
        int int_key = i;
        int int_value = i + 1;
        pair *int_pair = pair_alloc (&int_key, &int_value, int_key_cpy,
                                     int_value_cpy, char_key_cmp,
                                     int_value_cmp, char_key_free,
                                     int_value_free);
        hashmap_insert (int_map, int_pair);
          pair_free((void**)&int_pair);
      }
  assert(int_map->capacity == 16);
  assert(int_map->size == 10);

  valueT val_arr[11];
  for (int i=0; i<11; i++)
    {
      keyT key = &i;
      val_arr[i] = hashmap_at (int_map, key);
    }
  assert(*(int*)val_arr[0] == 1);
  assert(*(int*)val_arr[1] == 2);
  assert(*(int*)val_arr[2] == 3);
  assert(*(int*)val_arr[3] == 4);
  assert(*(int*)val_arr[4] == 5);
  assert(*(int*)val_arr[5] == 6);
  assert(*(int*)val_arr[6] == 7);
  assert(*(int*)val_arr[7] == 8);
  assert(*(int*)val_arr[8] == 9);
  assert(*(int*)val_arr[9] == 10);
  assert(val_arr[10] == NULL);

  hashmap_free (&int_map);
}

/**
 * This function checks the hashmap_erase function of the hashmap library.
 * If hashmap_erase fails at some points, the functions exits with exit code 1.
 */
void test_hash_map_erase(void)
{
  hashmap *int_map = NULL;
  keyT k = 0;
  assert(hashmap_erase (int_map, &k) == 0);
  int_map = hashmap_alloc (hash_int);
  assert(int_map->size == 0);
  assert(int_map->capacity == 16);

  for (int i = 0; i < 14; i++)
    {
      int int_key = i;
      int int_value = i + 1;
      pair *int_pair = pair_alloc (&int_key, &int_value, int_key_cpy,
                                   int_value_cpy, int_key_cmp,
                                   int_value_cmp, int_key_free,
                                   int_value_free);
      hashmap_insert (int_map, int_pair);
        pair_free((void**)&int_pair);
    }
  assert(int_map->capacity == 32);
  assert(int_map->size == 14);
  int nums[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

  assert(*(int *) hashmap_at (int_map, &nums[0]) == 1);
  assert(*(int *) hashmap_at (int_map, &nums[1]) == 2);
  assert(*(int *) hashmap_at (int_map, &nums[2]) == 3);
  assert(*(int *) hashmap_at (int_map, &nums[3]) == 4);
  assert(*(int *) hashmap_at (int_map, &nums[4]) == 5);
  assert(*(int *) hashmap_at (int_map, &nums[5]) == 6);
  assert(*(int *) hashmap_at (int_map, &nums[6]) == 7);
  assert(*(int *) hashmap_at (int_map, &nums[7]) == 8);
  assert(*(int *) hashmap_at (int_map, &nums[8]) == 9);
  assert(*(int *) hashmap_at (int_map, &nums[9]) == 10);

  for (int i = 0; i < 6; i++)
    {
      keyT key = &i;
      assert(hashmap_erase (int_map, key) == 1);
    }
  assert(hashmap_at (int_map, &nums[0]) == NULL);
  assert(hashmap_at (int_map, &nums[1]) == NULL);
  assert(hashmap_at (int_map, &nums[2]) == NULL);
  assert(hashmap_at (int_map, &nums[3]) == NULL);
  assert(hashmap_at (int_map, &nums[4]) == NULL);
  assert(hashmap_at (int_map, &nums[5]) == NULL);
  assert(*(int *) hashmap_at (int_map, &nums[6]) == 7);
  assert(*(int *) hashmap_at (int_map, &nums[7]) == 8);
  assert(*(int *) hashmap_at (int_map, &nums[8]) == 9);
  assert(*(int *) hashmap_at (int_map, &nums[9]) == 10);

  assert(int_map->capacity == 32);
  assert(int_map->size == 8);

  assert(hashmap_erase (int_map, &nums[0]) == 0);
  assert(hashmap_erase (int_map, &nums[1]) == 0);
  assert(hashmap_erase (int_map, &nums[2]) == 0);
  assert(hashmap_erase (int_map, &nums[3]) == 0);
  assert(hashmap_erase (int_map, &nums[4]) == 0);
  assert(hashmap_erase (int_map, &nums[5]) == 0);
  assert(hashmap_erase (int_map, &nums[6]) == 1);

  assert(int_map->capacity == 16);
  assert(int_map->size == 7);

  for (int i = 7; i < 10; i++)
    assert(hashmap_erase (int_map, &nums[i]) == 1);

  assert(int_map->capacity == 16);
  assert(int_map->size == 4);

  assert(hashmap_erase (int_map, &nums[7]) == 0);
  assert(hashmap_erase (int_map, &nums[8]) == 0);
  assert(hashmap_erase (int_map, &nums[9]) == 0);
  assert(hashmap_erase (int_map, &nums[10]) == 1);

  assert(int_map->capacity == 8);
  assert(int_map->size == 3);

  for (int i = 11; i < 13; i++)
    assert(hashmap_erase (int_map, &nums[i]) == 1);

  assert(hashmap_erase (int_map, &nums[11]) == 0);
  assert(hashmap_erase (int_map, &nums[12]) == 0);

  assert(int_map->capacity == 4);
  assert(int_map->size == 1);

  assert(hashmap_erase (int_map, &nums[13]) == 1);
  assert(hashmap_erase (int_map, &nums[13]) == 0);
  assert(int_map->capacity == 2);
  assert(int_map->size == 0);

  pair *int_pair = pair_alloc (&nums[0], &nums[0], int_key_cpy,
                               int_value_cpy, int_key_cmp,
                               int_value_cmp, int_key_free, int_value_free);
  hashmap_insert (int_map, int_pair);
  assert(int_map->capacity == 2);
  assert(int_map->size == 1);

  assert(hashmap_erase (int_map, &nums[0]) == 1);
  assert(int_map->capacity == 1);
  assert(int_map->size == 0);

  hashmap_insert (int_map, int_pair);
  assert(int_map->capacity == 2);
  assert(int_map->size == 1);
    pair_free((void**)&int_pair);

  assert(hashmap_erase (int_map, &nums[0]) == 1);
  assert(int_map->capacity == 1);
  assert(int_map->size == 0);

  for (int i = 0; i < 14; i++)
    {
      assert(hashmap_erase (int_map, &nums[i]) == 0);
      assert(hashmap_at (int_map, &nums[i]) == NULL);
    }
  hashmap_free (&int_map);

  ////////////////////////////////////////////////////////////
  hashmap *map = hashmap_alloc (hash_int);
  if (map == NULL)
    {
      return;
    }
  int int_arr[10];
  for (int i = 0; i < 10; i++)
    int_arr[i] = 16 * i;

  for (int i = 0; i < 10; i++)
    {
      pair *pair1 = pair_alloc (&int_arr[i], &int_arr[i], int_key_cpy,
                                int_value_cpy, int_key_cmp,
                                int_value_cmp, int_key_free, int_value_free);
      hashmap_insert (map, pair1);
        pair_free((void**)&pair1);
    }
  assert(map->buckets[0]->size == 10);

  assert(hashmap_erase (map, &int_arr[0]) == 1);
  for (int i = 0; i < 9; i++)
    assert(vector_at (map->buckets[0], i) != NULL);
  assert(vector_at (map->buckets[0], 10) == NULL);
  for (int i = 1; i < 5; i++)
      assert(hashmap_erase (map, &int_arr[i]) == 1);
  for (int i = 0; i < 5; i++)
    assert(hashmap_erase (map, &int_arr[i]) == 0);
  for (int i = 0; i < 4; i++)
    {
      if (i<5)
        assert(vector_at (map->buckets[0], i) != NULL);
      if (i>=5)
        assert(vector_at (map->buckets[0], i) == NULL);
    }
  for (int i = 5; i < 10; i++)
    assert(hashmap_erase (map, &int_arr[i]) == 1);
  for (int i = 0; i < 10; i++)
    {
      assert(hashmap_erase (map, &int_arr[i]) == 0);
      assert(vector_at (map->buckets[0], i) == NULL);
    }
  assert(map->buckets[0]->size == 0);
  hashmap_free (&map);
}

/**
 * This function checks the hashmap_get_load_factor function of
 * the hashmap library.
 * If hashmap_get_load_factor fails at some points, the functions
 * exits with exit code 1.
 */
void test_hash_map_get_load_factor(void)
{
  hashmap *long_hash = hashmap_alloc (hash_unsigned_long);
  for (unsigned long i = 0; i < 13; i++)
    {
      unsigned long long_key = i;
      double double_value = (double) long_key + 1.5;
      pair *long_pair = pair_alloc (&long_key, &double_value, long_key_cpy,
                                    double_value_cpy, long_key_cmp,
                                    double_value_cmp, long_key_free,
                                    double_value_free);
      hashmap_insert (long_hash, long_pair);
        pair_free((void**)&long_pair);
    }
  assert(long_hash->capacity == 32);
  assert(long_hash->size == 13);
  assert(hashmap_get_load_factor (long_hash) == (double) 13 / 32);

  for (unsigned long i = 13; i < 16; i++)
    {
      unsigned long long_key = i;
      double double_value = (double) long_key + 1.5;
      pair *long_pair = pair_alloc (&long_key, &double_value, long_key_cpy,
                                    double_value_cpy, long_key_cmp,
                                    double_value_cmp, long_key_free,
                                    double_value_free);
      hashmap_insert (long_hash, long_pair);
        pair_free((void**)&long_pair);
    }
  assert(long_hash->capacity == 32);
  assert(long_hash->size == 16);
  assert(hashmap_get_load_factor (long_hash) == 0.5);

  for (unsigned long i = 0; i < 8; i++)
    {
      unsigned long long_key = i;
      hashmap_erase (long_hash, &long_key);
    }
  assert(long_hash->capacity == 32);
  assert(long_hash->size == 8);
  assert(hashmap_get_load_factor (long_hash) == 0.25);

  {
    unsigned long long_key = 8;
    hashmap_erase (long_hash, &long_key);
  }
  assert(long_hash->capacity == 16);
  assert(long_hash->size == 7);
  assert(hashmap_get_load_factor (long_hash) == (double)7/16);

  for (unsigned long i = 0; i < 14; i++)
    {
      unsigned long long_key = i;
      hashmap_erase(long_hash, &long_key);
    }
  assert(long_hash->capacity == 8);
  assert(long_hash->size == 2);
  assert(hashmap_get_load_factor (long_hash) == 0.25);

  {
    unsigned long long_key = 14;
    double double_value = (double) long_key + 1.5;
    pair *long_pair = pair_alloc (&long_key, &double_value, long_key_cpy,
                                  double_value_cpy, long_key_cmp,
                                  double_value_cmp, long_key_free,
                                  double_value_free);
    hashmap_erase (long_hash, &long_key);
    assert(long_hash->capacity == 4);
    assert(long_hash->size == 1);
    assert(hashmap_get_load_factor (long_hash) == 0.25);
    hashmap_insert (long_hash,long_pair);
      pair_free((void**)&long_pair);
  }
  assert(long_hash->capacity == 4);
  assert(long_hash->size == 2);
  assert(hashmap_get_load_factor (long_hash) == 0.5);

  for (unsigned long i = 14; i < 16; i++)
    {
      unsigned long long_key = i;
      hashmap_erase(long_hash, &long_key);
    }
  assert(long_hash->capacity == 2);
  assert(long_hash->size == 0);
  assert(hashmap_get_load_factor (long_hash) == 0);

  {
    unsigned long long_key = 4294967200;
    double double_value = (double) long_key + 1.5;
    pair *long_pair = pair_alloc (&long_key, &double_value, long_key_cpy,
                                  double_value_cpy, long_key_cmp,
                                  double_value_cmp, long_key_free,
                                  double_value_free);
    hashmap_insert (long_hash, long_pair);
    assert(long_hash->capacity == 2);
    assert(long_hash->size == 1);
    assert(hashmap_get_load_factor (long_hash) == 0.5);

    hashmap_erase (long_hash, &long_key);
    assert(long_hash->capacity == 1);
    assert(long_hash->size == 0);
    assert(hashmap_get_load_factor (long_hash) == 0);

    hashmap_insert (long_hash, long_pair);
    assert(long_hash->capacity == 2);
    assert(long_hash->size == 1);
    assert(hashmap_get_load_factor (long_hash) == 0.5);
      pair_free((void**)&long_pair);

    long_key = 1;
    double_value = (double) long_key + 1.5;
    long_pair = pair_alloc (&long_key, &double_value, long_key_cpy,
                            double_value_cpy, long_key_cmp,
                                  double_value_cmp, long_key_free,
                                  double_value_free);
    hashmap_insert (long_hash, long_pair);
    assert(long_hash->capacity == 4);
    assert(long_hash->size == 2);
    assert(hashmap_get_load_factor (long_hash) == 0.5);
      pair_free((void**)&long_pair);
  }
  hashmap_free (&long_hash);
}

/**
 * This function checks the HashMapGetApplyIf function of the hashmap library.
 * If HashMapGetApplyIf fails at some points, the functions exits with
 * exit code 1.
 */
void test_hash_map_apply_if()
{
  hashmap *null_map = NULL;
  keyT_func null_func = NULL;
  valueT_func null_func1 = NULL;
  hashmap *char_map = hashmap_alloc (hash_char);
  assert(hashmap_apply_if (null_map, is_digit, double_value) == -1);
  assert(hashmap_apply_if (char_map, null_func, double_value) == -1);
  assert(hashmap_apply_if (char_map, is_digit, null_func1) == -1);
  assert(hashmap_apply_if (null_map, null_func, null_func1) == -1);

  for (int j = 0; j < 10; ++j)
    {
      char key = (char) (j + 48);
      //even keys are capital letters, odd keys are digits
      if (key % 2)
        {
          key += 17;
        }
      int value = j;
      pair *p = pair_alloc (&key, &value, char_key_cpy, int_value_cpy,
                            char_key_cmp,int_value_cmp,
                            char_key_free, int_value_free);
      hashmap_insert (char_map, p);
        pair_free((void**)&p);
    }
  assert(hashmap_apply_if (char_map, is_digit, double_value) == 5);
  const_keyT k = (const_keyT)"0";
  hashmap_erase (char_map, k);
  assert(hashmap_apply_if (char_map, is_digit, double_value) == 4);
  k = (const_keyT)"B";
  hashmap_erase (char_map, k);
  assert(hashmap_apply_if (char_map, is_digit, double_value) == 4);
  k = (const_keyT)"0";
  hashmap_erase (char_map, k);
  assert(hashmap_apply_if (char_map, is_digit, double_value) == 4);
  k = (const_keyT)"2";
  hashmap_erase (char_map, k);
  assert(hashmap_apply_if (char_map, is_digit, double_value) == 3);
  k = (const_keyT)"4";
  hashmap_erase (char_map, k);
  assert(hashmap_apply_if (char_map, is_digit, double_value) == 2);
  k = (const_keyT)"6";
  hashmap_erase (char_map, k);
  assert(hashmap_apply_if (char_map, is_digit, double_value) == 1);
  k = (const_keyT)"8";
  hashmap_erase (char_map, k);
  assert(hashmap_apply_if (char_map, is_digit, double_value) == 0);

  hashmap_free (&char_map);
}