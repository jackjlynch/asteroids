#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>
#include "Object.h"
#include "Ship.h"
#include "EventReceiver.h"
#include "Game.h"

using namespace irr;

void game_loop(IrrlichtDevice* device, video::IVideoDriver* driver, Game &game) {
  u32 then = device->getTimer()->getTime();
  u32 now = then;
  while(device->run() && driver) {
    if(device->isWindowActive()) {
      now = device->getTimer()->getTime();
      u32 deltaTime = now - then;
      then = now;
      game.update(deltaTime);
    }
  }
}

int main() {
  video::E_DRIVER_TYPE driverType=driverChoiceConsole();
  if(driverType == video::EDT_COUNT) {
    return 1;
  }

  EventReceiver receiver;
  IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(800, 800), 16, false, false, false, &receiver);

  if(device==0) {
    return 1;
  }

  device->setWindowCaption(L"Asteroids");
  video::IVideoDriver* driver = device->getVideoDriver();
  Game game = Game(driver, &receiver);

  game_loop(device, driver, game);
}
