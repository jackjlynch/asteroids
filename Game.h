#ifndef GAME_H
#define GAME_H

#include <irrlicht/irrlicht.h>
#include "Object.h"
#include "Ship.h"
#include "Bullet.h"
#include "EventReceiver.h"
#include "Asteroid.h"

#define X_SIZE 800
#define Y_SIZE 800

class Game {
  irr::core::list<Object*> objects;
  Ship ship;
  EventReceiver* receiver;
  irr::video::IVideoDriver* driver;
  irr::video::SColor color;
  irr::u32 points;
  irr::u32 game_time;
  irr::u32 time_since_last_asteroid;
  irr::u32 num_asteroids;
  irr::gui::IGUIFont* font;
  void handle_input();
  public:
    void update(irr::u32);
    Game(irr::video::IVideoDriver*, EventReceiver*, irr::gui::IGUIFont*);
};
#endif
