.. _limitations:

Limitations
===========

.. table:: Platform Limitations

    +------------------------------------------+------------+-----------+
    | Item                                     | EVAL       | DEV       |
    +==========================================+============+===========+
    | Number of Classes                        | 4000       | 4000      |
    +------------------------------------------+------------+-----------+
    | Number of methods per class              | 3000       | 65000     |
    +------------------------------------------+------------+-----------+
    | Total number of methods                  | 4000       | unlimited |
    +------------------------------------------+------------+-----------+
    | Class / Interface hierarchy depth        | 127 max    | 127 max   |
    +------------------------------------------+------------+-----------+
    | Number of monitors [1]_ per thread       | 8 max      | 8 max     |
    +------------------------------------------+------------+-----------+
    | Numbers of exception handlers per method | 63 max     | 63 max    |
    +----------------------+-------------------+------------+-----------+
    | Number of fields     | Base type         | 65000      | 65000     |
    |                      +-------------------+------------+-----------+
    |                      | References        | 65000      | 65000     |
    +----------------------+-------------------+------------+-----------+
    | Number of statics    | boolean + byte    | limited    | 65000     |
    |                      +-------------------+------------+-----------+
    |                      | short + char      | limited    | 65000     |
    |                      +-------------------+------------+-----------+
    |                      | int + float       | limited    | 65000     |
    |                      +-------------------+------------+-----------+
    |                      | long + double     | limited    | 65000     |
    |                      +-------------------+------------+-----------+
    |                      | References        | limited    | 65000     |
    +----------------------+-------------------+------------+-----------+
    | Method size                              | 65000      | 65000     |
    +------------------------------------------+------------+-----------+
    | Time limit                               | 60 minutes | unlimited |
    +------------------------------------------+------------+-----------+
    | Number of threads                        | 62         | 62        |
    +------------------------------------------+------------+-----------+

.. [1]
   No more than n different monitors can be held by one thread at any
   time.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
