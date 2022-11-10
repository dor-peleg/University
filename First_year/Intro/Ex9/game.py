class Game:
    """
    This class controls the game, checks for the cars and board if they are
    legal according to the game rules.
    Executing the turns of the game and responsible for ending it.
    """
    LEGAL_CAR_NAMES = 'YBOWGR'
    POSSIBLE_MOVES = 'udlr'
    def __init__(self, board):
        """
        Initialize a new Game object.
        :param board: An object of type board
        """
        #You may assume board follows the API
        # implement your code here (and then delete the next line - 'pass')
        self.board = board
        self.car_names = {}

    def __single_turn(self):
        """
        Note - this function is here to guide you and it is *not mandatory*
        to implement it. 

        The function runs one round of the game :
            1. Get user's input of: what color car to move, and what 
                direction to move it.
            2. Check if the input is valid.
            3. Try moving car according to user's input.

        Before and after every stage of a turn, you may print additional 
        information for the user, e.g., printing the board. In particular,
        you may support additional features, (e.g., hints) as long as they
        don't interfere with the API.
        """
        user_input = input('Enter a car name and direction (Car,Direction): ')
        if user_input == '!':
            return -1
        if self.check_input(user_input):
            for car in self.car_names:
                if car == user_input[0]:
                    car_name = car
            board.move_car(car_name, user_input[2])
        else:
            print("Illegal input!")

    def check_input(self, user_input):
        if len(user_input) != 3:
            return False
        if user_input[0] not in self.car_names:
            return False
        if user_input[2] not in self.POSSIBLE_MOVES:
            return False
        return True

    def add_car_from_json(self, car_dict):
        for car in car_dict:
            if len(car_dict[car]) != 3:
                continue
            if car_dict[car][0] < 2 or car_dict[car][0] > 4:
                continue
            if len(car) != 1:
                continue
            if car in self.LEGAL_CAR_NAMES:
                self.car_names[car] = Car(car, car_dict[car][0], car_dict[car][1],
                                          car_dict[car][2])

    def check_win(self):
        target_cell = board.target_location()
        for car, car_name in self.car_names.items():
            car_coordinates = car_name.car_coordinates()
            if target_cell in car_coordinates:
                return True
        return False

    def play(self):
        """
        The main driver of the Game. Manages the game until completion.
        :return: None
        """
        # implement your code here (and then delete the next line - 'pass')
        self.add_car_from_json(car_dict)
        for car in self.car_names:
            self.board.add_car(self.car_names[car])
        print(self.board)
        user_choice = True
        while not self.check_win() and user_choice != -1:
            user_choice = self.__single_turn()
            print(self.board)


if __name__ == "__main__":
    from car import *
    from board import *
    from helper import *
    from sys import *
    try:
        car_dict = load_json(argv[1])
    except FileNotFoundError:
        print("Json file not found")

    else:
        board = Board()
        game = Game(board)
        game.play()


