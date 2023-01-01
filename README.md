# Genesis 8 to 2 Texture Conversion
<br>
This software converts DAZ 3D's Genesis 8 textures to Genesis 2 textures.<br>

### Overall:


After one does the installation instructions below, all that is needed is to supply a new Genesis 8 face texture then run the software to generate all Genesis 2 textures.<br>
<br>
## Prerequisites:


If using Windows, Windows Subsystem for Linux 2 (WSL2) is needed. This will allow Linux commands in Windows.<br>
<br>
How to install WSL2 in Windows:<br>
In powershell run "wsl --install"<br>
<br>
### Required libraries:

Libpng-dev [site](http://www.libpng.org/pub/png/libpng.html)<br>
Install by running in a Linux or WSL2 command prompt "sudo apt install libpng-dev".<br>
Note: if using Linux and your Linux distro does not have a libpng-dev version that can be installed with apt install (package manager), compiled versions can be downloaded under "Previous
binaries" in the site. E.g., for Ubuntu, go to [this page](http://packages.debian.org/search?keywords=libpng&suite=default&section=all&arch=any&searchon=names) and download the bullseye (stable) amd64 versions of libpng16-16, libpng-tools, and libpng-dev deb files. Install each deb with "sudo apt install ./deb_name.deb" in the order listed in the prior sentence. libpng-dev should then be installed.<br>
<br>
Png++ (e.g., version 0.2.9) [download](https://www.nongnu.org/pngpp/).<br>
Place these program files into a directory named "png++" in the base directory of this software.<br>
<br>
Imagemagick (if wanting to automatically convert to png images). Install with "sudo apt install imagemagick".<br>
<br>
### Required textures:

Genesis 8 textures (to be converted)<br>
Genesis 2 textures (for reference)<br>
These are not included with the software because their licensing may not allow that.<br>
<br>
### Installation Instructions:

How to obtain DAZ's genesis textures:<br>
<br>
One needs to first download Genesis 8 into DAZ 3D to have the textures availible.<br>
<br>
Once downloaded, an example location of Genesis 8 textures is: "C:\Daz 3D\Applications\Data\DAZ 3D\My DAZ 3D Library\Runtime\Textures\DAZ\Characters\Genesis8\FemaleBase".<br>
<br>
Alternatively, one can use textures that are created by DAZ 3D's face transfer plugin [plugin link](https://www.daz3d.com/face-transfer-unlimited).<br>
<br>
An example of where those textures may be located is: "C:\Daz 3D\Applications\Data\DAZ 3D\My DAZ 3D Library\Runtime\Textures\user_name\Face Transfer\model_name", where user_name is your username and model_name is your DAZ 3D model name.<br>
<br>
The Genesis 8 textures need to be copied into the folder: "input/gen8textures" in the base directory of this software.<br>
The face texture must be converted to a png file and named in the following way:<br>
g8fbasefacemapd_1001.png<br>
<br> 
The script conv_png.sh is included to perform the jpg file conversion. Place the script into any folder that has files that conversion is wanted to be done on. Run the script to convert all jpg files to png files. If running this script is wanted, imagemagick needs to be installed.<br>
<br>
Next, one needs to download Genesis 2 into DAZ 3D for those textures.<br>
<br>
Once downloaded, an example location of Genesis 2 textures is: "C:\Daz 3D\Applications\Data\DAZ 3D\My DAZ 3D Library\Runtime\Textures\DAZ\Characters\Genesis2\BaseFemale".<br>
<br>
The Genesis 2 textures need to be copied into the folder: "input/gen2textures" in the base directory of this software.<br>
<br>
The textures must be converted to png files and named in the following way:<br>
eyes: v5breeeyes7m.png<br>
face: v5breeheadm.png<br>
mouth: v5breeinmouthm.png<br>
limbs: v5breelimbsm.png<br>
torso: v5breetorsom.png<br>
<br>
The results of the texture conversion will be in the "output" folder.<br>
<br>
Overall, the directories should be set this way:<br>
```
/input/gen2textures/		# place all gen 2 textures here
/input/gen8textures/		# place all gen 8 textures here
/output/			# where new textures will be output
/png++/				# where png++ files should be placed
/src/				# where source code for project is stored
gen8to2conv			# program to run the software
```

### Running software:

For each run that new texture conversions are wanted, supply a Genesis 8 face texture which will be used for all Genesis 2 textures to be created.<br>
<br>
Run from the base directory of this software:<br>
./gen8to2conv<br>
The software will print the statement "completed" when it has successfully completed running.<br>
<br>
Note: this software was compiled on Ubuntu 21.10. If a different distro is used, e.g., WSL2, it may need to be recompiled to run successfully. See "compiling software" directions below for that.<br>
<br>
Some post-processing of the generated images in an image editor by the user may be wanted to customize them based on user preferences. This software aims to do most of the texture conversion work automatically, and allow the user to make any final touches wanted. A known issue is that some lines between face texture sections may not be blended correctly. A blur brush in an image editor (e.g., [GIMP](https://www.gimp.org)) can be used to fix the blending in the textures. Perhaps in the future the software can be programmed to do the blending automatically.<br>
<br>
### Development guide:

Compiling software:<br>
<br>
If wanting to do development work one needs G++ on Linux or an equivalent C++ compiler.<br>
Note: this software has only been tested to work in Linux and Windows with WSL2 so far.<br>
<br>
G++ can be installed in Linux or WSL2 with "sudo apt install build-essential".<br>
<br>
An automated rebuilding and running of the software can be done by running "rebuild.sh" from the base directory in a command prompt.<br>
<br>
Notes: this software uses somewhat of a bespoke approach to do the texture conversion. This involves selected image portion rescaling, shifting, etc. Also, the color conversion is based on sampling colors between textures. Results seem decent in tests. Anyone contributing improvements by development to the software is welcome.<br>
<br>
Running on Windows without WSL2:<br>
<br>
It is not known how to compile or run this software in Windows without WSL2 because the Libpng or Png++ libraries seem to have issue with this. Possibly Libpng with GnuWin32 could be used [link](https://gnuwin32.sourceforge.net/packages/libpng.htm). It is unclear if Png++ works on Windows without WSL2. Development is welcome to try to get the software working without WSL2, but perhaps will need recoding the software to not use Png++.<br>
<br>
If one is not using WSL2, one may need to specify the library path for Libpng with "-I <Libpng_folderpath>" when compiling.<br>