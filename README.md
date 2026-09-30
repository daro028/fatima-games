# 🕹️ Juegos Fatima - Arcade Web & Microcontroladores

Una colección de rompecabezas clásicos modernos, responsivos y 100% autónomos, listos para jugar en navegadores de PC, tablets, smartphones, **GitHub Pages**, microcontroladores **ESP32-C3 / ESP32-S3** o una **Raspberry Pi 4**.

---

## 🎮 Juegos Incluidos

### 1. 💡 Lights Out ([`index.html`](index.html))
- Inspirado en el clásico de Tiger Electronics (1995) y [puzzle.now/lightsout](https://puzzle.now/lightsout/).
- **Objetivo**: Apagar todas las luces del tablero. Cada pulsación conmuta la celda y sus vecinas directas.
- **Niveles**:
  - **Línea 1x5** (5 botones contiguos).
  - **Matriz 3x3** (9 botones).
  - **Matriz 5x5** (25 botones clásico).
- **Pista Inteligente (💡 Pista)**: Resolvedor Gaussiano exacto sobre GF(2) que indica el movimiento óptimo en tiempo real.
- **100% Soluble**: Generación matemática sin acertijos imposibles.

### 2. 🌊 Flow Free ([`flow.html`](flow.html))
- Inspirado en Numberlink y [puzzle.now/flow](https://puzzle.now/flow/).
- **Objetivo**: Conectar los pares de puntos del mismo color mediante tuberías de neón continuas, sin que las líneas se crucen, y **cubriendo el 100% de las casillas** del tablero.
- **Modos de Cuadrícula**:
  - **5x5** (Fácil / Inicio)
  - **6x6** (Intermedio)
  - **7x7** (Avanzado)
  - **8x8** (Desafío Experto)
- **Controles Táctiles y de Ratón**: Arrastre ultrasuave, desandado automático al retroceder y corte automático al chocar.
- **Sonidos Pentatónicos**: Cada color reproduce su propia nota musical armónica al trazar y conectar.
- **Niveles prediseñados + Generador Aleatorio Infinito (🎲)**.

---

## 🏆 Tablas de Puntajes y Jugadores (JSON)

- Ambos juegos incluyen guardado de récords con nombre del jugador y tiempo en formato estándar **JSON**.
- Botón **📥 Exportar JSON** para descargar copias de seguridad de las partidas en cualquier momento.
- Panel de control unificado [**`admin.html`**](admin.html) protegido por PIN (clave por defecto: **`1234`**) para ver el JSON en tiempo real, descargar backups, restaurar o vaciar los puntajes con un solo clic.

---

## 🌐 Cómo Jugar en GitHub Pages (Online y Gratis)

1. En tu repositorio de GitHub ([github.com/daro028/lights-out](https://github.com/daro028/lights-out)):
2. Ve a **Settings** > **Pages**.
3. En **Branch**, selecciona `main` y la carpeta `/(root)`, luego haz clic en **Save**.
4. En 1 minuto tendrás acceso a:
   - **Lights Out**: `https://daro028.github.io/lights-out/`
   - **Flow**: `https://daro028.github.io/lights-out/flow.html`
   - **Admin**: `https://daro028.github.io/lights-out/admin.html`

---

## ⚡ Servidor en ESP32-C3 / ESP32-S3

1. Abre `esp32_lightsout.ino` en **Arduino IDE**.
2. Selecciona tu placa (ej. *ESP32C3 Dev Module* o *ESP32S3 Dev Module*).
3. Sube el código mediante USB.
4. El ESP32 creará la red Wi-Fi: **`Juegos-Fatima`**.
5. Conéctate con tu celular o PC y abre:
   - `http://192.168.4.1/` (Lights Out)
   - `http://192.168.4.1/flow.html` (Flow Free)
   - `http://192.168.4.1/admin.html` (Panel Admin)

---

## 🍓 Servidor en Raspberry Pi 4

### Comando rápido en Python:
```bash
python3 -m http.server 8080 --directory "Juegos Fatima"
```
Acceso en red local: `http://IP_DE_TU_RASPBERRY:8080`.

---

## 📁 Estructura del Proyecto

```
Juegos Fatima/
│
├── index.html            # Juego: Lights Out (con selector de juegos y ranking)
├── flow.html             # Juego: Flow Free (canvas neón, táctil, niveles 5x5 a 8x8)
├── admin.html            # Panel de Administración para ambos juegos (protegido por PIN)
├── esp32_lightsout.ino   # Firmware Arduino para ESP32-C3 / ESP32-S3 con LittleFS
├── index_html.h          # Header C++ con index.html embebido
├── flow_html.h           # Header C++ con flow.html embebido
├── admin_html.h          # Header C++ con admin.html embebido
├── .gitignore            # Exclusiones para Git
└── README.md             # Documentación del proyecto
```
