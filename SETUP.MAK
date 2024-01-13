.AUTODEPEND

#		*Translator Definitions*
CC = bcc +SETUP.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = C:\BORLANDC\LIB
INCLUDEPATH = C:\BORLANDC\INCLUDE;SRC


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
 src\screens\askpres.obj \
 src\screens\consel.obj \
 src\screens\control.obj \
 src\screens\idcard.obj \
 src\screens\idjoysel.obj \
 src\screens\idkeysel.obj \
 src\screens\idmain2.obj \
 src\screens\idmousel.obj \
 src\screens\irqerr.obj \
 src\screens\mcard.obj \
 src\screens\midiport.obj \
 src\screens\mousentr.obj \
 src\screens\mouspres.obj \
 src\screens\numdig.obj \
 src\screens\sbdma.obj \
 src\screens\sbirq.obj \
 src\screens\sbport.obj \
 src\screens\show.obj \
 src\screens\title.obj \
 config.obj \
 control.obj \
 main.obj \
 menu.obj \
 music.obj \
 prefapi.obj \
 scguess.obj \
 setup.obj \
 sfx.obj

#		*Explicit Rules*
setup.exe: setup.cfg $(EXE_dependencies)
  $(TLINK) /x/c/P-/L$(LIBPATH) @&&|
c0l.obj+
src\screens\askpres.obj+
src\screens\consel.obj+
src\screens\control.obj+
src\screens\idcard.obj+
src\screens\idjoysel.obj+
src\screens\idkeysel.obj+
src\screens\idmain2.obj+
src\screens\idmousel.obj+
src\screens\irqerr.obj+
src\screens\mcard.obj+
src\screens\midiport.obj+
src\screens\mousentr.obj+
src\screens\mouspres.obj+
src\screens\numdig.obj+
src\screens\sbdma.obj+
src\screens\sbirq.obj+
src\screens\sbport.obj+
src\screens\show.obj+
src\screens\title.obj+
config.obj+
control.obj+
main.obj+
menu.obj+
music.obj+
prefapi.obj+
scguess.obj+
setup.obj+
sfx.obj
setup
		# no map file
emu.lib+
mathl.lib+
cl.lib
|


#		*Individual File Dependencies*
config.obj: setup.cfg src\config.c 
	$(CC) -c src\config.c

control.obj: setup.cfg src\control.c 
	$(CC) -c src\control.c

main.obj: setup.cfg src\main.c 
	$(CC) -c src\main.c

menu.obj: setup.cfg src\menu.c 
	$(CC) -c src\menu.c

music.obj: setup.cfg src\music.c 
	$(CC) -c src\music.c

prefapi.obj: setup.cfg src\prefapi.c 
	$(CC) -c src\prefapi.c

scguess.obj: setup.cfg src\scguess.c 
	$(CC) -c src\scguess.c

setup.obj: setup.cfg src\setup.c 
	$(CC) -c src\setup.c

sfx.obj: setup.cfg src\sfx.c 
	$(CC) -c src\sfx.c

#		*Compiler Configuration File*
setup.cfg: setup.mak
  copy &&|
-ml
-v
-vi-
-wpro
-weas
-wpre
-I$(INCLUDEPATH)
-L$(LIBPATH)
| setup.cfg


