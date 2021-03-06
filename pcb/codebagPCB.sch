EESchema Schematic File Version 5
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
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega328-PU U1
U 1 1 5DCD46E3
P 3950 3350
F 0 "U1" H 3306 3396 50  0000 R CNN
F 1 "ATmega328-PU" H 3306 3305 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm_SMDSocket_SmallPads" H 3950 3350 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 3950 3350 50  0001 C CNN
	1    3950 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J7
U 1 1 5DCD7EE0
P 6050 3200
F 0 "J7" H 5820 3097 50  0000 R CNN
F 1 "USB_B_Micro" H 5820 3188 50  0000 R CNN
F 2 "codebagPCB:USB_Micro-B_Wuerth_629105150521_CircularHoles" H 6200 3150 50  0001 C CNN
F 3 "~" H 6200 3150 50  0001 C CNN
	1    6050 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	6450 4850 6450 2700
Wire Wire Line
	6450 2700 6050 2700
Wire Wire Line
	6050 2700 6050 2800
Wire Wire Line
	3950 4850 5100 4850
Wire Wire Line
	3950 1850 4050 1850
Wire Wire Line
	4050 1850 5350 1850
Wire Wire Line
	5350 1850 5350 2400
Wire Wire Line
	5350 3400 5750 3400
Connection ~ 4050 1850
Wire Wire Line
	4550 3950 4800 3950
Wire Wire Line
	4550 4350 4800 4350
Wire Wire Line
	4550 4550 4800 4550
Wire Wire Line
	4550 2150 5000 2150
Connection ~ 6050 2700
Wire Wire Line
	4550 4150 4700 4150
Wire Wire Line
	4550 3250 4700 3250
Wire Wire Line
	4550 3550 4700 3550
$Comp
L Connector:Conn_01x01_Female button3
U 1 1 5DCE85F3
P 5000 4550
F 0 "button3" H 5028 4576 50  0000 L CNN
F 1 "Conn_01x01_Female" H 5028 4485 50  0000 L CNN
F 2 "codebagPCB:1sewPin" H 5000 4550 50  0001 C CNN
F 3 "~" H 5000 4550 50  0001 C CNN
	1    5000 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female button2
U 1 1 5DCE4386
P 5000 4350
F 0 "button2" H 5028 4376 50  0000 L CNN
F 1 "Conn_01x01_Female" H 5028 4285 50  0000 L CNN
F 2 "codebagPCB:1sewPin" H 5000 4350 50  0001 C CNN
F 3 "~" H 5000 4350 50  0001 C CNN
	1    5000 4350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J3
U 1 1 5DCE5B41
P 4900 4150
F 0 "J3" H 4928 4176 50  0000 L CNN
F 1 "Conn_01x01_Female" H 4928 4085 50  0000 L CNN
F 2 "codebagPCB:1sewPin" H 4900 4150 50  0001 C CNN
F 3 "~" H 4900 4150 50  0001 C CNN
	1    4900 4150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female button1
U 1 1 5DCE5E55
P 5000 3950
F 0 "button1" H 5028 3976 50  0000 L CNN
F 1 "Conn_01x01_Female" H 5028 3885 50  0000 L CNN
F 2 "codebagPCB:1sewPin" H 5000 3950 50  0001 C CNN
F 3 "~" H 5000 3950 50  0001 C CNN
	1    5000 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J2
U 1 1 5DCE668B
P 4900 3550
F 0 "J2" H 4928 3576 50  0000 L CNN
F 1 "Conn_01x01_Female" H 4928 3485 50  0000 L CNN
F 2 "codebagPCB:1sewPin" H 4900 3550 50  0001 C CNN
F 3 "~" H 4900 3550 50  0001 C CNN
	1    4900 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J1
U 1 1 5DCE6939
P 4900 3250
F 0 "J1" H 4928 3276 50  0000 L CNN
F 1 "Conn_01x01_Female" H 4928 3185 50  0000 L CNN
F 2 "codebagPCB:1sewPin" H 4900 3250 50  0001 C CNN
F 3 "~" H 4900 3250 50  0001 C CNN
	1    4900 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female beeb1
U 1 1 5DCE727D
P 5200 2150
F 0 "beeb1" H 5228 2176 50  0000 L CNN
F 1 "Conn_01x01_Female" H 5228 2085 50  0000 L CNN
F 2 "codebagPCB:1sewPin" H 5200 2150 50  0001 C CNN
F 3 "~" H 5200 2150 50  0001 C CNN
	1    5200 2150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female -1
U 1 1 5DCE7602
P 6250 2400
F 0 "-1" H 6278 2426 50  0000 L CNN
F 1 "Conn_01x01_Female" H 6278 2335 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 6250 2400 50  0001 C CNN
F 3 "~" H 6250 2400 50  0001 C CNN
	1    6250 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J10
U 1 1 5DCE7659
P 7000 2000
F 0 "J10" H 7028 2026 50  0000 L CNN
F 1 "Conn_01x01_Female" H 7028 1935 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 7000 2000 50  0001 C CNN
F 3 "~" H 7000 2000 50  0001 C CNN
	1    7000 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J11
U 1 1 5DCE76C9
P 7000 2100
F 0 "J11" H 7028 2126 50  0000 L CNN
F 1 "Conn_01x01_Female" H 7028 2035 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 7000 2100 50  0001 C CNN
F 3 "~" H 7000 2100 50  0001 C CNN
	1    7000 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female +1
