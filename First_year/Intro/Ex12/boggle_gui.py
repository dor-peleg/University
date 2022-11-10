import tkinter as tk
from countdown_clock import Countdown
from tkinter import messagebox

BUTTON_COLOR = "snow"
BG_COLOR = 'AntiqueWhite2'
INSTRUCTIONS = "GOAL: to find as many words as you can\n" \
               "\nYou will have three minutes find as many words as you can " \
               "in the grid, " \
               "according to the following rules:\n"\
               "- The letters must be adjoining in a 'chain'.\n" \
               "  (horizontally, vertically, or diagonally.)\n" \
               "- Words must contain at least three letters.\n" \
               "- No cube may be used more than once within a single word.\n"\
               "The score for each word is calculated according to: " \
               "(length of the word)^2.\n" \
               "\nGOOD LUCK!"\



class BoggleGUI:
    """
    the main class of the GUI, combine all the parts of the game's graphic part
    """
    def __init__(self, board):
        self.board = board
        root = tk.Tk()
        root.title("Boggle")
        root.resizable(False, False)
        self._main_window = root
        self._main_window.geometry("800x500")

        self._outer_frame = tk.Frame(root, bg=BG_COLOR,
                                     highlightbackground='AntiqueWhite3',
                                     highlightthickness=5, width=1, height=1)

        self._welcome_label = tk.Label(self._outer_frame,
                                       text="Welcome to Boggle!\npress 'start'"
                                       , font=("Verdana 19 bold", 33),
                                       bg=BG_COLOR)
        self._exit_button = tk.Button(self._outer_frame, text="Exit",
                                      font=("Courier", 12), bg=BUTTON_COLOR)
        self._start_button = tk.Button(self._outer_frame, text="Start!",
                                       font=("Courier bold", 16),
                                       bg=BUTTON_COLOR,
                                       command=self._start_game)

        self.cubes = Cubes(self._main_window, self._outer_frame, self.board)
        self.cubes.init_game()

        self._clock = Countdown(self._main_window)
        self.words_related = Words(self._outer_frame)
        self.others = Others(self._outer_frame, self._clock)

        self._game_over_set()
        self._obj_place()

    def run(self):
        """
        starts the mainloop
        :return: None
        """
        self._main_window.mainloop()

    def _obj_place(self):
        """
        place objects on the main window.
        :return: None
        """
        self._outer_frame.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        self._exit_button.place(x=10, y=450)
        self._start_button.place(x=250, y=320)
        self._welcome_label.place(x=70, y=200)
        self.others.place_when_init()

    def _start_game(self):
        """
        the actions that occur when the start button pressed.
        makes the game begin.
        :return: None
        """
        self._start_button.place_forget()
        self._welcome_label.place_forget()
        self.cubes.start_game()
        self._clock.countdown()
        self._check_time()
        self.others.place_when_start()

    def _set_new_board(self, new_board):
        """
        change the self._board to a new board
        :param new_board: new board
        :return: None
        """
        self.board = new_board

    def _set_clock(self):
        """
        creates a Countdown object
        :return: None
        """
        self._clock = Countdown(self._main_window)

    def _check_time(self):
        """
        checks if the time is not over, and change the clock accordingly.
        when the time is over, calls the end_game function.
        :return: None
        """
        timer_on = self._clock.get_timer()
        if timer_on:
            time_left = self._clock.get_time_left()
            self.others.set_clock_lbl(time_left)
            self._outer_frame.after(10, self._check_time)
        else:
            self._end_game()

    def _end_game(self):
        """
        the actions that occur when the time is up and the game is over.
        :return: None
        """
        self.cubes.end_game_cubes()
        self.words_related.end_game_words()
        self.others.end_game_others()
        self._place_game_over_set()

    def _game_over_set(self):
        """
        creates label and buttons that appear when the game is over.
        :return: None
        """
        self.play_again_label = tk.Label(self._outer_frame,
                                         font=("Verdana 19 bold", 25),
                                         bg="AntiqueWhite2")
        self.play_again_btn_yes = tk.Button(self._outer_frame, text="Yes!",
                                            font=("Courier Bold", 12),
                                            bg="green")
        self.play_again_btn_no = tk.Button(self._outer_frame, text="No!",
                                           font=("Courier Bold", 12), bg="red")

    def _place_game_over_set(self):
        """
        place the label and buttons that appear when the game is over.
        :return: None
        """
        score = self.others.get_score_lbl_txt()
        self.play_again_label["text"] = f"Game over!\nYou got {score} points!"\
                                        f"\nDo you want to play again?" \

        self.play_again_label.place(x=70, y=220)
        self.play_again_btn_yes.place(x=200, y=350)
        self.play_again_btn_no.place(x=280, y=350)

    def _unplace_game_over_set(self):
        """
        remove the label and buttons that appear when the game is over
        if the user want to play again.
        :return: None
        """
        self.play_again_label.place_forget()
        self.play_again_btn_yes.place_forget()
        self.play_again_btn_no.place_forget()

    def set_play_again_btns_command(self, yes_command, no_command):
        """
        sets the command of the yes and no buttons.
        :param yes_command: a function that begins a new game
        :param no_command: a function that exit the game
        :return: None
        """
        self.play_again_btn_yes["command"] = yes_command
        self.play_again_btn_no["command"] = no_command

    def set_exit_btn_command(self, exit_command):
        """
        sets the command of the exit button.
        :param exit_command: a function that exit the game
        :return: None
        """
        self._exit_button["command"] = exit_command

    def reset_game_gui(self, new_board):
        """
        actions that occur when the user wants to start a new game
        :param new_board: a board for the new game
        :return: None
        """
        self._set_new_board(new_board)
        self.cubes.reset_game_cubes(new_board)
        self.others.reset_game_others()
        self.words_related.reset_game()
        self._set_clock()

        self._unplace_game_over_set()
        self._start_button.place(x=250, y=350)
        self._welcome_label.place(x=70, y=220)

    def exit_game(self):
        """
        closes the main window
        :return:
        """
        self._main_window.destroy()


