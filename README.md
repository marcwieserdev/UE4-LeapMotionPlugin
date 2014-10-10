leap-ue4
====================

A plugin for exposing Leap Motion SDK to UE4 blueprint. Forked to have event driven architecture, however this first release still contains old the setup updated with compile fixes for UE4.4.

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

1. Create new or open a project. 
2. Browse to your project root (typically found at *Documents/Unreal Project/{Your Project Root}*)
3. Copy *Plugins* folder into your Project root.
4. Copy *Binaries* folder into your Project root.
5. Restart the Editor and open your project again.
6. Select Window->Plugins. Click on Installed and you should see a category called Input and a plugin called Leap Motion now available. It should be automatically enabled, if not, Select Enabled. The Editor will warn you to restart, click restart.
7. The plugin should be enabled and ready to use.

====================

How to use it
====================

When you create a class blueprint you have a component Leap motion, if you place it on your scene you will have access to all the function of the
controller, so you can get the frame and do what you want with features currently developed.<br/>
<br/>

All the Blueprint nodes keep the name of the function in the <a href="https://developer.leapmotion.com/">documentation of leapmotion</a><br/>
<br/>

====================

Credits
====================
Original Plugin by Marc Wieser.
Event-driven fork by Getnamo.