//
// Created by Cassidy Heulings on 1/30/26.
//

#include "../Header Files/World.hpp"

#include <iostream>
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
    //srand((int)time(nullptr));

    // TODO change into biomes
    // make sure the following calculations are in terms of tiles:

    // while we are at 5 tiles less than width/height
    // generate random number for biome type
    // generate random number for height and width of biome
    // store in int rect the coords of the biome for setting textures
    // *this int rect should be a var with a getter in class so game can access where to place interactive sprites
    // on final 5 biomes, check that each biome was used at least once
    // if not, generate that biome then continue

    // divide int rect into tiles
    // set border tiles the same way we did with wall
    // set all in between tiles
    // ensure we are transforming tiles as necessary (reversed or upside down if allowed)

    // set biome locations
    IntRect grassZone = IntRect(1, 1, 9, 7);
    IntRect sandZone = IntRect(10, 1, 9, 7);
    IntRect waterZone = IntRect(3, 3, 8, 6); // TODO Fix
    IntRect mushroomZone = IntRect(1, 8, 9, 6);
    IntRect stoneZone = IntRect(10, 8, 9, 6);

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
            // border textures
            if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {
                // assign texture coords to vertices
                va[currVertex].texCoords = Vector2f((SHEET_WIDTH - 1) * TILE_SIZE, SHEET_WIDTH * TILE_SIZE);
                va[currVertex + 1].texCoords = Vector2f(SHEET_WIDTH * TILE_SIZE, SHEET_WIDTH * TILE_SIZE);
                va[currVertex + 2].texCoords = Vector2f( SHEET_WIDTH * TILE_SIZE, (SHEET_WIDTH - 1) * TILE_SIZE);
                va[currVertex + 3].texCoords = Vector2f((SHEET_WIDTH - 1) * TILE_SIZE, (SHEET_WIDTH - 1) * TILE_SIZE);
            }
            // use grass texture
            else if (h >= grassZone.top && h < grassZone.top + grassZone.height
                && w >= grassZone.left && w < grassZone.left + grassZone.width) {
                // top left corner
                if (h == grassZone.top && w == grassZone.left) {
                    va[currVertex].texCoords = Vector2f(0, 0);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 0);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(0, TILE_SIZE);
                }
                // top right
                else if (h == grassZone.top && w == grassZone.width) {
                    va[currVertex + 1].texCoords = Vector2f(0, 0);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, 0);
                    va[currVertex + 3].texCoords = Vector2f( TILE_SIZE, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(0, TILE_SIZE);
                }
                // bottom left
                else if (h == grassZone.height && w == grassZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(0, 0);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE, 0);
                    va[currVertex + 1].texCoords = Vector2f( TILE_SIZE, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(0, TILE_SIZE);
                }
                // bottom right
                else if (h == grassZone.height && w == grassZone.width) {
                    va[currVertex + 2].texCoords = Vector2f(0, 0);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, 0);
                    va[currVertex + 0].texCoords = Vector2f( TILE_SIZE, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(0, TILE_SIZE);
                }
                // top side
                else if (h == grassZone.top) {
                    va[currVertex].texCoords = Vector2f(TILE_SIZE, 0);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE * 2, 0);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                }
                // bottom side
                else if (h == grassZone.height) {
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, 0);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE * 2, 0);
                    va[currVertex + 0].texCoords = Vector2f( TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                }
                // left side
                else if (w == grassZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, 0);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE * 2, 0);
                    va[currVertex + 1].texCoords = Vector2f( TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                }
                // right side
                else if (w == grassZone.width) {
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 0);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE * 2, 0);
                    va[currVertex + 3].texCoords = Vector2f( TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                }
                // middle
                else {
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE * 2, 0);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE * 3, 0);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE * 3, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                }
            }
            // use water texture
            else if (h >= waterZone.top && h < waterZone.top + waterZone.height
                && w >= waterZone.left && w < waterZone.left + waterZone.width) {
                // top left corner
                if (h == waterZone.top && w == waterZone.left) {
                    va[currVertex].texCoords = Vector2f(0, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(0, 2 * TILE_SIZE);
                }
                // top right
                else if (h == waterZone.top && w == waterZone.width) {
                    va[currVertex + 1].texCoords = Vector2f(0, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f( TILE_SIZE,  2 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(0, 2 * TILE_SIZE);
                }
                // bottom left
                else if (h == waterZone.height && w == waterZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(0, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f( TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(0, 2 * TILE_SIZE);
                }
                // bottom right
                else if (h == waterZone.height && w == waterZone.width) {
                    va[currVertex + 2].texCoords = Vector2f(0, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f( TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(0, 2 * TILE_SIZE);
                }
                // top side
                else if (h == waterZone.top) {
                    va[currVertex].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE * 2, 2 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, 2 * TILE_SIZE);
                }
                // bottom side
                else if (h == waterZone.height) {
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f( TILE_SIZE * 2, 2 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 2 * TILE_SIZE);
                }
                // left side
                else if (w == waterZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f( TILE_SIZE * 2, 2 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, 2 * TILE_SIZE);
                }
                // right side
                else if (w == waterZone.width) {
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f( TILE_SIZE * 2, 2 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE, 2 * TILE_SIZE);
                }
                // middle
                else {
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE * 3, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE * 3, 2 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE * 2, 2 * TILE_SIZE);
                }
            }
            // use sand texture
            else if (h >= sandZone.top && h < sandZone.top + sandZone.height
                && w >= sandZone.left && w < sandZone.left + sandZone.width) {
                // top left corner
                if (h == sandZone.top && w == sandZone.left) {
                    va[currVertex].texCoords = Vector2f(0, 3 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE, 4 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(0, 4 * TILE_SIZE);
                }
                // top right
                else if (h == sandZone.top && w == sandZone.left + sandZone.width - 1) {
                    va[currVertex + 1].texCoords = Vector2f(0, 3 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f( TILE_SIZE, 4 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(0, 4 * TILE_SIZE);
                }
                // bottom left
                else if (h == sandZone.height && w == sandZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(0, 3 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f( TILE_SIZE, 4 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(0, 4 * TILE_SIZE);
                }
                // bottom right
                else if (h == sandZone.height && w == sandZone.left + sandZone.width - 1) {
                    va[currVertex + 2].texCoords = Vector2f(0, 3 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f( TILE_SIZE, 4 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(0, 4 * TILE_SIZE);
                }
                // top side
                else if (h == sandZone.top) {
                    va[currVertex].texCoords = Vector2f(TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE * 2, 3 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE * 2, 4 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, 4 * TILE_SIZE);
                }
                // bottom side
                else if (h == sandZone.height) {
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE * 2, 3 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f( TILE_SIZE * 2, 4 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 4 * TILE_SIZE);
                }
                // left side
                else if (w == sandZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE * 2, 3 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f( TILE_SIZE * 2, 4 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, 4 * TILE_SIZE);
                }
                // right side
                else if (w == sandZone.left + sandZone.width - 1) {
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE * 2, 3 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f( TILE_SIZE * 2, 4 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE, 4 * TILE_SIZE);
                }
                // middle
                else {
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE * 2, 3 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE * 3, 3 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE * 3, 4 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE * 2, 4 * TILE_SIZE);
                }
            }
            // use mushroom texture
            else if (h >= mushroomZone.top && h < mushroomZone.top + mushroomZone.height
                && w >= mushroomZone.left && w < mushroomZone.left + mushroomZone.width) {
                // top left corner
                if (h == mushroomZone.top && w == mushroomZone.left) {
                    va[currVertex].texCoords = Vector2f(3 * TILE_SIZE, 0);
                    va[currVertex + 1].texCoords = Vector2f(4 * TILE_SIZE, 0);
                    va[currVertex + 2].texCoords = Vector2f( 4 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(3 * TILE_SIZE, TILE_SIZE);
                }
                // top right
                else if (h == mushroomZone.top && w == mushroomZone.width) {
                    va[currVertex + 1].texCoords = Vector2f(3 * TILE_SIZE, 0);
                    va[currVertex + 2].texCoords = Vector2f(4 * TILE_SIZE, 0);
                    va[currVertex + 3].texCoords = Vector2f( 4 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(3 * TILE_SIZE, TILE_SIZE);
                }
                // bottom left
                else if (h == mushroomZone.top + mushroomZone.height - 1 && w == mushroomZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(3 * TILE_SIZE, 0);
                    va[currVertex + 0].texCoords = Vector2f(4 * TILE_SIZE, 0);
                    va[currVertex + 1].texCoords = Vector2f( 4 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(3 * TILE_SIZE, TILE_SIZE);
                }
                // bottom right
                else if (h == mushroomZone.top + mushroomZone.height - 1 && w == mushroomZone.left + mushroomZone.width - 1) {
                    va[currVertex + 2].texCoords = Vector2f(3 * TILE_SIZE, 0);
                    va[currVertex + 3].texCoords = Vector2f(4 * TILE_SIZE, 0);
                    va[currVertex + 0].texCoords = Vector2f( 4 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(3 * TILE_SIZE, TILE_SIZE);
                }
                // top side
                else if (h == mushroomZone.top) {
                    va[currVertex].texCoords = Vector2f(3 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(4 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( 4 * TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(3 * TILE_SIZE, 2 * TILE_SIZE);
                }
                // bottom side
                else if (h == mushroomZone.top + mushroomZone.height - 1) {
                    va[currVertex + 2].texCoords = Vector2f(3 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(4 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f( 4 * TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(3 * TILE_SIZE, 2 * TILE_SIZE);
                }
                // left side
                else if (w == mushroomZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(3 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(4 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f( 4 * TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(3 * TILE_SIZE, 2 * TILE_SIZE);
                }
                // right side
                else if (w == mushroomZone.left + mushroomZone.width - 1) {
                    va[currVertex + 1].texCoords = Vector2f(3 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(4 * TILE_SIZE, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f( 4 * TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(3 * TILE_SIZE, 2 * TILE_SIZE);
                }
                // middle
                else {
                    va[currVertex + 0].texCoords = Vector2f(3 * TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(4 * TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( 4 * TILE_SIZE, 3 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(3 * TILE_SIZE, 3 * TILE_SIZE);
                }
            }
            // use stone texture
            else if (h >= stoneZone.top && h < stoneZone.top + stoneZone.height
                && w >= stoneZone.left && w < stoneZone.left + stoneZone.width) {
                // top left corner
                if (h == stoneZone.top && w == stoneZone.left) {
                    va[currVertex].texCoords = Vector2f(0, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(0, 2 * TILE_SIZE);
                }
                // top right
                else if (h == stoneZone.top && w == stoneZone.left + stoneZone.width - 1) {
                    va[currVertex + 1].texCoords = Vector2f(0, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f( TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(0, 2 * TILE_SIZE);
                }
                // bottom left
                else if (h == stoneZone.top + stoneZone.height - 1 && w == stoneZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(0, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f( TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(0, 2 * TILE_SIZE);
                }
                // bottom right
                else if (h == stoneZone.top + stoneZone.height - 1 && w == stoneZone.left + stoneZone.width - 1) {
                    va[currVertex + 2].texCoords = Vector2f(0, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f( TILE_SIZE, 2 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(0, 2 * TILE_SIZE);
                }
                // top side
                else if (h == stoneZone.top) {
                    va[currVertex].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE * 2, 2 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, 2 * TILE_SIZE);
                }
                // bottom side
                else if (h == stoneZone.top + stoneZone.height - 1) {
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f( TILE_SIZE * 2, 2 * TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, 2 * TILE_SIZE);
                }
                // left side
                else if (w == stoneZone.left) {
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f( TILE_SIZE * 2, 2 * TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE, 2 * TILE_SIZE);
                }
                // right side
                else if (w == stoneZone.left + stoneZone.width - 1) {
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f( TILE_SIZE * 2, 2 * TILE_SIZE);
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE, 2 * TILE_SIZE);
                }
                // middle
                else {
                    va[currVertex + 0].texCoords = Vector2f(TILE_SIZE * 2, TILE_SIZE);
                    va[currVertex + 1].texCoords = Vector2f(TILE_SIZE * 3, TILE_SIZE);
                    va[currVertex + 2].texCoords = Vector2f( TILE_SIZE * 3, 2 * TILE_SIZE);
                    va[currVertex + 3].texCoords = Vector2f(TILE_SIZE * 2, 2 * TILE_SIZE);
                }
            }
            // move onto next set of vertices for next tile
            currVertex += VERTS_IN_QUAD;
        }
    }
    return TILE_SIZE;
}