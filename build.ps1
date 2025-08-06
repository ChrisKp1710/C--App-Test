# DevNotes Build Script per MSYS2 Qt6
# Esegui con: powershell -ExecutionPolicy Bypass .\build.ps1

param(
    [string]$Mode = "release"  # debug o release
)

Write-Host "🏗️  DevNotes Build System (MSYS2 Qt6)" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan

# Path MSYS2 Qt6
$msysPath = "C:\msys64\mingw64\bin"
$qtPath = "C:\msys64\mingw64"

# Verifica MSYS2 Qt6 installation
if (-not (Test-Path "$msysPath\qmake6.exe")) {
    Write-Host "❌ Qt6 non trovato in MSYS2. Installa con:" -ForegroundColor Red
    Write-Host "pacman -S mingw-w64-x86_64-qt6-base mingw-w64-x86_64-qt6-declarative mingw-w64-x86_64-qt6-tools" -ForegroundColor Yellow
    exit 1
}

Write-Host "📍 MSYS2 Qt6 Path: $qtPath" -ForegroundColor Green

# Aggiorna PATH per includere MSYS2 tools
$env:PATH = "$msysPath;$env:PATH"

# Pulisci build precedenti
Write-Host "🧹 Pulizia build precedenti..." -ForegroundColor Yellow
if (Test-Path "obj") { Remove-Item -Recurse -Force "obj" }
if (Test-Path "DevNotes.exe") { Remove-Item -Force "DevNotes.exe" }
if (Test-Path "Makefile") { Remove-Item -Force "Makefile" }
if (Test-Path "Makefile.Debug") { Remove-Item -Force "Makefile.Debug" }
if (Test-Path "Makefile.Release") { Remove-Item -Force "Makefile.Release" }

# Genera Makefile con qmake6
Write-Host "⚙️  Generazione Makefile..." -ForegroundColor Yellow
$qmakeArgs = @("DevNotes.pro")
if ($Mode -eq "debug") {
    $qmakeArgs += "CONFIG+=debug"
} else {
    $qmakeArgs += "CONFIG+=release"
}

& qmake6 @qmakeArgs
if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ Errore durante qmake6" -ForegroundColor Red
    exit 1
}

# Compila con mingw32-make
Write-Host "🔨 Compilazione in corso..." -ForegroundColor Yellow
& mingw32-make -j4
if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ Errore durante la compilazione" -ForegroundColor Red
    exit 1
}

# Verifica risultato
if (Test-Path "DevNotes.exe") {
    Write-Host "✅ Build completata con successo!" -ForegroundColor Green
    Write-Host "📱 Eseguibile: DevNotes.exe" -ForegroundColor Green
    
    # Mostra informazioni file
    $fileInfo = Get-Item "DevNotes.exe"
    Write-Host "📊 Dimensione: $([math]::Round($fileInfo.Length / 1MB, 2)) MB" -ForegroundColor Cyan
    Write-Host "📅 Creato: $($fileInfo.CreationTime)" -ForegroundColor Cyan
    
    # Opzione per eseguire
    $run = Read-Host "🚀 Vuoi eseguire DevNotes? (y/N)"
    if ($run -eq "y" -or $run -eq "Y") {
        Write-Host "🎬 Avvio DevNotes..." -ForegroundColor Green
        Start-Process ".\DevNotes.exe"
    }
} else {
    Write-Host "❌ Build fallita - eseguibile non trovato" -ForegroundColor Red
    exit 1
}
