#include <array>
#include <iostream>
#include <vector>

constexpr int size = 8;
using Board = std::array<int, size>;

void solveQueens(int row, Board& board, std::array<bool, size>& columns,
                 std::array<bool, 2 * size - 1>& diagonals,
                 std::array<bool, 2 * size - 1>& antiDiagonals,
                 std::vector<Board>& solutions) {
    if (row == size) {
        solutions.push_back(board);
        return;
    }

    for (int column = 0; column < size; ++column) {
        int diagonal = row - column + size - 1;
        int antiDiagonal = row + column;
        if (columns[column] || diagonals[diagonal] || antiDiagonals[antiDiagonal]) {
            continue;
        }

        board[row] = column;
        columns[column] = diagonals[diagonal] = antiDiagonals[antiDiagonal] = true;
        solveQueens(row + 1, board, columns, diagonals, antiDiagonals, solutions);
        columns[column] = diagonals[diagonal] = antiDiagonals[antiDiagonal] = false;
    }
}

int main() {
    Board board{};
    std::array<bool, size> columns{};
    std::array<bool, 2 * size - 1> diagonals{};
    std::array<bool, 2 * size - 1> antiDiagonals{};
    std::vector<Board> solutions;
    solveQueens(0, board, columns, diagonals, antiDiagonals, solutions);

    std::cout << "Total solutions: " << solutions.size() << '\n';
    if (!solutions.empty()) {
        std::cout << "One solution:\n";
        for (int queen : solutions.front()) {
            for (int column = 0; column < size; ++column) {
                if (column != 0) {
                    std::cout << ' ';
                }
                std::cout << (column == queen ? 'Q' : '.');
            }
            std::cout << '\n';
        }
    }
}
