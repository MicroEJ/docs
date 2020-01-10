Inputs
======

The XML file used as input by the MicroUI Static Initialization Tool may
contain tags related to the Input component as described below.

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

.. table:: Event Generators Static Definition

   +------------------+------------+--------------------------------------+
   | Tag              | Attributes | Description                          |
   +==================+============+======================================+
   | ``e              |            | The list of event generators.        |
   | ventgenerators`` |            |                                      |
   +------------------+------------+--------------------------------------+
   | ``priority``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | An integer |                                      |
   |                  | value.     |                                      |
   |                  | Defines    |                                      |
   |                  | the        |                                      |
   |                  | priority   |                                      |
   |                  | of the     |                                      |
   |                  | MicroUI    |                                      |
   |                  | dispatch   |                                      |
   |                  | thread     |                                      |
   |                  | (also      |                                      |
   |                  | called     |                                      |
   |                  | Input      |                                      |
   |                  | Pump).     |                                      |
   |                  | Default    |                                      |
   |                  | value is   |                                      |
   |                  | 5.         |                                      |
   +------------------+------------+--------------------------------------+
   | ``               |            | Describes a generic event generator. |
   | eventgenerator`` |            | See also                             |
   |                  |            | `??? <#javaEventGenerators>`__.      |
   +------------------+------------+--------------------------------------+
   | ``name``         | The        |                                      |
   |                  | logical    |                                      |
   |                  | name.      |                                      |
   +------------------+------------+--------------------------------------+
   | ``class``        | The event  |                                      |
   |                  | generator  |                                      |
   |                  | class      |                                      |
   |                  | (must      |                                      |
   |                  | extend the |                                      |
   |                  | ``         |                                      |
   |                  | ej.microui |                                      |
   |                  | .event.gen |                                      |
   |                  | erator.Gen |                                      |
   |                  | ericEventG |                                      |
   |                  | enerator`` |                                      |
   |                  | class).    |                                      |
   |                  | This class |                                      |
   |                  | must be    |                                      |
   |                  | available  |                                      |
   |                  | in the     |                                      |
   |                  | MicroEJ    |                                      |
   |                  | a          |                                      |
   |                  | pplication |                                      |
   |                  | classpath. |                                      |
   +------------------+------------+--------------------------------------+
   | ``listener``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | Default    |                                      |
   |                  | listener's |                                      |
   |                  | logical    |                                      |
   |                  | name. Only |                                      |
   |                  | a display  |                                      |
   |                  | is a valid |                                      |
   |                  | listener.  |                                      |
   |                  | If no      |                                      |
   |                  | listener   |                                      |
   |                  | is         |                                      |
   |                  | specified  |                                      |
   |                  | the        |                                      |
   |                  | listener   |                                      |
   |                  | is the     |                                      |
   |                  | default    |                                      |
   |                  | display.   |                                      |
   +------------------+------------+--------------------------------------+
   | ``property``     |            | A generic event generator property.  |
   |                  |            | The generic event generator will     |
   |                  |            | receive this property at startup,    |
   |                  |            | via the method ``setProperty``.      |
   +------------------+------------+--------------------------------------+
   | ``name``         | The        |                                      |
   |                  | property   |                                      |
   |                  | key.       |                                      |
   +------------------+------------+--------------------------------------+
   | ``value``        | The        |                                      |
   |                  | property   |                                      |
   |                  | value.     |                                      |
   +------------------+------------+--------------------------------------+
   | ``command``      |            | The default event generator          |
   |                  |            | ``Command``.                         |
   +------------------+------------+--------------------------------------+
   | ``name``         | The        |                                      |
   |                  | logical    |                                      |
   |                  | name.      |                                      |
   +------------------+------------+--------------------------------------+
   | ``listener``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | Default    |                                      |
   |                  | listener's |                                      |
   |                  | logical    |                                      |
   |                  | name. Only |                                      |
   |                  | a display  |                                      |
   |                  | is a valid |                                      |
   |                  | listener.  |                                      |
   |                  | If no      |                                      |
   |                  | listener   |                                      |
   |                  | is         |                                      |
   |                  | specified, |                                      |
   |                  | then the   |                                      |
   |                  | listener   |                                      |
   |                  | is the     |                                      |
   |                  | default    |                                      |
   |                  | display.   |                                      |
   +------------------+------------+--------------------------------------+
   | ``buttons``      |            | The default event generator          |
   |                  |            | ``Buttons``.                         |
   +------------------+------------+--------------------------------------+
   | ``name``         | The        |                                      |
   |                  | logical    |                                      |
   |                  | name.      |                                      |
   +------------------+------------+--------------------------------------+
   | ``extended``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | An integer |                                      |
   |                  | value.     |                                      |
   |                  | Defines    |                                      |
   |                  | the number |                                      |
   |                  | of buttons |                                      |
   |                  | which      |                                      |
   |                  | support    |                                      |
   |                  | the        |                                      |
   |                  | MicroUI    |                                      |
   |                  | extended   |                                      |
   |                  | features   |                                      |
   |                  | (elapsed   |                                      |
   |                  | time,      |                                      |
   |                  | click and  |                                      |
   |                  | doub       |                                      |
   |                  | le-click). |                                      |
   +------------------+------------+--------------------------------------+
   | ``listener``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | Default    |                                      |
   |                  | listener's |                                      |
   |                  | logical    |                                      |
   |                  | name. Only |                                      |
   |                  | a display  |                                      |
   |                  | is a valid |                                      |
   |                  | listener.  |                                      |
   |                  | If no      |                                      |
   |                  | listener   |                                      |
   |                  | is         |                                      |
   |                  | specified, |                                      |
   |                  | then the   |                                      |
   |                  | l          |                                      |
   |                  | istener is |                                      |
   |                  | the        |                                      |
   |                  | default    |                                      |
   |                  | display.   |                                      |
   +------------------+------------+--------------------------------------+
   | ``pointer``      |            | The default event generator          |
   |                  |            | ``Pointer``.                         |
   +------------------+------------+--------------------------------------+
   | ``name``         | The        |                                      |
   |                  | logical    |                                      |
   |                  | name.      |                                      |
   +------------------+------------+--------------------------------------+
   | ``width``        | An integer |                                      |
   |                  | value.     |                                      |
   |                  | Defines    |                                      |
   |                  | the        |                                      |
   |                  | pointer    |                                      |
   |                  | area       |                                      |
   |                  | width.     |                                      |
   +------------------+------------+--------------------------------------+
   | ``height``       | An integer |                                      |
   |                  | value.     |                                      |
   |                  | Defines    |                                      |
   |                  | the        |                                      |
   |                  | pointer    |                                      |
   |                  | area       |                                      |
   |                  | height.    |                                      |
   +------------------+------------+--------------------------------------+
   | ``extended``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | An integer |                                      |
   |                  | value.     |                                      |
   |                  | Defines    |                                      |
   |                  | the number |                                      |
   |                  | of pointer |                                      |
   |                  | buttons    |                                      |
   |                  | (right     |                                      |
   |                  | click,     |                                      |
   |                  | left       |                                      |
   |                  | click,     |                                      |
   |                  | etc.)      |                                      |
   |                  | which      |                                      |
   |                  | support    |                                      |
   |                  | the        |                                      |
   |                  | MicroUI    |                                      |
   |                  | extended   |                                      |
   |                  | features   |                                      |
   |                  | (elapsed   |                                      |
   |                  | time,      |                                      |
   |                  | click and  |                                      |
   |                  | doub       |                                      |
   |                  | le-click). |                                      |
   +------------------+------------+--------------------------------------+
   | ``listener``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | Default    |                                      |
   |                  | listener's |                                      |
   |                  | logical    |                                      |
   |                  | name. Only |                                      |
   |                  | a display  |                                      |
   |                  | is a valid |                                      |
   |                  | listener.  |                                      |
   |                  | If no      |                                      |
   |                  | listener   |                                      |
   |                  | is         |                                      |
   |                  | specified, |                                      |
   |                  | then the   |                                      |
   |                  | l          |                                      |
   |                  | istener is |                                      |
   |                  | the        |                                      |
   |                  | default    |                                      |
   |                  | display.   |                                      |
   +------------------+------------+--------------------------------------+
   | ``touch``        |            | The default event generator          |
   |                  |            | ``Touch``.                           |
   +------------------+------------+--------------------------------------+
   | ``name``         | The        |                                      |
   |                  | logical    |                                      |
   |                  | name.      |                                      |
   +------------------+------------+--------------------------------------+
   | ``display``      | Logical    |                                      |
   |                  | name of    |                                      |
   |                  | the        |                                      |
   |                  | Display    |                                      |
   |                  | with which |                                      |
   |                  | the touch  |                                      |
   |                  | is         |                                      |
   |                  | a          |                                      |
   |                  | ssociated. |                                      |
   +------------------+------------+--------------------------------------+
   | ``listener``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | Default    |                                      |
   |                  | listener's |                                      |
   |                  | logical    |                                      |
   |                  | name. Only |                                      |
   |                  | a display  |                                      |
   |                  | is a valid |                                      |
   |                  | listener.  |                                      |
   |                  | If no      |                                      |
   |                  | listener   |                                      |
   |                  | is         |                                      |
   |                  | specified, |                                      |
   |                  | then the   |                                      |
   |                  | l          |                                      |
   |                  | istener is |                                      |
   |                  | the        |                                      |
   |                  | default    |                                      |
   |                  | display.   |                                      |
   +------------------+------------+--------------------------------------+
   | ``states``       |            | An event generator that manages a    |
   |                  |            | group of state machines. The state   |
   |                  |            | of a machine is changed by sending   |
   |                  |            | an event using                       |
   |                  |            | ``LLINPUT_sendStateEvent``.          |
   +------------------+------------+--------------------------------------+
   | ``name``         | The        |                                      |
   |                  | logical    |                                      |
   |                  | name.      |                                      |
   +------------------+------------+--------------------------------------+
   | ``numbers``      | The        |                                      |
   |                  | logical    |                                      |
   |                  | name of    |                                      |
   |                  | the array  |                                      |
   |                  | which      |                                      |
   |                  | defines    |                                      |
   |                  | the number |                                      |
   |                  | of state   |                                      |
   |                  | machines   |                                      |
   |                  | for this   |                                      |
   |                  | States     |                                      |
   |                  | generator, |                                      |
   |                  | and their  |                                      |
   |                  | range of   |                                      |
   |                  | state      |                                      |
   |                  | values.    |                                      |
   |                  | The IDs of |                                      |
   |                  | the state  |                                      |
   |                  | machines   |                                      |
   |                  | start at   |                                      |
   |                  | 0. The     |                                      |
   |                  | number of  |                                      |
   |                  | state      |                                      |
   |                  | machines   |                                      |
   |                  | managed by |                                      |
   |                  | the States |                                      |
   |                  | generator  |                                      |
   |                  | is equal   |                                      |
   |                  | to the     |                                      |
   |                  | size of    |                                      |
   |                  | the        |                                      |
   |                  | `          |                                      |
   |                  | `numbers`` |                                      |
   |                  | array, and |                                      |
   |                  | the value  |                                      |
   |                  | of each    |                                      |
   |                  | entry in   |                                      |
   |                  | the array  |                                      |
   |                  | is the     |                                      |
   |                  | number of  |                                      |
   |                  | different  |                                      |
   |                  | values     |                                      |
   |                  | supported  |                                      |
   |                  | for that   |                                      |
   |                  | state      |                                      |
   |                  | machine.   |                                      |
   |                  | State      |                                      |
   |                  | machine    |                                      |
   |                  | values for |                                      |
   |                  | state      |                                      |
   |                  | machine i  |                                      |
   |                  | can be in  |                                      |
   |                  | the range  |                                      |
   |                  | 0 to       |                                      |
   |                  | ``numbe    |                                      |
   |                  | rs[i]``-1. |                                      |
   +------------------+------------+--------------------------------------+
   | ``values``       | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | The        |                                      |
   |                  | logical    |                                      |
   |                  | name of    |                                      |
   |                  | the array  |                                      |
   |                  | which      |                                      |
   |                  | defines    |                                      |
   |                  | the        |                                      |
   |                  | initial    |                                      |
   |                  | state      |                                      |
   |                  | values of  |                                      |
   |                  | the state  |                                      |
   |                  | machines   |                                      |
   |                  | for this   |                                      |
   |                  | States     |                                      |
   |                  | generator. |                                      |
   |                  | The        |                                      |
   |                  | ``values`` |                                      |
   |                  | array must |                                      |
   |                  | be the     |                                      |
   |                  | same size  |                                      |
   |                  | as the     |                                      |
   |                  | `          |                                      |
   |                  | `numbers`` |                                      |
   |                  | array. If  |                                      |
   |                  | initial    |                                      |
   |                  | state      |                                      |
   |                  | values are |                                      |
   |                  | specified  |                                      |
   |                  | using a    |                                      |
   |                  | ``values`` |                                      |
   |                  | array,     |                                      |
   |                  | then the   |                                      |
   |                  | ``LLINP    |                                      |
   |                  | UT_IMPL_ge |                                      |
   |                  | tInitialSt |                                      |
   |                  | ateValue`` |                                      |
   |                  | function   |                                      |
   |                  | is not     |                                      |
   |                  | called;    |                                      |
   |                  | otherwise  |                                      |
   |                  | that       |                                      |
   |                  | function   |                                      |
   |                  | is used to |                                      |
   |                  | establish  |                                      |
   |                  | the        |                                      |
   |                  | initial    |                                      |
   |                  | va         |                                      |
   |                  | lues [1]_. |                                      |
   +------------------+------------+--------------------------------------+
   | ``listener``     | *          |                                      |
   |                  | Optional.* |                                      |
   |                  | Default    |                                      |
   |                  | listener's |                                      |
   |                  | logical    |                                      |
   |                  | name. Only |                                      |
   |                  | a display  |                                      |
   |                  | is a valid |                                      |
   |                  | listener.  |                                      |
   |                  | If no      |                                      |
   |                  | listener   |                                      |
   |                  | is         |                                      |
   |                  | specified, |                                      |
   |                  | then the   |                                      |
   |                  | listener   |                                      |
   |                  | is the     |                                      |
   |                  | default    |                                      |
   |                  | display.   |                                      |
   +------------------+------------+--------------------------------------+
   | ``array``        |            | An array of values.                  |
   +------------------+------------+--------------------------------------+
   | ``name``         | The        |                                      |
   |                  | logical    |                                      |
   |                  | name.      |                                      |
   +------------------+------------+--------------------------------------+
   | ``elem``         |            | A value.                             |
   +------------------+------------+--------------------------------------+
   | ``value``        | An integer |                                      |
   |                  | value.     |                                      |
   +------------------+------------+--------------------------------------+

.. [1]
   Exception: When using EMBJPF, where there is no equivalent to the
   ``LLINPUT_IMPL_getInitialStateValue`` function. If no ``values``
   array is provided, and the EMBJPF is being used, all state machines
   take 0 as their initial state value.
