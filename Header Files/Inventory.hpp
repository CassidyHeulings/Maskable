//
// Created by Cassidy Heulings on 1/30/26.
//

#pragma once
#include <SFML/Graphics.hpp>

class Inventory {
public:
    Inventory(); // prepare a new inventory
    void collect(int type); // add item to inventory
    void update(); // ??
private:
    // number of items
    int woodNum;
    int maxHold; // max number for items
};