UE4-LeapMotionPlugin
====================

A plugin for exposing Leap Motion SDK to UE4 blueprint

Actually this features are done :<br/>
get all informations on :
<ul>
<li>Frame</li>
<li>HandList</li>
<li>Hand</li>
<li>FingerList</li>
<li>Finger</li>
<li>PointableList</li>
<li>Pointable</li>
<li>ToolList</li>
<li>Tool</li>
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
You can download a demo project with source code and SLN for easiest re compilation <a href="http://www.marc-wieser.fr/DemoLeapMotion.rar">here</a><br/>

====================

How to use it
====================

When you create a class blueprint you have a component Leap motion, if you place it on your scene you will have access to all the function of the
controller, so you can get the frame and do what you want with features currently developed.<br/>
<br/>
All the Blueprint nodes keep the name of the function in the <a href="https://developer.leapmotion.com/">documentation of leapmotion</a><br/>
<br/>
Don't hesitate to get me feedback by mail at <a href="mailto:contact@marc-wieser.fr">contact@marc-wieser.fr</a> or on the <a href="https://forums.unrealengine.com/showthread.php?6783-Plugin-Leap-Motion-exposing-to-blueprint-WIP">Epic Games forums</a>
