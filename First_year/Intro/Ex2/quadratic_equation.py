import math


def quadratic_equation(a, b, c):
    """
    This function gets three coefficients of a quadratic equation
    and returns its solutions.
    """
    if (b ** 2) - 4 * a * c < 0:
        return None, None
    else:
        x1 = (-b + math.sqrt((b ** 2) - 4 * a * c)) / 2 * a
        x2 = (-b - math.sqrt((b ** 2) - 4 * a * c)) / 2 * a

        if x1 == x2:
            return x1, None
        else:
            return x1, x2


def quadratic_equation_user_input():
    """
    The function asks the user for coefficients of a quadratic equation
    and prints the equation solutions to the screen.
    """
    coefficients = input("Insert coefficients a, b, and c: ")
    splt_coefficients = coefficients.split()
    if float(splt_coefficients[0]) == 0:
        print("The parameter 'a' may not equal 0")
    else:
        solutions = quadratic_equation(float(splt_coefficients[0]),
                                       float(splt_coefficients[1]),
                                       float(splt_coefficients[2]))

        if solutions[0] is None and solutions[1] is None:
            print("The equation has no solutions")

        elif solutions[0] and solutions[1] is None:
            print("The equation has 1 solution:", solutions[0])

        else:
            print("The equation has 2 solutions:", solutions[0],
                  "and", solutions[1])
