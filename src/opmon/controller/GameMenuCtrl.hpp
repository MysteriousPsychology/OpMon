/*!
 * \file GameMenuCtrl.hpp
 * \author Cyrielle
 * \copyright GNU GPL v3.0
*/
#pragma once

#include "../../utils/CycleCounter.hpp"
#include "../model/storage/GameMenuData.hpp"
#include "../model/sysObjects/Player.hpp"
#include "../view/GameMenu.hpp"
#include "AGameScreen.hpp"

namespace OpMon {
    namespace Controller {

        /*!
         * \brief Controller of the in-game menu.
         */
        class GameMenuCtrl : public AGameScreen {
          private:
            Model::GameMenuData &data;

            View::GameMenu view;
            Model::Player &player;

            /*!
             * \brief Determines which screen has to be loaded in loadNextScreen().
             *
             * This integer is filled with some special values determined by macros in GameMenuCtrl.cpp. Currently, there is LOAD_OPTIONS. Then, loadNextScreen() loads in _next_gs a game screen according the value of this variable.
             */
            int loadNext = 0;

            /*!
             * \brief The position of the cursor on the menu.
             */
            Utils::CycleCounter curPos = Utils::CycleCounter(6);

          public:
            ~GameMenuCtrl();

            GameMenuCtrl(Model::GameMenuData &data, Model::Player &player);

            GameStatus checkEvent(sf::Event const &event) override;
            GameStatus update(sf::RenderTexture &frame) override;

            void loadNextScreen() override;
            void suspend() override;
            void resume() override;
        };

    } // namespace Controller
} // namespace OpMon
