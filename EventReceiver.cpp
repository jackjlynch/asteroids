#include "EventReceiver.h"

using namespace irr;

bool EventReceiver::OnEvent(const SEvent& event) {
  if(event.EventType == EET_KEY_INPUT_EVENT) {
    key_is_down[event.KeyInput.Key] = event.KeyInput.PressedDown;
  }
  return false;
}

bool EventReceiver::is_key_down(EKEY_CODE key_code) {
  return key_is_down[key_code];
}

EventReceiver::EventReceiver() {
  for(u32 i = 0; i < KEY_KEY_CODES_COUNT; i ++) {
    key_is_down[i] = false;
  }
}
