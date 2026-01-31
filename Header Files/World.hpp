//
// Created by Cassidy Heulings on 1/30/26.
//

#pragma once
#include <SFML/Graphics.hpp>

// receive a background and arena dimensions
int createBackground(sf::VertexArray& va, sf::IntRect arena);
sf::FloatRect getBiomeRect(int type);