REM ---------------------------------------------------------------------------------------------------
REM
REM		 generate_all_project_opengl.bat : 	Nom de ce batch  
REM
REM      Batch de lancement de toutes les [re]générations des application OpenGL sous Windows (sources C avec un fichier resource) afin de tenir compte d'évolutions (version compilateurs, 
REM    version des sources, version CB, ...) avec plusieurs batchs de génération : d'abord la génération CMAKE, puis la génération "command files" et enfin la génération Code::Blocks (en mode ligne de commande).
REM
REM		Cette proécédure gère deux ou trois paramètres : 
REM				- le répertoire général des sources 								(par exemple C:\src\OpenGL dans mon cas)
REM 			- le type de generations attendues parmi la liste suivante : 		CMAKE,CMD, CB ou ALL
REM 							CMAKE 	: toutes les generations en mode CMAKE
REM 							CMD 	: toutes les generations en mode "lignes de commandes"
REM 							CB 		: toutes les generations à l'aide de l'IDE Code::Blocks (mais aussi en mode "ligne de commande") 
REM 							ALL 	: toutes les generations de tout type : CMAKE puis "ligne de commande" puis Code::Blocks
REM     		- le format général des répertoires contenant les projets OpenGL sous le répertoire général (optionnel)
REM 							(par exemple NeHe_Lesson#nn#-master dans mon cas, #nn# valant 01 à 47 avec des trous lors de l'itération ...)
REM 			
REM		Ce dernier paramètre est optionnel, et dans ce cas, il y a recherche des répertoires présents sous le répertoire genéral des sources, à la recherche des fichiers *.workspace (CB).
REM
REM     Dans les grands principes, ce batch lancce TOUTES les générations "batch" des projets OpenGL
REM 
REM 	AUTHOR : 						Thierry DECHAIZE
REM     Date de création :				22 août 2022   
REM 	Date dernière modification : 	15 juin 2024 
REM 	Détails des modifications : 	Adjonction d'un deuxième paramètre obligatoire permettant de choisir le type de generation : CMAKE, CMD, CB ou ALL
REM 	Version de ce script :			1.1.1  ->  "Version majeure" . "Version mineure" . "niveau de patch"
REM
REM      Pour mémoire, pour la génération sous Code::Blocks, les paramètres suivants permettent de suivre le déroulement des batchs de génération : --batch-build-notify --no-batch-window-close
REM
REM ---------------------------------------------------------------------------------------------------

REM     Affichage du nom du système d'exploitation Windows :              			Microsoft Windows 11 Famille 	(par exemple)
REM 	Affichage de la version du système Windows :              					10.0.22631 						(par exemple)
REM 	Affichage de l'architecture du processeur supportant le système Windows :   AMD64 							(par exemple)    
echo.  *********  Quelques caracteristiques du systeme hebergeant l'environnement de developpement.   ***********
WMIC OS GET Name
WMIC OS GET Version
echo "Processor architecture : %PROCESSOR_ARCHITECTURE%"
cmake --version
  
if [%1]==[] goto usage
if not exist %1\ goto usage
if [%2]==[] goto usage
echo "Répertoire général des applications OpenGL 									: %1"
echo "Type de generations attendues 												: %2"
if [%2] NEQ [] echo "Format général des répertoires contenant les projets OpenGL 	: %3"
 
set mydate=%date%
set mytime=%time%
set DAY=%mydate:~0,2%
set MONTH=%mydate:~3,2%
set YEAR=%mydate:~6,4%
echo Beginning of generate_all_project_opengl.bat, current time is %mydate%:%mytime%

set DIRINIT=%CD%
SET PATHINIT=%PATH%
SET DIRTARGET=%1
SET TYPEGEN=%2
cd %DIRTARGET%

IF "%2" NEQ "CMAKE" (
   IF "%2" NEQ "CMD" (
		IF "%2" NEQ "CB" (
			IF "%2" NEQ "ALL" goto USAGE
		)
   )
)

if [%3]==[] goto :LISTE_DIR
set "MOT1=NeHe_"
SET "MOT2=-master"

SETLOCAL ENABLEDELAYEDEXPANSION
FOR /L %%x IN (1,1,47) DO ( call :name_appli %%x)
endlocal
goto :FIN

:LISTE_DIR
SETLOCAL ENABLEDELAYEDEXPANSION
FOR /D %%a in (%1%) DO (
   cd %%a
   for /f "tokens=1,2 delims=." %%g in ("*.workspace") do ( 
		call :generate_all %2 %%a %%g
	)
)
endlocal
goto :FIN

:name_appli
IF %1 LSS 10 ( set "APPLI=Lesson0%1" ) else ( set "APPLI=Lesson%1" )
echo !APPLI!
echo %MOT1%!APPLI!%MOT2%
if exist %MOT1%!APPLI!%MOT2%\ call :generate_all %TYPEGEN% %MOT1%!APPLI!%MOT2% !APPLI!
cd %DIRTARGET%
EXIT /B

:generate_all
cd %~2
set CURDIR=%CD%
if "%~1" EQU "CMAKE" (
	if exist "generate_all_with_cmake.bat" generate_all_with_cmake.bat %CD% %~3 NOARC > generate_all_with_cmake.txt
	cd %CURDIR%
	)
if "%~1" EQU "CMD" (
	if exist "generate_all_with_command_files.bat" generate_all_with_command_files.bat %CD% %~3 NOARC > generate_all_with_command_files.txt
	cd %CURDIR%
	)
if "%~1" EQU "CB" (
	if exist "%~3.workspace" codeblocks.exe /na /nd --no-splash-screen --rebuild --target="All build" "%~3.workspace"
	cd %CURDIR%
	)
if "%~1" EQU "ALL" (
	if exist "generate_all_with_cmake.bat" generate_all_with_cmake.bat %CD% %~3 NOARC > generate_all_with_cmake.txt
	cd %CURDIR%
	if exist "generate_all_with_command_files.bat" generate_all_with_command_files.bat %CD% %~3 NOARC > generate_all_with_command_files.txt
	cd %CURDIR%
	if exist "%~3.workspace" codeblocks.exe /na /nd --no-splash-screen --rebuild --target="All build" "%~3.workspace"
	cd %CURDIR%
	)
EXIT /B

REM example -> codeblocks.exe /na /nd --no-splash-screen --rebuild --target="All build" Lesson01.workspace

:usage
echo Usage : %0 GENERAL_DIRECTORY TYPE [FORMAT_DIR_APPLI] 
echo   GENERAL_DIRECTORY donnant le répertoire principal des projets OpenGL       	(le plus souvent C:\src\OpenGL par exemple)
echo   TYPE, le type de generations attendues parmi la liste suivante : 			CMAKE, CMD, CB ou ALL  
echo   FORMAT_DIR_APPLI donnant le "motif" de base des noms des répertoires       	(par exemple : NeHe_Lesson#nn#-master dans mon cas, #nn# valant 01 à 47 avec des trous lors de l'itération ...)  
echo   			et si pas de troisieme parametre, generation des differents projets OpenGL presents sous le répertoire general (recherche de TOUS les répertoires)
 
:FIN
cd %DIRINIT%
SET PATH=%PATHINIT%
set mydate=%date%
set mytime=%time%
echo End of generate_all_project_opengl.bat, current time is %mydate%:%mytime%