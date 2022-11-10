#include "hashmap.h"


/**
 * Allocates dynamically new hash map element.
 * @param func a function which "hashes" keys.
 * @return pointer to dynamically allocated hashmap.
 * @if_fail return NULL.
 */
hashmap *hashmap_alloc (hash_func func)
{
  hashmap *new_hm = malloc(sizeof (hashmap));
  if (new_hm == NULL)
    {
      return NULL;
    }
  if (func == NULL)
    {
      free(new_hm);
      return NULL;
    }
  new_hm->capacity = HASH_MAP_INITIAL_CAP;
  new_hm->size = 0;
  new_hm->hash_func = func;
  new_hm->buckets = malloc(sizeof (vector*) * new_hm->capacity);
  if (new_hm->buckets == NULL)
    {
      free(new_hm);
      return NULL;
    }
  for (unsigned long i=0; i<HASH_MAP_INITIAL_CAP;i++)
    {
      new_hm->buckets[i] = vector_alloc(pair_copy, pair_cmp, pair_free);
    }
  return new_hm;
}

/**
 * the function check if a key already appear in the hash_map,
 * if so, returns its index in the vector.
 * @param vec vector (bucket)
 * @param key the key
 * @return the key's index if it appears in the vector, -1 otherwise
 */
int check_if_exist(vector *vec, const_keyT key)
{
  if (vec == NULL)
    {
      return -1;
    }
  for (int i=0; i<(int)vec->size; i++)
    {
      pair *p = (pair *)vec->data[i];
      int key_cmp = p->key_cmp (p->key, key);
      if (key_cmp == 1)
        {
          return i; // key exist
        }
    }
  return -1; // key doesnt exist
}
/**
 * the function gets hash_map with new capacity and transfers all the values
 * in the hashmap to their new hash value.
 * @param hash_map the hashmap
 * @param old_cap the capacity of the hashmap before the change.
 * @return 1 if all the values transferred successfully, 0 otherwise.
 */
int re_hash(hashmap *hash_map, size_t old_cap)
{
  if (hash_map == NULL)
    {
      return 0;
    }
  vector **old = hash_map->buckets;
  vector **new = malloc (sizeof (vector*) * hash_map->capacity);
  if (new == NULL)
    {
      return 0;
    }
  for (int i=0; i<(int)hash_map->capacity; i++)
    {
      new[i] = vector_alloc(pair_copy, pair_cmp, pair_free);
      if (new[i] == NULL)
        {
          for (int j=(int)old_cap; j<i; j++)
            {
              vector_free (&new[j]);
            }
          free(new);
          return 0;
        }
    }
  for (int i=0; i<(int)old_cap; i++)
    {
      for (int j=0; j<(int)old[i]->size; j++)
        {
          pair *p = vector_at(old[i], j);
          size_t new_num = hash_map->hash_func(p->key);
          size_t new_bucket = new_num & (hash_map->capacity - 1);
          int check = vector_push_back(new[new_bucket], p);
          if (check == 0)
            {
              for (int t=0; t<(int)hash_map->capacity; t++)
                {
                  vector_free (&new[i]);
                }
              free(new);
              return 0;
            }
        }
    }
  for (size_t i=0; i<old_cap; i++)
  {
      vector_free (&old[i]);
  }
  free(old);
  hash_map->buckets = new;
  new = NULL;
  return 1;
}

/**
 * Inserts a new in_pair to the hash map.
 * The function inserts *new*, *copied*, *dynamically allocated* in_pair,
 * NOT the in_pair it receives as a parameter.
 * @param hash_map the hash map to be inserted with new element.
 * @param in_pair a in_pair the hash map would contain.
 * @return returns 1 for successful insertion, 0 otherwise.
 */
int hashmap_insert (hashmap *hash_map, const pair *in_pair)
{
  if (hash_map == NULL || in_pair == NULL)
    {
      return 0;
    }
  hash_map->size++;
  double load_fac = hashmap_get_load_factor(hash_map);
  if (load_fac > HASH_MAP_MAX_LOAD_FACTOR)
    {
//      hashmap *new_hash_map = hashmap_alloc(hash_map->hash_func);
      hash_map->capacity = hash_map->capacity * HASH_MAP_GROWTH_FACTOR;
      int check = re_hash(hash_map, hash_map->capacity / 2);
      if (check == 0)
        {
          hash_map->size--;
          hash_map->capacity = hash_map->capacity / HASH_MAP_GROWTH_FACTOR;
          return 0;
        }
    }

  size_t elem_num = hash_map->hash_func(in_pair->key);
  size_t bucket = elem_num & (hash_map->capacity - 1);
  if (check_if_exist(hash_map->buckets[bucket], in_pair->key) != -1)
    {
      hash_map->size--;
      return 0;
    }
  int check = vector_push_back(hash_map->buckets[bucket], in_pair);
  if (check == 0)
    {
      hash_map->size--;
      return 0;
    }
  return 1;
}

