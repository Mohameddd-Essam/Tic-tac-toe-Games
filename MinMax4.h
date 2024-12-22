#ifndef ASSIGMENT_2_MINMAX4_H
#define ASSIGMENT_2_MINMAX4_H

#include "Board.h"
#include <limits>
#include <algorithm>
using namespace std;

template <typename T>
class X_O_MinMax_Player : public Player<T> {
private:
    char opponentSymbol; // Opponent's symbol

public:
    X_O_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(bool isMaximizing);
    std::pair<int, int> getBestMove();
};

template <typename T>
X_O_MinMax_Player<T>::X_O_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
    this->symbol = symbol; // AI's symbol
    opponentSymbol = (symbol == 'X') ? 'O' : 'X'; // Opponent's symbol
}

template <typename T>
void X_O_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
int X_O_MinMax_Player<T>::calculateMinMax(bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, isMaximizing ? this->symbol : opponentSymbol)) {
                int value = calculateMinMax(!isMaximizing);
                this->boardPtr->update_board(i, j, ' '); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

template <typename T>
std::pair<int, int> X_O_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(false);
                this->boardPtr->update_board(i, j, ' '); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

#endif // ASSIGMENT_2_MINMAX4_H
