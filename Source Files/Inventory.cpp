//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/Inventory.hpp"
#include "../Header Files/TextureHolder.hpp"
#include <iostream>
using namespace sf;

Inventory::Inventory() {
    woodNum = 0;
    shroomNum = 0;
    gemNum = 0;
    maxHold = 300;

    woodMaskSelected = false;
    woodMaskCrafted = 0;
    shroomMaskSelected = false;
    shroomMaskCrafted = 0;
    gemMaskSelected = false;
    gemMaskCrafted = 0;
    triMaskSelected = false;
    triMaskCrafted = 0;

    inventorySprite.setTexture(TextureHolder::GetTexture("../Graphics/Inventory.png"));
    inventorySprite.setOrigin(256, 256);
    woodMaskSprite.setTexture(TextureHolder::GetTexture("../Graphics/WoodMask.png"));
    woodMaskSprite.setOrigin(70, 75);
    shroomMaskSprite.setTexture(TextureHolder::GetTexture("../Graphics/ShroomMask.png"));
    shroomMaskSprite.setOrigin(70, 75);
    gemMaskSprite.setTexture(TextureHolder::GetTexture("../Graphics/GemMask.png"));
    gemMaskSprite.setOrigin(70, 75);
    triMaskSprite.setTexture(TextureHolder::GetTexture("../Graphics/TriMask.png"));
    triMaskSprite.setOrigin(70, 75);
    selectionSprite.setTexture(TextureHolder::GetTexture("../Graphics/Selection.png"));
    selectionSprite.setOrigin(256, 256);
}

void Inventory::collect(int type, int amount) {
    if (type == 1 && woodNum < maxHold) {
        woodNum += amount;
        if (woodNum > maxHold) woodNum = maxHold;
    }
    else if (type == 3 && shroomNum < maxHold) {
        shroomNum += amount;
        if (shroomNum > maxHold) shroomNum = maxHold;
    }
    else if (type == 4 && gemNum < maxHold) {
        gemNum += amount;
        if (gemNum > maxHold) gemNum = maxHold;
    }
}

int Inventory::getItemCount(int type) {
    if (type == 1) return woodNum;
    if (type == 3) return shroomNum;
    if (type == 4) return gemNum;
    return 0;
}

void Inventory::setItemCount(int type, int amount) {
    if (type == 1) {
        woodNum -= amount;
        if (woodNum < 0) woodNum = 0;
    }
    if (type == 3) {
        shroomNum -= amount;
        if (shroomNum < 0) shroomNum = 0;
    }
    if (type == 4) {
        gemNum -= amount;
        if (gemNum < 0) gemNum = 0;
    }
}

IntRect Inventory::getMaskCoords(int type, Vector2f centerView) {
    if (type == 1) { // wood mask
        return IntRect(centerView.x - 105, centerView.y + 45, 135,135);
    }
    if (type == 3) { // shroom mask
        return IntRect(centerView.x + 110, centerView.y + 45, 135,140);
    }
    if (type == 4) { // gem mask
        return IntRect(centerView.x - 105, centerView.y + 250, 135,150);
    }
    if (type == 6) { // tri mask
        return IntRect(centerView.x + 110, centerView.y + 250, 135,150);
    }
}

void Inventory::setMaskSelected(bool selected, int type) {
    if (type == 1) woodMaskSelected = selected;
    else if (type == 3) shroomMaskSelected = selected;
    else if (type == 4) gemMaskSelected = selected;
    else if (type == 6) triMaskSelected = selected;
}

bool Inventory::getMaskSelected(int type) {
    if (type == 1) return woodMaskSelected;
    if (type == 3) return shroomMaskSelected;
    if (type == 4) return gemMaskSelected;
    if (type == 6) return triMaskSelected;
}

void Inventory::makeMask(int type) {
    if (type == 1) woodMaskCrafted++;
    else if (type == 3) shroomMaskCrafted++;
    else if (type == 4) gemMaskCrafted++;
    else if (type == 6) triMaskCrafted++;
}

bool Inventory::isMaskCrafted(int type) {
    bool crafted = false;
    if (type == 1 && woodMaskCrafted >= 1) crafted = true;
    if (type == 3 && shroomMaskCrafted >= 1) crafted = true;
    if (type == 4 && gemMaskCrafted >= 1) crafted = true;
    if (type == 6 && triMaskCrafted >= 1) crafted = true;
    return crafted;
}

Sprite Inventory::getSprite() {
    return inventorySprite;
}

Sprite Inventory::getMaskSprite(int type) {
    if (type == 1) return woodMaskSprite;
    if (type == 3) return shroomMaskSprite;
    if (type == 4) return gemMaskSprite;
    if (type == 6) return triMaskSprite;
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
    woodMaskSprite.setPosition(position.x - 105, position.y - 112);
    shroomMaskSprite.setPosition(position.x + 113, position.y - 107);
    gemMaskSprite.setPosition(position.x - 105, position.y + 100);
    triMaskSprite.setPosition(position.x + 112, position.y + 97);
}

std::string Inventory::getMaskText(int type) {
    if (type == 1) return woodMaskText;
    if (type == 3) return shroomMaskText;
    if (type == 4) return gemMaskText;
    if (type == 6) return triMaskText;
}

int Inventory::getMaskCount(int type) {
    if (type == 1) return woodMaskCrafted;
    if (type == 3) return shroomMaskCrafted;
    if (type == 4) return gemMaskCrafted;
    if (type == 6) return triMaskCrafted;
    return 0;
}

