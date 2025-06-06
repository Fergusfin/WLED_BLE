#include "wled.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEBeacon.h>
#include <BLEAdvertising.h>

// Forward declaration
static void setupBLEBeacon();

class BLEBeaconUsermod : public Usermod {
  private:
    bool initDone = false;
  public:
    void setup() override {
      setupBLEBeacon();
      initDone = true;
    }

    void loop() override {}

    uint16_t getId() override {
      return USERMOD_ID_BLE_BEACON;
    }
};

static void setupBLEBeacon() {
  BLEDevice::init("ESP32-Beacon");
  BLEServer *pServer = BLEDevice::createServer();
  (void)pServer; // unused
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x004C);
  oBeacon.setMajor(123);
  oBeacon.setMinor(456);
  oBeacon.setUUID("e2c56db5-dffb-48d2-b060-d0f5a71096e0");

  BLEAdvertisementData advertisementData;
  advertisementData.setFlags(0x04);
  advertisementData.setManufacturerData(oBeacon.getData());

  pAdvertising->setAdvertisementData(advertisementData);
  pAdvertising->start();
}

static BLEBeaconUsermod ble_beacon;
REGISTER_USERMOD(ble_beacon);
