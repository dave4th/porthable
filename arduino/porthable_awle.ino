/*
 * Programma per la lettura di una sonda di Temperatura.
 * Oltre alla visualizzazione su schermo TFT LCD dei valori in formato testo,
 * viene realizzato un grafico temporale, con l'ausilio di un ESP8266.
 * Tramite quest'ultimo, i dati delle letture verranno inviati ad un MQTT Broker.
 * 
 * Versione OneWire w/ MQTT: porthable AWLE
 * . ATMEGA
 * . DS18B20 (1 Wire)
 * . LCD TFT 1,44"
 * . ESP8266 su seriale standard arduino
 * . Potenziometro per regolazione tempi grafico
 */

#include <TFT.h>  // Arduino LCD library
//#include <SPI.h>
//#include <dht11.h>  // Cambio libreria
//#include <DS1302RTC.h>
//#include <Time.h>
//#include <SoftwareSerial.h> // ESP8266
#include <TimeLib.h>        // Libreria per gestione data/ora
#include <OneWire.h>

// TFT LCD
// pin definition for the LCD (Uno, Nano)
#define cs   10
#define dc   8
#define rst  9

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

// DHT11, Sensore di temperatura e umidita`
//dht11 DHT;
//#define DHT11_PIN 4

OneWire  ds(4);  // on pin 4 (a 4.7K resistor is necessary)

//int ReadHumidity = 0;
int ReadTemperature = 0;
//int Humidity = 0;
int Temperature = 0;
//int MemReadHumidity = 0;
int MemReadTemperature = 0;
//int MemHumidity = 0;
int MemTemperature = 0;

// Init the DS1302
// Set pins:  CE, IO,CLK
//DS1302RTC RTC(5, 6, 7);

// ESP8266
//SoftwareSerial espSerial(2,3); // RX e` il 2,TX e` il 3, collegati a ESP8266

/*
 * Variabili accessorie per stampe sul display e memorizzazioni
 */
// char array to print to the screen, only Humidity & Temperature ?
char SensorTPrintout[3];
//char SensorHPrintout[3];
char DataPrintout[11];
char TimePrintout[9];

// e memorie ..
//char MemSensorHPrintout[6];
char MemSensorTPrintout[6];
char MemDataPrintout[11];
char MemTimePrintout[9];

int Day = 1;
int Month = 1;
int Year = 2016;
int Hours = 1;
int Minutes = 1;
int Seconds = 1;
int MemSeconds = 0;
int MemMinutes = 1;
int MemHours = 0; // Aggiunta per aggiornamento dell'orario (che non funziona bene ?)
int MemDay = 0;

// int array per creazione grafico
/*
 * Ho dovuto usare degli interi, sia per limitare l'uso di memoria
 * che per ragioni pratiche di stampa del grafico tramite accensione
 * dei pixel dello schermo LCD
 */
int ArrayTemperature[128];
//int ArrayHumidity[128];
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
  //TFTscreen.text("Umidita`", 0, 16);
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
  //TFTscreen.text("%\n ", 103, 16);
  // write the text
  TFTscreen.text("C\n ", 103, 32);
  
}

/*
 * Era usata dalla RTC, non serve ora.
void print2digits(int number) {
  if (number >= 0 && number < 10)
    Serial.write('0');
  Serial.print(number);
}
 */

void setup() {

  /*
  * Visto che si avvia sempre con orario 1970 ....
  * fisso una data che permetta il corretto funzionamento,
  * altrimenti il grafico inizia sempre all'accensione,
  * mentre deve rispettare la mezz'ora impostata.
  * 
  * setTime(Ora,Minuti,Secondi,Giorno,Mese,Anno);
  */
  setTime(Hours,Minutes,Seconds,Day,Month,Year); // alternative to above, yr is 2 or 4 digit yr (2010 or 10 sets year to 2010)

  // Setup Serial connection
  Serial.begin(9600);

  //Serial.println("Serial.begin(9600)");

  // Setup serial ESP8266
  //espSerial.begin(9600);
  //Serial.println("espSerial.begin(9600)");

  //espSerial.setTimeout(15000);
  
/*
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
*/

  // TFT
  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  writeTextStatic();
  
  delay(2000);
  //Serial.println("* END setup! *");

}

