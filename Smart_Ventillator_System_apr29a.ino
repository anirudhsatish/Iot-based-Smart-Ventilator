#include "arduino_secrets.h"
// Stepper - Version: Latest
#include <Stepper.h>

/*

  The following variables are automatically generated and updated when changes are made to the Thing

  float _delay_;
  float pressure;
  float rPM;
  float spO2;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"

float press;
float del;
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 4, 16, 17, 5);
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

}

void loop() {
  ArduinoCloud.update();
  // Your code here
  Serial.println("clockwise");
  myStepper.step(press);
  delay(del);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-press);
  //delay(del);

}

/*
  Since Delay is READ_WRITE variable, onDelayChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onDelayChange()  {
  // Add your code here to act upon Delay change
  del = map(_delay_, 0, 100, 0, 2000);
}
/*
  Since Pressure is READ_WRITE variable, onPressureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPressureChange()  {
  press = map(pressure, 0, 100, 0, 1000);// Add your code here to act upon Pressure change
}
/*
  Since RPM is READ_WRITE variable, onRPMChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRPMChange()  {
  // Add your code here to act upon RPM change
  myStepper.setSpeed(rPM);
}
/*
  Since SpO2 is READ_WRITE variable, onSpO2Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onSpO2Change()  {
  // Add your code here to act upon SpO2 change
}
