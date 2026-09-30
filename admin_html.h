const char ADMIN_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Lights Out - Panel de Administración</title>
  <style>
    :root {
      --bg-main: #0a0e17;
      --bg-card: #131c2e;
      --border: rgba(255, 255, 255, 0.1);
      --accent: #00f2fe;
      --danger: #ef4444;
      --danger-hover: #dc2626;
      --success: #06d6a0;
      --text: #f1f5f9;
      --text-muted: #94a3b8;
      --font-family: system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
    }

    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      font-family: var(--font-family);
    }

    body {
      background: var(--bg-main);
      color: var(--text);
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 24px 16px;
    }

    .container {
      width: 100%;
      max-width: 680px;
      display: flex;
      flex-direction: column;
      gap: 20px;
    }

    header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      border-bottom: 1px solid var(--border);
      padding-bottom: 16px;
    }

    h1 {
      font-size: 1.5rem;
      color: var(--accent);
      display: flex;
      align-items: center;
      gap: 8px;
    }

    .back-btn {
      color: var(--text-muted);
      text-decoration: none;
      font-size: 0.85rem;
      border: 1px solid var(--border);
      padding: 8px 12px;
      border-radius: 8px;
      transition: all 0.2s;
    }

    .back-btn:hover {
      color: #fff;
      border-color: var(--accent);
    }

    .card {
      background: var(--bg-card);
      border: 1px solid var(--border);
      border-radius: 14px;
      padding: 20px;
      box-shadow: 0 10px 25px rgba(0, 0, 0, 0.4);
    }

    .card-title {
      font-size: 1.1rem;
      margin-bottom: 12px;
      display: flex;
      align-items: center;
      gap: 8px;
    }

    .auth-section {
      display: flex;
      flex-direction: column;
      gap: 12px;
      align-items: center;
      padding: 30px 10px;
      text-align: center;
    }

    input[type="password"], input[type="text"] {
      background: #0f172a;
      border: 1px solid var(--border);
      color: #fff;
      padding: 10px 16px;
      border-radius: 8px;
      font-size: 1rem;
      width: 100%;
      max-width: 300px;
      outline: none;
      text-align: center;
    }

    input:focus {
      border-color: var(--accent);
      box-shadow: 0 0 10px rgba(0, 242, 254, 0.2);
    }

    .btn {
      padding: 10px 18px;
      border-radius: 8px;
      border: none;
      font-weight: 600;
      font-size: 0.9rem;
      cursor: pointer;
      display: inline-flex;
      align-items: center;
      gap: 6px;
      transition: all 0.2s;
    }

    .btn-primary {
      background: var(--accent);
      color: #070a12;
    }

    .btn-primary:hover {
      filter: brightness(1.1);
    }

    .btn-danger {
      background: var(--danger);
      color: #fff;
    }

    .btn-danger:hover {
      background: var(--danger-hover);
    }

    .btn-secondary {
      background: #1e293b;
      color: #fff;
      border: 1px solid var(--border);
    }

    .btn-secondary:hover {
      background: #334155;
    }

    .stats-summary {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(140px, 1fr));
      gap: 12px;
      margin-bottom: 16px;
    }

    .stat-box {
      background: #0d1424;
      padding: 12px;
      border-radius: 8px;
      text-align: center;
      border: 1px solid rgba(255, 255, 255, 0.05);
    }

    .stat-val {
      font-size: 1.4rem;
      font-weight: 700;
      color: var(--accent);
    }

    .stat-lbl {
      font-size: 0.72rem;
      color: var(--text-muted);
      text-transform: uppercase;
      margin-top: 2px;
    }

    .actions-grid {
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      margin-top: 14px;
    }

    pre {
      background: #090d16;
      padding: 12px;
      border-radius: 8px;
      font-family: monospace;
      font-size: 0.8rem;
      max-height: 220px;
      overflow-y: auto;
      color: #7dd3fc;
      border: 1px solid rgba(255, 255, 255, 0.05);
    }

    .hidden {
      display: none !important;
    }

    .toast {
      position: fixed;
      bottom: 24px;
      background: #1e293b;
      color: #fff;
      padding: 12px 20px;
      border-radius: 20px;
      border: 1px solid var(--accent);
      font-size: 0.85rem;
      opacity: 0;
      transform: translateY(20px);
      transition: all 0.3s;
      pointer-events: none;
    }

    .toast.show {
      opacity: 1;
      transform: translateY(0);
    }
  </style>
