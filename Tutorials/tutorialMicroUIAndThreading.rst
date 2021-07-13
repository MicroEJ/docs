MicroUI and Threading
=====================

On MicroEJ there are two threads that handle the application, ``DisplayPump`` and ``InputPump``.

#. ``DisplayPump`` is a thread responsible for

    - managing the events;
    - doing the validation (layout) of the widgets;
    - rendering the widgets.

#. ``InputPump`` waits for native events and immediately delegates their handling to the ``DisplayPump``.

DisplayPump
-----------------
Everything related to the UI must be executed on the DisplayPump. The goal is that all the actions are done in an ordered sequence. Another point is that it avoids to synchronise the modification and the rendering (and have glitches on the display).

Some methods request an action asynchronously in the DisplayPump:

- repaint asynchronously calls render (and ``renderContent``),
- revalidate asynchronously calls ``validate`` (and ``validateContent``) then ``setBounds`` (and ``setBoundsContent``).
- The handleEvent method is also called in the DisplayPump.

These methods (not exhaustive) should be called in the DisplayPump (if the receiver is in the displayed hierarchy):

- ``Composite``: ``add``, ``remove``,
- ``Widget``: ``setVisible``, ``setEnabled``,
- ``Panel``: ``setWidget``, ``show``,
- ``TransitionContainer``: ``show``.
- To execute methods in the ``DisplayPump``, use ``Display.callSerially``.

To avoid slowing down the rendering (and the animations), long running algorithm should be executed in another thread. For example the creation of a new complex page could be done entirely in another thread. Once it is ready, it could be shown on the display and then every modification in this page must be done in the ``DisplayPump``.

Animations management
----------------------

Widget library provides an ``Animator`` that repeatedly executes several animations. This animator uses the unique instance of Timer registered in the service loader ``ServiceLoader.getServiceLoader().getService(Timer.class)``. Therefore the tick method of the animations will be called in this timer.
If an animation needs to modify the UI, don’t forget to delegate it in the DisplayPump.

To avoid slowing down animations, long running algorithms should not be executed in this timer.
