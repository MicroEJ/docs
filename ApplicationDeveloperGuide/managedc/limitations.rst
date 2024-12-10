.. _managedc.limitations:

Limitations
===========

The Core Engine supports the `WebAssembly Core Specification 1.0 <https://www.w3.org/TR/wasm-core-1/>`_ with the following limitations.

Partially Supported Wasm Instructions 
-------------------------------------

- ``memory.grow``: Executing the ``memory.grow`` instruction will not result in an error, but it will not expand the Wasm linear either.
  Therefore, applications should not try to increase the Wasm linear memory. 
  Use the following linker options to set both the initial and maximum linear memory size to the same value: ``-Wl,--initial-memory=<value>`` and  ``-Wl,--max-memory=<value>`` 


Simulation
----------

Wasm code is not supported in simulation.

..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
