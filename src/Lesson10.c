/*
 *		This Code Was Created By Lionel Brits & Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 *      Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/24
 */

 /***************************************************************
 *  Project: $(project)
 *  Function : Main program
 ***************************************************************
 *  $Author: Jeff Molofee 2000
 *  $Name:  $
 ***************************************************************
 *
 *  Copyright NeHe Production
 *
 ***************************************************************/

/**         Comments manageable by Doxygen
*
*  Modified smoothly by Thierry DECHAIZE.
*
*  Paradigm : obtain one source (only one !) compatible for multiple free C Compilers (many GCC compilers included in MinGW, Mingw32, Mingw64, MSYS2, CYGWIN64,
*	 TDM, and another Visual C/C++ included in Visual Studio + kits Windows, LCC, WATCOM, DMC, Borland, OneAPI Intel compiler, many CLANG compilers, etc..)
*    and provide for all users an development environment on Windows 11 64 bits the great Code::Blocks IDE (improved version "nightly build" 23.06),
*    and don't use glaux.lib or glaux.dll (old and buggy library).
*
*	a) Mingw 32 bits, official version, with version gcc 9.2.0 (very old !) : downloadable on http://sourceforge.net/projects/mingw/ (dead branch ?)
*	b) Mingw 64 bits included in new IDE Red Panda Cpp varsion 3.1, version gcc 12.2.0 : donwloadable on https://sourceforge.net/projects/redpanda-cpp/files/
*	c) Mingw 64 bits included in package Code::Blocks (version 20.03 with mingw), downloadable on http://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/
*           but improved with most recent version of MinGW64 + gcc (version gcc 13.1.0) with "nightly build" dated of 4 june 2023 downloadable on :
*                       https://sourceforge.net/projects/codeblocks/files/Binaries/Nightlies/2023/CB_20230604_rev13311_win64-setup-MinGW.exe
*	d) Mingw 32 and 64 bits packaged, version gcc 14.2.0 : downloadable on  https://winlibs.com/ (and CLANG included in, 32 and 64 bits), two kits :
*			- winlibs-i686-posix-dwarf-gcc-14.2.0-llvm-19.1.1-mingw-w64ucrt-12.0.0-r2.7z (32 bits)
*			- winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.1-mingw-w64ucrt-12.0.0-r2.7z (64 bits)
*	e) Cygwin64 with three compilers, "native" GCC 64 bits and GCC in MinGW32 + MinGW64, versions gcc 12.4.0 : downloadable on http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*	f) TDM GCC, 32 and 64 bits, version 10.3.0 : downloadable on http://sourceforge.net/projects/TDM-GCC
*	g) MSYS2 environment MINGW32 and MINGW64, 32 et 64 bits, version de 2024 (msys2-x86_64-20240727.exe), version gcc 14.2.0 : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20240727.exe
*	h) Visual Studio 2022, 32 and 64 bit, community edition for free : downloadable on https://visualstudio.microsoft.com/fr/vs/community/
*	i) Borland C/C++ 32 bit, version 5.5.1 : downloadable on https://developerinsider.co/download-and-install-borland-c-compiler-on-windows-10/
*	j) Digital Mars Compiler C 32 bits, installation package version 8.57 : downloadable on http://www.digitalmars.com (the more old compiler, the more bugged, dead branch !)
*	k) OpenWatcom 32 and 64 bit, version 2.0 (frequently rebuild) : downloadable on https://github.com/open-watcom/open-watcom-v2/releases/tag/Current-build
*	l) Lcc and Lcc64, 32 and 64 bit : downloadable http://www.cs.virginia.edu/~lcc-win32/  (not really free !)
*	m) PELLES C, 32 and 64 bit, version 12.0 : downloadable on http://www.smorgasbordet.com/pellesc/
*	o) CLANG 32 and 64 bit included in version WinLibs, leaned at environments MINGW64 et MINGW32, version 19.1.1 (version gcc 14.2.0) : downloadable on https://winlibs.com/
*	p) CLANG 32 and 64 bit leaned at environments Visual Studio 2022 (+ kits Microsoft), version 19.1.1 : downloadable on https://releases.llvm.org/download.html
*	q) CLANG 32 and 64 bit included in version MSYS2, leaned at environments MINGW64 et MINGW32, version 18.1.8 (version gcc 14.2.0) : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
*	r) CLANG 32 bit of version CYGWIN64, adossé aux environnements MINGW64 et MINGW32, version 8.0.0, very old (version gcc 12.4.0) : downloadable http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*	s) OneAPI Intel C/C++ compiler 32 and 64 bit, version 2024.2.1 downloadable on site https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html
*
*   TDE -> Add resource file end resource header for restitute version + icon OpenGL.ico for fun, because versionning is important, same for freeware :-) !
*
*   62 generations with "All build" target into IDE Code::Blocks, or with CMAKE (and "make" tools with compilers don't supported with CMAKE), or,
*   finally, with "command files" (versions 32 or 64 bits, "Debug" or "Release"), just "for fun" or "academic demonstration" of these tools.
*
*  Date : 2024/10/16
*
* \file            Lesson10.c
* \author          Jeff Molofee ( NeHe ) originely, Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/23
* \author          After adapted by Thierry Dechaize to verify paradigm : one source for multiple C Compilers
* \version         2.0.4.0
* \date            16 octobre 2024
* \brief           Open simple window on Windows systems and create a 3D world in which you can navigated on click on "arrows key".
* \details         This program manage only three "Windows" events : click on "arrows key" on keyboard, click on button "Close" of open windows or exit by touch "ESC",
* \details         but manage also "Fullscreen" or not.
* \details 		   WARNING : Bug detected with Pelles C Compiler :  filein = fopen("../../data/world.txt", "rt"); fail because option "rt" is undefined in any std reference of
* \details 				language C. It's only a "tolerance" supported by many compiler on Windows ... except Pelles C. It's a major reason of rewrite of functions "SetWorld"
* \details 				and "readstr" in this source => it's not the orginally source of NeHe Lesson10. Tested with success with all free compilers described below or in "Notes"
* \details 				into CB project.
*
*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>		/* Header File For Windows OS                  */

