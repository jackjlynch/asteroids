#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

class Object {
  protected:
    video::SColor color;
    core::vector2d<f32> velocity;
  public:
    core::vector2d<f32> position;
    Object(core::vector2d<f32>, video::SColor color);
    virtual void draw(video::IVideoDriver*) { };
    virtual void update(u32);
    void setVelocity(core::vector2d<f32>);
    core::vector2d<f32> getVelocity();
};

Object::Object(core::vector2d<f32> position, video::SColor color) {
  this->position = core::vector2d<f32>(position);
  this->velocity = core::vector2d<f32>(0, 0);
  this->color = color;
};

void Object::update(u32 deltaTime) {
  this->position += ((f32) deltaTime) / 1000 * velocity;
}

void Object::setVelocity(core::vector2d<f32> velocity) {
  this->velocity = velocity;
}

core::vector2d<f32> Object::getVelocity() {
  return this->velocity;
}

class Ship : public Object {
  core::vector2d<s32> front_offset, back_left_offset, back_right_offset, back_mid_offset;
  public:
    Ship(core::vector2d<f32>, video::SColor color);
    void draw(video::IVideoDriver* driver);
};

Ship::Ship(core::vector2d<f32> position, video::SColor color) : Object(position, color) {
  front_offset = core::vector2d<s32>(0, 20);
  back_left_offset = core::vector2d<s32>(-9, -20);
  back_right_offset = core::vector2d<s32>(9, -20);
  back_mid_offset = core::vector2d<s32>(-0, -15);
}

void Ship::draw(video::IVideoDriver* driver) {
  core::vector2d<s32> intPosition = core::vector2d<s32>((s32) (position.X + 0.5), (s32) (position.Y + 0.5));
  driver->draw2DLine(intPosition + back_left_offset, intPosition + front_offset, color);
  driver->draw2DLine(intPosition + back_right_offset, intPosition + front_offset, color);
  driver->draw2DLine(intPosition + back_right_offset, intPosition + back_mid_offset, color);
  driver->draw2DLine(intPosition + back_left_offset, intPosition + back_mid_offset, color);
};

core::list<Object*> objects;

void drawLoop(IrrlichtDevice* device, video::IVideoDriver* driver) {
  video::SColor color = video::SColor(255, 255, 255, 255);
  Ship ship = Ship(core::vector2d<f32>(400, 400), color);
  ship.setVelocity(core::vector2d<f32>(10, 0));
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
