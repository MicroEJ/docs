Implementations
===============

External Resources Loader module provides some Low Level API (LLEXT_RES)
to let the BSP manage the external resources.

Open a Resource
---------------

The LLAPI to implement in the BSP are listed in the header file
``LLEXT_RES_impl.h``. First, the framework tries to open an external
resource using the ``open`` function. This function receives the
resources path as a parameter. This path is the absolute path of the
resource from the MicroEJ application classpath (the MicroEJ application
source base directory). For example, when the resource is located here:
``com.mycompany.myapplication.resource.MyResource.txt`` , the given path
is: ``com/mycompany/myapplication/resource/MyResource.txt``.

Resource Identifier
-------------------

This ``open`` function has to return a unique ID (positive value) for
the external resource, or returns an error code (negative value). This
ID will be used by the framework to manipulate the resource (read, seek,
close, etc.).

Several resources can be opened at the same time. The BSP does not have
to return the same identifier for two resources living at the same time.
However, it can return this ID for a new resource as soon as the old
resource is closed.

Resource Offset
---------------

The BSP must hold an offset for each opened resource. This offset must
be updated after each call to ``read`` and ``seek``.

Resource Inside the CPU Address Space Range
-------------------------------------------

An external resource can be programmed inside the CPU address space
range. This memory (or a part of memory) is not managed by the SOAR and
so the resources inside are considered as external.

Most of time the content of an external resource must be copied in a
memory inside the CPU address space range in order to be accessible by
the MicroEJ algorithms (draw an image etc.). However, when the resource
is already inside the CPU address space range, this copy is useless. The
function ``LLEXT_RES_getBaseAddress`` must return a valid CPU memory
address in order to avoid this copy. The MicroEJ algorithms are able to
target the external resource bytes without using the other ``LLEXT_RES``
APIs such as ``read``, ``mark`` etc.
