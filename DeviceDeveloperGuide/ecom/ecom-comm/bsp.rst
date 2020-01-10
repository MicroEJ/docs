BSP File
========

The ECOM Comm C module needs to know, when the MicroEJ application is
built, the name of the implementation. This mapping is defined in a BSP
definition file. The name of this file must be ``bsp.xml`` and must be
written in the ECOM comm module configuration folder (near the
``ecom-comm.xml`` file). In previous example the ``bsp.xml`` file would
contain:

::

   <bsp>
       <nativeImplementation
           name="MY_LLCOMM"
           nativeName="LLCOMM_BUFFERED_CONNECTION"
       />
   </bsp>

where ``nativeName`` is the name of the interface, and ``name`` is the
name of the implementation.
