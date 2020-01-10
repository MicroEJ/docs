HIL Engine
==========

Below are the HIL Engine options:

.. table:: HIL Engine Options

   +-----------------------+-----------------------------------------------+
   | Option name           | Description                                   |
   +=======================+===============================================+
   | ``-verbose[e....e]``  | Extra messages are printed out to the console |
   |                       | (add extra e to get more messages).           |
   +-----------------------+-----------------------------------------------+
   | ``-ip <address>``     | SIMJPF connection IP address (A.B.C.D). By    |
   |                       | default, set to localhost.                    |
   +-----------------------+-----------------------------------------------+
   | ``-port <port>``      | SIMJPF connection port. By default, set to    |
   |                       | 8001.                                         |
   +-----------------------+-----------------------------------------------+
   | ``-conne              | timeout in s for SIMJPF connections. By       |
   | ctTimeout <timeout>`` | default, set to 10 seconds.                   |
   +-----------------------+-----------------------------------------------+
   | ``-exclu              | Types that will be excluded from the HIL      |
   | des <name[sep]name>`` | Engine class resolution provided mocks. By    |
   |                       | default, no types are excluded.               |
   +-----------------------+-----------------------------------------------+
   | ``-mo                 | Mocks are either ``.jar`` file or ``.class``  |
   | cks <name[sep]name>`` | files.                                        |
   +-----------------------+-----------------------------------------------+
