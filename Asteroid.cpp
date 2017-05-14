#include <cstdlib>
#include "Asteroid.h"

using namespace irr;

Asteroid::Asteroid(core::vector2d<f64> position, f64 degrees, video::SColor color, video::IVideoDriver* driver, f64 radius) :
  Object(position, degrees, color, driver) {
    this->radius = radius;
    vertices = (5 + (std::rand() % 20));
  }

void Asteroid::draw() {
  if(alive) {
    driver->draw2DPolygon(core::position2d<s32>(position.X, position.Y), radius, color, vertices);
  }
}
