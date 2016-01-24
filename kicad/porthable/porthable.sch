EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:arduino
LIBS:Conn-raspberry
LIBS:porthable-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "PorTHable (DHT11: Temperatura, Umidita`)"
Date "23 jan 2016"
Rev "0.0.5"
Comp "mail4davide@gmail.com"
Comment1 "+ ESP8266, DS1302, Seriali e Programmazione"
Comment2 "ATmega328 w/ DHT11, TFT LCD"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DISPLAY_128X128SPI S1
U 1 1 565B3034
P 5500 1700
F 0 "S1" H 5300 1450 60  0000 C CNN
F 1 "DISPLAY_128X128SPI" H 5850 750 60  0000 C CNN
F 2 "~" H 6250 1100 60  0000 C CNN
F 3 "~" H 6250 1100 60  0000 C CNN
	1    5500 1700
	1    0    0    1   
$EndComp
$Comp
L CONN_4X2 U1
U 1 1 566699E3
P 7450 1300
F 0 "U1" H 7450 1550 50  0000 C CNN
F 1 "ESP8266" V 7450 1300 40  0000 C CNN
F 2 "" H 7450 1300 60  0000 C CNN
F 3 "" H 7450 1300 60  0000 C CNN
	1    7450 1300
	0    -1   -1   0   
$EndComp
Text Notes 7300 1800 1    60   ~ 0
TX0
Text Notes 7600 950  1    60   ~ 0
RX0
Text Notes 7300 950  1    60   ~ 0
GND
Text Notes 7400 1800 1    60   ~ 0
EN
Text Notes 7600 1800 1    60   ~ 0
VCC
$Comp
L ATMEGA328-P IC1
U 1 1 5666F771
P 2700 4800
F 0 "IC1" H 1950 6050 40  0000 L BNN
F 1 "ATMEGA328-P" H 3100 3400 40  0000 L BNN
F 2 "DIL28" H 2700 4800 30  0000 C CIN
F 3 "" H 2700 4800 60  0000 C CNN
	1    2700 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3700 1800 3700
Wire Wire Line
	1300 4000 1800 4000
Wire Wire Line
	1600 2200 1600 7300
Wire Wire Line
	1600 5900 1800 5900
Wire Wire Line
	1600 6000 1800 6000
Connection ~ 1600 5900
Wire Wire Line
	7600 900  7600 700 
Wire Wire Line
	7600 700  7800 700 
Wire Wire Line
	6000 1700 6000 3900
Wire Wire Line
	6000 3900 3600 3900
Wire Wire Line
	5900 1700 5900 3800
Wire Wire Line
	5900 3800 3600 3800
Wire Wire Line
	5800 1700 5800 3700
Wire Wire Line
	5800 3700 3600 3700
Wire Wire Line
	5700 1700 5700 4000
Wire Wire Line
	5600 1700 5600 4200
Wire Wire Line
	3700 5700 8000 5700
Wire Wire Line
	5500 1700 5500 4350
Wire Wire Line
	6200 2000 6200 1700
Connection ~ 5500 2000
Wire Wire Line
	7400 2000 7400 1700
Connection ~ 6200 2000
Wire Wire Line
	7600 1700 7600 4400
Connection ~ 7400 2000
Wire Wire Line
	1600 2200 8500 2200
Wire Wire Line
	6100 1700 6100 4350
Wire Wire Line
	7000 2200 7000 700 
Wire Wire Line
	7000 700  7300 700 
Wire Wire Line
	7300 700  7300 900 
Connection ~ 6100 2200
Connection ~ 7000 2200
$Comp
L +3,3V #PWR2
U 1 1 566702A4
P 1400 7300
F 0 "#PWR2" H 1400 7260 30  0001 C CNN
F 1 "+3,3V" H 1400 7410 30  0000 C CNN
F 2 "" H 1400 7300 60  0000 C CNN
F 3 "" H 1400 7300 60  0000 C CNN
	1    1400 7300
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR3
U 1 1 566702B3
P 1600 7300
F 0 "#PWR3" H 1600 7300 30  0001 C CNN
F 1 "GND" H 1600 7230 30  0001 C CNN
F 2 "" H 1600 7300 60  0000 C CNN
F 3 "" H 1600 7300 60  0000 C CNN
	1    1600 7300
	1    0    0    -1  
