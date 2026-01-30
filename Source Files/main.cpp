//
// Created by Cassidy Heulings on 1/29/26.
//
#include <SFMl/Graphics.hpp>
#include "../Header Files/Player.hpp"
using namespace sf;

int main() {
    // initializing screen/world vars
    // TODO decide game states
    enum class State { PAUSED, CRAFTING, NEW_GAME, PLAYING, JOURNAL };
    State state = State::PLAYING; // start game in game over state

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
            if (event.type == sf::Event::Closed) window.close();

            // handle one-off key presses
            if (event.type == Event::KeyPressed) {
                // **** inventory slots **** //
                if (state == State::CRAFTING) {
                    switch (event.key.code) {
                        case Keyboard::Num1:
                            // do something
                            break;
                        case Keyboard::Num2:
                            // do something
                            break;
                        case Keyboard::Num3:
                            // do something
                            break;
                        case Keyboard::Num4:
                            // do something
                            break;
                        case Keyboard::Num5:
                            // do something
                            break;
                        case Keyboard::Num6:
                            // do something
                            break;
                        default:
                            break;
                    } // end level up key code switch
                }
                if (state == State::NEW_GAME) {
                    // prepare new game level
                    world.width = 2304; // 64 * 36
                    world.height = 1920; // 64 * 30
                    world.left = 0;
                    world.top = 0;
                    int sizeTile = 64;
                    player.spawn(world, resolution, sizeTile); // spawn player in center of arena
                    clock.restart(); // reset clock to avoid frame jump
                } // end game preparation

                // **** other key codes **** //
                switch (event.key.code) {
                    // return key
                    case Keyboard::Escape:
                        // handle based on state
                        switch (state) {
                        case State::PLAYING: //pause game
                                state = State::PAUSED;
                                break;
                        case State::PAUSED: // unpause game
                                state = State::PLAYING;
                                clock.restart(); // reset clock to avoid frame jump
                                break;
                        case State::JOURNAL: // start a new game
                                state = State::PLAYING;
                                break;
                        case State::CRAFTING: // close crafting menu
                                state = State::PLAYING;
                                break;
                        default: break;
                        } // end return state switch
                        break;
                    default: break;
                } // end other key code switch
            } // end key pressed
        } // end event polling

        // real-time key presses (movement)
        if (state == State::PLAYING) {
            if (Keyboard::isKeyPressed(Keyboard::W)) player.moveUp();
            if (Keyboard::isKeyPressed(Keyboard::S)) player.moveDown();
            if (Keyboard::isKeyPressed(Keyboard::A)) player.moveLeft();
            if (Keyboard::isKeyPressed(Keyboard::D)) player.moveRight();
            // TODO remove
            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        } // end movement while playing

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