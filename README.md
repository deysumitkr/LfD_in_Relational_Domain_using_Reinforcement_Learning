## Dependencies
1. Python 2.7
1. [OpenCV](http://opencv.org/releases.html)
2. [ACE Datamining System](https://dtai.cs.kuleuven.be/ACE/)
3. Prolog ([SICStus](https://sicstus.sics.se/) (recommended) / [SWI-Prolog](http://www.swi-prolog.org/Download.html))
4. [Zenity](https://github.com/GNOME/zenity)
> To install zenity on Ubuntu
> `sudo apt-get install zenity`

## Installation
 Use `cmake-gui` or `ccmake` to set build options.
 
 ##### Required Options:
 * ACE_ILP_ROOT (Details in [ACE Manual](https://dtai.cs.kuleuven.be/ACE/doc/ACEuser-1.2.16.pdf))
 * PROLOG_EXECUTION_COMMAND (The command that runs interactive prolog shell. Usually its `prolog` for SICStus and `swipl` for SWI-Prolog)
