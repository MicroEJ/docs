.. _managedc.instructions:

Supported Instructions
======================

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

Partially Supported WebAssembly Instructions 
--------------------------------------------

* memory_grow: Executing the ``memory_grow`` instruction will not result in an error, but it will not expand the Wasm linear memory either. See :ref:`managedc.linear.memory` for more details.



..
   | Copyright 2023-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
