def solve_queens(n=8):
    solutions = []
    board = []
    columns = set()
    diagonals = set()
    anti_diagonals = set()

    def backtrack(row):
        if row == n:
            solutions.append(board[:])
            return
        for column in range(n):
            if (
                column in columns
                or row - column in diagonals
                or row + column in anti_diagonals
            ):
                continue
            board.append(column)
            columns.add(column)
            diagonals.add(row - column)
            anti_diagonals.add(row + column)
            backtrack(row + 1)
            board.pop()
            columns.remove(column)
            diagonals.remove(row - column)
            anti_diagonals.remove(row + column)

    backtrack(0)
    return solutions


if __name__ == "__main__":
    board_size = 8

    solutions = solve_queens(board_size)
    print("Total solutions:", len(solutions))
    if solutions:
        print("One solution:")
        for column in solutions[0]:
            print(" ".join("Q" if position == column else "." for position in range(board_size)))
