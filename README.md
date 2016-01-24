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


# w/ DS1302

Nei 'moduli' con orologio, per prima cosa si deve configurare l'ora, dopo aver collegato all'ATMEGA il DS1302 come da circuito elettrico, caricare sul microcontrollore il programma: "porthable_DS1302_SetSerial".

Le istruzioni su come procedere all'impostazione dell'ora sono indicate nel ".ino" (che contiene il codice sorgente).

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

Lo schema elettrico comprende ancora tutta la circuiteria, e\` sufficiente non collegare quello che non c'e\` o che non si utilizza (previa sistemazione del programma, ovviamente).

# porthable ADLE

Seconda versione, composta da:
* ATMEGA328P
* DHT11
* LCD TFT 1,44"
* ESP8266

Il programma e` stato ampiamente rivisto, ma contiene ancora qualche riferimento alla configurazione completa, sono stati commentati i blocchi inutilizzati.

Lo schema elettrico comprende ancora tutta la circuiteria, e\` sufficiente non collegare quello che non c'e\` o che non si utilizza (previa sistemazione del programma, ovviamente).

# Aggiornamenti 2016 01 24

Ho eliminato la seriale software, troppi problemi, collegando l'ESP sulla seriale standard dell'ATMEGA.

Ho aggiunto un potenziometro per selezionare/modificare i tempi di refresh del grafico.

Ho modificato la visualizzazione sul display,
 aggiungendo i tempi grafico e qualche tacca di riferimento,
 forse ho esagerato ..

Il programma testato e\` solamente quello della versione ADLE,
 nell'altro mi sono limitato a copiare le parti, quindi e\` da provare.

Modificato circuito elettrico.

Elimino i ".hex" dal repository github (sapete come ricavarli dai sorgenti ;) )
