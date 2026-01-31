//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/Inventory.hpp"

#include <iostream>

Inventory::Inventory() {
    woodNum = 0;
    maxHold = 300;
}

void Inventory::collect(int type, int amount) {
    if (type == 1 && woodNum < maxHold) {
        woodNum += amount;
        if (woodNum > maxHold) woodNum = maxHold;
        std::cout << "You collected " << woodNum << " of " << maxHold << std::endl;
    }
}

int Inventory::getItemCount(int type) {
    if (type == 1) {
        return woodNum;
    }
    else
        return 0;
}