/**
 * the function gets a key and a vector, and returns the value
 * associated with this key
 * @param vec a vector with pair elements
 * @param key key to search
 * @return  the value associated with the key, NULL if problem.
 */
valueT find_val(vector *vec, const_keyT key)
{
  if (vec == NULL)
    {
      return NULL;
    }
  for (int i=0; i<(int)vec->size; i++)
    {
      pair *p = (pair *)vec->data[i];
      int key_cmp = p->key_cmp (p->key, key);
      if (key_cmp == 1)
        {
          return p->value;
        }
    }
  return NULL;
}


/**
 * The function returns the value associated with the given key.
 * @param hash_map a hash map.
 * @param key the key to be checked.
 * @return the value associated with key if exists, NULL otherwise
 * (the value itself, not a copy of it).
 */
valueT hashmap_at (const hashmap *hash_map, const_keyT key)
{
  if (hash_map == NULL)
    {
      return NULL;
    }
  size_t num = hash_map->hash_func(key);
  size_t bucket = num & (hash_map->capacity - 1);
  valueT val = find_val(hash_map->buckets[bucket], key);
  if (val == NULL)
    {
      return NULL;
    }
  return val;
}

/**
 * This function returns the load factor of the hash map.
 * @param hash_map a hash map.
 * @return the hash map's load factor, -1 if the function failed.
 */
double hashmap_get_load_factor (const hashmap *hash_map)
{
  if (hash_map == NULL)
    {
      return -1;
    }
  return ((double)hash_map->size / (double)hash_map->capacity);
}

/**
 * This function receives a hashmap and 2 functions, the first checks a
 * condition on the keys,
 * and the seconds apply some modification on the values. The function should
 * apply the modification only on the values that are associated
 * with keys that meet the condition.
 *
 * Example: if the hashmap maps char->int, keyT_func checks if the char is a
 * capital letter (A-Z),
 * and val_t_func multiples the number by 2, hashmap_apply_if will change the
 * map:
 * {('C',2),('#',3),('X',5)}, to: {('C',4),('#',3),('X',10)}, and the return
 * value will be 2.
 * @param hash_map a hashmap
 * @param keyT_func a function that checks a condition on keyT and
 * return 1 if true, 0 else
 * @param valT_func a function that modifies valueT, in-place
 * @return number of changed values
 */
int hashmap_apply_if (const hashmap *hash_map, keyT_func keyT_func,
                      valueT_func valT_func)
{
  if (hash_map == NULL || keyT_func == NULL || valT_func == NULL)
    {
      return -1;
    }
  int counter = 0;
  for (int i=0; i<(int)hash_map->capacity; i++)
    {
      for (int j=0; j<(int)hash_map->buckets[i]->size; j++)
        {
          pair *p = hash_map->buckets[i]->data[j];
          if (keyT_func(p->key) == 1)
            {
              valT_func(p->value);
              counter++;
            }
        }
    }
  return counter;
}

/**
 * The function erases the pair associated with key.
 * @param hash_map a hash map.
 * @param key a key of the pair to be erased.
 * @return 1 if the erasing was done successfully, 0 otherwise.
 * (if key not in map, considered fail).
 */
int hashmap_erase (hashmap *hash_map, const_keyT key)
{
  if (hash_map == NULL)
    return 0;

  size_t num = hash_map->hash_func(key);
  size_t bucket = num & (hash_map->capacity - 1);
  int idx = check_if_exist (hash_map->buckets[bucket], key);
  if (idx == -1)
    return 0;

  int result = vector_erase(hash_map->buckets[bucket], idx);
  if (result == 0)
    return 0;

  hash_map->size--;
  double load_fac = hashmap_get_load_factor(hash_map);
  if (load_fac < HASH_MAP_MIN_LOAD_FACTOR && hash_map->capacity > 1)
    {
      hash_map->capacity = hash_map->capacity / HASH_MAP_GROWTH_FACTOR;
      int check = re_hash(hash_map, hash_map->capacity * 2);
      if (check == 0)
        {
          hash_map->size++;
          hash_map->capacity = hash_map->capacity * HASH_MAP_GROWTH_FACTOR;
          return 0;
        }
    }
  return 1;
}

/**
 * Frees a hash map and the elements the hash map itself allocated.
 * @param p_hash_map pointer to dynamically allocated pointer to hash_map.
 */
void hashmap_free (hashmap **p_hash_map)
{
  if (p_hash_map == NULL || *p_hash_map == NULL)
    return;

  for (int i=0; i<(int)((*p_hash_map)->capacity); i++)
    {
      vector_free (&((*p_hash_map)->buckets[i]));
    }
  free((*p_hash_map)->buckets);
  (*p_hash_map)->buckets = NULL;
  free(*p_hash_map);
  *p_hash_map = NULL;
  p_hash_map = NULL;
}