$EndComp
Connection ~ 1600 6000
$Comp
L C C1
U 1 1 56670337
P 1800 6700
F 0 "C1" H 1800 6800 40  0000 L CNN
F 1 "4,7uF" H 1806 6615 40  0000 L CNN
F 2 "~" H 1838 6550 30  0000 C CNN
F 3 "~" H 1800 6700 60  0000 C CNN
	1    1800 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6100 1800 6500
Wire Wire Line
	1800 6900 1800 7100
Wire Wire Line
	1800 7100 1600 7100
Connection ~ 1600 7100
$Comp
L R R1
U 1 1 56672AC8
P 3800 2650
F 0 "R1" V 3880 2650 40  0000 C CNN
F 1 "10K" V 3807 2651 40  0000 C CNN
F 2 "~" V 3730 2650 30  0000 C CNN
F 3 "~" H 3800 2650 30  0000 C CNN
	1    3800 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2000 3800 2400
Connection ~ 3800 2000
Wire Wire Line
	3800 2900 3800 5150
Wire Wire Line
	3700 5150 7900 5150
$Comp
L C C2
U 1 1 56672C56
P 4200 2600
F 0 "C2" H 4200 2700 40  0000 L CNN
F 1 "22pF" H 4206 2515 40  0000 L CNN
F 2 "~" H 4238 2450 30  0000 C CNN
F 3 "~" H 4200 2600 60  0000 C CNN
	1    4200 2600
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 56672C6F
P 5000 2600
F 0 "C3" H 5000 2700 40  0000 L CNN
F 1 "22pF" H 5006 2515 40  0000 L CNN
F 2 "~" H 5038 2450 30  0000 C CNN
F 3 "~" H 5000 2600 60  0000 C CNN
	1    5000 2600
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X1
U 1 1 56672C7C
P 4600 3100
F 0 "X1" H 4600 3250 60  0000 C CNN
F 1 "16,000M" H 4600 2950 60  0000 C CNN
F 2 "~" H 4600 3100 60  0000 C CNN
F 3 "~" H 4600 3100 60  0000 C CNN
	1    4600 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4300 3700 4300
Wire Wire Line
	4200 2800 4200 4300
Wire Wire Line
	5000 2800 5000 4400
Wire Wire Line
	4200 2400 4200 2200
Connection ~ 4200 2200
Wire Wire Line
	5000 2200 5000 2400
Connection ~ 5000 2200
Wire Wire Line
	5000 4400 3700 4400
$Comp
L R R2
U 1 1 566C71E2
P 4000 2650
F 0 "R2" V 4080 2650 40  0000 C CNN
F 1 "4.7K" V 4007 2651 40  0000 C CNN
F 2 "~" V 3930 2650 30  0000 C CNN
F 3 "~" H 4000 2650 30  0000 C CNN
	1    4000 2650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 566D2F91
P 3600 2700
F 0 "SW2" H 3750 2810 50  0000 C CNN
F 1 "RESET" H 3600 2620 50  0000 C CNN
F 2 "~" H 3600 2700 60  0000 C CNN
F 3 "~" H 3600 2700 60  0000 C CNN
	1    3600 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3600 2200 3600 2400
Connection ~ 3600 2200
Wire Wire Line
	3600 3000 3600 3200
Wire Wire Line
	3600 3200 3800 3200
Connection ~ 3800 3200
Wire Notes Line
	2800 3400 3900 3400
Wire Notes Line
	3900 3400 3900 1900
Wire Notes Line
	3900 1900 2800 1900
Wire Notes Line
	2800 1900 2800 3400
