#include <cstdlib>
#include "Asteroid.h"
#include "Game.h"

using namespace irr;

Asteroid::Asteroid(core::vector2d<f64> position, f64 degrees, video::SColor color, video::IVideoDriver* driver, f64 radius) :
  Object(position, degrees, color, driver) {
    this->radius = radius;
    vertices = (5 + ((float)radius / 64) * (std::rand() % 20));
    wrap = true;
  }

void Asteroid::draw() {
  if(alive) {
    driver->draw2DPolygon(core::position2d<s32>(position.X, position.Y), radius, color, vertices);
    if(wrap) {
      if(position.Y + radius > Y_SIZE) {
        Asteroid temp = Asteroid(position - core::vector2d<f64>(0, Y_SIZE), angle, color, driver, radius);
        temp.vertices = vertices;
        temp.wrap = false;
        temp.draw();
      }
      if(position.Y < radius) {
        Asteroid temp = Asteroid(position + core::vector2d<f64>(0, Y_SIZE), angle, color, driver, radius);
        temp.vertices = vertices;
        temp.wrap = false;
        temp.draw();
      }
      if(position.X < radius) {
        Asteroid temp = Asteroid(position + core::vector2d<f64>(X_SIZE, 0), angle, color, driver, radius);
        temp.vertices = vertices;
        temp.wrap = false;
        temp.draw();
      }
      if(position.X + radius > X_SIZE) {
        Asteroid temp = Asteroid(position - core::vector2d<f64>(X_SIZE, 0), angle, color, driver, radius);
        temp.vertices = vertices;
        temp.wrap = false;
        temp.draw();
      }
      if(position.X + radius > X_SIZE && position.Y + radius > Y_SIZE) {
        Asteroid temp = Asteroid(position - core::vector2d<f64>(X_SIZE, Y_SIZE), angle, color, driver, radius);
        temp.vertices = vertices;
        temp.wrap = false;
        temp.draw();
      }
      if(position.X + radius > X_SIZE && position.Y < radius) {
        Asteroid temp = Asteroid(position - core::vector2d<f64>(X_SIZE, -Y_SIZE), angle, color, driver, radius);
        temp.vertices = vertices;
        temp.wrap = false;
        temp.draw();
      }
      if(position.X < radius && position.Y + radius > Y_SIZE) {
        Asteroid temp = Asteroid(position - core::vector2d<f64>(-X_SIZE, Y_SIZE), angle, color, driver, radius);
        temp.vertices = vertices;
        temp.wrap = false;
        temp.draw();
      }
      if(position.X < radius && position.Y < radius) {
        Asteroid temp = Asteroid(position - core::vector2d<f64>(-X_SIZE, -Y_SIZE), angle, color, driver, radius);
        temp.vertices = vertices;
        temp.wrap = false;
        temp.draw();
      }
    }
  }
}
