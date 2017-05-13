#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>
#include "Object.h"
#include "Ship.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif



core::list<Object*> objects;

void drawLoop(IrrlichtDevice* device, video::IVideoDriver* driver) {
  video::SColor color = video::SColor(255, 255, 255, 255);
  Ship ship = Ship(core::vector2d<f64>(400, 400), color, driver);
  objects.push_front(&ship);
  u32 then = device->getTimer()->getTime();
  u32 now = then;
  while(device->run() && driver) {
    if(device->isWindowActive()) {
      now = device->getTimer()->getTime();
      u32 deltaTime = now - then;
      then = now;
      driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
      for(Object* o : objects) {
        o->update(deltaTime);
        o->draw();
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

  IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(800, 800));

  if(device==0) {
    return 1;
  }

  device->setWindowCaption(L"Asteroids");
  video::IVideoDriver* driver = device->getVideoDriver();

  objects = core::list<Object*>();

  drawLoop(device, driver);
}
