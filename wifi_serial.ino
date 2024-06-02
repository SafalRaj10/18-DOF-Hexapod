#include <ESP8266WiFi.h>   // For ESP8266
// #include <WiFi.h>        // For ESP32
#include <WiFiUdp.h>


const char* ssid = "7.0 GHz";
const char* password = "havoksahil";

WiFiUDP udp;

unsigned int localPort = 8888;  // Port to listen for UDP packets

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start UDP
  udp.begin(localPort);
  Serial.println("UDP server started");
}

void loop() {
  // Check if data has been received
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Serial.print("Received packet of size ");
    // Serial.println(packetSize);
    char packetBuffer[255];  // Buffer to hold incoming packet
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
      Serial.println(packetBuffer);
      // Serial.println("Contents (various encodings):");
      // Serial.println("UTF-8:");
      // Serial.println(convertToUTF8(packetBuffer));
      // Serial.println("ISO-8859-1:");
      // Serial.println(convertToISO8859_1(packetBuffer));
      // Serial.println("Windows-1252:");
      // Serial.println(convertToWindows1252(packetBuffer));
  }
  delay(10);
}


String convertToUTF8(const char* str) {
  return String(str);
}

String convertToISO8859_1(const char* str) {
  String result;
  for (int i = 0; i < strlen(str); i++) {
    result += (char)str[i];
  }
  return result;
}

String convertToWindows1252(const char* str) {
  String result;
  for (int i = 0; i < strlen(str); i++) {
    unsigned char c = (unsigned char)str[i];
    if (c < 0x80) {
      result += (char)c;
    } else {
      result += (char)(0xc0 | (c >> 6));
      result += (char)(0x80 | (c & 0x3f));
    }
  }
  return result;
}

