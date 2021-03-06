#ifndef ASTEROID_H
#define ASTEROID_H
#include <irrlicht/irrlicht.h>
#include "Object.h"

class Asteroid : public Object {
  public:
    Asteroid(irr::core::vector2d<irr::f64>, irr::f64, irr::video::SColor, irr::video::IVideoDriver*, irr::f64 radius);
    void draw();
    irr::u32 vertices;
    bool wrap;
};

#endif
