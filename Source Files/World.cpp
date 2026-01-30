//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/World.hpp"
using namespace sf;

// editing background in main
int createBackground(VertexArray& va, IntRect world) {
    // tile info
    const int TILE_SIZE = 128; // size in pixels
    const int SHEET_WIDTH = 4; // width of sheet in tiles
    const int VERTS_IN_QUAD = 4;
    // world size in number of tiles
    int worldWidth = world.width / TILE_SIZE;
    int worldHeight = world.height / TILE_SIZE;
    // type of primitive - how to interpret vertices
    va.setPrimitiveType(Quads); // shape with 4 vertices
    // set the size of the background
    // area of tiles multiplied by 4 vertices/tile
    // number of vertices the array will have when done preparing
    va.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

    // Start at the beginning of the vertex array
    int currVertex = 0;
    // TODO randomize for biome
    // randomize tile type
    //srand((int)time(nullptr));
    // position each vertex in current quad
    for (int w = 0; w < worldWidth; w++) {
        for (int h = 0; h < worldHeight; h++) {
            // set coordinates of vertices
            // upper left
            va[currVertex].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            // upper right corner
            va[currVertex + 1].position = Vector2f(w * TILE_SIZE + TILE_SIZE, h * TILE_SIZE);
            // bottom right corner
            va[currVertex + 2].position = Vector2f(w * TILE_SIZE + TILE_SIZE, h * TILE_SIZE + TILE_SIZE);
            // bottom left corner
            va[currVertex + 3].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE + TILE_SIZE);

            // define position in texture for current quad
            // use wall texture for border tiles
            if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {
                // assign texture coords to vertices
                va[currVertex].texCoords = Vector2f((SHEET_WIDTH - 1) * TILE_SIZE, SHEET_WIDTH * TILE_SIZE);
                va[currVertex + 1].texCoords = Vector2f(SHEET_WIDTH * TILE_SIZE, SHEET_WIDTH * TILE_SIZE);
                va[currVertex + 2].texCoords = Vector2f( SHEET_WIDTH * TILE_SIZE, (SHEET_WIDTH - 1) * TILE_SIZE);
                va[currVertex + 3].texCoords = Vector2f((SHEET_WIDTH - 1) * TILE_SIZE, (SHEET_WIDTH - 1) * TILE_SIZE);
            }
            // TODO change into biomes
            // use floor texture
            else {
                //int groundType = rand() % SHEET_WIDTH;
                // vertical reference point within sprite sheet dependent on type num
                //int verticalOffset = groundType * TILE_SIZE;
                int verticalOffset = 3 * TILE_SIZE;
                // assign texture coords to vertices
                va[currVertex].texCoords = Vector2f(0, verticalOffset);
                va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, verticalOffset);
                va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, verticalOffset + TILE_SIZE);
                va[currVertex + 3].texCoords = Vector2f(0, verticalOffset + TILE_SIZE);
            }
            // move onto next set of vertices for next tile
            currVertex += VERTS_IN_QUAD;
        }
    }
    return TILE_SIZE;
}