//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/Interactable.hpp"
#include "../Header Files/TextureHolder.hpp"
using namespace sf;
using namespace std;

Interactable::Interactable(int type, FloatRect biomeCoords) : intType{type} {
    timeSinceCollect = 3;
    timeToCollect = 2;
    srand((int)time(0) / type);
    int x = rand() % static_cast<int>(biomeCoords.width - 100) + static_cast<int>(biomeCoords.left + 100);
    srand((int)time(0) * type);
    int y = rand() % static_cast<int>(biomeCoords.height - 100) + static_cast<int>(biomeCoords.top + 100);
    // set texture, type, position of interactable
    if (type == 1) {
        sprite = Sprite(TextureHolder::GetTexture("../Graphics/PlayerFront.png"));
        intType = 1;
    }
    else if (type == 2) {
        sprite = Sprite(TextureHolder::GetTexture("../Graphics/PlayerBack.png"));
        intType = 2;
    }
    sprite.setOrigin(35, 74);
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