#if defined(__LCC__)
#ifndef WINGDIAPI
#   define WINGDIAPI __stdcall
#endif
#endif

#include <math.h>			/*  Math Library Header File                    					*/
#include <stdio.h>			/* Header File For Standard Input/Output        					*/
#include <string.h>         /* Header File foe string comparaison           					*/
#include <gl\gl.h>			/* Header File For The OpenGL32 Library         					*/
#include <gl\glu.h>			/* Header File For The GLu32 Library            					*/
#include <stdlib.h>         /* Header File for malloc function              					*/
// #include <gl\glaux.h>	/* Header File For The Glaux Library (NEW), but volontary unused ... */
#include "logger.h"         /* Added by Thierry DECHAIZE : logger for trace and debug if needed ...  */

// 				Warning : in originally include file "stdbool.h" of Pelles C compiler, only two boolean variables are defined : "true" and "false".
// 				To support this source, it's necessary to add "TRUE" and "FALSE" in this file (write protected in first time, but if you have "admin"
//				privilege, you can change this protection in submenu "property" after click on this file, remain to return in protected mode after change ...).
#include <stdbool.h>

// A ``bool'' type for compilers that don't yet support one.
#if !defined(__bool_true_false_are_defined)

  typedef int bool;

  #ifdef true
    #warning Better check include file ``mytypes.h''.
    #undef true
  #endif
  #define true 1
  #define TRUE 1

  #ifdef false
    #warning Better check include file ``mytypes.h''.
    #undef false
  #endif
  #define false 0
  #define FALSE 0

#endif

#include "resource.h"		// Header File in which you define "resources" used by this program (icons, info of version, ...)

#ifndef		CDS_FULLSCREEN										/* CDS_FULLSCREEN Is Not Defined By Some    */
#define		CDS_FULLSCREEN 4									/* Compilers. By Defining It This Way,      */
#endif

HDC			hDC=NULL;		/* Private GDI Device Context                                   */
HGLRC		hRC=NULL;		/* Permanent Rendering Context                                  */
HWND		hWnd=NULL;		/* Holds Our Window Handle                                      */
HINSTANCE	hInstance;		/* Holds The Instance Of The Application                        */

BOOL	keys[256];			/* Array Used For The Keyboard Routine                          */
BOOL	active=TRUE;		/* Window Active Flag Set To TRUE By Default                    */
BOOL	fullscreen=TRUE;	/* Fullscreen Flag Set To Fullscreen Mode By Default            */
BOOL	blend;				/* Blending ON/OFF                                              */
BOOL	bp;					/* B Pressed ?                                                  */
BOOL	fp;					/* F Pressed ?                                                  */

char *level_debug;          /* added by Thierry DECHAIZE, needed in test of logging activity (only with DEBUG mode) */
bool level_def = true;

const float piover180 = 0.0174532925f;
float heading;
float xpos;
float zpos;

GLfloat	yrot;				/* Y Rotation                                                   */
GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;
GLfloat lookupdown = 0.0f;
GLfloat	z=0.0f;				/* Depth Into The Screen                                        */

GLuint	filter=0;			/* Which Filter To Use                                          */
GLuint	texture[3],texid[3]; /* Storage For 3 Textures                                      */

