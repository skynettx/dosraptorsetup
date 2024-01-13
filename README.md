# DOS Raptor Setup
DOS version of the Raptor Call Of The Shadows setup program. This project is based on id Software's idsetup.

## Build
This project supports building with Borland C++ 3.1 under DOS.
You can use the project file `SETUP.PRJ` with bc or the makefile `SETUP.MAK` with make.
To build this project with the makefile type in the root of the repository:
```
make -f setup.mak
```
### Screens
Except for LDOG 1.14, all other tools are included in this repository.
The source code for ForAll is available [here](https://github.com/skynettx/forall) and for MakeOBJ [here](https://github.com/skynettx/makeobj).
The PUP files are created using LDOG 1.14, which as mentioned above is not included.
These files are then converted into the Object Module Format using ForAll and MakeOBJ and can then be linked directly into the EXE.
To convert the files use `make.bat` in the `SRC\SCREENS` folder.

## Licenses
DOS Raptor Setup is distributed under the GPL Version 2, see [LICENSE](https://github.com/skynettx/dosraptorsetup/blob/master/LICENSE) and this [email](https://github.com/skynettx/dosraptorsetup/blob/master/COPYING.Carmack).
ForAll is distributed under the GPL Version 2 or newer, see [LICENSE](https://github.com/skynettx/dosraptorsetup/blob/master/LICENSE).
The license for MakeOBJ can be viewed [here](https://github.com/skynettx/dosraptorsetup/blob/master/LICENSE.MakeOBJ).
