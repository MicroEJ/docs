Storage
=======

Introduction
------------

The `Storage <https://repository.microej.com/javadoc/microej_5.x/apis/index.html?ej/storage/Storage.html>`_ 
library provides a mechanism to store, retrieve, and manage data entries using identifiers. 
The library supports multiple implementations depending on the target environment and storage requirements.

Usage
-----

The Storage library offers two implementations:

- `RAM (Managed Heap) Implementation <https://repository.microej.com/modules/ej/library/runtime/storage/>`_:
   - Data is stored in RAM.
   - Add the following line to the project build file:
    
    .. code-block:: kotlin
       
       implementation("ej.library.runtime:storage:1.2.0")

- `FileSystem Implementation <https://repository.microej.com/modules/ej/library/runtime/storage-fs/>`_:
   - Data is stored in a file system.
   - Requires the :ref:`pack_fs` Pack to be available in the VEE Port.
   - Add the following line to the project build file: 
    
    .. code-block:: kotlin
       
       implementation("ej.library.runtime:storage-fs:1.2.0")

Initialization
~~~~~~~~~~~~~~

To create a ``Storage`` instance:

- **RAM (Managed Heap) Implementation:**
 
  .. code-block:: java
    
    Storage myStorage = new Storage();

- **FileSystem Implementation:**
 
  .. code-block:: java
    
    Storage myStorage = new StorageFs("my_root_folder");
  
Multi-Sandbox Specificities
^^^^^^^^^^^^^^^^^^^^^^^^^^^

When working in a multi-sandbox environment, the ``Storage`` instance should be created in the Kernel.

This instance can then be shared using :ref:`Shared Services <kernel_service_registry>`, to make it
available to Sandboxed Applications and other Kernel components:

- Register the ``Storage`` instance:
  
  .. code-block:: java

    final ServiceRegistryKF serviceRegistry = (ServiceRegistryKF) ServiceFactory.getServiceRegistry();
    serviceRegistry.register(Storage.class, myStorage, true);

- Retrieve it using:

  .. code-block:: java
    
    Storage storage = ServiceFactory.getService(Storage.class);
  

APIs
----

The ``Storage`` interface defines operations for managing entries with unique identifiers.

An identifier must be a valid string composed of letters, digits, underscores, hyphens, or dots, 
with the first character being a letter.

.. warning::
    
    The API does not guarantee thread safety for concurrent accesses to the same identifier.

Key Operations
~~~~~~~~~~~~~~

- ``store(id)``: Stores data under a given identifier.
- ``append(id)``: Appends data to an existing entry.
- ``exists(id)``: Checks if an entry exists.
- ``getSize(id)``: Retrieves the size of an entry in bytes.
- ``load(id)``: Loads data from a given identifier.
- ``modify(id, offset)``: Modifies data at a specific offset within an entry.
- ``move(id1, id2)``: Moves an entry from one identifier to another.
- ``getIds()``: Retrieves all stored identifiers.
- ``remove(id)``: Removes an entry with the specified identifier.

Code Example
~~~~~~~~~~~~

.. code-block:: java

    Storage storage = ServiceFactory.getService(Storage.class);
    String id1 = "example.data";
    String id2 = "example2.data";
    String id3 = "example3.data";

    try {
        // 1. Store data
        try (OutputStream os = storage.store(id1)) {
            os.write("Hello, MicroEJ Storage!".getBytes());
        }

        // 2. Append data
        try (OutputStream os = storage.append(id1)) {
            os.write(" This is appended data.".getBytes());
        }

        // 3. Check if an entry exists
        boolean exists = storage.exists(id1);

        // 4. Get the size of an entry
        long size = storage.getSize(id1);

        // 5. Load data
        try (InputStream is = storage.load(id1)) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = is.read(buffer)) != -1) {
                System.out.print(new String(buffer, 0, bytesRead));
            }
        }

        // 6. Modify data at a specific offset
        try (OutputStream os = storage.modify(id1, 7)) {
            os.write("Modified".getBytes());
        }

        // 7. Move an entry to a new ID
        storage.move(id1, id2);
        boolean exists1 = storage.exists(id1);
        boolean exists2 = storage.exists(id2);

        // 8. Get all stored IDs
        String[] ids = storage.getIds();
        for (String id : ids) {
            System.out.println(id);
        }

        // 9. Remove an entry
        storage.remove(id2);
        boolean existsRemoved = storage.exists(id2);

        // 10. Store and remove another entry
        try (OutputStream os = storage.store(id3)) {
            os.write("Temporary data".getBytes());
        }
        storage.remove(id3);

    } catch (IOException | IllegalArgumentException e) {
        e.printStackTrace();
    }

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

