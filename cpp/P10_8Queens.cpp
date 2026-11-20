#include <bits/stdc++.h>
using namespace std;

constexpr int boardSize = 8;

using Board = array<int, boardSize>;

void solveQueens(int row, Board& board, array<bool, boardSize>& columns,
                 array<bool, 2 * boardSize - 1>& diagonals,
                 array<bool, 2 * boardSize - 1>& antiDiagonals,
                 vector<Board>& solutions) {
    if (row == boardSize) {
        solutions.push_back(board);
        return;
    }

    for (int column = 0; column < boardSize; ++column) {
        int diagonal = row - column + boardSize - 1;
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
    array<bool, boardSize> columns{};
    array<bool, 2 * boardSize - 1> diagonals{};
    array<bool, 2 * boardSize - 1> antiDiagonals{};
    vector<Board> solutions;
    solveQueens(0, board, columns, diagonals, antiDiagonals, solutions);

    cout << "Total solutions: " << solutions.size() << '\n';
    if (!solutions.empty()) {
        cout << "One solution:\n";
        for (int queen : solutions.front()) {
            for (int column = 0; column < boardSize; ++column) {
                if (column != 0) {
                    cout << ' ';
                }
                cout << (column == queen ? 'Q' : '.');
            }
            cout << '\n';
        }
    }
}
