leap-ue4
====================

An event-driven [Leap Motion](http://www.leapmotion.com) plugin for the Unreal Engine 4.

Main use is by subscribing to events within your blueprint, but it also supports polling the LeapController for past 60 frames. You can extend functionality to any blueprint through adding the LeapInterfaceEvent interface then adding the LeapController component to that blueprint and setting delegate to self. This same architecture is available to C++ if you prefer, which also supports both event-driven and polling style use.

See [unreal thread](https://forums.unrealengine.com/showthread.php?49107-Plugin-Leap-Motion-Event-Driven) for version downloads and development updates.

##How to install it##


1. Create new or open a project. 
2. Browse to your project root (typically found at *Documents/Unreal Project/{Your Project Root}*)
3. Copy *Plugins* folder into your Project root.
4. Copy *Binaries* folder into your Project root.
5. Restart the Editor and open your project again.
6. Select Window->Plugins. Click on Installed and you should see a category called Input and a plugin called Leap Motion now available. It should be automatically enabled, if not, Select Enabled. The Editor will warn you to restart, click restart.
7. The plugin should be enabled and ready to use.

##Leap API Reference##

All the Blueprint nodes and functions keep the same name as specified in the <a href="https://developer.leapmotion.com/documentation/skeletal/cpp/api/Leap.Controller.html">documentation of leapmotion</a>, refer to this documentation for help with the API. Events are custom named, but follow action oriented naming. Type 'Leap Event' in your blueprint event graph to see all possible events after adding the LeapEventInterface to your blueprint interfaces.

###Blueprint API Examples###

Not an exhaustive list, but common use list. See the leap motion documentation for full list.

####Events####

<img src="http://i.imgur.com/XI3WmIM.png">

####Frame Functions####

<img src="http://i.imgur.com/Ioe19p0.png">

####Hand Functions and Properties####

<img src="http://i.imgur.com/o340HWj.png">

####Arm Functions and Properties####

<img src="http://i.imgur.com/ymlIeWt.png">

####Finger Functions and Properties####

<img src="http://i.imgur.com/MLblo0F.png">

####Pointable Functions and Properties####

<img src="http://i.imgur.com/NRpgG7z.png">

<br/>
<br/>

##How to use it - Blueprint - Event Driven##

<ol>
<li>Open desired blueprint where you want to receive the leap events.</li>
<li>Click on Blueprint Props and Scroll down in the details panel to Interfaces. </li>

<img src="http://i.imgur.com/s790gBs.png">

<li>Add the interface called LeapEventInterface</li>
<li>Place BeginPlay event on your event graph, drag out from the execute node typing 'Leap', select Add LeapController.</li>
<img src="http://i.imgur.com/y5caGWf.png">
<li>(Optional, recommended) Drag from the return value, save this as a blueprint variable e.g. Leap.
<li>(Optional) Drag from the return value or your Leap blueprint variable (get), type 'Opt' select the only node which is OptimizeForHMD. Select true for the boolean input (red input), this will optimize the leap for top-down use. Keep auto rotate and auto shift if you want the plugin to automatically shift the leap positions to account for HMD movement.
<li>You're ready to go.

</ol>

Now you can Right click anywhere on Event graph and type 'Leap Event' and you will see all the available events you can receive.

###Example 'Debug Hand' graph###
<img src="http://i.imgur.com/VzgR3xC.png">

with

<img src="http://i.imgur.com/aEEuZSI.png">

###Result###
<img src="http://i.imgur.com/URnaAHe.png">


###Gestures###
Require enabling before receiving events, below is an example of how to get the Circle gesture to emit and how to filter it.

<img src="http://i.imgur.com/czSJ1sg.png">

##How to use it - Blueprint - Polling##

When you create a class blueprint you can add a component called LeapController, this contains all the functionality that the LeapController has specified in their API. From the controller you can get the frame and do what you want with features currently available.<br/>
<br/>
Available blueprint classes branching from LeapController:
<ul>
<li>Frame</li>
<li>HandList</li>
<li>Hand</li>
<li>Arm</li>
<li>FingerList</li>
<li>Finger</li>
<li>PointableList</li>
<li>Pointable</li>
<li>Gesture</li>
<li>GestureList</li>
<li>Image - Preliminary Support</li> 
<li>ImageList</li> 
<li>InteractionBox</li>
<li>ToolList</li>
<li>Tool</li>
</ul>

##Shipping/Packaged Builds##
<ol>
<li> Projects require code, if you are using blueprint only add an empty class and compile your project module.</li>
<li> Add the following line to your DefaultEngine.ini </li>

<i>EnabledPlugins=LeapMotion</i>

under <i>[Plugins]</i>, create this category if missing.

<li> Package your content</li>
<li> In your packaged directory drag the <i>Binaries</i> folder from this plugin into your packaged project folder. E.g. if I have a packaged folder called <i>LeapPluginTest</i>
find <i>WindowsNoEditor/LeapPluginTest</i>, this is your packaged project root. Add the binaries folder there.</li>
</ol>

##Todo##

- Convenience Classes and Input mapping for casual support
- Wiki
- C++ how to

##Contact##
Post issues to this github or [the unreal thread](https://forums.unrealengine.com/showthread.php?49107-Plugin-Leap-Motion-Event-Driven).

##Credits##
Event-driven fork by Getnamo.

[Original Plugin](https://github.com/wieser-m/UE4-LeapMotionPlugin) by Marc Wieser.
