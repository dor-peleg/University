from wave_helper import *
from math import *
from copy import *
import os

###############################################################################
# FILE : wave_editor.py
# EXERCISE : intro2cs2 ex6 2020
# DESCRIPTION: Program that edit or compose wave files.
###############################################################################

DEFAULT_SAMPLE_RATE = 2000

MAX_VOLUME = 32767
MIN_VOLUME = -32768

A = 440     # A note frequency
B = 494     # B note frequency
C = 523     # C note frequency
D = 587     # D note frequency
E = 659     # E note frequency
F = 698     # F note frequency
G = 784     # G note frequency


def start_screen():
    """
    Prints to the screen the main options and asks the user to choose one.
    returns the user's choice.
    """
    initial_menu = ('1. Modify a .wav file.\n'
                    '2. Composing a melody in a format '
                    'suitable for a .wav file.\n'
                    '3. Exit the program.')
    print(initial_menu)

    user_input = input('What would you like to do: ')
    while user_input not in '123':
        print('There is no such option.')
        print(initial_menu)
        user_input = input('What would you like to do: ')
    return user_input


def load_file():
    """
    The function gets string of the .wav file's name the user want to change.
    :return: integer of the sample rate of the .wav file,
    and list of lists with the samples data.
    """
    wav_lst = -1
    while wav_lst == -1:
        wav_name = input("Please enter the .wav file's name: ")
        wav_lst = load_wave(wav_name)
        if wav_lst == -1:
            print("There is a problem with the .wav file!")
    return wav_lst[0], wav_lst[1]


def change_wav_menu():
    """
    The function prints the options for changing the wav data
    and asks the user what action he would like to do.
    :return: integer of the user's choice.
    """
    print("Welcome to Modify Wave file menu,\n"
          "Your options are:\n"
          "1. Reverse\n"
          "2. Audio_negation\n"
          "3. Audio acceleration\n"
          "4. Audio deceleration\n"
          "5. Increase volume\n"
          "6. Decrease volume\n"
          "7. Low pass filter\n"
          "8. Exit menu")

    user_input = '0'
    while user_input not in '12345678':
        user_input = input("What would you like to do? ")
        if user_input not in '12345678':
            print('No such option!')

    return user_input


def reverse(wav_lst):
    """
    The function creates a list in reverse order.
    :param wav_lst: list of sub-lists of wav values.
    :return: A list of all the sub-lists in reverse order
    """
    reversed_wav = wav_lst[::-1]
    return reversed_wav


def audio_negation(wav_lst):
    """
    The function negates all the values in a list.
    :param wav_lst: list of sub-lists of wav values.
    :return: List with all the negative values .
    """
    for sample in range(len(wav_lst)):
        for channel in range(2):
            if wav_lst[sample][channel] >= 0:
                wav_lst[sample][channel] = max(MIN_VOLUME,
                                               -wav_lst[sample][channel])
            elif wav_lst[sample][channel] < 0:
                wav_lst[sample][channel] = min(MAX_VOLUME,
                                               -wav_lst[sample][channel])
    return wav_lst


def acceleration(wav_lst):
    """
    The function accelerates the audio
    by returning only the values in even indexes.
    :param wav_lst: list of sub-lists of wav values.
    :return: List of values that were in the even indexes of the original list.
    """
    acc_wav = wav_lst[::2]
    return acc_wav


