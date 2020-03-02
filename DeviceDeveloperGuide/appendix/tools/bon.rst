Immutable Files Related Error Messages
======================================

The following error messages are issued at SOAR time (link phase) and
not at runtime.

.. table:: Errors when parsing immutable files at link time.

   +-------------+--------------------------------------------------------+
   | Message  ID | Description                                            |
   +=============+========================================================+
   | 0           | Duplicated ID in immutable files. Each immutable       |
   |             | object should have a unique ID in the SOAR image.      |
   +-------------+--------------------------------------------------------+
   | 1           | An immutable file refers to an unknown field of an     |
   |             | object.                                                |
   +-------------+--------------------------------------------------------+
   | 2           | Tried to assign the same object field twice.           |
   +-------------+--------------------------------------------------------+
   | 3           | All immutable object fields should be defined in the   |
   |             | immutable file description.                            |
   +-------------+--------------------------------------------------------+
   | 4           | The assigned value does not match the expected Java    |
   |             | type.                                                  |
   +-------------+--------------------------------------------------------+
   | 5           | An immutable object refers to an unknown ID.           |
   +-------------+--------------------------------------------------------+
   | 6           | The length of the immutable object does not match the  |
   |             | length of the assigned object.                         |
   +-------------+--------------------------------------------------------+
   | 7           | The type defined in the file doesn't match the Java    |
   |             | expected type.                                         |
   +-------------+--------------------------------------------------------+
   | 8           | Generic error while parsing an immutable file.         |
   +-------------+--------------------------------------------------------+
   | 9           | Cycle detected in an alias definition.                 |
   +-------------+--------------------------------------------------------+
   | 10          | An immutable object is an instance of an abstract      |
   |             | class or an interface.                                 |
   +-------------+--------------------------------------------------------+
   | 11          | Unknown XML attribute in an immutable file.            |
   +-------------+--------------------------------------------------------+
   | 12          | A mandatory XML attribute is missing.                  |
   +-------------+--------------------------------------------------------+
   | 13          | The value is not a valid Java literal.                 |
   +-------------+--------------------------------------------------------+
   | 14          | Alias already exists.                                  |
   +-------------+--------------------------------------------------------+

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
