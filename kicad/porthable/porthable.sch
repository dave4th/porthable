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
Date "27 dec 2015"
Rev "0.0.3"
Comp "mail4davide@gmail.com"
Comment1 "+ ESP8266, DS1302, Seriali e Programmazione"
Comment2 "ATmega328 w/ DHT11, TFT LCD"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DISPLAY_128X128SPI S1
U 1 1 565B3034
P 6300 1700
F 0 "S1" H 6100 1450 60  0000 C CNN
F 1 "DISPLAY_128X128SPI" H 6650 750 60  0000 C CNN
F 2 "~" H 7050 1100 60  0000 C CNN
F 3 "~" H 7050 1100 60  0000 C CNN
	1    6300 1700
	1    0    0    1   
$EndComp
$Comp
L CONN_4X2 U2
U 1 1 566699E3
P 8650 1300
F 0 "U2" H 8650 1550 50  0000 C CNN
F 1 "ESP8266" V 8650 1300 40  0000 C CNN
F 2 "" H 8650 1300 60  0000 C CNN
F 3 "" H 8650 1300 60  0000 C CNN
	1    8650 1300
	0    -1   -1   0   
$EndComp
$Comp
L CONN_5 P3
U 1 1 56669A09
P 10400 1300
F 0 "P3" V 10350 1300 50  0000 C CNN
F 1 "DS1302" V 10450 1300 50  0000 C CNN
F 2 "" H 10400 1300 60  0000 C CNN
F 3 "" H 10400 1300 60  0000 C CNN
	1    10400 1300
	0    -1   -1   0   
$EndComp
Text Notes 10200 1850 1    60   ~ 0
VCC
Text Notes 10300 1850 1    60   ~ 0
GND
Text Notes 10400 1850 1    60   ~ 0
CLK
Text Notes 10500 1850 1    60   ~ 0
DAT
$Comp
L CONN_3 P2
U 1 1 5666A2A2
P 9600 1350
F 0 "P2" V 9550 1350 50  0000 C CNN
F 1 "DHT11" V 9650 1350 40  0000 C CNN
F 2 "" H 9600 1350 60  0000 C CNN
F 3 "" H 9600 1350 60  0000 C CNN
	1    9600 1350
	0    -1   -1   0   
$EndComp
Text Notes 9500 1800 1    60   ~ 0
+
Text Notes 9700 1800 1    60   ~ 0
-
Text Notes 9600 1800 1    60   ~ 0
out
Text Notes 8500 1800 1    60   ~ 0
TX0
Text Notes 8800 950  1    60   ~ 0
RX0
Text Notes 8500 950  1    60   ~ 0
GND
Text Notes 8600 1800 1    60   ~ 0
EN
Text Notes 8800 1800 1    60   ~ 0
VCC
$Comp
L ATMEGA328-P IC1
U 1 1 5666F771
P 3400 4800
F 0 "IC1" H 2650 6050 40  0000 L BNN
F 1 "ATMEGA328-P" H 3800 3400 40  0000 L BNN
F 2 "DIL28" H 3400 4800 30  0000 C CIN
F 3 "" H 3400 4800 60  0000 C CNN
	1    3400 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3700 2500 3700
Wire Wire Line
	1500 4000 2500 4000
Text Notes 10600 1900 1    60   ~ 0
RESET
Wire Wire Line
	1800 2200 1800 7300
Wire Wire Line
	1800 5900 2500 5900
Wire Wire Line
	1800 6000 2500 6000
Connection ~ 1800 5900
Wire Wire Line
	8800 900  8800 700 
Wire Wire Line
	8800 700  9100 700 
Wire Wire Line
	9100 700  9100 5600
Wire Wire Line
	9100 5600 4400 5600
Wire Wire Line
	8500 1700 8500 5500
Wire Wire Line
	8500 5500 4400 5500
Wire Wire Line
	6800 1700 6800 3900
Wire Wire Line
	6800 3900 4400 3900
Wire Wire Line
	6700 1700 6700 3800
Wire Wire Line
	6700 3800 4400 3800
Wire Wire Line
	6600 1700 6600 3700
Wire Wire Line
	6600 3700 4400 3700
Wire Wire Line
	6500 1700 6500 4000
Wire Wire Line
	6400 1700 6400 4200
Wire Wire Line
	10400 1700 10400 6000
Wire Wire Line
	10400 6000 4400 6000
Wire Wire Line
	10500 1700 10500 5900
Wire Wire Line
	10500 5900 4400 5900
Wire Wire Line
	10600 1700 10600 5800
Wire Wire Line
	10600 5800 4400 5800
Wire Wire Line
	9600 5700 9600 1700
Wire Wire Line
	4400 5700 9600 5700
Wire Wire Line
	6300 2000 6300 1700
Wire Wire Line
	7000 2000 7000 1700
