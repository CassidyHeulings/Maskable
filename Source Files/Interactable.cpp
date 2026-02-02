//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/Interactable.hpp"
#include "../Header Files/TextureHolder.hpp"
using namespace sf;
using namespace std;

Interactable::Interactable(int type, FloatRect biomeCoords, int num) : intType{type} {
    timeSinceCollect = 3;
    timeToCollect = BASE_COLLECT_SPEED;
    int x, y;
    if (num == 1) {
        x = biomeCoords.left + biomeCoords.width / 5;
        y = biomeCoords.top + biomeCoords.height / 5;
    }
    else if (num == 2) {
        x = biomeCoords.left + biomeCoords.width / 5 * 4;
        y = biomeCoords.top + biomeCoords.height / 3;
    }
    else {
        x = biomeCoords.left + biomeCoords.width / 5 * 2;
        y = biomeCoords.top + biomeCoords.height / 4 * 3;
    }
    // set texture, type, position of interactable
    if (type == 1) {
        sprite = Sprite(TextureHolder::GetTexture("../Graphics/Tree.png"));
        intType = 1;
    }
    else if (type == 3) {
        sprite = Sprite(TextureHolder::GetTexture("../Graphics/Mushroom.png"));
        intType = 3;
    }
    else if (type == 4) {
        sprite = Sprite(TextureHolder::GetTexture("../Graphics/Tree.png"));
        intType = 4;
    }
    sprite.setOrigin(128, 128);
    sprite.setPosition(x, y);
}

Vector2f Interactable::getPosition() {
    return position;
}

void Interactable::increaseCollectSpeed(float factor) {
    timeToCollect = BASE_COLLECT_SPEED * factor;
}

int Interactable::interact(int amount) {
    // if player can collect
    if (timeSinceCollect >= timeToCollect) {
        timeSinceCollect = 0;
        return amount;
    }
    return 0;
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