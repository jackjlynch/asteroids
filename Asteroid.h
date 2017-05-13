#ifndef ASTEROID_H
#define ASTEROID_H
#include <irrlicht/irrlicht.h>
#include "Object.h"

class Asteroid : public Object {
  public:
    Asteroid(irr::core::vector2d<irr::f64>, irr::f64, irr::video::SColor, irr::video::IVideoDriver*);
    void draw();
};

#endif
