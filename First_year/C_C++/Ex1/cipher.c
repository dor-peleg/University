//
// Created by dorp1 on 06/04/2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_OF_LETTERS 26
#define CAP_A_VALUE 65
#define CAP_Z_VALUE 90
#define SMALL_A_VALUE 97
#define SMALL_Z_VALUE 122
#define MAX_STR_LEN 100000
#define CODE_NUM_OF_ARGS 5
#define CHECK_NUM_OF_ARGS 4

int convert (int k, int letter)
/*
 * The function gets an int and a letter (char)
 * and returns new char with value of the letter according to the ascii table
 * after adding k to it.
 */
{
  if (letter >= SMALL_A_VALUE && letter <= SMALL_Z_VALUE)
    {
      letter = letter + k;
      if (letter < SMALL_A_VALUE)
        {
          letter = letter + NUM_OF_LETTERS;
        }

      if (letter > SMALL_Z_VALUE)
        {
          letter = letter - NUM_OF_LETTERS;
        }
    }
  else if (letter >= CAP_A_VALUE && letter <= CAP_Z_VALUE)
    {
      letter = letter + k;
      if (letter < CAP_A_VALUE)
        {
          letter = letter + NUM_OF_LETTERS;
        }
      if (letter > CAP_Z_VALUE)
        {
          letter = letter - NUM_OF_LETTERS;
        }
    }
  return (char)letter;
}

int encode(int k, char *inPath, char *outPath)
/*
 * The function gets an int, and paths to two files,
 * and writing to the second file the text from the first file
 * after indentation of all the letters.
 */
{
  char msg[MAX_STR_LEN];
  int x;
  FILE *f_in = fopen(inPath, "r");
  FILE *f_out = fopen(outPath, "w");
  if (k >= NUM_OF_LETTERS || k <= -NUM_OF_LETTERS)
    {
      k = k % NUM_OF_LETTERS;
    }
  while (fgets(msg, MAX_STR_LEN, f_in))
    {
      for (int i = 0; msg[i] != '\0'; i++)
        {
          x = convert (k, msg[i]);
          msg[i] = (char)x;
        }
      fprintf(f_out, "%s", msg);
    }
  if (f_in != NULL)
    {
      fclose(f_in);
    }
  if (f_out != NULL)
    {
      fclose(f_out);
    }
  return EXIT_SUCCESS;
}


int find_k(char *txt_1, char *txt_2)
/*
 * the function gets to files paths and go over the text in them.
 * when the loop finds a letter in the first file,
 * if there is a letter in the same location in the second file,
 * the function returns the difference between the letters
 * according to the ascii table.
 * if there is no letter in the same location in the second file,
 * the function return -1.
 */
{
  FILE *f_txt_1 = fopen(txt_1, "r");
  FILE *f_txt_2 = fopen(txt_2, "r");
  int k=-1;
  char msg1[MAX_STR_LEN], msg2[MAX_STR_LEN];
  while (k==-1)
    {
      fgets (msg1, MAX_STR_LEN, f_txt_1);
      fgets (msg2, MAX_STR_LEN, f_txt_2);
      for (int i = 0; msg1[i] != '\0'; i++)
        {
          if (isalpha(msg1[i]) != 0)
            {
              if (msg1[i] >= CAP_A_VALUE && msg1[i] <= CAP_Z_VALUE)
                {
                  if (msg2[i] < CAP_A_VALUE || msg2[i] > CAP_Z_VALUE)
                    {
                      fclose(f_txt_1);
                      fclose(f_txt_2);
                      return k;
                    }
                }
              if (msg1[i] >= SMALL_A_VALUE && msg1[i] <= SMALL_Z_VALUE)
                {
                  if (msg2[i] < SMALL_A_VALUE || msg2[i] > SMALL_Z_VALUE)
                    {
                      fclose(f_txt_1);
                      fclose(f_txt_2);
                      return k;
                    }
                }
              k = msg2[i] - msg1[i];
              if (k < 0)
                {
                  k = NUM_OF_LETTERS + k;
                }
              break;
            }
        }
      if (feof(f_txt_1) && k == -1)
        {
          k = 0;
        }
    }
  if (f_txt_1 != NULL)
    {
      fclose(f_txt_1);
    }
  if (f_txt_2 != NULL)
    {
      fclose(f_txt_2);
    }
  return k;
}


