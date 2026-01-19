.. _kernel_faq:

FAQ
===

Frequently asked questions during Kernel and Applications development.

Glossary
--------

- **App**: Sandboxed Application.
- **VEE**: Virtual Execution Environment.
- **KF**: Kernel Framework.
- **FO/FSO**: Feature Object / Feature Shared Object (Application binaries).

Security & Sandboxing
---------------------

.. dropdown:: How do I ensure that apps written by 3rd party developers are secured from each other and from the main body of other device code, especially with no HW MMU to enforce memory protection?
    :animate: fade-in-slide-down

    MEJ32 container, with the KF extension enabled, prevents an app from accessing another app's assets 
    (objects, threads, code, resources, etc.). This is done by design.

    The two main rules that illustrate this are:
    - An app cannot access an object of another app; otherwise, an exception ``java.lang.IllegalAccessError`` is generated.
    - An app can only call its own code and the Runtime Environment APIs (methods) that are explicitly exposed by the Kernel.

.. dropdown:: How is the code of apps secured from the rest of the device code?
    :animate: fade-in-slide-down

    MEJ32 container implements a "Software MMU". The code is so-called "managed code", and no direct-to-memory pointers are manipulated.
    
    The container executes managed code that only triggers (under its control) hardware read or write memory instructions in the dedicated memory sections (where the MEJ32 container heap is placed).
    
    MEJ32 memory sections are defined at link-time. See the list of :ref:`MEJ32 sections <core_engine_link>`.

.. dropdown:: How do we protect against malicious code injection in the app?
    :animate: fade-in-slide-down

    Any built app binary goes through the ``Binary Code Verifier`` tool, whose semantics & principles have been 
    formally proven mathematically.
    After verification, the pre-linked app must be placed in a location where its integrity is maintained.
    
    An on-device signing and checksum comparison can be set up before execution to enforce integrity checks.

.. dropdown:: Can you outline what the integrity check does?
    :animate: fade-in-slide-down

    The integrity check is performed by MEJ32 before an app starts.
    
    It is a basic checksum computation on the linked app content.
    This ensures the app's memory has not been altered after the installation phase, before booting.

.. dropdown:: Is it possible to introduce app signatures for security?
    :animate: fade-in-slide-down

    Yes, MicroEJ provides an app signature mechanism. After the build process, the application binary (``.fo``) is signed (the ``.fo``file is wrapped in a ``.fo.signed``file).
 
    Once the application is available on the device, the ``.fo.signed`` authenticity is verified before installing it.
 
    Contact `our support team <https://www.microej.com/contact/#form_2>`_ for implementing this feature in your product.

.. dropdown:: I want to open app development to 3rd parties. Can I set up Kernel API access control?
    :animate: fade-in-slide-down

    Yes, API access control is done using the Standard Java Security Manager mechanism.
    
    Most libraries provided by MicroEJ already implement a security checkpoint before accessing native resources (e.g., Socket creation, File access, ...).
    
    You can add your own security checks for custom APIs. See instructions in :ref:`securitymanager_permission_check`
    and :ref:`applicationSecurityPolicy`.

.. dropdown:: How is security managed?
    :animate: fade-in-slide-down

    The managed code runs on a formally verified virtual processor (MEJ32), and the multi-sandboxed system isolates each app.
    A kernel manages app lifecycles and controls access to resources through a security manager.

.. dropdown:: How to prevent man-in-the-middle attacks during app deployment on the device?
    :animate: fade-in-slide-down

    Just like any data sent over the devices, the app must be encrypted before sent to the network and decrypted on the device.
    This is usually done automatically when the app is transferred using a protocol that natively supports encryption (e.g. SSL/HTTPS...).
    
    Otherwise, this can be done on the device either in the BSP side or in Managed Code using the `crypto API's <https://repository.microej.com/javadoc/microej_5.x/apis/javax/crypto/package-summary.html>`_.

.. dropdown:: What is the recommended TLS architecture for applications: end-to-end encryption from the application to the cloud, or a segmented approach terminated at a network gateway?
    :animate: fade-in-slide-down

    MICROEJ VEE supports a flexible security model based on the definition of a "safe area."
    Within this safe internal network (e.g. a secure area behind a local headend or gateway),
    communication may be kept unencrypted to reduce the overhead on resource-constrained devices.
    
    However, once traffic leaves this "safe area" and traverses the public internet or untrusted segments,
    encryption over a secure transport layer (such as TLS) is mandatory.

.. dropdown:: What kind of isolation exists between applications?
    :animate: fade-in-slide-down

    MEJ32 implements the KF specification, ensuring applications are fully isolated from each other by design.
    Applications cannot keep direct references to objects owned by other Applications, allowing the Kernel to dynamically stop / uninstall an application.


Inter-App Communication & APIs
------------------------------

