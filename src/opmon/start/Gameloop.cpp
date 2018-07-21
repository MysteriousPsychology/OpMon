
#include "./Gameloop.hpp"
#include "../controller/MainMenuCtrl.hpp"
#include "../model/sysObjects/Player.hpp"
#include "../model/storage/UiData.hpp"
#include "../view/Window.hpp"
#include <SFML/Window/Event.hpp>

namespace OpMon {

    GameLoop::GameLoop()
      : frames(0) {
    }

    GameLoop::~GameLoop() {
        while(!_gameScreens.empty()) {
            delete(_gameScreens.top());
            _gameScreens.pop();
        }
    }

    int *GameLoop::getFrames() {
        return &this->frames;
    }

    GameStatus GameLoop::operator()() {

      window.open();

      Model::UiData* uidata = new Model::UiData(window);
      
      // TODO: add first item outside of the Gameloop.
        Controller::AGameScreen *first_ctrl = new Controller::MainMenuCtrl(uidata);

        _gameScreens.push(first_ctrl);

        GameStatus status = GameStatus::CONTINUE;

	
	
        while(status != GameStatus::STOP) {
            status = GameStatus::CONTINUE;

            frames++;

            auto ctrl = _gameScreens.top();
            sf::Event event;

            //process all pending SFML events
            while(status == GameStatus::CONTINUE) {
	      bool isEvent = window.getWindow().pollEvent(event);
                if(isEvent == false)
                    event.type = sf::Event::SensorChanged;
                status = _checkQuit(event);
                if(status == GameStatus::STOP)
                    break;
                status = ctrl->checkEvent(event);
                if(isEvent == false) {
                    break;
                }
            }

            if(status == GameStatus::CONTINUE) {
                // frame update & draw
	      status = ctrl->update(window.getFrame());
            }

            switch(status) {
            case GameStatus::NEXT:
                ctrl->suspend();
                _gameScreens.push(ctrl->getNextGameScreen());
                break;
            case GameStatus::PREVIOUS:
                delete(ctrl);
                _gameScreens.pop();
                _gameScreens.top()->resume();
		break;
            case GameStatus::CONTINUE:
	      window.getFrame().display();
	      window.winRefresh();
		break;
            default:
                break;
            }
        }

	window.close();

	delete(uidata);
	
        return GameStatus::STOP;
    }

    GameStatus GameLoop::_checkQuit(const sf::Event &event) {
        switch(event.type) {
        case sf::Event::Closed:
            return GameStatus::STOP;
        default:
            break;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return GameStatus::STOP;
        }

        return GameStatus::CONTINUE;
    }

} // namespace OpMon