def deceleration(wav_lst):
    """
    The function slows down the audio by adding an average sample
    between each pair of samples.
    :param wav_lst: list of sub-lists of wav values.
    :return:A list in which between each pair of samples from the original list
     is a sample with the average value of these samples.
    """
    dec_wav = []
    if len(wav_lst) == 0:
        return []
    for sample in range(len(wav_lst) - 1):
        dec_wav.extend(
            [wav_lst[sample],
             [int((wav_lst[sample][0] + wav_lst[sample + 1][0]) // 2),
              int((wav_lst[sample][1] + wav_lst[sample + 1][1]) // 2)]])
    dec_wav.append(wav_lst[-1])
    return dec_wav


def increase_vol(wav_lst):
    """
    The function increases the volume by multiplying each sample by 1.2.
    :param wav_lst: list of sub-lists of wav values.
    :return: A list of sub-lists which each value from the original list
     is multiplied by 1.2.
    """
    for sample in range(len(wav_lst)):
        for channel in range(2):
            if wav_lst[sample][channel] >= 0:
                wav_lst[sample][channel] = int(min(MAX_VOLUME, 1.2 *
                                                   wav_lst[sample][channel]))
            if wav_lst[sample][channel] < 0:
                wav_lst[sample][channel] = int(max(MIN_VOLUME, 1.2 *
                                                   wav_lst[sample][channel]))
    return wav_lst


def decreasing_volume(lst):
    """
    The list lowers the volume by dividing each sample by 1.2.
    :param lst: list of sub-lists of wav values.
    :return: A list of sub-lists which each value from the original list
     is divided by 1.2.
    """
    for i in range(len(lst)):
        for j in range(2):
            lst[i][j] = int(lst[i][j] / 1.2)
    return lst


def low_pass_filter(wav_lst):
    """
    The function blur the sound by replacing each value in the list with the
    average value of that value, the value before it and the value after it.
    :param wav_lst: list of sub-lists of wav values
    :return: A list where each value is the average value of that value,
    the value before it and the value after it from the original list
    """
    l_p_wav = deepcopy(wav_lst)
    for sample in range(len(wav_lst)):
        for channel in range(2):
            if sample == 0:
                l_p_wav[sample][channel] = (int((wav_lst[sample][channel]
                                            + wav_lst[sample + 1][channel])
                                            // 2))
            elif sample == len(wav_lst) - 1:
                l_p_wav[sample][channel] = (int((wav_lst[sample][channel]
                                            + wav_lst[sample - 1][channel])
                                            / 2))
            else:
                l_p_wav[sample][channel] = (int((wav_lst[sample - 1][channel]
                                            + wav_lst[sample][channel]
                                            + wav_lst[sample + 1][channel])
                                            / 3))

    return l_p_wav


def creating_composing_list():
    """
    The function gets file name, reads the input
    and return list of lists of the notes and their duration.
    :return: list of lists of the notes and their duration.
    """
    file_exist = False
    while not file_exist:
        file_name = input('Please enter file to compose: ')
        file_exist = os.path.exists(file_name)
    lst = []
    with open(file_name, 'r') as f:
        for line in f:
            line = line.replace(' ', '')
            line = line.replace('\n', '')
            line = line.replace('\t', '')
            lst.append(line)
    note_str = ''.join(lst)
    note_lst = []
    for note_idx in range(0, len(note_str) - 1, 2):
        for duration in range(note_idx + 1, note_idx + 2):
            note_lst.append([note_str[note_idx], int(note_str[duration])])
    return note_lst


def change_letter(char):
    """
    Gets string of letter and return the matching constant value.
    """
    if char == 'A':
        char = A
    elif char == 'B':
        char = B
    elif char == 'C':
        char = C
    elif char == 'D':
        char = D
    elif char == 'E':
        char = E
    elif char == 'F':
        char = F
    elif char == 'G':
        char = G
    return char


def composing_lst(note_lst):
    """
    The function composing the wanted audio by the given list of notes.
    :param note_lst: list of lists of the notes and their duration.
    :return: list of lists of each sample according to the notes.
    """
    data_lst = []
    for i in range(len(note_lst)):
        if note_lst[i][0] == 'Q':
            result = [0, 0]
            for j in range(125 * note_lst[i][1]):
                data_lst.append(result)
        else:
            char = note_lst[i][0]
            frequency = change_letter(char)
            samples_per_cycle = 2000 / frequency
            for j in range(125 * note_lst[i][1]):
                result = MAX_VOLUME * sin(2 * pi * (j / samples_per_cycle))
                result = [int(result)] * 2
                data_lst.append(result)
    return data_lst


def saving_screen(sample_rate, audio_data):
    """
    The function gets sample rate value and list of the wav data and saves it
    to a file of the user's choice.
    :param sample_rate: the original sample rate of the wav file the user
    loaded, or the default sample rate if the user composed audio.
    :param audio_data: list of the wav data after all the changes.
    """
    wave_filename = -1
    while wave_filename == -1:
        wave_filename = input(
            'Enter the file name where you want to save the information: ')
        if wave_filename == -1:
            print('Wrong_input')
    save_wave(sample_rate, audio_data, wave_filename)
    print('The information was saved successfully')


def modify_wav(data_lst):
    """
    The function calls the 'change_wav_menu' function and get the user's choice
    Also gets list of all the wav data,
    and calls the matching function with the data list.
    :param data_lst: list of sub-lists of wav values
    :return: The data list after the change.
    """
    user_input = '0'
    while user_input != '8':
        user_input = change_wav_menu()
        if user_input == '1':
            data_lst = reverse(data_lst)
        elif user_input == '2':
            data_lst = audio_negation(data_lst)
        elif user_input == '3':
            data_lst = acceleration(data_lst)
        elif user_input == '4':
            data_lst = deceleration(data_lst)
        elif user_input == '5':
            data_lst = increase_vol(data_lst)
        elif user_input == '6':
            data_lst = decreasing_volume(data_lst)
        elif user_input == '7':
            data_lst = low_pass_filter(data_lst)
        print("The wave file changed successfully!")
    return data_lst


def main():
    user_input = '0'
    while user_input != '3':
        user_input = start_screen()

        if user_input == '1':
            sample_rate, data_lst = load_file()
            modified_data = modify_wav(data_lst)
            saving_screen(sample_rate, modified_data)

        elif user_input == '2':
            note_lst = creating_composing_list()
            data_lst = composing_lst(note_lst)
            modified_wav = modify_wav(data_lst)
            saving_screen(DEFAULT_SAMPLE_RATE, modified_wav)

    exit()


if __name__ == "__main__":
    main()
