#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

#include "controller.html.h"
#include "favicon.ico.h"

const char *ssid = "TMNL-818E4D";
const char *password = "DSC8ZLKGLKYFT7";
const char *hostname = "rgbcontroller";
const uint8_t addr[]{192, 168, 1, 99};

IPAddress ipaddress(addr[0], addr[1], addr[2], addr[3]);
IPAddress gateway(addr[0], addr[1], addr[2], 1);
IPAddress subnet(255, 255, 255, 0);

int ledPin = LED_BUILTIN;
WiFiServer server(80);

int LED_R = D5;
int LED_G = D6;
int LED_B = D7;

void initOTA()
{
  ArduinoOTA.setHostname("esp8266LEDString");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      type = "sketch";
    }
    else
    { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
}

void sendHTMLHeader(WiFiClient client) {
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
}

void sendImage(WiFiClient client, uint8_t data[], int data_length) {
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: image/x-icon");
  client.print("Content-Length: ");
  client.println(favicon_data_length);
  client.println("Connection: close");
  client.println(""); //  do not forget this one
  client.write_P((const char *)data, data_length);
  // client.println("<!DOCTYPE HTML>");
}


void setup()
{
  Serial.begin(115200);
  delay(10);

  analogWriteFreq(500); // PWM freq for LEDs

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // LEDs off
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  WiFi.config(ipaddress, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  //    Serial.print(".");
  //  }

  initOTA();

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  ArduinoOTA.handle();

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  // Serial.println("new client");

  int timeOut = 100;
  while (!client.available())
  {
    timeOut--;
    if (timeOut <= 0)
      break;
    delay(1);
  }

  bool handled = false;

  String request = "";
  if (client.available())
  {
    // Read the first line of the request
    request = client.readStringUntil('\r');
    client.flush();

    // Match the request

    if (request.startsWith("GET "))
    {
      int urlStart = 4;
      // Main page: controller
      if (request.startsWith("/ ", urlStart))
      {
        // *** Root: display the page
        sendHTMLHeader(client);
        client.println(controller_html);
        handled = true;
      }

      // Favicon
      if (request.indexOf("/favicon.ico") >= 0) {
        // TODO
        sendImage(client, favicon_data, favicon_data_length);
      }

      // Request for RGB values: /api/set, ex: /api/set0,20,1023
      int idx = request.indexOf("/api/set");
      // int rval = -1, gval = -1, bval = -1;
      if (idx != -1)
      {
        // API call, return plain HTML
        sendHTMLHeader(client);
        // Find boundaries for r, g, b
        int rstart = idx + 8;
        int gstart = request.indexOf(",", rstart) + 1;
        if (gstart > rstart)
        {
          int bstart = request.indexOf(",", gstart) + 1;
          if (bstart > gstart)
          {
            // RGB OK, output
            int r = request.substring(rstart, gstart - 1).toInt();
            int g = request.substring(gstart, bstart - 1).toInt();
            int b = request.substring(bstart).toInt();
            analogWrite(LED_R, r);
            analogWrite(LED_G, g);
            analogWrite(LED_B, b);
            // Test
            analogWrite(ledPin, 1023 - r);
            Serial.printf("r=%i g=%i b=%i\n", r, g, b);
          }
        }
        client.println("<html>OK</html>");
        handled = true;
      }
    }
  }

  if (!handled) {
    sendHTMLHeader(client);
    client.println("<html>Unknown request:<br/>");
    client.println(request);
    client.println("</html>");
  }

  // if (sendIcon)
  // {
  //   client.println(controller_html);
  // }
  // else
  // {
  //   // client.print("<html>Request: [");
  //   // client.print(request);
  //   // client.println("]</html>");
  //    client.println("<html>OK</html>");
  // }

  delay(1);

  Serial.println("Client disconnected");
  Serial.println("");
}
