//
// Created by macie on 04.06.2024.
//

#include "Board.h"

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;
    for (int i = 0; i < width; i++) {
        current_state.push_back(std::vector<bool>());
        next_state.push_back(std::vector<bool>());
        for (int j = 0; j < height; j++) {
            current_state[i].push_back(false);
            next_state[i].push_back(false);
        }
    }
}

bool Board::is_alive(int x, int y) {
    int alive_neighbours = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++){
            if((i != 0 || j != 0) && x + i >= 0 && x + i < width && y + j >= 0 && y + j < height && current_state[x + i][y + j]){
                alive_neighbours += 1;
            }
        }
    }
    if(current_state[x][y] && (alive_neighbours == 2 || alive_neighbours == 3)){
        return true;
    }
    else if(alive_neighbours == 3){
        return true;
    }
    return false;
}

void Board::calculate_next_state() {
    for(int i = 0;i < width;i++){
        for(int j = 0;j < height;j++){
            next_state[i][j] = is_alive(i, j);
        }
    }
}

void Board::push_next_state() {
    current_state = next_state;
    for(int i = 0;i < width;i++){
        for(int j = 0;j < height;j++){
            next_state[i][j] = false;
        }
    }
}

bool Board::point_is_alive(int x, int y) {
    if(current_state[x][y]){
        return true;
    }
    return false;
}

void Board::set_point_alive(int x, int y) {
    current_state[x][y] = true;
}