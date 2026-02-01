//
// Created by Cassidy Heulings on 1/29/26.
//
#include <iostream>
#include <sstream>
#include <SFMl/Graphics.hpp>
#include "../Header Files/Player.hpp"
#include "../Header Files/World.hpp"
#include "../Header Files/TextureHolder.hpp"
#include "../Header Files/Interactable.hpp"
#include "../Header Files/Inventory.hpp"
using namespace sf;

/**
 * BIOME & CORRESPONDING ITEM TYPES
 * Grass/wood -> 1
 * Sand -> 2
 * Mushroom -> 3
 * Stone -> 4
 * Water -> 5
*/

//TODO sprite.setPosition for inventory items

int main() {
    // initializing screen/world vars
    // add instance of texture holder
    TextureHolder holder;
    // TODO decide game states
    enum class State { PAUSED, CRAFTING, NEW_GAME, PLAYING, JOURNAL };
    State state = State::NEW_GAME; // start game in paused state

    // create SFML window with screen resolution
    Vector2f resolution;
    resolution.x = VideoMode::getFullscreenModes()[0].width;
    resolution.y = VideoMode::getFullscreenModes()[0].height;
    RenderWindow window(VideoMode::getFullscreenModes()[0],
        "Maskable", Style::Fullscreen);
    // view following character in world
    View mainView(FloatRect(0,0,resolution.x,resolution.y));
    Vector2f viewPosition;

    // Initialize game-wide variables
    Clock clock; // used to time everything
    Vector2f mouseWorldPos; // mouse in relation to world coords
    Vector2i mouseScreenPos; // mouse in relation to screen coords
    Player player; // create instance of player class
    IntRect world; // boundaries of world
    VertexArray background; // create background
    Texture backgroundTexture = TextureHolder::GetTexture("../Graphics/BackgroundSheet.png"); // load texture for background

    // HUD
    View hudView(sf::FloatRect(0, 0, resolution.x,resolution.y));
    Font font;
    font.loadFromFile("../Graphics/Pixel.ttf");
    // paused
    Text pausedText;
    pausedText.setFont(font);
    pausedText.setCharacterSize(100);
    pausedText.setFillColor(Color::White);
    pausedText.setPosition(200, 200);
    pausedText.setString("Press esc \nto continue");
    // wood count
    Text woodText;
    woodText.setFont(font);
    woodText.setCharacterSize(55);
    woodText.setFillColor(Color::White);
    woodText.setPosition(20, 0);
    // time since HUD was updated
    int framesSinceLastHUDUpdate = 0;
    // how often the HUD is updated
    int fpsFrameInterval = 1000;

    // world coords
    world.width = 2560; // 128 * 20
    world.height = 1920; // 128 * 15
    world.left = 0;
    world.top = 0;

    // menu overlays
    RectangleShape dimOverlay;
    dimOverlay.setSize(Vector2f(world.width, world.height));
    dimOverlay.setFillColor(Color(0, 0, 0, 150));

    // create interactable
    Interactable tree(1, getBiomeRect(1));
    bool interacting = false;

    // create inventory
    Inventory inventory = Inventory();
    bool maskCrafted = false;

    // selected
    Sprite selectedSprite;
    selectedSprite.setTexture(TextureHolder::GetTexture("../Graphics/Selection.png"));
    selectedSprite.setOrigin(256,256);

    window.setMouseCursorVisible(false); // hide mouse pointer
    Sprite spriteMouse;
    Texture textureMouse = TextureHolder::GetTexture("../Graphics/Mouse.png");
    spriteMouse.setTexture(textureMouse);

    // game loop
    while (window.isOpen()) {

        /*
         *************
         HANDLE INPUT
         *************
         */

        // Handle events by polling
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseButtonReleased) {
                if (state == State::CRAFTING) {
                    if (event.mouseButton.button == Mouse::Left) {
                        // move sprite to outline the item
                        // cycle through each item and click on specific one
                        if (inventory.getMaskCoords(1, mainView.getCenter()).contains(mouseWorldPos.x + 72, mouseWorldPos.y + 230)) {
                            inventory.setMaskSelected(true, 1);
                        }
                        else inventory.setMaskSelected(false, 1);
                    }
                }
            }
            if (event.type == Event::KeyPressed) {
                switch (state) {
                    case State::PAUSED:
                        switch (event.key.code) {
                        case Keyboard::Escape:
                                state = State::PLAYING;
                                clock.restart();
                                break;
                        case Keyboard::Enter:
                                state = State::NEW_GAME;
                                break;
                        case Keyboard::BackSpace:
                                window.close();
                                break;
                        } break;
                    case State::NEW_GAME: {
                        int sizeTile = createBackground(background, world);
                        player.spawn(world, resolution, sizeTile);
                        state = State::PLAYING;
                        clock.restart();
                        break;
                    }
                    case State::PLAYING:
                        switch (event.key.code) {
                            case Keyboard::Escape:
                                state = State::PAUSED;
                                break;
                            case Keyboard::Enter:
                                interacting = true;
                                break;
                            case Keyboard::E:
                                state = State::CRAFTING;
                                break;
                            }
                            break;
                    case State::CRAFTING:
                        switch (event.key.code) {
                            case Keyboard::Escape:
                                state = State::PLAYING;
                                break;
                            case Keyboard::Enter:
                                // cycle through each mask
                                // check have the items available
                                // craft and add to inventory
                                if (inventory.getMaskSelected(1)) {
                                    if (inventory.getItemCount(1) >= 10) { // wood mask recipe
                                        maskCrafted = true;
                                    }
                                    else maskCrafted = false;
                                }
                                break;
                        }
                        break;
                    case State::JOURNAL:
                        if (event.key.code == Keyboard::Escape) {
                            state = State::PLAYING;
                            clock.restart();
                        }
                        break;
                }
            }

            // real-time key presses (movement)
            if (state == State::PLAYING) {
                if (Keyboard::isKeyPressed(Keyboard::W)) player.moveUp(); else player.stopUp();
                if (Keyboard::isKeyPressed(Keyboard::S)) player.moveDown(); else player.stopDown();
                if (Keyboard::isKeyPressed(Keyboard::A)) player.moveLeft(); else player.stopLeft();
                if (Keyboard::isKeyPressed(Keyboard::D)) player.moveRight(); else player.stopRight();
            } // end movement while playing
        } // end event polling

        /*
        ****************
        UPDATE THE FRAME
        ****************
        */

        // check if state is playing
        if (state == State::PLAYING) {
            // update times
            Time dt = clock.restart(); // update change in time
            float dtAsSeconds = dt.asSeconds(); // convert dt to seconds
            framesSinceLastHUDUpdate++;

            // re-calculate every fpsMeasurementFrameInterval frames
            if (framesSinceLastHUDUpdate > fpsFrameInterval) {
                // update HUD text
                std::stringstream ssWood;
                ssWood << "Wood: " << inventory.getItemCount(1) << "/300";
                woodText.setString(ssWood.str());
                framesSinceLastHUDUpdate = 0;
            }

            // update player
            player.update(dtAsSeconds);
            // update tree
            tree.update(dtAsSeconds);

            // set camera view
            // horizontal
            if (player.getCenter().x < resolution.x / 2) // player is approaching left side
                viewPosition.x = resolution.x / 2;
            else if (player.getCenter().x > world.width - resolution.x / 2) // player is approaching right side
                viewPosition.x = world.width - resolution.x / 2;
            else // player is not at boundary
                viewPosition.x = player.getCenter().x;
            // vertical
            if (player.getCenter().y < resolution.y / 2) // player is approaching top
                viewPosition.y = resolution.y / 2;
            else if (player.getCenter().y > world.height - resolution.y / 2) // player is approaching bottom
                viewPosition.y = world.height - resolution.y / 2;
            else // player is not at boundary
                viewPosition.y = player.getCenter().y;

            // make view centered around player
            mainView.setCenter(viewPosition);

            // interactable collecting
            if (interacting && player.getPosition().intersects(tree.getSprite().getGlobalBounds())) {
                inventory.collect(1, tree.interact());
                interacting = false;
            }

            // TODO change interactable width and height
            // stop player from walking into interactable

            /**
            if (player.getPosition().left - 35 < tree.getPosition().x + 35 // right side
                && tree.getSprite().getGlobalBounds().contains(player.getPosition().left - 35, player.getPosition().top)) {
                player.intRight();
            }
            else if (player.getPosition().left + 35 > tree.getPosition().x - 35 // left side
                && tree.getSprite().getGlobalBounds().contains(player.getCenter().x + 35, player.getCenter().y + 72)) {
                player.intLeft();
            }
            else player.intNoneHori();
            // vertical
            if (player.getPosition().top - 20 < tree.getPosition().y // bottom side
                && (tree.getSprite().getGlobalBounds().contains(player.getCenter().x + 32, player.getCenter().y - 74)
                || tree.getSprite().getGlobalBounds().contains(player.getCenter().x - 32, player.getCenter().y - 74))) {
                player.intUp();
            }
            else if (player.getPosition().top + 74 > tree.getPosition().x - 74 // top side
                && (tree.getSprite().getGlobalBounds().contains(player.getCenter().x + 32, player.getCenter().y + 74)
                || tree.getSprite().getGlobalBounds().contains(player.getCenter().x - 32, player.getCenter().y + 74))) {
                player.intDown();
            }
            else player.intNoneVert();
            */


        } // end update state playing

        if (state == State::CRAFTING) {
            // check mouse pointer
            mouseWorldPos = window.mapPixelToCoords(
                Mouse::getPosition(window), mainView); // convert to world coords of mainView
            inventory.setInvPosition(mainView.getCenter());
            spriteMouse.setPosition(mouseWorldPos);
            inventory.setMaskPosition(Vector2f(mainView.getCenter().x - 105, mainView.getCenter().y - 112));

            if (inventory.getMaskSelected(1)) {
                selectedSprite.setPosition(mainView.getCenter());
            }
            else selectedSprite.setPosition(-1000, -1000);

            if (maskCrafted) {
                // make the mask
                inventory.makeMask(1);
                inventory.setItemCount(1, 10);
            }
            // check if mask is made
            if (inventory.isMaskCrafted(1)) {
                // maskToggle
                player.toggleWoodMask(true);
            }
        }

        /*
        ****************
        DRAW THE SCENE
        ****************
        */

        // check if state is playing
        switch (state) {
            case State::PLAYING:
                window.clear();
                // draw everything related to mainView window
                window.setView(mainView);
                window.draw(background, &backgroundTexture); // draw background
                window.draw(tree.getSprite());
                window.draw(player.getSprite()); // draw player
                window.draw(player.getWoodMaskSprite());
                window.draw(player.getWoodMaskSprite());
                // hud view
                window.setView(hudView);
                window.draw(woodText);
                break;
            case State::JOURNAL:
                break;
            case State::PAUSED:
                window.clear();
                // draw everything related to mainView window
                window.setView(mainView);
                window.draw(background, &backgroundTexture); // draw background
                window.draw(tree.getSprite());
                window.draw(player.getSprite()); // draw player
                window.draw(player.getWoodMaskSprite());
                window.draw(dimOverlay);
                window.draw(pausedText);
                break;
            case State::CRAFTING:
                window.clear();
                window.setView(mainView);
                window.draw(background, &backgroundTexture); // draw background
                window.draw(tree.getSprite());
                window.draw(player.getSprite()); // draw player
                window.draw(player.getWoodMaskSprite());
                window.draw(dimOverlay);
                window.draw(inventory.getSprite());
                window.draw(inventory.getMaskSprite());
                window.draw(selectedSprite);
                window.draw(spriteMouse);
                break;
            case State::NEW_GAME:
                window.clear();
                window.draw(dimOverlay);
                break;
            default: break;
        }
        window.display(); // display window

    } // end game loop

    return 0;
}