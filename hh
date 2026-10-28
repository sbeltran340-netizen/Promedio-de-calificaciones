<!DOCTYPE html>
<html lang="es" class="h-full">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Promedio Fácil | Calculadora de Notas & Exportador</title>

  <!-- Tailwind CSS CDN -->
  <script src="https://cdn.tailwindcss.com"></script>
  
  <!-- JSZip para generar el archivo ZIP descomprimible -->
  <script src="https://cdnjs.cloudflare.com/ajax/libs/jszip/3.10.1/jszip.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/FileSaver.js/2.0.5/FileSaver.min.js"></script>

  <!-- Lucide Icons -->
  <script src="https://unpkg.com/lucide@latest"></script>

  <!-- Google Fonts (Inter + Outfit) -->
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&family=Outfit:wght@500;600;700;800&display=swap" rel="stylesheet">

  <script>
    tailwind.config = {
      darkMode: 'class',
      theme: {
        extend: {
          fontFamily: {
            sans: ['Inter', 'sans-serif'],
            display: ['Outfit', 'sans-serif'],
          },
          colors: {
            brand: {
              50: '#eef2ff',
              100: '#e0e7ff',
              500: '#6366f1',
              600: '#4f46e5',
              700: '#4338ca',
            }
          }
        }
      }
    }
  </script>

  <style>
    /* Custom Scrollbar */
    ::-webkit-scrollbar {
      width: 6px;
      height: 6px;
    }
    ::-webkit-scrollbar-track {
      background: rgba(15, 23, 42, 0.6);
    }
    ::-webkit-scrollbar-thumb {
      background: #334155;
      border-radius: 9999px;
    }
    ::-webkit-scrollbar-thumb:hover {
      background: #475569;
    }
    
    .glass-panel {
      background: rgba(30, 41, 59, 0.7);
      backdrop-filter: blur(12px);
      border: 1px solid rgba(255, 255, 255, 0.08);
    }
    
    .glow-purple {
      box-shadow: 0 0 25px -5px rgba(99, 102, 241, 0.3);
    }
  </style>
