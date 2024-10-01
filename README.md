# NOT Subway Surfers:

The  goal  of  the  game  is  to  survive  for  as  long  as  you  can  without  dying  to  the  many  obstacles  
that  come  your  way.  
If  you  can  live  for  long  enough  you  get  thrown  into  a  boss  fight  against  Santa  where  you  must  
survive  his  3  different  modes  and  defeat  him  by  throwing  snowballs.  


## Controls:  
-  A  :  Will  move  the  player  to  the  lane  to  the  left  of  them.  
-  D  :  Will  move  the  player  to  the  lane  to  the  right  of  them.  
-  Space:  The  player  will  jump  
-  Shift:  The  player  will  shoot  a  snowball  
-  Right  Click  (Hold):  Will  move  the  player  forward  
-  Mouse:  (pressed)  
-  M1  swipe  left  -  Move  Right  
-  M1  swipe  right  -  Move  Left  


## Stage Generation:

  - Stage  Elements  were  created  in  Blender.  
-  Depending  on  the  stage  element  a  hit  box  was  added  on  to  obstacles  to  kill  the  player  
when  the  hit  boxes  collided.  
-  Stages  were  added  into  an  array  to  generate  a  valid  list  of  elements  that  can  be  placed.  
-  A  pseudo  random  list  of  numbers  will  generate  a  seed  that  will  then  determine  which  
stage  is  picked  out  of  the  array.  
-  Will  make  sure  that  the  same  stage  does  not  get  selected  too  many  times  in  a  row  to  
prevent  impossible  game  states  and  to  make  sure  that  I  have  diversity  in  my  stage  
generation  
-  Using  the  same  seed  that  is  used  to  generate  the  stages,  I  pick  a  number  between  75  
and  90  to  determine  how  many  stages  need  to  pass  before  the  boss  fight  is  generated.  

## Boss FSM:

  - Boss  scene  is  instantiated  in  my  generator.gd  and  added  to  the  scene  tree  

GDState:  Template  state  class  with  functions  to  override  
-  Enter  
-  Exit  
-  Transition  

GDStateMachine:  Controller  script  to  handle  all  class  transitions  and  storage

-  States  are  loaded  and  stored  on  start  
-  When  a  state  transitions  the  controller  will  call  the  appropriate  enter/exit  functions  of  the  
two  transitioning  states  

Boss  States  
-  Normal  
-  Default  state  for  the  boss  with  slowly  simple  attack  pattern  
-  Stagger  
-  Boss  can  take  damage  and  will  not  attack  
-  Angry  
-  When  low  HP,  the  boss  will  start  attacking  more  frequent,  faster,  and  with  more  
difficult  attack  patterns  

Boss  Extras  
- Floor  attacks  
-  Each  attack  is  callable  using  “_on_start”  and  “_on_reset”  
Weakpoints  
-  Boss  has  6  set  weakpoints  (square  meshes)  that  are  randomly  activated  
-  Hitting  a  weakpoint  will  stagger  the  boss  
Death  Particle  Effects  
-  One  shot  on  death  
Swipe  movement  
-  When  player  has  “swipe”  property  enabled  they  can  use  swipes  to  move  left/right/jump  
Menu  
-  Starting  scene  of  the  game  with  directions/join  buttons  
-  On  load,  will  delete  every  other  scene  that  may  be  in  the  scene  tree

Credit: All code and stage pieces were made by me in C#, Godot, and Blener. Santa photo from free license site. 