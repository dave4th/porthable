ATTENZIONE
==========
Il progetto e` in corso, le informazioni contenute in questo repository sono inesatte ed incomplete.

# porthable
Portabile (?) "logger" di temperatura e umidita` con LCD e mdulo ESP8266

Un piccolo esperimento per realizzare un sensore di temperatura che sia movibile per rilevazioni temporanee, che memorizzi le variazioni in un grafico e trasmetta o permetta di leggere da remoto i valori.

Poi .. vedremo in cosa e se .. si evolvera`.

## Composizione
* ATMEGA328P (Arduino)
* Sonda di temperatura e umidita` DHT11
* TFT LCD 1,44"
* Modulo wifi ESP8266
* Modulo orologio DS1302

# Kicad

Il circuito e` aggiornato (se non ho dimenticato di fare upload ;) ), normalmente anche il ".pdf", per il resto, estrazione materiali, pcb .. eccetera, sono solo delle prove.

# w/ DS1302

Nei 'moduli' con orologio, per prima cosa si deve configurare l'ora, dopo aver collegato all'ATMEGA il DS1302 come da circuito elettrico, caricare sul microcontrollore il programma: "porthable_DS1302_SetSerial".

### Problema DS1302

Se si sostituisce l'atmega (per esempio quando se ne mette uno programmato differente) togliendo completamente alimentazione, lsciando comunque la batteria tampone, il DS1302 sembra vada in blocco e si deve riprogrammare.

Sembra sia sufficiente mantenere alimentazione (o meglio, mantenere il riferimento a 0V) aprendo solo l'interruttore di accensione, quando si sostituisce l'atmega.

## Programmazione con Raspberry Pi

Anzitutto ho creato il ".hex" semplicemente facendo un verifica dall'Arduino IDE 1.6.7, il file viene generato in una sottodirectory "/tmp".

Prima di caricare il programma, scollegate/togliete il Display (perche\` ha dei collegamenti in comune sulla SPI) e il modulo ESP8266 (perche\` e\` collegato sulla seriale), se li avete collegati.

Caricare lo sketch col comando (non serve avere un'ATMEGA col bootloader precaricato):
<pre>sudo avrdude -p m328p -P /dev/spidev0.0 -c linuxspi -b 10000 -U flash:w:git/porthable/arduino/porthable_DS1302_SetSerial.ino.hex</pre>

Con le "python-serial" (http://pyserial.readthedocs.org/en/latest/tools.html#module-serial.tools.miniterm) ho configurato l'ora:
<pre>miniterm.py --cr /dev/ttyAMA0 115200</pre>

Le istruzioni su come procedere all'impostazione dell'ora sono indicate nel ".ino" (che contiene il codice sorgente), comunque basta inserire la stringa "aaaa,mm,gg,HH,MM,SS" (Anno,Mese,Giorno,Hora,Minuti,Secondi).

Questa operazione dovra\` essere ripetuta quando si scarichera` la batteria tampone.

Ora potete procedere caricando sull'ATMEGA il programma vero e proprio ...


# porthable ADLD

Prima versione, composta da:
* ATMEGA328P
* DHT11
* LCD TFT 1,44"
* DS1302

Programmazione ATMEGA328P:
<pre><code>sudo avrdude -p m328p -P /dev/spidev0.0 -c linuxspi -b 10000 -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0x06:m</code></pre>
<pre><code>sudo avrdude -p m328p -P /dev/spidev0.0 -c linuxspi -b 10000 -U flash:w:porthable_adld.ino.hex</code></pre>

Il programma contiene ancora tutti i riferimenti alla configurazione completa, ma sono stati commentati i blocchi inutilizzati.

Lo schema elettrico comprende ancora tutta la circuiteria, e\` sufficiente non collegare quello che non c'e\` o che non si utilizza (vedi programma/sketch).

# porthable ADLE

Seconda versione, composta da:
* ATMEGA328P
* DHT11
* LCD TFT 1,44"
* ESP8266

Il programma e\` stato ampiamente rivisto, ma contiene ancora qualche riferimento alla configurazione completa, sono stati commentati i blocchi inutilizzati.

Lo schema elettrico comprende ancora tutta la circuiteria, e\` sufficiente non collegare quello che non c'e\` o che non si utilizza (vedi programma/sketch).

# porthable AWLD

Versione con sonda 'OneWire', composta da:
* ATMEGA328P
* DS18B20
* LCD TFT 1,44"
* DS1302

Solito, il programma e\` stato modificato mantenendo alcuni riferimenti alla configurazione da cui e\` stato originato (ADLE), sono stati commentati i blocchi inutilizzati.

Il collegamento della sonda 'OneWire' DS18B20 e\` identico al DHT11 (non ho ancora fatto o modificato uno schema elettrico)

Lo schema elettrico comprende ancora tutta la circuiteria, e\` sufficiente non collegare quello che non c'e\` o che non si utilizza (vedi programma/sketch).


# Update

## Aggiornamenti 2016 01 24

Ho eliminato la seriale software, troppi problemi, collegando l'ESP sulla seriale standard dell'ATMEGA.

Ho aggiunto un potenziometro per selezionare/modificare i tempi di refresh del grafico.

Ho modificato la visualizzazione sul display,
 aggiungendo i tempi grafico e qualche tacca di riferimento,
 forse ho esagerato ..

Il programma testato e\` solamente quello della versione ADLE,
 nell'altro mi sono limitato a copiare le parti, quindi e\` da provare.

Modificato circuito elettrico.

Elimino i ".hex" dal repository github (sapete come ricavarli dai sorgenti ;) )

## Aggiornamenti 2016 01 31

Rimesso ".hex" per comodita\`.

## Aggiornamenti 2016 02 03

Cambiato libreria sensore DHT11 (http://playground.arduino.cc/Main/DHT11Lib).

Modificato aggiornamento data-ora.

Aggiunte memorie di lettura per eliminare le troppe oscillazioni sui valori.

Per ora solo versione ADLE.


# Riferimenti

* http://www.rinkydinkelectronics.com/library.php?id=5
* https://github.com/PaulStoffregen/OneWire