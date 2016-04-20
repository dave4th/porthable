#include <user_config.h>
#include <SmingCore/SmingCore.h>

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
	//#define WIFI_SSID "PleaseEnterSSID" // Put you SSID and Password here
	//#define WIFI_PWD "PleaseEnterPass"
#endif

// ... and/or MQTT username and password
#ifndef MQTT_USERNAME
	#define MQTT_USERNAME ""
	#define MQTT_PWD ""
#endif

// ... and/or MQTT host and port
#ifndef MQTT_HOST
	#define MQTT_HOST "level1"
	#define MQTT_PORT 1883
#endif

/* (My) User settings */
#define MQTT_PUBLISH "I/Mobile/Mobile/porthable/Temperatura"	// Percorso di pubblicazione dei dati MQTT
#define MQTT_SUBSCRIBE "O/Mobile/Mobile/porthable/#"	// Percorso di lettura dei dati MQTT
#define ID "TEMPmobile"	// Identificatore
#define NTP_SERVER   "0.it.pool.ntp.org"	// Indirizzo del sever NTP
#define FTP_USERNAME "me"			// Username FTP
#define FTP_PASSWORD "123"			// Password FTP

// Mi serve per stamparla sulla pagina web
String Temperatura;
// Usata solo per la stampa RTC che ho disattivato
//Timer printTimer;

// Forward declarations
void startMqttClient();
void onMessageReceived(String topic, String message);
void onDataCallback(Stream& stream, char arrivedChar, unsigned short availableCharsCount);

// MQTT client
// For quickly check you can use: http://www.hivemq.com/demos/websocket-client/ (Connection= test.mosquitto.org:8080)
MqttClient mqtt(MQTT_HOST, 1883, onMessageReceived);

// Questa serve all'elenco delle reti WiFi
BssList networks;

HttpServer server;
FTPServer ftp;

/***	NTP	***/
void onNtpReceive(NtpClient& client, time_t timestamp);

// Option 1
// Use this option if you want to have full control of NtpTime client
// Default : no automatic NTP requests sent, no automatic update of SystemTime
// Default : NTP_DEFAULT_SERVER and NTP_DEFAULT_AUTO_UPDATE_INTERVAL from ntpclient.h
// NtpClient ntpClient(onNtpReceive);

// Option 2
// Use this option if you want control but other server/timeout options
// Default : use server as defined in call, no automatic update of SystemTime
// Default : automatic NTP request at myRequestInterval seconds
// Default : if myRequestInterval == 0 -> no automatic NTP request
NtpClient ntpClient (NTP_SERVER, 8 * 60 * 60, onNtpReceive);	// 8 ore, * 60 minuti, * 60 secondi

// Option 3
// Use this option if you want to start wit autorefresh and autosystemupdate
// No further callback from ntpClient
// NtpClient ntpClient("pool.ntp.org", 30);

// Option 4
// only create pointer and initialize on ConnectOK
// NtpClient *ntpClient;


// Callback example using defined class ntpClientDemo
//ntpClientDemo *demo;

// CallBack example 1 
// ntpClientDemo dm1 = ntpClientDemo();
// or use 
// ntpClientDemo dm1;
/*	NTP	*/


