# Coscoroba
#### A 2-player Alt-Control game in which players have to crank a pipe and hit a foot-pedal each, to control the up-down and side-to-side motion and firing, for an all powerful Anti-Aircraft gun setup on a spaceship

Read the full article here: https://naiduvishal13.wixsite.com/portfolio/project-03 </br></br>
![Gun Master](Screencapture_GunMaster.gif)


</br>

## The Magic Part 1 - The Ship
### A. Base Character (The Spline Rider)
1. <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/ACosco/Cosco_Base_Character.h">Header</a> / <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/ACosco/Cosco_Base_Character.cpp">C++</a>
2. It's the lowest layer of the <b>PlayerCharacter</b> hierarchy
3. Controls how the ships ride SplineActors
4. Used some real cool <b>interpolation</b> to make the ship
    * <b>Lerp</b> to the next spline point instead of teleporting, to make the movement feel super smooth
    * <b>Lean</b> like a bike upon turning
  
  

### B. Camera Controller Subclass
1. <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/ACosco/Cosco_Camera_Character.h">Header</a> / <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/ACosco/Cosco_Camera_Character.cpp">C++</a>
2. Implemented a 2-layer buffer system to <b>mitigate the Input Irregularities</b> from the Alt-Ctrl
3. Input X/Y => Current Yaw/Pitch Rates (which has it's own Rise/Fall Rate)



### C. Weapon Controller Subclass
1. <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/ACosco/Cosco_Weapons_Character.h">Header</a> / <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/ACosco/Cosco_Weapons_Character.cpp">C++</a>
2. Implemented a <b>Generalized Weapon Firing System</b> to which you can tag as many weapons as you want attached to a ship, each with its own firing properties
3. Originally created with a star wars destroyer in mind, with numerous guns attached to one body
</br>







## Part 2 - Gun Setup
### A. Base Projectile
1. <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/Projectiles/BaseProjectile.h">Header</a> / <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/Projectiles/BaseProjectile.cpp">C++</a>
2. Created a base layer

### B. Airburst Subclass
1. <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/Projectiles/AirburstProjectile.h">Header</a> / <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/Projectiles/AirburstProjectile.cpp">C++</a>
2. Implemented a <b>delayed explosion trigger</b> mechanism on the airburst
3. Wrote the radial damage calculator
</br></br>![Airburst Gun](Screencapture_Airburst.gif)</br>


### C. Gatling Subclass
1. <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/Projectiles/GatlingProjectile.h">Header</a> / <a href="https://github.com/Vieper1/coscoroba/blob/master/Bofor/Source/Bofor/Projectiles/GatlingProjectile.cpp">C++</a>
2. Wrote an <a href="">AnimBP</a> to apply <b>bone rotation</b> to the gatling gun
3. Weapon logic to only start firing over Threshold RPM | Rise/fall of bone rotation upon trigger | Overheat logic & dynamic material control
</br></br>![Gatling Gun](Screencapture_Gatling.gif)</br></br>





## Alt Control In Action
![Alt Control](AltControl.gif)</br>
This video shows the first prototype of the Alt-Controller as a teammate and I try to shoot down a plane on the far screen
