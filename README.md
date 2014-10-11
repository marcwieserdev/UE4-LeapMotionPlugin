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

How to use it - Blueprint - Event Driven
====================

1. Open desired blueprint where you want to receive the leap events.
2. Click on Blueprint Props and Scroll down in the details panel to Interfaces.
3. Add the interface called LeapEventInterface
4. Place BeginPlay event on your event graph, drag out from the execute node typing 'Leap', select Add LeapController.
5. (Optional, recommended) Drag from the return value, save this as a blueprint variable e.g. Leap.
6. Drag from the return value or your new Leap blueprint variable (get) and type 'Leap' to narrow results. Select Set Delegate.
7. To the input which says 'Select Asset' connect a reference to self (Right click on graph type 'Self' it will be the only node available).
8. (Optional) Drag from the return value or your Leap blueprint variable (get), type 'Opt' select the only node which is OptimizeForHMD. Select true for the boolean input (red input), this will optimize the leap for top-down use.
9. You're ready to go.

Now you can Right click anywhere on Event graph and type 'Leap Event' and you will see all the available events you can receive.

====================

How to use it - Blueprint - Polling
====================

When you create a class blueprint you can add a component called LeapController, if you place it on your scene you will have access to all the function of the
controller, so you can get the frame and do what you want with features currently developed.<br/>
<br/>

All the Blueprint nodes keep the name of the function in the <a href="https://developer.leapmotion.com/">documentation of leapmotion</a><br/>
<br/>

====================

Todo
====================
-Convenience Classes
-Wiki
-Better Documentation
-C++ how to use

====================

Credits
====================
Original Plugin by Marc Wieser.
Event-driven fork by Getnamo.