Text Notes 2950 3350 1    60   ~ 0
Nella versione finale\nnon servira`, ci sara`\ninterruttore generale\non/off. Il reset sara`\ncollegato alla +VCC\ndirettamente.
Wire Wire Line
	3700 5400 9500 5400
Wire Wire Line
	3700 5300 9500 5300
Wire Wire Line
	4200 3100 4300 3100
Connection ~ 4200 3100
Wire Wire Line
	4900 3100 5000 3100
Connection ~ 5000 3100
Wire Wire Line
	3600 4000 9500 4000
Wire Wire Line
	3600 4200 9500 4200
Connection ~ 5700 4000
Wire Wire Line
	3700 4100 9500 4100
Connection ~ 5600 4200
Connection ~ 3800 5150
Text Notes 10050 3900 0    39   ~ 0
15 (GPIO22)
Text Notes 10050 4000 0    39   ~ 0
19 (GPIO10/MOSI)
Text Notes 10050 4100 0    39   ~ 0
21 (GPIO9/MISO)
Text Notes 10050 4200 0    39   ~ 0
23 (GPIO11/SCLK)
Text Notes 10050 4300 0    39   ~ 0
25 (GND)
$Comp
L SWITCH_INV SW1
U 1 1 567E7B08
P 1300 6700
F 0 "SW1" H 1100 6850 50  0000 C CNN
F 1 "Supply EXT/INT" H 1150 6550 50  0000 C CNN
F 2 "~" H 1300 6700 60  0000 C CNN
F 3 "~" H 1300 6700 60  0000 C CNN
	1    1300 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	1300 6100 1800 6100
Wire Wire Line
	1400 7200 1400 7300
$Comp
L +3,3V #PWR1
U 1 1 567E7BE8
P 1200 7300
F 0 "#PWR1" H 1200 7260 30  0001 C CNN
F 1 "+3,3V" H 1200 7410 30  0000 C CNN
F 2 "" H 1200 7300 60  0000 C CNN
F 3 "" H 1200 7300 60  0000 C CNN
	1    1200 7300
	-1   0    0    1   
$EndComp
Wire Wire Line
	1200 7300 1200 7200
Wire Wire Line
	1300 2000 1300 6200
Connection ~ 1300 6100
Connection ~ 1300 4000
Connection ~ 1300 3700
Text Notes 1400 7600 0    59   ~ 0
Alimentazione\nda Batteria interna
Text Notes 1200 7600 2    59   ~ 0
Alimentazione\nEsterna
Wire Wire Line
	7900 3900 9500 3900
Wire Wire Line
	7900 5150 7900 3900
Text Notes 10050 3800 0    39   ~ 0
[ 17 (+3.3V) ]
$Comp
L DS1302 U2
U 1 1 568E1D1C
P 9750 2000
F 0 "U2" H 10020 2550 60  0000 C CNN
F 1 "DS1302" H 10110 1450 60  0000 C CNN
F 2 "" H 9750 2000 60  0000 C CNN
F 3 "" H 9750 2000 60  0000 C CNN
	1    9750 2000
	1    0    0    1   
$EndComp
$Comp
L CRYSTAL X2
U 1 1 568E1D4D
P 9100 800
F 0 "X2" H 9100 950 60  0000 C CNN
F 1 "323768K" H 9100 650 60  0000 C CNN
F 2 "~" H 9100 800 60  0000 C CNN
F 3 "~" H 9100 800 60  0000 C CNN
	1    9100 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1700 7300 5300
Wire Wire Line
	8600 2100 8600 5800
Wire Wire Line
	8600 5800 3700 5800
Wire Wire Line
	3700 6000 8700 6000
Wire Wire Line
	10800 5900 3700 5900
Wire Wire Line
	10800 2300 10800 5900
Wire Wire Line
	8900 2100 8600 2100
Wire Wire Line
	8900 2300 8700 2300
Wire Wire Line
	8700 2300 8700 6000
Wire Wire Line
	10600 2300 10800 2300
Wire Wire Line
	7600 2800 9750 2800
Wire Wire Line
	9750 2800 9750 2600
Wire Wire Line
	9750 1400 9750 600 
Wire Wire Line
	8500 600  10800 600 
Wire Wire Line
	8500 600  8500 4700
$Comp
L BATTERY BT1
U 1 1 568E244A
P 10800 1100
F 0 "BT1" H 10800 1300 50  0000 C CNN
F 1 "CR 2032" H 10800 910 50  0000 C CNN
F 2 "~" H 10800 1100 60  0000 C CNN
F 3 "~" H 10800 1100 60  0000 C CNN
	1    10800 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10800 600  10800 800 
Connection ~ 9750 600 
Wire Wire Line
	10800 1400 10800 1700
Wire Wire Line
	10800 1700 10600 1700
Wire Wire Line
	9400 800  9550 800 
Wire Wire Line
	9550 800  9550 1300
Wire Wire Line
	9550 1300 8800 1300
Wire Wire Line
	8900 1600 8800 1600
Wire Wire Line
	8800 1600 8800 1300
Wire Wire Line
	8800 800  8600 800 
Wire Wire Line
	8600 800  8600 1800
Wire Wire Line
	8600 1800 8900 1800
$Comp
L POT RV1
U 1 1 569BE382
P 5800 4350
F 0 "RV1" H 5800 4250 50  0000 C CNN
F 1 "10K" H 5800 4350 50  0000 C CNN
F 2 "~" H 5800 4350 60  0000 C CNN
F 3 "~" H 5800 4350 60  0000 C CNN
	1    5800 4350
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 2000 4000 2400
Connection ~ 4000 2000
Wire Wire Line
	4000 2900 4000 5700
Connection ~ 4000 5700
Connection ~ 7300 5300
Wire Wire Line
	7800 700  7800 5400
Connection ~ 7800 5400
$Comp
L CONN_17 P1
U 1 1 56A32017
P 9850 4600
F 0 "P1" V 9800 5550 60  0000 C CNN
F 1 "CONN_17" V 9950 5700 60  0000 C CNN
F 2 "" H 9850 4600 60  0000 C CNN
F 3 "" H 9850 4600 60  0000 C CNN
	1    9850 4600
	1    0    0    -1  
$EndComp
Text Notes 9800 5400 0    100  ~ 0
SERIAL
Text Notes 9900 4300 1    39   ~ 0
Program w/ RPi
Wire Wire Line
	8500 4300 9500 4300
Connection ~ 8500 2200
Wire Wire Line
	7600 3800 9500 3800
Wire Notes Line
	9800 3800 9950 3800
Wire Notes Line
	9950 3800 9950 4300
Wire Notes Line
	9950 4300 9800 4300
Wire Wire Line
	7600 4400 9500 4400
Wire Wire Line
	8500 4700 9500 4700
Connection ~ 8500 4300
Wire Wire Line
	8000 4500 9500 4500
Wire Wire Line
	8000 5700 8000 4500
Wire Wire Line
	1300 2000 7600 2000
Connection ~ 7600 2000
Connection ~ 7600 3800
Connection ~ 7600 2800
Wire Notes Line
	9800 4400 9950 4400
Wire Notes Line
	9950 4400 9950 4700
Wire Notes Line
	9950 4700 9800 4700
Text Notes 9900 4700 1    59   ~ 0
DHT11
Text Notes 10050 4400 0    39   ~ 0
+
Text Notes 10050 4500 0    39   ~ 0
out
Text Notes 10050 4700 0    39   ~ 0
-
Wire Wire Line
	3700 5600 8500 5600
Wire Wire Line
	8500 5600 8500 5200
Wire Wire Line
	8500 5200 9500 5200
Wire Wire Line
	3700 5500 8400 5500
Wire Wire Line
	8400 5500 8400 5100
Wire Wire Line
	8400 5100 9500 5100
Wire Wire Line
	8400 4800 9500 4800
Wire Wire Line
	8300 4900 9500 4900
Wire Wire Line
	8200 5000 9500 5000
Wire Wire Line
	8200 5000 8200 4950
Wire Wire Line
	8200 4950 3700 4950
Wire Wire Line
	3700 4850 8300 4850
Wire Wire Line
	8300 4850 8300 4900
Wire Wire Line
	3700 4750 8400 4750
Wire Wire Line
	8400 4750 8400 4800
Wire Wire Line
	3700 4650 8400 4650
Wire Wire Line
	8400 4650 8400 4600
Wire Wire Line
	8400 4600 9500 4600
Wire Wire Line
	6100 4350 6050 4350
Wire Wire Line
	5500 4350 5550 4350
Wire Wire Line
	3700 4550 5800 4550
Wire Wire Line
	5800 4550 5800 4500
$EndSCHEMATC
