from boggle_gui import BoggleGUI
from boggle_logic import BoggleLogic
from ex12_utils import load_words_dict
import boggle_board_randomizer

WORDS_FILE = "boggle_dict.txt"


class BoggleController:
    """
    This class controls the Boggle game, connecting between the
    GUI part and the logic part
    """
    def __init__(self):
        self._board = boggle_board_randomizer.randomize_board()
        # print(self._board)
        self._word_dict = load_words_dict(WORDS_FILE)
        self._gui = BoggleGUI(self._board)
        self._model = BoggleLogic(self._board, self._word_dict)

        self._assign_btn_command()

        _check_btn_command = self._create_check_btn_command()
        self._gui.words_related.set_check_btn_cmd(_check_btn_command)

        yes_func, no_func = self._create_play_again_commands()
        self._gui.set_play_again_btns_command(yes_func, no_func)

        _exit_command = self._create_exit_btn_command()
        self._gui.set_exit_btn_command(_exit_command)

    def _assign_btn_command(self):
        """
        assign each cube button the matching command
        :return:None
        """
        for cube in self._gui.cubes.get_cubes_info():
            cube_btn_command = self._create_button_command(cube)
            self._gui.cubes.set_button_command(cube, cube_btn_command)

    def _create_button_command(self, cube_info):
        """
        creates a function to assign the cubes buttons as a command
        :param cube_info: the letter and coordinate of the relevant cube button
        :return: the command function
        """
        def func():
            """
            the actions that occur when a cube button is pressed
            :return:None
            """
            # print("button_pressed: ", cube_info)
            self._gui.cubes.button_pressed(cube_info)
            self._model.set_letters_and_coords(cube_info)
            partial_word = self._model.get_partial_word()
            self._gui.words_related.update_word_label(partial_word)

        return func

    def _create_check_btn_command(self):
        """
        creates a function to assign the check button as a command
        :return: the command function
        """
        def func():
            """
            the actions that occur when the check button is pressed.
            :return: None
            """
            word_path = self._model.get_partial_path()
            # print("checking word")
            # print("word path", word_path)
            # print("get part path", word_path)
            if self._model.is_valid_word(word_path):
                # print("valid word")
                word_lst = self._model.get_words_lst()
                self._gui.words_related.set_word_lst_lbl(word_lst)
                self._model.set_score(word_lst[-1])
                score = self._model.get_score()
                self._gui.others.set_score_label(score)

            self._model.clear_word_and_path()
            self._gui.cubes.return_button_to_normal()
            # self.word_path = self._model.get_partial_path()
            self._gui.words_related.clear_word_label()
        return func

    def _create_play_again_commands(self):
        """
        creates functions to assign the yes and no buttons as a command
        :return: the functions
        """
        def yes_func():
            """
            the actions that occur when the yes button is pressed.
            :return: None
            """
            self._board = boggle_board_randomizer.randomize_board()
            self._model.reset_game_logic(self._board)
            self._gui.reset_game_gui(self._board)
            self._assign_btn_command()
            new_record = self._model.get_record()
            # print(new_record)
            self._gui.others.set_record_lbl(new_record)

        def no_func():
            """
            the actions that occur when the no button is pressed.
            :return: None
            """
            self._gui.exit_game()
            exit()

        return yes_func, no_func

    def _create_exit_btn_command(self):
        """
        creates a functions to assign the exit buttons as a command
        :return: the function
        """
        def exit_func():
            """
            the actions that occur when the exit button is pressed.
            :return: None
            """
            self._gui.exit_game()
            exit()

        return exit_func

    def run(self) -> None:
        """
        start the GUI mainloop.
        :return: None
        """
        self._gui.run()


if __name__ == "__main__":
    BoggleController().run()
