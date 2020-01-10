Display Element
===============

The display component augments the initialization file with:

-  The configuration of the display.

-  Fonts that are implicitly embedded within the application (also
   called system fonts). Applications can also embed their own fonts.

::

   <display name="DISPLAY"/>

   <fonts>
       <font file="resources\fonts\myfont.ejf">
           <range name="LATIN" sections="0-2"/>
           <customrange start="0x21" end="0x3f"/>
       </font>
       <font file="C:\data\myfont.ejf"/>
   </fonts>