.. dropdown:: What is the recommended method for calls (RPC / IPC) between applications?
    :animate: fade-in-slide-down

    MEJ32 provides a built-in mechanism called Shared Interfaces.
    
    This mechanism is governed by access policies, managed by the kernel's security manager.

    See :ref:`chapter.shared.interfaces` for more details.

.. dropdown:: How can we recognize and differentiate installed applications?
    :animate: fade-in-slide-down

    When the Kernel installs an Application, it returns a ``Feature`` object that represents the application execution context.
    The Kernel can keep a map between the Feature provenance/identification and the Feature object.
    
    In the Security Manager check method or any Kernel code, you can get the caller using ``Kernel.getContextOwner()``.

.. dropdown:: Is there a way to extend Kernel APIs? (provide new APIs in new libraries dynamically)
    :animate: fade-in-slide-down

    The Kernel APIs are fixed and cannot be extended directly. Updating a Kernel API means updating the full kernel // device firmware.
    
    Several options exist to mitigate that:
    
    1. Expose an "extendable" interface in the Kernel as a Kernel API.
       Use a dedicated application that provides a service (a.k.a an implementation of this interface).
       Use this service from other applications.
    2. Provide App-to-App services using the :ref:`chapter.shared.interfaces` mechanism.


Scheduling & Resource Management
--------------------------------