U 1 1 5DCE7BA1
P 5550 2400
F 0 "+1" H 5578 2426 50  0000 L CNN
F 1 "Conn_01x01_Female" H 5578 2335 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 5550 2400 50  0001 C CNN
F 3 "~" H 5550 2400 50  0001 C CNN
	1    5550 2400
	1    0    0    -1  
$EndComp
Connection ~ 5350 2400
$Comp
L Connector:Conn_01x01_Female J8
U 1 1 5DCE7FA1
P 7000 1700
F 0 "J8" H 7028 1726 50  0000 L CNN
F 1 "Conn_01x01_Female" H 7028 1635 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 7000 1700 50  0001 C CNN
F 3 "~" H 7000 1700 50  0001 C CNN
	1    7000 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J9
U 1 1 5DCE8179
P 7000 1800
F 0 "J9" H 7028 1826 50  0000 L CNN
F 1 "Conn_01x01_Female" H 7028 1735 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 7000 1800 50  0001 C CNN
F 3 "~" H 7000 1800 50  0001 C CNN
	1    7000 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2400 5350 2700
Wire Wire Line
	6050 2400 6050 2700
$Comp
L Connector:Conn_01x01_Female -2
U 1 1 5DCFA1F1
P 5100 5050
F 0 "-2" H 5128 5076 50  0000 L CNN
F 1 "Conn_01x01_Female" H 5128 4985 50  0000 L CNN
F 2 "codebagPCB:1sewPin" H 5100 5050 50  0001 C CNN
F 3 "~" H 5100 5050 50  0001 C CNN
	1    5100 5050
	0    1    1    0   
$EndComp
Connection ~ 5100 4850
Wire Wire Line
	5100 4850 6450 4850
$Comp
L Connector:Conn_01x01_Female J18
U 1 1 5DCFB8EA
P 8250 1850
F 0 "J18" H 8278 1876 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8278 1785 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8250 1850 50  0001 C CNN
F 3 "~" H 8250 1850 50  0001 C CNN
	1    8250 1850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J17
U 1 1 5DCFB8F8
P 8250 1750
F 0 "J17" H 8278 1776 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8278 1685 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8250 1750 50  0001 C CNN
F 3 "~" H 8250 1750 50  0001 C CNN
	1    8250 1750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J20
U 1 1 5DCFB906
P 8250 2150
F 0 "J20" H 8278 2176 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8278 2085 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8250 2150 50  0001 C CNN
F 3 "~" H 8250 2150 50  0001 C CNN
	1    8250 2150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J19
U 1 1 5DCFB914
P 8250 2050
F 0 "J19" H 8278 2076 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8278 1985 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8250 2050 50  0001 C CNN
F 3 "~" H 8250 2050 50  0001 C CNN
	1    8250 2050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J5
U 1 1 5DCFCB82
P 8200 2550
F 0 "J5" H 8228 2576 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8228 2485 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8200 2550 50  0001 C CNN
F 3 "~" H 8200 2550 50  0001 C CNN
	1    8200 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J4
U 1 1 5DCFCB90
P 8200 2450
F 0 "J4" H 8228 2476 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8228 2385 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8200 2450 50  0001 C CNN
F 3 "~" H 8200 2450 50  0001 C CNN
	1    8200 2450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J12
U 1 1 5DCFCB9E
P 8200 2850
F 0 "J12" H 8228 2876 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8228 2785 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8200 2850 50  0001 C CNN
F 3 "~" H 8200 2850 50  0001 C CNN
	1    8200 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J6
U 1 1 5DCFCBAC
P 8200 2750
F 0 "J6" H 8228 2776 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8228 2685 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8200 2750 50  0001 C CNN
F 3 "~" H 8200 2750 50  0001 C CNN
	1    8200 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J14
U 1 1 5DCFDC3A
P 8200 3300
F 0 "J14" H 8228 3326 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8228 3235 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8200 3300 50  0001 C CNN
F 3 "~" H 8200 3300 50  0001 C CNN
	1    8200 3300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J13
U 1 1 5DCFDC48
P 8200 3200
F 0 "J13" H 8228 3226 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8228 3135 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8200 3200 50  0001 C CNN
F 3 "~" H 8200 3200 50  0001 C CNN
	1    8200 3200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J15
U 1 1 5DCDA2AF
P 8100 3600
F 0 "J15" H 8128 3626 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8128 3535 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8100 3600 50  0001 C CNN
F 3 "~" H 8100 3600 50  0001 C CNN
	1    8100 3600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J16
U 1 1 5DCDA2BD
P 8100 3700
F 0 "J16" H 8128 3726 50  0000 L CNN
F 1 "Conn_01x01_Female" H 8128 3635 50  0000 L CNN
F 2 "codebagPCB:1aditionalPin" H 8100 3700 50  0001 C CNN
F 3 "~" H 8100 3700 50  0001 C CNN
	1    8100 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5DDD9C2C
P 5700 2700
F 0 "C1" V 5448 2700 50  0000 C CNN
F 1 "100n" V 5539 2700 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5738 2550 50  0001 C CNN
F 3 "~" H 5700 2700 50  0001 C CNN
	1    5700 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 2700 6050 2700
Wire Wire Line
	5550 2700 5350 2700
Connection ~ 5350 2700
Wire Wire Line
	5350 2700 5350 3400
$EndSCHEMATC
