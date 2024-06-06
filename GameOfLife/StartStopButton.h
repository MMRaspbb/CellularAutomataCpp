#ifndef GAMEOFLIFE_STARTSTOPBUTTON_H
#define GAMEOFLIFE_STARTSTOPBUTTON_H

#include <SFML/Graphics.hpp>

class StartStopButton {
private:
    sf::RectangleShape rectangle;
    const int height = 60;
    const int width = 120;
    int x;
    int y;
    sf::Text text;
    sf::Font font;
public:
    StartStopButton(int, int);
    bool is_point_in_button(sf::Vector2i);
    void switch_text();
    void draw_button(sf::RenderWindow&);
    bool is_start();
};


#endif //GAMEOFLIFE_STARTSTOPBUTTON_H