.. dropdown:: What is the behavior of the scheduler when several apps are running?
   :animate: fade-in-slide-down

    The Core Engine uses a priority-preemptive scheduling policy with round-robin time-slicing for equal-priority threads.
    (see https://docs.microej.com/en/latest/ApplicationDeveloperGuide/runtime.html?#scheduler).
    All threads have the same priority by default, so none will prevent the others from executing.
    However, a thread's priority can be customized either when creating the thread with 
    a specific constructor or dynamically by calling ``Thread.setPriority()``.

    In a multi-sandbox context, the Kernel can block the usage of the methods that set the priority.
    Therefore, all application threads have the same priority, and the round-robin ensures that they are all executed.

    Specific cases to consider are callbacks owned by an application and called from a Kernel thread.
    In such a case, the Kernel thread's priority is used. To avoid any potential issues, in our framework,
    we delegate the execution of all callbacks to an application-owned thread.

    If you require more fine-tuned scheduling, you can customize thread priorities and use the quotamechanism to ensure that an application won't monopolize the CPU. 
    To achieve that, a Kernel can assign an execution quota to an application using ``Feature.setExecutionQuota()``.
    The quota is expressed in execution units. When an application reaches its execution quota, 
    its execution is suspended until all other applications have reached their execution quota. 
    When there are no eligible application threads available to be scheduled, 
    the execution counter of all applications is reset.
    Setting an application execution quota to 0 suspends the application (i.e., pauses it).

.. dropdown:: How does the scheduler behave with multiple applications?
    :animate: fade-in-slide-down

    The Core Engine uses a priority preemptive scheduling policy with round-robin time-slicing for equal-priority threads.
    
    In a multi-sandbox context, the Kernel can block the use of APIs such as ``Thread.setPriority()``,
    ensuring that all application threads have the same priority.

    Callbacks owned by an application and called from a Kernel thread use the Kernel thread's priority, but the execution is delegated to an application-owned thread to prevent issues.
    
    For more fine-tuned scheduling, you can use the quota mechanism via `Feature.setExecutionQuota() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Feature.html#setExecutionQuota-long->`_.

.. dropdown:: How are execution quotas incremented?
   :animate: fade-in-slide-down

    When execution counting is enabled, execution quotas are incremented at branching instructions
    (Method invocation, Method return, Object Allocation, Internal method back jumps (a.k.a Loops)). 
    When the virtual machine steps into a native, the quota stops incrementing until 
    the native operations are complete and the native has been exited.

.. dropdown:: How to estimate RAM usage for an ``.fso`` build?
    :animate: fade-in-slide-down

    The required RAM is proportional to the ``.fso`` size, but can vary depending on code/resources. A ratio of about ``3.5x`` the ``.fso`` size has been observed.
    
    Use the heap monitoring tools to measure RAM usage on your VEE Port.

.. dropdown:: How does MicroEJ handle high-resolution sampling data?
    :animate: fade-in-slide-down

    Metrology data is reified as streams from the application point of view.
    A publish/subscribe pattern is commonly used to share data with apps.
    Multiple resolution channels can be created depending on the system architecture.

App Deployment & Compatibility
------------------------------

.. dropdown:: When using dynamic loading for ``.fo`` (Feature Object) files, how is compatibility ensured to prevent runtime linking errors?
    :animate: fade-in-slide-down

    By default, the system validates compatibility before linking.
    If a "wild" Kernel update occurs (e.g., the Kernel is updated to a version without regenerating the associated ``.fo`` files),
    the ``.fo`` files will **only** link if they are strictly compatible with the new Kernel.
    
    This is managed via the **Feature Portability Control**. The system performs a check between the **Kernel UIDs** supported by the current Kernel and the specific Kernel UID against which the ``.fo`` was originally built.
    
    Unlike a simple MD5 hash of the file, this check ensures the binary interfaces and dependencies match.
    If the new Kernel has activated :ref:`feature_portability_control`,
    it will strictly enforce these UID matches at "Kernel boot time" or during installation.

.. dropdown:: What happens if a ``.fo`` or ``.fso`` is found to be incompatible? Is there an event or programmatic way to detect this?
    :animate: fade-in-slide-down

    If an incompatibility is detected during the installation process, the system does not fail silently; instead, it raises a specific **Exception**.
    
    When calling the ``Kernel.install()`` method, the runtime performs the compatibility check.
    If the Kernel UIDs do not match or the Feature Portability requirements are not met, an exception is thrown,
    allowing the Kernel to handle the error programmatically (e.g., by logging the error, notifying a management server, deleting the incompatible app, ...).
    
    You can find the list of possible exceptions in the `ej.kf.Kernel Javadoc <https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#install-java.io.InputStream->`_.

.. dropdown:: My Kernel already embeds the ``widget`` library as a Kernel API. I am writing an application and added a dependency on the ``widget`` library to use it. Will the code of the library be embedded into my app again?
    :animate: fade-in-slide-down

    No. According to the Kernel & Features semantics, a class exposed as a Kernel API is considered before
    a class loaded from the application classpath. So the ``widget`` library will not be embedded twice.  

    However, if only a subset of the ``widget`` library classes are open as Kernel APIs,
    all other classes used by your application will be embedded into your application code.

.. dropdown:: Can I pre-install applications in my device firmware?
    :animate: fade-in-slide-down

    Technically, yes, the usual way to prepare the flash image with pre-installed applications consists of running the kernel,
    installing the desired applications and then dumping the whole flash contents
    (at least the sections containing the kernel + installed apps) into a binary file.
    
    This "Device ROM" can then be sent to the factory for production.

.. dropdown:: Can the kernel access the app's resources before they are started?
    :animate: fade-in-slide-down

    No, the kernel cannot access app resources before they are started.
    
    Such resources are usually called "application metadata" and must be managed outside of the app image file. Often, this is done during a provisioning phase.
    If you need to access resources before a feature is started, consider using a provisioning phase or storing metadata in a separate location.
    
    No, the kernel cannot access app resources before they are started.
 
    Such resources are usually called "application metadata" and must be managed outside of the app image file. Often, this is done during a provisioning phase.
    If you need to access resources before a feature is started, consider using a provisioning phase or storing metadata in a separate location.
 
    However, the ``Feature.getResourceAsStream("resource_path")``method allows access to
    resources as soon as the app is installed (not yet started).

.. dropdown:: How to access application metadata before installing it? (e.g. name, version, description)
    :animate: fade-in-slide-down

    A custom mechanism should be implemented.
    
    Metadata should be provided alongside the application binary during deployment.

    For example, by wrapping the application binary and the metadata file in a ``.zip`` archive.

.. dropdown:: How are versioning checks handled for applications?
    :animate: fade-in-slide-down

    Each Sandboxed Application must define a KF declaration file named ``[name].kf``.
    This is a property file that defines the application name, version, and entryPoint.
    
    Since ``SDK6 1.5.0``, this ``[name].kf`` file is generated automatically during the build process:
    
    - The version of the application corresponds to the version defined in the application ``build.gradle.kts`` file.
    - The name of the application corresponds to the name of the entryPoint class of the application.
    
    That information can be overridden; refer to :ref:`kf-feature-declaration` for more information.
    
    The kernel can retrieve that information after application installation (before starting it),
    using the the `Module.getVersion() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Module.html#getVersion-->`_ and `Module.getName() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Module.html#getName-->`_ APIs.

.. dropdown:: What is the process for verifying applications?
    :animate: fade-in-slide-down

    Applications are verified using the ``SOAR`` tool, which performs bytecode verification and ensures the app only calls APIs exposed by the kernel.
    
    The ``SOAR`` tool does not require access to the source code, as it checks the bytecode for tampering detection.
    
    The process involves:
    
    1. Running the Dependency Discoverer to list all classes and methods the app relies on.
    2. Checking resources against corporate policy.
    3. Running the ``SOAR`` to generate the application binary (``.fo``), ready for packaging/signing/deployment.

.. dropdown:: What is the lifecycle of an application?
    :animate: fade-in-slide-down

    Applications can be installed, stopped, started, and uninstalled.
    
    See :ref:`kernel_application_lifecycle` for more information.

.. dropdown:: Can applications be used across different vendors?
    :animate: fade-in-slide-down

    Yes. MICROEJ VEE is a software container that leverages virtualization to create an ISA-agnostic execution model,
    enabling applications to be semantically binary-portable across different vendors.

..
   | Copyright 2026, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.

