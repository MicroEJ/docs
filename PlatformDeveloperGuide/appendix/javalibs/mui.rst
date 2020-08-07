MicroUI
=======

Error Messages
--------------

When an exception is thrown by the implementation of the MicroUI API, the exception ``MicroUIException`` with the error message

``MicroUI:E=<messageId>``

is issued, where the meaning of ``<messageId>`` is defined in :ref:`Table "MicroUI Error Messages" <table_mui-error-msgs>`.

.. _table_mui-error-msgs:
.. tabularcolumns:: |p{2cm}|p{13cm}|
.. table:: MicroUI Error Messages

   +-------------+--------------------------------------------------------+
   | Message ID  | Description                                            |
   +=============+========================================================+
   | 1           | Another ``EventGenerator`` cannot be added into the    |
   |             | system pool (max 254).                                 |
   +-------------+--------------------------------------------------------+
   | 0           | [platform issue] Result of MicroUI static              |
   |             | initialization step seems invalid. MicroUI cannot      |
   |             | start. Please fix MicroUI static initialization step   |
   |             | (see :ref:`section_static_init`)  and rebuild the      | 
   |             | platform.                                              |
   +-------------+--------------------------------------------------------+
   | -1          | MicroUI is not started; call MicroUI.start() before    |
   |             | using a MicroUI API.                                   |
   +-------------+--------------------------------------------------------+
   | -2          | Unknown event generator class name.                    |
   +-------------+--------------------------------------------------------+
   | -3          | Deadlock. Cannot wait for an event in the same thread  |
   |             | that runs events. ``Display.waitFlushCompleted()``     |
   |             | must not be called in the display pump thread (for     |
   |             | example in ``render`` method).                         |
   +-------------+--------------------------------------------------------+
   | -4          | Resource's path must be relative to the classpath      |
   |             | (start with '/') or resource is not available.         |
   +-------------+--------------------------------------------------------+
   | -5          | The resource data cannot be read for unknown reason.   |
   +-------------+--------------------------------------------------------+
   | -6          | The resource has been closed and cannot be used        |
   |             | anymore.                                               |
   +-------------+--------------------------------------------------------+
   | -7          | Out of memory. Not enough memory to allocate the       |
   |             | ``Image``'s buffer. Try to close some                  |
   |             | useless images and retry opening the new image, or     |
   |             | increase the size of the MicroUI images heap.          |
   +-------------+--------------------------------------------------------+
   | -8          | The platform cannot decode this kind of image, because |
   |             | the required runtime image decoder is not available in |
   |             | the platform.                                          |
   +-------------+--------------------------------------------------------+
   | -9          | This exception is thrown when the pump of the internal |
   |             | thread ``UIPump`` is full. In this case, no more event |     
   |             | (such as ``requestRender``, input events etc.) can be  |
   |             | added into it.                                         |
   |             |                                                        |
   |             | Most of time this error occurs when:                   |
   |             |                                                        |
   |             | -  There is a user thread which performs too many      |
   |             |    calls to the method ``requestRender`` without       |
   |             |    waiting for the end of the previous drawing.        |
   |             |                                                        |
   |             | -  Too many input events are pushed from an input      |
   |             |    driver to the UI pump (for example some touch       |
   |             |    events).                                            |
   +-------------+--------------------------------------------------------+
   | -10         | There is no display on the platform.                   |
   +-------------+--------------------------------------------------------+
   | -11         | There is no font (platform and application).           |
   +-------------+--------------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
