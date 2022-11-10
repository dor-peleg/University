# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>

#define SUCCESS 0
#define FAILURE 1
#define MAX_FIELD_LEN 20
#define ID_LEN 10
#define MAX_GRADE 100
#define MIN_GRADE 0
#define MIN_AGE 18
#define MAX_AGE 120
#define MAX_INPUT_LEN 60
#define DECIMAL_BASE 10

typedef struct Student
/*
 * Structs that defines the student info
 */
{
  long int id;
  int grade;
  int age;

}Student;

long check_if_num (const char *input)
/***
 * the function check if the char array is a number
 * @param input - pointer to char array
 * @return - 0 if the char array is a number, 1 else
 */
{
      for (int i=0; input[i]!='\n' && input[i]!='\0' ; i++)
        {
          if (isdigit(input[i]) == 0)
            {
              return FAILURE;
            }
        }
  return SUCCESS;
}

int check_stu_info(char *input)
/***
 * the function checks if the student's ID, garde and age are valid
 * according to the guidelines.
 * @param input pointer to char array with all the student's info
 * @return 0 if the info is valid, 1 else.
 */
{
  char id[MAX_FIELD_LEN], grade[MAX_FIELD_LEN], age[MAX_FIELD_LEN];
  char *input_field;
  char *temp;

  input_field = strtok (input, ",");
  strcpy (id, input_field);
  input_field = strtok(NULL, ",");
  strcpy (grade, input_field);
  input_field = strtok(NULL, ",");
  strcpy (age, input_field);

  if (check_if_num(id) != SUCCESS
  || id[0] == '0' || strlen(id) != ID_LEN)
    {
      printf ("ERROR: Id must have 10 digits and can not start with 0.\n");
      return FAILURE;
    }
  if (check_if_num(grade) != SUCCESS
  || (MIN_GRADE > strtol(grade, &temp, DECIMAL_BASE))
  || (MAX_GRADE < strtol(grade, &temp, DECIMAL_BASE)))
    {
      fprintf(stdout, "ERROR: grade should be an integer between 0 and 100\n");
      return FAILURE;
    }
  if (check_if_num(age) != SUCCESS
  || (MIN_AGE > strtol(age, &temp, DECIMAL_BASE))
  || (MAX_AGE < strtol(age, &temp, DECIMAL_BASE)))
    {
      printf("ERROR: age should be an integer between 18 and 120\n");
      return FAILURE;
    }
  return SUCCESS;
}

Student **get_input()
/***
 * the function ask the user for number of students and their info,
 * creates Student Structs with the info and allocates memory for the students
 * @return pointer to pointers to the start and end of the array of the
 * students struct, NULL if the memory allocation failed
 */
{
  char num_of_students_input[MAX_INPUT_LEN];
  long num_of_students = -1;
  int counter = 0;
  char student[MAX_INPUT_LEN];
  char *temp_ptr;
  Student *student_db;

  while (num_of_students == -1)
    {
      printf ("Enter number of students. Then enter\n");
      fgets(num_of_students_input, MAX_INPUT_LEN, stdin);
      if (check_if_num(num_of_students_input)!= 0
      || strcmp(num_of_students_input, "\n")==0
      || strtol(num_of_students_input, &temp_ptr, DECIMAL_BASE) ==0)
        {
          printf("ERROR: Please enter int > 0\n");
          continue;
        }
      num_of_students = strtol(num_of_students_input, &temp_ptr,
                               DECIMAL_BASE);
    }
  student_db = (Student *)calloc(num_of_students, sizeof(Student));
  if (student_db == NULL)
    {
      return NULL;
    }
  while (counter < num_of_students)
    {
      printf ("Enter student info. Then enter\n");
      fgets (student, MAX_INPUT_LEN, stdin);
      Student stu;
      if (check_stu_info (student) == FAILURE)
        {
          continue;
        }
      long stu_id = strtol (student, &temp_ptr, DECIMAL_BASE);
      stu.id = stu_id;
      int stu_grade = (int) strtol (temp_ptr + 1, &temp_ptr, DECIMAL_BASE);
      stu.grade = stu_grade;
      int stu_age = (int) strtol (temp_ptr + 1, &temp_ptr, DECIMAL_BASE);
      stu.age = (int) stu_age;
      student_db[counter] = stu;
      counter += 1;
    }
  Student **db_ptrs=malloc(sizeof (Student)*2);
  if (db_ptrs == NULL)
    {
      return NULL;
    }
  db_ptrs[0] = student_db;
  db_ptrs[1] = student_db+num_of_students;
  return db_ptrs;
}

