Display
=======

The display component augments the static initialization file with:

-  The configuration of each display.

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

.. table:: Display Static Initialization XML Tags Definition

   +---------------+---------------+---------------------------------------+
   | Tag           | Attributes    | Description                           |
   +===============+===============+=======================================+
   | ``display``   |               | The display element describes one     |
   |               |               | display.                              |
   +---------------+---------------+---------------------------------------+
   | ``name``      | The logical   |                                       |
   |               | name of the   |                                       |
   |               | display.      |                                       |
   +---------------+---------------+---------------------------------------+
   | ``priority``  | *Optional.*   |                                       |
   |               | An integer    |                                       |
   |               | value.        |                                       |
   |               | Defines the   |                                       |
   |               | internal      |                                       |
   |               | display       |                                       |
   |               | thread        |                                       |
   |               | priority.     |                                       |
   |               | Default value |                                       |
   |               | is 5.         |                                       |
   +---------------+---------------+---------------------------------------+
   | ``default``   | *Optional.*   |                                       |
   |               | ``true`` or   |                                       |
   |               | ``false``.    |                                       |
   |               | Defines this  |                                       |
   |               | display to be |                                       |
   |               | the default   |                                       |
   |               | display. By   |                                       |
   |               | default the   |                                       |
   |               | very first    |                                       |
   |               | display       |                                       |
   |               | described in  |                                       |
   |               | the XML file  |                                       |
   |               | is the        |                                       |
   |               | default       |                                       |
   |               | display.      |                                       |
   +---------------+---------------+---------------------------------------+
   | ``fonts``     |               | The list of system fonts. The system  |
   |               |               | fonts are available for all displays. |
   +---------------+---------------+---------------------------------------+
   | ``font``      |               | A system font.                        |
   +---------------+---------------+---------------------------------------+
   | ``file``      | The font file |                                       |
   |               | path. The     |                                       |
   |               | path may be   |                                       |
   |               | absolute or   |                                       |
   |               | relative to   |                                       |
   |               | the XML file. |                                       |
   +---------------+---------------+---------------------------------------+
   | ``range``     |               | A font generic range.                 |
   +---------------+---------------+---------------------------------------+
   | ``name``      | The generic   |                                       |
   |               | range name    |                                       |
   |               | (``LATIN``,   |                                       |
   |               | ``HAN``,      |                                       |
   |               | etc.)         |                                       |
   +---------------+---------------+---------------------------------------+
   | ``sections``  | *Optional.*   |                                       |
   |               | Defines one   |                                       |
   |               | or several    |                                       |
   |               | sub parts of  |                                       |
   |               | the generic   |                                       |
   |               | range.        |                                       |
   |               |               |                                       |
   |               | "1": add only |                                       |
   |               | part 1 of the |                                       |
   |               | range         |                                       |
   |               |               |                                       |
   |               | "1-5": add    |                                       |
   |               | parts 1 to 5  |                                       |
   |               |               |                                       |
   |               | "1,5": add    |                                       |
   |               | parts 1 and 5 |                                       |
   |               |               |                                       |
   |               | These         |                                       |
   |               | combinations  |                                       |
   |               | are allowed:  |                                       |
   |               |               |                                       |
   |               | "1,5,6-8" add |                                       |
   |               | parts 1, 5,   |                                       |
   |               | and 6 through |                                       |
   |               | 8             |                                       |
   |               |               |                                       |
   |               | By default,   |                                       |
   |               | all range     |                                       |
   |               | parts are     |                                       |
   |               | embedded.     |                                       |
   +---------------+---------------+---------------------------------------+
   | ``            |               | A font-specific range.                |
   | customrange`` |               |                                       |
   +---------------+---------------+---------------------------------------+
   | ``start``     | UTF16 value   |                                       |
   |               | of the very   |                                       |
   |               | first         |                                       |
   |               | character to  |                                       |
   |               | embed.        |                                       |
   +---------------+---------------+---------------------------------------+
   | ``end``       | UTF16 value   |                                       |
   |               | of the very   |                                       |
   |               | last          |                                       |
   |               | character to  |                                       |
   |               | embed.        |                                       |
   +---------------+---------------+---------------------------------------+
