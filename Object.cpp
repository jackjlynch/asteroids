#include "Object.h"

using namespace irr;

Object::Object(core::vector2d<f64> position, f64 degrees, video::SColor color, video::IVideoDriver* driver) {
  this->position = core::vector2d<f64>(position);
  this->velocity = core::vector2d<f64>(0, 0);
  this->color = color;
  this->angle = degrees;
  this->driver = driver;
  alive = true;
};

void Object::update(u32 deltaTime) {
  this->position += ((f64) deltaTime) / 1000 * velocity;
  if(this->position.X > 800) {
    this->position.X -= 800;
  }
  else if(this->position.X < 0) {
    this->position.X += 800;
  }
  if(this->position.Y > 800) {
    this->position.Y -= 800;
  }
  else if(this->position.Y < 0) {
    this->position.Y += 800;
  }
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

bool Object::collide(Object object) {
  return position.getDistanceFrom(object.position) <= radius + object.radius;
}
