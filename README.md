# Remote RGB-strip controller for D1 Mini

This software allows you to set up a remotely controlled RGB-strip using a (Wemos) D1 Mini based on the ESP8266.

To configure the code for your use, fill in the correct data in the code:
- SSID: the name of your WiFi network
- Password: your password to access the network
- IP-address: the address assigned to the controller.

Note: we do not use DHCP, so we can guarantee the IP-address will not change. The IP-address chosen must be valid for your network, and it should not overlap with DHCP-assigned addresses. Alternatively, you can configure your router to assign a specfic IP-address to your controller. In that case, you can comment out the assignment of the static IP.

You can control the brightness levels of the LED-strip using a browser. Direct your browser to the IP-address chosen and the controller page will show up.

## Electronics design

In the kicad directory you will find a matching electronics design to drive a (12V) LED-strip. Make sure the power supply used can provide the maximum current for the 3 channels. It is strongly adviced to use a heat sink or other means of cooling for the 7805 that supplies the regulated 5V power for the controller module.