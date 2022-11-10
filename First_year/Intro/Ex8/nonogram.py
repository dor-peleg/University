from copy import *


def ok_to_stop(n, blocks, ind):
    """
    The function gets row length, blocks and row-index, and checks if it is
    possible to complete the row.
    :param n: the row length
    :param blocks: the blocks needed to add to the row
    :param ind: the index of the row
    :return: True if it is impossible to continue, False otherwise.
    """
    if n < sum(blocks[ind:]) + len(blocks[ind:]) - 1:
        return True
    return False


def constraint_satisfactions_helper(n, blocks, ind, partial_sol, result_list):
    """
    The function gets row length, blocks, row-index and partial solution,
    checks if the partial solution is valid and add it to the result list.
    :param n: the row length
    :param blocks: the blocks needed to add to the row
    :param ind: the index of the row
    :param partial_sol: the solution so far.
    :param result_list: a list with all the valid results.
    """
    # checking option func
    if ok_to_stop(n, blocks, ind):
        return

    if n <= 0:
        result_list.append(partial_sol)
        return

    if ind < len(blocks):
        # if we are adding the block
        with_block = partial_sol + [1] * blocks[ind]
        if n > blocks[ind]:
            with_block += [0]

        constraint_satisfactions_helper(n - blocks[ind] - 1, blocks, ind + 1,
                                        with_block, result_list)

    without_block = partial_sol + [0]
    constraint_satisfactions_helper(n - 1, blocks, ind, without_block,
                                    result_list)


#   1
def constraint_satisfactions(n, blocks):
    """
    The function gets row length and blocks.
    with the helper function creates all the possible options of the row.
    :param n: row length
    :param blocks: list of the blocks
    :return: list with all the valid options.
    """
    result_list = []

    constraint_satisfactions_helper(n, blocks, 0, [], result_list)
    return result_list


#   2
def row_variations(row, blocks):
    """
    the function gets partly full solution and the blocks.
    with the helper function creates a list of all the possible options
    of the row.
    :param row: partly full solution
    :param blocks: list of the blocks
    :return: list with all the valid options.
    """
    result_lst = []
    row_variations_helper(row, row[:], blocks, 0, 0, result_lst)
    return result_lst


def row_variations_helper(row, solution, blocks, row_idx, block_idx,
                          result_lst):
    """
    the function checks every option of filling the partly full row
    with the blocks
    :param row: partly full solution
    :param solution: copy of the partly full solution that getting changed.
    :param blocks: list of the blocks
    :param row_idx: index in row
    :param block_idx: index in block list
    :param result_lst: a list with all the valid result so far
    :return: a list with all the valid result
    """
    if block_idx > len(blocks) - 1:
        if -1 in solution:
            for i in range(len(solution)):
                if solution[i] == -1:
                    solution[i] = 0
        if sum(solution) == sum(blocks):
            result_lst.append(solution)
        return

    if row_idx > len(solution) - 1:
        return

    if ok_to_place(solution, blocks, row_idx, block_idx):
        solution[row_idx: row_idx + blocks[block_idx]] = \
            [1] * blocks[block_idx]
        if len(solution) - (row_idx + blocks[block_idx]) - 1 >= 0:
            solution[row_idx + blocks[block_idx]] = 0
        row_variations_helper(row, solution, blocks,
                              row_idx + blocks[block_idx] + 1,
                              block_idx + 1, result_lst)
    temp_solution = solution.copy()
    temp_solution[row_idx:] = row[row_idx:]
    if row[row_idx] == -1:
        temp_solution[row_idx] = 0
    row_variations_helper(row, temp_solution, blocks,
                          row_idx + 1, block_idx, result_lst)
    return result_lst


def ok_to_place(solution, blocks, row_idx, block_idx):
    """
    the function check if it is possible to black a cell according to the rules
    :param solution: partly full solution
    :param blocks: list of the blocks
    :param row_idx: index in row
    :param block_idx: index in block list
    :return: True if its possible to black the cell and False if it is not.
    """
    if row_idx + blocks[block_idx] > len(solution):
        return False
    for cell in solution[row_idx: row_idx + blocks[block_idx]]:
        if cell == 0:
            return False
    if len(solution) - (row_idx + blocks[block_idx]) > 0:
        if solution[row_idx + blocks[block_idx]] == 1:
            return False
    return True


