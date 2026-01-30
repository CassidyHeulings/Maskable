//
// Created by Cassidy Heulings on 1/29/26.
//

#include "../Header Files/Player.hpp"
#include <cmath>

using namespace sf;

// constructor
Player::Player()
    : speed(START_SPEED),
      texture(),
      sprite() {
    // associate texture with sprite
    // TODO change file name
    texture.loadFromFile("../Graphics/player.png");
    sprite.setTexture(texture);
    // set origin of sprite to center for smooth rotation
    sprite.setOrigin(64,64);
}
// spawns player
void Player::spawn(IntRect worldSize, Vector2f res, int sizeTile) {
    // place player in middle of arena
    position.x = worldSize.width / 2;
    position.y = worldSize.height / 2;
    // copy details of arena to players arena
    world.left = worldSize.left;
    world.top = worldSize.top;
    world.width = worldSize.width;
    world.height = worldSize.height;
    // remember tile size
    tileSize = sizeTile;
    // store resolution
    resolution.x = res.x;
    resolution.y = res.y;
}
// reset stats at end of every game
void Player::resetPlayerStats() {
    speed = START_SPEED;
}

// players current position
FloatRect Player::getPosition() {
    return sprite.getGlobalBounds();
}
// center of player
Vector2f Player::getCenter() {
    return position;
}
// direction player is facing
Vector2i Player::getDirection() {
    return lastFacing;
}
// makes copy of sprite to main function
Sprite Player::getSprite() {
    return sprite;
}
// player movement
// informs which keys were pressed
void Player::moveLeft() {
    leftPressed = true;
}
void Player::moveRight() {
    rightPressed = true;
}
void Player::moveUp() {
    upPressed = true;
}
void Player::moveDown() {
    downPressed = true;
}
// stop player moving in that direction
// informs which keys weren't pressed
void Player::stopLeft() {
    leftPressed = false;
}
void Player::stopRight() {
    rightPressed = false;
}
void Player::stopUp() {
    upPressed = false;
}
void Player::stopDown() {
    downPressed = false;
}
// update player every frame
void Player::update(float dt, Vector2i mousePos) {
    // update current position
    // figure out angle player is facing player is facing
    if (leftPressed) {
        position.x -= speed * dt;
        lastFacing.x = -1;
    }
    if (rightPressed) {
        position.x += speed * dt;
        lastFacing.x = 1;
    }
    if (upPressed) {
        position.y -= speed * dt;
        lastFacing.y = -1;
    }
    if (downPressed) {
        position.y += speed * dt;
        lastFacing.y = 1;
    }
    sprite.setPosition(position.x, position.y);
    // keep player in world bounds
    // each size has a wall with dimensions of 1x1 tile size
    if (position.x > world.width - tileSize) position.x = world.width - tileSize;
    if (position.x < world.left + tileSize) position.x = world.left + tileSize;
    if (position.y > world.height - tileSize) position.y = world.height - tileSize;
    if (position.y < world.top + tileSize) position.y = world.top + tileSize;
}