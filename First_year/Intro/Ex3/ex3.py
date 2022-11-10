"""
# WRITER : Dor Peleg , dor.peleg , 312163421
# EXERCISE : intro2cs1 Ex3 2021
"""


def input_list():
    """
    The function receives inputs from user,
    and returns a list of the inputs, and their sum at the end of the list.
    """
    num_lst = []
    num_sum = 0
    while True:
        num = input()
        if num == "":
            break
        num_lst.append(float(num))
        num_sum += float(num)
    num_lst.append(num_sum)
    return num_lst


def inner_product(vec_1, vec_2):
    """
    The function gets two lists of numbers,
    and returns their inner product.
    """
    ip = 0
    if id(vec_1) == id(vec_2):
        return
    elif len(vec_1) != len(vec_2):
        return None
    for i in range(len(vec_1)):
        ip += vec_1[i] * vec_2[i]
    return ip


def sequence_monotonicity(sequence):
    """
    The function receives a sequence (list of numbers),
    and returns if the sequence is
    monotonically increasing, strictly monotonically increasing,
    monotonically decreasing or strictly monotonically decreasing
    as a list of boolean values.
    """
    boolean_lst = [True, True, True, True]
    for i in range(1, len(sequence)):
        if sequence[i - 1] > sequence[i]:
            boolean_lst[0] = False
        if sequence[i - 1] >= sequence[i]:
            boolean_lst[1] = False
        if sequence[i - 1] < sequence[i]:
            boolean_lst[2] = False
        if sequence[i - 1] <= sequence[i]:
            boolean_lst[3] = False
    return boolean_lst


def monotonicity_inverse(def_bool):
    """
    The function receives a list of 4 boolean values
    and returns a list of 4 numbers representing a Sequence
    that is an example of a Sequence according to the received list.
    """
    if not def_bool[0] and not def_bool[1] and \
            not def_bool[2] and not def_bool[3]:
        return [1, 2, 1, 2]

    if def_bool[0]:
        if def_bool[3]:
            return None
        elif def_bool[1]:
            if def_bool[2]:
                return None
            return [1, 2, 3, 4]
        elif def_bool[2]:
            return [1, 1, 1, 1]
        return [1, 2, 2, 4]

    if def_bool[2]:
        if def_bool[1]:
            return None
        elif def_bool[3]:
            return [4, 3, 2, 1]
        return [4, 3, 3, 1]

    return None


def primes_for_asafi(n):
    """
    The function gets an integer n
    and returns a list of the first n prime numbers.
    """
    primes = []
    num = 2
    while len(primes) < n:
        prime = True
        for i in primes:
            if num % i == 0:
                prime = False
        if prime:
            primes.append(num)
        num += 1
    return primes


def sum_of_vectors(vec_lst):
    """
    The function receives a list of vectors (list of lists)
    and returns a vector (list) which is their vector sum.
    """
    vec_sum = []
    if len(vec_lst) == 0:
        return None
    else:
        for i in range(len(vec_lst[0])):
            index_sum = 0
            for j in vec_lst:
                index_sum += j[i]
            vec_sum.append(index_sum)
        return vec_sum


def num_of_orthogonal(vectors):
    """
    The function receives a list of vectors (list of lists)
    and returns the number of pairs of lists
    that are perpendicular to each other
    """
    counter = 0
    for i in vectors:
        for j in vectors:
            if inner_product(i, j) == 0:
                counter += 1
    return int(counter / 2)
