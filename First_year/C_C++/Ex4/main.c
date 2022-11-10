#include "test_pairs.h"
#include "hash_funcs.h"
#include "hashmap.h"
//#include "test_suite.h"
#include <assert.h>

#include <stdio.h>

void *elem_cpy (const void *elem)
{
  int *a = malloc (sizeof (int));
  *a = *((int *) elem);
  return a;
}
int elem_cmp (const void *elem_1, const void *elem_2)
{
  return *((const int *) elem_1) == *((const int *) elem_2);
}
void elem_free (void **elem)
{
  free (*elem);
}

/////
int main ()
{
//    hashmap *h = hashmap_alloc(hash_int);
//    int key = 0;
//    int val = 0;
//    pair* p = pair_alloc(&key, &val, int_key_cpy, int_value_cpy, int_key_cmp,
//                         int_value_cmp, int_key_free, int_value_free);
//    hashmap_insert(h, p);
//    hashmap_free(&h);
//    pair_free((void **) &p);
//  printf("start\n");
//  // Insert elements to vec.
//  vector *vec = vector_alloc (elem_cpy, elem_cmp, elem_free);
//  for (int i = 0; i < 8; ++i)
//    {
//      vector_push_back (vec, &i);
//      for (size_t j=0; j<vec->size; j++)
//        {
//          printf("%d ", *((int *)vec->data[j]));
//        }
//      printf("\n");
//    }
//  for (int i=0; i<4; i++)
//    {
//      vector_erase(vec, i);
//      for (size_t j=0; j<vec->size; j++)
//        {
//          printf("%d ", *((int *)vec->data[j]));
//        }
//      printf("\n");
//    }
//  vector_free (&vec);
//  printf("end vector\n");
//
//  // Create Pairs.
//  printf("start pairs\n");
//  pair *pairs[8];
//  for (int j = 0; j < 8; ++j)
//    {
//      char key = (char) (j + 48);
//      //even keys are capital letters, odd keys are digits
//      if (key % 2)
//        {
//          key += 17;
//        }
//      int value = j;
//      pairs[j] = pair_alloc (&key, &value, char_key_cpy, int_value_cpy, char_key_cmp,
//                             int_value_cmp, char_key_free, int_value_free);
//    }
//  printf("end pairs\n");
//  // Create hash-map and inserts elements into it, using pair_char_int.h
//  hashmap *map = hashmap_alloc (hash_char);
//
//  printf("alloc good\n");
//  for (int k = 0; k < 8; ++k)
//    {
//      hashmap_insert (map, pairs[k]);
//    }
//  printf("insert good\n");
//  for (size_t i=0; i<map->capacity; i++)
//    {
//      printf("Bucket %zu: ", i);
//      for (size_t k=0; k<map->buckets[i]->size; k++)
//        {
//          pair* p = (pair*)map->buckets[i]->data[k];
//          printf("%c : %d   ", *(char *)p->key, *(int *)p->value);
//        }
//      printf("\n");
//    }
//  //apply double_value on values where key is a digit
//  char key_dig = '2', key_letter = 'D';
//  printf ("map['2'] before apply if: %d, map['D'] before apply if: %d\n",
//          *(int *) hashmap_at (map, &key_dig), *(int *) hashmap_at (map, &key_letter));
//  int apply_if_res = hashmap_apply_if (map, is_digit, double_value);
//  printf ("Number of changed values: %d\n", apply_if_res);
//  printf ("map['2'] after apply if: %d, map['D'] after apply if: %d\n",
//          *(int *) hashmap_at (map, &key_dig), *(int *) hashmap_at (map, &key_letter));
//  // Free the pairs.
//  for (int k_i = 0; k_i < 8; ++k_i)
//    {
//      pair_free ((void **) &pairs[k_i]);
//    }
//  // Free the hash-map.
//  hashmap_free (&map);
//  printf ("finished");

//  printf ("start tests\n");
//  test_hash_map_insert();
//  test_hash_map_at();
//  test_hash_map_erase();
//  test_hash_map_get_load_factor();
//  test_hash_map_apply_if();
//  printf ("finished tests\n");
    printf("start");
    hashmap *map = hashmap_alloc (hash_char);

    for (int i = 1; i < 13; i++)
    {
        char key = (char) (i + 48);
        int value = i;
        pair *mypair = pair_alloc (&key, &value, char_key_cpy, int_value_cpy, char_key_cmp,
                                   int_value_cmp, char_key_free, int_value_free);
        hashmap_insert (map, mypair);
        assert(map->capacity == 16);
        pair_free(&mypair);
    }
    assert(map->size == 12);
    assert(map->capacity == 16);

    char key = (char) (13 + 48);
    int value = 13;
    pair *mypair = pair_alloc (&key, &value, char_key_cpy, int_value_cpy, char_key_cmp,
                               int_value_cmp, char_key_free, int_value_free);
    hashmap_insert (map, mypair);
    pair_free(&mypair);
    assert(map->size == 13);
    assert(map->capacity == 32);


    for (int i = 14; i < 25; i++)
    {
        char key = (char) (i + 48);
        int value = i;
        pair *mypair = pair_alloc (&key, &value, char_key_cpy, int_value_cpy, char_key_cmp,
                                   int_value_cmp, char_key_free, int_value_free);
        hashmap_insert (map, mypair);
        assert(map->capacity == 32);
        pair_free(&mypair);
    }
    assert(map->size == 24);
    assert(map->capacity == 32);

    key = (char) (25 + 48);
    value = 25;
    mypair = pair_alloc (&key, &value, char_key_cpy, int_value_cpy, char_key_cmp,
                         int_value_cmp, char_key_free, int_value_free);
    hashmap_insert (map, mypair);
    pair_free(&mypair);
    assert(map->size == 25);
    assert(map->capacity == 64);

//     check NULL pointers
    hashmap *null_map = NULL;
    pair *pair_null = NULL;
    assert(hashmap_insert (null_map, mypair) == 0);
    assert(hashmap_insert (map, pair_null) == 0);

    // checks already existing pairs
    for (int i = 1; i < 24; i++)
    {
        char key = (char) (i + 48);
        int value = 1;
        pair *mypair = pair_alloc (&key, &value, char_key_cpy, int_value_cpy, char_key_cmp,
                                   int_value_cmp, char_key_free, int_value_free);
        hashmap_insert (map, mypair);
        assert(map->size == 25);
        assert(map->capacity == 64);
        pair_free(&mypair);

    }
    hashmap_free (&map);
    printf("finish");
  return 0;
}

