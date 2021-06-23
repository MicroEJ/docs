How to test a GUI application with a (software) robot
=====================================================

This article presents how to test a GUI application with a software robot for robotic process automation (RPA).
Robot tests and traditional unit tests are different but both are useful.
Traditional unit tests validate the systems through calls to the API (internal or external). Robot tests validate the systems by mimiing the human user behavior directly in the GUI.
The robot implementation proposed here targets the following errors detection:
    - ``OutOfMemory``
    - ``StackOverflow``
    - MEJ32 and platform librairies error
    - Widget sequence validation

The following document covers:

    - recording human touch events on the simulator or on the embedded platform
    - running recorded events on the simulator or on the embedded platform

The following document does not cover:

    - the display rendering validation
    - integration of the robot into an automatic JUnit test suite

We will now present the basic architecture and code required to create and to run a robot within a MicroEJ application on the simulator and embedded platform.


In the following sections, we assume:

    - the MicroEJ Java application is based in MicroUI 2.x, MWT 2.x and Widget 2.x
    - the MicroEJ platform has a display interface and a touch controller (using the MicroUI EventGenerator for Pointer)

Overview
--------

The robot creation process is twofold. First, we have to record and store the human user events. Second, we have to play them back with the robot.
To record the events we will develop a custom ``EventHandler`` and we will inject it into the ``EventGenerator`` of ``Pointer`` events. The handler will record the events and generate the Java code to play them back.
Then, we will inject this code into our main application and run it.
NB: In the next sections, we show code that is mostly functional. To use it in our project, we have to put it in our MicroEJ SDK/Studio workspace and add the proper imports.

Record the Robot input events
-----------------------------

We will now look at how to record the events.

Record events with ``WatchPointerEventHandler``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here is the custom ``EventHandler`` named ``WatchPointerEventHandler``.

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

This ``EventHandler`` does two things:

    #. It records all pressed, moved, dragged and released events as well as the time between each event (we want to play our robot at the same speed as the human)
    #. It forwards all events to the initial ``EventHandler``. Without that, our handler would hijack the initial handler and our UI would be unresponsive because it would receive no event.

Note that ``WatchPointerEventHandler`` outputs the commands on the standard output. More on this a bit later.

Replace default ``EventHandler`` with ``WatchPointerEventHandler``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Next, we setup the handler

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

This code
    #. saves the default ``EventHandler`` of the Pointer to pass it to the ``WatchPointerEventHandler`` so that it can forward the events
    #. we start the recording by replacing the ``EventHandler``
    #. and we stop it by restoring the initial ``EventHandler``.

Use WatchPointer in our main application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The API of our ``WatchPointer`` is straightforward, just ``start()`` and ``stop()`` the recording of events. A good place to start the recording is after the initialization of your GUI.

.. code:: java

    public class MainApp {
        public static void main(String[] args) {
            // Initialization.
            // ...

            // Start recording events.
            WatchPointer.getInstance().setInitialEventHandler(desktop);
            WatchPointer.getInstance().start();
        }
    }

And that's it

The easiest way to record our robots is to run it on the platform simulator.
The events will be outputted in the MicroEJ SDK console.

The robot can also be run on board with the ``WatchPointer`` enabled. The events will be outputted on the trace output (typically a UART).

We will now see how to run our robot with the recorded events

Run a robot
-----------
Play the Robot
~~~~~~~~~~~~~~

Playing a robot is easy. We just need to send the recorded events. Here is our Robot class.

.. code:: java

    public class Robot {

        private final Pointer pointer;

        /**
        * Creates a Robot.
        */
        public Robot() {
            this.pointer = EventGenerator.get(Pointer.class, 0);
        }

        /**
        * Pauses for n milliseconds.
        *
        * @param delay
        *            the delay to pause.
        */
        public void pause(long delay) {
            try {
            Thread.sleep(delay);
            } catch (InterruptedException e) {
            e.printStackTrace();
            }
        }

        /**
        * Sends press event at the given coordinate.
        *
        * @param x
        *            the x
        * @param y
        *            the y
        */
        public void press(int x, int y) {
            this.pointer.move(x, y);
            this.pointer.send(Pointer.PRESSED, 0);
        }

        /**
        * Sends move event at the given coordinate.
        *
        * @param x
        *            the x
        * @param y
        *            the y
        */
        public void move(int x, int y) {
            this.pointer.move(x, y);
        }

        /**
        * Sends release event at the given coordinate.
        *
        * @param x
        *            the x
        * @param y
        *            the y
        */
        public void release(int x, int y) {
            this.pointer.move(x, y);
            this.pointer.send(Pointer.RELEASED, 0);
        }
    }

