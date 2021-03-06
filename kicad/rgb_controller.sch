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
P 5200 3950
F 0 "U2" H 5200 3061 50  0000 C CNN
F 1 "WeMos_D1_mini" H 5200 2970 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 5200 2800 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 3350 2800 50  0001 C CNN
	1    5200 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5E653E3B
P 5200 5000
F 0 "#PWR0101" H 5200 4750 50  0001 C CNN
F 1 "GND" H 5205 4827 50  0000 C CNN
F 2 "" H 5200 5000 50  0001 C CNN
F 3 "" H 5200 5000 50  0001 C CNN
	1    5200 5000
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0102
U 1 1 5E65A00D
P 5100 2750
F 0 "#PWR0102" H 5100 2600 50  0001 C CNN
F 1 "VCC" H 5117 2923 50  0000 C CNN
F 2 "" H 5100 2750 50  0001 C CNN
F 3 "" H 5100 2750 50  0001 C CNN
	1    5100 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 2750 5100 3000
Connection ~ 5100 3000
Wire Wire Line
	5100 3000 5100 3150
$Comp
L Transistor_FET:IRLZ34N Q6
U 1 1 5E666EE7
P 7150 3750
F 0 "Q6" H 7354 3796 50  0000 L CNN
F 1 "IRLZ34N" H 7354 3705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7400 3675 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/irlz34npbf.pdf?fileId=5546d462533600a40153567206892720" H 7150 3750 50  0001 L CNN
	1    7150 3750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRLZ34N Q7
U 1 1 5E66771F
P 7600 3750
F 0 "Q7" H 7804 3796 50  0000 L CNN
F 1 "IRLZ34N" H 7804 3705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7850 3675 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/irlz34npbf.pdf?fileId=5546d462533600a40153567206892720" H 7600 3750 50  0001 L CNN
	1    7600 3750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRLZ34N Q8
U 1 1 5E667B59
P 8050 3750
F 0 "Q8" H 8254 3796 50  0000 L CNN
F 1 "IRLZ34N" H 8254 3705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 8300 3675 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/irlz34npbf.pdf?fileId=5546d462533600a40153567206892720" H 8050 3750 50  0001 L CNN
	1    8050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 4050 6950 3750
Wire Wire Line
	6350 4150 7400 4150
Wire Wire Line
	7400 4150 7400 3750
Wire Wire Line
	6350 4250 7850 4250
Wire Wire Line
	7850 4250 7850 3750
$Comp
L power:+12V #PWR0103
U 1 1 5E679485
P 8150 2750
F 0 "#PWR0103" H 8150 2600 50  0001 C CNN
F 1 "+12V" H 8165 2923 50  0000 C CNN
F 2 "" H 8150 2750 50  0001 C CNN
F 3 "" H 8150 2750 50  0001 C CNN
	1    8150 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 4050 6950 4050
$Comp
L power:GND #PWR0104
U 1 1 5E69A2D8
P 8150 5000
F 0 "#PWR0104" H 8150 4750 50  0001 C CNN
F 1 "GND" H 8155 4827 50  0000 C CNN
F 2 "" H 8150 5000 50  0001 C CNN
F 3 "" H 8150 5000 50  0001 C CNN
	1    8150 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E6AA625
P 3400 3300
F 0 "C1" H 3515 3346 50  0000 L CNN
F 1 "0.33u" H 3515 3255 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 3438 3150 50  0001 C CNN
F 3 "~" H 3400 3300 50  0001 C CNN
	1    3400 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E6AB0D7
P 4300 3300
F 0 "C2" H 4415 3346 50  0000 L CNN
F 1 "0.1u" H 4415 3255 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 4338 3150 50  0001 C CNN
F 3 "~" H 4300 3300 50  0001 C CNN
	1    4300 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3000 4300 3000
Wire Wire Line
	3550 3000 3400 3000
Wire Wire Line
	3400 3000 3400 3150