int check(char *txt_1, char *txt_2)
/*
 * The function gets two files paths,
 * and checks whether there is valid encryption between the two files.
 * if the encryption is valid, the function prints the indentation value.
 * if the encryption is not valid, the function informs about it.
 */
{
  int k = 0, valid = 0;
  char msg1[MAX_STR_LEN];
  char msg2[MAX_STR_LEN];

  k = find_k(txt_1, txt_2);
  if (k == -1)
    {
      printf ("Invalid encrypting\n");
      return EXIT_SUCCESS;
    }

  FILE *f_txt_1 = fopen(txt_1, "r");
  FILE *f_txt_2 = fopen(txt_2, "r");


  while (fgets(msg1, MAX_STR_LEN, f_txt_1) && valid == 0)

    {
      fgets(msg2, MAX_STR_LEN, f_txt_2);
      if (strlen(msg1) != strlen(msg2))
        {
          printf ("Invalid encrypting\n");
          valid = -1;
          break;
        }
      for (int i = 0; msg1[i] != '\0'; i++)
        {
          if ((isalpha(msg1[i]) != 0) && (isalpha(msg2[i]) != 0))
            {
              if (convert(k, msg1[i]) != msg2[i])
                {
                  printf ("Invalid encrypting\n");
                  valid = -1;
                  break;
                }
            }
          else if (
              ((isalpha(msg1[i]) != 0) &&(isalpha(msg2[i]) == 0)) ||
              ((isalpha(msg1[i]) == 0) && (isalpha(msg2[i]) != 0)))
            {
              printf ("Invalid encrypting\n");
              valid = -1;
              break;
            }
          else if ((isalpha(msg1[i]) == 0) && (isalpha(msg2[i]) == 0))
            {
              if (msg1[i] != msg2[i])
                {
                  printf ("Invalid encrypting\n");
                  valid = -1;
                  break;
                }
            }
        }
    }
  if (fgets(msg2, MAX_STR_LEN, f_txt_2) && valid == 0)
    {
      printf ("Invalid encrypting\n");
      valid = -1;
    }
  if (f_txt_1 != NULL)
    {
      fclose(f_txt_1);
    }
  if (f_txt_2 != NULL)
    {
      fclose(f_txt_2);
    }
  if (valid == 0)
    {
      printf("Valid encrypting with k = %d\n", k);
    }
  return EXIT_SUCCESS;
}


int check_input(int num_of_args, char *argv[])
/*
 * The function checks whether the call to the program was with arguments as
 * expected, and checks that the files exist and proper.
 */
{
  if (num_of_args == 1)
    {
      fprintf(stderr, "The given command is invalid\n");
      return EXIT_FAILURE;
    }
  if ((strcmp(argv[1], "encode") != 0) && (strcmp(argv[1], "decode") != 0) &&
      (strcmp(argv[1], "check") != 0))
    {
      fprintf(stderr, "The given command is invalid\n");
      return EXIT_FAILURE;
    }
  else if ((strcmp(argv[1], "encode") == 0) ||
           (strcmp(argv[1], "decode") == 0))
    {
      if (num_of_args != CODE_NUM_OF_ARGS)
        {
          fprintf(stderr, "Usage: cipher <encode|decode> <k>"
                          " <source path file> <output path file>\n");
          return EXIT_FAILURE;
        }
      FILE *f_1 = fopen(argv[3], "r");
      FILE *f_2 = fopen(argv[4], "w");
      if (f_1 != NULL)
        {
          fclose(f_1);
        }
      if (f_2 != NULL)
        {
          fclose(f_2);
        }
      if ((f_1 == NULL) || (f_2 == NULL))
        {
          fprintf (stderr, "The given file is invalid\n");
          return EXIT_FAILURE;
        }
    }
  else if (strcmp(argv[1], "check") == 0)
    {
      if (num_of_args != CHECK_NUM_OF_ARGS)
        {
          fprintf (stderr, "Usage: cipher <check>"
                           " <source path file> <output path file>\n");
          return EXIT_FAILURE;
        }
      FILE *f_1 = fopen(argv[2], "r");
      FILE *f_2 = fopen(argv[3], "r");
      if (f_1 != NULL)
        {
          fclose(f_1);
        }
      if (f_2 != NULL)
        {
          fclose(f_2);
        }
      if ((f_1 == NULL) || (f_2 == NULL))
        {
          fprintf (stderr, "The given file is invalid\n");
          return EXIT_FAILURE;
        }
    }
  return EXIT_SUCCESS;
}

int main (int argc, char *argv[])
/*
 * The main function of the program,
 * call the other function according to the provided arguments
 */
{
  int input_result;
  input_result = check_input(argc, argv);
  if (input_result == 1)
    {
      return EXIT_FAILURE;
    }
  if (strcmp(argv[1], "encode") == 0)
    {
      {
        if (encode(atoi(argv[2]), argv[3],
                   argv[4]) == 0)
          {
            return EXIT_SUCCESS;
          }
      }
    }
  else if (strcmp(argv[1], "decode") == 0)
    {
      {
        if (encode(-atoi(argv[2]), argv[3],
                   argv[4]) == 0)
          {
            return EXIT_SUCCESS;
          }
      }
    }
  else if (strcmp(argv[1], "check") == 0)
    {
      {
        if (check(argv[2], argv[3]) == 0)
          {
            return EXIT_SUCCESS;
          }

      }
    }
  return EXIT_FAILURE;
}