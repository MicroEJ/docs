HIL Engine
==========

Below are the HIL Engine options:

.. table:: HIL Engine Options

   +-------------------------------+-----------------------------------------------+
   | Option name                   | Description                                   |
   +===============================+===============================================+
   | ``-verbose[e....e]``          | Extra messages are printed out to the console |
   |                               | (add extra e to get more messages).           |
   +-------------------------------+-----------------------------------------------+
   | ``-ip <address>``             | MicroEJ Simulator connection IP address       |
   |                               | (A.B.C.D). By default, set to localhost.      |
   +-------------------------------+-----------------------------------------------+
   | ``-port <port>``              | MicroEJ Simulator connection port. By         |
   |                               | default, set to 8001.                         |
   +-------------------------------+-----------------------------------------------+
   | ``-connectTimeout <timeout>`` | timeout in s for MicroEJ Simulator            |
   |                               | connections. By default, set to 10 seconds.   |
   +-------------------------------+-----------------------------------------------+
   | ``-excludes <name[sep]name>`` | Types that will be excluded from the HIL      |
   |                               | Engine class resolution provided mocks. By    |
   |                               | default, no types are excluded.               |
   +-------------------------------+-----------------------------------------------+
   | ``-mocks <name[sep]name>``    | Mocks are either ``.jar`` file or ``.class``  |
   |                               | files.                                        |
   +-------------------------------+-----------------------------------------------+

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
