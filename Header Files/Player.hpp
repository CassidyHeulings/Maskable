//
// Created by Cassidy Heulings on 1/29/26.
//
#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void spawn(sf::IntRect worldSize, sf::Vector2f res, int sizeTile);
    void resetPlayerStats(); // call at the end of every game
    sf::FloatRect getPosition(); // players position
    sf::Vector2f getCenter(); // center of player
    sf::Vector2i getDirection(); // direction player is facing
    sf::Sprite getSprite(); // send copy of sprite to main function
    // player movement
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    // stop player moving in specific direction
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    // player update - called once per frame
    void update(float dt);
    // TODO mask effects
private:
    const float START_SPEED = 300;
    sf::Vector2f position; // players current position
    sf::Sprite sprite; // sprite
    sf::Texture texture; // players texture
    sf::Vector2f resolution; // screen resolution
    sf::IntRect world; // size of world
    int tileSize; // size of tiles in world
    // direction player is moving in
    bool upPressed;
    bool downPressed;
    bool leftPressed;
    bool rightPressed;
    // direction player was last facing
    sf::Vector2i lastFacing;
    float speed; // speed in pixels per second
};