#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS_IN_SENTENCE_GENERATION 20
#define MAX_SENTENCE_LENGTH 1000

#define DECIMAL_BASE 10
#define NUM_OF_ARGS 5
#define SUCCESS 0
#define FAILURE 1

#define FILE_NOT_FOUND_ERR "Error: File does not exist!\n"
#define USAGE_ERR "Usage: please enter the correct inputs: "\
    "<seed, number of tweets, path, number of words to read(optional)>\n"


typedef struct WordStruct {
  char *word;
  struct WordProbability *prob_list;
} WordStruct;

typedef struct WordProbability {
  struct WordStruct *word_struct_ptr;
  int num_of_apps;
  struct WordProbability *next;
} WordProbability;

/************ LINKED LIST ************/
typedef struct Node {
  WordStruct *data;
  struct Node *next;
} Node;

typedef struct LinkList {
  Node *first;
  Node *last;
  int size;
} LinkList;

/**
 * Add data to new node at the end of the given link list.
 * @param link_list Link list to add data to
 * @param data pointer to dynamically allocated data
 * @return 0 on success, 1 otherwise
 */
int add(LinkList *link_list, WordStruct *data)
{
  Node *new_node = malloc(sizeof(Node));
  if (new_node == NULL)
  {
	return FAILURE;
  }
  *new_node = (Node){data, NULL};

  if (link_list->first == NULL)
  {
	link_list->first = new_node;
	link_list->last = new_node;
  }
  else
  {
	link_list->last->next = new_node;
	link_list->last = new_node;
  }

  link_list->size++;
  return SUCCESS;
}
/*************************************/

/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
int get_random_number(int max_number)
{
  int random_num = rand()% max_number;
  return random_num;
}

/**
 * checks if given word ends with '.' (nekuda)
 * @param word_struct Wordstruct with word to be check
 * @return 1 if word ends with '.', 0 otherwise.
 */
int check_if_dot(WordStruct* word_struct)
{
  if (strcmp(&word_struct->word[strlen(word_struct->word)-1],".")==0)
    {
      return FAILURE;
    }
  return SUCCESS;
}

/**
 * Choose randomly the next word from the given dictionary, drawn uniformly.
 * The function won't return a word that end's in full stop '.' (Nekuda).
 * @param dictionary Dictionary to choose a word from
 * @return WordStruct of the chosen word
 */
WordStruct *get_first_random_word(LinkList *dictionary)
{
  int max_number = dictionary->size;
  int word_ok = 1;
  WordStruct *first_word = NULL;
  while (word_ok == 1)
    {
      Node *cur = dictionary->first;
      int rand_num = get_random_number(max_number);
      for (int i=0; i<rand_num; i++)
        {
          cur = cur->next;
        }
      first_word = cur->data;
      word_ok = check_if_dot(first_word);
    }
  return first_word;
}

/**
 * Choose randomly the next word. Depend on it's occurrence frequency
 * in word_struct_ptr->WordProbability.
 * @param word_struct_ptr WordStruct to choose from
 * @return WordStruct of the chosen word
 */
WordStruct *get_next_random_word(WordStruct *word_struct_ptr)
{
  int idx = 0;
  int num_of_cells = 0;
  int *prob_lst = malloc(0);
  WordProbability *cur = word_struct_ptr->prob_list;
  while (cur != NULL)
    {
      int num_of_apps = cur->num_of_apps;
      int *temp = realloc(prob_lst, (num_of_apps+num_of_cells) * sizeof (int));
      if (temp == NULL)
        {
          exit(EXIT_FAILURE);
        }
      prob_lst = temp;
      num_of_cells += num_of_apps;
      for (int i=num_of_cells - num_of_apps; i<num_of_cells; i++)
        {
          prob_lst[i] = idx;
        }
      idx += 1;
      cur = cur->next;
    }
  int rand_num = get_random_number(num_of_cells);
  int rand_idx = prob_lst[rand_num];
  cur = word_struct_ptr->prob_list;
  for (int i=0; i<rand_idx; ++i)
    {
      cur = cur->next;
    }
  free(prob_lst);
  prob_lst = NULL;
  return cur->word_struct_ptr;
}

