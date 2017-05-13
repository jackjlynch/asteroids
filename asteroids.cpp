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
    core::vector2d<f64> velocity;
    f64 angle;
    void draw_and_wrap(core::vector2d<f64>, core::vector2d<f64>);
    video::IVideoDriver* driver;
  public:
    core::vector2d<f64> position;
    Object(core::vector2d<f64>, video::SColor, video::IVideoDriver*);
    virtual void draw() { };
    virtual void update(u32);
    void set_velocity(core::vector2d<f64>);
    core::vector2d<f64> get_velocity();
    virtual void rotate(f64);
};

Object::Object(core::vector2d<f64> position, video::SColor color, video::IVideoDriver* driver) {
  this->position = core::vector2d<f64>(position);
  this->velocity = core::vector2d<f64>(0, 0);
  this->color = color;
  this->angle = 0;
  this->driver = driver;
};

void Object::update(u32 deltaTime) {
  this->position += ((f64) deltaTime) / 1000 * velocity;
}

void Object::set_velocity(core::vector2d<f64> velocity) {
  this->velocity = velocity;
}

core::vector2d<f64> Object::get_velocity() {
  return this->velocity;
}

void Object::rotate(f64 degrees) {
  angle += degrees;
  if(angle >= 360) {
    angle -= 360;
  }
}

void Object::draw_and_wrap(core::vector2d<f64> start, core::vector2d<f64> end) {
  if(false) {

  }
  else {
    driver->draw2DLine(core::vector2d<s32>((int) (start.X + 0.5), (int) (start.Y + 0.5)), core::vector2d<s32>((int) (end.X + 0.5), (int) (end.Y + 0.5)), color);
  }

}

class Ship : public Object {
  core::vector2d<f64> front_offset, back_left_offset, back_right_offset, back_mid_offset;
  public:
    Ship(core::vector2d<f64>, video::SColor, video::IVideoDriver* );
    void draw();
    void rotate(f64);
};

Ship::Ship(core::vector2d<f64> position, video::SColor color, video::IVideoDriver* driver) : Object(position, color, driver) {
  front_offset = core::vector2d<f64>(0, 20);
  back_left_offset = core::vector2d<f64>(-9, -20);
  back_right_offset = core::vector2d<f64>(9, -20);
  back_mid_offset = core::vector2d<f64>(-0, -15);
}

void Ship::draw() {
  draw_and_wrap(position + back_left_offset, position + front_offset);
  draw_and_wrap(position + back_right_offset, position + front_offset);
  draw_and_wrap(position + back_right_offset, position + back_mid_offset);
  draw_and_wrap(position + back_left_offset, position + back_mid_offset);
};

void Ship::rotate(f64 angle) {
  Object::rotate(angle);

  core::vector2d<f64> zero_vector = core::vector2d<f64>(0, 0);
  front_offset.rotateBy(angle, zero_vector);
  back_left_offset.rotateBy(angle, zero_vector);
  back_right_offset.rotateBy(angle, zero_vector);
  back_mid_offset.rotateBy(angle, zero_vector);
}

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
