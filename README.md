UE4-LeapMotionPlugin
====================

A plugin for exposing Leap Motion SDK to UE4 blueprint

Actually this features are done : 
-> get a controller, check if the controller is connected or not, check the focus of it & check if the Leap service is on
-> get any frame & check the validity of the frame
-> get a HandList for a frame
-> get the frontmost, leftmost or rightmost hand of a handlist
-> get a hand in a handlist thanks to hand ID
-> Check if the hand get is left or right
-> get the number of hand detected
-> check if HandList is empty or not
-> check if a hand is left or right hand
-> check if the hand is valid or not
-> get the palm position, normal and velocity
-> get the confidence level in the given hand pose
-> get the direction from palm to fingers
-> get the grabStrength

====================

How to install it
====================

You simply have to create a folder Plugins in your game directory and place the code with binaries,
and place the requires Binaries into the folder of your plateform into the folder Binaries of your game project
and if it haven't, just place the requires Binaries into the folder of executable of UE4 editor.

====================

Binaries
====================

Plugin precompile for Win64 is <a href="http://www.marc-wieser.fr/UE4Editor-LeapMotion.rar">here</a>
Requires Binaries are <a href="http://www.marc-wieser.fr/Requires_plugin_Leap_Motion_UE4.rar">here</a>

