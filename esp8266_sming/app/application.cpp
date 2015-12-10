#include <user_config.h>
#include <SmingCore/SmingCore.h>

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
	#define WIFI_SSID "PleaseEnterSSID" // Put you SSID and Password here
	#define WIFI_PWD "PleaseEnterPass"
#endif

// Forward declarations
void startMqttClient();
void onMessageReceived(String topic, String message);
void onDataCallback(Stream& stream, char arrivedChar, unsigned short availableCharsCount);

Timer procTimer;
//String Message = "";
//char Message[] = {""};

// MQTT client
// For quickly check you can use: http://www.hivemq.com/demos/websocket-client/ (Connection= test.mosquitto.org:8080)
MqttClient mqtt("broker.mqtt.your.network", 1883, onMessageReceived);

// Legge lo stream della seriale e lo mette sulla variabile "Message" come stringa
// Credo che questa funzione sia in un ".h/.cpp" del framework. Funziona ? La uso ;)
// Aggiungo l'invio del dato al broker mqtt.
void onDataCallback(Stream& stream, char arrivedChar, unsigned short availableCharsCount)
{
  String Message = "";  // Inizializzo stringa da inviare al broker mqtt
  if (arrivedChar == '\n')
  {
    Serial.println("<New line received>");
    while (stream.available())
    {
      char cur = stream.read();
      Serial.print(cur);
      Message += cur;   // Aggiunge caratteri (cur) alla stringa
    }

  Message.remove(Message.length()-2);   // Elimino dalla stringa i caratteri "\" e "n", perche` inviano un CR

  if (mqtt.getConnectionState() != eTCS_Connected)
    startMqttClient(); // Auto reconnect

  // Promemoria
  Serial.println("##### PROMEMORIA #####");
  Serial.println("Sottoscrizione a: main/status/#");
  Serial.println("Pubblicazione sul topic: temperature/esp8266");
  Serial.println("--------------------------------------------");

  Serial.println("Let's publish message now!");
  mqtt.publish("temperature/esp8266", String(Message)); // or publishWithQoS
  }
}


// Callback for messages, arrived from MQTT server
void onMessageReceived(String topic, String message)
{
	Serial.print(topic);
	Serial.print(":\r\n\t"); // Prettify alignment for printing
	Serial.println(message);
}

// Run MQTT client
void startMqttClient()
{
	if(!mqtt.setWill("last/will","The connection from this device is lost:(", 1, true)) {
		debugf("Unable to set the last will and testament. Most probably there is not enough memory on the device.");
	}
	mqtt.connect("esp8266");
	mqtt.subscribe("main/status/#");
}

// Will be called when WiFi station was connected to AP
void connectOk()
{
	Serial.println("I'm CONNECTED");

	// Run MQTT client
	startMqttClient();

    // Boh ?!?! ??????????????????????????????????????????????????????????????????????
    // Pero`, m'e` venuto un dubbio, tutte le direttive "forward" chiamate all'inizio,
    // forse funzionano come un "loop", il problema e` che devono essere richiamate
    // almeno una volta dal programma, da quel momento in poi, lavorano sempre.
    Serial.setCallback(onDataCallback);

    Serial.println("Inizializzazione completata!");

}

// Will be called when WiFi station timeout was reached
void connectFail()
{
	Serial.println("I'm NOT CONNECTED. Need help :(");

	// .. some you code for device configuration ..
}

/*
  Non so, ma qua, non sembra sia mai chiamata
*/
// Will be called when WiFi hardware and software initialization was finished
// And system initialization was completed
void ready()
{
	debugf("READY!");
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(false); // Debug output to serial

	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiStation.enable(true);
	WifiAccessPoint.enable(false);

	// Run our method when station was connected to AP (or not connected)
	WifiStation.waitConnection(connectOk, 20, connectFail); // We recommend 20+ seconds for connection timeout at start
}
