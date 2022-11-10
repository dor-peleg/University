from screen import Screen
import sys
import random
from ship import *
from asteroid import *
from torpedo import *
from math import *


DELTA_X = Screen.SCREEN_MAX_X - Screen.SCREEN_MIN_X
DELTA_Y = Screen.SCREEN_MAX_Y - Screen.SCREEN_MIN_Y
DEFAULT_ASTEROIDS_NUM = 5


class GameRunner:
    """
    this class creates 'Asteroids' game
    """
    DEFAULT_ASTEROID_SIZE = 3
    DEFAULT_SHIP_LIVES = 3
    ASTEROID_OPTIONAL_SPEED = [-4, -3, -2, -1, 1, 2, 3, 4]
    DEFAULT_TORPEDO_NUM = 10
    DEFAULT_TORPEDO_LIFETIME = 200
    DEFAULT_SHIP_ANGLE_CHANGE = 7

    def __init__(self, asteroids_amount):
        self.__screen = Screen()

        self.__screen_max_x = Screen.SCREEN_MAX_X
        self.__screen_max_y = Screen.SCREEN_MAX_Y
        self.__screen_min_x = Screen.SCREEN_MIN_X
        self.__screen_min_y = Screen.SCREEN_MIN_Y

        self.ship_lives = self.DEFAULT_SHIP_LIVES
        self.points = 0
        self.ship1 = Ship(random.randint(self.__screen_min_x,
                                         self.__screen_max_x),
                          random.randint(self.__screen_min_y,
                                         self.__screen_max_y),
                          0, 0, 0)

        self.torpedo_lst = []
        self.torpedo_lifetime = {}

        self.asteroids_lst = []
        for i in range(asteroids_amount):
            self.asteroid = Asteroid(random.randint(self.__screen_min_x,
                                                    self.__screen_max_x),
                                     random.randint(self.__screen_min_y,
                                                    self.__screen_max_y),
                                     random.choice(self.ASTEROID_OPTIONAL_SPEED
                                                   ),
                                     random.choice(self.ASTEROID_OPTIONAL_SPEED
                                                   ),
                                     self.DEFAULT_ASTEROID_SIZE)

            self.asteroids_lst.append(self.asteroid)
            self.__screen.register_asteroid(self.asteroid,
                                            self.asteroids_lst[-1].size)
            self.__screen.draw_asteroid(self.asteroid, self.asteroid.x_pos,
                                        self.asteroid.y_pos)

    def run(self):
        self._do_loop()
        self.__screen.start_screen()

    def _do_loop(self):
        # You should not to change this method!
        self._game_loop()
        # Set the timer to go off again
        self.__screen.update()
        self.__screen.ontimer(self._do_loop, 5)

    def _game_loop(self):
        """
        this function manage the game by executing all the other functions
        repeatedly.
        :return: None
        """
        self.__move_ship()

        for asteroid in self.asteroids_lst:
            self.__move_asteroid(asteroid)
            if asteroid.has_intersection(self.ship1):
                self.__check_ship_crush(asteroid)
            self.__check_torpedo_crush(asteroid)

        if self.__screen.is_space_pressed():
            if len(self.torpedo_lst) < self.DEFAULT_TORPEDO_NUM:
                self.__add_torpedo()

        for torpedo in self.torpedo_lst:
            self.__move_torpedo(torpedo)

        if self.__check_end_game():
            self.__screen.end_game()
            sys.exit()

    def __update_score(self, asteroid):
        """
        this function updates the player's score according to the asteroid size
        :param asteroid: the asteroid that was hit
        :return: None
        """
        if asteroid.size == 3:
            self.points += 20
        elif asteroid.size == 2:
            self.points += 50
        elif asteroid.size == 1:
            self.points += 100
        self.__screen.set_score(self.points)

    def __move_torpedo(self, torpedo):
        """
        this function represent the movement of the torpedo on the board.
        :param torpedo: a torpedo object
        :return: None
        """
        self.change_spot(torpedo)
        self.__screen.draw_torpedo(torpedo, torpedo.x_pos, torpedo.y_pos,
                                   torpedo.direction)
        self.torpedo_lifetime[torpedo] += 1
        self.__remove_torpedo_check(torpedo)

    def __check_torpedo_crush(self, asteroid):
        """
        this function check if a torpedo hit an asteroid
        :param asteroid: an asteroid object
        :return: None
        """
        for torpedo in self.torpedo_lst:
            if asteroid.has_intersection(torpedo):
                self.__update_score(asteroid)
                self.__screen.unregister_torpedo(torpedo)
                self.torpedo_lst.remove(torpedo)
                if asteroid.size == 1:
                    self.__screen.unregister_asteroid(asteroid)
                    self.asteroids_lst.remove(asteroid)
                else:
                    self.__split_asteroids(asteroid, torpedo)
                break

    def __check_ship_crush(self, asteroid):
        """
        this function check if the ship hit an asteroid
        :param asteroid: an asteroid object
        :return: None
        """
        self.__screen.show_message("Warning", "You crashed into asteroid")
        self.__screen.remove_life()
        self.ship_lives -= 1
        self.__screen.unregister_asteroid(asteroid)
        self.asteroids_lst.remove(asteroid)

    def __move_asteroid(self, asteroid):
        """
        this function represent the movement of an asteroid on the game board
        :param asteroid: an asteroid object
        :return: None
        """
        self.change_spot(asteroid)
        self.__screen.draw_asteroid(asteroid, asteroid.x_pos, asteroid.y_pos)

    def __move_ship(self):
        """
        this function represent the movement of the ship on the game board
        :return: None
        """
        self.change_spot(self.ship1)
        self.change_ship_direction()
        self.change_ship_speed()
        self.__screen.draw_ship(self.ship1.x_pos, self.ship1.y_pos,
                                self.ship1.direction)

    def __check_end_game(self):
        """
        this function check if the game is over according to the rules
        :return: True if the game is over, False otherwise.
        """
        if self.ship_lives == 0:
            self.__screen.show_message('You lost!',
                                       "Sorry, Your ship was destroyed!")
            return True
        if len(self.asteroids_lst) == 0:
            self.__screen.show_message('You Won!', "Congratulation! You won!!")
            return True
        if self.__screen.should_end():
            self.__screen.show_message('Game over!',
                                       "You decided to stop, Goodbye!")
            return True
        return False

    def __add_torpedo(self):
        """
        this function adds a torpedo to the game when 'space' is pressed
        :return: None
        """
        self.torpedo_lst.append(Torpedo(self.ship1.x_pos, self.ship1.y_pos,
                                        self.ship1.x_speed + 2 * cos(
                                            radians(self.ship1.direction)),
                                        self.ship1.y_speed + 2 * sin(
                                            radians(self.ship1.direction)),
                                        self.ship1.direction))
        self.__screen.register_torpedo(self.torpedo_lst[-1])
        self.torpedo_lifetime[self.torpedo_lst[-1]] = 0

    def __remove_torpedo_check(self, torpedo):
        """
        check if the torpedo lifetime is over and remove it from the game.
        :param torpedo: a torpedo object
        :return: None
        """
        if self.torpedo_lifetime[torpedo] >= self.DEFAULT_TORPEDO_LIFETIME:
            self.__screen.unregister_torpedo(torpedo)
            self.torpedo_lst.remove(torpedo)

    def __split_asteroids(self, asteroid, torpedo):
        """
        manage the asteroid's splitting when it get hit by a torpedo by using
        'asteroid_splitting' function.
        :param asteroid: an asteroid object
        :param torpedo: a torpedo object
        :return: None
        """
        new_speed_x_pos = (torpedo.x_speed + asteroid.x_speed) / sqrt(
            asteroid.x_speed ** 2 + asteroid.y_speed ** 2)
        new_speed_y_pos = (torpedo.y_speed + asteroid.y_speed) / sqrt(
            asteroid.x_speed ** 2 + asteroid.y_speed ** 2)
        new_speed_x_neg = -new_speed_x_pos
        new_speed_y_neg = -new_speed_y_pos

        self.__asteroid_splitting(asteroid)

        self.asteroids_lst[-1].x_speed = new_speed_x_pos
        self.asteroids_lst[-1].y_speed = new_speed_y_neg
        self.asteroids_lst[-2].x_speed = new_speed_x_neg
        self.asteroids_lst[-2].y_speed = new_speed_y_pos

        self.asteroids_lst.remove(asteroid)
        self.__screen.unregister_asteroid(asteroid)

    def __asteroid_splitting(self, asteroid):
        """
        creates two new smaller asteroid.
        :param asteroid: an asteroid object
        :return: None
        """
        for i in range(2):
            self.asteroids_lst.append(Asteroid(asteroid.x_pos,
                                               asteroid.y_pos,
                                               random.choice(
                                                   self.ASTEROID_OPTIONAL_SPEED
                                                   ),
                                               random.choice(
                                                   self.ASTEROID_OPTIONAL_SPEED
                                                   ),
                                               asteroid.size - 1))

            self.__screen.register_asteroid(self.asteroids_lst[-1], 2)

    def change_ship_speed(self):
        """
        changing the ship's speed
        :return: None
        """
        if self.__screen.is_up_pressed():
            self.ship1.x_speed = self.ship1.x_speed + cos(
                radians(self.ship1.direction))
            self.ship1.y_speed = self.ship1.y_speed + sin(
                radians(self.ship1.direction))

    def change_ship_direction(self):
        """
        changing the ship's heading
        :return: None
        """
        if self.__screen.is_left_pressed():
            self.ship1.direction += self.DEFAULT_SHIP_ANGLE_CHANGE
        if self.__screen.is_right_pressed():
            self.ship1.direction -= self.DEFAULT_SHIP_ANGLE_CHANGE

    def change_spot(self, obj):
        """
        changing the object location
        :param obj: an object (ship, asteroid or torpedo)
        :return: None
        """
        new_spot_x = self.__screen_min_x + (obj.x_pos + obj.x_speed
                                            - self.__screen_min_x) % DELTA_X
        new_spot_y = self.__screen_min_y + (obj.y_pos + obj.y_speed
                                            - self.__screen_min_y) % DELTA_Y
        obj.x_pos = new_spot_x
        obj.y_pos = new_spot_y


def main(amount):
    runner = GameRunner(amount)
    runner.run()


if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(int(sys.argv[1]))
    else:
        main(DEFAULT_ASTEROIDS_NUM)