class Cubes:
    """
    a class that manages the cubes buttons.
    """
    def __init__(self, root, frame, board):
        self._main_window = root
        self._outer_frame = frame
        self._board = board
        self._cubes = {}
        self._cubes_frame = tk.Frame(self._outer_frame, background=BG_COLOR)

    def init_game(self):
        """
        actions that occur when the game is initializing.
        :return:
        """
        self._set_cubes()

    def start_game(self):
        """
        actions that occur when the game is starting.
        :return:
        """
        self._place_btn_grid()

    def _set_cubes(self):
        """
        creates a button for each letter according to the board and place
        them in 4X4 grid.
        :return: None
        """
        for i in range(len(self._board)):
            for j in range(len(self._board)):
                button = tk.Button(self._cubes_frame, height=2, width=3,
                                   text=self._board[i][j],
                                   font="Verdana 19 bold", bg="snow")
                button.grid(row=i, column=j, padx=2, pady=2)
                self._cubes[(self._board[i][j], (i, j))] = button
        # print(self._cubes)

    def _place_btn_grid(self):
        """
        places the cubes buttons grid on the main window
        :return: None
        """
        self._cubes_frame.place(x=230, y=130)

    def _set_new_board(self, new_board):
        """
        change the self._board to a new board
        :param new_board: new board
        :return: None
        """
        self._board = new_board

    def set_button_command(self, cube, action):
        """
        sets the command of the cube's buttons
        :param cube: cube info (letter and coordinate)
        :param action: function that happened when the cube button is pressed
        :return: None
        """
        # print (cube, action)
        self._cubes[cube].configure(command=action)

    def end_game_cubes(self):
        """
        actions that occur when the game is over.
        :return: None
        """
        self._cubes_frame.place_forget()

    def button_pressed(self, button):
        """
        actions that occur when a cube button is pressed
        :param button: a cube info (letter and coordinate)
        :return: None
        """
        self._cubes[button]["bg"] = 'AntiqueWhite3'
        self._cubes[button]["state"] = 'disabled'

    def get_cubes_info(self):
        """
        return the info (letter and coordinate) of all the cubes.
        :return: the cube's info
        """
        return list(self._cubes.keys())

    def _get_cubes(self):
        """
        getter for the cubes dictionary
        :return: the cubes dictionary
        """
        return self._cubes

    def return_button_to_normal(self):
        """
        returns the pressed buttons to normal state after the check button
        is pressed
        :return: None
        """
        for button in self._get_cubes():
            self._cubes[button]["bg"] = 'snow'
            self._cubes[button]["state"] = 'normal'

    def reset_game_cubes(self, new_board):
        """
        actions that occur when the player want to start a new game
        :param new_board: board for the new game
        :return: None
        """
        self._cubes = {}
        self._set_new_board(new_board)
        self._set_cubes()