</head>
<body>
  <div class="container">
    <header>
      <h1>⚙️ Panel de Administración</h1>
      <a href="index.html" class="back-btn">⬅ Volver al Juego</a>
    </header>

    <!-- PANTALLA DE ACCESO CON CLAVE -->
    <div class="card auth-section" id="auth-panel">
      <div style="font-size: 2.5rem;">🔒</div>
      <h2>Acceso Protegido</h2>
      <p style="color: var(--text-muted); font-size: 0.85rem;">
        Ingresa la clave de administrador para gestionar la tabla de puntajes.<br>
        (Clave por defecto: <strong>1234</strong>)
      </p>
      <input type="password" id="admin-pass" placeholder="Ingresa la clave" autofocus>
      <button class="btn btn-primary" onclick="verifyPassword()">Ingresar al Panel</button>
    </div>

    <!-- PANEL PRINCIPAL (Visible tras ingresar clave) -->
    <div id="main-panel" class="hidden" style="display: flex; flex-direction: column; gap: 20px;">
      
      <!-- Resumen -->
      <div class="card">
        <h2 class="card-title">📊 Resumen de Puntajes</h2>
        <div class="stats-summary">
          <div class="stat-box">
            <div class="stat-val" id="total-scores">0</div>
            <div class="stat-lbl">Partidas Registradas</div>
          </div>
          <div class="stat-box">
            <div class="stat-val" id="scores-1x5">0</div>
            <div class="stat-lbl">Nivel 1x5</div>
          </div>
          <div class="stat-box">
            <div class="stat-val" id="scores-3x3">0</div>
            <div class="stat-lbl">Nivel 3x3</div>
          </div>
          <div class="stat-box">
            <div class="stat-val" id="scores-5x5">0</div>
            <div class="stat-lbl">Nivel 5x5</div>
          </div>
        </div>

        <div class="actions-grid">
          <button class="btn btn-danger" onclick="clearAllScores()">
            🗑️ Vaciar Lista Completa
          </button>
          <button class="btn btn-secondary" onclick="downloadJSON()">
            📥 Descargar Backup JSON
          </button>
          <label class="btn btn-secondary" style="cursor: pointer;">
            📤 Restaurar desde JSON
            <input type="file" id="file-input" accept=".json" style="display: none;" onchange="importJSON(event)">
          </label>
        </div>
      </div>

      <!-- Visor de JSON -->
      <div class="card">
        <h2 class="card-title">📄 Archivo JSON en Memoria</h2>
        <pre id="json-viewer">[]</pre>
      </div>

      <!-- Configuración de Clave -->
      <div class="card">
        <h2 class="card-title">🔑 Cambiar Clave de Administrador</h2>
        <div style="display: flex; gap: 8px; max-width: 400px;">
          <input type="password" id="new-pass" placeholder="Nueva clave" style="text-align: left;">
          <button class="btn btn-secondary" onclick="changeAdminPassword()">Actualizar</button>
        </div>
      </div>

    </div>
  </div>

  <div id="toast" class="toast"></div>

  <script>
    const STORAGE_KEY = 'lightsout_scores_json';
    const PIN_KEY = 'lightsout_admin_pin';
    const DEFAULT_PIN = '1234';

    function getAdminPin() {
      return localStorage.getItem(PIN_KEY) || DEFAULT_PIN;
    }

    function verifyPassword() {
      const entered = document.getElementById('admin-pass').value;
      if (entered === getAdminPin()) {
        document.getElementById('auth-panel').classList.add('hidden');
        document.getElementById('main-panel').classList.remove('hidden');
        loadData();
        showToast("Acceso concedido");
      } else {
        showToast("Clave incorrecta");
      }
    }

    // Permitir presionar Enter en el input de clave
    document.getElementById('admin-pass').addEventListener('keypress', (e) => {
      if (e.key === 'Enter') verifyPassword();
    });

    function loadData() {
      let scores = [];
      try {
        const raw = localStorage.getItem(STORAGE_KEY);
        scores = raw ? JSON.parse(raw) : [];
      } catch (e) {
        scores = [];
      }

      // Actualizar contadores
      document.getElementById('total-scores').textContent = scores.length;
      document.getElementById('scores-1x5').textContent = scores.filter(s => s.mode === '1x5').length;
      document.getElementById('scores-3x3').textContent = scores.filter(s => s.mode === '3x3').length;
      document.getElementById('scores-5x5').textContent = scores.filter(s => s.mode === '5x5').length;

      // Actualizar visor JSON
      document.getElementById('json-viewer').textContent = JSON.stringify(scores, null, 2);
    }

    function clearAllScores() {
      if (confirm("⚠️ ¿Confirmas que deseas vaciar TODOS los puntajes guardados? Esta acción no se puede deshacer.")) {
        localStorage.removeItem(STORAGE_KEY);
        ['1x5', '3x3', '5x5'].forEach(m => localStorage.removeItem(`lightsout_best_${m}`));
        
        // Notificar al backend si existe (ESP32 / servidor)
        if (window.location.protocol.startsWith('http')) {
          fetch('/api/scores/clear?key=' + encodeURIComponent(getAdminPin()), { method: 'POST' }).catch(() => {});
        }

        loadData();
        showToast("¡Puntajes eliminados exitosamente!");
      }
    }

    function downloadJSON() {
      const raw = localStorage.getItem(STORAGE_KEY) || '[]';
      const blob = new Blob([raw], { type: 'application/json' });
      const url = URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = `lightsout_scores_${new Date().toISOString().slice(0, 10)}.json`;
      a.click();
      URL.revokeObjectURL(url);
      showToast("Descarga iniciada");
    }

    function importJSON(e) {
      const file = e.target.files[0];
      if (!file) return;

      const reader = new FileReader();
      reader.onload = (event) => {
        try {
          const parsed = JSON.parse(event.target.result);
          if (Array.isArray(parsed)) {
            localStorage.setItem(STORAGE_KEY, JSON.stringify(parsed));
            loadData();
            showToast("Puntajes restaurados correctamente");
          } else {
            alert("El archivo JSON debe contener un arreglo de puntajes válido.");
          }
        } catch (err) {
          alert("Error al leer el archivo JSON: formato inválido.");
        }
      };
      reader.readAsText(file);
    }

    function changeAdminPassword() {
      const newPass = document.getElementById('new-pass').value.trim();
      if (newPass.length < 3) {
        alert("La clave debe tener al menos 3 caracteres.");
        return;
      }
      localStorage.setItem(PIN_KEY, newPass);
      document.getElementById('new-pass').value = '';
      showToast("Clave actualizada correctamente");
    }

    function showToast(msg) {
      const t = document.getElementById('toast');
      t.textContent = msg;
      t.classList.add('show');
      setTimeout(() => t.classList.remove('show'), 2500);
    }
  </script>
</body>
</html>

)rawliteral";