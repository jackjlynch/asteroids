#include <stdio.h>
#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

class Object {
  protected:
    video::SColor color;
  public:
    core::vector2d<s32> position;
    Object(core::vector2d<s32>, video::SColor color);
    virtual void draw(video::IVideoDriver*) { };
};

Object::Object(core::vector2d<s32> position, video::SColor color) {
  this->position = core::vector2d<s32>(position);
  this->color = color;
};

class Ship : public Object {
  core::vector2d<s32> front_offset, back_left_offset, back_right_offset, back_mid_offset;
  public:
    Ship(core::vector2d<s32>, video::SColor color);
    void draw(video::IVideoDriver* driver);
};

Ship::Ship(core::vector2d<s32> position, video::SColor color) : Object(position, color) {
  front_offset = core::vector2d<s32>(0, 20);
  back_left_offset = core::vector2d<s32>(-9, -20);
  back_right_offset = core::vector2d<s32>(9, -20);
  back_mid_offset = core::vector2d<s32>(-0, -15);
}

void Ship::draw(video::IVideoDriver* driver) {
  driver->draw2DLine(position + back_left_offset, position + front_offset, color);
  driver->draw2DLine(position + back_right_offset, position + front_offset, color);
  driver->draw2DLine(position + back_right_offset, position + back_mid_offset, color);
  driver->draw2DLine(position + back_left_offset, position + back_mid_offset, color);
};

core::list<Object*> objects;

void drawLoop(IrrlichtDevice* device, video::IVideoDriver* driver) {
  video::SColor color = video::SColor(255, 255, 255, 255);
  Ship ship = Ship(core::vector2d<s32>(400, 400), color);
  objects.push_front(&ship);
  while(device->run() && driver) {
    if(device->isWindowActive()) {
      u32 time = device->getTimer()->getTime();
      driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
      for(Object* o : objects) {
        o->draw(driver);
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
