# Lesson10
Lesson10 OpenGL (from NeHe)

Vous trouverez au niveau du sommaire ci-dessous, beaucoup d'explications sur cette application, encore un exemple d'usage d'OpenGL (en provenance du site NeHe).

## Table of contents

- [Introduction](<Introduction.md>)
  - [Accueil](<Accueil.md>)
  - [Quoi de neuf](<Quoideneuf.md>)
- [Comment démarrer une génération ?](<Commentdemarrerunegeneration.md>)
  - [Exigences du système](<Exigencesdusysteme.md>)
  - [Lancement d'une génération CB ou CMAKE](<LancementdunegenerationCBouCMAKE.md>)

## OpenGL Tutorial #10.

Project Name: Lionel Brits and Jeff Molofee's OpenGL Tutorial

Project Description: 3D World Tutorial

Authors Name: Lionel Brits and Jeff Molofee (aka NeHe)

Authors Web Site: nehe.gamedev.net

COPYRIGHT AND DISCLAIMER: (c)2000 Jeff Molofee

	If you plan to put this program on your web page or a cdrom of
	any sort, let me know via email, I'm curious to see where
	it ends up :)

        If you use the code for your own projects please give me credit,
        or mention my web site somewhere in your program or it's docs.

 Modified smoothly by Thierry DECHAIZE

 Paradigm : obtain one source (only one !) compatible for multiple free C Compilers (many GCC compilers included in MinGW, Mingw32, Mingw64, MSYS2, CYGWIN64,
	TDM, and another Visual C/C++ included in Visual Studio + kits Windows, LCC, WATCOM, DMC, Borland, OneAPI Intel compiler, many CLANG compilers, etc..)
    and provide for all users an development environment on Windows 11 64 bits the great Code::Blocks IDE (improved version "nightly build" 23.06),
    and don't use glaux.lib or glaux.dll (old and buggy library).

	a) Mingw 32 bits, version officielle gcc 9.2.0 (very old !) : downloadable on http://sourceforge.net/projects/mingw/ (official)
	b) Mingw 64 bits included in new IDE Red Panda Cpp varsion 3.1, version gcc 12.2.0 : donwloadable on https://sourceforge.net/projects/redpanda-cpp/files/
	c) Mingw 64 bits included in package Code::Blocks (version 20.03 with mingw), downloadable on http://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/
           but improved with most recent version of MinGW64 + gcc (version gcc 13.1.0) with "nightly build" dated of 4 june 2023 downloadable on :
                      https://sourceforge.net/projects/codeblocks/files/Binaries/Nightlies/2023/CB_20230604_rev13311_win64-setup-MinGW.exe
	d) Mingw 32 and 64 bits packagés, version gcc 14.2.0 : downloadable on  https://winlibs.com/ (and CLANG included in, 32 and 64 bits), two kits :
			- winlibs-i686-posix-dwarf-gcc-14.2.0-llvm-19.1.1-mingw-w64ucrt-12.0.0-r2.7z (32 bits)
			- winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.1-mingw-w64ucrt-12.0.0-r2.7z (64 bits)
	e) Cygwin64 with three compilers, "native" GCC 64 bits and GCC in MinGW32 + MinGW64 bit, version gcc 12.4.0 : downloadable on http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
	f) TDM GCC, 32 and 64 bit, version 10.3.0 : downloadable on http://sourceforge.net/projects/TDM-GCC
	g) MSYS2 environment MINGW32 and MINGW64, 32 and 64 bit, version de 2024 (msys2-x86_64-20240727.exe), version gcc 14.2.0 : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20240727.exe
	h) Visual Studio 2022, 32 and 64 bit, community edition for free : downloadable on https://visualstudio.microsoft.com/fr/vs/community/
	i) Borland C/C++ 32 bit, version 5.5.1 : downloadable on https://developerinsider.co/download-and-install-borland-c-compiler-on-windows-10/
	j) Digital Mars Compiler C 32 bit, installation package version 8.57 : downloadable on http://www.digitalmars.com (the more old compiler, the more bugged, dead branch !)
	k) OpenWatcom 32 and 64 bit, version 2.0 (frequently rebuild) : downloadable on https://github.com/open-watcom/open-watcom-v2/releases/tag/Current-build
	l) Lcc and Lcc64, 32 and 64 bit : downloadable http://www.cs.virginia.edu/~lcc-win32/  (not really free !) 
	m) PELLES C, 32 and 64 bit, version 12.0 : downloadable on http://www.smorgasbordet.com/pellesc/
	o) CLANG 32 and 64 bit included in version WinLibs, leaned at environments MINGW64 et MINGW32, version 19.1.1 (version gcc 14.2.0) : downloadable on https://winlibs.com/
	p) CLANG 32 and 64 bit leaned at environments Visual Studio 2022 (+ kits Microsoft), version 19.1.1 : downloadable on https://releases.llvm.org/download.html
	q) CLANG 32 and 64 bit included in version MSYS2, leaned at environments MINGW64 et MINGW32, version 18.1.8 (version gcc 14.2.0) : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
	r) CLANG 32 bit included in version CYGWIN64, leaned at environments MINGW64 et MINGW32, version 8.0.0, very old (version gcc 12.4.0) : downloadable http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
	s) OneAPI Intel C/C++ compiler 32 and 64 bit, version 2024.2.1 downloadable on site https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html
	
  Add resource file and resource header for restitute version + icon OpenGL.ico for fun because versionning is important, same for freeware :-)

  62 generations with "All build" target into IDE Code::Blocks, or with CMAKE (and "make" tools with compilers don't supported with CMAKE), or,
  finally, with "command files" (versions 32 or 64 bits, "Debug" or "Release"), just "for fun" or "academic demonstration" of these tools.  !
