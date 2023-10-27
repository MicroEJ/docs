.. _tutorials_software_robot:

How to Test a GUI Application with a (Software) Robot
=====================================================

This document presents how to test a GUI application with a software robot for robotic process automation (RPA).

Robot tests and traditional unit tests are different but both are useful.
Traditional unit tests validate the systems through calls to the API (internal or external). Robot tests validate the systems by mimicking the human user behavior directly in the GUI.
The robot implementation proposed here targets the following errors detection:

* OutOfMemory
* StackOverflow
* MEJ32 and platform libraries error
* Widget sequence validation

The following document covers:

* Recording human touch events on the simulator or on the embedded platform
* Running recorded events on the simulator or on the embedded platform

The following document does not cover:

* The display rendering validation (this can be done using the `Test Automation <https://github.com/MicroEJ/Tool-UITestAutomation>`_ Tool)
* Integration of the robot into an automatic JUnit test suite

We will now present the basic architecture and code required to create and to run a robot within a MicroEJ application on the simulator and embedded platform.

In the following sections, we assume the MicroEJ VEE Port has a display interface and a touch controller.
 
Overview
--------

The robot creation process is twofold. First, we have to record and store the human user events.
Second, we have to play them back with the robot.

Record the Scenario
-------------------

The first step is to record the human user events.

Here is the code of the ``EventRecorder`` class that should be added to our application's project:

.. code-block:: java

      import ej.annotation.Nullable;
      import ej.microui.event.Event;
      import ej.microui.event.generator.Buttons;
      import ej.microui.event.generator.Pointer;

      /**
      * Records events.
      */
      public class EventRecorder {

        private long lastEventTime;

        /**
        * Creates an event recorder.
        */
        public EventRecorder() {
          this.lastEventTime = -1;
        }

        /**
        * Records an event.
        *
        * @param event
        *            the event to record.
        */
        public void recordEvent(int event) {
          String command = getEventCommand(event);
          if (command != null) {
            long currentTime = System.currentTimeMillis();
            if (this.lastEventTime == -1) {
              this.lastEventTime = currentTime;
            }

            long delta = currentTime - this.lastEventTime;
            if (delta > 0) {
              System.out.println(getPauseCommand(delta));
            }

            System.out.println(command);

            this.lastEventTime = currentTime;
          }
        }

        @SuppressWarnings("nls")
        private static @Nullable String getEventCommand(int event) {
          if (Event.getType(event) == Pointer.EVENT_TYPE) {
            Pointer pointer = (Pointer) Event.getGenerator(event);
            switch (Pointer.getAction(event)) {
            case Pointer.PRESSED:
              return "robot.press(" + pointer.getX() + ", " + pointer.getY() + ");";
            case Pointer.MOVED:
            case Pointer.DRAGGED:
              return "robot.move(" + pointer.getX() + ", " + pointer.getY() + ");";
            case Buttons.RELEASED:
              return "robot.release(" + pointer.getX() + ", " + pointer.getY() + ");";
            default:
              return null;
            }
          } else if (Event.getType(event) == Buttons.EVENT_TYPE) {
            if (Buttons.getAction(event) == Buttons.RELEASED) {
              return "robot.button();";
            } else {
              return null;
            }
          } else {
            return null;
          }
        }

        @SuppressWarnings("nls")
        private static @Nullable String getPauseCommand(long delay) {
          return "robot.pause(" + delay + ");";
        }
      }

This code records all pressed, moved, dragged and released events as well as the time between each event (we want to play our robot at the same speed as the human). ``EventRecorder`` outputs the commands on the standard output. More on this a bit later.

Set Up the Event Recorder
~~~~~~~~~~~~~~~~~~~~~~~~~

The events have to be recorded from the application's desktop's ``EventDispatcher``. Here is how to override it:

.. code-block:: java

      final EventRecorder eventRecorder = new EventRecorder();

      Desktop desktop = new Desktop() {

        @Override
        protected EventDispatcher createEventDispatcher() {
          return new PointerEventDispatcher(this) {

            @Override
            public boolean dispatchEvent(int event) {
              eventRecorder.recordEvent(event);

              return super.dispatchEvent(event);
            }
          };
        }
      };

