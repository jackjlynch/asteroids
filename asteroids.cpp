#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>
#include "Object.h"
#include "Ship.h"
#include "EventReceiver.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif


core::list<Object*> objects;

void handle_input(Ship &ship, EventReceiver* receiver) {
  ship.turn_left = receiver->is_key_down(KEY_KEY_A);
  ship.turn_right = receiver->is_key_down(KEY_KEY_D);
  ship.thrust = receiver->is_key_down(KEY_KEY_W);
  ship.firing = receiver->is_key_down(KEY_SPACE);
}

void draw_loop(IrrlichtDevice* device, video::IVideoDriver* driver, EventReceiver* receiver) {
  video::SColor color = video::SColor(255, 255, 255, 255);
  Ship ship = Ship(core::vector2d<f64>(400, 400), 180, color, driver);
  objects.push_front(&ship);
  u32 then = device->getTimer()->getTime();
  u32 now = then;
  while(device->run() && driver) {
    if(device->isWindowActive()) {
      now = device->getTimer()->getTime();
      u32 deltaTime = now - then;
      then = now;
      handle_input(ship, receiver);
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

  objects = core::list<Object*>();

  draw_loop(device, driver, &receiver);
}