Connection ~ 6300 2000
Wire Wire Line
	8600 2000 8600 1700
Connection ~ 7000 2000
Wire Wire Line
	8800 2000 8800 1700
Connection ~ 8600 2000
Wire Wire Line
	9500 2000 9500 1700
Connection ~ 8800 2000
Wire Wire Line
	10200 2000 10200 1700
Connection ~ 9500 2000
Wire Wire Line
	1800 2200 10300 2200
Wire Wire Line
	6900 2200 6900 1700
Wire Wire Line
	8200 2200 8200 700 
Wire Wire Line
	8200 700  8500 700 
Wire Wire Line
	8500 700  8500 900 
Connection ~ 6900 2200
Wire Wire Line
	9700 2200 9700 1700
Connection ~ 8200 2200
Wire Wire Line
	10300 2200 10300 1700
Connection ~ 9700 2200
$Comp
L +3,3V #PWR2
U 1 1 566702A4
P 1600 7300
F 0 "#PWR2" H 1600 7260 30  0001 C CNN
F 1 "+3,3V" H 1600 7410 30  0000 C CNN
F 2 "" H 1600 7300 60  0000 C CNN
F 3 "" H 1600 7300 60  0000 C CNN
	1    1600 7300
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR3
U 1 1 566702B3
P 1800 7300
F 0 "#PWR3" H 1800 7300 30  0001 C CNN
F 1 "GND" H 1800 7230 30  0001 C CNN
F 2 "" H 1800 7300 60  0000 C CNN
F 3 "" H 1800 7300 60  0000 C CNN
	1    1800 7300
	1    0    0    -1  
$EndComp
Connection ~ 1800 6000
$Comp
L C C1
U 1 1 56670337
P 2000 6700
F 0 "C1" H 2000 6800 40  0000 L CNN
F 1 "4,7uF" H 2006 6615 40  0000 L CNN
F 2 "~" H 2038 6550 30  0000 C CNN
F 3 "~" H 2000 6700 60  0000 C CNN
	1    2000 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 6100 2000 6500
Wire Wire Line
	2000 6900 2000 7100
Wire Wire Line
	2000 7100 1800 7100
Connection ~ 1800 7100
$Comp
L R R1
U 1 1 56672AC8
P 4600 2650
F 0 "R1" V 4680 2650 40  0000 C CNN
F 1 "10K" V 4607 2651 40  0000 C CNN
F 2 "~" V 4530 2650 30  0000 C CNN
F 3 "~" H 4600 2650 30  0000 C CNN
	1    4600 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2000 4600 2400
Connection ~ 4600 2000
Wire Wire Line
	4600 2900 4600 5150
Wire Wire Line
	4400 5150 7000 5150
$Comp
L C C3
U 1 1 56672C56
P 5000 2600
F 0 "C3" H 5000 2700 40  0000 L CNN
F 1 "22pF" H 5006 2515 40  0000 L CNN
F 2 "~" H 5038 2450 30  0000 C CNN
F 3 "~" H 5000 2600 60  0000 C CNN
	1    5000 2600
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 56672C6F
P 5800 2600
F 0 "C4" H 5800 2700 40  0000 L CNN
F 1 "22pF" H 5806 2515 40  0000 L CNN
F 2 "~" H 5838 2450 30  0000 C CNN
F 3 "~" H 5800 2600 60  0000 C CNN
	1    5800 2600
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X1
U 1 1 56672C7C
P 5400 3100
F 0 "X1" H 5400 3250 60  0000 C CNN
F 1 "16000M" H 5400 2950 60  0000 C CNN
F 2 "~" H 5400 3100 60  0000 C CNN
F 3 "~" H 5400 3100 60  0000 C CNN
	1    5400 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 4300 4400 4300
Wire Wire Line
	5000 2800 5000 4300
Wire Wire Line
	5800 2800 5800 4400
Wire Wire Line
	5000 2400 5000 2200
Connection ~ 5000 2200
Wire Wire Line
	5800 2200 5800 2400
Connection ~ 5800 2200
Wire Wire Line
	5800 4400 4400 4400
$Comp
L R R2
U 1 1 566C71E2
P 6100 2650
F 0 "R2" V 6180 2650 40  0000 C CNN
F 1 "4.7K" V 6107 2651 40  0000 C CNN
F 2 "~" V 6030 2650 30  0000 C CNN
F 3 "~" H 6100 2650 30  0000 C CNN
	1    6100 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 2000 6100 2400
Connection ~ 6100 2000
Wire Wire Line
	6100 2900 6100 5700
Connection ~ 6100 5700
$Comp
L SW_PUSH SW1
U 1 1 566D2F91
P 4400 2700
F 0 "SW1" H 4550 2810 50  0000 C CNN
F 1 "RESET" H 4400 2620 50  0000 C CNN
F 2 "~" H 4400 2700 60  0000 C CNN
F 3 "~" H 4400 2700 60  0000 C CNN
	1    4400 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 2200 4400 2400
