.. _lldisplayextra_error:

LLDISPLAY_EXTRA
===============

Error Messages
--------------

Display module calls the function ``LLDISPLAY_EXTRA_IMPL_error`` when
the LLDISPLAY implementation *has to* perform a drawing but does not.

.. table:: LLDISPLAY_EXTRA Error Messages

   +---------+------------------------------------------------------------+
   | ID      | Description                                                |
   +=========+============================================================+
   | -10     | A call to ``LLDISPLAY_EXTRA_IMPL_fillRect`` has been       |
   |         | performed but the implementation has not performed the     |
   |         | drawing.                                                   |
   +---------+------------------------------------------------------------+
   | -11     | A call to ``LLDISPLAY_EXTRA_IMPL_drawImage`` has been      |
   |         | performed but the implementation has not performed the     |
   |         | drawing.                                                   |
   +---------+------------------------------------------------------------+
   | -12     | A call to ``LLDISPLAY_EXTRA_IMPL_scaleImage`` has been     |
   |         | performed but the implementation has not performed the     |
   |         | drawing.                                                   |
   +---------+------------------------------------------------------------+
   | -13     | A call to ``LLDISPLAY_EXTRA_IMPL_rotateImage`` has been    |
   |         | performed but the implementation has not performed the     |
   |         | drawing.                                                   |
   +---------+------------------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
