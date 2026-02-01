//
// Created by Cassidy Heulings on 1/30/26.
//

#pragma once
#include <SFML/Graphics.hpp>

class Inventory {
public:
    Inventory(); // prepare a new inventory
    void collect(int type, int amount); // add item to inventory
    int getItemCount(int type);
    void setItemCount(int type, int amount);
    sf::IntRect getMaskCoords(int type, sf::Vector2f centerView);
    void setMaskSelected(bool selected, int type);
    bool getMaskSelected(int type);
    void makeMask(int type);
    bool isMaskCrafted(int type);
    sf::Sprite getSprite();
    sf::Sprite getMaskSprite();
    sf::Sprite getSelectionSprite();
    void setInvPosition(sf::Vector2f position);
    void setSelectionPosition(sf::Vector2f position);
    void setMaskPosition(sf::Vector2f position);
    std::string getMaskText(int type);
    int getMaskCount(int type);
private:
    // number of items
    sf::Sprite inventorySprite;
    int woodNum;
    bool woodMaskSelected;
    int woodMaskCrafted;
    int maxHold; // max number for items
    sf::Sprite woodMaskSprite;
    sf::Sprite selectionSprite;
    std::string woodMaskText = "A wooden mask\nIncreases resource\ncollection by 1\n\nCost: 10 wood";
};