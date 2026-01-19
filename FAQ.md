## Glossary

- app: Sandboxed Application

### Question
My Kernel already embeds the ``widget`` library as a Kernel API. 
I am writing an application and I added a dependency to the ``widget`` library to use it. Will the code be embedded again into my app?

### Answer
No. According to the Kernel & Features semantic, a class that is exposed as Kernel API is taken into account prior to a class loaded from the application classpath. So the ``widget`` library will not be embedded twice.

However, if only a subset of the ``widget`` library classes are open as Kernel APIs,
all other classes used by your application will be embedded into your application code.

### Question
How do I ensure that app written by 3rd party developers are secured from each other and from the main body of other device code,
especially with no HW MMU to enforce memory protection?

### Answer
MEJ32 container, with the KF extension activated, ensures that an app cannot access the assets of another app (objects, threads, code, resources, etc.). This is done by design.

The two main rules that illustrate this are:
- An app cannot access an object of another app; otherwise, an exception ``java.lang.IllegalAccessError`` is generated.
- An app can only call its own code and the Runtime Environment APIs (methods) that are explicitly exposed by the Kernel.

### Question
How is the code of apps secured from the rest of the device code?

### Answer
MEJ32 container implements a "Software MMU". The code is so called "managed code", and no direct-to-memory pointers are manipulated.

The container executes managed code that only triggers (under its control) hardware read or write memory instructions in the dedicated memory sections (where the MEJ32 container heap is placed).

