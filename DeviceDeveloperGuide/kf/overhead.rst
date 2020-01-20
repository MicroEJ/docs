Memory Considerations
=====================

Multi applications memory overhead of MicroEJ core engine runtime
elements are described in `table_title <#kf-overhead>`__.

.. table:: Multi applications Memory Overhead

   +-----------+-----------+-----------------------------------------------+
   | Runtime   | Memory    | Description                                   |
   | element   |           |                                               |
   +===========+===========+===============================================+
   | Object    | RW        | 4 bytes                                       |
   +-----------+-----------+-----------------------------------------------+
   | Thread    | RW        | 24 bytes                                      |
   +-----------+-----------+-----------------------------------------------+
   | Stack     | RW        | 8 bytes                                       |
   | Frame     |           |                                               |
   +-----------+-----------+-----------------------------------------------+
   | Class     | RO        | 4 bytes                                       |
   | Type      |           |                                               |
   +-----------+-----------+-----------------------------------------------+
   | Interface | RO        | 8 bytes                                       |
   | Type      |           |                                               |
   +-----------+-----------+-----------------------------------------------+
