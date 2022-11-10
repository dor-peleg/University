from boggle_board_randomizer import *

WORDS_FILE = "boggle_dict.txt"


def load_words_dict(file_path=WORDS_FILE):
    """
    creates a dictionary of all the words in a file
    :param file_path: the path of the file
    :return: the dictionary
    """
    word_dict = {}
    with open(file_path, "r") as f:
        for line in f:
            line = line.strip()
            word_dict[line] = True
    return word_dict


def _check_coordinate(coor_idx, path, path_set):
    """
    checks if path are valid according to the game's rules.
    :param coor_idx: the current coordinates that the function checks.
    :param path: list of tuples
    :param path_set: set that holds the previous coordinates
    :return: True if the path is valid, False otherwise
    """
    #  checks if the coor in board and nor in set
    if path[coor_idx][0] < 0 or path[coor_idx][0] >= BOARD_SIZE or \
            path[coor_idx][1] < 0 or path[coor_idx][1] >= BOARD_SIZE:
        #print(path[coor_idx], "coord out of board")
        return False

    if path[coor_idx] in path_set:
        # print("coord already in set")
        return False

    return True


def is_valid_path(board, path, words):
    """
    gets a path, and checks if the word created by the path on the board is
    in the word list.
    :param board: list of lists of strings
    :param path: list of tuples
    :param words: dictionary of words
    :return: The word if its legal, None otherwise.
    """
    if not path:
        return

    word = ""
    path_set = set()
    if not _check_coordinate(0, path, path_set):
        return None

    path_set.add(path[0])
    word += board[path[0][0]][path[0][1]]

    for coor_idx in range(len(path)-1):
        if not _check_coordinate(coor_idx + 1, path, path_set):
            return None

        moving = [(path[coor_idx][0] + 1, path[coor_idx][1]),
                  (path[coor_idx][0], path[coor_idx][1] + 1),
                  (path[coor_idx][0] - 1, path[coor_idx][1]),
                  (path[coor_idx][0], path[coor_idx][1] - 1),
                  (path[coor_idx][0] + 1, path[coor_idx][1] + 1),
                  (path[coor_idx][0] - 1, path[coor_idx][1] + 1),
                  (path[coor_idx][0] + 1, path[coor_idx][1] - 1),
                  (path[coor_idx][0] - 1, path[coor_idx][1] - 1)]

        if path[coor_idx+1] not in moving:
            # print("coord not a neighbor")
            return None

        word += board[path[coor_idx+1][0]][path[coor_idx+1][1]]

    if word in words:
        return word
    # print('word not in dict')


def find_length_n_words(n, board, words):
    """
    finds all the n-length valid words on the board according to the game's
    rules
    :param n: int
    :param board: list of lists of strings
    :param words: dictionary of words
    :return: List of all the valid words.
    """
    final_lst = []
    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            temp_lst = _helper(n, board, words, [], "", [], i, j)
            if temp_lst:
                final_lst += temp_lst
    return final_lst


def _helper(n, board, words, path, word, final_lst, row_idx, col_idx):
    if n <= 0:
        if (word, path) not in final_lst and word in words:
            final_lst.append((word, path))
        return

    if row_idx >= BOARD_SIZE or col_idx >= BOARD_SIZE or \
            row_idx < 0 or col_idx < 0:
        return

    coord = (row_idx, col_idx)
    if coord in path:
        return

    letter = board[row_idx][col_idx]
    new_path = path + [coord]
    word = word + letter

    _helper(n - 1, board, words, new_path, word, final_lst, row_idx,
            col_idx + 1)
    _helper(n - 1, board, words, new_path, word, final_lst, row_idx + 1,
            col_idx)
    _helper(n - 1, board, words, new_path, word, final_lst, row_idx - 1,
            col_idx)
    _helper(n - 1, board, words, new_path, word, final_lst, row_idx,
            col_idx - 1)
    _helper(n - 1, board, words, new_path, word, final_lst, row_idx + 1,
            col_idx -1)
    _helper(n - 1, board, words, new_path, word, final_lst, row_idx + 1,
            col_idx+1)
    _helper(n - 1, board, words, new_path, word, final_lst, row_idx - 1,
            col_idx + 1)
    _helper(n - 1, board, words, new_path, word, final_lst, row_idx -1,
            col_idx - 1)

    return final_lst
