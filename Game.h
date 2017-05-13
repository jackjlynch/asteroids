#ifndef GAME_H
#define GAME_H

#include <irrlicht/irrlicht.h>
#include "Object.h"
#include "Ship.h"
#include "Bullet.h"
#include "EventReceiver.h"
#include "Asteroid.h"

class Game {
  irr::core::list<Object*> objects;
  Ship ship;
  EventReceiver* receiver;
  irr::video::IVideoDriver* driver;
  irr::video::SColor color;
  void handle_input();
  public:
    void update(irr::u32);
    Game(irr::video::IVideoDriver*, EventReceiver*);
};
#endif