Connection ~ 4400 2200
Wire Wire Line
	4400 3000 4400 3200
Wire Wire Line
	4400 3200 4600 3200
Connection ~ 4600 3200
Wire Notes Line
	3600 3400 4800 3400
Wire Notes Line
	4800 3400 4800 1900
Wire Notes Line
	4800 1900 3600 1900
Wire Notes Line
	3600 1900 3600 3400
Text Notes 3750 3350 1    60   ~ 0
Nella versione finale\nnon servira`, ci sara`\ninterruttore generale\non/off. Il reset sara`\ncollegato alla +VCC\ndirettamente.
Wire Wire Line
	4400 5400 7400 5400
Wire Wire Line
	4400 5300 7400 5300
Wire Wire Line
	5000 3100 5100 3100
Connection ~ 5000 3100
Wire Wire Line
	5700 3100 5800 3100
Connection ~ 5800 3100
Wire Wire Line
	4400 4000 7400 4000
Wire Wire Line
	4400 4200 7400 4200
Connection ~ 6500 4000
Wire Wire Line
	4400 4100 7400 4100
Connection ~ 6400 4200
Connection ~ 4600 5150
Wire Wire Line
	7100 4300 7400 4300
Wire Wire Line
	7100 2200 7100 5200
Connection ~ 7100 2200
Text Notes 7900 3900 0    39   ~ 0
15 (GPIO22)
Text Notes 7900 4000 0    39   ~ 0
19 (GPIO10/MOSI)
Text Notes 7900 4100 0    39   ~ 0
21 (GPIO9/MISO)
Text Notes 7900 4200 0    39   ~ 0
23 (GPIO11/SCLK)
Text Notes 7900 4300 0    39   ~ 0
25 (GND)
$Comp
L SWITCH_INV SW2
U 1 1 567E7B08
P 1500 6700
F 0 "SW2" H 1300 6850 50  0000 C CNN
F 1 "Supply EXT/INT" H 1350 6550 50  0000 C CNN
F 2 "~" H 1500 6700 60  0000 C CNN
F 3 "~" H 1500 6700 60  0000 C CNN
	1    1500 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 2000 10200 2000
Wire Wire Line
	1500 6100 2000 6100
Wire Wire Line
	1600 7200 1600 7300
$Comp
L +3,3V #PWR1
U 1 1 567E7BE8
P 1400 7300
F 0 "#PWR1" H 1400 7260 30  0001 C CNN
F 1 "+3,3V" H 1400 7410 30  0000 C CNN
F 2 "" H 1400 7300 60  0000 C CNN
F 3 "" H 1400 7300 60  0000 C CNN
	1    1400 7300
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 7300 1400 7200
Wire Wire Line
	1500 2000 1500 6200
Connection ~ 1500 6100
Connection ~ 1500 4000
Connection ~ 1500 3700
Text Notes 1600 7600 0    59   ~ 0
Alimentazione\nda Batteria interna
Text Notes 1400 7600 2    59   ~ 0
Alimentazione\nEsterna
Wire Notes Line
	10000 1900 10800 1900
Wire Notes Line
	10800 1900 10800 500 
Wire Notes Line
	10800 500  10000 500 
Wire Notes Line
	10000 500  10000 1900
Text Notes 9900 700  0    59   ~ 0
Da verificare/decidere\nse utilizzare scheda\no componenti singoli
Wire Wire Line
	7100 5200 7400 5200
Connection ~ 7100 4300
$Comp
L CONN_5 P1
U 1 1 567E9538
P 7800 4100
F 0 "P1" V 7750 4100 50  0000 C CNN
F 1 "Program w/R.Pi" V 7850 4100 50  0000 C CNN
F 2 "" H 7800 4100 60  0000 C CNN
F 3 "" H 7800 4100 60  0000 C CNN
	1    7800 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3900 7400 3900
Wire Wire Line
	7000 5150 7000 3900
Text Notes 7900 3800 0    39   ~ 0
[ 17 (+3.3V) ]
$Comp
L CONN_4 P?
U 1 1 567FE68B
P 7750 5250
F 0 "P?" V 7700 5250 50  0000 C CNN
F 1 "Serial" V 7800 5250 50  0000 C CNN
F 2 "" H 7750 5250 60  0000 C CNN
F 3 "" H 7750 5250 60  0000 C CNN
	1    7750 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 5100 7200 5100
Wire Wire Line
	7200 5100 7200 2000
Connection ~ 7200 2000
Text Notes 7900 5200 0    39   ~ 0
GND
Text Notes 7900 5100 0    39   ~ 0
+3,3V
$EndSCHEMATC
