#ifndef SHIP_H
#define SHIP_H
#include <irrlicht/irrlicht.h>
#include "Object.h"

class Ship : public Object {
  irr::core::vector2d<irr::f64> front_offset, back_left_offset, back_right_offset, back_mid_offset;
  public:
    Ship(irr::core::vector2d<irr::f64>, irr::video::SColor, irr::video::IVideoDriver* );
    void draw();
    void rotate(irr::f64);
};

#endif
