#include "Game.h"

using namespace irr;

Game::Game(video::IVideoDriver* driver, EventReceiver* receiver) :
  color(video::SColor(255, 255, 255, 255)),
  ship(Ship(core::vector2d<f64>(400, 400), 180, video::SColor(255, 255, 255, 255), driver)),
  receiver(receiver),
  driver(driver) {
  objects.push_front(&ship);
  Asteroid* asteroid = new Asteroid(core::vector2d<f64>(300, 200), 0, color, driver);
  objects.push_front(asteroid);
}

void Game::handle_input() {
  ship.turn_left = receiver->is_key_down(KEY_KEY_A);
  ship.turn_right = receiver->is_key_down(KEY_KEY_D);
  ship.thrust = receiver->is_key_down(KEY_KEY_W);
  ship.firing = receiver->is_key_down(KEY_SPACE);
}

void Game::update(u32 deltaTime) {
    handle_input();
    driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
    for(Object* o : objects) {
      o->update(deltaTime);
      o->draw();
    }
    if(ship.check_for_bullet()) {
      objects.push_front(ship.get_bullet());
    }
    driver->endScene();
}
