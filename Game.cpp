#include <typeinfo>
#include <iostream>
#include <string>
#include "Game.h"

using namespace irr;

Game::Game(video::IVideoDriver* driver, EventReceiver* receiver, gui::IGUIFont* font) :
  color(video::SColor(255, 255, 255, 255)),
  ship(Ship(core::vector2d<f64>(X_SIZE / 2, Y_SIZE / 2), 180, video::SColor(255, 255, 255, 255), driver)),
  receiver(receiver),
  driver(driver),
  font(font),
  points(0),
  game_time(1),
  time_since_last_asteroid(10000000),
  time_since_death(0),
  num_asteroids(0) {
  objects.push_front(&ship);
}

void Game::handle_input() {
  ship.turn_left = receiver->is_key_down(KEY_KEY_A);
  ship.turn_right = receiver->is_key_down(KEY_KEY_D);
  ship.thrust = receiver->is_key_down(KEY_KEY_W);
  ship.firing = receiver->is_key_down(KEY_SPACE);
}

void Game::update(u32 deltaTime) {
  if(ship.alive) {
    handle_input();
    game_time += deltaTime;
    time_since_last_asteroid += deltaTime;
    if(time_since_last_asteroid * ((f64) game_time / 10000) > 100 * (5 + rand() % 10000)) {
      time_since_last_asteroid = 0;
      Asteroid* asteroid = new Asteroid(core::vector2d<f64>(rand() % X_SIZE, rand() % Y_SIZE), 0, color, driver, 64);
      if(asteroid->collide(ship)) {
        asteroid->position.X -= 3 * asteroid->radius;
      }
      asteroid->set_velocity(core::vector2d<f64>(rand() % 60 - 30, rand() % 60 - 30));
      objects.push_front(asteroid);
    }
    if(game_time / 10000 != (game_time - deltaTime) / 10000) {
      core::list<Object*>::Iterator i = objects.begin();
      while(i != objects.end()) {
        if(!(*i)->alive) {
          delete *i;
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
            if(p->alive && typeid(*p) == typeid(Asteroid) && o->collide(*p)) {
              p->alive = false;
              o->alive = false;
              points += p->radius * 10;
              if(p->radius > 16) {
                core::vector2d<f64> zero_vector = core::vector2d<f64>(0, 0);
                Asteroid* child1 = new Asteroid(core::vector2d<f64>(p->position), 0, color, driver, p->radius / 2);
                core::vector2d<f64> velocity_1 = core::vector2d<f64>(p->get_velocity());
                velocity_1.rotateBy(90);
                child1->set_velocity(3 * velocity_1);
                Asteroid* child2 = new Asteroid(core::vector2d<f64>(p->position), 0, color, driver, p->radius / 2);
                core::vector2d<f64> velocity_2 = core::vector2d<f64>(p->get_velocity());
                velocity_2.rotateBy(-90);
                child2->set_velocity(3 * velocity_2);

                objects.push_front(child1);
                objects.push_front(child2);
              }
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
  else {
    time_since_death += deltaTime;
    if(time_since_death > 3000 && (receiver->is_key_down(KEY_KEY_A) || receiver->is_key_down(KEY_KEY_D) || receiver->is_key_down(KEY_KEY_W) || receiver->is_key_down(KEY_SPACE))) {
      core::list<Object*>::Iterator last = objects.getLast();
      objects.erase(last);
      objects.clear();
      ship = Ship(core::vector2d<f64>(X_SIZE / 2, Y_SIZE / 2), 180, video::SColor(255, 255, 255, 255), driver);
      objects.push_front(&ship);
      game_time = 0;
      time_since_last_asteroid = 10000000;
      points = 0;
      time_since_death = 0;
    }
  }
}
