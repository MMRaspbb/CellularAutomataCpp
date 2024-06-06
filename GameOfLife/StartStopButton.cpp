#include "StartStopButton.h"
#include<iostream>

StartStopButton::StartStopButton(int x, int y) {
    this->x = x;
    this->y = y;

    rectangle.setPosition(x - width/2, y - height/2);
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setFillColor(sf::Color::Blue);

    if(!font.loadFromFile("..\\resources\\DejaVuSans-Bold.ttf")){
        std::cout << "Failed to load font" << std::endl;
    }

    text.setFont(font);
    text.setString("start");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    sf::Vector2 text_size = text.getLocalBounds().getSize();
    text.setPosition(x - text_size.x/2, y -text_size.y/2);
}

bool StartStopButton::is_point_in_button(sf::Vector2i vector) {
    if(vector.x > this->x - width/2 && vector.x < this->x + width/2 && vector.y > this->y - height/2 && vector.y < this->y + height/2){
        return true;
    }
    return false;
}

void StartStopButton::switch_text() {
    if(text.getString() == "start"){
        text.setString("stop");
    } else{
        text.setString("start");

    }
    sf::Vector2 text_size = text.getLocalBounds().getSize();
    text.setPosition(x - text_size.x/2, y -text_size.y/2);
}

void StartStopButton::draw_button(sf::RenderWindow& window) {
    window.draw(rectangle);
    window.draw(text);
}

bool StartStopButton::is_start() {
    if(text.getString() == "start"){
        return true;
    }
    return false;
}