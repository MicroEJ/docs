MicroUI and Threading
=====================

On MicroEJ, there are two Threads that handle the application, ``DisplayPump`` and ``InputPump``.

The user can add more Threads if needed.

#. ``DisplayPump`` is a thread responsible for:

    - Managing the Events;
    - Doing the Validation (layout) of The Widgets;
    - Rendering the Widgets.

#. ``InputPump`` waits for native events and immediately delegates their handling to the ``DisplayPump``.

DisplayPump
-----------

Everything related to the UI must be executed on the DisplayPump. The goal is that all the actions are done in an ordered sequence. Another point is that it avoids to synchronise the modification and the rendering (and have glitches on the display).

Some methods request an action asynchronously in the DisplayPump:

- Repaint Asynchronously Calls Render (and ``renderContent``),
- Revalidate Asynchronously Calls ``validate`` (and ``validateContent``) then ``setBounds`` (and ``setBoundsContent``).
- The handleEvent Method is Also Called in the DisplayPump.

These methods (not exhaustive) should be called in the DisplayPump (if the receiver is in the displayed hierarchy):

- ``Composite``: ``add``, ``remove``,
- ``Widget``: ``setVisible``, ``setEnabled``,
- ``Panel``: ``setWidget``, ``show``,
- ``TransitionContainer``: ``show``.
- To execute methods in the ``DisplayPump``, use ``Display.callSerially``.

To avoid slowing down the rendering (and the animations), long running algorithm should be executed in another Thread. For example the creation of a new complex page could be done entirely in another thread. Once it is ready, it could be shown on the display and then every modification in this page must be done in the ``DisplayPump``.

Animations Management
---------------------

MWT library provides an ``Animator`` that repeatedly executes several animations. a new Runnable is added to the DisplayPump as soon as the previous frame has been flushed.


To avoid slowing down animations, long running algorithms should not be executed in this timer.
