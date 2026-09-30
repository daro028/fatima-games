# 💡 Lights Out - Desafío de Luces

Una versión moderna, responsiva y 100% autónoma del clásico rompecabezas electrónico **Lights Out** (Tiger Electronics, 1995 / [puzzle.now/lightsout](https://puzzle.now/lightsout/)).

Diseñado para funcionar en navegadores web de PC, tablets y smartphones, y optimizado específicamente para ser servido directamente desde microcontroladores **ESP32-C3**, **ESP32-S3**, **GitHub Pages** o una **Raspberry Pi 4**.

---

## 🎮 Niveles y Modos Disponibles

1. **Línea 1x5 (5 botones)**: 
   - 1 fila de 5 luces contiguas.
   - Ideal para partidas rápidas, niños o para entender la mecánica de conmutación.
   - Al pulsar un botón, conmuta su estado y el de sus vecinas inmediatas (izquierda y derecha).
2. **Matriz 3x3 (9 botones)**: 
   - 3 filas por 3 columnas.
   - Dificultad intermedia clásica. Conmuta la celda y sus 4 vecinas ortogonales (arriba, abajo, izquierda, derecha).
3. **Matriz 5x5 (25 botones)**: 
   - El tamaño clásico original del juego.
   - Desafío completo con miles de combinaciones posibles.

---

## 🏆 Tabla de Puntajes y Jugadores (JSON)

- **Registro de Nombre**: Al ganar cualquier nivel, el jugador puede ingresar su nombre para guardar su récord.
- **Formato Estándar JSON**: Cada partida se guarda como un objeto estructurado:
  ```json
  {
    "id": "score_1727654321000",
    "player": "Fátima",
    "mode": "3x3",
    "moves": 9,
    "time": 24,
    "date": "29/09/2026, 23:30"
  }
  ```
- **Exportación e Importación**:
  - Puedes descargar un archivo `.json` de backup en cualquier momento pulsando **📥 Exportar JSON**.
  - Puedes restaurar puntajes previos en el panel de administración.
- **Seguridad y Vaciado de Lista**:
  - Se puede vaciar la lista desde el botón **🔒 Vaciar Lista** en el juego (solicita la clave de administrador).
  - O bien desde el archivo dedicado [**`admin.html`**](admin.html).
  - **Clave de Administrador por Defecto**: `1234` (se puede cambiar desde `admin.html`).

---

## ✨ Características Técnicas

- **100% Soluble Garantizado**: Generación a partir del estado apagado aplicando secuencias de movimientos aleatorios válidos. ¡Nunca un nivel imposible!
- **Botón de Pista Inteligente (💡 Pista)**: Resolvedor Gaussiano exacto sobre el cuerpo finito $\mathbb{F}_2$ (GF(2)) que calcula en menos de 1 milisegundo el siguiente movimiento óptimo.
- **Sonidos Sintetizados (Web Audio API)**: Tonos y fanfarria al ganar generados por código mediante osciladores, **sin archivos de audio externos**.
- **Cero Dependencias**: No requiere internet, CDNs ni librerías pesadas. Ocupa solo ~35 KB.

---

## 🌐 Cómo Subirlo a GitHub y Activar GitHub Pages

¡Sí! Este proyecto está 100% listo para subirse a GitHub y jugarse online gratis.

### Pasos:

1. **Crear repositorio en GitHub**:
   - Entra a [github.com/new](https://github.com/new) y crea un nuevo repositorio (ej: `lights-out-juego`).
2. **Subir los archivos desde tu computadora**:
   Abre una terminal (PowerShell o Git Bash) en esta carpeta y ejecuta:
   ```bash
   git init
   git add .
   git commit -m "Versión inicial de Lights Out con niveles, ranking JSON y soporte ESP32"
   git branch -M main
   git remote add origin https://github.com/TU_USUARIO/TU_REPOSITORIO.git
   git push -u origin main
   ```
3. **Activar GitHub Pages (Web gratuita online)**:
   - En tu repositorio de GitHub, ve a **Settings** > **Pages** (en el menú lateral izquierdo).
   - En **Build and deployment > Source**, selecciona **Deploy from a branch**.
   - En **Branch**, elige `main` y la carpeta `/(root)`.
   - Haz clic en **Save**.
4. ¡Listo! En 1 minuto tendrás tu enlace público tipo:
   `https://TU_USUARIO.github.io/TU_REPOSITORIO/` para compartir y jugar desde cualquier parte del mundo.

---

## ⚡ Servidor en ESP32-C3 / ESP32-S3

Tanto el ESP32-C3 como el ESP32-S3 incluyen Wi-Fi y memoria Flash suficiente para alojar el juego y guardar el archivo `scores.json` en **LittleFS**, permitiendo que varios jugadores conectados a la red del ESP32 compartan la misma tabla de posiciones.

### Pasos en Arduino IDE:
1. Abre `esp32_lightsout.ino`.
2. En **Herramientas > Placa**, selecciona tu modelo (ej. `ESP32C3 Dev Module` o `ESP32S3 Dev Module`).
3. Conecta por USB y haz clic en **Subir**.
4. El ESP32 creará la red Wi-Fi `LightsOut-Game`.
5. Conéctate con tu celular o PC y abre:
   - **Juego**: `http://192.168.4.1/` o `http://lightsout.local/`
   - **Panel Admin**: `http://192.168.4.1/admin.html`

---

## 🍓 Servidor en Raspberry Pi 4

### Opción Rápida con Python (1 línea):
```bash
python3 -m http.server 8080 --directory "Juegos Fatima"
```
Acceso desde la red local: `http://IP_DE_TU_RASPBERRY:8080`.

### Opción Permanente con Nginx:
```bash
sudo apt update && sudo apt install -y nginx
sudo cp index.html admin.html /var/www/html/
```
Acceso directo: `http://IP_DE_TU_RASPBERRY/`.

---

## 📁 Estructura de Archivos

```
Juegos Fatima/
│
├── index.html            # Juego principal + Tabla de puntajes + Exportador JSON
├── admin.html            # Panel de control de administrador protegido por PIN
├── esp32_lightsout.ino   # Firmware Arduino para ESP32-C3 / ESP32-S3 (LittleFS + WebServer)
├── index_html.h          # Header C++ con index.html embebido en Flash
├── admin_html.h          # Header C++ con admin.html embebido en Flash
├── .gitignore            # Archivos temporales ignorados para Git
└── README.md             # Documentación completa
```