The Robot API implements the commands that were generated in the ``WatchPointerEventHandler``. Through the basic operations ``press()``, ``move()`` and ``release()`` the click and drag actions are simulated. With the ``pause()`` we ensure we do it exactly at the same speed as the human who recorded it.

Use Robot in our main application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Copy the commands into a function and call it from the main application at the same place where ``WatchPointer`` was called.
Here is an example of a simple Robot.

.. code:: java

    public class DemoRobot {
        public static void runDemo1() {
            System.out.println("DemoRobot.runDemo1() -- START");
            final Robot robot = new Robot();

            robot.press(33, 130);
            robot.pause(82);
            robot.release(33, 130);
            robot.pause(1972);
            robot.press(401, 248);
            robot.pause(78);
            robot.release(401, 248);
            robot.pause(1047);
            robot.press(419, 249);
            robot.pause(43);
            robot.release(419, 249);
            robot.pause(1035);
            robot.press(407, 245);
            robot.pause(39);
            robot.release(407, 245);
            robot.pause(1012);
            robot.press(425, 250);
            robot.pause(20);
            robot.release(425, 250);
            robot.pause(918);
            robot.press(407, 249);
            robot.pause(58);
            robot.release(407, 249);
            robot.pause(1000);
            robot.press(302, 250);
            robot.pause(39);
            robot.release(302, 250);
            robot.pause(918);
            robot.press(307, 243);
            robot.pause(59);
            robot.move(304, 232);
            robot.pause(19);
            robot.release(304, 232);
            robot.pause(922);
            System.out.println("DemoRobot.runDemo1() -- END");
        }
    }

And now we plug it into our main application.

.. code:: java

    public class MainApp {
        public static void main(String[] args) {
            // initialization
            // ...

            // Start the robot.
            DemoRobot.runDemo1();
        }
    }

This new application can run on both the simulator and on the board.
At this point, we have the basics to create and to play software robots to test our applications.
Note that because we act at the UI level, whenever our application’s appearance changes, in particular if UI elements are moved around, we will need to update a new version of our robots to match the new UI.

Going further
-------------

Split the Robot into actions and build complex scenario
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As we create more and more complex robots it is a good idea to put the various behaviors into separate functions so that we can create complex scenarios out of simple action blocks.

Here is an example.

