/*!
 * \file MainMenuCtrl.hpp
 * \authors BAKFR
 * \authors Cyrielle
 * \copyright GNU GPL v3.0
*/
#pragma once

#include <SFML/Window/Event.hpp>

#include "../model/storage/MainMenuData.hpp"
#include "../start/Core.hpp"
#include "../view/MainMenu.hpp"
#include "AGameScreen.hpp"
#include "MenuHelper.hpp"
#include "../../utils/CycleCounter.hpp"

namespace OpMon {
    namespace Controller {
        /*!
         * \brief Manages the main menu of the game.
         */
        class MainMenuCtrl : public AGameScreen {
          private:
            Model::MainMenuData data;
            View::MainMenu view;

            /*!
             * \brief Determines which screen has to be loaded in loadNextScreen().
             *
             * This integer is filled with some special values determined by macros in GameMenuCtrl.cpp. Currently, there is LOAD_STARTSCENE and LOAD_OPTIONS. Then, loadNextScreen loads in _next_gs a game screen according the value of this variable().
             */
            int loadNext = 0;
            /*!
             * \brief The position of the cursor on the menu.
             */
            Utils::CycleCounter curPosI = Utils::CycleCounter(4);

          public:
            MainMenuCtrl(Model::UiData *data);

            GameStatus checkEvent(sf::Event const &event) override;
            GameStatus update(sf::RenderTexture &frame) override;

            void loadNextScreen() override;

            void suspend() override;
            void resume() override;
        };

    } // namespace Controller
} // namespace OpMon
