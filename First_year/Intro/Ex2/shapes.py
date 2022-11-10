import math


def circle_area():
    """
    The function waits for an input of the radius length
    and returns the area of the circle with that radius.
    """
    radius = float(input())
    return math.pi*(radius**2)


def rectangle_area():
    """
    The function waits for input of the lengths of the two edges
    and returns the area of the rectangle with these edges.
    """
    edge_1 = float(input())
    edge_2 = float(input())
    return edge_1*edge_2


def triangle_area():
    """
    The function waits for input of the length of the edge
    and returns the area of the triangle with these edges.
    """
    edge = float(input())
    return (math.sqrt(3)/4)*(edge**2)


def shape_area():
    """
    The function requests input of a shape and returns its area.
    """
    shape_num = input("Choose shape (1=circle, 2=rectangle, 3=triangle): ")
    if shape_num == '1':
        return circle_area()
    elif shape_num == '2':
        return rectangle_area()
    elif shape_num == '3':
        return triangle_area()
