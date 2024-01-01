# Depth Estimator RGB

This example sketch demonstrates the use of the ESP8266WiFi and WiFiClientSecure libraries to access an HTTPS API. The code fetches and displays the status of the esp8266/Arduino project continuous integration build from the "indodax.com" website.

## Getting Started

### Prerequisites

Ensure you have the following Arduino libraries installed:

- [ArduinoJson](https://arduinojson.org/)

### WiFi Configuration

Update the following WiFi credentials in the code:

```cpp
#ifndef STASSID
#define STASSID "Your_SSID"
#define STAPSK  "Your_PASSWORD"
#endif
```

Replace "Your_SSID" with your WiFi network's SSID and "Your_PASSWORD" with the corresponding password.

### HTTPS Configuration

Set the host and HTTPS port:

```cpp
const char* host = "indodax.com";
const int httpsPort = 443;
```

Provide the SHA1 fingerprint of the server certificate:

```cpp
const char fingerprint[] PROGMEM = "CF 27 71 86 F3 25 8E FD 79 49 6C 39 E9 EC EF 8E B0 F8 73 02";
```

Ensure the fingerprint matches the certificate fingerprint of the server you are connecting to. You can obtain the fingerprint using a web browser.

## Running the Example

1. Upload the code to your ESP8266 board.
2. Open the serial monitor to view the output.

The code establishes a secure connection to "indodax.com" and retrieves the ticker information for Bitcoin to Indonesian Rupiah exchange rates. The response is then parsed using the ArduinoJson library, and relevant details (last, buy, sell prices) are displayed on the serial monitor.

Feel free to modify the code for your specific use case or integrate it into a larger project.
