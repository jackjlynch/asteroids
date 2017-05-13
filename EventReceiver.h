#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H
#include <irrlicht/irrlicht.h>

class EventReceiver : public irr::IEventReceiver {
  public:
    bool OnEvent(const irr::SEvent&);
    bool is_key_down(irr::EKEY_CODE);
    EventReceiver();
  private:
    bool key_is_down[irr::KEY_KEY_CODES_COUNT];
};

#endif
