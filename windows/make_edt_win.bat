@call "%~dp0set_path.bat"

:: Check Visual Studio 2005
:: ========================
@call "%~dp0..\_src\eidmw\SetPathVs2005.bat"
@if %ERRORLEVEL%==0 goto find_vs2005

@echo [TIP] Use set_path.bat script to define PTEID_DIR_VS_2005
@goto end

:find_vs2005
@echo [INFO] Using PTEID_DIR_VS_2005=%PTEID_DIR_VS_2005%

:: Check if MW binaries exist
:: ==========================
@call "%~dp0..\_src\eidmw\CheckFilesMwRelease.bat"
@if %ERRORLEVEL%==0 goto find_MW

@echo [TIP] Please build the middleware first
@goto end

:find_MW


:: Check QT 4.5.0 exe
:: ==================
@call "%~dp0..\_src\eidmw\SetPathQt450_Exe.bat"
@if %ERRORLEVEL%==0 goto find_qt450_exe

@echo [TIP] Use set_path.bat script to define PTEID_DIR_QT_450_EXE
@goto end

:find_qt450_exe
@echo [INFO] Using PTEID_DIR_QT_450_EXE=%PTEID_DIR_QT_450_EXE%


:: Check QT 4.5.0 include
:: ======================
@call "%~dp0..\_src\eidmw\SetPathQt450_Include.bat"
@if %ERRORLEVEL%==0 goto find_qt450_include

@echo [TIP] Use set_path.bat script to define PTEID_DIR_QT_450_INCLUDE 
@goto end

:find_qt450_include
@echo [INFO] Using PTEID_DIR_QT_450_INCLUDE=%PTEID_DIR_QT_450_INCLUDE%

:: Check QT 4.5.0 static
:: =====================
@call "%~dp0..\_src\eidmw\SetPathQt450_Static.bat"
@if %ERRORLEVEL%==0 goto find_qt450_static

@echo [TIP] Use set_path.bat script to define PTEID_DIR_QT_450_STATIC 
@goto end

:find_qt450_static
@echo [INFO] Using PTEID_DIR_QT_450_STATIC=%PTEID_DIR_QT_450_STATIC%


:: BUILD
:: =====

@if "%DEBUG%"=="1" goto debug

:build
@echo [INFO] Building "%~dp0..\_src\eDT\eDT.sln"
@"%PTEID_DIR_VS_2005%\Common7\IDE\devenv.exe" "%~dp0..\_src\eDT\eDT.sln" /clean Release
@"%PTEID_DIR_VS_2005%\Common7\IDE\devenv.exe" "%~dp0..\_src\eDT\eDT.sln" /build Release

@echo [INFO] Done...
@goto end

:debug
@"%PTEID_DIR_VS_2005%\Common7\IDE\devenv.exe" "%~dp0..\_src\eDT\eDT.sln"
@goto end

:end
@if NOT "%DEBUG%"=="1" pause