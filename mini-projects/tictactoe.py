def display(grid):
    for i in grid:
        print(i)

def check_win(mover, grid):
    # check diagonals
    if [grid[0][0], grid[1][1], grid[2][2]] == [mover for x in range(3)]:
        return mover
    elif [grid[2][0], grid[1][1], grid[0][2]] == [mover for x in range(3)]:
        return mover
    else:
        # check vertical and horizontal
        for i in range(3):
            if [grid[0][i], grid[1][i], grid[2][i]] == [mover for x in range(3)]:
                return mover
            elif i == [mover for x in range(3)]:
                return mover
    return 0

def valid_move(grid, move):
    if move == []:
        print(1)
        return False
    if move[0] >= 3 or move[1] >=3 or move[0] <= -1 or move[1] <=-1:
        print(1)
        return False

    if grid[move[0]][move[1]] != 0:
        print(1)
        return False

    return True

def check(grid, move, player, prev):
    if not valid_move(grid, move):
        print(1)
        grid = prev
        return 0, grid, grid

    grid[move[0]][move[1]] = player
    mover = player
    win = check_win(mover, grid)
    prev = grid

    return win, prev, grid

def play(player):
    move = input(f"enter the index of where you want to marker {player}: ")
    if ' '  in move:
        move = [int(x) for x in move.split()]
    else:
        move = [int(x) for x in move]
    return move

grid = [[0 for x in range(3)] for y in range(3)] # 3x3 grid for tictactoe
prev = grid.copy()

player = 'x'

move = play(player)
win, prev, grid = check(grid, move, player, prev=prev)
display(grid)

win = 0
while not win:
    if player == 'x':
        player = 'o'
    else:
        player = 'x'

    move = play(player)
    win, prev, grid = check(grid, move, player=player, prev=prev)
    display(grid)

print(win)
