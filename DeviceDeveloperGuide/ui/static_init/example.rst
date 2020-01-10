Example
=======

This common MicroUI initialization file initializes MicroUI with:

-  a display

-  a ``Command`` event generator

-  a ``Buttons`` event generator which targets *n* buttons (3 first
   buttons having extended features)

-  a ``Buttons`` event generator which targets the buttons of a joystick

-  a ``Pointer`` event generator which targets a touch panel

-  a ``DisplayFont`` whose path is relative to this file

::

   <microui>

       <display name="DISPLAY"/>
       
       <eventgenerators>
           <command name="COMMANDS"/>
           <buttons name="BUTTONS" extended="3"/>
           <buttons name="JOYSTICK" extended="5"/>
           <touch name="TOUCH" display="DISPLAY"/>
       </eventgenerators>
       
       <fonts>
           <font file="resources\fonts\myfont.ejf"/>
       </fonts>

   </microui>