typedef struct tagVERTEX
{
	float x, y, z;
	float u, v;
} VERTEX;

typedef struct tagTRIANGLE
{
	VERTEX vertex[3];
} TRIANGLE;

typedef struct tagSECTOR
{
	int numtriangles;
	TRIANGLE* triangle;
} SECTOR;

SECTOR sector1;				/* Our Model Goes Here:                                         */

static	PIXELFORMATDESCRIPTOR pfd=					/* pfd Tells Windows How We Want Things To Be,  move at the top level of this source file because someone compilers require it   */
	{
		sizeof(PIXELFORMATDESCRIPTOR),				/* Size Of This Pixel Format Descriptor     */
		1,											/* Version Number                           */
		PFD_DRAW_TO_WINDOW |						/* Format Must Support Window               */
		PFD_SUPPORT_OPENGL |						/* Format Must Support OpenGL               */
		PFD_DOUBLEBUFFER,							/* Must Support Double Buffering            */
		PFD_TYPE_RGBA,								/* Request An RGBA Format                   */
		0,  										/* Select Our Color Depth                   */
		0, 0, 0, 0, 0, 0,							/* Color Bits Ignored                       */
		0,											/* No Alpha Buffer                          */
		0,											/* Shift Bit Ignored                        */
		0,											/* No Accumulation Buffer                   */
		0, 0, 0, 0,									/* Accumulation Bits Ignored                */
		16,											/* 16Bit Z-Buffer (Depth Buffer)            */
		0,											/* No Stencil Buffer                        */
		0,											/* No Auxiliary Buffer                      */
		PFD_MAIN_PLANE,								/* Main Drawing Layer                       */
		0,											/* Reserved                                 */
		0, 0, 0										/* Layer Masks Ignored                      */
    };


int loop = 0, vert = -1;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	/* Declaration For WndProc              */

// 				Not the originally function "readstr" describe in "real" source of NeHe Lesson10
void readstr(char *string)
{
	float x, y, z, u, v;
    int numtriangles = 0;
#ifdef DEBUG
    if (level_def) {
        if ((strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0))
            log_print(__FILE__, __LINE__,"In function readstr analyze this record : %s",string);
    }
#endif /* defined DEBUG         */
	if (strstr(string, "NUMPOLLIES") != NULL) {
		sscanf(string, "NUMPOLLIES %d\n", &numtriangles);
        if (numtriangles == 0)									// Attempt To Register The Window Class
            {
                MessageBox(NULL,"Failed to read config file","ERROR",MB_OK|MB_ICONEXCLAMATION);
                return ;											// Return
            }
		sector1.triangle = (TRIANGLE *) malloc(sizeof(TRIANGLE)*numtriangles);
//	    sector1.triangle = new TRIANGLE[numtriangles];         //   in C++
		sector1.numtriangles = numtriangles;
	} else {
		if (strstr(string, "//") == NULL) {
            vert++;
			sscanf(string, "%f %f %f %f %f", &x, &y, &z, &u, &v);
			sector1.triangle[loop].vertex[vert].x = x;
			sector1.triangle[loop].vertex[vert].y = y;
			sector1.triangle[loop].vertex[vert].z = z;
			sector1.triangle[loop].vertex[vert].u = u;
			sector1.triangle[loop].vertex[vert].v = v;
			if (vert == 2) {
				vert = -1;
				loop++;
			}
		}
	}
	return;
}

// 				Not the originally function "SetupWorld" describe in "real" source of NeHe Lesson10
void SetupWorld()
{
	FILE *filein;
	char oneline[255];
/*      World.txt describe single vertex in your 3D scene : the first three numbers are the x, y and z coordinates,
        and last two numbers are the texture coordinates for that vertex.

        X Y Z U V

        They are grouped into rows of three and six to define a triangle or a quad (two triangles obviously).
    */
	filein = fopen("../../data/world.txt", "r");				/* File To Load World Data From         */
    if (filein == NULL)									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Unabled to read config file","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return ;											// Return
	}

#ifdef DEBUG
    if (level_def) {
        if ((strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0))
            log_print(__FILE__, __LINE__,"In function SetupWorld -> fichier traite : ../../data/world.txt .");
    }
#endif /* defined DEBUG         */

    while (fgets(oneline, 255, filein)) {
        //: Check for empty lines:
        if( strcmp(oneline,"\n"  ) != 0 &&
            strcmp(oneline,"\r\n") != 0 &&
            strcmp(oneline,"\0"  ) != 0 && 1){
				readstr(oneline);
			} else {
				continue;
			}
        }

	fclose(filein);

#ifdef DEBUG
    if (level_def) {
        if ((strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0))
            log_print(__FILE__, __LINE__,"At the end of function SetupWorld");
    }
