/*
   SPI pin numbers:
   SCK   13  // Serial Clock.
   MISO  12  // Master In Slave Out.
   MOSI  11  // Master Out Slave In.
   SS    10  // Slave Select
*/
#include <SPI.h>
#define MAX_LEN 500
bool msgComplete = false; 
uint8_t userBuffer[MAX_LEN];
uint32_t cnt = 0;

//Initialize SPI slave.
void SPI_SlaveInit(void)
{
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);
  // Enable SPI as slave.
  SPCR = (1 << SPE);
}

//sends one byte of data
void SPI_SlaveTransmit(uint8_t data)
{
  /* Start transmission */
  SPDR = data;
  /* Wait for transmission complete */
  while (!(SPSR & (1 << SPIF)));
}

void setup()
{
  // Initialize serial for troubleshooting.
  Serial.begin(9600);
  // Initialize SPI Slave.
  SPI_SlaveInit();
  Serial.println("Slave Initialized");
}

void loop()
{
  Serial.println("Type anything and send...");
  while (!msgComplete)
  {
    if (Serial.available())
    {
      //Read a byte of incoming serial data.
      char readByte = (char)Serial.read();
      Serial.println(readByte);
      userBuffer[cnt++] = readByte;
      if (readByte == '0' || ( cnt == MAX_LEN))
      {
        msgComplete = true;
      }
    }
  }

  Serial.println("Your message...");
  Serial.println((char*)userBuffer);

  /*Transmit the user buffer over SPI */
  for (uint32_t i = 0 ; i < cnt ; i++)
  {
    SPI_SlaveTransmit(userBuffer[i]);
  }
  cnt = 0;
  msgComplete = false;
  Serial.println("Message sent...");

  while (!digitalRead(SS));
  Serial.println("Master ends communication");
}