.. code:: java

    public class DemoRobot {
        final Robot robot;

        /**
        * Instantiates our Demo.
        */
        public void DemoRobot() {
            this.robot = new Robot();
        }

        public void login() {
            this.robot.press(33, 130);
            this.robot.pause(82);
            this.robot.release(33, 130);
            this.robot.pause(1972);
            this.robot.press(401, 248);
            this.robot.pause(78);
            this.robot.release(401, 248);
            this.robot.pause(1047);
        }

        public void openMenuConfiguration() {
            this.robot.press(425, 250);
            this.robot.pause(20);
            this.robot.release(425, 250);
            this.robot.pause(918);
            this.robot.press(407, 249);
            this.robot.pause(58);
            this.robot.release(407, 249);
            this.robot.pause(1000);
        }

        public void closeMenuConfiguration() {
            this.robot.press(307, 243);
            this.robot.pause(59);
            this.robot.move(304, 232);
            this.robot.pause(19);
            this.robot.release(304, 232);
            this.robot.pause(922);
        }

        public void selectOption1() {
            this.robot.press(407, 245);
            this.robot.pause(39);
            this.robot.release(407, 245);
            this.robot.pause(1012);
        }

        public void selectOption2() {
            this.robot.press(419, 249);
            this.robot.pause(43);
            this.robot.release(419, 249);
            this.robot.pause(1035);
        }

        public void goToLogin() {
            this.robot.press(302, 250);
            this.robot.pause(39);
            this.robot.release(302, 250);
            this.robot.pause(918);
        }

        // Logins and tests open/close of configuration menu.
        public void scenario1() {
            try {
                login();
                openMenuConfiguration();
                closeMenuConfiguration();
                goToLogin();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        // Logins and selects option 1 in configuration menu.
        public void scenario2() {
            try {
                login();
                openMenuConfiguration();
                selectOption1();
                goToLogin();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        // Logins and selects option 2 in configuration menu.
        public void scenario3() {
            try {
                login();
                openMenuConfiguration();
                selectOption2();
                goToLogin();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        // Endless loop with all three scenarios in random order.
        public void scenarioLoop() {
            Rand rand = new Random();
            try {
                while (true) {
                    switch (rand.nextInt(3)) {
                    case 0:
                        scenario1();
                        break;
                    case 1:
                        scenario2();
                        break;
                    case 2:
                        scenario3();
                        break;
                    }
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

Here we have the following basic actions:

    #. Logging;
    #. Opening the configuration menu;
    #. Closing the configuration menu;
    #. Selecting option 1;
    #. Selecting option 2;
    #. Going back to the login.

From those actions we build 3 scenarios:

    #. Test the opening/closing of the configuration menu.
    #. Select the option 1 in the configuration menu.
    #. Select the option 2 in the configuration menu.

And finally, we also have a “stress” scenario that endlessly go through the 3 previous scenarios in random order.
We can call each of those scenarios from our main application to test whatever we want to.

Validate the Widget
-------------------

So far our Robot is pretty simple and can catch all raised exceptions and runtime errors.

Depending on your application architecture, you most likely have some kind of central class that manages which is the main Widget currently displayed. For example you may use a ``TransitionContainer``. What we need, is a way to retrieve the Widget currently displayed.

The idea is:

    #. to record the Widget displayed before recording an action in our WatchPointerEventHandler and
    #. to check that the Widget is displayed before playing an action in our Robot.

Let’s assume that we have a ``Main.getCurrentWidget()`` method that returns the current Widget. We update WatchPointerEventHandler like this:

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
            Widget currentWidget = Main.getCurrentWidget();
            switch (action) {
            case Buttons.PRESSED:
                command = "robot.checkWidget(\"" + currentWidget.getClass().getName() + "\");\n"
                    + "robot.press(" + WatchPointer.this.pointer.getX() + ", " + WatchPointer.this.pointer.getY()
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

Conversely, we update Robot to add the ``checkWidget()`` method.

.. code:: java

    public class Robot {
        // snip

        /**
        * Ensures that the given Widget is displayed before proceeding to the next action.
        *
        * @param className
        *            the class name of the Widget that is expected to be displayed.
        *
        * @throws InterruptedException
        *             when the current Widget is different from the given Widget.
        */
        public void checkWidget(String className) throws InterruptedException {
            final Widget lastShown = Main.getCurrentWidget();
            final String lastShownName = lastShown.getClass().getName();
            if (!className.equals(lastShownName)) {
                throw new InterruptedException("Expected " + className + " got " + lastShownName);
            }
        }
    }

When we record new robots, we will record the current Widget before a press action is executed. And when we play the robots, we will ensure that the same Widget is displayed before sending the press event. If the Widget is not the one recorded, ``checkWidget`` will raise an exception, otherwise, we proceed as before.

JUnit
~~~~~

It is possible to integrate the robot into a JUnit test suite if we use ``assertEquals`` instead of raising an Exception.

.. note::
    check https://github.com/MicroEJ/Example-Sandboxed-JUnit 3 for more information on the JUnit use.

Add more checks
~~~~~~~~~~~~~~~

We can also use our application’s API and check the various states of our application. For example, once we have activated some buttons, a motor should start or some other actions should be taken.
We can use whatever we want to have a rock solid application!

Performance Regression Framework
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``checkWidget()`` method can also be used as a performance regression framework. If a Widget display time becomes much slower because of a regression, assuming the robot was recorded by a “not too slow” human, our robot will fail with an Exception.
We can even lower manually (or automatically) the timings to make sure our UI is responsive.
