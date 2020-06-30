@echo off
echo Building - Cre8 Demo
pushd build
REM ======================== DEBUG BUILD ============================= 
echo Debug Build
cl /nologo /FC /Z7 /Fedemo.exe ..\code\demo.cpp /link user32.lib gdi32.lib winmm.lib /DEBUG:FULL /incremental:no /opt:ref
REM ======================== DEBUG BUILD ============================= 
REM
REM ======================= RELEASE BUILD ============================ 
REM echo Release build
REM cl /nologo /FC /Fedemo.exe /Oi /O2 ..\code\demo.cpp /link user32.lib gdi32.lib winmm.lib /incremental:no /opt:ref
REM ======================= RELEASE BUILD ============================ 
popd


REM cl Compiler Flags:
REM ------------------
REM Zi         : debug info (use Z7 for older debug format for complex builds)
REM Zo         : More debug info for optimized builds
REM FC         : Full path on errors
REM Oi         : Always use intrinsics when possible
REM Od         : No optimizations
REM OZ         : Full optimizations
REM MT         : Use c static runtime instead of searching for dll at run-time
REM MTd        : Same as MT but use the debug version of crt
REM GR-        : Turn off C++ runtime type info
REM Gm-        : Turn off incremental build (depreciated)
REM EHa-       : Turn off exception handling
REM WX         : Treat warnings as errors
REM W4         : Set warning level to 4
REM wd         : Ignore warning 
REM fp:fast    : Ignores the rules sometimes to optimize fp operations
REM Fmfile.map : Outputs a file map (mapping of the functions in an exe)
REM Feout.exe  : Specifies exe name and directory
REM c          : Only compile do not link; user needs to call LINK

REM Linker options:
REM ---------------
REM /link                : link commands
REM subsytem:windows,5.1 : make exe compatible with Windows XP (only in x86 mode)
REM OPT:REF              : do not put unused things in the exe
REM incremental:no       : do not build incremental
REM LD                   : build DLL
REM PDB:file.pdb         : change the .pdb's path
