# Remote RGB-strip controller for D1 Mini

This software allows you to set up a remotely controlled RGB-strip using a (Wemos) D1 Mini based on the ESP8266.

This project was created using Platformio with Visual Studio Code. Furthermore, node has been installed for running a local web server to simulate and test the behavior of the device.

To upload the code, follow these steps:

### 1. Configure the network:

Create file "access.h" in the src folder and fill in your SSID and matching password:
> const char *ssid = "*your SSID*";\
> const char *password = "*your password*";

In file main.cpp, specify the IP-address: the 4 bytes of the (static) IP-address to be assigned to the controller:

> const uint8_t addr[]{ *a1, a2, a3, a4* };

Example (match with your local network):
> const uint8_t addr[]{ *192, 168, 1, 99* };

### 2. Upload data:
Choose "Upload File System image" from the platformio project tasks. This will upload the disk image in the /data folder that contains the static files to be served.

### 3. Upload the program.

The device should be accessible at the configured IP-address. The device indicates its state using the connected LEDs:
- Faint red: the processor has started
- Faint green: the server is running

Note: we do not use DHCP, so we can guarantee the IP-address will not change. The IP-address chosen must be valid for your network, and it should not overlap with DHCP-assigned addresses. Alternatively, you can configure your router to assign a specfic IP-address to your controller. In that case, you can comment out the assignment of the static IP.

You can control the brightness levels of the LED-strip using a browser. Direct your browser to the IP-address chosen and the controller page will show up.

## Electronics design

In the kicad directory you will find a matching electronics design to drive a (12V) LED-strip. Make sure the power supply used can provide the maximum current for the 3 channels. It is strongly adviced to use a heat sink or other means of cooling for the 7805 that supplies the regulated 5V power for the controller module.