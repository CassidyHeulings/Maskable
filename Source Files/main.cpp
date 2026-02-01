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
 * Gem -> 4
 * Water -> 5
*/

int main() {
    // initializing screen/world vars
    // add instance of texture holder
    TextureHolder holder;
    enum class State { PAUSED, CRAFTING, NEW_GAME, PLAYING };
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
    pausedText.setCharacterSize(80);
    pausedText.setFillColor(Color::White);
    pausedText.setPosition(130, 200);
    pausedText.setString("Press < esc > to continue\n\nPress < backspace > to quit");
    Text newGameText;
    newGameText.setFont(font);
    newGameText.setCharacterSize(65);
    newGameText.setFillColor(Color::White);
    newGameText.setPosition(80, 80);
    newGameText.setString("How to play Maskable:\n\n   1. Collect resources from the land\n\n      using < enter >\n\n   2. Craft masks using < e >\n\nPress < enter > to start!");
    // resource count crafting
    Text resourceCraftingText;
    resourceCraftingText.setFont(font);
    resourceCraftingText.setCharacterSize(40);
    resourceCraftingText.setFillColor(Color::White);
    resourceCraftingText.setPosition(75, 270);
    // resource count
    Text resourceText;
    resourceText.setFont(font);
    resourceText.setCharacterSize(55);
    resourceText.setFillColor(Color::White);
    resourceText.setPosition(20, 0);
    // mask text
    Text maskText;
    maskText.setFont(font);
    maskText.setFillColor(Color::White);
    maskText.setCharacterSize(35);
    maskText.setPosition(910, 250);
    // crafting HUD
    Text craftingText;
    craftingText.setFont(font);
    craftingText.setCharacterSize(35);
    craftingText.setFillColor(Color::White);
    craftingText.setPosition(130, 50);
    craftingText.setString("< esc > to exit    < enter > to craft     < Q > to put mask on");
    Text craftingText2;
    craftingText2.setFont(font);
    craftingText2.setCharacterSize(35);
    craftingText2.setFillColor(Color::White);
    craftingText2.setPosition(400, 700);
    craftingText2.setString("Use mouse to select mask");
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
    std::vector<Interactable> interactableList;
    Interactable tree1(1, getBiomeRect(1), 1);
    interactableList.push_back(tree1);
    Interactable tree2(1, getBiomeRect(1), 2);
    interactableList.push_back(tree2);
    Interactable tree3(1, getBiomeRect(1), 3);
    interactableList.push_back(tree3);
    Interactable shroom1(3, getBiomeRect(3), 1);
    interactableList.push_back(shroom1);
    Interactable shroom2(3, getBiomeRect(3), 2);
    interactableList.push_back(shroom2);
    Interactable shroom3(3, getBiomeRect(3), 3);
    interactableList.push_back(shroom3);
    Interactable gem1(4, getBiomeRect(4), 1);
    interactableList.push_back(gem1);
    Interactable gem2(4, getBiomeRect(4), 2);
    interactableList.push_back(gem2);
    Interactable gem3(4, getBiomeRect(4), 3);
    interactableList.push_back(gem3);
    bool interacting = false;
    // store positions
    std::vector<FloatRect> interactablePositions;
    for (auto& interactableItem : interactableList)
    {
        interactablePositions.push_back(interactableItem.getSprite().getGlobalBounds());
    }

    // create inventory
    Inventory inventory = Inventory();
    bool woodMaskCrafted = false;
    bool wearWoodMask = false;
    bool shroomMaskCrafted = false;
    bool wearShroomMask = false;
    bool gemMaskCrafted = false;
    bool wearGemMask = false;

    // TODO selection sprite
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
                        if (inventory.getMaskCoords(3, mainView.getCenter()).contains(mouseWorldPos.x + 72, mouseWorldPos.y + 230)) {
                            inventory.setMaskSelected(true, 3);
                        }
                        else inventory.setMaskSelected(false, 3);
                        if (inventory.getMaskCoords(4, mainView.getCenter()).contains(mouseWorldPos.x + 72, mouseWorldPos.y + 230)) {
                            inventory.setMaskSelected(true, 4);
                        }
                        else inventory.setMaskSelected(false, 4);
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
                        case Keyboard::BackSpace:
                                window.close();
                                break;
                        } break;
                    case State::NEW_GAME: {
                        int sizeTile = createBackground(background, world);
                        player.spawn(world, resolution, sizeTile, interactablePositions);
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
                                        woodMaskCrafted = true;
                                    }
                                    else woodMaskCrafted = false;
                                }
                                if (inventory.getMaskSelected(3)) {
                                    if (inventory.getItemCount(3) >= 10) { // shroom mask recipe
                                        shroomMaskCrafted = true;
                                    }
                                    else shroomMaskCrafted = false;
                                }
                                if (inventory.getMaskSelected(4)) {
                                    if (inventory.getItemCount(4) >= 15) { // gem mask recipe
                                        gemMaskCrafted = true;
                                    }
                                    else gemMaskCrafted = false;
                                }
                                break;
                            case Keyboard::Q:
                                // wood mask
                                if (inventory.getMaskSelected(1) && !wearWoodMask && inventory.isMaskCrafted(1)) wearWoodMask = true;
                                else if (inventory.getMaskSelected(1) && wearWoodMask) wearWoodMask = false;
                                else wearWoodMask = false;
                                // shroom mask
                                if (inventory.getMaskSelected(3) && !wearShroomMask && inventory.isMaskCrafted(3)) wearShroomMask = true;
                                else if (inventory.getMaskSelected(3) && wearShroomMask) wearShroomMask = false;
                                else wearShroomMask = false;
                                // gem mask
                                if (inventory.getMaskSelected(4) && !wearGemMask && inventory.isMaskCrafted(4)) wearGemMask = true;
                                else if (inventory.getMaskSelected(4) && wearGemMask) wearGemMask = false;
                                else wearGemMask = false;
                                break;
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
                std::stringstream ssResource;
                ssResource << "Wood: " << inventory.getItemCount(1) << "/300" << "  Mushrooms: " << inventory.getItemCount(3) << "/300" << "  Gems: " << inventory.getItemCount(4) << "/300";
                resourceText.setString(ssResource.str());
                framesSinceLastHUDUpdate = 0;
            }

            // update player
            player.update(dtAsSeconds);
            // update interactable
            for (auto& interactableItem : interactableList)
            {
                interactableItem.update(dtAsSeconds);
            }

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
            for (auto& interactableItem : interactableList)
            {
                if (interacting && player.getPosition().intersects(interactableItem.getSprite().getGlobalBounds())) {
                    interactableItem.increaseCollectSpeed(wearGemMask);
                    inventory.collect(interactableItem.getType(), interactableItem.interact(wearWoodMask));
                    interacting = false;
                }
            }

        } // end update state playing

        if (state == State::CRAFTING) {
            // check mouse pointer
            mouseWorldPos = window.mapPixelToCoords(
                Mouse::getPosition(window), mainView); // convert to world coords of mainView
            inventory.setInvPosition(mainView.getCenter());
            spriteMouse.setPosition(mouseWorldPos);
            inventory.setMaskPosition(Vector2f(mainView.getCenter()));

            if (inventory.getMaskSelected(1)) {
                selectedSprite.setPosition(mainView.getCenter());
                selectedSprite.setRotation(0);
            }
            else if (inventory.getMaskSelected(3)) {
                selectedSprite.setPosition(mainView.getCenter());
                selectedSprite.setRotation(90);
            }
            else if (inventory.getMaskSelected(4)) {
                selectedSprite.setPosition(mainView.getCenter());
                selectedSprite.setRotation(270);
            }
            else selectedSprite.setPosition(-1000, 1000);

            // make the mask
            if (woodMaskCrafted) {
                inventory.setItemCount(1, 10);
                inventory.makeMask(1);
                woodMaskCrafted = false;
            }
            if (shroomMaskCrafted) {
                inventory.setItemCount(3, 10);
                inventory.makeMask(3);
                shroomMaskCrafted = false;
            }
            if (gemMaskCrafted) {
                inventory.setItemCount(4, 15);
                inventory.makeMask(4);
                gemMaskCrafted = false;
            }

            // check if mask is made to wear
            if (wearWoodMask && inventory.isMaskCrafted(1)) {
                player.toggleMask(true, 1);
            }
            else player.toggleMask(false, 1);
            if (wearShroomMask && inventory.isMaskCrafted(3)) {
                player.toggleMask(true, 3);
                player.setSpeed(true);
            }
            else {
                player.toggleMask(false, 3);
                player.setSpeed(false);
            }
            if (wearGemMask && inventory.isMaskCrafted(4)) {
                player.toggleMask(true, 4);
            }
            else player.toggleMask(false, 4);

            // update HUD
            std::stringstream ssResource;
            ssResource << "Wood: " << inventory.getItemCount(1) << "\n\nMushrooms: " << inventory.getItemCount(3) << "\n\nGems: " << inventory.getItemCount(4);
            resourceCraftingText.setString(ssResource.str());
            std::stringstream ssMask;
            if (inventory.getMaskSelected(1)) ssMask << inventory.getMaskText(1) << "\nOwned: " << inventory.getMaskCount(1);
            else if (inventory.getMaskSelected(3)) ssMask << inventory.getMaskText(3) << "\nOwned: " << inventory.getMaskCount(3);
            else if (inventory.getMaskSelected(4)) ssMask << inventory.getMaskText(4) << "\nOwned: " << inventory.getMaskCount(4);
            else ssMask << "";
            maskText.setString(ssMask.str());
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
                for (auto& interactableItem : interactableList)
                {
                    window.draw(interactableItem.getSprite());
                }
                window.draw(player.getSprite()); // draw player
                window.draw(player.getMaskSprite(1));
                window.draw(player.getMaskSprite(3));
                window.draw(player.getMaskSprite(4));
                // hud view
                window.setView(hudView);
                window.draw(resourceText);
                break;
            case State::PAUSED:
                window.clear();
                // draw everything related to mainView window
                window.setView(mainView);
                window.draw(background, &backgroundTexture); // draw background
                for (auto& interactableItem : interactableList)
                {
                    window.draw(interactableItem.getSprite());
                }
                window.draw(player.getSprite()); // draw player
                window.draw(player.getMaskSprite(1));
                window.draw(player.getMaskSprite(3));
                window.draw(player.getMaskSprite(4));
                window.draw(dimOverlay);
                window.setView(hudView);
                window.draw(pausedText);
                break;
            case State::CRAFTING:
                window.clear();
                window.setView(mainView);
                window.draw(background, &backgroundTexture); // draw background
                for (auto& interactableItem : interactableList)
                {
                    window.draw(interactableItem.getSprite());
                }
                window.draw(player.getSprite()); // draw player
                window.draw(player.getMaskSprite(1));
                window.draw(player.getMaskSprite(3));
                window.draw(player.getMaskSprite(4));
                window.draw(dimOverlay);
                window.draw(inventory.getSprite());
                window.draw(inventory.getMaskSprite(1));
                window.draw(inventory.getMaskSprite(3));
                window.draw(inventory.getMaskSprite(4));
                window.draw(selectedSprite);
                window.setView(hudView);
                window.draw(craftingText);
                window.draw(craftingText2);
                window.draw(resourceCraftingText);
                window.draw(maskText);
                window.setView(mainView);
                window.draw(spriteMouse);
                break;
            case State::NEW_GAME:
                window.clear();
                window.draw(dimOverlay);
                window.setView(hudView);
                window.draw(newGameText);
                break;
        }
        window.display(); // display window

    } // end game loop

    return 0;
}