#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

#include "controller.html.h"
#include "manifest.json.h"
#include "favicon.ico.h"
#include "icon.png.h"

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

class Color {
  public:
    int r,g,b;

    Color(): Color(0,0,0) { }

    Color(int r, int g, int b) {
      Color::r = r;
      Color::g = g;
      Color::b = b;
    }
};

// The step factor determines how much values will be increased at every step.
// The increment will be equal to interp * stepFactor, so the step will increase
// as the value increases. This creates an exponential behaviour, which is
// more logical than linear.
const float stepFactor = 0.1f;
Color cFrom, cTo;
// We interpolate over the max component (max delta of r, g, or b)
// Interpolation is done when interp != interpTo
float interpFrom = 0, interpTo = 0, interp = 0;

// For timing
unsigned long curTime = 0;
// Interval for each tick in milliseconds, 20ms = 50hz
const int animInterval = 20;

// Interpolates the from and two colors, based on the interpolation values.
// It returns the interpolated color.
Color interpColor() {
  if (interp == interpTo) {
    return cTo;
  }
  else {
    if (interp == interpFrom) {
      return cFrom;
    }
    else {
      float span = interpTo - interpFrom;
      if (span == 0) {
        return cFrom;
      }
      else {
        float f = (interp - interpFrom) / span;
        return Color(
          (int)((cTo.r - cFrom.r) * f + cFrom.r),
          (int)((cTo.g - cFrom.g) * f + cFrom.g),
          (int)((cTo.b - cFrom.b) * f + cFrom.b)
        );
      }
    }
  }
}

  // Handle interpolation
void doInterp() {
  if (interp != interpTo) {
    unsigned long t = millis();
    if ((t - curTime) >= animInterval) {
      curTime += animInterval;
      // Make sure we do not lag behind
      if ((t - curTime) >= animInterval) {
        // Catch up
        curTime = t;
      } 
      float delta = (interp + 1) * stepFactor;
      if (interpFrom < interpTo) {
        interp += delta;
        if (interp > interpTo)
          interp = interpTo;  // Stops interpolation
      }
      else {
        interp -= delta;
        if (interp < interpTo)
          interp = interpTo;  // Stops interpolation
      }
      Color c = interpColor();
      // Set RGB
      analogWrite(LED_R, c.r);
      analogWrite(LED_G, c.g);
      analogWrite(LED_B, c.b);
      // Test
      // analogWrite(ledPin, 1023 - c.r);
    }
  }
}

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

void sendHeader(WiFiClient client, const char *mime) {
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(mime);
  client.println("Connection: close");
  client.println(""); //  do not forget this one
}

void sendData(WiFiClient client, const char *mime, uint8_t data[], int data_length) {
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(mime);
  client.print("Content-Length: ");
  client.println(data_length);
  client.println("Connection: close");
  client.println(""); //  do not forget this one
  client.write((const char *)data, data_length);
  // client.println("<!DOCTYPE HTML>");
}

void handleWebRequests() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  // Serial.println("new client");

  int timeOut = 500;
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
    // client.flush();

    // Match the request

    if (request.startsWith("GET "))
    {
      int urlStart = 4;
      // Main page: controller
      if (request.startsWith("/ ", urlStart))
      {
        // *** Root: display the page
        sendHeader(client, "text/html");
        client.println("<!DOCTYPE HTML>");
        client.println(controller_html);
        handled = true;
      }

      if (request.startsWith("/manifest.json", urlStart))
      {
        // *** Server manifest file
        sendHeader(client, "application/json");
        client.println(manifest_html);
        handled = true;
      }

      // Favicon
      if (request.startsWith("/favicon.ico", urlStart)) {
        sendData(client, "image/x-icon", favicon_data, favicon_data_length);
      }

      // Icon
      if (request.startsWith("/icon.png", urlStart)) {
        sendData(client, "image/png", icon_data, icon_data_length);
      }

      // Request for RGB values: /api/set, ex: /api/set0,20,1023
      // int rval = -1, gval = -1, bval = -1;
      if (request.startsWith("/api/set", urlStart))
      {
        // API call, return plain HTML
        sendHeader(client, "text/html");
        client.println("<!DOCTYPE HTML>");
        // Find boundaries for r, g, b
        int rstart = 8 + urlStart;
        int gstart = request.indexOf(",", rstart) + 1;
        if (gstart > rstart)
        {
          int bstart = request.indexOf(",", gstart) + 1;
          if (bstart > gstart)
          {
            // RGB OK, set interpolation
            int r = request.substring(rstart, gstart - 1).toInt();
            int g = request.substring(gstart, bstart - 1).toInt();
            int b = request.substring(bstart).toInt();
            cFrom = interpColor();  // Start where you are now
            cTo = Color(r, g, b);
            // Find the largest component
            float dr = abs(cTo.r - cFrom.r);
            float dg = abs(cTo.g - cFrom.g);
            float db = abs(cTo.b - cFrom.b);
            if (dr >= dg) {
              if (dr >= db) {
                // Red
                interpFrom = cFrom.r;
                interpTo = cTo.r;
              }
              else {
                // Blue
                interpFrom = cFrom.b;
                interpTo = cTo.b;
              }
            }
            else {
              if (dg >= db) {
                // Green
                interpFrom = cFrom.g;
                interpTo = cTo.g;
              }
              else {
                // Blue
                interpFrom = cFrom.b;
                interpTo = cTo.b;
              }
            }
            // Start interpolation if cFrom and cTo differ
            interp = interpFrom;
          }
        }
        client.println("<html>OK</html>");
        handled = true;
      }
    }
  }

  if (!handled) {
    sendHeader(client, "text/html");
    client.println("<!DOCTYPE HTML>");
    client.print("<html>Unknown request: [");
    client.print(request);
    client.println("]");
    client.print("Rest of the input: [");
    client.print(client.readString());
    client.println("]\n</html>");
  }

  // delay(1);
}

void setup()
{
  // pinMode(ledPin, OUTPUT);
  // digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  delay(10);

  analogWriteFreq(500); // PWM freq for LEDs

  // digitalWrite(ledPin, HIGH);

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

  // digitalWrite(ledPin, LOW);

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

  // digitalWrite(ledPin, LOW);
}

// int toggle = 0;

void loop()
{
  ArduinoOTA.handle();

  // Interpolation and output of RGB
  doInterp();

  // Web requests, set interpolation target
  handleWebRequests();

  // digitalWrite(ledPin, toggle);
  // toggle = 1 - toggle;
}
