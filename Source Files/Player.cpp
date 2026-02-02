//
// Created by Cassidy Heulings on 1/29/26.
//
#include "../Header Files/Player.hpp"
#include <iostream>
#include "../Header Files/TextureHolder.hpp"
#include "../Header Files/World.hpp"
using namespace sf;

// constructor
Player::Player()
    : speed(START_SPEED) {
    // add all file names into texture list
    textureList.emplace_back("../Graphics/PlayerFront.png");
    textureList.emplace_back("../Graphics/PlayerBack.png");
    textureList.emplace_back("../Graphics/PlayerRight.png");
    textureList.emplace_back("../Graphics/PlayerLeft.png");
    // associate texture with sprite
    sprite = Sprite(TextureHolder::GetTexture(textureList[0]));
    // set origin of sprite to center
    sprite.setOrigin(35,74);

    woodMask = Sprite(TextureHolder::GetTexture("../Graphics/WoodMaskFront.png"));
    woodMask.setOrigin(34,75);
    woodMaskOn = false;

    shroomMask = Sprite(TextureHolder::GetTexture("../Graphics/WoodMaskFront.png"));
    shroomMask.setOrigin(34,75);
    shroomMaskOn = false;

    gemMask = Sprite(TextureHolder::GetTexture("../Graphics/WoodMaskFront.png"));
    gemMask.setOrigin(34,75);
    gemMaskOn = false;

    triMask = Sprite(TextureHolder::GetTexture("../Graphics/WoodMaskFront.png"));
    triMask.setOrigin(34,75);
    triMaskOn = false;

    interRight = false;
    interLeft = false;
    interDown = false;
    interUp = false;
}
// spawns player
void Player::spawn(IntRect worldSize, Vector2f res, int sizeTile, std::vector<FloatRect> interactablePos) {
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
    // store interactable positions
    interactablePositions = interactablePos;
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
int Player::getDirection() {
    return lastFacing;
}
// makes copy of sprite to main function
Sprite Player::getSprite() {
    return sprite;
}

Sprite Player::getMaskSprite(int type) {
    if (type == 1) return woodMask;
    if (type == 3) return shroomMask;
    if (type == 4) return gemMask;
    if (type == 6) return triMask;
}

void Player::toggleMask(bool on, int type) {
    if (type == 1) woodMaskOn = on;
    if (type == 3) shroomMaskOn = on;
    if (type == 4) gemMaskOn = on;
    if (type == 6) triMaskOn = on;
}

void Player::setSpeed() {
    if (shroomMaskOn) speed = START_SPEED * 1.2;
    else if (triMaskOn) speed = START_SPEED * 1.35;
    else speed = START_SPEED;
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
void Player::update(float dt) {
    // update current position
    // figure out angle player is facing
    if (leftPressed && !interLeft) {
        position.x -= speed * dt;
        sprite.setTexture(TextureHolder::GetTexture(textureList[3]));
        lastFacing = -1;
        // masks
        if (woodMaskOn) woodMask.setPosition(position.x - 6, position.y + 1);
        else woodMask.setPosition(-1000, -1000);
        if (shroomMaskOn) shroomMask.setPosition(position.x - 6, position.y + 1);
        else shroomMask.setPosition(-1000, -1000);
        if (gemMaskOn) gemMask.setPosition(position.x - 6, position.y + 1);
        else gemMask.setPosition(-1000, -1000);
        if (triMaskOn) triMask.setPosition(position.x - 6, position.y + 1);
        else triMask.setPosition(-1000, -1000);
    }
    if (rightPressed && !interRight) {
        position.x += speed * dt;
        sprite.setTexture(TextureHolder::GetTexture(textureList[2]));
        lastFacing = -2;
        // masks
        if (woodMaskOn) woodMask.setPosition(position.x + 5, position.y + 1);
        else woodMask.setPosition(-1000, -1000);
        if (shroomMaskOn) shroomMask.setPosition(position.x + 5, position.y + 1);
        else shroomMask.setPosition(-1000, -1000);
        if (gemMaskOn) gemMask.setPosition(position.x + 5, position.y + 1);
        else gemMask.setPosition(-1000, -1000);
        if (triMaskOn) triMask.setPosition(position.x + 5, position.y + 1);
        else triMask.setPosition(-1000, -1000);
    }
    if (upPressed && !interUp) {
        position.y -= speed * dt;
        // only use up texture when going straight up
        if (!(leftPressed || rightPressed)) {
            sprite.setTexture(TextureHolder::GetTexture(textureList[1]));
            lastFacing = 1;
            // masks
            woodMask.setPosition(-1000, -1000);
            shroomMask.setPosition(-1000, -1000);
            gemMask.setPosition(-1000, -1000);
            triMask.setPosition(-1000, -1000);
        }
    }
    if (downPressed && !interDown) {
        position.y += speed * dt;
        // only use down texture when going straight down
        if (!(leftPressed || rightPressed)) {
            sprite.setTexture(TextureHolder::GetTexture(textureList[0]));
            lastFacing = 2;
            // masks
            if (woodMaskOn) woodMask.setPosition(position.x, position.y);
            else woodMask.setPosition(-1000, -1000);
            if (shroomMaskOn) shroomMask.setPosition(position.x, position.y);
            else shroomMask.setPosition(-1000, -1000);
            if (gemMaskOn) gemMask.setPosition(position.x, position.y);
            else gemMask.setPosition(-1000, -1000);
            if (triMaskOn) triMask.setPosition(position.x, position.y);
            else triMask.setPosition(-1000, -1000);
        }
    }

    // if player is stopped, fix texture
    if (!(leftPressed && rightPressed && upPressed && downPressed)) {
        // facing left
        if (lastFacing == -1) {
            sprite.setTexture(TextureHolder::GetTexture(textureList[3]));
            // masks
            if (woodMaskOn) woodMask.setPosition(position.x - 6, position.y + 1);
            else woodMask.setPosition(-1000, -1000);
            if (shroomMaskOn) shroomMask.setPosition(position.x - 6, position.y + 1);
            else shroomMask.setPosition(-1000, -1000);
            if (gemMaskOn) gemMask.setPosition(position.x - 6, position.y + 1);
            else gemMask.setPosition(-1000, -1000);
            if (triMaskOn) triMask.setPosition(position.x - 6, position.y + 1);
            else triMask.setPosition(-1000, -1000);
        }
        // facing right
        else if (lastFacing == -2) {
            sprite.setTexture(TextureHolder::GetTexture(textureList[2]));
            // masks
            if (woodMaskOn) woodMask.setPosition(position.x + 5, position.y + 1);
            else woodMask.setPosition(-1000, -1000);
            if (shroomMaskOn) shroomMask.setPosition(position.x + 5, position.y + 1);
            else shroomMask.setPosition(-1000, -1000);
            if (gemMaskOn) gemMask.setPosition(position.x + 5, position.y + 1);
            else gemMask.setPosition(-1000, -1000);
            if (triMaskOn) triMask.setPosition(position.x + 5, position.y + 1);
            else triMask.setPosition(-1000, -1000);
        }
        // facing up
        else if (lastFacing == 1) {
            sprite.setTexture(TextureHolder::GetTexture(textureList[1]));
        }
        // facing down
        else if (lastFacing == 2) {
            sprite.setTexture(TextureHolder::GetTexture(textureList[0]));
            // masks
            if (woodMaskOn) woodMask.setPosition(position.x, position.y);
            else woodMask.setPosition(-1000, -1000);
            if (shroomMaskOn) shroomMask.setPosition(position.x, position.y);
            else shroomMask.setPosition(-1000, -1000);
            if (gemMaskOn) gemMask.setPosition(position.x, position.y);
            else gemMask.setPosition(-1000, -1000);
            if (triMaskOn) triMask.setPosition(position.x, position.y);
            else triMask.setPosition(-1000, -1000);
        }

    }

    sprite.setPosition(position.x, position.y);
    // keep player in world bounds
    // each size has a wall with dimensions of 1x1 tile size
    // stop player from walking past wall
    if (position.x > world.width - tileSize - 35) position.x = world.width - tileSize - 35;
    if (position.x < world.left + tileSize + 35) position.x = world.left + tileSize + 35;
    // stop player from walking on wall
    if (position.y > world.height - tileSize - 74) position.y = world.height - tileSize - 74;
    // allow player to walk up to wall
    if (position.y < world.top + tileSize) position.y = world.top + tileSize;

    // stop player from walking into ocean
    // horizontal
    if (position.x - 35 < getBiomeRect(5).left + getBiomeRect(5).width
        && getBiomeRect(5).contains(position.x - 35, position.y + 72)) {
        position.x = getBiomeRect(5).left + getBiomeRect(5).width + 35; // right side
    }
    else if (position.x + 35 > getBiomeRect(5).left
        && getBiomeRect(5).contains(position.x + 35, position.y + 72)) {
        position.x = getBiomeRect(5).left - 35; // left side
    }
    // vertical
    if (position.y < getBiomeRect(5).top + getBiomeRect(5).height
        && (getBiomeRect(5).contains(position.x + 32, position.y - 74)
        || getBiomeRect(5).contains(position.x - 32, position.y - 74))) {
        position.y = getBiomeRect(5).top + getBiomeRect(5).height; // bottom side
    }
    else if (position.y + 74 > getBiomeRect(5).top
        && (getBiomeRect(5).contains(position.x + 32, position.y + 74)
        || getBiomeRect(5).contains(position.x - 32, position.y + 74))) {
        position.y = getBiomeRect(5).top - 74; // top side
    }

    // stop player from walking into interactable
    // horizontal
    for (auto& interactableItem : interactablePositions) {
        if (position.x - 35 < interactableItem.left + interactableItem.width
           && interactableItem.contains(position.x - 35, position.y + 72)) {
            position.x = interactableItem.left + interactableItem.width + 35; // right side
           }
        else if (position.x + 35 > interactableItem.left
            && interactableItem.contains(position.x + 35, position.y + 72)) {
            position.x = interactableItem.left - 35; // left side
            }
        // vertical
        if (position.y < interactableItem.top + interactableItem.height
            && (interactableItem.contains(position.x + 32, position.y - 74)
            || interactableItem.contains(position.x - 32, position.y - 74))) {
            position.y = interactableItem.top + interactableItem.height; // bottom side
            }
        else if (position.y + 74 > interactableItem.top
            && (interactableItem.contains(position.x + 32, position.y + 74)
            || interactableItem.contains(position.x - 32, position.y + 74))) {
            position.y = interactableItem.top - 74; // top side
            }
    }

}