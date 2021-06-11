How to test a GUI application with a (software) robot
=====================================================

- This article presents how to test a GUI application with a software robot for robotic process automation (RPA).
- Robot tests and traditional unit tests are different but both are useful.
- Traditional unit tests validate the systems through calls to the API (internal or external). Robot tests validate the systems by mimiing the human user behavior directly in the GUI.
- The robot implementation proposed here targets the following errors detection:
    - OutOfMemory
    - StackOverflow
    - MEJ32 and platform librairies error
    - Widget sequence validation

- The following document covers:
    - recording human touch events on the simulator or on the embedded platform
    - running recorded events on the simulator or on the embedded platform
- The following document does not cover:
    - the display rendering validation
    - integration of the robot into an automatic JUnit test suite
- We will now present the basic architecture and code required to create and to run a robot within a MicroEJ application on the simulator and embedded platform.


- In the following sections, we assume:
    - the MicroEJ Java application is based in MicroUI 2.x, MWT 2.x and Widget 2.x
    - the MicroEJ platform has a display interface and a touch controller (using the MicroUI EventGenerator for Pointer)

Overview
--------

- The robot creation process is twofold. First, we have to record and store the human user events. Second, we have to play them back with the robot.
- To record the events we will develop a custom EventHandler and we will inject it into the EventGenerator of Pointer events. The handler will record the events and generate the Java code to play them back.
- Then, we will inject this code into our main application and run it.
- NB: In the next sections, we show code that is mostly functional. To use it in our project, we have to put it in our MicroEJ SDK/Studio workspace and add the proper imports.

Record the Robot input events
-----------------------------

- We will now look at how to record the events.

Record events with WatchPointerEventHandler
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Here is the custom EventHandler named WatchPointerEventHandler.

.. code:: java

    private class WatchPointerEventHandler implements EventHandler {
        private final EventHandler initialEventHandler;
        private long lastTimeEvent;

        public WatchPointerEventHandler(EventHandler eventHandler) {
            this.initialEventHandler = eventHandler;
            this.lastTimeEvent = System.currentTimeMillis();
        }

        @Override
        public boolean handleEvent(int event) {
            // Forward events to the initial EventHandler.
            final boolean ret = this.initialEventHandler.handleEvent(event);

            if (Pointer.EVENT_TYPE == Event.getType(event)) {
                Pointer pointer = (Pointer) Event.getGenerator(event);
                final int action = Buttons.getAction(event);
                onAction(action);
            }
            return ret;
        }

        private void onAction(int action) {
            String command = null;
            boolean isCommand = true;
            switch (action) {
            case Buttons.PRESSED:
                command = "robot.press(" + WatchPointer.this.pointer.getX() + ", " + WatchPointer.this.pointer.getY()
                        + ");";
                break;
            case Pointer.MOVED:
            case Pointer.DRAGGED:
                command = "robot.move(" + WatchPointer.this.pointer.getX() + ", " + WatchPointer.this.pointer.getY()
                        + ");";
                break;
            case Buttons.RELEASED:
                command = "robot.release(" + WatchPointer.this.pointer.getX() + ", " + WatchPointer.this.pointer.getY()
                        + ");";
                break;
            default:
                isCommand = false;
            }

            if (isCommand) {
                final long delta = System.currentTimeMillis() - this.lastTimeEvent;
                this.lastTimeEvent = System.currentTimeMillis();
                System.out.println("robot.pause(" + delta + ");");
                System.out.println(command);
            }
        }
    }

- This EventHandler does two things.
    #. It records all pressed, moved, dragged and released events as well as the time between each event (we want to play our robot at the same speed as the human)
    #. It forwards all events to the initial EventHandler. Without that, our handler would hijack the initial handler and our UI would be unresponsive because it would receive no event.

- Note that WatchPointerEventHandler outputs the commands on the standard output. More on this a bit later.

Replace default EventHandler with WatchPointerEventHandler
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Next, we setup the handler

.. code:: java

    public class WatchPointer {
        final Pointer pointer;
        EventHandler initialEventHandler;
        private static WatchPointer instance;

        private class WatchPointerEventHandler implements EventHandler {
            // snip
        }

        WatchPointer() {
            // (1)
            this.pointer = EventGenerator.get(Pointer.class, 0);
        }

        public static WatchPointer getInstance() {
            if (instance == null) {
                instance = new WatchPointer();
            }
            return instance;
        }

        public EventHandler getInitialEventHandler() {
            return this.initialEventHandler;
        }

        public void setInitialEventHandler(EventHandler initialEventHandler) {
            this.initialEventHandler = initialEventHandler;
        }

        /**
        * Starts monitoring activity by setting up a new EventHandler.
        */
        public void start() {
            // (2)
            this.pointer.setEventHandler(new WatchPointerEventHandler(this.initialEventHandler));
        }

        /**
        * Stops monitoring activity by restoring the initial EventHandler.
        */
        public void stop() {
            // (3)
            this.pointer.setEventHandler(this.initialEventHandler);
        }
    }

- This code
    #. saves the default EventHandler of the Pointer to pass it to the WatchPointerEventHandler so that it can forward the events
    #. we start the recording by replacing the EventHandler 
    #. and we stop it by restoring the initial EventHandler.

Use WatchPointer in our main application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- The API of our WatchPointer is straightforward, just start() and stop() the recording of events. A good place to start the recording is after the initialization of your GUI.

.. code:: java

    public class MainApp {
        public static void main(String[] args) {
            // Initialization.
            // ...

            // Start recording events.
            new WatchPointer().start();
        }
    }

- And that's it

- The easiest way to record our robots is to run it on the platform simulator.
- The events will be outputted in the MicroEJ SDK console.

- The robot can also be run on board with the WatchPointer enabled. The events will be outputted on the trace output (typically a UART).

- We will now see how to run our robot with the recorded events
