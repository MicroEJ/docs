MicroUI and Threading
=====================

There are two default Threads that handle the application when using MicroUI, the ``DisplayPump`` and the ``InputPump``.

The user can add more Threads if needed.

#. The ``DisplayPump`` is a thread responsible for:

    - Managing the Events;
    - Doing the Validation (layout) of The Widgets;
    - Rendering the Widgets.

#. The ``InputPump`` waits for native events from the hardware and immediately delegates their handling to the ``DisplayPump``.

DisplayPump
-----------

Everything related to the UI must be executed in the DisplayPump thread also known as the UI thread. The goal is that all the actions are done sequencially. Another point is that it avoids to synchronise the modification and the rendering (and have glitches on the display).

Some methods request an action asynchronously in the DisplayPump:

- The method requestRender is called asynchronously.
- In MWT the widget is asynchronously revalidated on requestLayout.
- The handleEvent Method is also called in the DisplayPump.

The UI thread is the right place for:

- Handling the user input events
- Laying out the widgets
- Rendering the widgets

To avoid slowing down the rendering (and the animations), long running algorithm should be executed in another Thread. For example the creation of a new complex page could be done entirely in another thread. Once it is ready, it could be shown on the display and then every modification in this page must be done in the ``DisplayPump``.
