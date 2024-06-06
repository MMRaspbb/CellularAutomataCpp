#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include<iostream>
#include "StartStopButton.h"
#include "Board.h"

const int WINDOW_HEIGHT = 880;
const int WINDOW_WIDTH = 1000;
const int POINT_SQUARE_SIDE = 20;
const int BUTTON_SPACE = 80;
const int DESIRED_FPS = 60;
const int ITERATION_TO_REFRESH = 5;

void draw_rectangles(sf::RenderWindow &, const std::vector<sf::RectangleShape> &);

void make_horizontal_gridlines(std::vector<sf::RectangleShape> &, int);

void make_vertical_gridlines(std::vector<sf::RectangleShape> &, int);

void make_points(std::vector<std::vector<sf::RectangleShape>>&);

void recolor_points(std::vector<std::vector<sf::RectangleShape>>&, Board&);


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GameOfLife",
                            sf::Style::Close | sf::Style::Titlebar);

    const int rectangle_number_in_line = WINDOW_WIDTH / POINT_SQUARE_SIDE;
    const int rectangle_number_in_column = (WINDOW_HEIGHT - BUTTON_SPACE) / POINT_SQUARE_SIDE;

    std::vector<sf::RectangleShape> gridlines_horizontal;
    std::vector<sf::RectangleShape> gridlines_vertical;

    std::vector<std::vector<sf::RectangleShape>> points;

    make_horizontal_gridlines(gridlines_horizontal, rectangle_number_in_column);
    make_vertical_gridlines(gridlines_vertical, rectangle_number_in_line);

    make_points(points);

    Board board(rectangle_number_in_line, rectangle_number_in_column);

    StartStopButton button(WINDOW_WIDTH / 2, WINDOW_HEIGHT - BUTTON_SPACE / 2);
    bool mouse_button_down = false;

    sf::Clock clock;
    long iteration = 0;

    while (window.isOpen()) {
        sf::Event action;
        while (window.pollEvent(action)) {
            switch (action.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    mouse_button_down = true;
                    if (button.is_point_in_button(sf::Mouse::getPosition(window))) {
                        button.switch_text();
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    mouse_button_down = false;
                    break;
            }
        }

        if(mouse_button_down && button.is_start()){
            sf::Vector2 position = sf::Mouse::getPosition(window);
            int x = position.x;
            int y = position.y;
            x -= x%POINT_SQUARE_SIDE;
            y -= y%POINT_SQUARE_SIDE;
            x /= POINT_SQUARE_SIDE;
            y /= POINT_SQUARE_SIDE;
            if(x >= 0 && x < rectangle_number_in_line && y >= 0 && y < rectangle_number_in_column) {
                points[x][y].setFillColor(sf::Color::Black);
                board.set_point_alive(x, y);
            }
        }

        window.clear(sf::Color::White);

        recolor_points(points, board);
        for(int i = 0;i < rectangle_number_in_line;i++){
            draw_rectangles(window, points[i]);
        }
        draw_rectangles(window, gridlines_horizontal);
        draw_rectangles(window, gridlines_vertical);
        button.draw_button(window);
        window.display();

        if(!button.is_start() && iteration % ITERATION_TO_REFRESH == 0){
            board.calculate_next_state();
            board.push_next_state();
            //std::cout << iteration << std::endl;
        }

        if (clock.getElapsedTime().asSeconds() < 1.0f / DESIRED_FPS) {
            sf::Time sleepTime = sf::seconds((1.0f / DESIRED_FPS) - clock.getElapsedTime().asSeconds());
            sleep(sleepTime);
        }
        clock.restart();
        iteration++;
    }

    return EXIT_SUCCESS;
}

void draw_rectangles(sf::RenderWindow &window, const std::vector<sf::RectangleShape> &rectangles) {
    for (const auto &rect: rectangles) {
        window.draw(rect);
    }
}

void make_horizontal_gridlines(std::vector<sf::RectangleShape> &gridlines_horizontal, int size) {
    for (int i = 1; i <= size; i++) {
        sf::RectangleShape rect(sf::Vector2f(WINDOW_WIDTH, 1));
        rect.setPosition(0, i * POINT_SQUARE_SIDE);
        rect.setFillColor(sf::Color::Black);
        gridlines_horizontal.push_back(rect);
    }
}

void make_vertical_gridlines(std::vector<sf::RectangleShape> &gridlines_vertical, int size) {
    for (int i = 1; i < size; i++) {
        sf::RectangleShape rect(sf::Vector2f(1, WINDOW_HEIGHT - BUTTON_SPACE));
        rect.setPosition(i * POINT_SQUARE_SIDE, 0);
        rect.setFillColor(sf::Color::Black);
        gridlines_vertical.push_back(rect);
    }
}

void make_points(std::vector<std::vector<sf::RectangleShape>>& points) {
    for (int i = 0; i < WINDOW_WIDTH / POINT_SQUARE_SIDE; i++){
        points.push_back(std::vector<sf::RectangleShape>());
        for(int j = 0;j < (WINDOW_HEIGHT - BUTTON_SPACE) / POINT_SQUARE_SIDE;j++){
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(POINT_SQUARE_SIDE, POINT_SQUARE_SIDE));
            rectangle.setPosition(i * POINT_SQUARE_SIDE, j * POINT_SQUARE_SIDE);
            rectangle.setFillColor(sf::Color::White);
            points[i].push_back(rectangle);
        }
    }
}

void recolor_points(std::vector<std::vector<sf::RectangleShape>>& points, Board& board){
    for(int i = 0;i < WINDOW_WIDTH / POINT_SQUARE_SIDE;i++){
        for(int j = 0;j < (WINDOW_HEIGHT - BUTTON_SPACE) / POINT_SQUARE_SIDE;j++){
            if(board.point_is_alive(i,j)){
                points[i][j].setFillColor(sf::Color::Black);
            }
            else{
                points[i][j].setFillColor(sf::Color::White);
            }
        }
    }
}