UE4-LeapMotionPlugin
====================

A plugin for exposing Leap Motion SDK to UE4 blueprint

Actually this features are done :
<ul>
<li>get a controller, check if the controller is connected or not, check the focus of it & check if the Leap service is on</li>
<li>get any frame & check the validity of the frame</li>
<li>get a HandList for a frame</li>
<li>get the frontmost, leftmost or rightmost hand of a handlist</li>
<li>get a hand in a handlist thanks to hand ID</li>
<li>Check if the hand get is left or right</li>
<li>get the number of hand detected</li>
<li>check if HandList is empty or not</li>
<li>check if a hand is left or right hand</li>
<li>check if the hand is valid or not</li>
<li>get the palm position, normal and velocity</li>
<li>get the confidence level in the given hand pose</li>
<li>get the direction from palm to fingers</li>
<li>get the grabStrength</li>
</ul>
====================

How to install it
====================

You simply have to create a folder Plugins in your game directory and place the code with binaries,<br/>
and place the requires Binaries into the folder of your plateform into the folder Binaries of your game project<br/>
and if it haven't, just place the requires Binaries into the folder of executable of UE4 editor.<br/>

====================

Binaries
====================

Plugin precompile for Win64 is <a href="http://www.marc-wieser.fr/UE4Editor-LeapMotion.rar">here</a><br/>
Requires Binaries are <a href="http://www.marc-wieser.fr/Requires_plugin_Leap_Motion_UE4.rar">here</a><br/>