MEJ32 memory sections are defined at link-time. See the list of MEJ32 sections [here](https://docs.microej.com/en/latest/VEEPortingGuide/coreEngine.html#link).

### Question
How do we protect against malicious code injection in the app? 

### Answer
Any built app binary goes through the ``Binary Code Verifier`` tool, which semantic & principle have been mathematically formally proven.
After verification, the pre-linked app must be placed in a location where its integrity is maintained.

An on device signing and checksum comparison can be setup before execution to enforce integrity checks.

### Question

How to prevent man-in-the-middle attacks during app deployment on the device?

### Answer

Just like any data sent over the devices, the app must encrypted before sent to the network and decrypted on the device.
This is usually done automatically when the app is transferred using a protocol that natively supports encryption (e.g. SSL/HTTPS...).

Otherwise, this can be done on the device either in the BSP side or in Managed Code using the crypto API’s (https://repository.microej.com/javadoc/microej_5.x/apis/javax/crypto/package-summary.html)

### Question

What is the recommended TLS architecture for applications:
end-to-end encryption from the application to the cloud, or a segmented approach terminated at a network gateway?

### Answer

MICROEJ VEE supports a flexible security model based on the definition of a "safe area."
Within this safe internal network (e.g., a secure area behind a local headend or gateway),
communication may be kept unencrypted to reduce the overhead on resource-constrained devices.

However, once traffic leaves this "safe area" and traverses the public internet or untrusted segments, 
encryption over a secure transport layer (such as TLS) is mandatory.

### Question 

When using dynamic loading for ``.fo`` (Feature Object) files, how is compatibility ensured to prevent runtime linking errors?

### Answer

By default, the system validates compatibility before linking. 
If a "wild" Kernel update occurs (e.g., the Kernel is updated to version without regenerating the associated ``.fo`` files), 
the ``.fo`` files will **only** link if they are strictly compatible with the new Kernel.

This is managed via the **Feature Portability Control**. The system performs a check between the **Kernel UIDs** supported by the current Kernel and the specific Kernel UID against which the ``.fo`` was originally built.

Unlike a simple MD5 hash of the file, this check ensures the binary interfaces and dependencies match. 
If the new Kernel has activated [Feature Portability Control](https://docs.microej.com/en/latest/KernelDeveloperGuide/kernelLink.html#feature-portability-control),
it will strictly enforce these UID matches at "Kernel boot time" or during installation. 

### Question

What happens if a ``.fo`` or ``.fso`` is found to be incompatible? Is there an event or programmatic way to detect this?

### Answer

If an incompatibility is detected during the installation process, the system does not fail silently; instead, it raises a specific **Exception**.

When calling the ``Kernel.install()`` method, the runtime performs the compatibility check. 
If the Kernel UIDs do not match or the Feature Portability requirements are not met, an exception is thrown, 
allowing the Kernel to handle the error programmatically (e.g., by logging the error, notifying a management server, deleting the incompatible app, ...).

You can find the list of possible exceptions in the [ej.kf.Kernel Javadoc](https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#install-java.io.InputStream-).

### Question
Can the kernel access app's resources before they are started?

### Answer
No, the kernel cannot access app resources before they are started.

Such resources are usually called "application metadata" and must be managed outside of the app image file. Often, this is done during a provisioning phase.
If you need to access resources before a feature is started, consider using a provisioning phase or storing metadata in a separate location.

However, the ``Feature.getResourceAsStream("resource_path")`` allows access to resources before as soon as the app is installed (not started yet).

### Question

Can I pre-install applications to in my device firmware?

### Answer

Technically yes, the usual way to prepare the flash image with pre-installed applications consists in running the kernel, 
installing the desired applications and then dumping the whole flash contents
(at least the sections containing the kernel + installed apps) into a binary file.

This "Device ROM" can then be sent to the factory for production.

### Question
Can you outline what the integrity check does?

### Answer
The integrity check is performed by MEJ32 before starting an app.

It is a basic checksum computation on the linked app content.
This ensures the app memory has not been altered after the installation phase before booting on it.

### Question
Is it possible to introduce app signatures for security?

### Answer

Yes, MicroEJ provides an app signature mechanism. After the build process, the application binary (``.fo``) is signed (the ``.fo`` is wrapped into a ``.fo.signed``).

Once the application is available on the device, the ``.fo.signed`` authenticity is checked before installing the application.

Contact `our support team <https://www.microej.com/contact/#form_2>`_ for implementing this feature in your product.

### Question
I want to open app development to 3rd parties, can I setup Kernel APIs access control?

### Answer
Yes, API access control is done using the Standard Java Security Manager mechanism.

Most libraries provided by MicroEJ already implement a security checkpoint before accessing native resources (e.g., Socket creation, File access, ...).

You can add your own security checks for custom APIs. See instructions in [Implement a Security Manager Check](https://docs.microej.com/en/latest/KernelDeveloperGuide/kfEnabledLibraries.html#implement-a-security-manager-check) and [Define a Security Policy](https://docs.microej.com/en/latest/KernelDeveloperGuide/applicationSecurityPolicy.html).

### Question
How can we recognize and differentiate installed applications?

### Answer
When the Kernel installs an Application, it returns a ``Feature`` object that represents the application execution context. 
The Kernel can keep a map between the Feature provenance/identification and the Feature object.

In the Security Manager check method or any Kernel code, you can get the caller using ``Kernel.getContextOwner()``.

### Question
Is there a way to extend Kernel APIs? (provide new APIs are new libraries dynamically)

### Answer
The Kernel APIs are fixed and cannot be extended directly. Updating a Kernel API means updating the full kernel // device firmware.

Several options exist to mitigate that:

1. Expose an "extendable" interface in the Kernel, as a Kernel API.
   Use a dedicated application that provides a service (a.k.a an implementation of this interface).
   Use this service from other applications.
2. Provide App-to-App services using the [Sandboxed App Shared Interface](https://docs.microej.com/en/latest/ApplicationDeveloperGuide/sandboxedAppSharedInterface.html) mechanism.

### Question
What is the recommended method for calls (RPC / IPC) between applications?

### Answer
MEJ32 provides a built-in mechanism called Shared Interfaces. 

This mechanism is ruled by access policies, managed by the security manager of the kernel.

See [Sandboxed App Shared Interface](https://docs.microej.com/en/latest/ApplicationDeveloperGuide/sandboxedAppSharedInterface.html) for more details.

### Question
What kind of isolation exists between applications?

### Answer
MEJ32 implements the KF specification, ensuring applications are fully isolated from each other, by design. 
Applications cannot keep direct references to objects owned by other Applications, allowing the Kernel to dynamically stop / uninstall an application.

### Question
How does the scheduler behave with multiple applications?

### Answer
The Core Engine uses a priority preemptive scheduling policy with round-robin time-slicing for equal-priority threads.

In a multi-sandbox context, the Kernel can block the usage of APIs like ``Thread.setPriority()``, ensuring all application threads have the same priority.

Callbacks owned by an application and called from a Kernel thread use the Kernel thread's priority, but the execution is delegated to an application-owned thread to prevent issues.

For more fine-tuned scheduling, you can use the quota mechanism via `Feature.setExecutionQuota()`.

### Question
What is the process for verifying applications?

### Answer
Applications are verified using the ``SOAR`` tool, which performs bytecode verification and ensures the app only calls APIs exposed by the kernel.

The ``SOAR`` tool does not require access to the source code, as it checks the bytecode for tampering detection.

The process involves:

1. Running the Dependency Discoverer to list all classes and methods the app relies on.
2. Checking resources against corporate policy.
3. Running the ``SOAR`` to generate the application binary (``.fo``), ready for packaging/signing/deployment.

## FSO Size Estimation

### Question
How to estimate RAM usage for an ``.fso`` build?

### Answer
The required RAM is proportional to the ``.fso`` size, but can vary based on code/resources. A ratio of about ``3.5x`` the ``.fso`` size has been observed.

Use the heap monitoring tools to measure RAM usage on your VEE Port.

## Portability and Architecture

### Question
Can apps be used across different vendors?

### Answer
Yes. MICROEJ VEE is a software container that leverages virtualization to create an ISA-agnostic execution model, making applications semantically binary portable across different vendors.

### Question
How is security managed?

### Answer
The managed code is inside a formally proven virtual processor (MEJ32), and the multi-sandboxed system isolates each app. A kernel manages app lifecycles and controls access to resources through a security manager.

### Question
How does MicroEJ handle high-resolution sampling data?

### Answer
Metrology data is reified as streams of data.
Most customers use a publish/subscribe pattern to share data with apps.
Multiple resolution channels can be created depending on the system architecture.

### Question
What is the architecture of MicroEJ?

### Answer
For a high-level overview, refer to the VEE Energy slide in the presentation.

### Question
What are the minimum requirements for processor, memory, and RAM?

### Answer
MicroEJ can run on MCUs like Cortex M0+ up to Cortex M7 and application processors like ARMv7 or ARMv8.

MEJ32 requires only 30KB of code and 1KB of RAM. Typical memory usage is defined by the application.

### Question
How does MicroEJ scale with multi-core CPUs?

### Answer
MicroEJ supports heterogeneous multi-cores from Cortex-M0+ with RTOS to Cortex-A with Linux or QNX.

### Question
How are patches handled and how is the environment secured?

### Answer
The Core technology is rarely patched due to maturity and extensive testing.

We release new editions on a 9-12 month cadence, with bug fixes delivered quickly.

We have a process for reporting vulnerabilities, and they are tracked and reported in our changelog.

### Question
How are versioning checks handled for applications?

### Answer

Each Sandboxed Application must define a KF declaration file named ``[name].kf``. 
This is a property file that defines the application name, version and entryPoint.

Since SDK6 1.5.0, this ``[name].kf`` file is generated automatically during the build process:

- The version of the application corresponds to the version defined in the application ``build.gradle.kts`` file.
- The name of the application corresponds to the name of the entryPoint class of the application.

Those information can be overridden, refer to: https://docs.microej.com/en/latest/KernelDeveloperGuide/kf.html#kernel-and-features-declaration for more information.

The kernel can retrieve those information after application installation (before starting it),
using the the `Module.getVersion()`_ and `Module.getName()`_ APIs.

### Question

How to access application metadata before installing it? (e.g. name, version, description)

### Answer

A custom mechanism should be implemented.

Metadata should be provided next to the application binary file during deployment.

For example, by wrapping the application binary and the metadata file in a ``.zip`` archive.

### Question
What is the lifecycle of an application ?

### Answer

Applications can be installed, stopped, started, and uninstalled.

See https://docs.microej.com/en/latest/KernelDeveloperGuide/sandboxedAppLifecycle.html for more information.


.. _Module.getVersion(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Module.html#getVersion--
.. _Module.getName(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Module.html#getName--
