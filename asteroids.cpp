#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

void drawLoop(IrrlichtDevice* device, video::IVideoDriver* driver) {
  while(device->run() && driver) {
    if(device->isWindowActive()) {
      u32 time = device->getTimer()->getTime();
    }
  }
}

int main() {
  video::E_DRIVER_TYPE driverType=driverChoiceConsole();
  if(driverType == video::EDT_COUNT) {
    return 1;
  }

  IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(512,384));

  if(device==0) {
    return 1;
  }

  device->setWindowCaption(L"Asteroids");
  video::IVideoDriver* driver = device->getVideoDriver();

  drawLoop(device, driver);
}
