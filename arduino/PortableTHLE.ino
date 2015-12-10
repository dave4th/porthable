/*
 * Programma per la lettura di una sonda DHT11, ovvero, Temperatura e Umidita`.
 * Oltre alla visualizzazione su schermo TFT LCD dei valori in formato testo,
 * viene realizzato un grafico temporale, con l'ausilio di un integrato DS1302
 * con relativo modulo completo di batteria tampone.
 * Se possibile, sara` aggiunto un ESP8266 per la trasmissione dei dati o
 * per la lettura tramite pagina web, da decidere ...
 * 
 * PortableTHLE:
 * . Temperatura
 * . Umidita`
 * . LCD
 * . ESP8266
 */

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <dht.h>
#include <DS1302RTC.h>
#include <Time.h>
#include <SoftwareSerial.h>

// TFT LCD
// pin definition for the LCD (Uno, Nano)
#define cs   10
#define dc   8
#define rst  9

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

// DHT11, Sensore di temperatura e umidita`
dht DHT;
#define DHT11_PIN 4

float Humidity;
float Temperature;
float MemHumidity = 0;
float MemTemperature = 0;

// Init the DS1302
// Set pins:  CE, IO,CLK
DS1302RTC RTC(5, 6, 7);

// ESP8266
SoftwareSerial ESP(2,3); // RX e` il 2,TX e` il 3, collegati a ESP8266

/*
 * Variabili accessorie per stampe sul display e memorizzazioni
 */
// char array to print to the screen, only Humidity & Temperature ?
char SensorTPrintout[6];
char SensorHPrintout[6];
char DataPrintout[11];
char TimePrintout[9];

// e memorie ..
char MemSensorHPrintout[6];
char MemSensorTPrintout[6];
char MemDataPrintout[11];
char MemTimePrintout[9];

//int Second = 0;
//int Minute = 0;
//int Day = 0;
int MemSecond = 0;
int MemMinute = 0;
int MemDay = 0;

// int array per creazione grafico
/*
 * Ho dovuto usare degli interi, sia per limitare l'uso di memoria
 * che per ragioni pratiche di stampa del grafico tramite accensione
 * dei pixel dello schermo LCD
 */
int ArrayTemperature[128];
int ArrayHumidity[128];
int CycleArray = 0; // Valori ciclici da 0 a 127

void writeTextStatic() {
  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  // set the font size
  TFTscreen.setTextSize(1);
  // write the text to the top left corner of the screen
  // write the text
  TFTscreen.text("Data       Ora\n ", 0, 0);
  // write the text
  TFTscreen.text("Umidita`\n ", 0, 16);
  // write the text
  TFTscreen.text("Temperatura\n ", 0, 32);
}

void print2digits(int number) {
  if (number >= 0 && number < 10)
    Serial.write('0');
  Serial.print(number);
}

void setup() {
  // Setup Serial connection
  Serial.begin(9600);

  // Setup serial ESP8266
  ESP.begin(115200);
  ESP.setTimeout(15000);
  
  Serial.println("DS1302RTC Read Test");
  Serial.println("-------------------");
  
  // Activate RTC module
  Serial.println("RTC module activated");
  Serial.println();
  delay(500);
  
  if (RTC.haltRTC()) {
    Serial.println("The DS1302 is stopped.  Please run the SetTime");
    Serial.println("example to initialize the time and begin running.");
    Serial.println();
  }
  if (!RTC.writeEN()) {
    Serial.println("The DS1302 is write protected. This normal.");
    Serial.println();
  }
  
  //delay(5000);

  // TFT
  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  writeTextStatic();
  
  delay(2000);
}