#endif /* defined DEBUG         */

	return;
}

/**	            This Code Creates Texture From a Bitmap File.
*
* \brief      Fonction NeHeLoadBitmap3 : charge un fichier BMP en mémoire pour generer un tableau de trois textures
* \details    En entrée le nom du fichier Bitmap et en sortie le tableau des trois textures utilisables avec OpenGL
* \param	  szFileName			nom du fichier BMP				                *
* \param	  *texid			    un pointeur sur lae tableau des trois textures générées			    *
* \return     bool                  un booleen, le tableau des trois textures créé ou non.
*
*/

bool NeHeLoadBitmap3(LPTSTR szFileName, GLuint *texid)					/* Creates Texture From A Bitmap File   */
{
	HBITMAP hBMP;														/* Handle Of The Bitmap                 */
	BITMAP	BMP;														/* Bitmap Structure                     */

    glGenTextures(3, &texid[0]);					                    /* Create Three Textures                */

#ifdef DEBUG
    if (level_def) {
        if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
            log_print(__FILE__, __LINE__,"At the beginning of function NeHeLoadBitmap3, load file name : %s.\n",szFileName);
    }
#endif /* defined DEBUG         */

	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP)															/* Does The Bitmap Exist?               */
		return FALSE;													/* If Not Return False                  */

	GetObject(hBMP, sizeof(BMP), &BMP);									/* Get The Object                       */
																		/* hBMP:        Handle To Graphics Object               */
																		/* sizeof(BMP): Size Of Buffer For Object Information   */
																		/* &BMP:        Buffer For Object Information           */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);								/* Pixel Storage Mode (Word Alignment / 4 Bytes)        */

    /* Create Nearest Filtered Texture      */
    glBindTexture(GL_TEXTURE_2D, texid[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, BMP.bmBits);

    /* Create Linear Filtered Texture       */
    glBindTexture(GL_TEXTURE_2D, texid[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, BMP.bmBits);

    /* Create MipMapped Texture             */
    glBindTexture(GL_TEXTURE_2D, texid[2]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_RGB, GL_UNSIGNED_BYTE, BMP.bmBits);


	DeleteObject(hBMP);													/* Delete The Object            */

#ifdef DEBUG
    if (level_def) {
        if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
            log_print(__FILE__, __LINE__,"At the ending of function NeHeLoadBitmap3.");
    }
#endif /* defined DEBUG         */

	return TRUE;														// Loading Was Successful
}

int LoadGLTextures()									/* Load Bitmaps And Convert To Textures */
{
#ifdef DEBUG
    if (level_def) {
        if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
            log_print(__FILE__, __LINE__,"At the beginning of function LoadGLTextures.");
    }
#endif /* defined DEBUG         */

	/* Start Of User Initialization     */
	if (!NeHeLoadBitmap3("../../Data/Mud2.bmp", texture))	/* Load The Bitmap                  */
		return FALSE;

#ifdef DEBUG
    if (level_def) {
        if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
            log_print(__FILE__, __LINE__,"At the ending of function LoadGLTextures.");
    }
#endif /* defined DEBUG         */

	return TRUE;										    /* Return The Status                */
}

/**	            This Code Resize the main window.
*
* \brief      Fonction ReSizeGLScene : redimensionnement de la fenêtre Windows gérant OpenGL
* \details    En entrée les deux nouvelles dimensions de la fenêtre
* \param	  width			Width of the GL Window Or Fullscreen Mode				*
* \param	  height		Height of the GL Window Or Fullscreen Mode			    *
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		/* Resize And Initialize The GL Window  */
{
	if (height==0)										/* Prevent A Divide By Zero By          */
	{
		height=1;										/* Making Height Equal One              */
	}

	glViewport(0,0,width,height);						/* Reset The Current Viewport           */

	glMatrixMode(GL_PROJECTION);						/* Select The Projection Matrix         */
	glLoadIdentity();									/* Reset The Projection Matrix          */

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							/* Select The Modelview Matrix          */
	glLoadIdentity();									/* Reset The Modelview Matrix           */
}

/**	            This Code finish the initialization OpenGL of the main window.
*
* \brief      Fonction InitGL : Fin de l'initialisation de la fenêtre Windows gérant OpenGL
* \details    Rien
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int InitGL(GLvoid)										/* All Setup For OpenGL Goes Here           */
{

#ifdef DEBUG
    if (level_def) {
        if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
            log_print(__FILE__, __LINE__,"At the beginning of function InitGL.");
    }
#endif /* defined DEBUG         */

	if (!LoadGLTextures())								/* Jump To Texture Loading Routine              */
	{
		return FALSE;									/* If Texture Didn't Load Return FALSE          */
	}

	glEnable(GL_TEXTURE_2D);							/* Enable Texture Mapping                       */
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					/* Set The Blending Function For Translucency   */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				/* This Will Clear The Background Color To Black */
	glClearDepth(1.0);									/* Enables Clearing Of The Depth Buffer         */
	glDepthFunc(GL_LESS);								/* The Type Of Depth Test To Do                 */
	glEnable(GL_DEPTH_TEST);							/* Enables Depth Testing                        */
	glShadeModel(GL_SMOOTH);							/* Enables Smooth Color Shading                 */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	/* Really Nice Perspective Calculations         */

	SetupWorld();

#ifdef DEBUG
    if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
         log_print(__FILE__, __LINE__,"At the ending of function InitGL.");
#endif /* defined DEBUG         */

	return TRUE;										/* Initialization Went OK                       */
}

/**	            This Code draw the scene OpenGL in the main window.
*
* \brief      Fonction DrawGLScene : Dessin sous OpenGL dans la fenêtre Windows.
* \details    Rien
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int DrawGLScene(GLvoid)									/* Here's Where We Do All The Drawing           */
{
	GLfloat x_m, y_m, z_m, u_m, v_m;
	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias-0.25f;
	GLfloat sceneroty = 360.0f - yrot;

	int numtriangles;
	int loop_m = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/* Clear The Screen And The Depth Buffer        */
	glLoadIdentity();									/* Reset The View                               */

	glRotatef(lookupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);

	glTranslatef(xtrans, ytrans, ztrans);
    glBindTexture(GL_TEXTURE_2D, texture[filter]);

	numtriangles = sector1.numtriangles;

	// Process Each Triangle
	for (loop_m = 0; loop_m < numtriangles; loop_m++)
	{
		glBegin(GL_TRIANGLES);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			x_m = sector1.triangle[loop_m].vertex[0].x;
			y_m = sector1.triangle[loop_m].vertex[0].y;
			z_m = sector1.triangle[loop_m].vertex[0].z;
			u_m = sector1.triangle[loop_m].vertex[0].u;
			v_m = sector1.triangle[loop_m].vertex[0].v;
			glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);

			x_m = sector1.triangle[loop_m].vertex[1].x;
			y_m = sector1.triangle[loop_m].vertex[1].y;
			z_m = sector1.triangle[loop_m].vertex[1].z;
			u_m = sector1.triangle[loop_m].vertex[1].u;
			v_m = sector1.triangle[loop_m].vertex[1].v;
			glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);

			x_m = sector1.triangle[loop_m].vertex[2].x;
			y_m = sector1.triangle[loop_m].vertex[2].y;
			z_m = sector1.triangle[loop_m].vertex[2].z;
			u_m = sector1.triangle[loop_m].vertex[2].u;
			v_m = sector1.triangle[loop_m].vertex[2].v;
			glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
		glEnd();
        glBindTexture(GL_TEXTURE_2D, texture[filter]);
	}
	return TRUE;										/* Everything Went OK                   */
}

