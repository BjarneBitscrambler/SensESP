#include <Arduino.h>

//#define SERIAL_DEBUG_DISABLED

#include "sensesp_app.h"
#include "devices/digital_input.h"
#include "transforms/frequency.h"
#include "wiring_helpers.h"

ReactESP app([] () {
  #ifndef SERIAL_DEBUG_DISABLED
  Serial.begin(115200);

  // A small arbitrary delay is required to let the
  // serial port catch up

  delay(100);
  Debug.setSerialEnabled(true);
  #endif

  sensesp_app = new SensESPApp();

  //////////
  // connect a RPM meter. A DigitalInputCounter counts pulses
  // and reports the readings every read_delay ms
  // (500 in the example). A Frequency
  // transform takes a number of pulses and converts that into
  // a frequency. The sample multiplier converts the 97 tooth
  // tach output into Hz, SK native units.

  sensesp_app->connect_1to1<DigitalInputCounter, Frequency>(
    new DigitalInputCounter(D5, INPUT_PULLUP, RISING, 500),
    new Frequency("propulsion.left.revolutions", 1./97., "/sensors/engine_rpm")
  );

  sensesp_app->enable();
});