# 3
def intersection_row(row):
    """
    the function checks for each cell if the result is common to all the rows.
    :param row: list of all the possible rows.
    :return: a row that is combination of all the rows.
    """
    final_lst = []
    if len(row) > 0:
        for idx in range(len(row[0])):
            value_set = set()
            for lst in row:
                value_set.add(lst[idx])
            if len(value_set) == 1:
                final_lst.append(list(value_set)[0])
            if 0 in value_set and 1 in value_set:
                final_lst.append(-1)
            elif 0 in value_set and -1 in value_set:
                final_lst.append(0)
            elif 1 in value_set and -1 in value_set:
                final_lst.append(1)
    return final_lst


def rows_to_columns(board, flag):
    """
    the function change the rows to columns and columns to rows.
    :param board: two dimensional array.
    :param flag: indicates if the original rows are rows or columns.
    :return: transposed two dimensional array
    """
    new_board = []
    if [] in board:
        return new_board, flag
    for idx in range(len(board[0])):
        column = []
        for row in board:
            column.append(row[idx])
        new_board.append(column)
    if flag == 0:
        flag = 1
    elif flag == 1:
        flag = 0
    return new_board, flag


def check_win(board, prev_board):
    """
    the function check if the board is done or can't be done.
    :param board: two dimensional array.
    :param prev_board: the previous two dimensional array for comparing.
    :return: True if the board is done or can't be done.
    """
    if prev_board == board:
        return True

    for lst in board:
        if -1 in lst:
            return False

    return True


def create_board(constraints):
    """
    the function gets list of rows and columns constraints and creat board
    according to those constraints
    :param constraints: list of rows and columns constraints
    :return: two dimensional array according to the constraints
    """
    board = []
    for blocks in constraints[0]:
        temp_list = constraint_satisfactions(len(constraints[1]), blocks)
        final_row = intersection_row(temp_list)
        board.append(final_row)
    return board


def solve_easy_nonogram_helper(constraints, board):
    """
    the function gets unsolved board and list of constrains and try repeatedly
    to solve the board
    :param constraints: list of rows and columns constraints
    :param board: two dimensional array.
    :return: solved two dimensional array.
    """
    flag = 0
    prev_board = []
    while not check_win(board, prev_board):
        if [] in board:
            return None
        if flag == 1:
            prev_board = deepcopy(board)
        board, flag = rows_to_columns(board, flag)
        for idx in range(len(board)):
            temp_list = row_variations(board[idx], constraints[flag][idx])
            if temp_list:
                final_list = intersection_row(temp_list)
            else:
                final_list = temp_list
            board[idx] = final_list
    if flag == 1:
        board, flag = rows_to_columns(board, flag)
    return board


#   4
def solve_easy_nonogram(constraints):
    """
    the function gets list of rows and columns constraints,
    create the board and try to solve it according to the constrains.
    :param constraints: list of rows and columns constraints
    :return: solved board.
    """
    board = create_board(constraints)
    board = solve_easy_nonogram_helper(constraints, board)
    if not board:
        return None
    return board


#   5
def solve_nonogram(constraints):
    """
    the function gets list of rows and columns constraints,
    and with helper functions, create the board and try to solve it by trying
    all the possible options.
    :param constraints: list of rows and columns constraints
    :return: list of all the valid solved boards.
    """
    board = solve_easy_nonogram(constraints)
    final_lst = solve_nonogram_helper(board, constraints, [])
    return final_lst


def solve_nonogram_helper(board, constraints, final_lst):
    """
    the function tries to solve the board using BackTracking, and check for all
    the possible full boards if they are valid.
    :param board: two dimensional array.
    :param constraints: list of rows and columns constraints
    :param final_lst: list of the valid board found so far
    :return: list of all the valid board
    """
    if board:
        board = solve_easy_nonogram_helper(constraints, board)
    if not board:
        return

    finished = True
    for row in range(len(board)):
        for idx in range(len(board[row])):
            if board[row][idx] == -1:
                finished = False
    for row in range(len(board)):
        if sum(board[row]) != sum(constraints[0][row]):
            finished = False

    if finished:
        if board not in final_lst:
            final_lst.append(board)
        return final_lst

    for row in range(len(board)):
        for idx in range(len(board[row])):
            if board[row][idx] == -1:
                temp_board = board.copy()
                temp_board[row][idx] = 1
                solve_nonogram_helper(temp_board, constraints, final_lst)

                temp_board[row][idx] = 0
                solve_nonogram_helper(temp_board, constraints, final_lst)

    return final_lst