/**	            This Code destroy all resources of this program.
*
* \brief      Fonction KillGLWindow : Destruction de toutes les ressources du programme.
* \details    Rien
* \param	  GLvoid			un void OpenGL.
* \return     GLvoid        	un void OpenGL.
*
*/

GLvoid KillGLWindow(GLvoid)								/* Properly Kill The Window                         */
{
	if (fullscreen)										/* Are We In Fullscreen Mode?                       */
	{
		ChangeDisplaySettings(NULL,0);					/* If So Switch Back To The Desktop                 */
		ShowCursor(TRUE);								/* Show Mouse Pointer                               */
	}

	if (hRC)											/* Do We Have A Rendering Context?                  */
	{
		if (!wglMakeCurrent(NULL,NULL))					/* Are We Able To Release The DC And RC Contexts ?  */
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						/* Are We Able To Delete The RC?                    */
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										/* Set RC To NULL                                   */
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					/* Are We Able To Release The DC                    */
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										/* Set DC To NULL                                   */
	}

	if (hWnd && !DestroyWindow(hWnd))					/* Are We Able To Destroy The Window?               */
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										/* Set hWnd To NULL                                 */
	}

	if (!UnregisterClass("OpenGL",hInstance))			/* Are We Able To Unregister Class                  */
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									/* Set hInstance To NULL                            */
	}
}

/**	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *  \brief          Creation of our OpenGL Window
 *  \param 			title			- Title To Appear At The Top Of The Window				*
 *	\param 			width			- Width Of The GL Window Or Fullscreen Mode				*
 *	\param 			height			- Height Of The GL Window Or Fullscreen Mode			*
 *	\param          bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	\param          fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*
 *  \return         BOOL            - un entier booleen (OK ou non).
 */

BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
	GLuint		PixelFormat;			/* Holds The Results After Searching For A Match        */
	WNDCLASS	wc;						/* Windows Class Structure                              */
	DWORD		dwExStyle;				/* Window Extended Style                                */
	DWORD		dwStyle;				/* Window Style                                         */
	RECT		WindowRect;				/* Grabs Rectangle Upper Left / Lower Right Values      */
	WindowRect.left=(long)0;			/* Set Left Value To 0                                  */
	WindowRect.right=(long)width;		/* Set Right Value To Requested Width                   */
	WindowRect.top=(long)0;				/* Set Top Value To 0                                   */
	WindowRect.bottom=(long)height;		/* Set Bottom Value To Requested Height                 */

	fullscreen=fullscreenflag;			/* Set The Global Fullscreen Flag                       */

	hInstance			= GetModuleHandle(NULL);				/* Grab An Instance For Our Window          */
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	/* Redraw On Size, And Own DC For Window.   */
	wc.lpfnWndProc		= (WNDPROC) WndProc;					/* WndProc Handles Messages                 */
	wc.cbClsExtra		= 0;									/* No Extra Window Data                     */
	wc.cbWndExtra		= 0;									/* No Extra Window Data                     */
	wc.hInstance		= hInstance;							/* Set The Instance                         */
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			/* Load The Default Icon                    */
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			/* Load The Arrow Pointer                   */
	wc.hbrBackground	= NULL;									/* No Background Required For GL            */
	wc.lpszMenuName		= NULL;									/* We Don't Want A Menu                     */
	wc.lpszClassName	= "OpenGL";								/* Set The Class Name                       */

#ifdef DEBUG
    if (level_def) {
        if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
            log_print(__FILE__, __LINE__,"At the beginning of function CreateGLWindow.");
    }
#endif /* defined DEBUG         */

	if (!RegisterClass(&wc))									/* Attempt To Register The Window Class     */
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											/* Return FALSE                             */
	}

	if (fullscreen)												/* Attempt Fullscreen Mode?                 */
	{
		DEVMODE dmScreenSettings;								/* Device Mode                              */
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	/* Makes Sure Memory's Cleared              */
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		/* Size Of The Devmode Structure            */
		dmScreenSettings.dmPelsWidth	= width;				/* Selected Screen Width                    */
		dmScreenSettings.dmPelsHeight	= height;				/* Selected Screen Height                   */
		dmScreenSettings.dmBitsPerPel	= bits;					/* Selected Bits Per Pixel                  */
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		/* Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.       */
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			/* If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.        */
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		/* Windowed Mode Selected.  Fullscreen = FALSE      */
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									/* Return FALSE             */
			}
		}
	}

	if (fullscreen)												/* Are We Still In Fullscreen Mode ?            */
        {
		dwExStyle=WS_EX_APPWINDOW;								/* Window Extended Style                        */
		dwStyle=WS_POPUP;										/* Windows Style                                */
		ShowCursor(FALSE);										/* Hide Mouse Pointer                           */
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			/* Window Extended Style                        */
		dwStyle=WS_OVERLAPPEDWINDOW;							/* Windows Style                                */
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		/* Adjust Window To True Requested Size     */

#ifdef DEBUG
    if (level_def) {
        if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
            log_print(__FILE__, __LINE__,"In function CreateGLWindow, before CreateWindowsEx.");
    }
#endif /* defined DEBUG         */

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							/* Extended Style For The Window            */
								"OpenGL",							/* Class Name                               */
								title,								/* Window Title                             */
								dwStyle |							/* Defined Window Style                     */
								WS_CLIPSIBLINGS |					/* Required Window Style                    */
								WS_CLIPCHILDREN,					/* Required Window Style                    */
								0, 0,								/* Window Position                          */
								WindowRect.right-WindowRect.left,	/* Calculate Window Width                   */
								WindowRect.bottom-WindowRect.top,	/* Calculate Window Height                  */
								NULL,								/* No Parent Window                         */
								NULL,								/* No Menu                                  */
								hInstance,							/* Instance                                 */
								NULL)))								/* Dont Pass Anything To WM_CREATE          */
	{
		KillGLWindow();								/* Reset The Display            */
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								/* Return FALSE                 */
	}

    pfd.cColorBits = bits;

    if (!(hDC=GetDC(hWnd)))                         /* Did We Get A Device Context ? */
    {	KillGLWindow();								/* Reset The Display            */
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								/* Return FALSE                 */
	}

    if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))/* Did Windows Find A Matching Pixel Format ?  */
	{
        PixelFormat=0;
		KillGLWindow();								/* Reset The Display            */
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								/* Return FALSE                 */
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		/* Are We Able To Set The Pixel Format ? */
	{
		KillGLWindow();								/* Reset The Display            */
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								/* Return FALSE                 */
	}

	if (!(hRC=wglCreateContext(hDC)))				/* Are We Able To Get A Rendering Context ? */
	{
		KillGLWindow();								/* Reset The Display            */
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								/* Return FALSE                 */
	}

	if(!wglMakeCurrent(hDC,hRC))					/* Try To Activate The Rendering Context */
	{
		KillGLWindow();								/* Reset The Display            */
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								/* Return FALSE                 */
	}

	ShowWindow(hWnd,SW_SHOW);						/* Show The Window                      */
	SetForegroundWindow(hWnd);						/* Slightly Higher Priority             */
	SetFocus(hWnd);									/* Sets Keyboard Focus To The Window    */

#ifdef DEBUG
    if (level_def) {
        if (strcmp(level_debug,"BASE") == 0 || strcmp(level_debug,"FULL") == 0)
            log_print(__FILE__, __LINE__,"In function CreateGLWindow, before ReSizeGLScene.");
    }
#endif /* defined DEBUG         */

	ReSizeGLScene(width, height);					/* Set Up Our Perspective GL Screen     */

	if (!InitGL())									/* Initialize Our Newly Created GL Window */
	{
		KillGLWindow();								/* Reset The Display            */
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								/* Return FALSE                 */
	}

	return TRUE;									/* Success                      */
}

