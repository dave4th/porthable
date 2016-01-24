/*
 * Programma per la lettura di una sonda DHT11, ovvero, Temperatura e Umidita`.
 * Oltre alla visualizzazione su schermo TFT LCD dei valori in formato testo,
 * viene realizzato un grafico temporale, con l'ausilio di un integrato DS1302
 * con relativo modulo completo di batteria tampone.
 * 
 * Version base: porthable ADLD
 * . ATMEGA
 * . DHT11
 * . LCD TFT 1,44"
 * . DS1302
 * . Potenziometro per regolazione tempi grafico
 */

#include <TFT.h>  // Arduino LCD library
//#include <SPI.h>
#include <dht.h>
#include <DS1302RTC.h>
//#include <Time.h>
//#include <SoftwareSerial.h> // ESP8266

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

int Humidity;
int Temperature;
int MemHumidity = 0;
int MemTemperature = 0;

// Init the DS1302
// Set pins:  CE, IO,CLK
DS1302RTC RTC(5, 6, 7);

// ESP8266
//SoftwareSerial ESP(2,3); // RX e` il 2,TX e` il 3, collegati a ESP8266

/*
 * Variabili accessorie per stampe sul display e memorizzazioni
 */
// char array to print to the screen, only Humidity & Temperature ?
char SensorTPrintout[3];
char SensorHPrintout[3];
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
int MemSeconds = 0;
int MemMinutes = 30; // Cosi` inizia sempre ad ogni ora.
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

//Variabili per Potenziometro
int PotPin = A0;
int PotValue = 0;
int TimeGraph = 0;
int MemTimeGraph = 0;
char TimeGraphPrintout[3];
char MemTimeGraphPrintout[3];
// e Grafico
char TotalTimeGraphPrintout[5];
char MemTotalTimeGraphPrintout[5];

void writeTextStatic() {
  /*
   * Le lettere sono alte 7 e larghe 5
   * Quindi considerare 6 di occupazione orizzontale
  */ 
  // write the static text to the screen
  // set the font color to gray
  TFTscreen.stroke(128, 128, 128);
  // set the font size
  TFTscreen.setTextSize(1);
  // write the text to the top left corner of the screen
  // write the text
  TFTscreen.text("Data       Ora", 0, 0);
  // write the text
  TFTscreen.text("Umidita`", 0, 16);
  // write the text
  TFTscreen.text("Temperatura", 0, 32);
  // write the text
  TFTscreen.text("Campionamento", 0, 48);
  // write the text
  TFTscreen.text("min.", 103, 48);
  // write the text
  TFTscreen.text("In memoria", 0, 56);
  // write the text
  TFTscreen.text("min.", 103, 56);
  /*
   * Volevo mettere delle tacche, ha senso ?
   * .. write ..
   */
  TFTscreen.stroke(64, 64, 64);  // gray 75%
  TFTscreen.text("50 -  -  -  -  -  -  -", 0, 74);
  TFTscreen.text("40 -  -  -  -  -  -  -", 0, 84);
  TFTscreen.text("30 -  -  -  -  -  -  -", 0, 94);
  TFTscreen.text("20 -  -  -  -  -  -  -", 0, 104);
  TFTscreen.text("10 -  -  -  -  -  -  -", 0, 114);
  TFTscreen.text("0", 0, 120);
  
  // set the font color to white
  TFTscreen.stroke(128, 128, 128);
  // set the font size
  TFTscreen.setTextSize(2);
  // write the text
  TFTscreen.text("%\n ", 103, 16);
  // write the text
  TFTscreen.text("C\n ", 103, 32);
  
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
  //ESP.begin(115200);
  //ESP.setTimeout(15000);
  
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
  sensorValH.toCharArray(SensorHPrintout, 3);
  sensorValT.toCharArray(SensorTPrintout, 3);
  
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

  if (tm.Second != MemSeconds) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemTimePrintout, 66, 8);
    // set the font color
    TFTscreen.stroke(255, 255, 0);
    // print
    TFTscreen.text(TimePrintout, 66, 8);
    // Memorie
    MemSeconds = tm.Second;
    strcpy (MemTimePrintout, TimePrintout);
  }

  // ste the font size for date/time
  TFTscreen.setTextSize(2);

  // Humidity
  if (Humidity != MemHumidity) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemSensorHPrintout, 76, 16);
    // set the font color
    TFTscreen.stroke(0, 255, 0);
    // print the sensor value
    TFTscreen.text(SensorHPrintout, 76, 16);
    MemHumidity = Humidity;
    strcpy (MemSensorHPrintout, SensorHPrintout);
  }

  // Temperature
  if (Temperature != MemTemperature) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemSensorTPrintout, 76, 32);
    // set the font color
    TFTscreen.stroke(255, 0, 0);
    // print the sensor value
    TFTscreen.text(SensorTPrintout, 76, 32);
    //ESP.println(SensorTPrintout); // ESP8266
    MemTemperature = Temperature;
    strcpy (MemSensorTPrintout, SensorTPrintout);
  }

  /*
   * Inserisco qua la gestione del potenziometro e del grafico
   */
  PotValue = analogRead(PotPin);
  TimeGraph = map(PotValue,0,1023,1,31);  // da 1 a 30 minuti, ho dovuto restringere il campo causa sensibilita` potenziometro
  // Potenziometro
  String stringTimeGraph = String(TimeGraph);
  // convert the reading to a char array
  stringTimeGraph.toCharArray(TimeGraphPrintout, 3);
  // Grafico
  String stringTimeGraph128 = String(TimeGraph * 128);
  // convert the reading to a char array
  stringTimeGraph128.toCharArray(TotalTimeGraphPrintout, 5);
  if (TimeGraph != MemTimeGraph) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemTimeGraphPrintout, 88, 48);
    TFTscreen.text(MemTotalTimeGraphPrintout, 76, 56);
    // set the font color
    TFTscreen.stroke(0, 0, 255);
    // print the sensor value
    TFTscreen.text(TimeGraphPrintout, 88, 48);
    TFTscreen.text(TotalTimeGraphPrintout, 76, 56);
    MemTimeGraph = TimeGraph;
    strcpy (MemTimeGraphPrintout, TimeGraphPrintout);
    strcpy (MemTotalTimeGraphPrintout, TotalTimeGraphPrintout);
  }

  /*
   * Devo stare attento perche` questa routine dev'essere eseguita
   * una sola volta, quindi: ATTENZIONE alle condizioni!
   * 
   * Aggiorno ogni mezz'ora e non m'interessa da quando ho acceso,
   * preferisco sia "fisso", come i termostati in casa ..
   */
  // Questa riga aggiorna ogni minuto
  //if (tm.Minute != MemMinutes) {
  // Questa riga era com'era prima del potenziometro
  //if (tm.Minute != MemMinutes && (tm.Minute == 0 || tm.Minute == 30)) {
  if (tm.Minute != MemMinutes && (tm.Minute % TimeGraph == 0)) {
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
    // Memorizzo il tempo attuale
    MemMinutes = tm.Minute;
    // Scrivo ..
    for (CycleArray = 127; CycleArray >= 0; CycleArray--) {
      TFTscreen.stroke(0, 255, 0);
      TFTscreen.point(CycleArray, 127 - ArrayHumidity[CycleArray]);
      TFTscreen.stroke(255, 0, 0);
      TFTscreen.point(CycleArray, 127 - ArrayTemperature[CycleArray]);
    }
  }

  /*
   * Mi sa che i delay serva per la stabilita` delle letture
   * Cerco di tenerlo il piu` basso possibile, a 200 funziona, metto 300 per sicurezza
   */
  delay(300);
}
