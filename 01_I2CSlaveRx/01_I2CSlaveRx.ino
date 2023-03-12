// Wire Slave Receiver
// A4 (SDA), A5 (SCL)
#include <Wire.h>

#define MY_ADDR   0x68

char rx_buffer[32] ;
uint32_t cnt =0;
uint8_t message[50];
void setup() {

  Serial.begin(9600);
  
  Wire.begin(MY_ADDR); 
  
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);

  sprintf(message,"Slave is ready : Address 0x%x",MY_ADDR);
  Serial.println((char*)message );  
  Serial.println("Waiting for data from master");  
}

void loop(void)
{
  
}

void receiveEvent(int bytes) 
{
 while( Wire.available() )
 {
   rx_buffer[cnt++] = Wire.read();
 }
  rx_buffer[cnt] = '\0';
  cnt=0;
  Serial.print("Received:");  
  Serial.println((char*)rx_buffer);  
}
