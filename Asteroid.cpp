#include "Asteroid.h"

using namespace irr;

Asteroid::Asteroid(core::vector2d<f64> position, f64 degrees, video::SColor color, video::IVideoDriver* driver) :
  Object(position, degrees, color, driver) {
    radius = 20;
  }

void Asteroid::draw() {
  if(alive) {
    driver->draw2DPolygon(core::position2d<s32>(position.X, position.Y), radius, color, 40);
  }
}
