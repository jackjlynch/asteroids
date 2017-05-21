#include "Bullet.h"

using namespace irr;

Bullet::Bullet(core::vector2d<f64> position, f64 degrees, video::SColor color, video::IVideoDriver* driver) : Object(position, degrees, color, driver) {
  size_vector = core::vector2d<f64>(0, 5);
  set_velocity(core::vector2d<f64>(0, 300).rotateBy(degrees));
  rotate(degrees);
  range = 6000;
}

Bullet::Bullet() : Object(core::vector2d<f64>(0, 0), 0, video::SColor(0, 0, 0, 0), NULL) {
  //dummy constructor, this object should never be returned out of ship
}

void Bullet::draw() {
  if(alive) {
    draw_line(position - size_vector, position + size_vector);
  }
}

void Bullet::rotate(f64 degrees) {
  Object::rotate(degrees);
  core::vector2d<f64> zero_vector = core::vector2d<f64>(0, 0);
  size_vector.rotateBy(degrees, zero_vector);
}

void Bullet::update(u32 deltaTime) {
  range -= deltaTime;
  if(range <= 0) {
    alive = false;
  }
  Object::update(deltaTime);
}

bool Bullet::collide(Object object) {
  return (position + size_vector).getDistanceFrom(object.position) <= object.radius;
}
