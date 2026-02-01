//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/Interactable.hpp"
#include "../Header Files/TextureHolder.hpp"
using namespace sf;
using namespace std;

Interactable::Interactable(int type, FloatRect biomeCoords, int num) : intType{type} {
    timeSinceCollect = 3;
    timeToCollect = 2;
    int x, y;
    if (num == 1) {
        x = (biomeCoords.left + biomeCoords.width) / 3;
        y = (biomeCoords.top + biomeCoords.height) / 3 * 2;
    }
    else {
        x = (biomeCoords.left + biomeCoords.width) / 3 * 2;
        y = (biomeCoords.top + biomeCoords.height) / 3;
    }
    // set texture, type, position of interactable
    if (type == 1) {
        sprite = Sprite(TextureHolder::GetTexture("../Graphics/Tree.png"));
        intType = 1;
    }
    else if (type == 2) {
        sprite = Sprite(TextureHolder::GetTexture("../Graphics/PlayerBack.png"));
        intType = 2;
    }
    sprite.setOrigin(128, 128);
    sprite.setPosition(x, y);
}

Vector2f Interactable::getPosition() {
    return position;
}

int Interactable::interact() {
    // if player can collect
    if (timeSinceCollect >= timeToCollect) {
        timeSinceCollect = 0;
        // collect random number of items to inventory
        return 2;
    }
    else return 0;
}

int Interactable::getType() {
    return intType;
}

Sprite Interactable::getSprite() {
    return sprite;
}

void Interactable::update(float dt) {
    timeSinceCollect += dt;
}