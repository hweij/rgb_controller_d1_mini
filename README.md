# Remote RGB-strip controller for D1 Mini

This software allows you to set up a remotely controlled RGB-strip using a (Wemos) D1 Mini based on the ESP8266.

You can control the levels using a browser to connect to the server running on the controller.

In the kicad directory you will find a matching electronics design to drive a (12V) LED-strip. Make sure the power supply used can provide the maximum current for the 3 channels. It is stronly adviced to use a heat sink or other means of cooling for the 7805 that supplies the regulated 5V power for the controller module.