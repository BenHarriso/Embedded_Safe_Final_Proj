#include <msp430.h>
#include <stdint.h>
#include "adxl343.h" // ADXL343 library

#define RED_LED BIT2 // P6.2

void main(void) {
  uint8_t data[6];
  int16_t x, y, z;
  float accel_threshold = 2.0; // adjust this value to set threshold

  WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer

  P6DIR |= RED_LED; // set red LED pin as output
  P6OUT &= ~RED_LED; // turn off red LED initially

  adxl343_setup(); // initialize ADXL343

  while (1) {
    adxl343_read_data(data); // read accelerometer data
    x = (data[1] << 8) | data[0];
    y = (data[3] << 8) | data[2];
    z = (data[5] << 8) | data[4];

    float accel_mag = sqrt(xx + yy + z*z); // calculate acceleration magnitude
    if (accel_mag > accel_threshold) {
      P6OUT |= RED_LED; // turn on red LED if threshold is exceeded
    } else {
      P6OUT &= ~RED_LED; // turn off red LED otherwise
    }
  }
}
