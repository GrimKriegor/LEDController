#include <Arduino.h>

class LEDController {
  private:
    uint8_t _pin;
    bool _status;
  public:
    LEDController(uint8_t pin);
    bool status();
    void on();
    void off();
    void toggle();
    void dim(uint8_t intensity=128);
    void onOff(int wait=100);
    void stepDim(int wait=10, uint8_t begining=0, uint8_t end=255);
    void cycleDim(int wait=10, uint8_t min=0, uint8_t max=255);
};

