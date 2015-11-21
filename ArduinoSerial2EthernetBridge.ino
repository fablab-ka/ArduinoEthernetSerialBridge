#include <UIPEthernet.h>

EthernetServer server(8080);

void setup()
{
  uint8_t mac[6] = {0x50, 0x41, 0x32, 0x23, 0x14, 0x05};

  Ethernet.begin(mac);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  server.begin();
}

void loop()
{
  size_t size;

  if (EthernetClient client = server.available()) {
    while ((size = client.available()) > 0) {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg, size);
      Serial.write(msg, size);
      free(msg);
    }

    if (Serial.available() > 0) {
      int incomingByte = Serial.read();

      client.print(incomingByte);
    }

    client.stop();
  }
}
