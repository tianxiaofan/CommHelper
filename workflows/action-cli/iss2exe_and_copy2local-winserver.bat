@echo off

chcp 65001
mkdir out
cd out
:: 打包exe
"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" /O. "..\workflows\action-cli\InstallerScript.iss"

:: 获取当前版本号和上一次的版本号
setlocal enabledelayedexpansion
set /a line=1
for /f %%i in ('git rev-list --tags --max-count=2' )  do (
if !line!==1 set CURRENT_COMMIT=%%i
if !line!==2 set LAST_COMMIT=%%i
set /a line+=1
)

echo %CURRENT_COMMIT%
echo %LAST_COMMIT%

for /f %%a in ('git describe --abbrev^=0 --tags %CURRENT_COMMIT%') do set CURRENT_TAG=%%a
for /f %%a in ('git describe --abbrev^=0 --tags %LAST_COMMIT%') do set LAST_TAG=%%a

echo %CURRENT_TAG%
echo %LAST_TAG%

REM 获取当前的提交哈希值（HEAD提交）
for /f %%h in ('git rev-parse HEAD') do set HEAD_COMMIT=%%h
echo Current commit (HEAD): %HEAD_COMMIT%

REM 检查当前提交是否与最后一个标签的提交一致
if "%HEAD_COMMIT%"=="%CURRENT_COMMIT%" (
    set FILE_NAME=TUGS_%CURRENT_TAG%_x64_windows
) else (
    set FILE_NAME=TUGS_master_x64_windows
)

echo FILE_NAME: %FILE_NAME%

REM 重命名生成的安装文件为 TUGS_<tag>_x64_windows.exe
ren "installer.exe" "%FILE_NAME%.exe"

copy "%FILE_NAME%.exe" "E:\Share\软件发布\TUGS2.0" /y

REM 删除out目录下的所有exe文件
del /q "*.exe"
