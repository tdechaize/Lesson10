 /*************************************************************************
 *  Project : $logger
 *  Function : Utility program : add trace in text file, only in mode Debug
 **************************************************************************
 *  $Author: Thierry DECHAIZE
 *  $Name:  thierry.dechaize@gmail.com
 ***************************************************************
 *  Find this extract after navigate on Internet
 *  No Copyright : public domain
 *  Adapted because my needs are specifics.
 ***************************************************************/

//logger.c

/**         Comments manageable by Doxygen
*
*  Modified by Thierry DECHAIZE
*
*  Date : 2024/10/20
*
* \file            logger.c
* \author          Thierry Dechaize
* \version         2.0.1.0
* \date            5 mars 2023
* \brief           Ajout de fonction de "logging" (traces dans un fichier texte log.txt) uniquement en mode Debug et avec des niveaux de tracing définis dans une varaiable d'environnement (LEVEL)
* \details         L'utilisation est très simple : #if define(DEBUG)
* \details                                              if ((strcmp(level_debug,"BASE") == 0) || (strcmp(level_debug,"FULL") == 0)) [  || (strcmp(level_debug,"OPENGL") == 0))]
* \details                                                      log_print( __FILE__, __LINE__, texte approprié);
* \details                                         #endif
* \details          Warning : la variable LEVEL doit être définie au niveau "user" et non au niveau "system" sous Windows.
*
*
*/

/*           Discussion about PATH separator and directory separator beetween Linux/Unix and Windows into Libc      */

/* path handling portability macros */
#ifndef DIR_SEPARATOR
# define DIR_SEPARATOR '/'
# define PATH_SEPARATOR ':'
#endif

#if defined (_WIN32) || defined (__MSDOS__) || defined (__DJGPP__) || \
  defined (__OS2__)
# define HAVE_DOS_BASED_FILE_SYSTEM
# define FOPEN_WB "wb"
# ifndef DIR_SEPARATOR_2
#  define DIR_SEPARATOR_2 '\\'
# endif
# ifndef PATH_SEPARATOR_2
#  define PATH_SEPARATOR_2 ';'
# endif
#endif

#ifndef DIR_SEPARATOR_2
# define IS_DIR_SEPARATOR(ch) ((ch) == DIR_SEPARATOR)
#else /* DIR_SEPARATOR_2 */
# define IS_DIR_SEPARATOR(ch) \
	(((ch) == DIR_SEPARATOR) || ((ch) == DIR_SEPARATOR_2))
#endif /* DIR_SEPARATOR_2 */

#ifndef PATH_SEPARATOR_2
# define IS_PATH_SEPARATOR(ch) ((ch) == PATH_SEPARATOR)
#else /* PATH_SEPARATOR_2 */
# define IS_PATH_SEPARATOR(ch) ((ch) == PATH_SEPARATOR_2)
#endif /* PATH_SEPARATOR_2 */

/*           End discussion about PATH separator and directory separator beetween Linux/Unix and Windows           */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#if defined (_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#endif
#include "logger.h"

FILE *ft ;
static int SESSION_TRACKER; //Keeps track of session
static char filedir[MAX_PATH]; //Keeps track of full path of log file

char* print_time()
{
    int size = 0;
    time_t now;
    char *buf,timestr[37];
    struct tm * tm;
          /* Utilise tm_year, tm_mday, tm_month, tm_hour, tm_min, tm_sec ou strftime: */
    char date[64];

    now = time(NULL); /* get current calendar time */
    tm = localtime(&now);
    strftime(timestr, sizeof timestr, "%A, %d %B %Y, %H:%M:%S ", tm);
    timestr[strlen(timestr) - 1] = 0;  //Getting rid of \n

    size = strlen(timestr)+ 1 + 2; //Additional +2 for square braces
    buf = (char*)malloc(size);

    memset(buf, 0x0, size);
#if defined(__SC__) || defined(__DMC__)
    _snprintf(buf,size,"[%s]", timestr);
#else
    snprintf(buf,size,"[%s]", timestr);
#endif
    return buf;
}
void log_print(char* filename, int line, char *fmt,...)
{
    va_list         list;
    char            *p, *r;
    int             e,i,len = MAX_PATH;
    char            pBuf[MAX_PATH] = "";
    char *          pch;
#if defined(_WIN32) || defined(__CYGWIN__)
    int             bytes = GetModuleFileName(NULL, pBuf, len);
    char            dir_ch = '\\';
#elif defined(__linux__) || defined(__UNIX__)
    int             bytes = readlink("/proc/self/exe", pBuf, len)
    char            dir_ch = '/';
#endif

    if (SESSION_TRACKER == 0) {

      pch=strchr(pBuf,dir_ch);
      while (pch!=NULL)
        {
        i = pch-pBuf+1;
        pch=strchr(pch+1,dir_ch);
        }

      strncpy(filedir, pBuf, i);
#if defined(_WIN32) || defined(__CYGWIN__)
      filedir[i] = '\0' ;
#endif
      strcat(filedir,"log.txt");
#ifdef DEBUG
      /* printf(" Full Path of log : %s\n",filedir);  */
#endif        /*DEBUG */
    }

    if (SESSION_TRACKER > 0) {
      ft = fopen (filedir,"a+");
    }
    else {
      ft = fopen (filedir,"w");
    }

    fprintf(ft,"%s ",print_time());
    fprintf(ft,"[%s ,line: %d] ",filename,line);
    va_start( list, fmt );

    for ( p = fmt ; *p ; ++p )
    {
        if ( *p != '%' )//If simple string
        {
            fputc( *p,ft );
        }
        else
        {
            switch ( *++p )
            {
                /* string */
            case 's':
            {
                r = va_arg( list, char * );

                fprintf(ft,"%s", r);
                continue;
            }

            /* integer */
            case 'd':
            {
                e = va_arg( list, int );

                fprintf(ft,"%d", e);
                continue;
            }

            default:
                fputc( *p, ft );
            }
        }
    }
    va_end( list );
    fputc( '\n', ft );
    SESSION_TRACKER++;
    fclose(ft);
}