void loop() {

  //RTC
  tmElements_t tm;
  
  Serial.print("UNIX Time: ");
  Serial.print(RTC.get());

  if (! RTC.read(tm)) {
    Serial.print("  Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.print(", DoW = ");
    Serial.print(tm.Wday);
    Serial.println();
  } else {
    Serial.println("DS1302 read error!  Please check the circuitry.");
    Serial.println();
    delay(9000);
  }

  // DHT11
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
  }
  // DISPLAY DATA
  Temperature = DHT.temperature;
  Humidity = DHT.humidity;
  Serial.print(Humidity, 1);
  Serial.print(",\t");
  Serial.println(Temperature, 1);

  // LCD
  // Read the value from DHT11
  String sensorValH = String(Humidity);
  String sensorValT = String(Temperature);
  
  // convert the reading to a char array
  sensorValH.toCharArray(SensorHPrintout, 6);
  sensorValT.toCharArray(SensorTPrintout, 6);
  
  // Read the value from
  // String DataValT = String(tmYearToCalendar(tm.Year) + tm.Month + tm.Day + tm.Hour + tm.Minute + tm.Second); CALCOLA INVECE DI CONCATENARE !
  String DataVal1 = String(tmYearToCalendar(tm.Year));
  String DataVal2 = String(DataVal1 + "-" + tm.Month);
  String DataValDay = String(DataVal2 + "-" + tm.Day);
  String DataVal3 = String(tm.Hour);
  String DataVal4 = String(DataVal3 + ":" + tm.Minute);
  String DataValTime = String(DataVal4 + ":" + tm.Second);
  int Second = tm.Second;
  DataValDay.toCharArray(DataPrintout, 11);
  DataValTime.toCharArray(TimePrintout, 9);
  
  // ste the font size for date/time
  TFTscreen.setTextSize(1);

  // Date/time
  /*
   *  Se valore e` diverso dalla memoria,
   *  [ri]scrivo la memoria e poi il valore,
   *  poi metto la memoria uguale al valore
   */
  if (tm.Day != MemDay) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemDataPrintout, 0, 8);
    // set the font color
    TFTscreen.stroke(255, 255, 0);
    // print
    TFTscreen.text(DataPrintout, 0, 8);
    // Memorie
    MemDay = tm.Day;
    strcpy (MemDataPrintout, DataPrintout);
  }

  if (tm.Second != MemSecond) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemTimePrintout, 66, 8);
    // set the font color
    TFTscreen.stroke(255, 255, 0);
    // print
    TFTscreen.text(TimePrintout, 66, 8);
    // Memorie
    MemSecond = tm.Second;
    strcpy (MemTimePrintout, TimePrintout);
  }

  // ste the font size for date/time
  TFTscreen.setTextSize(2);

  // Humidity
  if (Humidity != MemHumidity) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemSensorHPrintout, 66, 16);
    // set the font color
    TFTscreen.stroke(0, 255, 0);
    // print the sensor value
    TFTscreen.text(SensorHPrintout, 66, 16);
    MemHumidity = Humidity;
    strcpy (MemSensorHPrintout, SensorHPrintout);
  }

  // Temperature
  if (Temperature != MemTemperature) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemSensorTPrintout, 66, 32);
    // set the font color
    TFTscreen.stroke(255, 0, 0);
    // print the sensor value
    TFTscreen.text(SensorTPrintout, 66, 32);
    ESP.println(SensorTPrintout); // ESP8266
    MemTemperature = Temperature;
    strcpy (MemSensorTPrintout, SensorTPrintout);
  }


  // Adesso ho messo SECONDI, solo per velocizzare i test
  //if (Minute != MemMinute) {
  if (tm.Minute != MemMinute) {
    // Stampa array su LCD
    /*
    * Stampa i 128 (come i pixel) valori di temperatura e umidita`,
    * creando un grafico.
    * Al solito, devo prima eliminare la scritta precedente 
    * e poi mettere la nuova.
    */
    // Prima cancello le scritte
    TFTscreen.stroke(0, 0, 0);
    for (CycleArray = 127; CycleArray >= 0; CycleArray--) {
      TFTscreen.point(CycleArray, 127 - ArrayHumidity[CycleArray]);
      TFTscreen.point(CycleArray, 127 - ArrayTemperature[CycleArray]);
    }
    // Poi shifto e aggiorno con l'ultimo valore
    for (CycleArray = 0; CycleArray <= 126; CycleArray++) {
      ArrayHumidity[CycleArray] = ArrayHumidity[CycleArray+1];
      ArrayTemperature[CycleArray] = ArrayTemperature[CycleArray+1];
    }
    // Quando finisce e` al 127 e posso scrivere il dato nuovo
    ArrayHumidity[CycleArray] = Humidity;
    ArrayTemperature[CycleArray] = Temperature;
    MemMinute = tm.Minute;
    // Scrivo ..
    for (CycleArray = 127; CycleArray >= 0; CycleArray--) {
      TFTscreen.stroke(0, 255, 0);
      TFTscreen.point(CycleArray, 127 - ArrayHumidity[CycleArray]);
      TFTscreen.stroke(255, 0, 0);
      TFTscreen.point(CycleArray, 127 - ArrayTemperature[CycleArray]);
    }
  }

/*
  // Stampe a video (seriale) per verifiche
  Serial.print("\n"); 
  Serial.print(DHT.humidity);
  Serial.print(",\t");
  Serial.print(DHT.temperature);

  Serial.print("\n");
  Serial.print(sensorValH);
  Serial.print(",\t");
  Serial.print(sensorValT);
  
  Serial.print("\n");
  Serial.print(SensorHPrintout);
  Serial.print(",\t");
  Serial.print(SensorTPrintout);
  
  Serial.print("\n");
  Serial.print(MemSensorHPrintout);
  Serial.print(",\t");
  Serial.print(MemSensorTPrintout);
  
  Serial.print("\nHumidity, Temperature\n");
  Serial.print(Humidity);
  Serial.print(",\t");
  Serial.print(Temperature);
  
  Serial.print("\n");
  Serial.print(MemHumidity);
  Serial.print(",\t");
  Serial.print(MemTemperature);
  
  Serial.print("\nDataValT, DataPrintout\n");
  Serial.print(DataValT);
  Serial.print(",\t");
  Serial.print(DataPrintout);
  
  Serial.print("\nSecond, Memory\n");
  Serial.print(Second);
  Serial.print(",\t");
  Serial.print(MemSecond);
  Serial.print("\n");

  Serial.print("\nLarghezza, Altezza\n");
  Serial.print(TFTscreen.width());
  Serial.print(",\t");
  Serial.print(TFTscreen.height());
  Serial.print("\n");
  
  Serial.print("\nMinuti,\n");
  Serial.print(tm.Minute);
  Serial.print(",\t");
  Serial.print(MemMinute);
  Serial.print(",\t");
  Serial.print(CycleArray);
  Serial.print("\n");
  
  Serial.print("\nArray ...\n");
  int i;
  for (i = 0; i < 128; i = i + 1) {
    Serial.print(ArrayTemperature[i]);
    Serial.print(",");
  }
  Serial.print("\n");
  //int i;
  for (i = 0; i < 128; i = i + 1) {
    Serial.print(ArrayHumidity[i]);
    Serial.print(",");
  }
  Serial.print("\n");

  /*
  TFTscreen.stroke(255, 0, 0);
  // draw a pixel in the screen's center
  TFTscreen.point(TFTscreen.width()/2, TFTscreen.height()/2);
  TFTscreen.point(64, 64);
  TFTscreen.point(65, 65);
  TFTscreen.point(66, 66);
  */
  
  /*
   * Mi sa che i delay serva per la stabilita` delle letture
   * Cerco di tenerlo il piu` basso possibile, a 200 funziona, metto 300 per sicurezza
   */
  delay(300);
}
