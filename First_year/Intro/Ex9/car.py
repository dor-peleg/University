class Car:
    """
    The class creates car objects for the game with the relevant properties.
    Can make several checks and actions with the cars.
    """
    VERTICAL = 0
    HORIZONTAL = 1
    MOVE_UP = "u"
    MOVE_DOWN = "d"
    MOVE_LEFT = "l"
    MOVE_RIGHT = "r"

    def __init__(self, name, length, location, orientation):
        """
        A constructor for a Car object
        :param name: A string representing the car's name
        :param length: A positive int representing the car's length.
        :param location: A tuple representing the car's head (row, col) location
        :param orientation: One of either 0 (VERTICAL) or 1 (HORIZONTAL)
        """
        self.name = name
        self.length = length
        self.location = location
        self.orientation = orientation
        # Note that this function is required in your Car implementation.
        # However, is not part of the API for general car types.
        # implement your code and erase the "pass"

    def car_coordinates(self):
        """
        :return: A list of coordinates the car is in
        """
        coord_lst = []
        for coordinate in range(self.length):
            if self.orientation == self.VERTICAL:
                coord_lst.append((self.location[0] + coordinate,
                                  self.location[1]))
            if self.orientation == self.HORIZONTAL:
                coord_lst.append((self.location[0],
                                  self.location[1] + coordinate))
        return coord_lst

    def possible_moves(self):
        """
        :return: A dictionary of strings describing possible movements permitted by this car.
        """
        #For this car type, keys are from 'udrl'
        #The keys for vertical cars are 'u' and 'd'.
        #The keys for horizontal cars are 'l' and 'r'.
        #You may choose appropriate strings.
        # implement your code and erase the "pass"
        #The dictionary returned should look something like this:
        #result = {'f': "cause the car to fly and reach the Moon",
        #          'd': "cause the car to dig and reach the core of Earth",
        #          'a': "another unknown action"}
        #A car returning this dictionary supports the commands 'f','d','a'.
        if self.orientation == self.VERTICAL:
            return {'u': 'make the car move up',
                    'd': 'make the car move down'}
        if self.orientation == self.HORIZONTAL:
            return {'l': 'make the car move to the left',
                    'r': 'make the car move to the right'}

    def movement_requirements(self, movekey):
        """ 
        :param movekey: A string representing the key of the required move.
        :return: A list of cell locations which must be empty in order for this move to be legal.
        """
        #For example, a car in locations [(1,2),(2,2)] requires [(3,2)] to
        #be empty in order to move down (with a key 'd').
        # implement your code and erase the "pass"
        coordinates = self.car_coordinates()
        if self.orientation == self.VERTICAL:
            if movekey == self.MOVE_UP:
                return [(coordinates[0][0]-1, coordinates[0][1])]
            elif movekey == self.MOVE_DOWN:
                return [(coordinates[-1][0]+1, coordinates[-1][1])]

        if self.orientation == self.HORIZONTAL:
            if movekey == self.MOVE_LEFT:
                return [(coordinates[0][0], coordinates[0][1]-1)]
            elif movekey == self.MOVE_RIGHT:
                return [(coordinates[-1][0], coordinates[-1][1]+1)]
        return []

    def move(self, movekey):
        """ 
        :param movekey: A string representing the key of the required move.
        :return: True upon success, False otherwise
        """
        # implement your code and erase the "pass"
        if self.orientation == self.VERTICAL:
            if movekey not in 'ud':
                print("The car can't go that way!")
                return False
            elif movekey == self.MOVE_UP:
                self.location = (self.location[0] - 1, self.location[1])
            elif movekey == self.MOVE_DOWN:
                self.location = (self.location[0] + 1, self.location[1])
        if self.orientation == self.HORIZONTAL:
            if movekey not in 'lr':
                print("The car can't go that way!")
                return False
            elif movekey == self.MOVE_LEFT:
                self.location = (self.location[0], self.location[1] - 1)
            elif movekey == self.MOVE_RIGHT:
                self.location = (self.location[0], self.location[1] + 1)

        return True

    def get_name(self):
        """
        :return: The name of this car.
        """
        return self.name
