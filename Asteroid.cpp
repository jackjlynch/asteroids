#include "Asteroid.h"

using namespace irr;

Asteroid::Asteroid(core::vector2d<f64> position, f64 degrees, video::SColor color, video::IVideoDriver* driver) :
  Object(position, degrees, color, driver) {}

void Asteroid::draw() {
  driver->draw2DPolygon(core::position2d<s32>(position.X, position.Y), 20, color, 40);
}
