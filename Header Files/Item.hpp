//
// Created by Cassidy Heulings on 1/30/26.
//

#pragma once
#include <SFML/Graphics.hpp>

class Item {
public:
    Item(int type); // prepare new item
    sf::Sprite getSprite();
private:
    int type;
    sf::Sprite sprite;
};