#ifndef SHIP_H
#define SHIP_H
#include <irrlicht/irrlicht.h>
#include "Object.h"
#include "Bullet.h"

class Ship : public Object {
  irr::core::vector2d<irr::f64> front_offset, back_left_offset, back_right_offset, back_mid_offset;
  bool has_bullet;
  Bullet* bullet;
  public:
    Ship(irr::core::vector2d<irr::f64>, irr::f64, irr::video::SColor, irr::video::IVideoDriver* );
    void draw();
    void rotate(irr::f64);
    void update(irr::u32);
    bool turn_left;
    bool turn_right;
    bool thrust;
    bool firing;
    bool hyperspace;
    irr::u32 fire_cooldown;
    irr::u32 time_since_last_shot;
    irr::u32 hyperspace_cooldown;
    irr::u32 time_since_hyperspace;
    bool check_for_bullet();
    Bullet* get_bullet();
    bool wrap;
};

#endif
