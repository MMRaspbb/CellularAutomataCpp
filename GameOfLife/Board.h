//
// Created by macie on 04.06.2024.
//

#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H

#include<iostream>
#include <vector>

class Board {
private:
    int width;
    int height;
    std::vector<std::vector<bool>> current_state;
    std::vector<std::vector<bool>> next_state;
public:
    Board(int, int);

    ~Board() = default;

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(Board&&) = delete;

    bool is_alive(int, int);

    void calculate_next_state();

    void push_next_state();

    bool point_is_alive(int, int);

    void set_point_alive(int, int);
};


#endif //GAMEOFLIFE_BOARD_H