void loop() {

  //Serial.println("* Start LOOP *");
/*
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
*/

/* Ho eliminato totalmente la parte DHT11 */

  /* DS18x20 */
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  
  if ( !ds.search(addr)) {
    //Serial.println("No more addresses.");
    //Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  
  //Serial.print("ROM =");
  //for( i = 0; i < 8; i++) {
  //  Serial.write(' ');
  //  Serial.print(addr[i], HEX);
  //}

  //if (OneWire::crc8(addr, 7) != addr[7]) {
  //    Serial.println("CRC is not valid!");
  //    return;
  //}
  //Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      //Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      //Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      //Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      //Serial.println("Device is not a DS18x20 family device.");
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  //Serial.print("  Data = ");
  //Serial.print(present, HEX);
  //Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    //Serial.print(data[i], HEX);
    //Serial.print(" ");
  }
  //Serial.print(" CRC=");
  //Serial.print(OneWire::crc8(data, 8), HEX);
  //Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  //Serial.print("  Temperature = ");
  //Serial.print(celsius);
  //Serial.print(" Celsius, ");
  //Serial.print(fahrenheit);
  //Serial.println(" Fahrenheit");
/* END */

ReadTemperature = int(celsius);

  /*
   * Visto che il valore letto e` incostante, aggiungo un ciclo di conferma 
   * prima di memorizzare:
   * 
   * Se temperatura letta divera, 
   * e se la memoria e` diversa da quella in lettura ..
   * memorizzo,
   * se e` uguale,
   * metto la memoria in "valore ok"
   */
/*
  if (ReadHumidity != Humidity) {
    if (MemReadHumidity != ReadHumidity) {
      MemReadHumidity = ReadHumidity;
    }
    else {
      Humidity = MemReadHumidity;
    }
  }
*/
  if (ReadTemperature != Temperature) {
    if (MemReadTemperature != ReadTemperature) {
      MemReadTemperature = ReadTemperature;
    }
    else {
      Temperature = MemReadTemperature;
    }
  }
  /* Fine controllo e memorizzazione nuovi valori */

  // DISPLAY DATA
  //Serial.print(Humidity, 1);
  //Serial.print(",\t");
  //Serial.println(Temperature, 1);

  // LCD
  // Read the value from DHT11
  //String sensorValH = String(Humidity);
  String sensorValT = String(Temperature);
  
  // convert the reading to a char array
  //sensorValH.toCharArray(SensorHPrintout, 3);
  sensorValT.toCharArray(SensorTPrintout, 3);

  // Gestione DATA/ORA proveniente da ESP8266 via seriale
  while (Serial.available() > 0) {
    String inString = Serial.readStringUntil('\n');
    //Serial.println(inString);
    // Se la stringa inizia per ... la riga successiva conterra` la data e ora
    if (inString.startsWith("Date:")) {
      Day = Serial.parseInt();
      Month = Serial.parseInt();
      Year = Serial.parseInt();
      Hours = Serial.parseInt();
      Minutes = Serial.parseInt();
      Seconds = Serial.parseInt();
      //Serial.println(now());
    }
    // Ogni ora aggiorno ..
  }
  
  if (Hours != MemHours) {
    setTime(Hours,Minutes,Seconds,Day,Month,Year); // alternative to above, yr is 2 or 4 digit yr (2010 or 10 sets year to 2010)
    MemHours = Hours;
  }

  /*
   * Queste le devo comunque eseguire ..
   * servono per la conversione in stringa e la stampa sul display
   * (Ho messo i "." come la stringa dell'ESP)
   */
  String DataVal1 = String(year());
  String DataVal2 = String(DataVal1 + "." + month());
  String DataValDay = String(DataVal2 + "." + day());
  String DataVal3 = String(hour());
  String DataVal4 = String(DataVal3 + ":" + minute());
  String DataValTime = String(DataVal4 + ":" + second());
  DataValDay.toCharArray(DataPrintout, 11);
  DataValTime.toCharArray(TimePrintout, 9);
  
  // set the font size for date/time
  TFTscreen.setTextSize(1);

  // Date/time
  /*
   *  Se valore e` diverso dalla memoria,
   *  [ri]scrivo la memoria e poi il valore,
   *  poi metto la memoria uguale al valore
   */
  if (Day != MemDay) {
    /*Serial.print("Compare: ");
    Serial.print(MemDataPrintout);
    Serial.print(" - ");
    Serial.println(DataPrintout);*/
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemDataPrintout, 0, 8);
    // set the font color
    TFTscreen.stroke(255, 255, 0);
    // print
    TFTscreen.text(DataPrintout, 0, 8);
    // Memorie
    MemDay = Day;
    strcpy (MemDataPrintout, DataPrintout);
  }

  /*
   * L'utilizzo dei secondi non e` propriamente corretto, perche` potrebbe
   * per pura coincidenza, ripetersi un cambio lettura al medesimo "secondo"
   * ma di un minuto/i successivo/i .. solo che non funziona la comparazione
   * fra le stringhe ..
   */
  if (second() != MemSeconds) {
    /*Serial.print("Compare: ");
    Serial.print(MemTimePrintout);
    Serial.print(" - ");
    Serial.println(TimePrintout);*/
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemTimePrintout, 66, 8);
    // set the font color
    TFTscreen.stroke(255, 255, 0);
    // print
    TFTscreen.text(TimePrintout, 66, 8);
    // Memorie
    MemSeconds = second();
    strcpy (MemTimePrintout, TimePrintout);
  }

  // set the font size for humidity/temperature
  TFTscreen.setTextSize(2);