/**
 * Receive dictionary, generate and print to stdout random sentence out of it.
 * The sentence most have at least 2 words in it.
 * @param dictionary Dictionary to use
 * @return Amount of words in printed sentence
 */
int generate_sentence(LinkList *dictionary)
{
  int idx = 0, word_count = 1;
  char space[2] = " ";
  char *temp = NULL;
  WordStruct *next_word;
  WordStruct *first_word = get_first_random_word(dictionary);
  WordStruct *prev_word = first_word;
  char *tweet = (char*) malloc(strlen(first_word->word) + 2);
  if (tweet == NULL)
    {
      exit(EXIT_FAILURE);
    }
  strcpy(tweet + idx, first_word->word);

  while (word_count < MAX_WORDS_IN_SENTENCE_GENERATION &&
  check_if_dot(prev_word) == SUCCESS)
    {
      idx += (int)strlen(prev_word->word);
      strcpy(tweet+ idx, space);
      idx += 1;
      next_word = get_next_random_word(prev_word);
      temp = (char*) realloc(tweet, idx + strlen(next_word->word) +2);
      if (!temp)
        {
          printf("bye");
          exit(EXIT_FAILURE);
        }
      tweet = temp;
      temp = NULL;
      strcpy(tweet+ idx, next_word->word);
      word_count += 1;
      prev_word = next_word;
    }
  printf("%s\n", tweet);
  free(tweet);
  tweet = NULL;
  return word_count;

}

/**
 * Gets 2 WordStructs. If second_word in first_word's prob_list,
 * update the existing probability value.
 * Otherwise, add the second word to the prob_list of the first word.
 * @param first_word
 * @param second_word
 * @return 0 if already in list, 1 otherwise.
 */
int add_word_to_probability_list(WordStruct *first_word,
                                 WordStruct *second_word)
{
  if (strcmp(&first_word->word[strlen(first_word->word)-1], ".") == 0)
    {
      return FAILURE;
    }
  WordProbability *cur = first_word->prob_list;
  while (cur != NULL)
    {
      if (strcmp(cur->word_struct_ptr->word,second_word->word) == 0)
        {
          cur->num_of_apps += 1;
          return 0;
        }
      cur = cur->next;
    }
  WordProbability *new_prob = malloc(sizeof (struct WordProbability));
  new_prob->num_of_apps = 1;
  new_prob->word_struct_ptr = second_word;
  new_prob->next = first_word->prob_list;
  first_word->prob_list = new_prob;
  return FAILURE;
}
/**
 * checks if a word already appeared, and update the prob_list accordingly.
 * @param dictionary the list of words
 * @param new_word the new word
 * @param word the current word
 * @param prev_word the previous word
 * @param exist_flg 1 if the word already appeared, 0 else
 */
void update_prob_lst (LinkList *dictionary, WordStruct *new_word,
                 char **word, WordStruct **prev_word, int *exist_flg)
{
  for (Node *ptr = dictionary->first; ptr != NULL ; ptr = ptr->next)
    {
      if (strcmp(ptr->data->word, (*word)) == 0)
        {
          new_word = ptr->data;
          if (new_word == (*prev_word))
            {
              add_word_to_probability_list(new_word, new_word);
              // if the same word appears twice in  a row
            }
          else
            {
              add_word_to_probability_list((*prev_word), new_word);
              // if a word already appear so didnt make W.S
            }
          (*prev_word) = ptr->data;
          (*word) = strtok (NULL, " \n\r");
          (*exist_flg) = 1;
          break;
        }
    }
}
/**
 * Read word from the given file. Add every unique word to the dictionary.
 * Also, at every iteration, update the prob_list of the previous word with
 * the value of the current word.
 * @param fp File pointer
 * @param words_to_read Number of words to read from file.
 *                      If value is bigger than the file's word count,
 *                      or if words_to_read == -1 than read entire file.
 * @param dictionary Empty dictionary to fill
 */
