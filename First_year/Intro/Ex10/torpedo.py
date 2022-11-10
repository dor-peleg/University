TORPEDO_RADIUS = 4


class Torpedo:
    def __init__(self, x_pos, y_pos, x_speed, y_speed, direction):
        self.x_pos = x_pos
        self.y_pos = y_pos
        self.x_speed = x_speed
        self.y_speed = y_speed
        self.direction = direction

    def get_radius(self):
        """
        this function returns the torpedo's radius
        :return: int - radius
        """
        return TORPEDO_RADIUS
