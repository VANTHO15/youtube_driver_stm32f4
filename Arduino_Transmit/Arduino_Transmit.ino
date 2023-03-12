/*
   SPI pin numbers:
   SCK   13  // Serial Clock.
   MISO  12  // Master In Slave Out.
   MOSI  11  // Master Out Slave In.
   SS    10  // Slave Select
*/

#include <SPI.h>
uint8_t board_id[10] = "ThoNV";
//Initialize SPI slave.
void SPI_SlaveInit(void)
{
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);
  //make SPI as slave
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
  //1. fist make sure that ss is low . so lets wait until ss is low
  Serial.println("Slave waiting for ss to go low");
  while (digitalRead(SS) );

  for (int i = 0 ; i < strlen(board_id) ; i++)
  {
    SPI_SlaveTransmit(board_id[i]);
  }

  while (1);
}
