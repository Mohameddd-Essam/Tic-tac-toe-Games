#ifndef GAME_3_H
#define GAME_3_H

#include "Board.h"
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

template <typename T>
class Game_3 : public Board<T> {
public:
    Game_3();
    ~Game_3();

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    bool is_full();
    pair<int, int> count_scores();

private:
    bool check_line_win(vector<T> line);
    bool check_rows();
    bool check_columns();
    bool check_diagonals();
};

template <typename T>
Game_3<T>::Game_3() {
    this->rows = 5;
    this->columns = 5;
    this->n_moves = 0;

    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = ' ';
        }
    }
}

template <typename T>
Game_3<T>::~Game_3() {
    for (int i = 0; i < this->rows; ++i)
        delete[] this->board[i];
    delete[] this->board;
}

template <typename T>
bool Game_3<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void Game_3<T>::display_board() {
    cout << "\n   ";
    for (int i = 0; i < this->columns; i++)
        cout << i << "   ";
    cout << "\n";

    for (int i = 0; i < this->rows; i++) {
        cout << i << " ";
        for (int j = 0; j < this->columns; j++) {
            cout << "| " << this->board[i][j] << " ";
        }
        cout << "|\n";
        cout << "  " << string(this->columns * 4, '-') << "\n";
    }
}

template <typename T>
bool Game_3<T>::is_win() {
    return check_rows() || check_columns() || check_diagonals();
}

template <typename T>
bool Game_3<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !is_win();
}

template <typename T>
bool Game_3<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
bool Game_3<T>::is_full() {
    return this->n_moves == this->rows * this->columns;
}

template <typename T>
pair<int, int> Game_3<T>::count_scores() {
    int scoreX = 0, scoreO = 0;
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == 'X') scoreX++;
            else if (this->board[i][j] == 'O') scoreO++;
        }
    }
    return {scoreX, scoreO};
}

template <typename T>
bool Game_3<T>::check_line_win(vector<T> line) {
    int countX = 0, countO = 0;
    for (T cell : line) {
        if (cell == 'X') {
            countX++;
            countO = 0;
        } else if (cell == 'O') {
            countO++;
            countX = 0;
        } else {
            countX = countO = 0;
        }
        if (countX >= 3 || countO >= 3)
            return true;
    }
    return false;
}

template <typename T>
bool Game_3<T>::check_rows() {
    for (int i = 0; i < this->rows; i++) {
        vector<T> row(this->board[i], this->board[i] + this->columns);
        if (check_line_win(row))
            return true;
    }
    return false;
}

template <typename T>
bool Game_3<T>::check_columns() {
    for (int j = 0; j < this->columns; j++) {
        vector<T> col;
        for (int i = 0; i < this->rows; i++)
            col.push_back(this->board[i][j]);
        if (check_line_win(col))
            return true;
    }
    return false;
}

template <typename T>
bool Game_3<T>::check_diagonals() {

    for (int d = -this->rows + 1; d < this->columns; d++) {
        vector<T> diag1, diag2;
        for (int i = 0; i < this->rows; i++) {
            int j1 = i + d;
            int j2 = this->columns - 1 - i - d;
            if (j1 >= 0 && j1 < this->columns)
                diag1.push_back(this->board[i][j1]);
            if (j2 >= 0 && j2 < this->columns)
                diag2.push_back(this->board[i][j2]);
        }
        if (check_line_win(diag1) || check_line_win(diag2))
            return true;
    }
    return false;
}

#endif // GAME_3_H
