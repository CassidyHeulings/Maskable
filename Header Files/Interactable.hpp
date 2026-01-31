//
// Created by Cassidy Heulings on 1/30/26.
//

#pragma once
#include <SFML/Graphics.hpp>

class Interactable {
public:
    Interactable(int type); // prepare interactable
    void setWorld(sf::IntRect worldCoords);
    void interacted(); // player is interacting
    // send list of interactable positions
    std::vector<sf::Vector2f> getPositions(int type);
    sf::Sprite getSprite();
private:
    sf::Sprite sprite;
    sf::IntRect worldCoords;
    // making sure time in between collection
    float timeSinceCollect;
    float timeToCollect;
};