// Legge lo stream della seriale e lo mette sulla variabile "Message" come stringa
// Credo che questa funzione sia in un ".h/.cpp" del framework. Funziona ? La uso ;)
// Aggiungo l'invio del dato al broker mqtt.
void onDataCallback(Stream& stream, char arrivedChar, unsigned short availableCharsCount)
{
    String Message = "";  // Inizializzo stringa da inviare al broker mqtt
    if (arrivedChar == '\n')
    {
	//Serial.println("<New line received>");			// Ho dovuto eliminare tutti i messaggi alla seriale
	while (stream.available())
        {
            char cur = stream.read();
            //Serial.print(cur);
            Message += cur;   // Aggiunge caratteri (cur) alla stringa
        }

    Message.remove(Message.length()-2);   // Elimino dalla stringa i caratteri "\" e "n", perche` inviano un CR

    // Non sono sicuro che funzioni, e` da provare!

    if (mqtt.getConnectionState() != eTCS_Connected)
        startMqttClient(); // Auto reconnect

    // Promemoria
    //Serial.println("* PROMEMORIA *");
    //Serial.println("Sottoscrizione a: main/status/#");
    //Serial.println("Pubblicazione sul topic: porthable/adle/message");
    //Serial.println("-----------------------------------------------");

    //Serial.println("Let's publish message now!");
    //mqtt.publish(MQTT_PUBLISH, String(SystemClock.getSystemTimeString(eTZ_UTC)+","+Message)); // or publishWithQoS	// Prima di "level 1"
	mqtt.publish(MQTT_PUBLISH, "{ \"ID\" : \"" + String(ID) + "\", \"Valore\" : \"" + String(Message) + "\" }"); // or publishWithQoS
    //Serial.println(Temperatura);	// Usata per verifica temperatura
    Temperatura = Message;	// Copia stringa per stampa
    //Serial.println(Temperatura);	// Usata per verifica temperatura

    // Queste le metto per leggerle dall'ATMEGA ('data e ora' attuali)
    Serial.println("Date:");	// Mi serve un prefisso di riconoscimento
    Serial.println(SystemClock.getSystemTimeString(eTZ_UTC));
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

/*
void onPrintSystemTime() {
	Serial.print("Local Time    : ");
	Serial.println(SystemClock.getSystemTimeString());
	Serial.print("UTC Time: ");
	Serial.println(SystemClock.getSystemTimeString(eTZ_UTC));
}
*/

// Called when time has been received by NtpClient (option 1 or 2)
// Either after manual requestTime() or when
// and automatic request has been made.
void onNtpReceive(NtpClient& client, time_t timestamp) {
	SystemClock.setTime(timestamp);

	Serial.print("Time synchronized: ");
	Serial.println(SystemClock.getSystemTimeString());
}
/*	NTP	*/


/*	WEB/FTP Servers	*/
void onIndex(HttpRequest &request, HttpResponse &response)
{
	TemplateFileStream *tmpl = new TemplateFileStream("index.html");
	auto &vars = tmpl->variables();
	//vars["counter"] = String(counter);
	response.sendTemplate(tmpl); // this template object will be deleted automatically
}

void onFile(HttpRequest &request, HttpResponse &response)
{
	String file = request.getPath();
	if (file[0] == '/')
		file = file.substring(1);

	if (file[0] == '.')
		response.forbidden();
	else
	{
		response.setCache(86400, true); // It's important to use cache for better performance.
		response.sendFile(file);
	}
}


void onAjaxSerial(HttpRequest &request, HttpResponse &response)
{
	JsonObjectStream* stream = new JsonObjectStream();
	JsonObject& json = stream->getRoot();
	json["status"] = (bool)true;
	json["value"] = SystemClock.getSystemTimeString((eTZ_UTC));

	response.sendJsonObject(stream);
}

void onAjaxTemperature(HttpRequest &request, HttpResponse &response)
{
	//Serial.print("Temperatura: ");
	//Serial.println(Temperatura);

	JsonObjectStream* stream = new JsonObjectStream();
	JsonObject& json = stream->getRoot();
	json["status"] = (bool)true;
	json["value"] = String(Temperatura);

	response.sendJsonObject(stream);
}


void startWebServer()
{
	server.listen(80);
	server.addPath("/", onIndex);
	server.addPath("/ajax/serial", onAjaxSerial);
	server.addPath("/ajax/temperature", onAjaxTemperature);
	server.setDefaultHandler(onFile);

	Serial.println("\r\n=== WEB SERVER STARTED ===");
	Serial.println(WifiStation.getIP());
	Serial.println("==========================\r\n");
}

void startFTP()
{
	if (!fileExist("index.html"))
		fileSetContent("index.html", "<h3>Please connect to FTP and upload files from folder 'web/build' (details in code)</h3>");

	// Start FTP server
	ftp.listen(21);
	ftp.addUser(FTP_USERNAME, FTP_PASSWORD); // FTP account
}
/*	WEB/FTP Servers	*/

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

/*	NTP	*/
// Set specific parameters if started by option 1 or 2
	// Set client to do automatic time requests every 60 seconds.
	// NOTE: you should have longer interval in a real world application
	// no need for query for time every 60 sec, should be at least 10 minutes or so.
//	ntpClient.setAutoQueryInterval(60);
//	ntpClient.setAutoQuery(true);
//  ntpClient.setAutoUpdateSystemClock(true);
	// Request to update time now. 
	// Otherwise the set interval will pass before time
	// is updated.
//	ntpClient.requestTime();

//  When using option 4 -> create client after connect OK
//  ntpClient = new NtpClient("my_ntp_server", myrefreshinterval);

//	When using Delegate Callback Option 2
//	demo = new ntpClientDemo();
/*	NTP	*/


    Serial.println("Inizializzazione completata!");


    //startFTP();
    startWebServer();
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

	// If AP is enabled:
	debugf("AP. ip: %s mac: %s", WifiAccessPoint.getIP().toString().c_str(), WifiAccessPoint.getMAC().c_str());

	//connectOk();
}

void init()
{
	spiffs_mount(); // Mount file system, in order to work with files

	//Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.begin(9600); // Ok, a 9600 "si parlano", non ho provato altre velocita` !!!
	Serial.systemDebugOutput(false); // Debug output to serial

	// Set system ready callback method
	System.onReady(ready);

	// Station - WiFi client
	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiStation.enable(true);

	// Soft access point
	WifiAccessPoint.enable(false);
	//WifiAccessPoint.config("Sming InternetOfThings", "", AUTH_OPEN);

	// Optional: Change IP addresses (and disable DHCP)
	//WifiAccessPoint.setIP(IPAddress(192, 168, 5, 1));
	//WifiStation.setIP(IPAddress(192, 168, 6, 1));

	// Print available access points
	//WifiStation.startScan(listNetworks); // In Sming we can start network scan from init method without additional code

	// set timezone hourly difference to UTC
	SystemClock.setTimeZone(-1);

	//printTimer.initializeMs( 60 * 1000, onPrintSystemTime).start();	// [60 minuti *] 60 secondi * 1000 millisecondi


	// Run our method when station was connected to AP (or not connected)
	WifiStation.waitConnection(connectOk, 20, connectFail); // We recommend 20+ seconds for connection timeout at start
}