void best_student(Student *start, Student *end)
/***
 * The function goes over the array and finds the best student.
 * @param start - pointer to the array's start
 * @param end - pointer to the array's end
 */
{
  Student best_stu;
  best_stu.id=start->id;
  best_stu.grade=start->grade;
  best_stu.age=start->age;
  double avg, best_avg;

  for (Student *i=start; i != end; ++i)
    {
      avg = (double)i->grade/i->age;
      best_avg=((double)best_stu.grade/best_stu.age);
      if (avg > best_avg)
        {
          best_stu.id=i->id;
          best_stu.grade=i->grade;
          best_stu.age=i->age;
        }
    }
  printf("best student info is: %ld,%d,%d\n",
         best_stu.id, best_stu.grade, best_stu.age);
}

void swap(Student *ptr_1, Student *ptr_2)
/***
 * the function gets tow pointers and swap their values
 * @param ptr_1 - 1st pointer
 * @param ptr_2 - 2nd pointer
 */
{
  Student temp = *ptr_1;
  *ptr_1 = *ptr_2;
  *ptr_2 = temp;
}

void print_db(Student *start, Student *end)
/***
 * the function prints all the information of all the students in the array.
 * @param start - pointer to the array's start
 * @param end - pointer to the array's end
 */
{
  for (Student *k=start; k != end; ++k)
    {
      printf("%ld,%d,%d\n",k->id,k->grade,k->age);
    }
}

void bubble_sort(Student *start, Student *end)
/***
 * the function sorts the students by grade using 'Bubble sort' algorithm
 * @param start - pointer to the array's start
 * @param end - pointer to the array's end
 */
{
    Student *new_end= end;
    for (Student *i=start; i != end; ++i)
      {
        for (Student *j=start; j != new_end-1; ++j)
          {
            if(j->grade > (j+1)->grade)
              {
                swap(j, j+1);
              }
          }
        new_end = new_end-1;
      }
}

Student *partition(Student *start, Student *end)
/***
 * helper function to the quick-sort,
 * Rearranges the array so that all the values smaller than the pivot
 * are on its left and all the values larger than it are on its right
 * @param start - pointer to the array's start
 * @param end - pointer to the array's end
 * @return - pointer to the pivot
 */
{
  int pivot = (end-1)->age;
  Student *l = start-1;
  Student *h = start;
  for (; h != end-1; h++)
    {
      if (h->age < pivot)
        {
          l++;
          swap(h, l);
        }
    }
  swap(l+1, end-1);
  return l+1;
}

void quick_sort(Student *start, Student *end)
/***
 * the function sorts the students by age using 'Quick sort' algorithm
 * @param start - pointer to the array's start
 * @param end - pointer to the array's end
 */
{
  if (start < end)
    {
      Student *pivot = partition(start, end);
      quick_sort(start, pivot);
      quick_sort(pivot+1, end);
    }
}



int main(int argc,char **argv)
/***
 * the main function of the program
 */
{
  if (argc != 2)
    {
      printf("USAGE: enter valid command('best', 'bubble' or 'quick')\n");
      exit(EXIT_FAILURE);
    }
  if (strcmp(argv[1], "best")!=0
  && strcmp(argv[1], "bubble")!=0
  && strcmp(argv[1], "quick")!=0)
    {
      printf("USAGE: enter valid command('best', 'bubble' or 'quick')\n");
      return EXIT_FAILURE;
    }
  Student **student_db =get_input();
  if (student_db == NULL)
    {
      return EXIT_FAILURE;
    }
  if (strcmp(argv[1], "best") == 0)
    {
      best_student(student_db[0], student_db[1]);
    }
  else if (strcmp(argv[1], "bubble") == 0)
    {
      bubble_sort(student_db[0], student_db[1]);
      print_db(student_db[0], student_db[1]);
    }
  else if((strcmp(argv[1], "quick") == 0))
    {
      quick_sort(student_db[0], student_db[1]);
      print_db(student_db[0], student_db[1]);
    }
  free(student_db[0]);
  student_db[0] = NULL;
  student_db[1] = NULL;
  free(student_db);
  student_db = NULL;
  return 0;
}