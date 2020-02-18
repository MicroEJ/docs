HIL Engine
==========

Below are the HIL Engine options:

.. tabularcolumns:: |L|L|

.. table:: HIL Engine Options

   +-------------------------------+-----------------------------------------------+
   | Option name                   | Description                                   |
   +===============================+===============================================+
   | ``-verbose[e....e]``          | Extra messages are printed out to the console |
   |                               | (add extra e to get more messages).           |
   +-------------------------------+-----------------------------------------------+
   | ``-ip <address>``             | MicroEJ simulator connection IP address       |
   |                               | (A.B.C.D). By default, set to localhost.      |
   +-------------------------------+-----------------------------------------------+
   | ``-port <port>``              | MicroEJ simulator connection port. By         |
   |                               | default, set to 8001.                         |
   +-------------------------------+-----------------------------------------------+
   | ``-connectTimeout <timeout>`` | timeout in s for MicroEJ simulator            |
   |                               | connections. By default, set to 10 seconds.   |
   +-------------------------------+-----------------------------------------------+
   | ``-excludes <name[sep]name>`` | Types that will be excluded from the HIL      |
   |                               | Engine class resolution provided mocks. By    |
   |                               | default, no types are excluded.               |
   +-------------------------------+-----------------------------------------------+
   | ``-mocks <name[sep]name>``    | Mocks are either ``.jar`` file or ``.class``  |
   |                               | files.                                        |
   +-------------------------------+-----------------------------------------------+

.. list-table::

   -
      - ``-verbose[e....e]``
      - Extra messages are printed out to the console (add extra e to get more messages).
   -
      - ``-ip <address>``
      - MicroEJ simulator connection IP address (A.B.C.D). By default, set to localhost.
   -
      - ``-port <port>``
      - MicroEJ simulator connection port. By default, set to 8001.
   -
      - ``-connectTimeout <timeout>``
      - timeout in s for MicroEJ simulator connections. By default, set to 10 seconds.
   -
      - ``-excludes <name[sep]name>``
      - Types that will be excluded from the HIL Engine class resolution provided mocks. By default, no types are excluded.
   -
      - ``-mocks <name[sep]name>``
      - Mocks are either ``.jar`` file or ``.class`` files.
