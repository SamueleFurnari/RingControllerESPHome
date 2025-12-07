NeoPixel Ring ESPHome Component

Componente ESPHome per controllare un anello NeoPixel (ESP01 / ESP8266) con effetti animati, integrato direttamente in Home Assistant tramite API.

Caratteristiche

Light RGB + dimmer (colore e luminosità)

Effetti animati: Rainbow, Theater, Breathing, Wipe, Sparkle, ColorCycle, Static, Off

Selezione effetti tramite select in Home Assistant

Controllo velocità e intensità tramite number in Home Assistant

Nessun MQTT necessario, usa solo ESPHome API

Pin e numero di LED fissi come nel firmware originale

Autodiscovery nativa in Home Assistant

Struttura cartelle
neopixel_ring_esphome/
├── components/
│   └── neopixel_ring/
│       ├── component.yaml
│       ├── neopixel_ring.h
│       ├── neopixel_ring.cpp
│       ├── effects.h
│       └── effects.cpp
├── README.md
└── example.yaml

Installazione e uso

Copia la struttura dei file sul tuo PC.

Modifica example.yaml con i tuoi parametri Wi‑Fi:

wifi:
  ssid: "TUO_WIFI"
  password: "TUA_PASSWORD"


Compila e flasha il firmware con ESPHome:

esphome run example.yaml


Dopo l’avvio, Home Assistant rileverà automaticamente il dispositivo come NeoPixel Ring.

Puoi controllare da HA:

Colore e luminosità della light

Effetto (dal menu a tendina select)

Velocità e intensità degli effetti

Accensione / spegnimento

Personalizzazione

Effetti: puoi aggiungere o modificare gli effetti nei file effects.h e effects.cpp.

Pin e LED: fissati in neopixel_ring.h, non modificabili da Home Assistant.

Compatibilità

ESP01 / ESP8266 con almeno 1MB flash

Home Assistant con integrazione ESPHome

Se vuoi, posso anche generarti una versione Markdown più “carina” con immagini e tabelle per descrivere tutti gli effetti e i comandi disponibili, pronta per GitHub. Vuoi che lo faccia?

You said:
si
ChatGPT said:

Perfetto! Ecco una versione più “grafica” del README pronta per GitHub, con immagini di esempio, tabelle e descrizione chiara degli effetti e controlli.

NeoPixel Ring ESPHome Component

Componente ESPHome per controllare un anello NeoPixel (ESP01 / ESP8266) con effetti animati, integrato direttamente in Home Assistant tramite API.

🌟 Caratteristiche
Funzionalità	Descrizione
Light RGB + dimmer	Colore e luminosità controllabili da Home Assistant
Effetti animati	Rainbow, Theater, Breathing, Wipe, Sparkle, ColorCycle, Static, Off
Controllo effetti	Selezionabili tramite select in Home Assistant
Controllo velocità/intensità	Regolabili tramite number in Home Assistant
Pin & LED	Fissi in firmware (non modificabili via HA)
Autodiscovery	Rilevamento automatico in Home Assistant
Comunicazione	Solo ESPHome API, nessun MQTT
📂 Struttura cartelle
neopixel_ring_esphome/
├── components/
│   └── neopixel_ring/
│       ├── component.yaml
│       ├── neopixel_ring.h
│       ├── neopixel_ring.cpp
│       ├── effects.h
│       └── effects.cpp
├── README.md
└── example.yaml

⚡ Installazione e uso

Copia la struttura dei file sul tuo PC.

Modifica example.yaml con i tuoi parametri Wi‑Fi:

wifi:
  ssid: "TUO_WIFI"
  password: "TUA_PASSWORD"


Compila e flasha il firmware con ESPHome:

esphome run example.yaml


Home Assistant rileverà automaticamente il dispositivo come NeoPixel Ring.

🛠 Controlli disponibili in Home Assistant
Tipo	Nome ID	Descrizione
Light	ring	Colore e luminosità LED
Select	neopixel_effect	Effetto attivo (Rainbow, Theater…)
Number	neopixel_speed	Velocità effetto
Number	neopixel_intensity	Intensità effetto
🎨 Effetti disponibili
Effetto	Descrizione
Rainbow	Ciclo arcobaleno continuo
Theater	Scie alternate tipo “teatro”
Breathing	Dissolvenza in entrata e uscita della luce
Wipe	Accensione progressiva dei LED
Sparkle	LED casuali lampeggianti
ColorCycle	Ciclo di colori uniforme
Static	Colore fisso (rosso di default)
Off	Spegne tutti i LED
⚙ Personalizzazione

Effetti: puoi aggiungere o modificare gli effetti nei file effects.h e effects.cpp.

Pin e numero di LED: fissati in neopixel_ring.h, non modificabili da Home Assistant.

🧩 Compatibilità

ESP01 / ESP8266 con almeno 1MB flash

Home Assistant con integrazione ESPHome