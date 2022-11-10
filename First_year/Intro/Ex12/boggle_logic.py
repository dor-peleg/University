from ex12_utils import is_valid_path


class BoggleLogic:
    """
    a class that manages all the logical part of the game.
    """
    def __init__(self, board, word_dict):
        self._word_dict = word_dict
        self._words_lst = []
        self._temp_word = ""
        self._temp_coords = []
        self._score = 0
        self._record = 0
        self._board = board

    def set_letters_and_coords(self, cube_info):
        """
        add letter and coordinates according to the player's action.
        :param cube_info: letter and coordinate of the cube that the player
        chose
        :return: None
        """
        self._temp_word += cube_info[0]
        self._temp_coords.append(cube_info[1])

    def clear_word_and_path(self):
        """
        clear the partial word and path
        :return: None
        """
        self._temp_word = ""
        self._temp_coords = []

    def is_valid_word(self, word_path):
        """
        checks if a word is valid according to the game's rules.
        :param word_path: list of coordinates
        :return: True if the word is valid, False otherwise.
        """
        # print("is_valid", word_path)
        word = is_valid_path(self._board, word_path, self._word_dict)
        # print("word: ", word)
        if word and word not in self._words_lst:
            self._words_lst.append(word)
            # print("True")
            return True

        # print("False")
        return False

    def set_score(self, word):
        """
        add score according to the word length
        :param word: a word
        :return: None
        """
        self._score += len(word) ** 2

    def get_score(self):
        """
        return the player's current score
        :return: int - the score.
        """
        return self._score
    #
    # def get_board(self):
    #     return self._board

    def get_words_lst(self):
        """
        returns a list of the current valid word list.
        :return: list of valid words the player found.
        """
        return self._words_lst

    def get_partial_word(self):
        """
        return the partial word the player found.
        :return: string
        """
        return self._temp_word

    def get_partial_path(self):
        """
        return the partial path of the word the player found.
        :return: list of coordinates
        """
        return self._temp_coords

    def get_record(self):
        """
        return the record of the player
        :return: int
        """
        return self._record

    def _set_new_board(self, new_board):
        """
        update the board to a new one.
        :param new_board: new board
        :return: None
        """
        self._board = new_board

    def _reset_word_lst(self):
        """
        clears the world list
        :return: None
        """
        self._words_lst = []

    def _reset_score(self):
        """
        reset the player's score to 0
        :return: None
        """
        self._score = 0

    def _set_record(self):
        """
        check if the score of the current game is higher then the previous
        games, if yes, change the record to the new highest score
        :return: None
        """
        if self._score > self._record:
            self._record = self._score

    def reset_game_logic(self, new_board):
        """
        the actions that occur when the player wants to start a new game.
        :param new_board: board of the new game
        :return: None
        """
        self._set_record()
        self._set_new_board(new_board)
        self.clear_word_and_path()
        self._reset_word_lst()
        self._reset_score()
