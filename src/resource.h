
/*
*
*******************************************
*                                         *
*   Resource Header File                  *
*   Created by Thierry DECHAIZE           *
*   Date : 2013/11/29					  *
*******************************************
*
*/

/**          Comments manageable by Doxygen
*
* \file            resource.h
* \author          Created by Thierry Dechaize to verify paradigm : one source for multiple C Compilers
* \version         2.0.4.0
* \date            16 Octobre 2024
* \brief           Les d�finitions utilis�es par le programme et les ressources
* \details         Rien � dire, il faut lire.
*
*
*/

#ifndef HEADER_RESOURCE__INCLUDED
#define HEADER_RESOURCE__INCLUDED

#define IDC_MYICON                      2
#define IDR_MAINFRAME      				101
#define IDD_TEXTDIALOGSAMPLE_DIALOG     102
#define IDS_APP_TITLE                   103
#define IDD_ABOUTBOX                    103
#define IDM_ABOUT                       104
#define IDM_EXIT                        105
#define IDI_TEXTDIALOGSAMPLE            107
#define IDI_SMALL                       108
#define IDC_TEXTDIALOGSAMPLE            109
// #define IDR_MAINFRAME                   128
#define IDI_MYICON 						201
#define IDC_BUTTON1                     1000
#define IDC_BUTTON2                     1001
#define IDC_SIZE_SLIDER                 1002
#define IDC_SIZE_LABEL                  1003
#define IDC_INPUT_TEXT                  1005
#define IDC_FONT_LIST                   1006
#define IDC_BOLD                        1008
#define IDC_ITALIC                      1009
#define IDC_CHECK4                      1010
#define IDC_UNDERLINE                   1010
#define IDC_STATIC                      -1
#define IDC_DWRITE_TEXT                 -1

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NO_MFC                     1
#define _APS_NEXT_RESOURCE_VALUE        129
#define _APS_NEXT_COMMAND_VALUE         32771
#define _APS_NEXT_CONTROL_VALUE         1011
#define _APS_NEXT_SYMED_VALUE           110
#endif
#endif

// 		Define strings for VERSIONINFO

#define VER_FILEVERSION             2,0,4,0
#define VER_FILEVERSION_STR         "2.0.4.0\0"

#define VER_PRODUCTVERSION          2,0,4,0
#define VER_PRODUCTVERSION_STR      "2.0.4.0\0"

#if !defined(DEBUG) || !defined(_DEBUG)
#define VER_DEBUG                   0
#else
#define VER_DEBUG                   VS_FF_DEBUG
#endif

#define VER_COMPANYNAME_STR 		"NeHe Productions\0"
#define VER_FILEDESCRIPTION_STR 	"NeHe Lesson10 OpenGL\0"
#define VER_INTERNALNAME_STR 		"Lesson10\0"
#define VER_LEGALCOPYRIGHT_STR 		"No patent. For free use.\0"
#define VER_LEGALTRADEMARKS1_STR 	"Neon Helium Productions\0"
#define VER_LEGALTRADEMARKS2_STR 	"See usage rules on www -> nehe.gamedev.net\0"
#define VER_ORIGINALFILENAME_STR 	"Lesson10.exe\0"
// #define VER_PRODUCTNAME_STR 		"Lesson10 OpenGL : Texture mapping on cube in rotation.\0"
#define VER_DATE_BUILD 	            "Septembre 2020\0"
#define VER_COMMENTS	            "Paradigm : one source for multiple free C compilers\0"
#define VER_SUPPORT 	            "thierry.dechaize@gmail.com\0"
#define VER_USERS 	                "Anyone, unlimited.\0"

#endif   // HEADER_RESOURCE__INCLUDED


