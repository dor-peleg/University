def calculate_mathematical_expression(a, b, c):
    """
    The function receives two numbers and one mathematical operation
    and returns the result of the calculation.
    """
    if c == '+':
        return a + b
    elif c == '*':
        return a * b
    elif c == '-':
        return a - b
    elif c == ':':
        if b == 0:
            return None
        else:
            return a / b
    else:
        return None


def calculate_from_string(string):
    """
    The function receives a mathematical expression as a string
    and returns the result of that expression.
    """
    splt = string.split()
    return calculate_mathematical_expression(float(splt[0]),
                                             float(splt[2]),
                                             splt[1])
