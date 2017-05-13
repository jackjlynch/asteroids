#include "Ship.h"

using namespace irr;

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