void fill_dictionary(FILE *fp, int words_to_read, LinkList *dictionary)
{
  char *buff= (char*)malloc(MAX_SENTENCE_LENGTH);
  char *word;
  WordStruct *prev_word;
  WordStruct *new_word;

  while (fgets(buff, MAX_SENTENCE_LENGTH, fp))
    {
      word = strtok (buff," \n\r");
      while (word != NULL)
        {
          if (words_to_read == dictionary->size)
            {
              free(buff);
              buff = NULL;
              new_word = NULL;
              prev_word = NULL;
              return;
            }
          int exist_flg = 0;
          if (dictionary->first != NULL)
            {
              update_prob_lst (dictionary, new_word, &word,
                               &prev_word, &exist_flg);
            }
          if (exist_flg == 1)
            {
              continue;
            }
          new_word = malloc(sizeof (WordStruct));
          if (new_word == NULL)
            {
              exit(EXIT_FAILURE);
            }
          new_word->word = malloc(strlen(word)+1);
          WordProbability *word_probability = NULL;
          strcpy(new_word->word, word);
          new_word->prob_list = word_probability;
          add(dictionary, new_word);
          if (new_word != dictionary->first->data)
            {
              add_word_to_probability_list(prev_word, new_word);
            }
          prev_word = dictionary->last->data;
          word = strtok (NULL, " \n\r");
        }
    }
  free(buff);
  buff = NULL;
  new_word = NULL;
  prev_word = NULL;
}

/**
 * Free the given dictionary and all of it's content from memory.
 * @param dictionary Dictionary to free
 */
void free_dictionary(LinkList *dictionary)
{

  Node *cur_node = NULL;
  WordStruct *cur_w_s;
  while (dictionary->first != NULL)
    {
      cur_node = dictionary->first;
      cur_w_s = cur_node->data;
      free(cur_w_s->word);
      cur_w_s->word = NULL;
      while (cur_w_s->prob_list != NULL)
        {
          WordProbability *temp = cur_w_s->prob_list->next;
          free(cur_w_s->prob_list);
          cur_w_s->prob_list = temp;
          temp = NULL;
        }
      cur_w_s->prob_list = NULL;
      free(cur_w_s);
      cur_node->data = NULL;
      cur_w_s = NULL;
      dictionary->first = cur_node->next;
      free(cur_node);
      cur_node = NULL;
    }
}

/**
 * check if the user entered 3 or 4 args as expected
 * @param argc number of args
 * @return 0 if as expected, 1 elsewhere
 */
int check_input(int argc)
{
  if (argc != 4 && argc != NUM_OF_ARGS)
    {
      printf(USAGE_ERR);
      return EXIT_FAILURE;
    }
    return SUCCESS;
}
/**
 * @param argc
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 *             3) Path to file
 *             4) Optional - Number of words to read
 */
int main(int argc, char *argv[])
{
  if (check_input(argc) == EXIT_FAILURE)
    {
      return EXIT_FAILURE;
    }
  char* ptr;
  int words_to_read;
  LinkList* word_dict = malloc(sizeof(LinkList));
  *word_dict = (LinkList){NULL, NULL, 0};
  long seed = strtol(argv[1],&ptr,DECIMAL_BASE);
  long num_of_tweets = strtol(argv[2],&ptr,DECIMAL_BASE);
  if (argc != NUM_OF_ARGS)
    {
      words_to_read = -1;
    }
  else
    {
      words_to_read = strtol(argv[4],&ptr,DECIMAL_BASE);
    }
  srand(seed);
  FILE *fp = fopen(argv[3], "r");
  if (fp == NULL)
    {
      printf(FILE_NOT_FOUND_ERR);
      exit(EXIT_FAILURE);
    }
  fill_dictionary(fp, words_to_read, word_dict);
  fclose(fp);

  for (int i=1; i<=num_of_tweets; i++)
    {
      printf("Tweet %d: ", i);
      generate_sentence(word_dict);
    }
  free_dictionary(word_dict);
  free(word_dict);
  word_dict = NULL;
}