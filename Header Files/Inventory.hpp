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
    sf::Sprite getMaskSprite(int type);
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
    int shroomNum;
    bool shroomMaskSelected;
    int shroomMaskCrafted;
    int gemNum;
    bool gemMaskSelected;
    int gemMaskCrafted;
    int triMaskCrafted;
    bool triMaskSelected;
    int maxHold; // max number for items
    sf::Sprite woodMaskSprite;
    sf::Sprite shroomMaskSprite;
    sf::Sprite gemMaskSprite;
    sf::Sprite triMaskSprite;
    sf::Sprite selectionSprite;
    std::string woodMaskText = "A wooden mask\n\nIncreases resource\n collection by 1\n\nCost: 10 wood";
    std::string shroomMaskText = "A mushroom mask\n\nIncreases player\n speed by 20%\n\nCost: 10 mushrooms";
    std::string gemMaskText = "A gem mask\n\nIncreases resource\n collection speed\n by 50%\n\nCost: 15 gems";
    std::string triMaskText = "The Trifold Mask\n\nIncreases resource\n collection by 3\nIncreases player\n speed by 30%\nIncreases resource\n collection speed\n by 75%\n\nCost: 30 wood\n      30 mushrooms\n      30 gems";
};