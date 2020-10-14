![](/TTX-Config/Resources/Logo.png)

TTX-Monitor+
------------

***TTX-Monitor+*** is a loader for *Taito's Type X* arcade machines software.<br>
Originally developed by *Romhack*: *[ttx_monitor](https://github.com/zxmarcos/ttx_monitor)*

Some features were added/changed/removed:

- Added support for *AxisR* and *AxisZ*
- Added option *PovAsAxis*
- Corrected the *sensitivity* of the *deadzone*
- Added the standard *SavePatch* function
- Developed a new configuration user interface
- Removed the *Direct3D* wrapper
- Deactivated the *logging* engine

The biggest feature should be the implementation of a new *DirectInput* wrapper with support for *mahjong* games, namely *Psikyo's* ***Taisen Hot Gimmick 5***, and in the future, ***Taisen Hot Gimmick Mix Party***.

The *SavePatch* doesn't work properly with all games, as some like ***The King Of Fighters '98***, ***Gouketsuji Ichizoku Senzo Kuyou*** and ***Trouble Witches*** will store data but won't read it. A temporal solution would be patching the games accordingly.

Some games like ***Chaos Breaker*** and ***Homura*** might have speed or other graphical issues in moder systems. A use of an external wrapper like *[dgVoodoo](http://dege.freeweb.hu/dgVoodoo2/dgVoodoo2.html)* will likely solve this issues, while some other enhancements may be used as well.

The code has been cleaned up a lot and reorganized completely, with some parts rewritten, so should be easier to see what's going on.