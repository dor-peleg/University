class Board:
    EMPTY_CELL = '_ '
    NUM_OF_ROWS = 7
    NUM_OF_COLS = 7
    POSSIBLE_MOVES = 'udlr'
    MOVE_UP = "u"
    MOVE_DOWN = "d"
    MOVE_LEFT = "l"
    MOVE_RIGHT = "r"
    """
    This class creates the game-board, 
    can add and move the cars on the board.
    """

    def __init__(self):
        self.my_board = {(0, 0): '_ ', (0, 1): '_ ', (0, 2): '_ ',
                         (0, 3): '_ ',
                         (0, 4): '_ ', (0, 5): '_ ', (0, 6): '_ ',
                         (0, 7): '\n',
                         (1, 0): '_ ', (1, 1): '_ ', (1, 2): '_ ',
                         (1, 3): '_ ',
                         (1, 4): '_ ', (1, 5): '_ ', (1, 6): '_ ',
                         (1, 7): '\n',
                         (2, 0): '_ ', (2, 1): '_ ', (2, 2): '_ ',
                         (2, 3): '_ ',
                         (2, 4): '_ ', (2, 5): '_ ', (2, 6): '_ ',
                         (2, 7): '\n',
                         (3, 0): '_ ', (3, 1): '_ ', (3, 2): '_ ',
                         (3, 3): '_ ',
                         (3, 4): '_ ', (3, 5): '_ ', (3, 6): '_ ',
                         (3, 7): '->',
                         (3, 8): '\n',
                         (4, 0): '_ ', (4, 1): '_ ', (4, 2): '_ ',
                         (4, 3): '_ ',
                         (4, 4): '_ ', (4, 5): '_ ', (4, 6): '_ ',
                         (4, 7): '\n',
                         (5, 0): '_ ', (5, 1): '_ ', (5, 2): '_ ',
                         (5, 3): '_ ',
                         (5, 4): '_ ', (5, 5): '_ ', (5, 6): '_ ',
                         (5, 7): '\n',
                         (6, 0): '_ ', (6, 1): '_ ', (6, 2): '_ ',
                         (6, 3): '_ ',
                         (6, 4): '_ ', (6, 5): '_ ', (6, 6): '_ '}

        self.car_names = {}
        # implement your code and erase the "pass"
        # Note that this function is required in your Board implementation.
        # However, is not part of the API for general board types.

    def __str__(self):
        """
        This function is called when a board object is to be printed.
        :return: A string of the current status of the board
        """
        # The game may assume this function returns a reasonable representation
        # of the board for printing, but may not assume details about it.
        printed_board = ''
        for location in self.my_board:
            printed_board += self.my_board[location]
        return printed_board

    def cell_list(self):
        """ This function returns the coordinates of cells in this board
        :return: list of coordinates
        """
        # In this board, returns a list containing the cells in the square
        # from (0,0) to (6,6) and the target cell (3,7)
        all_cells = [(i, j) for i in range(self.NUM_OF_ROWS)
                     for j in range(self.NUM_OF_COLS)]
        all_cells.append((3, 7))
        return all_cells

    def possible_moves(self):
        """ This function returns the legal moves of all cars in this board
        :return: list of tuples of the form (name,movekey,description)
                 representing legal moves
        """
        # From the provided example car_config.json file, the return value could be
        # [('O','d',"some description"),('R','r',"some description"),('O','u',"some description")]
        final_lst = []
        move_dict = {'u': 'up', 'd': 'down', 'l': 'left', 'r': 'right'}
        for car in self.car_names:
            for movekey in self.POSSIBLE_MOVES:
                target_cell = car.movement_requirements(movekey)
                if not target_cell:
                    continue
                if not self.cell_content(target_cell[0]):
                    final_lst.append((self.car_names[car], movekey,
                                      self.car_names[car] + ' can go ' +
                                      move_dict[movekey]))
        return final_lst

    def target_location(self):
        """
        This function returns the coordinates of the location which is to be filled for victory.
        :return: (row,col) of goal location
        """
        # In this board, returns (3,7)
        return (3, 7)

    def cell_content(self, coordinate):
        """
        Checks if the given coordinates are empty.
        :param coordinate: tuple of (row,col) of the coordinate to check
        :return: The name if the car in coordinate, None if empty
        """
        if coordinate not in self.my_board:
            return -1
        if self.my_board[coordinate] == '->':
            return None
        if self.my_board[coordinate] != self.EMPTY_CELL:
            return self.my_board[coordinate][0]
        return None

    def add_car(self, car):
        """
        Adds a car to the game.
        :param car: car object of car to add
        :return: True upon success. False if failed
        """
        # Remember to consider all the reasons adding a car can fail.
        # You may assume the car is a legal car object following the API.
        # implement your code and erase the "pass"
        valid_car = True
        car_name = car.get_name()
        car_coordinates = car.car_coordinates()

        for coordinate in car_coordinates:
            if coordinate not in self.my_board:
                valid_car = False
                return False
            content = self.cell_content(coordinate)
            if content is not None:
                valid_car = False
                return False

        for existing_car in self.car_names:
            if car_name == existing_car.get_name():
                valid_car = False
                return False

        if valid_car:
            for coordinate in car_coordinates:
                self.my_board[coordinate] = car_name + ' '
            self.car_names[car] = car_name

            return True
        return False

    def move_car(self, name, movekey):
        """
        moves car one step in given direction.
        :param name: name of the car to move
        :param movekey: Key of move in car to activate
        :return: True upon success, False otherwise
        """
        # implement your code and erase the "pass"
        car_exist = False
        for car in self.car_names:
            if name == self.car_names[car]:
                moving_car = car
                car_exist = True

        if car_exist:
            car_coordinates = moving_car.car_coordinates()
            target_cell = moving_car.movement_requirements(movekey)
            if not target_cell:
                return False
            if movekey == self.MOVE_UP:
                if target_cell[0][0] < 0:
                    print("The car is out of board, Try again")
                    return False
            elif movekey == self.MOVE_DOWN:
                if target_cell[0][0] > self.NUM_OF_ROWS - 1:
                    print("The car is out of board, Try again")
                    return False
            elif movekey == self.MOVE_RIGHT:
                if target_cell[0][1] > self.NUM_OF_COLS:
                    print("The car is out of board, Try again")
                    return False
            elif movekey == self.MOVE_LEFT:
                if target_cell[0][1] < 0:
                    print("The car is out of board, Try again")
                    return False
            if self.my_board[target_cell[0]] != self.EMPTY_CELL and \
                    self.my_board[target_cell[0]] != '->':
                print("You can't go there!")
                return False
            for coord in car_coordinates:
                self.my_board[coord] = self.EMPTY_CELL
            moving_car.move(movekey)
            car_coordinates = moving_car.car_coordinates()
            for coordinate in car_coordinates:
                self.my_board[coordinate] = moving_car.get_name() + ' '
            return True
        return False