class Words:
    """
    a class that manage the label and buttons that related to the words
    """
    def __init__(self, frame):
        self._frame = frame
        self._word_lst = []
        self._word_lst_frame = tk.Frame(self._frame, height=350,
                                        width=150, bg=BUTTON_COLOR, bd=2,
                                        relief="groove")
        self._word_list_label = tk.Label(self._frame, bg=BUTTON_COLOR,
                                         justify="left")
        self._display_current_word = tk.Label(self._frame, bg=BG_COLOR,
                                              font=("Courier", 20))
        self._check_button = tk.Button(self._frame, text="check",
                                       font=("Courier", 16), bg=BUTTON_COLOR)
        self._obj_place()

    def _obj_place(self):
        """
        place the objects on the main window.
        :return: None
        """
        self._word_lst_frame.place(x=620, y=133)
        self._word_list_label.place(x=625, y=135)
        self._display_current_word.place(x=230, y=80)
        self._check_button.place(x=685, y=83)

    def set_check_btn_cmd(self, command):
        """
        set the check button command
        :param command: function that happened when the check button is pressed
        :return: None
        """
        self._check_button["command"] = command

    def set_word_lst_lbl(self, word_lst):
        """
        sets the word list label
        :param word_lst: a list of all the valid words the player found
        :return: None
        """
        self._word_list_label["text"] = "\n".join(word_lst)

    def clear_word_label(self):
        """
        clears the letters that the players chose.
        :return: None
        """
        self._display_current_word["text"] = ""

    def update_word_label(self, word):
        """
        adds the letters the player chose
        :param word:
        :return: None
        """
        self._display_current_word["text"] = word

    def end_game_words(self):
        """
        actions that occur when the game is over
        :return: None
        """
        self._check_button["state"] = ["disabled"]
        self.clear_word_label()

    def reset_game(self):
        """
        actions that occur when the player want to start a new game
        :return: None
        """
        self._check_button["state"] = 'normal'
        self.set_word_lst_lbl([])


class Others:
    """
    a class that manage the timer label, score and record labels and the
    info button.
    """
    def __init__(self, frame, clock_obj):
        self._frame = frame
        self._clock = clock_obj
        self._boggle_label = tk.Label(self._frame, text="Boggle",
                                      font=("Courier bold", 35), bg=BG_COLOR)
        self._timer_label = tk.Label(self._frame, text="03:00:000",
                                     font=("Courier", 20), bg=BG_COLOR)
        self._score_title_lbl = tk.Label(self._frame, text="Score: ",
                                         font=("Courier", 20), bg=BG_COLOR)
        self._score_lbl = tk.Label(self._frame, text="0",
                                   bg=BG_COLOR, font=("Courier", 20))
        self._record_title_lbl = tk.Label(self._frame, text="Record: ",
                                          font=("Courier", 17), bg=BG_COLOR)
        self._record_lbl = tk.Label(self._frame, text="0",
                                    bg=BG_COLOR, font=("Courier", 17))
        self._info_btn = tk.Button(self._frame, bg=BUTTON_COLOR, text=" ? ",
                                   font=("Courier bold", 10),
                                   command=self._info_window)

    def place_when_init(self):
        """
        places the object on the main window when the game is initializing.
        :return: None
        """
        self._boggle_label.place(x=280, y=0)
        self._timer_label.place(x=30, y=90)
        self._info_btn.place(x=740, y=20)

    def place_when_start(self):
        """
        places the object on the main window when the game is starting.
        :return: None
        """
        self._score_lbl.place(x=130, y=152)
        self._score_title_lbl.place(x=30, y=150)
        self._record_title_lbl.place(x=30, y=180)
        self._record_lbl.place(x=130, y=180)

    def _info_window(self):
        """
        creates a massage box with the instructions of the Boggle game
        :return: None
        """
        tk.messagebox.showinfo("information", INSTRUCTIONS)

    def set_clock_lbl(self, time_left):
        """
        sets the clock label
        :param time_left: time left until the end of the game
        :return: None
        """
        self._timer_label["text"] = time_left

    def set_score_label(self, score):
        """
        sets the score label
        :param score: the player's score
        :return: None
        """
        self._score_lbl["text"] = score

    def get_score_lbl_txt(self):
        return self._score_lbl["text"]

    def set_record_lbl(self, score):
        """
        sets the record label
        :param score: the player's score
        :return: None
        """
        self._record_lbl["text"] = score

    def end_game_others(self):
        """
        actions that occur when the game is over
        :return: None
        """
        self.set_clock_lbl("00:00:000")

    def reset_game_others(self):
        """
        actions that occur when the player want to start a new game
        :return: None
        """
        self.set_clock_lbl("03:00:000")
        self.set_score_label(0)
