#include <cstdlib>
#include "Ship.h"
#include "Game.h"

using namespace irr;

Ship::Ship(core::vector2d<f64> position, f64 degrees, video::SColor color, video::IVideoDriver* driver) : Object(position, 0, color, driver) {
  front_offset = core::vector2d<f64>(0, 20);
  back_left_offset = core::vector2d<f64>(-9, -20);
  back_right_offset = core::vector2d<f64>(9, -20);
  back_mid_offset = core::vector2d<f64>(-0, -15);
  thrust_mid_offset = core::vector2d<f64>(0, -28);
  thrust_left_offset = core::vector2d<f64>(-5, -17);
  thrust_right_offset = core::vector2d<f64>(5, -17);
  rotate(degrees);
  turn_right = false;
  turn_left = false;
  fire_cooldown = 250;
  time_since_last_shot = 0;
  has_bullet = false;
  radius = 15;
  hyperspace = false;
  hyperspace_cooldown = 500;
  time_since_hyperspace = 0;
  wrap = true;
}

void Ship::draw() {
  if(alive) {
    draw_line(position + back_left_offset, position + front_offset);
    draw_line(position + back_right_offset, position + front_offset);
    draw_line(position + back_right_offset, position + back_mid_offset);
    draw_line(position + back_left_offset, position + back_mid_offset);
    if(thrust) {
      draw_line(position + thrust_left_offset, position + thrust_mid_offset);
      draw_line(position + thrust_right_offset, position + thrust_mid_offset);
    }
    if(wrap) {
      if(position.Y + radius > Y_SIZE) {
        Ship temp = Ship(position - core::vector2d<f64>(0, Y_SIZE), angle, color, driver);
        temp.wrap = false;
        temp.draw();
      }
      if(position.Y < radius) {
        Ship temp = Ship(position + core::vector2d<f64>(0, Y_SIZE), angle, color, driver);
        temp.wrap = false;
        temp.draw();
      }
      if(position.X < radius) {
        Ship temp = Ship(position + core::vector2d<f64>(X_SIZE, 0), angle, color, driver);
        temp.wrap = false;
        temp.draw();
      }
      if(position.X + radius > X_SIZE) {
        Ship temp = Ship(position - core::vector2d<f64>(X_SIZE, 0), angle, color, driver);
        temp.wrap = false;
        temp.draw();
      }
      if(position.X + radius > X_SIZE && position.Y + radius > Y_SIZE) {
        Ship temp = Ship(position - core::vector2d<f64>(X_SIZE, Y_SIZE), angle, color, driver);
        temp.wrap = false;
        temp.draw();
      }
      if(position.X + radius > X_SIZE && position.Y < radius) {
        Ship temp = Ship(position - core::vector2d<f64>(X_SIZE, -Y_SIZE), angle, color, driver);
        temp.wrap = false;
        temp.draw();
      }
      if(position.X < radius && position.Y + radius > Y_SIZE) {
        Ship temp = Ship(position - core::vector2d<f64>(-X_SIZE, Y_SIZE), angle, color, driver);
        temp.wrap = false;
        temp.draw();
      }
      if(position.X < radius && position.Y < radius) {
        Ship temp = Ship(position - core::vector2d<f64>(-X_SIZE, -Y_SIZE), angle, color, driver);
        temp.wrap = false;
        temp.draw();
      }
    }
  }
};

void Ship::rotate(f64 degrees) {
  Object::rotate(degrees);

  core::vector2d<f64> zero_vector = core::vector2d<f64>(0, 0);
  front_offset.rotateBy(degrees, zero_vector);
  back_left_offset.rotateBy(degrees, zero_vector);
  back_right_offset.rotateBy(degrees, zero_vector);
  back_mid_offset.rotateBy(degrees, zero_vector);
  thrust_left_offset.rotateBy(degrees, zero_vector);
  thrust_mid_offset.rotateBy(degrees, zero_vector);
  thrust_right_offset.rotateBy(degrees, zero_vector);
}

void Ship::update(u32 deltaTime) {
  if(turn_left) {
    rotate(-(f64) deltaTime / 1000 * 360);
  }
  if(turn_right) {
    rotate((f64) deltaTime / 1000 * 360);
  }
  if(thrust) {
    core::vector2d<f64> zero_vector = core::vector2d<f64>(0, 0);
    core::vector2d<f64> thrust_vector = core::vector2d<f64>(0, 100).rotateBy(angle, zero_vector) * (f64) deltaTime / 1000;
    velocity += thrust_vector;
  }
  time_since_last_shot += deltaTime;
  if(firing && time_since_last_shot >= fire_cooldown) {
    bullet = new Bullet(position + front_offset, angle, color, driver);
    has_bullet = true;
    time_since_last_shot = 0;
  }
  time_since_hyperspace += deltaTime;
  if(hyperspace && time_since_hyperspace > hyperspace_cooldown) {
    position.X = rand() % X_SIZE;
    position.Y = rand() % Y_SIZE;
    time_since_hyperspace = 0;
  }
  Object::update(deltaTime);
}

bool Ship::check_for_bullet() {
  return has_bullet;
}

Bullet* Ship::get_bullet() {
  has_bullet = false;
  return bullet;
}
