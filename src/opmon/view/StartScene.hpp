/*!
 * \file StartScene.hpp
 * \authors Cyrielle
 * \authors BAKFR
 * \copyright GNU GPL v3.0
 */
#ifndef STARTSCENE_HPP
#define STARTSCENE_HPP

#include "../../utils/OpString.hpp"
#include "../model/storage/StartSceneData.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

#include "../start/Core.hpp"
#include "../start/i18n/ATranslatable.hpp"
#include "./Dialog.hpp"

namespace OpMon {
    namespace View {

        /*!
         * \brief View managing the introduction scene.
         * \todo Change name to IntroScene.
         */
        class StartScene : public I18n::ATranslatable {
          public:
            StartScene(Model::StartSceneData &data);
            ~StartScene() override = default;

            /*!
             * \brief Updates the screen.
             */
            GameStatus operator()();
            /*!
             * \brief Draws the screen.
             */
            void draw(sf::RenderTarget &frame);

            void play();
            void pause();

            /*!
             * \brief Retreives the strings from the language files.
             */
            void initStrings();
            void onLangChanged() override;

            Dialog *getDialog() {
                return dialog.get();
            }

            /*!
             * \brief Returns StartScene::part
             */
            int getPart() {
                return part;
            }

            /*!
             * \brief Returns the entered player name.
             */
            sf::String &getpName() {
                return pName;
            }

            /*!
             * \brief Deletes the data used for the name input screen.
             */
            void delLoop1();

          private:
            sf::Sprite bg;
            sf::Sprite prof;

            /*!
             * \brief Indicates the part the introduction scene is currently playing.
             *
             * - The first part (part 0) is a dialog introducing the professor.
             * - The second part (part 1) is the name input screen.
             * - The third part (part 2) is an another dialog with the professor.
             * Any other value than 0,1 or 2 for this variable is invalid.
             */
            int part = 0;

            /*!
             * \brief Contains the dialog with the professor in the third part.
             * \todo Change the name to txtP2
             */
            Utils::OpString txtP1;

            std::unique_ptr<Dialog> dialog;

            /*!
             * \brief The texts shown during the name input screen.
             */
            sf::Text textDescs[4];
            sf::Sprite bgName;
            sf::Text nameField;

            /*!
             * \brief The player's entered name.
             */
            sf::String pName;
            Model::StartSceneData &data;
        };

    } // namespace View
} // namespace OpMon

#endif // STARTSCENE_H
