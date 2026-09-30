const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Fátima Games - Arcade de Rompecabezas</title>
  <style>
    :root {
      --bg-main: #070b14;
      --bg-card: rgba(18, 26, 44, 0.85);
      --border-card: rgba(255, 255, 255, 0.08);
      --accent: #00f2fe;
      --accent-glow: rgba(0, 242, 254, 0.4);
      --text: #f1f5f9;
      --text-muted: #94a3b8;
      --font-family: system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
    }

    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      user-select: none;
      -webkit-user-select: none;
    }

    body {
      background-color: var(--bg-main);
      background-image: 
        radial-gradient(circle at 20% 15%, rgba(0, 242, 254, 0.08) 0%, transparent 50%),
        radial-gradient(circle at 80% 85%, rgba(168, 85, 247, 0.08) 0%, transparent 55%),
        linear-gradient(180deg, #050811 0%, #0c1322 100%);
      color: var(--text);
      font-family: var(--font-family);
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      padding: 20px 14px;
    }

    .container {
      width: 100%;
      max-width: 680px;
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 22px;
    }

    /* HEADER */
    header {
      text-align: center;
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 6px;
    }

    .badge-portal {
      font-size: 0.75rem;
      font-weight: 700;
      text-transform: uppercase;
      letter-spacing: 1.5px;
      background: rgba(0, 242, 254, 0.12);
      color: var(--accent);
      padding: 4px 12px;
      border-radius: 20px;
      border: 1px solid rgba(0, 242, 254, 0.3);
      display: inline-block;
    }

    h1 {
      font-size: clamp(2rem, 6vw, 2.7rem);
      font-weight: 900;
      letter-spacing: 1px;
      background: linear-gradient(135deg, #ffffff 20%, #00f2fe 70%, #a855f7 100%);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
      text-shadow: 0 0 30px rgba(0, 242, 254, 0.3);
    }

    .subtitle {
      font-size: 0.92rem;
      color: var(--text-muted);
      max-width: 440px;
      line-height: 1.5;
    }

    /* GRID DE JUEGOS */
    .games-grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
      gap: 16px;
      width: 100%;
    }

    .game-card {
      background: var(--bg-card);
      border: 1px solid var(--border-card);
      border-radius: 20px;
      padding: 24px;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      gap: 16px;
      text-decoration: none;
      color: inherit;
      position: relative;
      overflow: hidden;
      transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
      box-shadow: 0 10px 25px rgba(0, 0, 0, 0.4);
    }

    .game-card::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      height: 4px;
      background: var(--card-color, var(--accent));
      opacity: 0.8;
      transition: height 0.2s ease;
    }

    .game-card:hover {
      transform: translateY(-4px);
      border-color: rgba(255, 255, 255, 0.2);
      box-shadow: 0 16px 36px rgba(0, 0, 0, 0.6), 0 0 25px var(--card-glow, rgba(0, 242, 254, 0.2));
    }

    .game-card:hover::before {
      height: 6px;
    }

    .card-top {
      display: flex;
      align-items: flex-start;
      gap: 14px;
    }

    .card-icon {
      font-size: 2.6rem;
      background: rgba(255, 255, 255, 0.04);
      padding: 12px;
      border-radius: 16px;
      border: 1px solid rgba(255, 255, 255, 0.08);
      display: flex;
      align-items: center;
      justify-content: center;
      line-height: 1;
    }

    .card-info h2 {
      font-size: 1.35rem;
      font-weight: 800;
      color: #fff;
      margin-bottom: 4px;
    }

    .card-info p {
      font-size: 0.84rem;
      color: var(--text-muted);
      line-height: 1.45;
    }

    .card-tags {
      display: flex;
      flex-wrap: wrap;
      gap: 6px;
      margin-top: 4px;
    }

    .tag {
      font-size: 0.7rem;
      font-weight: 600;
      padding: 3px 8px;
      border-radius: 6px;
      background: rgba(255, 255, 255, 0.05);
      color: #cbd5e1;
      border: 1px solid rgba(255, 255, 255, 0.06);
    }

    .play-btn {
      background: linear-gradient(135deg, var(--card-color) 0%, #1e293b 140%);
      color: #fff;
      padding: 12px 18px;
      border-radius: 12px;
      font-weight: 700;
      font-size: 0.9rem;
      display: flex;
      align-items: center;
      justify-content: space-between;
      border: 1px solid rgba(255, 255, 255, 0.12);
      transition: all 0.2s ease;
    }

    .game-card:hover .play-btn {
      filter: brightness(1.15);
      padding-right: 14px;
    }

    /* FOOTER & ACCIONES */
    .hub-footer {
      display: flex;
      flex-wrap: wrap;
      align-items: center;
      justify-content: center;
      gap: 12px;
      margin-top: 8px;
      font-size: 0.8rem;
      color: var(--text-muted);
    }

    .admin-link {
      color: var(--accent);
      text-decoration: none;
      border: 1px solid rgba(0, 242, 254, 0.3);
      padding: 6px 14px;
      border-radius: 8px;
      background: rgba(0, 242, 254, 0.06);
      transition: all 0.2s;
      font-weight: 600;
      display: inline-flex;
      align-items: center;
      gap: 6px;
    }

    .admin-link:hover {
      background: rgba(0, 242, 254, 0.18);
      color: #fff;
    }

    /* COLORES ESPECÍFICOS DE TARJETAS */
    .card-lightsout {
      --card-color: #ffd166;
      --card-glow: rgba(255, 209, 102, 0.25);
    }
    .card-lightsout .play-btn {
      background: linear-gradient(135deg, #ffd166 0%, #f39c12 100%);
      color: #080c14;
      border: none;
    }

    .card-flow {
      --card-color: #00f2fe;
      --card-glow: rgba(0, 242, 254, 0.25);
    }
    .card-flow .play-btn {
      background: linear-gradient(135deg, #00c6ff 0%, #0072ff 100%);
      color: #fff;
      border: none;
    }
  </style>
</head>
<body>
  <div class="container">
    <!-- Header -->
    <header>
      <span class="badge-portal">Portal de Juegos</span>
      <h1>Fátima Games</h1>
      <p class="subtitle">Elige un juego, pon a prueba tu ingenio y supera los mejores récords.</p>
    </header>

    <!-- Catálogo de Juegos -->
    <main class="games-grid">
      <!-- Tarjeta: Lights Out -->
      <a href="lights-out.html" class="game-card card-lightsout">
        <div class="card-top">
          <div class="card-icon">💡</div>
          <div class="card-info">
            <h2>Lights Out</h2>
            <p>El clásico rompecabezas electrónico: conmuta las casillas y apaga todas las luces del tablero.</p>
            <div class="card-tags">
              <span class="tag">1x5 Línea</span>
              <span class="tag">3x3 Matriz</span>
              <span class="tag">5x5 Clásico</span>
              <span class="tag">Pistas en vivo</span>
            </div>
          </div>
        </div>
        <div class="play-btn">
          <span>Jugar Lights Out</span>
          <span>➔</span>
        </div>
      </a>

      <!-- Tarjeta: Flow Free -->
      <a href="flow.html" class="game-card card-flow">
        <div class="card-top">
          <div class="card-icon">🌊</div>
          <div class="card-info">
            <h2>Flow Free</h2>
            <p>Conecta los puntos del mismo color trazando tuberías de neón sin cruzar líneas y cubre el 100%.</p>
            <div class="card-tags">
              <span class="tag">5x5 a 8x8</span>
              <span class="tag">100% Cobertura</span>
              <span class="tag">Modo Aleatorio</span>
              <span class="tag">Audio Armónico</span>
            </div>
          </div>
        </div>
        <div class="play-btn">
          <span>Jugar Flow Free</span>
          <span>➔</span>
        </div>
      </a>
    </main>

    <!-- Pie de página y Acceso Admin -->
    <footer class="hub-footer">
      <span>Compatible con ESP32-C3 / ESP32-S3 / Raspberry Pi</span>
      <span>·</span>
      <a href="admin.html" class="admin-link">⚙️ Panel Admin / Puntajes JSON</a>
    </footer>
  </div>
</body>
</html>

)rawliteral";