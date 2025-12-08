# Ring Controller ESPHome

Un componente custom per ESPHome che permette di controllare strisce LED NeoPixel (WS2812B) con effetti luminosi predefiniti.

## 🌟 Caratteristiche

- **9 effetti luminosi** predefiniti, incluso l'effetto fiamma realistico
- **Controllo completo** da Home Assistant
- **Regolazione velocità** e intensità degli effetti
- **Facile configurazione** tramite YAML
- **Ottimizzato** per ESP8266 (testato su ESP-01 1M)

## 📋 Effetti Disponibili

1. **Flame** 🔥 - Simulazione realistica di fiamme tremolanti
2. **Rainbow** - Arcobaleno animato
3. **Theater** - Effetto teatro con LED alternati
4. **Breathing** - Respirazione dolce
5. **Wipe** - Riempimento progressivo
6. **Sparkle** - Scintillio casuale
7. **ColorCycle** - Ciclo di colori
8. **Static** - Colore statico rosso
9. **Off** - Spento

## 🔧 Installazione

### Requisiti Hardware

- ESP8266 o ESP32
- Striscia LED NeoPixel (WS2812B, WS2811, ecc.)
- Alimentazione adeguata per i LED

### Configurazione ESPHome

Aggiungi questa configurazione al tuo file YAML:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/SamueleFurnari/RingControllerESPHome.git
      ref: main
    refresh: 1min
    components: [ring_controller]

light:
  - platform: ring_controller
    output_id: ring_output
    id: ring_light
    name: "Ring Controller"
    pin: GPIO2           # Pin di controllo LED
    num_leds: 16         # Numero di LED nella striscia

select:
  - platform: ring_controller
    ring_controller_id: ring_output
    name: "Effetto Anello"

number:
  - platform: ring_controller
    ring_controller_id: ring_output
    parameter: speed
    name: "Velocità Effetto"
    
  - platform: ring_controller
    ring_controller_id: ring_output
    parameter: intensity
    name: "Intensità Effetto"
```

## ⚙️ Parametri di Configurazione

### Light Component

| Parametro | Tipo | Default | Descrizione |
|-----------|------|---------|-------------|
| `output_id` | ID | Richiesto | ID univoco del controller |
| `id` | ID | Richiesto | ID del componente light |
| `name` | string | Richiesto | Nome visualizzato in Home Assistant |
| `pin` | GPIO | 2 | Pin GPIO connesso ai LED |
| `num_leds` | int | 16 | Numero di LED nella striscia (1-1000) |

### Select Component

| Parametro | Tipo | Default | Descrizione |
|-----------|------|---------|-------------|
| `ring_controller_id` | ID | Richiesto | Riferimento all'output_id del light |
| `name` | string | Richiesto | Nome del selettore effetti |

### Number Component

| Parametro | Tipo | Default | Descrizione |
|-----------|------|---------|-------------|
| `ring_controller_id` | ID | Richiesto | Riferimento all'output_id del light |
| `parameter` | enum | Richiesto | `speed` o `intensity` |
| `name` | string | Richiesto | Nome del controllo numerico |

**Ranges:**
- **Speed**: 1-100 (default: 50)
- **Intensity**: 0-255 (default: 150)

## 📱 Utilizzo in Home Assistant

Dopo aver installato il componente, avrai accesso a:

### Entità Light
- **Accendi/Spegni** il ring LED
- **Controllo RGB** (nota: attualmente non utilizzato dagli effetti)
- **Luminosità** (nota: attualmente non utilizzato dagli effetti)

### Entità Select
- **Selezione effetto** - Scegli tra i 9 effetti disponibili (Flame, Rainbow, Theater, Breathing, Wipe, Sparkle, ColorCycle, Static, Off)

### Entità Number
- **Velocità** - Controlla la velocità dell'animazione (1-100)
- **Intensità** - Controlla l'intensità dell'effetto (0-255)

## 🔌 Schema di Collegamento

### ESP8266 (ESP-01)

```
ESP-01          NeoPixel Strip
GPIO2    -->    Data In (DIN)
GND      -->    GND
         -->    +5V (alimentazione esterna)
```

⚠️ **Importante**: 
- Usa un'alimentazione separata per i LED
- Aggiungi un condensatore da 1000µF tra +5V e GND
- Aggiungi una resistenza da 470Ω sul pin dati

## 🛠️ Sviluppo

### Struttura del Progetto

```
components/ring_controller/
├── __init__.py                 # Configurazione base
├── light/
│   ├── __init__.py            # Configurazione light platform
│   ├── ring_controller_light.h # Implementazione controller
│   ├── effects.h              # Definizione effetti
│   └── effects.cpp            # Implementazione effetti
├── select/
│   ├── __init__.py            # Configurazione select platform
│   └── ring_controller_select.h # Implementazione select
└── number/
    ├── __init__.py            # Configurazione number platform
    └── ring_controller_number.h # Implementazione number
```

### Dipendenze

- **Adafruit NeoPixel** v1.10.6 (inclusa automaticamente)

## 🐛 Risoluzione Problemi

### I LED non si accendono
- Verifica il pin GPIO configurato
- Controlla l'alimentazione dei LED
- Verifica il tipo di LED (NEO_GRB + NEO_KHZ800)

### Effetto non cambia
- Verifica che il select sia correttamente collegato al `ring_controller_id`
- Controlla i log ESPHome per errori

### Compilazione fallita
- Assicurati di usare ESPHome 2024.11.0 o superiore
- Verifica che il componente sia scaricato correttamente
- Usa `refresh: 1min` nella configurazione external_components

## 📝 Esempio Completo

```yaml
esphome:
  name: ring-controller
  friendly_name: Ring Controller

esp8266:
  board: esp01_1m

logger:

api:
  encryption:
    key: "tua_chiave_api"

ota:
  - platform: esphome
    password: "tua_password"

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  ap:
    ssid: "Ring-Controller Fallback"
    password: "password_fallback"

captive_portal:

external_components:
  - source:
      type: git
      url: https://github.com/SamueleFurnari/RingControllerESPHome.git
      ref: main
    refresh: 1min
    components: [ring_controller]

light:
  - platform: ring_controller
    output_id: ring_output
    id: ring_light
    name: "Ring Controller"
    pin: GPIO2
    num_leds: 16

select:
  - platform: ring_controller
    ring_controller_id: ring_output
    name: "Effetto Anello"

number:
  - platform: ring_controller
    ring_controller_id: ring_output
    parameter: speed
    name: "Velocità Effetto"
    
  - platform: ring_controller
    ring_controller_id: ring_output
    parameter: intensity
    name: "Intensità Effetto"
```

## 🤝 Contribuire

I contributi sono benvenuti! Sentiti libero di:
- Aprire issue per bug o richieste di funzionalità
- Inviare pull request
- Suggerire nuovi effetti luminosi

## 📄 Licenza

Questo progetto è distribuito sotto licenza MIT.

## 👤 Autore

**Samuele Furnari**
- GitHub: [@SamueleFurnari](https://github.com/SamueleFurnari)

## 🙏 Ringraziamenti

- [ESPHome](https://esphome.io/) per il framework fantastico
- [Adafruit](https://github.com/adafruit/Adafruit_NeoPixel) per la libreria NeoPixel
- La community di Home Assistant

---

⭐ Se questo progetto ti è stato utile, considera di mettere una stella su GitHub!