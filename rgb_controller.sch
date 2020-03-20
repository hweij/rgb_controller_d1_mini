EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:WeMos_D1_mini U2
U 1 1 5E64E3CD
P 4050 2450
F 0 "U2" H 4050 1561 50  0000 C CNN
F 1 "WeMos_D1_mini" H 4050 1470 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 4050 1300 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 2200 1300 50  0001 C CNN
	1    4050 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5E653E3B
P 4050 3700
F 0 "#PWR0101" H 4050 3450 50  0001 C CNN
F 1 "GND" H 4055 3527 50  0000 C CNN
F 2 "" H 4050 3700 50  0001 C CNN
F 3 "" H 4050 3700 50  0001 C CNN
	1    4050 3700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0102
U 1 1 5E65A00D
P 3950 1250
F 0 "#PWR0102" H 3950 1100 50  0001 C CNN
F 1 "VCC" H 3967 1423 50  0000 C CNN
F 2 "" H 3950 1250 50  0001 C CNN
F 3 "" H 3950 1250 50  0001 C CNN
	1    3950 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1250 3950 1500
Connection ~ 3950 1500
Wire Wire Line
	3950 1500 3950 1650
Wire Wire Line
	4050 3250 4050 3500
$Comp
L Transistor_FET:IRLZ34N Q6
U 1 1 5E666EE7
P 6000 1850
F 0 "Q6" H 6204 1896 50  0000 L CNN
F 1 "IRLZ34N" H 6204 1805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6250 1775 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/irlz34npbf.pdf?fileId=5546d462533600a40153567206892720" H 6000 1850 50  0001 L CNN
	1    6000 1850
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRLZ34N Q7
U 1 1 5E66771F
P 6450 1850
F 0 "Q7" H 6654 1896 50  0000 L CNN
F 1 "IRLZ34N" H 6654 1805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6700 1775 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/irlz34npbf.pdf?fileId=5546d462533600a40153567206892720" H 6450 1850 50  0001 L CNN
	1    6450 1850
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRLZ34N Q8
U 1 1 5E667B59
P 6900 1850
F 0 "Q8" H 7104 1896 50  0000 L CNN
F 1 "IRLZ34N" H 7104 1805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7150 1775 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/irlz34npbf.pdf?fileId=5546d462533600a40153567206892720" H 6900 1850 50  0001 L CNN
	1    6900 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2550 5800 1850
Wire Wire Line
	5200 2650 6250 2650
Wire Wire Line
	6250 2650 6250 1850
Wire Wire Line
	5200 2750 6700 2750
Wire Wire Line
	6700 2750 6700 1850
$Comp
L power:+12V #PWR0103
U 1 1 5E679485
P 6100 1250
F 0 "#PWR0103" H 6100 1100 50  0001 C CNN
F 1 "+12V" H 6115 1423 50  0000 C CNN
F 2 "" H 6100 1250 50  0001 C CNN
F 3 "" H 6100 1250 50  0001 C CNN
	1    6100 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1250 6100 1550
Wire Wire Line
	6100 1650 6100 1550
Wire Wire Line
	6550 1650 6550 1550
Wire Wire Line
	6550 1550 6100 1550
Wire Wire Line
	7000 1650 7000 1550
Wire Wire Line
	7000 1550 6550 1550
Connection ~ 6550 1550
Wire Wire Line
	5200 2550 5800 2550
Wire Wire Line
	7000 2050 7000 2850
Wire Wire Line
	6550 2050 6550 2950
Wire Wire Line
	6550 2950 7000 2950
Wire Wire Line
	6100 2050 6100 3050
Wire Wire Line
	6100 3050 7000 3050
$Comp
L power:GND #PWR0104
U 1 1 5E69A2D8
P 6900 3350
F 0 "#PWR0104" H 6900 3100 50  0001 C CNN
F 1 "GND" H 6905 3177 50  0000 C CNN
F 2 "" H 6900 3350 50  0001 C CNN
F 3 "" H 6900 3350 50  0001 C CNN
	1    6900 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3150 6900 3150
Wire Wire Line
	6900 3150 6900 3250
Wire Wire Line
	7000 3250 6900 3250