Wire Wire Line
	4300 3150 4300 3000
Connection ~ 4300 3000
Wire Wire Line
	3400 3450 3400 3600
Wire Wire Line
	3400 3600 3850 3600
Wire Wire Line
	4300 3600 4300 3450
$Comp
L power:GND #PWR0105
U 1 1 5E6B8B21
P 4300 3750
F 0 "#PWR0105" H 4300 3500 50  0001 C CNN
F 1 "GND" H 4305 3577 50  0000 C CNN
F 2 "" H 4300 3750 50  0001 C CNN
F 3 "" H 4300 3750 50  0001 C CNN
	1    4300 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3600 4300 3750
Connection ~ 4300 3600
$Comp
L power:+12V #PWR0106
U 1 1 5E6BB3A5
P 3400 2750
F 0 "#PWR0106" H 3400 2600 50  0001 C CNN
F 1 "+12V" H 3415 2923 50  0000 C CNN
F 2 "" H 3400 2750 50  0001 C CNN
F 3 "" H 3400 2750 50  0001 C CNN
	1    3400 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2750 3400 3000
Connection ~ 3400 3000
Wire Wire Line
	3850 3300 3850 3600
Connection ~ 3850 3600
Wire Wire Line
	3850 3600 4300 3600
$Comp
L Device:R R8
U 1 1 5E65F92A
P 6200 4250
F 0 "R8" V 6200 4250 50  0000 C CNN
F 1 "330R" V 6150 4500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6130 4250 50  0001 C CNN
F 3 "~" H 6200 4250 50  0001 C CNN
	1    6200 4250
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5E65F7DF
P 6200 4150
F 0 "R7" V 6200 4150 50  0000 C CNN
F 1 "330R" V 6150 4400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6130 4150 50  0001 C CNN
F 3 "~" H 6200 4150 50  0001 C CNN
	1    6200 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5E65F5A3
P 6200 4050
F 0 "R6" V 6200 4050 50  0000 C CNN
F 1 "330R" V 6150 4300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6130 4050 50  0001 C CNN
F 3 "~" H 6200 4050 50  0001 C CNN
	1    6200 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	5600 4050 6050 4050
Wire Wire Line
	5600 4150 6050 4150
Wire Wire Line
	5600 4250 6050 4250
$Comp
L Regulator_Linear:L7805 U?
U 1 1 5E74FC66
P 3850 3000
F 0 "U?" H 3850 3242 50  0000 C CNN
F 1 "L7805" H 3850 3151 50  0000 C CNN
F 2 "" H 3875 2850 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 3850 2950 50  0001 C CNN
	1    3850 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5E76A7C0
P 8400 3300
F 0 "J1" H 8372 3182 50  0000 R CNN
F 1 "LEDs" H 8372 3273 50  0000 R CNN
F 2 "" H 8400 3300 50  0001 C CNN
F 3 "~" H 8400 3300 50  0001 C CNN
	1    8400 3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 3950 7250 4050
Wire Wire Line
	7250 4050 7700 4050
Wire Wire Line
	8150 4050 8150 3950
Wire Wire Line
	7700 3950 7700 4050
Connection ~ 7700 4050
Wire Wire Line
	7700 4050 8150 4050
Wire Wire Line
	8150 4050 8150 5000
Connection ~ 8150 4050
Wire Wire Line
	8200 3400 8150 3400
Wire Wire Line
	8150 3400 8150 3550
Wire Wire Line
	8200 3300 7700 3300
Wire Wire Line
	7700 3300 7700 3550
Wire Wire Line
	8200 3200 7250 3200
Wire Wire Line
	7250 3200 7250 3550
Wire Wire Line
	8150 2750 8150 3100
Wire Wire Line
	8150 3100 8200 3100
Wire Wire Line
	4300 3000 5100 3000
Wire Wire Line
	5200 4750 5200 5000
$EndSCHEMATC
