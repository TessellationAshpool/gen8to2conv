# gen8to2conv
<br>
This software converts DAZ 3D's Genesis 8 textures to Genesis 2 textures.<br>
<br>
Overall:<br>
<br>
After one does the installation instructions below, all that is needed is to supply a new Genesis 8 face texture then run the software to generate all Genesis 2 textures.<br>
<br>
Prerequisites:<br>
<br>
G++ (Linux c++ compiler) or Windows, etc., equivalent.<br>
<br>
Png++ (e.g., version 0.2.9) [download](https://www.nongnu.org/pngpp/).<br>
Place these program files into a "png++" directory.<br>
<br>
Genesis 8 textures (to be converted)<br>
<br>
Genesis 2 textures (for reference)<br>
<br>
Installation Instructions:<br>
<br>
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
Running software:<br>
<br>
From the base directory run "rebuild.sh" from a command prompt. The software will print "completed" when done.<br>
<br>
For each run that new texture conversions are wanted, only the Genesis 8 face texture needs to be updated for all Genesis 2 textures to be recreated.<br>
<br>
Notes: this software uses somewhat of a bespoke approach to do the texture conversion. This involves selected image portion rescaling, shifting, etc. Also, the color conversion is based on sampling colors between textures. Results seem decent in tests. Anyone contributing improvements to the software is welcome.<br>
<br>
Some post-processing of the generated images in an image editor by the user may be wanted to customize them based on user preferences. This software aims to do most of the texture conversion work automatically, and allow the user to make any final touches wanted.<br>
<br>
This software has only been tested in Linux currently but should work in Windows and Apple OSes.<br>