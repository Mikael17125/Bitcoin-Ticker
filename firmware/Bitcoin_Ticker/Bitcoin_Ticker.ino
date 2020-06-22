/*
    HTTP over TLS (HTTPS) example sketch

    This example demonstrates how to use
    WiFiClientSecure class to access HTTPS API.
    We fetch and display the status of
    esp8266/Arduino project continuous integration
    build.

    Limitations:
      only RSA certificates
      no support of Perfect Forward Secrecy (PFS)
      TLSv1.2 is supported since version 2.4.0-rc1

    Created by Ivan Grokhotkov, 2015.
    This example is in public domain.
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "Rumah"
#define STAPSK  "belajar123123"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "indodax.com";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "CF 27 71 86 F3 25 8E FD 79 49 6C 39 E9 EC EF 8E B0 F8 73 02";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


}

void loop() {
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
//  Serial.print("connecting to ");
//  Serial.println(host);

//  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
//    Serial.println("connection failed");
    return;
  }

  String url = "/api/btc_idr/ticker";
//  Serial.print("requesting URL: ");
//  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

//  Serial.println("request sent");
  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
//      Serial.println("headers received");
      break;
    }
  }
  
//  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  while(client.available()){  
    //Print response
    line = client.readStringUntil('\n');  //Read Line by Line
    if(line[0] == '{'){
      char JSONMessage[line.length() + 1] ;
      line.toCharArray(JSONMessage,line.length() + 1 );
      
      StaticJsonBuffer<300> JSONBuffer;
      JsonObject& parsed = JSONBuffer.parseObject(JSONMessage);

      if(!parsed.success()){
        Serial.println("Parsing Failed");

        break;
      }

      const char* last = parsed["ticker"]["last"];
      const char* buy = parsed["ticker"]["buy"];
      const char* sell = parsed["ticker"]["sell"];

      Serial.print("LAST : ");
      Serial.println(last);
      Serial.print("BUY : ");
      Serial.println(buy);
      Serial.print("SELL : ");
      Serial.println(sell);
    }
//      Serial.println(line); //Print response
  }
  Serial.println("==========");
//  Serial.println("closing connection");
}

