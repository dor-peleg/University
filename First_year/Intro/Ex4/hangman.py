from hangman_helper import *

EMPTY_MSG = ""
ILLEGAL_MSG = "Illegal input! try again!"
EXISTING_LETTER_MSG = "You already guessed that letter!"
WIN_MSG = "Congratulations!! You guessed the right word!"


def update_word_pattern(word, pattern, letter):
    lst_pattern = list(pattern)
    for i in range(len(word)):
        if word[i] == letter:
            lst_pattern[i] = letter
    return "".join(lst_pattern)


def letter_guess(word, letter, pattern, wrong_guess_lst, updated_points):
    if len(letter) > 1 or letter.islower() is False:
        msg = ILLEGAL_MSG
    elif letter in wrong_guess_lst or letter in pattern:
        msg = EXISTING_LETTER_MSG
    else:
        updated_points -= 1
        msg = EMPTY_MSG
        if letter in word:
            pattern = update_word_pattern(word, pattern, letter)
            occurrences = word.count(letter)
            updated_points += occurrences * (occurrences + 1) // 2
        else:
            wrong_guess_lst.append(letter)
    return pattern, wrong_guess_lst, updated_points, msg


def word_guess(word, guess, pattern, updated_points):
    if guess == word:
        occurrences = pattern.count("_")
        updated_points += occurrences * (occurrences + 1) // 2
        for letter in guess:
            pattern = update_word_pattern(word, pattern, letter)
    return pattern, updated_points


def ask_hint(words_list, pattern, wrong_guess_lst):
    filtered_lst = filter_words_list(words_list, pattern,
                                     wrong_guess_lst)
    hint_lst = []
    if len(filtered_lst) > HINT_LENGTH:
        for i in range(HINT_LENGTH, 0, -1):
            hint_idx = ((HINT_LENGTH - i) * len(filtered_lst)) \
                       // HINT_LENGTH
            hint_lst.append(filtered_lst[hint_idx])
        show_suggestions(hint_lst)
    else:
        show_suggestions(filtered_lst)


def run_single_game(words_list, points):
    updated_points = points
    word = get_random_word(words_list)
    wrong_guess_lst = []
    pattern = "_" * len(word)
    msg = ""
    while updated_points > 0 and "_" in pattern:
        display_state(pattern, wrong_guess_lst, updated_points, msg)
        guess_type, guess = get_input()
        if guess_type == LETTER:
            pattern, wrong_guess_lst, updated_points, msg = letter_guess(
                word, guess, pattern, wrong_guess_lst, updated_points)
        if guess_type == WORD:
            msg = EMPTY_MSG
            updated_points -= 1
            pattern, updated_points = word_guess(
                word, guess, pattern, updated_points)
        if guess_type == HINT:
            msg = EMPTY_MSG
            updated_points -= 1
            ask_hint(words_list, pattern, wrong_guess_lst)
    if updated_points > 0:
        msg = WIN_MSG
    else:
        msg = f"Sorry, you lost! The word was: {word}"
    display_state(pattern, wrong_guess_lst, updated_points, msg)
    return updated_points


def filter_words_list(words, pattern, wrong_guess_lst):
    filter_words = []
    for word in words:
        match_word = True
        if len(word) == len(pattern):
            for letter in wrong_guess_lst:
                if letter in word:
                    match_word = False
            if match_word:
                for slot in range(len(pattern)):
                    if pattern[slot].islower():
                        if pattern[slot] != word[slot]:
                            match_word = False
                    else:
                        if word[slot] in pattern:
                            match_word = False
            if match_word:
                filter_words.append(word)
    return filter_words


def main():
    words_list = load_words(file='words.txt')
    want_to_play = True
    while want_to_play:
        points = POINTS_INITIAL
        num_of_games = 0
        while points > 0:
            num_of_games += 1
            points = run_single_game(words_list, points)
            if points > 0:
                if play_again(f"Number of games played so far: {num_of_games}."
                              f" Your score:{points}. Want to play again?"):
                    continue
                return
        if play_again(f"Number of games survived: {num_of_games}."
                      f" Start a new series of games?"):
            continue
        return


if __name__ == "__main__":
    main()
