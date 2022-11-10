"""
# WRITER : Dor Peleg , dor.peleg , 312163421
# EXERCISE : intro2cs1 Ex3 2021
"""


import os
import sys


def read_wordlist(filename):
    """
    The function gets path to a file with words,
    and returns a list of those words.
    :param filename: path to a file (string).
    :return: list of words.
    """
    with open(filename) as f:
        words_lst = f.read().splitlines()
    return words_lst


def read_matrix(filename):
    """
    The function gets path to a file with matrix of letters,
    and returns a list of lists.
    Each list contains letters from a row in the file.
    :param filename: path to a file (string).
    :return: list of lists.
    """
    with open(filename) as f:
        matrix = []
        lines = f.read().splitlines()
        for line in lines:
            row = line.split(",")
            matrix.append(row)
        return matrix


def check_word_in_row(word, row):
    """
    The function gets word and list of letters,
    and checks if all the word's letters are in the list.
    :param word: a word (string)
    :param row: a list of letters (list)
    :return: Boolean value whether the letters of the word appear in the list
    """
    for letter in word:
        if letter not in row:
            return False
    return True


def l_r_check_exact_word(word, row, direction):
    """
    The function checks if the word appears correctly in the line.
    The function checks both left and right.
    :param word: a word (string)
    :param row: list of letters (list)
    :param direction: the letter l or r,
           to search the word to the left or to the right
    :return: How many times the word appears in the row (int)
    """
    exact_word = 0
    for i in range(len(row)):
        if row[i] == word[0]:
            ltrs = 0
            if 'r' in direction:
                for idx, letter in enumerate(word):
                    ltr_idx = idx + i
                    if ltr_idx > len(row) - 1:
                        break
                    if letter != row[ltr_idx]:
                        break
                    else:
                        ltrs += 1
                if ltrs == len(word):
                    exact_word += 1
            if 'l' in direction:
                for idx, letter in enumerate(word):
                    ltr_idx = i - idx
                # the next line prevents the index from getting out of range
                    if ltr_idx < 0:
                        break
                    if letter != row[ltr_idx]:
                        break
                    else:
                        ltrs += 1
                if ltrs == len(word):
                    exact_word += 1
    return exact_word


def u_d_check_exact_word(word, matrix, row_num, direction):
    """
    The function checks if the word appears correctly in the matrix.
    The function checks both up and down.
    :param word: a word (string)
    :param matrix: list of lists of letters (list)
    :param row_num: index of the row number that contains
        the first letter of the word (int)
    :param direction: the letter u or d,
           to search the word upward or downward.
    :return:How many times the word appears in the matrix (int)
    """
    exact_word = 0
    if direction == 'd':
        for i in range(len(matrix[row_num])):
            ltrs = 0
            if matrix[row_num][i] == word[0]:
                for idx, letter in enumerate(word):
                    row_idx = idx + row_num
                # the next line prevents the index from getting out of range
                    if row_idx > len(matrix) - 1:
                        break
                    if letter != matrix[row_idx][i]:
                        break
                    else:
                        ltrs += 1
                    if ltrs == len(word):
                        exact_word += 1
    if direction == 'u':
        for i in range(len(matrix[row_num])):
            ltrs = 0
            if matrix[row_num][i] == word[0]:
                for idx, letter in enumerate(word):
                    row_idx = row_num - idx
                # the next line prevents the index from getting out of range
                    if row_idx < 0:
                        break
                    if letter != matrix[row_idx][i]:
                        break
                    else:
                        ltrs += 1
                    if ltrs == len(word):
                        exact_word += 1

    return exact_word