/**         Comments manageable by Doxygen
*
* \brief      Fonction CALLBACK de traitement des messages Windows
* \details    Traitement de la boucle infinie des messages Windows
* \param      hWnd         L'header de la fenêtre principale.
* \param      uMsg         Un entier non signé.
* \param      wParam       Les paramétres en entrée.
* \param      lParam       Autres paramétres en entrée.
* \return     LRESULT 	   Un LRESULT donnant le status du traitement du message.
*
*/

LRESULT CALLBACK WndProc(	HWND	hWnd,			/* Handle For This Window               */
							UINT	uMsg,			/* Message For This Window              */
							WPARAM	wParam,			/* Additional Message Information       */
							LPARAM	lParam)			/* Additional Message Information       */
{
	switch (uMsg)									/* Check For Windows Messages           */
	{
		case WM_ACTIVATE:							/* Watch For Window Activate Message    */
		{
			if (!HIWORD(wParam))					/* Check Minimization State             */
			{
				active=TRUE;						/* Program Is Active                    */
			}
			else
			{
				active=FALSE;						/* Program Is No Longer Active          */
			}

			return 0;								/* Return To The Message Loop           */
		}

		case WM_SYSCOMMAND:							/* Intercept System Commands            */
		{
			switch (wParam)							/* Check System Calls                   */
			{
				case SC_SCREENSAVE:					/* Screensaver Trying To Start ?        */
				case SC_MONITORPOWER:				/* Monitor Trying To Enter Powersave ?  */
				return 0;							/* Prevent From Happening               */
			}
			break;									/* Exit                                 */
		}

		case WM_CLOSE:								/* Did We Receive A Close Message ?     */
		{
			PostQuitMessage(0);						/* Send A Quit Message                  */
			return 0;								/* Jump Back                            */
		}

		case WM_KEYDOWN:							/* Is A Key Being Held Down ?           */
		{
			keys[wParam] = TRUE;					/* If So, Mark It As TRUE               */
			return 0;								/* Jump Back                            */
		}

		case WM_KEYUP:								/* Has A Key Been Released ?            */
		{
			keys[wParam] = FALSE;					/* If So, Mark It As FALSE              */
			return 0;								/* Jump Back                            */
		}

		case WM_SIZE:								/* Resize The OpenGL Window             */
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  /* LoWord=Width, HiWord=Height   */
			return 0;								/* Jump Back                            */
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

/**	This Code is mandatory to create windows application (function WinMain)					*
 *  \brief          Creation of our application on Windows System (not console application) *
 *  \param 			hInstance		- Header de l'instance Windows				            *
 *	\param 			hPrevInstance	- Header de l'instance précédente de Windows 			*
 *	\param 			lpCmdLine		- Un pointeur sur la ligne de commande 			        *
 *	\param          nCmdShow		- Un indicateur d'état			                        *
 *  \return         int             - un entier booleen (OK ou non).                        *
 *	                                                                                        *
 */

int WINAPI WinMain(	HINSTANCE	hInstance,			/* Instance                             */
					HINSTANCE	hPrevInstance,		/* Previous Instance                    */
					LPSTR		lpCmdLine,			/* Command Line Parameters              */
					int			nCmdShow)			/* Window Show State                    */
{
	MSG		msg;									/* Windows Message Structure            */
	BOOL	done=FALSE;								/* BOOL Variable To Exit Loop           */

    level_debug=getenv("LEVEL");  /* Added by Thierry DECHAIZE : récupérer la valeur de la variable d'environnement LEVEL */
    if (level_debug == NULL)  {
//      printf( "LEVEL variable is undefined.\n");
      level_def = FALSE;
    }
#ifdef DEBUG
    if (level_def) {
        if ((strcmp(level_debug,"BASE") == 0) || (strcmp(level_debug,"FULL") == 0))
            log_print(__FILE__, __LINE__,"Lancement du programme Lesson10.");
    }
#endif /* defined DEBUG         */

#ifdef DEBUG
    if (level_def) {
        if ((strcmp(level_debug,"BASE") == 0) || (strcmp(level_debug,"FULL") == 0))
            log_print(__FILE__, __LINE__,"Niveau de trace : %s.",level_debug);
    }
#endif /* defined DEBUG         */

	/* Ask The User Which Screen Mode They Prefer   */
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							/* Windowed Mode                    */
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Lionel Brits & NeHe's 3D World Tutorial",640,480,16,fullscreen))
	{
		return 0;									/* Quit If Window Was Not Created   */
	}


	while(!done)									/* Loop That Runs While done=FALSE  */
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	/* Is There A Message Waiting ?     */
		{
			if (msg.message==WM_QUIT)				/* Have We Received A Quit Message? */
			{
				done=TRUE;							/* If So done=TRUE                  */
			}
			else									/* If Not, Deal With Window Messages */
			{
				TranslateMessage(&msg);				/* Translate The Message            */
				DispatchMessage(&msg);				/* Dispatch The Message             */
			}
		}
		else										/* If There Are No Messages         */
		{
			/* Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()  */
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	/* Active ? Was There A Quit Received ? */
			{
				done=TRUE;							/* ESC or DrawGLScene Signalled A Quit  */
			}
			else									/* Not Time To Quit, Update Screen      */
			{
				SwapBuffers(hDC);					/* Swap Buffers (Double Buffering)      */
				if (keys['B'] && !bp)
				{
					bp=TRUE;
					blend=!blend;
					if (!blend)
					{
						glDisable(GL_BLEND);
						glEnable(GL_DEPTH_TEST);
					}
					else
					{
						glEnable(GL_BLEND);
						glDisable(GL_DEPTH_TEST);
					}
				}
				if (!keys['B'])
				{
					bp=FALSE;
				}

				if (keys['F'] && !fp)
				{
					fp=TRUE;
					filter+=1;
					if (filter>2)
					{
						filter=0;
					}
				}
				if (!keys['F'])
				{
					fp=FALSE;
				}

				if (keys[VK_PRIOR])
				{
					z-=0.02f;
				}

				if (keys[VK_NEXT])
				{
					z+=0.02f;
				}

				if (keys[VK_UP])
				{

					xpos -= (float)sin(heading*piover180) * 0.05f;
					zpos -= (float)cos(heading*piover180) * 0.05f;
					if (walkbiasangle >= 359.0f)
					{
						walkbiasangle = 0.0f;
					}
					else
					{
						walkbiasangle+= 10;
					}
					walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
				}

				if (keys[VK_DOWN])
				{
					xpos += (float)sin(heading*piover180) * 0.05f;
					zpos += (float)cos(heading*piover180) * 0.05f;
					if (walkbiasangle <= 1.0f)
					{
						walkbiasangle = 359.0f;
					}
					else
					{
						walkbiasangle-= 10;
					}
					walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
				}

				if (keys[VK_RIGHT])
				{
					heading -= 1.0f;
					yrot = heading;
				}

				if (keys[VK_LEFT])
				{
					heading += 1.0f;
					yrot = heading;
				}

				if (keys[VK_PRIOR])
				{
					lookupdown-= 1.0f;
				}

				if (keys[VK_NEXT])
				{
					lookupdown+= 1.0f;
				}

				if (keys[VK_F1])						/* Is F1 Being Pressed ?                */
				{
					keys[VK_F1]=FALSE;					/* If So Make Key FALSE                 */
					KillGLWindow();						/* Kill Our Current Window              */
					fullscreen=!fullscreen;				/* Toggle Fullscreen / Windowed Mode    */
					// Recreate Our OpenGL Window
					if (!CreateGLWindow("Lionel Brits & NeHe's 3D World Tutorial",640,480,16,fullscreen))
					{
						return 0;						/* Quit If Window Was Not Created       */
					}
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();										/* Kill The Window          */
	return (msg.wParam);								/* Exit The Program         */
}
