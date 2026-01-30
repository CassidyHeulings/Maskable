//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/TextureHolder.hpp"
#include <assert.h>

using namespace sf;
using namespace std;

// make a pointer that points to no location
// GPS coordinate to the object that stores all the textures
TextureHolder* TextureHolder::textureInstance = nullptr;

TextureHolder::TextureHolder() {
    // will exit execution if points to something
    assert(textureInstance==nullptr);
    // assigns the pointer to this instance
    // points to only the only instance of the class all the time
    textureInstance = this;
}
// since this is static, it only has access to its own class
// has no access to this
// cannot directly access non-static members (texture map is non-static)
Texture& TextureHolder::GetTexture(string const &filename) {
    // get a reference to map location using the one instance
    auto& mapReference = textureInstance->textureMap;
    // find the file pairing in the texture map
    auto keyValuePair = mapReference.find(filename);
    // if the file pairing exists in the texture map
    if (keyValuePair != mapReference.end()) {
        // return the texture
        return keyValuePair->second;
    }
    else {
        // create a new pairing of filename to its texture
        auto& texture = mapReference[filename];
        // make the file texture the content
        texture.loadFromFile(filename);
        // return the texture to the calling code
        return texture;
    }
}