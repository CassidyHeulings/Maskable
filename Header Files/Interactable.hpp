//
// Created by Cassidy Heulings on 1/30/26.
//

#pragma once
#include <SFML/Graphics.hpp>

class Interactable {
public:
    Interactable(int type, sf::FloatRect biomeCoords, int num); // prepare interactable
    sf::Vector2f getPosition();
    void increaseCollectSpeed(bool wearingMask);
    int interact(bool wearingMask);
    int getType();
    sf::Sprite getSprite();
    void update(float dt);
private:
    int intType;
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::IntRect worldCoords;
    // making sure time in between collection
    float timeSinceCollect;
    float BASE_COLLECT_SPEED = 2;
    float timeToCollect;
    bool interacting = false;
};