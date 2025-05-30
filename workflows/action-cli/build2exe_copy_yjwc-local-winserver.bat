@echo off
mkdir out
cd out
::生成exe，生成到out目录
"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" /O. ..\InstallerScript.iss
::拷贝到目标目录
copy "out\*.exe" "E:\Share\软件发布\TUGS2.0安装包" /y