def wxyz_check_exact_word(word, matrix, row_num, direction):
    """
    The function checks if the word appears correctly in the matrix.
    The function checks in all diagonal directions.
    :param word: a word (string)
    :param matrix: list of lists of letters (list)
    :param row_num: index of the row number that contains
           the first letter of the word (int)
    :param direction: the letter w, x, ,y or z,
           to search the word in which diagonal direction.
    :return:How many times the word appears in the matrix (int)
    """
    exact_word = 0
    for i in range(len(matrix[row_num])):
        ltrs = 0
        if matrix[row_num][i] == word[0]:
            for idx, letter in enumerate(word):
                if direction == 'w':    # r and u
                    row_idx = row_num - idx
                    ltr_idx = i + idx
                # the next line prevents the index from getting out of range
                    if row_idx < 0 or ltr_idx > len(matrix[row_num]) - 1:
                        break
                elif direction == 'x':  # l and u
                    row_idx = row_num - idx
                    ltr_idx = i - idx
                # the next line prevents the index from getting out of range
                    if row_idx < 0 or ltr_idx < 0:
                        break
                elif direction == 'y':  # r and d
                    row_idx = row_num + idx
                    ltr_idx = i + idx
                # the next line prevents the index from getting out of range
                    if row_idx > len(matrix) - 1 or \
                            ltr_idx > len(matrix[row_num]) - 1:
                        break
                elif direction == 'z':  # l and d
                    row_idx = row_num + idx
                    ltr_idx = i - idx
                # the next line prevents the index from getting out of range
                    if row_idx > len(matrix) - 1 or ltr_idx < 0:
                        break
                if letter != matrix[row_idx][ltr_idx]:
                    break
                else:
                    ltrs += 1
                if ltrs == len(word):
                    exact_word += 1
    return exact_word


def find_words(word_list, matrix, directions):
    """
    The function goes through all the search directions
    and all the words from the word list
    and checks for each direction which words are in the matrix.
    :param word_list: a list of words (list)
    :param matrix: a list of list of letters (list)
    :param directions: a string
    :return: a list of all the words that found in the matrix
             and how many times they were found. (list of tuples)
    """
    find_lst = []
    findings = {}
    for direction in set(directions):
        for word in word_list:
            if direction in 'lr':
                for row in matrix:
                    if check_word_in_row(word, row):
                        num_of_appears = l_r_check_exact_word(word,
                                                              row,
                                                              direction)
                        if word not in findings:
                            findings[word] = num_of_appears
                        else:
                            findings[word] += num_of_appears

            else:
                for row_num in range(len(matrix)):
                    if word[0] in matrix[row_num]:
                        if direction in 'ud':
                            num_of_appears = u_d_check_exact_word(word,
                                                                  matrix,
                                                                  row_num,
                                                                  direction)

                        if direction in 'wxyz':
                            num_of_appears = wxyz_check_exact_word(word,
                                                                   matrix,
                                                                   row_num,
                                                                   direction)
                        if word not in findings:
                            findings[word] = num_of_appears
                        else:
                            findings[word] += num_of_appears

    for word in findings:
        if findings[word] != 0:
            word_count = (word, findings[word])
            find_lst.append(word_count)
    return find_lst


def write_output(results, filename):
    """
    The function gets a list of words found in the matrix
    and the number of times they are found and prints them into a file.
    :param results: list of tuples of the words that found
           and how many times they were found
    :param filename: the path of the file that the function prints to.
    """
    with open(filename, 'w') as f:
        for word, count in results:
            f.write(f"{word},{count}\n")


def check_input():
    """
    The function checks that the input provided to the program is correct
    in order for the program to run properly.
    """
    if len(sys.argv) != 5:
        print("the program gets exactly 4 arguments")
        exit()
    if not os.path.exists(sys.argv[1]):
        print("the word list path does not exist!")
        exit()
    if not os.path.exists(sys.argv[2]):
        print("the matrix does not exist!")
        exit()
    for direction in sys.argv[4]:
        if direction not in 'udlrwxyz':
            print("You entered illegal search direction!")
            exit()


def main():
    """
    the main program.
    """
    check_input()
    word_list = read_wordlist(sys.argv[1])
    matrix = read_matrix(sys.argv[2])
    found_words = find_words(word_list, matrix, sys.argv[4])
    write_output(found_words, sys.argv[3])


if __name__ == "__main__":
    main()
