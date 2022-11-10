from math import *

class Asteroid:
    def __init__(self, x_pos, y_pos, x_speed, y_speed, size):
        self.x_pos = x_pos
        self.y_pos = y_pos
        self.x_speed = x_speed
        self.y_speed = y_speed
        self.size = size

    def get_radius(self):
        """
        this function returns the asteroid's radius
        :return: int - radius
        """
        return self.size * 10 - 5

    def has_intersection(self, obj):
        """
        this function checks if the asteroid crashed with another object
        :param obj: the given object
        :return: True if there is crush, False otherwise
        """
        distance = sqrt((obj.x_pos - self.x_pos)**2
                        + ((obj.y_pos - self.y_pos)**2))
        return distance <= self.get_radius() + obj.get_radius()