</head>
<body class="bg-slate-950 text-slate-100 font-sans min-h-screen flex flex-col antialiased selection:bg-brand-500 selection:text-white">

  <!-- TOP HEADER / NAVBAR -->
  <header class="border-b border-slate-800/80 bg-slate-900/60 backdrop-blur-md sticky top-0 z-40">
    <div class="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 h-16 flex items-center justify-between">
      
      <!-- Logo & Title -->
      <div class="flex items-center space-x-3">
        <div class="w-10 h-10 rounded-xl bg-gradient-to-tr from-brand-600 to-indigo-400 flex items-center justify-center text-white shadow-lg shadow-brand-500/20 font-display font-bold text-xl">
          PF
        </div>
        <div>
          <h1 class="font-display font-bold text-lg leading-none text-white tracking-tight">Promedio Fácil</h1>
          <p class="text-xs text-slate-400 mt-0.5">Gestión de Calificaciones Académicas</p>
        </div>
      </div>

      <!-- Navigation Tabs -->
      <nav class="hidden md:flex items-center space-x-1 bg-slate-800/60 p-1 rounded-xl border border-slate-700/50">
        <button id="tab-app-btn" onclick="switchMainTab('app')" class="px-4 py-1.5 rounded-lg text-sm font-medium transition-all duration-200 bg-brand-600 text-white shadow-sm flex items-center gap-2">
          <i data-lucide="calculator" class="w-4 h-4"></i>
          Calculadora & Historial
        </button>
        <button id="tab-code-btn" onclick="switchMainTab('code')" class="px-4 py-1.5 rounded-lg text-sm font-medium transition-all duration-200 text-slate-400 hover:text-white flex items-center gap-2">
          <i data-lucide="code-2" class="w-4 h-4"></i>
          Código VS Code & Descarga ZIP
        </button>
      </nav>

      <!-- Action: Quick Download ZIP -->
      <button onclick="downloadZipFiles()" class="inline-flex items-center gap-2 px-3.5 py-1.5 bg-emerald-600/20 hover:bg-emerald-600/30 text-emerald-300 border border-emerald-500/30 rounded-xl text-xs font-semibold transition-all">
        <i data-lucide="download" class="w-4 h-4 text-emerald-400"></i>
        <span>Descargar ZIP</span>
      </button>

    </div>
  </header>

  <!-- MOBILE TABS -->
  <div class="md:hidden flex border-b border-slate-800 bg-slate-900 px-4 py-2 gap-2">
    <button id="tab-app-btn-mb" onclick="switchMainTab('app')" class="flex-1 py-2 text-xs font-semibold rounded-lg bg-brand-600 text-white text-center">
      Calculadora
    </button>
    <button id="tab-code-btn-mb" onclick="switchMainTab('code')" class="flex-1 py-2 text-xs font-semibold rounded-lg bg-slate-800 text-slate-400 text-center">
      Código & ZIP
    </button>
  </div>

  <!-- MAIN CONTAINER -->
  <main class="flex-1 max-w-7xl w-full mx-auto p-4 sm:p-6 lg:p-8">

    <!-- ================= VIEW 1: CALCULATOR & DASHBOARD ================= -->
    <div id="view-app" class="space-y-6">
      
      <div class="grid grid-cols-1 lg:grid-cols-12 gap-6">
        
        <!-- LEFT COLUMN: INPUT FORM -->
        <div class="lg:col-span-5 space-y-6">
          
          <div class="glass-panel rounded-2xl p-6 shadow-xl relative overflow-hidden">
            <div class="absolute -right-10 -bottom-10 w-40 h-40 bg-brand-500/10 rounded-full blur-3xl pointer-events-none"></div>

            <div class="flex items-center gap-3 mb-6">
              <div class="p-2.5 rounded-xl bg-slate-800 text-brand-400 border border-slate-700/50">
                <i data-lucide="user-check" class="w-5 h-5"></i>
              </div>
              <div>
                <h2 class="font-display font-bold text-lg text-white">Ingreso de Calificaciones</h2>
                <p class="text-xs text-slate-400">Escala estándar de 0.0 a 5.0</p>
              </div>
            </div>

            <form id="calc-form" onsubmit="calculateGrade(event)" class="space-y-4">
              
              <!-- Student Name -->
              <div>
                <label for="student-name" class="block text-xs font-medium text-slate-300 mb-1">Nombre del Estudiante</label>
                <div class="relative">
                  <input type="text" id="student-name" value="Ana Gómez" placeholder="Ej: Ana María Gómez" required
                    class="w-full pl-10 pr-4 py-2.5 bg-slate-900/80 border border-slate-700 rounded-xl text-slate-100 text-sm focus:outline-none focus:border-brand-500 focus:ring-1 focus:ring-brand-500 transition">
                  <i data-lucide="user" class="w-4 h-4 text-slate-500 absolute left-3 top-3"></i>
                </div>
              </div>

              <!-- Grades (3 inputs) -->
              <div>
                <label class="block text-xs font-medium text-slate-300 mb-2">Las 3 Notas del Semestre</label>
                <div class="grid grid-cols-3 gap-3">
                  
                  <div>
                    <span class="text-[10px] text-slate-400 block mb-1">Nota 1</span>
                    <input type="number" id="grade1" min="0" max="5" step="0.1" value="4.2" required
                      class="w-full text-center py-2 bg-slate-900/80 border border-slate-700 rounded-xl text-slate-100 font-semibold text-sm focus:outline-none focus:border-brand-500 focus:ring-1 focus:ring-brand-500">
                  </div>

                  <div>
                    <span class="text-[10px] text-slate-400 block mb-1">Nota 2</span>
                    <input type="number" id="grade2" min="0" max="5" step="0.1" value="3.8" required
                      class="w-full text-center py-2 bg-slate-900/80 border border-slate-700 rounded-xl text-slate-100 font-semibold text-sm focus:outline-none focus:border-brand-500 focus:ring-1 focus:ring-brand-500">
                  </div>

                  <div>
                    <span class="text-[10px] text-slate-400 block mb-1">Nota 3</span>
                    <input type="number" id="grade3" min="0" max="5" step="0.1" value="4.5" required
                      class="w-full text-center py-2 bg-slate-900/80 border border-slate-700 rounded-xl text-slate-100 font-semibold text-sm focus:outline-none focus:border-brand-500 focus:ring-1 focus:ring-brand-500">
                  </div>

                </div>
              </div>

              <!-- Validation Error -->
              <div id="error-box" class="hidden p-3 rounded-xl bg-rose-500/10 border border-rose-500/20 text-rose-300 text-xs flex items-center gap-2">
                <i data-lucide="alert-circle" class="w-4 h-4 shrink-0"></i>
                <span id="error-msg">Por favor verifica los valores.</span>
              </div>

              <!-- Action Buttons -->
              <div class="pt-2 flex gap-3">
                <button type="submit" class="flex-1 py-3 bg-gradient-to-r from-brand-600 to-indigo-600 hover:from-brand-500 hover:to-indigo-500 text-white font-semibold text-sm rounded-xl shadow-lg shadow-brand-500/25 transition-all transform active:scale-95 flex items-center justify-center gap-2">
                  <i data-lucide="calculator" class="w-4 h-4"></i>
                  Calcular y Guardar
                </button>
                
                <button type="button" onclick="clearForm()" class="px-3.5 py-3 bg-slate-800 hover:bg-slate-700 text-slate-300 rounded-xl text-sm transition border border-slate-700" title="Limpiar formulario">
                  <i data-lucide="rotate-ccw" class="w-4 h-4"></i>
                </button>
              </div>

            </form>

          </div>

        </div>

        <!-- RIGHT COLUMN: LIVE RESULT CARD & SUMMARY -->
        <div class="lg:col-span-7 space-y-6">
          
          <!-- CURRENT RESULT CARD -->
          <div id="result-card" class="glass-panel rounded-2xl p-6 shadow-xl border-l-4 border-emerald-500 transition-all duration-300">
            <div class="flex flex-col sm:flex-row items-start sm:items-center justify-between gap-4">
              
              <div class="space-y-1">
                <span class="inline-flex items-center gap-1.5 px-2.5 py-1 rounded-full bg-slate-800 border border-slate-700 text-[11px] text-slate-300 font-medium">
                  <i data-lucide="sparkles" class="w-3 h-3 text-amber-400"></i> Resultado en Tiempo Real
                </span>
                <h3 id="res-name" class="text-2xl font-display font-bold text-white pt-1">Ana Gómez</h3>
                <p id="res-detail" class="text-xs text-slate-400">Notas: 4.2 · 3.8 · 4.5</p>
              </div>

              <div class="flex items-center gap-4 bg-slate-900/90 p-4 rounded-2xl border border-slate-800 min-w-[200px] justify-between">
                <div>
                  <span class="text-[10px] text-slate-400 uppercase tracking-wider block">Promedio</span>
                  <span id="res-score" class="text-4xl font-display font-extrabold text-emerald-400">4.17</span>
                </div>

                <div id="res-badge" class="px-3 py-1.5 rounded-xl bg-emerald-500/10 text-emerald-400 border border-emerald-500/20 text-xs font-bold flex items-center gap-1">
                  <i data-lucide="check-circle-2" class="w-3.5 h-3.5"></i>
                  <span>Aprobado</span>
                </div>
              </div>

            </div>
          </div>

          <!-- HISTORICAL TABLE -->
          <div class="glass-panel rounded-2xl p-6 shadow-xl space-y-4">
            <div class="flex items-center justify-between">
              <div class="flex items-center gap-3">
                <div class="p-2 rounded-xl bg-slate-800 text-slate-300 border border-slate-700">
                  <i data-lucide="history" class="w-4 h-4"></i>
                </div>
                <div>
                  <h3 class="font-display font-bold text-base text-white">Historial de Estudiantes</h3>
                  <p class="text-xs text-slate-400">Registros almacenados en esta sesión</p>
                </div>
              </div>

              <button onclick="clearHistory()" class="text-xs text-rose-400 hover:text-rose-300 transition flex items-center gap-1 hover:underline">
                <i data-lucide="trash-2" class="w-3.5 h-3.5"></i>
                <span>Vaciar Tabla</span>
              </button>
            </div>

            <div class="overflow-x-auto">
              <table class="w-full text-left text-xs text-slate-300">
                <thead class="bg-slate-900/80 text-slate-400 uppercase text-[10px] tracking-wider border-b border-slate-800">
                  <tr>
                    <th class="py-3 px-3">Estudiante</th>
                    <th class="py-3 px-2 text-center">N1</th>
                    <th class="py-3 px-2 text-center">N2</th>
                    <th class="py-3 px-2 text-center">N3</th>
                    <th class="py-3 px-3 text-center">Promedio</th>
                    <th class="py-3 px-3 text-center">Estado</th>
                    <th class="py-3 px-3 text-right">Acción</th>
                  </tr>
                </thead>
                <tbody id="history-rows" class="divide-y divide-slate-800/60 font-medium">
                  <!-- Rows injected via JS -->
                </tbody>
              </table>
            </div>

          </div>

        </div>

      </div>

    </div>


    <!-- ================= VIEW 2: VS CODE FILES & ZIP EXPORT ================= -->
    <div id="view-code" class="hidden space-y-6">
      
      <!-- Top Banner for ZIP Download -->
      <div class="glass-panel rounded-2xl p-6 shadow-2xl border border-brand-500/30 relative overflow-hidden flex flex-col md:flex-row items-center justify-between gap-6">
        <div class="space-y-1 text-center md:text-left">
          <span class="px-2.5 py-0.5 rounded-full bg-brand-500/20 text-brand-300 border border-brand-500/30 text-xs font-semibold">
            Archivos Independientes para VS Code
          </span>
          <h2 class="text-xl font-display font-bold text-white pt-1">¿Necesitas los archivos en tu computadora?</h2>
          <p class="text-xs text-slate-400 max-w-2xl">
            Descarga el paquete comprimido con la estructura limpia: <code class="bg-slate-800 px-1.5 py-0.5 rounded text-indigo-300">index.html</code>, <code class="bg-slate-800 px-1.5 py-0.5 rounded text-indigo-300">styles.css</code> y <code class="bg-slate-800 px-1.5 py-0.5 rounded text-indigo-300">script.js</code> para abrir directamente en Visual Studio Code.
          </p>
        </div>

        <button onclick="downloadZipFiles()" class="px-6 py-3 bg-gradient-to-r from-emerald-500 to-teal-600 hover:from-emerald-400 hover:to-teal-500 text-white font-bold text-sm rounded-xl shadow-lg shadow-emerald-500/20 transition flex items-center gap-2 shrink-0">
          <i data-lucide="archive" class="w-5 h-5"></i>
          Descargar .ZIP Descomprimible
        </button>
      </div>

      <!-- CODE VIEWER CONTAINER -->
      <div class="glass-panel rounded-2xl overflow-hidden shadow-2xl border border-slate-800">
        
        <!-- File Tabs Selector -->
        <div class="bg-slate-900 px-4 py-2 border-b border-slate-800 flex items-center justify-between overflow-x-auto">
          <div class="flex items-center space-x-2">
            
            <button id="file-tab-html" onclick="selectCodeFile('html')" class="px-3.5 py-2 rounded-lg text-xs font-semibold transition flex items-center gap-2 bg-brand-600 text-white">
              <span class="w-2 h-2 rounded-full bg-orange-400"></span>
              index.html
            </button>

            <button id="file-tab-css" onclick="selectCodeFile('css')" class="px-3.5 py-2 rounded-lg text-xs font-semibold transition flex items-center gap-2 bg-slate-800 text-slate-400 hover:text-white">
              <span class="w-2 h-2 rounded-full bg-blue-400"></span>
              styles.css
            </button>

            <button id="file-tab-js" onclick="selectCodeFile('js')" class="px-3.5 py-2 rounded-lg text-xs font-semibold transition flex items-center gap-2 bg-slate-800 text-slate-400 hover:text-white">
              <span class="w-2 h-2 rounded-full bg-yellow-400"></span>
              script.js
            </button>

          </div>

          <!-- Copy Code Button -->
          <button onclick="copyCurrentCode()" class="text-xs bg-slate-800 hover:bg-slate-700 text-slate-300 px-3 py-1.5 rounded-lg border border-slate-700 transition flex items-center gap-1.5">
            <i data-lucide="copy" class="w-3.5 h-3.5"></i>
            <span id="copy-btn-text">Copiar Código</span>
          </button>
        </div>

        <!-- Code Content Display -->
        <div class="relative bg-slate-950 p-4 font-mono text-xs text-slate-200 overflow-x-auto max-h-[500px]">
          <pre id="code-display"><code class="language-html">Cargando código...</code></pre>
        </div>

      </div>

    </div>

  </main>

  <!-- FOOTER -->
  <footer class="border-t border-slate-800/80 bg-slate-900/40 py-4 text-center text-xs text-slate-500">
    Promedio Fácil · Proyecto de Algoritmia & Desarrollo Web
  </footer>

  <!-- SCRIPT LOGIC -->
  <script>
    // --- STATE MANAGEMENT ---
    let history = [
      { id: 1, name: 'Ana Gómez', g1: 4.2, g2: 3.8, g3: 4.5, avg: 4.17, passed: true },
      { id: 2, name: 'Carlos Pérez', g1: 2.5, g2: 2.8, g3: 3.0, avg: 2.77, passed: false }
    ];

    let currentFile = 'html';

    // --- CODE FILE SOURCE STRINGS (Separated for Padlet & VS Code) ---
    const sourceFiles = {
      html: `<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Promedio Fácil | Calculadora de Calificaciones</title>
  <link rel="stylesheet" href="styles.css">
</head>
<body>

  <div class="container">
    <header class="header">
      <h1>🎓 Promedio Fácil</h1>
      <p>Calcula y evalúa calificaciones escolares al instante</p>
    </header>

    <main class="card">
      <form id="gradeForm">
        <div class="form-group">
          <label for="studentName">Nombre del Estudiante:</label>
          <input type="text" id="studentName" placeholder="Ej. Ana Gómez" required>
        </div>

        <div class="form-group">
          <label>Notas del Semestre (Escala 0.0 - 5.0):</label>
          <div class="grades-grid">
            <input type="number" id="grade1" min="0" max="5" step="0.1" placeholder="Nota 1" required>
            <input type="number" id="grade2" min="0" max="5" step="0.1" placeholder="Nota 2" required>
            <input type="number" id="grade3" min="0" max="5" step="0.1" placeholder="Nota 3" required>
          </div>
        </div>

        <button type="submit" class="btn-primary">Calcular Promedio</button>
      </form>

      <div id="resultBox" class="result-box">
        <h2 id="resStudent">Estudiante</h2>
        <div class="score-display">
          <span id="resScore" class="score">0.00</span>
          <span id="resStatus" class="badge">Pendiente</span>
        </div>
      </div>
    </main>
  </div>

  <script src="script.js"><\/script>
</body>
</html>`,

      css: `/* ESTILOS CSS PARA VISUAL STUDIO CODE (styles.css) */

:root {
  --bg-color: #0f172a;
  --card-bg: #1e293b;
  --text-main: #f8fafc;
  --text-muted: #94a3b8;
  --primary: #6366f1;
  --primary-hover: #4f46e5;
  --success: #10b981;
  --danger: #ef4444;
  --border-radius: 16px;
}

* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
  font-family: 'Segoe UI', system-ui, sans-serif;
}

body {
  background-color: var(--bg-color);
  color: var(--text-main);
  min-height: 100vh;
  display: grid;
  place-items: center;
  padding: 20px;
}

.container {
  width: 100%;
  max-width: 500px;
}

.header {
  text-align: center;
  margin-bottom: 24px;
}

.header h1 {
  font-size: 28px;
  color: var(--text-main);
}

.header p {
  color: var(--text-muted);
  font-size: 14px;
}

.card {
  background-color: var(--card-bg);
  padding: 28px;
  border-radius: var(--border-radius);
  border: 1px solid rgba(255, 255, 255, 0.1);
  box-shadow: 0 20px 25px -5px rgba(0, 0, 0, 0.3);
}

.form-group {
  margin-bottom: 20px;
}

label {
  display: block;
  font-size: 13px;
  font-weight: 600;
  margin-bottom: 8px;
  color: var(--text-muted);
}

input[type="text"], input[type="number"] {
  width: 100%;
  padding: 12px;
  background-color: #0f172a;
  border: 1px solid #334155;
  border-radius: 10px;
  color: #fff;
  font-size: 14px;
  outline: none;
}

input:focus {
  border-color: var(--primary);
}

.grades-grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 10px;
}

.btn-primary {
  width: 100%;
  padding: 14px;
  background-color: var(--primary);
  color: white;
  border: none;
  border-radius: 10px;
  font-weight: 700;
  cursor: pointer;
  transition: background 0.2s;
}

.btn-primary:hover {
  background-color: var(--primary-hover);
}

.result-box {
  margin-top: 24px;
  padding: 18px;
  background-color: #0f172a;
  border-radius: 12px;
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.score {
  font-size: 32px;
  font-weight: 800;
  color: var(--primary);
}

.badge {
  padding: 4px 10px;
  border-radius: 20px;
  font-size: 12px;
  font-weight: 700;
}

.badge.approved {
  background-color: rgba(16, 185, 129, 0.2);
  color: var(--success);
}

.badge.failed {
  background-color: rgba(239, 68, 68, 0.2);
  color: var(--danger);
}`,

      js: `// LÓGICA JAVASCRIPT PARA VISUAL STUDIO CODE (script.js)

document.addEventListener("DOMContentLoaded", function () {
  const form = document.getElementById("gradeForm");
  const studentInput = document.getElementById("studentName");
  const g1Input = document.getElementById("grade1");
  const g2Input = document.getElementById("grade2");
  const g3Input = document.getElementById("grade3");

  const resStudent = document.getElementById("resStudent");
  const resScore = document.getElementById("resScore");
  const resStatus = document.getElementById("resStatus");

  form.addEventListener("submit", function (e) {
    e.preventDefault();

    const name = studentInput.value.trim();
    const g1 = parseFloat(g1Input.value);
    const g2 = parseFloat(g2Input.value);
    const g3 = parseFloat(g3Input.value);

    // Validación de rango (0.0 a 5.0)
    if (isNaN(g1) || isNaN(g2) || isNaN(g3) || g1 < 0 || g1 > 5 || g2 < 0 || g2 > 5 || g3 < 0 || g3 > 5) {
      alert("Por favor ingresa notas válidas entre 0.0 y 5.0");
      return;
    }

    // Cálculo del promedio aritmético
    const promedio = (g1 + g2 + g3) / 3;
    const aprobado = promedio >= 3.0;

    // Actualizar vista de resultados
    resStudent.textContent = name;
    resScore.textContent = promedio.toFixed(2);
    resStatus.textContent = aprobado ? "Aprobado" : "Por Mejorar";
    
    resStatus.className = "badge " + (aprobado ? "approved" : "failed");
  });
});`
    };

    // --- INITIALIZATION ---
    window.addEventListener('DOMContentLoaded', () => {
      lucide.createIcons();
      renderHistory();
      renderCodeDisplay();
    });

    // --- TAB SWITCHING ---
    function switchMainTab(tab) {
      const viewApp = document.getElementById('view-app');
      const viewCode = document.getElementById('view-code');

      const btnApp = document.getElementById('tab-app-btn');
      const btnCode = document.getElementById('tab-code-btn');
      
      const btnAppMb = document.getElementById('tab-app-btn-mb');
      const btnCodeMb = document.getElementById('tab-code-btn-mb');

      if (tab === 'app') {
        viewApp.classList.remove('hidden');
        viewCode.classList.add('hidden');

        btnApp.className = "px-4 py-1.5 rounded-lg text-sm font-medium transition-all duration-200 bg-brand-600 text-white shadow-sm flex items-center gap-2";
        btnCode.className = "px-4 py-1.5 rounded-lg text-sm font-medium transition-all duration-200 text-slate-400 hover:text-white flex items-center gap-2";
        
        btnAppMb.className = "flex-1 py-2 text-xs font-semibold rounded-lg bg-brand-600 text-white text-center";
        btnCodeMb.className = "flex-1 py-2 text-xs font-semibold rounded-lg bg-slate-800 text-slate-400 text-center";
      } else {
        viewApp.classList.add('hidden');
        viewCode.classList.remove('hidden');

        btnCode.className = "px-4 py-1.5 rounded-lg text-sm font-medium transition-all duration-200 bg-brand-600 text-white shadow-sm flex items-center gap-2";
        btnApp.className = "px-4 py-1.5 rounded-lg text-sm font-medium transition-all duration-200 text-slate-400 hover:text-white flex items-center gap-2";

        btnCodeMb.className = "flex-1 py-2 text-xs font-semibold rounded-lg bg-brand-600 text-white text-center";
        btnAppMb.className = "flex-1 py-2 text-xs font-semibold rounded-lg bg-slate-800 text-slate-400 text-center";
      }
    }

    // --- CALCULATOR LOGIC ---
    function calculateGrade(e) {
      e.preventDefault();
      
      const name = document.getElementById('student-name').value.trim();
      const g1 = parseFloat(document.getElementById('grade1').value);
      const g2 = parseFloat(document.getElementById('grade2').value);
      const g3 = parseFloat(document.getElementById('grade3').value);

      const errorBox = document.getElementById('error-box');
      const errorMsg = document.getElementById('error-msg');

      if (!name) {
        showError('Debes ingresar el nombre del estudiante.');
        return;
      }

      if (isNaN(g1) || isNaN(g2) || isNaN(g3) || g1 < 0 || g1 > 5 || g2 < 0 || g2 > 5 || g3 < 0 || g3 > 5) {
        showError('Las tres notas deben estar entre 0.0 y 5.0.');
        return;
      }

      errorBox.classList.add('hidden');

      const avg = (g1 + g2 + g3) / 3;
      const passed = avg >= 3.0;

      // Update Result Card
      document.getElementById('res-name').textContent = name;
      document.getElementById('res-detail').textContent = `Notas: ${g1.toFixed(1)} · ${g2.toFixed(1)} · ${g3.toFixed(1)}`;
      document.getElementById('res-score').textContent = avg.toFixed(2);

      const card = document.getElementById('result-card');
      const badge = document.getElementById('res-badge');
      const scoreEl = document.getElementById('res-score');

      if (passed) {
        card.className = "glass-panel rounded-2xl p-6 shadow-xl border-l-4 border-emerald-500 transition-all duration-300";
        badge.className = "px-3 py-1.5 rounded-xl bg-emerald-500/10 text-emerald-400 border border-emerald-500/20 text-xs font-bold flex items-center gap-1";
        badge.innerHTML = `<i data-lucide="check-circle-2" class="w-3.5 h-3.5"></i><span>Aprobado</span>`;
        scoreEl.className = "text-4xl font-display font-extrabold text-emerald-400";
      } else {
        card.className = "glass-panel rounded-2xl p-6 shadow-xl border-l-4 border-rose-500 transition-all duration-300";
        badge.className = "px-3 py-1.5 rounded-xl bg-rose-500/10 text-rose-400 border border-rose-500/20 text-xs font-bold flex items-center gap-1";
        badge.innerHTML = `<i data-lucide="alert-triangle" class="w-3.5 h-3.5"></i><span>Por Mejorar</span>`;
        scoreEl.className = "text-4xl font-display font-extrabold text-rose-400";
      }

      // Add to History
      history.unshift({
        id: Date.now(),
        name,
        g1,
        g2,
        g3,
        avg: parseFloat(avg.toFixed(2)),
        passed
      });

      renderHistory();
      lucide.createIcons();
    }

    function showError(msg) {
      const errorBox = document.getElementById('error-box');
      const errorMsg = document.getElementById('error-msg');
      errorMsg.textContent = msg;
      errorBox.classList.remove('hidden');
    }

    function clearForm() {
      document.getElementById('student-name').value = '';
      document.getElementById('grade1').value = '';
      document.getElementById('grade2').value = '';
      document.getElementById('grade3').value = '';
      document.getElementById('error-box').classList.add('hidden');
    }

    function renderHistory() {
      const tbody = document.getElementById('history-rows');
      if (history.length === 0) {
        tbody.innerHTML = `<tr><td colspan="7" class="py-6 text-center text-slate-500 text-xs">No hay registros guardados.</td></tr>`;
        return;
      }

      tbody.innerHTML = history.map(item => `
        <tr class="hover:bg-slate-800/40 transition">
          <td class="py-3 px-3 font-semibold text-white">${escapeHtml(item.name)}</td>
          <td class="py-3 px-2 text-center text-slate-400">${item.g1.toFixed(1)}</td>
          <td class="py-3 px-2 text-center text-slate-400">${item.g2.toFixed(1)}</td>
          <td class="py-3 px-2 text-center text-slate-400">${item.g3.toFixed(1)}</td>
          <td class="py-3 px-3 text-center font-bold ${item.passed ? 'text-emerald-400' : 'text-rose-400'}">${item.avg.toFixed(2)}</td>
          <td class="py-3 px-3 text-center">
            <span class="inline-block px-2 py-0.5 rounded-full text-[10px] font-bold ${item.passed ? 'bg-emerald-500/10 text-emerald-400 border border-emerald-500/20' : 'bg-rose-500/10 text-rose-400 border border-rose-500/20'}">
              ${item.passed ? 'Aprobado' : 'Por Mejorar'}
            </span>
          </td>
          <td class="py-3 px-3 text-right">
            <button onclick="deleteItem(${item.id})" class="text-slate-500 hover:text-rose-400 transition p-1" title="Eliminar fila">
              <i data-lucide="x" class="w-3.5 h-3.5"></i>
            </button>
          </td>
        </tr>
      `).join('');
      
      lucide.createIcons();
    }

    function deleteItem(id) {
      history = history.filter(item => item.id !== id);
      renderHistory();
    }

    function clearHistory() {
      history = [];
      renderHistory();
    }

    function escapeHtml(text) {
      return text.replace(/[&<>"']/g, function(m) {
        return { '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#039;' }[m];
      });
    }

    // --- CODE DISPLAY & COPY ---
    function selectCodeFile(fileKey) {
      currentFile = fileKey;

      const tabs = {
        html: document.getElementById('file-tab-html'),
        css: document.getElementById('file-tab-css'),
        js: document.getElementById('file-tab-js')
      };

      Object.keys(tabs).forEach(key => {
        if (key === fileKey) {
          tabs[key].className = "px-3.5 py-2 rounded-lg text-xs font-semibold transition flex items-center gap-2 bg-brand-600 text-white";
        } else {
          tabs[key].className = "px-3.5 py-2 rounded-lg text-xs font-semibold transition flex items-center gap-2 bg-slate-800 text-slate-400 hover:text-white";
        }
      });

      renderCodeDisplay();
    }

    function renderCodeDisplay() {
      const codeDisplay = document.getElementById('code-display');
      codeDisplay.textContent = sourceFiles[currentFile];
    }

    function copyCurrentCode() {
      const codeText = sourceFiles[currentFile];
      
      const el = document.createElement('textarea');
      el.value = codeText;
      document.body.appendChild(el);
      el.select();
      document.execCommand('copy');
      document.body.removeChild(el);

      const btnText = document.getElementById('copy-btn-text');
      btnText.textContent = '¡Copiado!';
      setTimeout(() => {
        btnText.textContent = 'Copiar Código';
      }, 2000);
    }

    // --- ZIP DOWNLOAD FUNCTION (Generates index.html, styles.css, script.js) ---
    function downloadZipFiles() {
      const zip = new JSZip();

      // Add the 3 files to the ZIP
      zip.file("index.html", sourceFiles.html);
      zip.file("styles.css", sourceFiles.css);
      zip.file("script.js", sourceFiles.js);

      // Generate the ZIP file and trigger download
      zip.generateAsync({ type: "blob" }).then(function (content) {
        saveAs(content, "PromedioFacil_VSCode.zip");
      });
    }
  </script>
</body>
</html>
