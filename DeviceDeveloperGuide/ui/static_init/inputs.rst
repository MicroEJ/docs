Event Generators Element
========================

The event generators component augments the initialization file with:

-  the configuration of the predefined MicroUI ``Event Generator``:
   ``Command``, ``Buttons``, ``States``, ``Pointer``, ``Touch``

-  the configuration of the generic MicroUI ``Event Generator``

::

   <eventgenerators>
       <!-- Generic Event Generators -->
       <eventgenerator name="GENERIC" class="foo.bar.Zork">
           <property name="PROP1" value="3"/>
           <property name="PROP2" value="aaa"/>
       </eventgenerator>

       <!-- Predefined Event Generators -->
       <command name="COMMANDS"/>
       <buttons name="BUTTONS" extended="3"/>
       <buttons name="JOYSTICK" extended="5"/>
       <pointer name="POINTER" width="1200" height="1200"/>
       <touch name="TOUCH" display="DISPLAY"/>
       <states name="STATES" numbers="NUMBERS" values="VALUES"/>

   </eventgenerators>

   <array name="NUMBERS">
       <elem value="3"/>
       <elem value="2"/>
       <elem value="5"/>
   </array>

   <array name="VALUES">
       <elem value="2"/>
       <elem value="0"/>
       <elem value="1"/>
   </array>
