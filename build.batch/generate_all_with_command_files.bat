@echo off
REM ---------------------------------------------------------------------------------------------------
REM
REM		 Nom de ce batch : generate_all_with_command_files.bat	  
REM
REM     Batch de lancement de toutes les g�n�rations d'une application Windows (source C avec un fichier resource de m�me nom) 
REM     avec plusieurs batchs de g�n�ration, ou bien d'une seule g�n�ration cibl�e.
REM
REM		Cette pro�c�dure g�re trois param�tres : le r�pertoire de l'application � g�n�rer, le nom de l'application (qui devient le nom de l'ex�cutable), et un param�tre optionnel
REM     l'id de la g�n�ration, qui fait partie de la liste suivante :
REM
REM          [BCC|MINGW32OF|MINGW64CB|DEVCPP|CYGWIN32|CYGWIN64|MINGW32WL|MINGW64WL|TDM32|TDM64|MSYS2W32|MSYS2W64|MSYS2U64|NMAKEX32|NMAKEX64|VS2022X32|VS2022X64|INTELX32|INTELX64|CLANGX32|CLANGX64|CLANGW32|CLANGW64|CLANGMW32|CLANGMW64|DMC|LCC32|LCC64|PELLESC32|PELLESC64|WATCOM32|WATCOM64] 
REM
REM     Dans les grands principes, il y a un fichier batch diff�rent pour chaque cat�gorie de compilateurs stock� sous %APPLI_DIR%\build.batch\Compil_link_"Id Compilateur"_[32|64]b_windows.bat
REM     Il est n�cessaire de g�n�rer l'application attendue pour chacune des versions Debug et Release (.ie. on lance le batch deux fois de suite ...).
REM     Il faut bien etendu, positionner pour chaque compilateur les variables d'environnement PATH, et parfois LIB et INCLUDE, mais tout cette "tambouille" d'identification de r�pertoires
REM 	est bien g�r�e dans chacun de ces batchs. J'ai ainsi permis un totale autonomie : vous pouvez les utilisez ind�pendamment de TOUTES contraintes d'outils tierces.
REM 	Seuls, les param�trages de chaque PATH, INCLUDE (il peut en exister plusieurs INC1, INC2 ...) et LIB (il peuten exister plusieurs LIB, LIB2 ...) sont d�pendants des r�pertoires
REM     d'installation des diff�rents environnements de d�veloppement (IDE + compilateurs, compilateurs ou packages assimilant/englobant compilateurs + outils).
REM
REM     Points d'attention, j'ai positionn� des variables d'environnement sous Windows (en mode "syst�me") pour g�rer les diff�rentes versions de Visual Studio, du KIT WINDOWS et de CLANG installees :
REM          CLANG_VERSION     valu� (� date) par       18.1.6    		(derni�re version sur Windows 11, aussi bien pour les binaires valables pour VS2022 que pour les environnements Mingw et MSYS)
REM          VS_VERSION        valu� (� date) par       2022       		(derni�re version sur Windows 11)
REM          VS_NUM            valu� (� date) par       14.40.33807     (derni�re version sur Windows 11)
REM          KIT_WIN_VERSION   valu� (� date) par       10    			(derni�re version sur Windows 11)
REM          KIT_WIN_NUM       valu� (� date) par       10.0.22621.0    (derni�re version sur Windows 11)
REM
REM 	PS : la proc�dure "create_dir.bat" permet de cr�er TOUS les r�pertoires utiles � ces g�n�rations multiples (certains compilateurs ne sont pas caapbles de les cr�er ONLINE s'ils sont absents),
REM          et ensuite on lance generate_all_with_command_files.bat "nom_r�pertoire" "nom_appli" [id_generator].
REM 
REM 	AUTHOR : 						Thierry DECHAIZE
REM     Date de cr�ation :				10 octobre 2022   
REM 	Date derni�re modification : 	11 juin 2024 : Adjonction des g�n�rations en mode "batch" pour le compilateur OneAPI INTEL  C/C++ compiler (32 et 64 bits)
REM 	D�tails des modifications : 	Pour cette adjonction, il faut correctement positionner le PATH Windows ainsi que les variables d'environnement INCLUDE et LIB
REM 	Version de ce script :			1.2.2  ->  "Version majeure" . "Version mineure" . "niveau de patch"
REM
REM ---------------------------------------------------------------------------------------------------
  
if [%1]==[] goto usage
if not exist %1\ goto usage
@echo off
echo "Directory del'application : %1"
echo "Nom de l'application  	: %2"
 
set mydate=%date%
set mytime=%time%
set DAY=%mydate:~0,2%
set MONTH=%mydate:~3,2%
set YEAR=%mydate:~6,4%
echo Beginning of generate_all_with_command_files.bat, current time is %mydate%:%mytime%

set DIRINIT=%CD%
SET PATHSAV=%PATH%
set APPLI_DIR=%1
set NAME_APPLI=%2
cd %1

@setlocal enableextensions enabledelayedexpansion 
:SEARCH_SRC
dir /a-d /b %1\src > lst_src.txt
for /f "tokens=* delims=" %%a in ('type lst_src.txt') do (	
	IF NOT "%%a"=="%2.c" (
	    SET NAMEC=%%a
		echo %NAMEC%
		call :findinstring %%a ".c"
		)
)

endlocal
goto :SUITE

:findinstring
ECHO.%~1 | FIND /I "%~2">Nul && (
  for /f "tokens=1,2 delims=." %%a in ("%NAMEC%") do (  
	if exist %1\src_c.txt (
	  echo.%%a>> %1\src_c.txt
	  ) else (
	  echo.%%a> %1\src_c.txt
	  )
   )	
) || (
  Echo.Not found ".c"
)
EXIT /B

:SUITE
if "%3" NEQ "" goto %3

REM             G�n�ration batch pour le compilateur Borland C/C++ 5.51 
:BCC
echo "G�n�ration batch pour le compilateur Borland C/C++ 5.51 : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_Borland_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour le compilateur Borland C/C++ 5.51 : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_Borland_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 9.2.0 int�gr� � MINGW32 (version officielle)
:MINGW32OF
echo "G�n�ration batch pour GCC 9.2.0 int�gr� � MINGW32 (version officielle) : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_MINGW32OF_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 9.2.0 int�gr� � MINGW32 (version officielle) : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_MINGW32OF_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 11.2.0 int�gr� � Red-Panda DevCpp 2.10  (Dev-Cpp n'est plus maintenu !)
:DEVCPP
echo "G�n�ration batch pour GCC 11.2.0 int�gr� � Red-Panda DevCpp 2.10 : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_DEVCPP_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 11.2.0 int�gr� � Red-Panda DevCpp 2.10 : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_DEVCPP_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 13.1.0 int�gr� � l'environnement IDE Code::Blocks
:MINGW64CB
echo "G�n�ration batch pour GCC 13.1.0 int�gr� � l'environnement IDE Code::Blocks : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_MINGW64CB_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 13.1.0 int�gr� � l'environnement IDE Code::Blocks : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_MINGW64CB_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 11.1.0 32 bits int�gr� � l'environnement CYGWIN 64 bits
:CYGWIN32
echo "G�n�ration batch pour GCC 11.4.0 32 bits int�gr� � l'environnement CYGWIN 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_cygwin_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 11.4.0 32 bits int�gr� � l'environnement CYGWIN 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_cygwin_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 11.1.0 64 bits int�gr� � l'environnement CYGWIN 64 bits
:CYGWIN64
echo "G�n�ration batch pour GCC 11.4.0 64 bits int�gr� � l'environnement CYGWIN 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_cygwin_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 11.4.0 64 bits int�gr� � l'environnement CYGWIN 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_cygwin_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 13.2.0 32 bits int�gr� au package WINLIBS
:MINGW32WL
echo "G�n�ration batch pour GCC 13.2.0 32 bits int�gr� au package WINLIBS : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_MINGW32WL_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 13.2.0 32 bits int�gr� au package WINLIBS : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_MINGW32WL_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 13.2.0 64 bits int�gr� au package WINLIBS
:MINGW64WL
echo "G�n�ration batch pour GCC 13.2.0 64 bits int�gr� au package WINLIBS : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_MINGW64WL_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 13.2.0 64 bits int�gr� au package WINLIBS : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_MINGW64WL_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 13.2.0 32 bits int�gr� � l'environnement MSYS2 
:MSYS2W32
echo "G�n�ration batch pour GCC 13.2.0 32 bits int�gr� � l'environnement MSYS2 : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_MSYS2W32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 13.2.0 32 bits int�gr� � l'environnement MSYS2 : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_MSYS2W32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 13.2.0 64 bits int�gr� � l'environnement MSYS2 
:MSYS2W64
echo "G�n�ration batch pour GCC 13.2.0 64 bits int�gr� � l'environnement MSYS2 : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_MSYS2W64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 13.2.0 64 bits int�gr� � l'environnement MSYS2 : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_MSYS2W64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 13.2.0 UCRT 64 bits int�gr� � l'environnement MSYS2 
:MSYS2U64
echo "G�n�ration batch pour GCC 13.2.0 UCRT 64 bits int�gr� � l'environnement MSYS2 : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_MSYS2U64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 13.2.0 UCRT 64 bits int�gr� � l'environnement MSYS2 : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_MSYS2U64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 10.3.0 int�gr� � l'environnement TDM 32 bits
:TDM32
echo "G�n�ration batch pour GCC 10.3.0 int�gr� � l'environnement TDM 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_TDMW32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 10.3.0 int�gr� � l'environnement TDM 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_TDMW32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour GCC 10.3.0 int�gr� � l'environnement TDM 64 bits
:TDM64
echo "G�n�ration batch pour GCC 10.3.0 int�gr� � l'environnement TDM 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_TDMW64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour GCC 10.3.0 int�gr� � l'environnement TDM 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_TDMW64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour Visual Studio 2022 Community en version 32 bits
:VS2022X32
echo "G�n�ration batch pour Visual Studio 2022 Community en version 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_VS2022X32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour Visual Studio 2022 Community en version 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_VS2022X32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour Visual Studio 2022 Community en version 64 bits
:VS2022X64 
echo "G�n�ration batch pour Visual Studio 2022 Community en version 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_VS2022X64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour Visual Studio 2022 Community en version 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_VS2022X64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour OneAPI INTEL C/C++ compiler adoss� � Visual Studio 2022 en version 32 bits
:INTELX32
echo "G�n�ration batch pour OneAPI INTEL C/C++ compiler adoss� � Visual Studio 2022 en version 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_INTELX32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour OneAPI INTEL C/C++ compiler adoss� � Visual Studio 2022 en version 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_INTELX32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour OneAPI INTEL C/C++ compiler adoss� � Visual Studio 2022 en version 64 bits
:INTELX64 
echo "G�n�ration batch pour OneAPI INTEL C/C++ compiler adoss� � Visual Studio 2022 en version 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_INTELX64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour OneAPI INTEL C/C++ compiler adoss� � Visual Studio 2022 en version 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_INTELX64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour CLANG en version 32 bits adoss� � Visual Studio 2022 
:CLANGX32 
echo "G�n�ration batch pour CLANG en version 32 bits adoss� � Visual Studio 2022 : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_CLANGX32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour CLANG en version 32 bits adoss� � Visual Studio 2022 : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_CLANGX32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour CLANG en version 64 BITS adoss� � Visual Studio 2022 
:CLANGX64 
echo "G�n�ration batch pour CLANG en version 64 bits adoss� � Visual Studio 2022 : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_CLANGX64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour CLANG en version 64 bits adoss� � Visual Studio 2022 : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_CLANGX64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour CLANG MINGW GNU/GCC en version 32 bits
:CLANGW32
echo "G�n�ration batch pour CLANG MINGW GNU/GCC en version 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_CLANGW32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour CLANG MINGW GNU/GCC en version 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_CLANGW32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour CLANG MINGW GNU/GCC en version 64 bits
:CLANGW64
echo "G�n�ration batch pour CLANG MINGW GNU/GCC en version 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_CLANGW64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour CLANG MINGW GNU/GCC en version 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_CLANGW64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour CLANG MSYS2 GNU/GCC en version 32 bits
:CLANGMW32
echo "G�n�ration batch pour CLANG MSYS2 GNU/GCC en version 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_CLANGMW32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour CLANG MSYS2 GNU/GCC en version 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_CLANGMW32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour CLANG MSYS2 GNU/GCC en version 64 bits
:CLANGMW64
echo "G�n�ration batch pour CLANG MSYS2 GNU/GCC en version 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_CLANGMW64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour CLANG MSYS2 GNU/GCC en version 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_CLANGMW64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour DMC 32 bits
:DMC
echo "G�n�ration batch pour DMC 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_dmc_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour DMC 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_dmc_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour LCC 32 bits
:LCC32
echo "G�n�ration batch pour LCC 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_lcc32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour LCC 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_lcc32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour LCC 64 bits
:LCC64
echo "G�n�ration batch pour LCC 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_lcc64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour LCC 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_lcc64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour PellesC 32 bits
:PELLESC32
echo "G�n�ration batch pour PellesC 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_pellesc32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour PellesC 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_pellesc32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour PellesC 64 bits
:PELLESC64
echo "G�n�ration batch pour PellesC 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_pellesc64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour PellesC 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_pellesc64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch pour Open WATCOM 2.0 en version 32 bits
:WATCOM32
echo "G�n�ration batch pour Open WATCOM 2.0 en version 32 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_OW32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour Open WATCOM 2.0 en version 32 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_OW32_32b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
IF "%3" NEQ "" GOTO FIN

REM             G�n�ration batch our Open WATCOM 2.0 en version 64 bits 
:WATCOM64
echo "G�n�ration batch pour Open WATCOM 2.0 en version 64 bits : mode Debug"
call %APPLI_DIR%\build.batch\Compil_link_OW64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Debug
echo "G�n�ration batch pour Open WATCOM 2.0 en version 64 bits : mode Release"
call %APPLI_DIR%\build.batch\Compil_link_OW64_64b_windows.bat %APPLI_DIR% %NAME_APPLI% windows Release
 
:ARCHIVE
del /Q *.7z *.tgz *.tar
if exist %1\lst_src.txt del %1\lst_src.txt
if exist %1\src_c.txt del %1\src_c.txt
REM "C:\CodeBlocks\cbp2make.exe" --local -in $(project_dir)$(project_filename) -out makefile
%PYTHON64% ..\..\tools\Size_exec.py %NAME_APPLI%
%PYTHON64% ..\..\tools\Calc_checksums_exe.py %NAME_APPLI%
"C:\Program Files\7-Zip\7z" a %NAME_APPLI%_%YEAR%-%MONTH%-%DAY%_src.7z src\*.* res\*.* data\*.* build.cmake\* build.batch\* *.bat *.txt *.html *.md doxygen\* doc\* *.cbp *.workspace -x!*.bak README makefile -mhe -p"%NAME_APPLI%_tde@03!"
"C:\Program Files\7-Zip\7z" a -ttar %NAME_APPLI%-%YEAR%-%MONTH%_%DAY%_all.tar * -x!*.7z x!*.bak 
"C:\Program Files\7-Zip\7z" a %NAME_APPLI%_%YEAR%-%MONTH%-%DAY%_all.7z *.tar -mhe -p"%NAME_APPLI%_tde@03!"
del /Q *.tar
set mydate=%date%
set mytime=%time%
echo End of generate_all_with_command_files.bat, current time is %mydate%:%mytime%
GOTO FIN

:usage
echo Usage : %0 DIRECTORY_SRC NAME_APPLI [Id_Compilateur] 
echo   avec Id_Compilateur = [BCC|MINGW32OF|MINGW64CB|DEVCPP|CYGWIN32|CYGWIN64|MINGW32WL|MINGW64WL|TDM32|TDM64|MSYS2W32|MSYS2W64|NMAKEX32|NMAKEX64|VS2022X32|VS2022X64|CLANGX32|CLANGX64|CLANGW32|CLANGW64|CLANGMW32|CLANGMW64|DMC|LCC32|LCC64|PELLESC32|PELLESC64|WATCOM32|WATCOM64]
echo   et si pas de trois�me param�tre, g�n�ration de toutes les compilations en mode "batch" pour chaque cat�gorie de compilateurs en mode Debug puis Release
 
:FIN
cd %DIRINIT%


