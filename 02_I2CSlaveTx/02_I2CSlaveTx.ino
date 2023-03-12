// A4 (SDA), A5 (SCL)
#include <Wire.h>

uint8_t active_command = 0xff;
char name_msg[14] = "Hello ThoNV12\n";

#define SLAVE_ADDR 0x68

void setup() {
  // Start the I2C Bus as Slave on address 9
  Wire.begin(SLAVE_ADDR);

  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void receiveEvent(int bytes) 
{
  active_command = Wire.read();    // read one character from the I2C
}

void requestEvent()
{
  if (active_command == 0x01)
  {
    uint8_t data = 20; 
    Wire.write(&data, 1);
  }

  if (active_command == 0x02)
  {
    Wire.write(name_msg, 14);
  }

}
void loop()
{
}
