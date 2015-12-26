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

# porthable ADLD

Prima versione, composta da:
* ATMEGA328
* DHT11
* LCD TFT 1,44"
* DS1302

Programmazione ATMEGA:
<pre><code>sudo avrdude -p m328p -P /dev/spidev0.0 -c linuxspi -b 10000 -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0x06:m</code></pre>
<pre><code>sudo avrdude -p m328p -P /dev/spidev0.0 -c linuxspi -b 10000 -U flash:w:porthable_adld.ino.hex</code></pre>

Il programma contiene ancora tutti i riferimenti alla configurazione completa, ma sono stati commentati i blocchi inutilizzati.

Il programma e` stato aggiornato/modificato perche` memorizzi la temperatura ogni mezz'ora, ai minuti 00 e 30.

Lo schema elettrico comprende ancora tutta la circuiteria, e` sufficiente non collegare quello che non c'e` o che non si utilizza (previa sistemazione del programma, ovviamente).

