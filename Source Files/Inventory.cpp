//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/Inventory.hpp"
#include "../Header Files/TextureHolder.hpp"
#include <iostream>
using namespace sf;

Inventory::Inventory() {
    woodNum = 0;
    maxHold = 300;
    woodMaskSelected = false;
    woodMaskCrafted = 0;
    inventorySprite.setTexture(TextureHolder::GetTexture("../Graphics/Inventory.png"));
    inventorySprite.setOrigin(256, 256);
    maskSprite.setTexture(TextureHolder::GetTexture("../Graphics/WoodMask.png"));
    maskSprite.setOrigin(70, 75);
    selectionSprite.setTexture(TextureHolder::GetTexture("../Graphics/Selection.png"));
    selectionSprite.setOrigin(256, 256);
}

void Inventory::collect(int type, int amount) {
    if (type == 1 && woodNum < maxHold) {
        woodNum += amount;
        if (woodNum > maxHold) woodNum = maxHold;
    }
}

int Inventory::getItemCount(int type) {
    if (type == 1) {
        return woodNum;
    }
    else
        return 0;
}

void Inventory::setItemCount(int type, int amount) {
    if (type == 1) {
        woodNum -= amount;
        if (woodNum < 0) woodNum = 0;
    }
}

IntRect Inventory::getMaskCoords(int type, Vector2f centerView) {
    if (type == 1) { // wood mask
        return IntRect(centerView.x - 105, centerView.y + 45, 135,135);
    }
}

void Inventory::setMaskSelected(bool selected, int type) {
    if (type == 1) { // wood mask
        woodMaskSelected = selected;
    }
}

bool Inventory::getMaskSelected(int type) {
    if (type == 1) { // wood mask
        return woodMaskSelected;
    }
}

void Inventory::makeMask(int type) {
    if (type == 1) {
        woodMaskCrafted++;
    }
}

bool Inventory::isMaskCrafted(int type) {
    bool crafted = false;
    if (type == 1) {
        if (woodMaskCrafted >= 1) crafted = true;
    }
    return crafted;
}

Sprite Inventory::getSprite() {
    return inventorySprite;
}

Sprite Inventory::getMaskSprite() {
    return maskSprite;
}

Sprite Inventory::getSelectionSprite() {
    return selectionSprite;
}

void Inventory::setInvPosition(Vector2f position) {
    inventorySprite.setPosition(position);
}

void Inventory::setSelectionPosition(Vector2f position) {
    selectionSprite.setPosition(position);
}

void Inventory::setMaskPosition(Vector2f position) {
    maskSprite.setPosition(position);
}

std::string Inventory::getMaskText(int type) {
    if (type == 1) {
        return woodMaskText;
    }
}

int Inventory::getMaskCount(int type) {
    if (type == 1) {
        return woodMaskCrafted;
    }
    return 0;
}

