# I chose to test the function with (-1,0,1)
# to check if the function can handle negative numbers.

# I chose to test the function with (5, 5.1, 5.11)
# to check if the function can handle float numbers
# and check its accuracy.

def largest_and_smallest(a, b, c):
    """
    The function receives three numbers and returns two values:
    the largest and the smallest.
    """
    if a <= b <= c:
        return c, a
    elif a <= c <= b:
        return b, a
    elif b <= c <= a:
        return a, b
    elif b <= a <= c:
        return c, b
    elif c <= a <= b:
        return b, c
    elif c <= b <= a:
        return a, c


def check_largest_and_smallest():
    """
    The function calls the 'largest_and_smallest' function several times
    with different parameters to check if the function works properly.
    """
    return largest_and_smallest(17, 1, 6) == (17, 1) and (
            largest_and_smallest(1, 17, 6) == (17, 1)) and (
            largest_and_smallest(1, 1, 2) == (2, 1)) and (
            largest_and_smallest(0, -1, 1)) == (1, -1) and (
            largest_and_smallest(5, 5.1, 5.11) == (5.11, 5))
