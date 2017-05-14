#ifndef BULLET_H
#define BULLET_H
#include <irrlicht/irrlicht.h>
#include "Object.h"

class Bullet : public Object {
  irr::core::vector2d<irr::f64> size_vector;
  irr::s32 range;
  public:
    void draw();
    void update(irr::u32);
    void rotate(irr::f64);
    Bullet(irr::core::vector2d<irr::f64>, irr::f64, irr::video::SColor, irr::video::IVideoDriver*);
    Bullet();
    bool collide(Object);
};

#endif