When runnning the application, the ``EventDispatcher`` will now record the events and then redirect them to its parent ``dispatchEvent`` so they can be managed normally by the application.

Set Up the Scenario Player
----------------

As we now have recorded our scenario we have to play it. For that we have to add the ``EventPlayer`` to our project:

.. code-block:: java

      /**
       * Plays events.
       */
      public class EventPlayer {

        @Nullable
        private final Pointer pointer;
        @Nullable
        private final Buttons buttons;

        /**
        * Creates a robot.
        */
        public EventPlayer() {
          this.pointer = EventGenerator.get(Pointer.class, 0);
          this.buttons = EventGenerator.get(Buttons.class, 1);
        }

        /**
        * Pauses before the next action.
        *
        * @param delay
        *            the delay to pause.
        */
        public void pause(long delay) {
          ThreadUtils.sleep(delay);
        }

        /**
        * Generates a press event.
        *
        * @param x
        *            the x coordinate of the pointer.
        * @param y
        *            the y coordinate of the pointer.
        */
        public void press(int x, int y) {
          if (null != this.pointer) {
            this.pointer.reset(x, y);
          }
          if (null != this.pointer) {
            this.pointer.send(Pointer.PRESSED, 0);
          }
        }

        /**
        * Generates a move event.
        *
        * @param x
        *            the x coordinate of the pointer.
        * @param y
        *            the y coordinate of the pointer.
        */
        public void move(int x, int y) {
          if (null != this.pointer) {
            this.pointer.move(x, y);
          }
        }

        /**
        * Generates a release event.
        *
        * @param x
        *            the x coordinate of the pointer.
        * @param y
        *            the y coordinate of the pointer.
        */
        public void release(int x, int y) {
          if (null != this.pointer) {
            this.pointer.reset(x, y);
          }
          if (null != this.pointer) {
            this.pointer.send(Pointer.RELEASED, 0);
          }
        }

        /**
        * Generates a button event.
        */
        public void button() {
          if (null != this.buttons) {
            this.buttons.send(Buttons.RELEASED, 0);
          }
        }
      }

``EventPlayer`` will play events using the ``EventGenerator``.

We will now extend ``EventPlayer`` in order to play a specific scenario:

.. code-block:: java

      /**
      * Robot scenario which reproduces the recorded human user events .
      */
      public class NavigationScenario extends EventPlayer implements Runnable {

        @Override
        public void run() {
          press(344, 177);
          pause(885);
          release(344, 177);
          pause(359);
          press(184, 192);
          pause(34);
          move(185, 192);
          pause(24);
          move(188, 192);
          pause(23);
          move(191, 192);
          pause(24);
          move(196, 192);
          pause(21);
          move(206, 191);

        }
      }

The ``run`` method from the code above already contains recorded events, you will have to replace it by the ``EventRecorder`` output you get when recording the events.

Run the Scenario
----------------

We will now create a task that will run the scenario:

.. code-block:: java

        /**
      * A robot task is able to run a given scenario.
      */
      public class RobotTask {

        private boolean running;

        /**
        * Creates a demo robot.
        */
        public RobotTask() {
          this.running = false;
        }

        /**
        * Starts the given scenario.
        *
        * @param scenario
        *            the scenario to run.
        */
        public void startScenario(final Runnable scenario) {
          if (!this.running) {
            this.running = true;

            new Thread() {
              @Override
              public void run() {
                scenario.run();
                RobotTask.this.running = false;
              }
            }.start();
          }
        }

        /**
        * Returns whether the robot is currently running.
        *
        * @return <code>true</code> if the robot is running, false otherwise</code>.
        */
        public boolean isRunning() {
          return this.running;
        }
      }

You can now start the ``RobotTask`` in your application:

.. code-block:: java

      RobotTask robot = new RobotTask();
			robot.startScenario(new NavigationScenario());

Then, launch your application: the recorded scenario is now re-played, well done!
