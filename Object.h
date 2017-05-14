#ifndef OBJECT_H
#define OBJECT_H
#include <irrlicht/irrlicht.h>

class Object {
  protected:
    irr::video::SColor color;
    irr::core::vector2d<irr::f64> velocity;
    irr::f64 angle;
    void draw_and_wrap(irr::core::vector2d<irr::f64>, irr::core::vector2d<irr::f64>);
    irr::video::IVideoDriver* driver;
  public:
    irr::core::vector2d<irr::f64> position;
    irr::f64 radius;
    Object(irr::core::vector2d<irr::f64>, irr::f64, irr::video::SColor, irr::video::IVideoDriver*);
    virtual void draw() { };
    virtual void update(irr::u32);
    void set_velocity(irr::core::vector2d<irr::f64>);
    irr::core::vector2d<irr::f64> get_velocity();
    virtual void rotate(irr::f64);
    bool collide(Object);
    bool alive;
};

#endif
