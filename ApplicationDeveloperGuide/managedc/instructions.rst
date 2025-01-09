.. _managedc.instructions:

Instructions
============

The MicroEJ engine supports the version 1.0 of the `Wasm specification <https://www.w3.org/TR/wasm-core-1/>`_ with the following additionnal instsructions and limitations.

Additionnal WebAssembly Instructions
------------------------------------

* i32.extend8_s
* i32.extend16_s
* i64.extend8_s
* i64.extend16_s
* i64.extend32_s

* memory.init
* data.drop
* memory.copy
* memory.fill

* memory.atomic.notify
* memory.atomic.wait32

* i32.atomic.load
* i64.atomic.load
* i32.atomic.store
* i32.atomic.rmw.xchg
* i32.atomic.rmw.cmpxchg


.. _managedc.instructions.partially_supported:

Wasm Instructions partially supported
-------------------------------------

* memory_grow: Executing the ``memory_grow`` instruction will not result in an error, but it will not expand the Wasm linear memory either.

Therefore, applications should not try to increase the Wasm linear memory.
Use the following linker options to set both the initial and maximum linear memory size to the same value: ``-Wl,--initial-memory=<value>`` and  ``-Wl,--max-memory=<value>`` 


..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