Connection ~ 6900 3250
Wire Wire Line
	6900 3250 6900 3350
$Comp
L Device:C C1
U 1 1 5E6AA625
P 2050 1800
F 0 "C1" H 2165 1846 50  0000 L CNN
F 1 "0.33u" H 2165 1755 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 2088 1650 50  0001 C CNN
F 3 "~" H 2050 1800 50  0001 C CNN
	1    2050 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E6AB0D7
P 2950 1800
F 0 "C2" H 3065 1846 50  0000 L CNN
F 1 "0.1u" H 3065 1755 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 2988 1650 50  0001 C CNN
F 3 "~" H 2950 1800 50  0001 C CNN
	1    2950 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 1500 2950 1500
Wire Wire Line
	2200 1500 2050 1500
Wire Wire Line
	2050 1500 2050 1650
Wire Wire Line
	2950 1650 2950 1500
Connection ~ 2950 1500
Wire Wire Line
	2950 1500 3500 1500
Wire Wire Line
	2050 1950 2050 2100
Wire Wire Line
	2050 2100 2500 2100
Wire Wire Line
	2950 2100 2950 1950
$Comp
L power:GND #PWR0105
U 1 1 5E6B8B21
P 2950 2250
F 0 "#PWR0105" H 2950 2000 50  0001 C CNN
F 1 "GND" H 2955 2077 50  0000 C CNN
F 2 "" H 2950 2250 50  0001 C CNN
F 3 "" H 2950 2250 50  0001 C CNN
	1    2950 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 2100 2950 2250
Connection ~ 2950 2100
$Comp
L power:+12V #PWR0106
U 1 1 5E6BB3A5
P 2050 1250
F 0 "#PWR0106" H 2050 1100 50  0001 C CNN
F 1 "+12V" H 2065 1423 50  0000 C CNN
F 2 "" H 2050 1250 50  0001 C CNN
F 3 "" H 2050 1250 50  0001 C CNN
	1    2050 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 1250 2050 1500
Connection ~ 2050 1500
Wire Wire Line
	2500 1800 2500 2100
Connection ~ 2500 2100
Wire Wire Line
	2500 2100 2950 2100
$Comp
L Device:C C3
U 1 1 5E6630BB
P 3500 1800
F 0 "C3" H 3615 1846 50  0000 L CNN
F 1 "100n" H 3615 1755 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 3538 1650 50  0001 C CNN
F 3 "~" H 3500 1800 50  0001 C CNN
	1    3500 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1650 3500 1500
Connection ~ 3500 1500
Wire Wire Line
	3500 1500 3950 1500
Wire Wire Line
	3500 1950 3500 3500
Wire Wire Line
	3500 3500 4050 3500
Connection ~ 4050 3500
$Comp
L Device:R R8
U 1 1 5E65F92A
P 5050 2750
F 0 "R8" V 5050 2750 50  0000 C CNN
F 1 "330R" V 5000 3000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 4980 2750 50  0001 C CNN
F 3 "~" H 5050 2750 50  0001 C CNN
	1    5050 2750
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5E65F7DF
P 5050 2650
F 0 "R7" V 5050 2650 50  0000 C CNN
F 1 "330R" V 5000 2900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 4980 2650 50  0001 C CNN
F 3 "~" H 5050 2650 50  0001 C CNN
	1    5050 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5E65F5A3
P 5050 2550
F 0 "R6" V 5050 2550 50  0000 C CNN
F 1 "330R" V 5000 2800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 4980 2550 50  0001 C CNN
F 3 "~" H 5050 2550 50  0001 C CNN
	1    5050 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2550 4900 2550
Wire Wire Line
	4450 2650 4900 2650
Wire Wire Line
	4450 2750 4900 2750
Wire Wire Line
	4050 3500 4050 3700
$Comp
L Regulator_Linear:L7805 U?
U 1 1 5E74FC66
P 2500 1500
F 0 "U?" H 2500 1742 50  0000 C CNN
F 1 "L7805" H 2500 1651 50  0000 C CNN
F 2 "" H 2525 1350 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 2500 1450 50  0001 C CNN
	1    2500 1500
	1    0    0    -1  
$EndComp
Connection ~ 6100 1550
$EndSCHEMATC
