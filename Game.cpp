#include <typeinfo>
#include <iostream>
#include <string>
#include "Game.h"

using namespace irr;

Game::Game(video::IVideoDriver* driver, EventReceiver* receiver, gui::IGUIFont* font) :
  color(video::SColor(255, 255, 255, 255)),
  ship(Ship(core::vector2d<f64>(400, 400), 180, video::SColor(255, 255, 255, 255), driver)),
  receiver(receiver),
  driver(driver),
  font(font),
  points(0),
  game_time(0),
  time_since_last_asteroid(0),
  num_asteroids(0) {
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
    game_time += deltaTime;
    time_since_last_asteroid += deltaTime;
    if(game_time / 10000 != (game_time - deltaTime) / 10000) {
      core::list<Object*>::Iterator i = objects.begin();
      while(i != objects.end()) {
        if(!(*i)->alive) {
          i = objects.erase(i);
        }
        else {
          i++;
        }
      }
    }
    driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
    core::stringw points_str = core::stringw(points);
    font->draw(points_str, core::rect<s32>(), color, false, false, 0);
    for(Object* o : objects) {
      if(o->alive) {
        if(typeid(*o) == typeid(Asteroid) && o->collide(ship)) {
          ship.alive = false;
        }
        else if(typeid(*o) == typeid(Bullet)) {
          for(Object* p : objects) {
            if(typeid(*p) == typeid(Asteroid) && o->collide(*p)) {
              p->alive = false;
              o->alive = false;
            }
          }
        }
        o->update(deltaTime);
        o->draw();
      }
    }
    if(ship.check_for_bullet()) {
      objects.push_front(ship.get_bullet());
    }
    driver->endScene();
}
