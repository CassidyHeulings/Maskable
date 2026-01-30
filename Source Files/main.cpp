//
// Created by Cassidy Heulings on 1/29/26.
//
#include <SFMl/Graphics.hpp>
#include "../Header Files/Player.hpp"
#include "../Header Files/World.hpp"
using namespace sf;

int main() {
    // initializing screen/world vars
    // TODO decide game states
    enum class State { PAUSED, CRAFTING, NEW_GAME, PLAYING, JOURNAL };
    State state = State::PAUSED; // start game in paused state

    // create SFML window with screen resolution
    Vector2f resolution;
    resolution.x = VideoMode::getFullscreenModes()[0].width;
    resolution.y = VideoMode::getFullscreenModes()[0].height;
    RenderWindow window(VideoMode::getFullscreenModes()[0],
        "Maskable", Style::Fullscreen);
    // view following character in world
    View mainView(FloatRect(0,0,resolution.x,resolution.y));

    // Initialize game-wide variables
    Clock clock; // used to time everything
    Vector2f mouseWorldPos; // mouse in relation to world coords
    Vector2i mouseScreenPos; // mouse in relation to screen coords
    Player player; // create instance of player class
    IntRect world; // boundaries of world
    VertexArray background; // create background
    Texture backgroundTexture; // load texture for background
    backgroundTexture.loadFromFile("../Graphics/BackgroundSheet.png");

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
            // close window
            if (event.type == Event::Closed) window.close();

            // handle key presses
            if (event.type == Event::KeyPressed) {
                // **** inventory slots **** //
                if (state == State::PAUSED) {
                    switch (event.key.code) {
                        case Keyboard::Escape:
                            state = State::PLAYING;
                            clock.restart(); // reset clock to avoid frame jump
                            break;
                        case Keyboard::Enter:
                            state = State::NEW_GAME;
                            break;
                        case Keyboard::Delete:
                            window.close();
                            break;
                        default: break;
                    }
                }
                if (state == State::CRAFTING) {
                    switch (event.key.code) {
                        case Keyboard::Escape:
                            state = State::PLAYING;
                            clock.restart();
                            break;
                        // TODO add crafting interactions
                        default: break;
                    }
                }
                if (state == State::JOURNAL) {
                    switch (event.key.code) {
                        case Keyboard::Escape:
                            state = State::PLAYING;
                            clock.restart();
                            break;
                            // TODO add journal interactions
                        default: break;
                    }
                }
                if (state == State::NEW_GAME) {
                    // prepare new game level
                    world.width = 4608; // 128 * 36 (36 tiles)
                    world.height = 3840; // 128 * 30 (30 tiles)
                    world.left = 0;
                    world.top = 0;
                    // pass vertex array by reference to create the background here
                    int sizeTile = createBackground(background, world);
                    player.spawn(world, resolution, sizeTile); // spawn player in center of arena
                    state = State::PLAYING;
                    clock.restart(); // reset clock to avoid frame jump
                } // end game preparation
                if (state == State::PLAYING) {
                    switch (event.key.code) {
                        case Keyboard::Escape:
                            state = State::PAUSED;
                            break;
                        // TODO add interaction buttons
                        default: break;
                    }
                }
            } // end key pressed

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

            // update player
            player.update(dtAsSeconds);
            Vector2f playerPos(player.getCenter()); // note players new pos

            // TODO if at edge, do not center anymore
            // make view centered around player
            mainView.setCenter(player.getCenter());
        } // end update state playing

        // TODO mouse coords in menus?
        /**
        if (state == State::CRAFTING) {
            // check mouse pointer
            mouseWorldPos = window.mapPixelToCoords(
                Mouse::getPosition(window), mainView); // convert to world coords of mainView
        }
        */

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
                window.draw(player.getSprite()); // draw player
                break;
            case State::JOURNAL:
                break;
            case State::PAUSED:
                break;
            case State::CRAFTING:
                break;
            case State::NEW_GAME:
                break;
            default: break;
        }
        window.display(); // display window

    } // end game loop

    return 0;
}