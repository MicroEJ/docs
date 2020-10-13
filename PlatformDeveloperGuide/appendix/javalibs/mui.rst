MicroUI
=======

Error Messages
--------------

When an exception is thrown by the implementation of the MicroUI API,
the exception ``MicroUIException`` with the error message

``MicroUI:E=<messageId>``

is issued, where the meaning of ``<messageId>`` is defined in
:ref:`Table "MicroUI Error Messages" <table_mui-error-msgs>`.

.. _table_mui-error-msgs:
.. tabularcolumns:: |p{2cm}|p{13cm}|
.. table:: MicroUI Error Messages

   +-------------+--------------------------------------------------------+
   | Message ID  | Description                                            |
   +=============+========================================================+
   | 1           | Deadlock. Cannot wait for an event in the same thread  |
   |             | that runs events. ``Display.waitForEvent()`` must not  |
   |             | be called in the display pump thread (for example in   |
   |             | ``paint`` methods).                                    |
   +-------------+--------------------------------------------------------+
   | 3           | Out of memory. Not enough memory to allocate the       |
   |             | ``Image``'s buffer. Try to remove references on        |
   |             | useless images and retry opening the new image, or     |
   |             | increase the size of the MicroUI working buffer.       |
   +-------------+--------------------------------------------------------+
   | 4           | A polygon cannot have more than 16 sides.              |
   +-------------+--------------------------------------------------------+
   | 5           | The platform cannot allocate memory to create a        |
   |             | dynamic image.                                         |
   +-------------+--------------------------------------------------------+
   | 6           | ``Image``'s path is limited to 100 characters.         |
   +-------------+--------------------------------------------------------+
   | 7           | The platform cannot decode this kind of image, because |
   |             | the required runtime image decoder is not available in |
   |             | the platform.                                          |
   +-------------+--------------------------------------------------------+
   | 8           | Another ``EventGenerator`` cannot be added into the    |
   |             | system pool (max 254).                                 |
   +-------------+--------------------------------------------------------+
   | 9           | Font's path is limited to 100 characters.              |
   +-------------+--------------------------------------------------------+
   | 10          | Invalid font path: cannot load this font.              |
   +-------------+--------------------------------------------------------+
   | 11          | MicroUI is not started; call MicroUI.start() before    |
   |             | using a MicroUI API.                                   |
   +-------------+--------------------------------------------------------+
   | 15          | ``FIFOPump`` size must be positive                     |
   +-------------+--------------------------------------------------------+
   | 16          | ``FlyingImage`` feature is disabled in MicroEJ launch  |
   |             | options; cannot use this feature in application.       |
   +-------------+--------------------------------------------------------+
   | 17          | Out of memory. There is not enough memory to open a    |
   |             | new ``FlyingImage`` Try to increase the number of      |
   |             | concurrent flying images in the MicroEJ launcher.      |
   +-------------+--------------------------------------------------------+
   | 19          | Font's path must be relative to the classpath.         |
   +-------------+--------------------------------------------------------+
   | 20          | Unknown event generator class name.                    |
   +-------------+--------------------------------------------------------+
   | 21          | The font data cannot be loaded for an unknown reason   |
   |             | (font is stored outside the CPU address space range).  |
   +-------------+--------------------------------------------------------+

Exceptions
----------

Some other exceptions can be thrown by the MicroUI framework in addition
to the generic ``MicroUIException`` (see previous chapter).

.. tabularcolumns:: |p{3.5cm}|p{11.5cm}|
.. table:: MicroUI Exceptions

   +----------------------+--------------------------------------------------------+
   | Message ID           | Description                                            |
   +======================+========================================================+
   | OutOfEventsException | This exception is thrown when the pump of the internal |
   |                      | thread ``DisplayPump`` is full. In this case, no more  |
   |                      | event (such as ``repaint``, input events etc.) can be  |
   |                      | added into it.                                         |
   |                      |                                                        |
   |                      | Most of time this error occurs when:                   |
   |                      |                                                        |
   |                      | -  There is a user thread which performs too many      |
   |                      |    calls to the method ``paint`` without waiting for   |
   |                      |    the end of the previous drawing.                    |
   |                      |                                                        |
   |                      | -  Too many input events are pushed from an input      |
   |                      |    driver to the display pump (for example some touch  |
   |                      |    events).                                            |
   +----------------------+--------------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
