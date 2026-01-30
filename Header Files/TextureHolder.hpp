//
// Created by Cassidy Heulings on 1/30/26.
//

#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
public:
    TextureHolder();
    // returns reference to the location of the texture
    static sf::Texture& GetTexture(std::string const& filename);
private:
    // map container that holds related pairs of String and Texture
    std::map<std::string, sf::Texture> textureMap;
    // points to the single instance of the class that stores the map
    static TextureHolder* textureInstance; // the only instance
};
#endif