/*
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
*/

  // Temperature
  if (Temperature != MemTemperature) {
    // erase the text you just wrote
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text(MemSensorTPrintout, 76, 32);
    // set the font color
    TFTscreen.stroke(255, 0, 0);
    // print the sensor value
    TFTscreen.text(SensorTPrintout, 76, 32);
    //Serial.println(SensorTPrintout); // ESP8266
    Serial.println(celsius); // Stavolta metto il dato float
    MemTemperature = Temperature;
    strcpy (MemSensorTPrintout, SensorTPrintout);
  }

  // set the font size for potentiometer
  TFTscreen.setTextSize(1);

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
   * Aggiorno ogni X-minuto/i non m'interessa da quando ho acceso,
   * preferisco sia "fisso", come i termostati in casa ..
   * 
   * Aggiorna una sola volta nello stesso minuto, 
   * e aggiorna solo se la divisione non da` resto
   */
  if (minute() != MemMinutes && (minute() % TimeGraph == 0)) {
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
      //TFTscreen.point(CycleArray, 127 - ArrayHumidity[CycleArray]);
      TFTscreen.point(CycleArray, 127 - ArrayTemperature[CycleArray]);
    }
    // Poi shifto e aggiorno con l'ultimo valore
    for (CycleArray = 0; CycleArray <= 126; CycleArray++) {
      //ArrayHumidity[CycleArray] = ArrayHumidity[CycleArray+1];
      ArrayTemperature[CycleArray] = ArrayTemperature[CycleArray+1];
    }
    // Quando finisce e` al 127 e posso scrivere il dato nuovo
    //ArrayHumidity[CycleArray] = Humidity;
    ArrayTemperature[CycleArray] = Temperature;
    // Memorizzo il tempo attuale
    MemMinutes = minute();
    // Scrivo ..
    for (CycleArray = 127; CycleArray >= 0; CycleArray--) {
      //TFTscreen.stroke(0, 255, 0);
      //TFTscreen.point(CycleArray, 127 - ArrayHumidity[CycleArray]);
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
