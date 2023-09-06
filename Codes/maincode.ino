#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "BLE2902.h"
#include "BLEHIDDevice.h"
#include "HIDTypes.h"
#include "./settings.h"

#define LED_PIN 2 // Define the LED pin number

BLEHIDDevice* keyboard;
BLECharacteristic* inputReport;
BLECharacteristic* outputReport;

bool isConnected = false; // Flag to track Bluetooth connection status
bool buttonPressed = false; // Flag to track button press status

// Callbacks for BLE server events
class MyCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      isConnected = true;
      // Enable notifications on the input report descriptor
      BLE2902* desc = (BLE2902*)inputReport->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
      desc->setNotifications(true);
    }

    void onDisconnect(BLEServer* pServer) {
      isConnected = false;
      // Disable notifications on the input report descriptor
      BLE2902* desc = (BLE2902*)inputReport->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
      desc->setNotifications(false);
    }
};

// Callbacks for BLE characteristic write events
class MyOutputCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* me) {
      // Handle write events on the output report characteristic
      uint8_t* value = (uint8_t*)(me->getValue().c_str());
      ESP_LOGI(LOG_TAG, "special keys: %d", *value);
    }
};

void taskServer(void*) {
  // Initialize BLE
  BLEDevice::init(__BT_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyCallbacks());

  // Create HID device, input report, and output report
  keyboard = new BLEHIDDevice(pServer);
  inputReport = keyboard->inputReport(1); // Input REPORTID from report map
  outputReport = keyboard->outputReport(1); // Output REPORTID from report map

  outputReport->setCallbacks(new MyOutputCallbacks());

  // Set manufacturer name
  std::string manufacturerName = __MANUFACTURER;
  keyboard->manufacturer()->setValue(manufacturerName);

  // Set PnP ID and HID info
  keyboard->pnp(0x02, 0xe502, 0xa111, 0x0210);
  keyboard->hidInfo(0x00, 0x02);

  BLESecurity *pSecurity = new BLESecurity();
  pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);

  const uint8_t report[] = {
    // ... (the HID report map)
  };

  keyboard->reportMap((uint8_t*)report, sizeof(report));
  keyboard->startServices();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setAppearance(HID_KEYBOARD);
  pAdvertising->addServiceUUID(keyboard->hidService()->getUUID());
  pAdvertising->start();
  keyboard->setBatteryLevel(7);

  ESP_LOGD(LOG_TAG, "Advertising started!");
  delay(portMAX_DELAY);
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE works!");

  // Configure the button pin as an input and attach an interrupt
  pinMode(__BUTTONPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(__BUTTONPIN), buttonInterrupt, FALLING);

  // Configure the LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Create a task to run the BLE server
  xTaskCreate(taskServer, "server", 20000, NULL, 5, NULL);
}

void loop() {
  // Check if connected to a BLE device and if the button is pressed
  if (isConnected && buttonPressed) {
    buttonPressed = false;
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
    Serial.println("Cheese...");

    // Simulate a key press
    uint8_t keyPressMsg[] = {0x0, 0x0, __SEND_KEY, 0x0, 0x0, 0x0, 0x0, 0x0};
    inputReport->setValue(keyPressMsg, sizeof(keyPressMsg));
    inputReport->notify();

    // Simulate a key release
    uint8_t keyReleaseMsg[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    inputReport->setValue(keyReleaseMsg, sizeof(keyReleaseMsg));
    inputReport->notify();

    delay(1000);
    digitalWrite(LED_PIN, LOW); // Turn off the LED
    attachInterrupt(digitalPinToInterrupt(__BUTTONPIN), buttonInterrupt, FALLING); // Reattach button interrupt
  }
  delay(50);
}

// Interrupt handler for the button press
IRAM_ATTR void buttonInterrupt() {
  detachInterrupt(digitalPinToInterrupt(__BUTTONPIN)); // Detach button interrupt
  buttonPressed = true; // Set the button press flag
}
