.. _chapter.java_time:

.. _Instant: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/Instant.html
.. _LocalDate: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/LocalDate.html
.. _LocalTime: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/LocalTime.html
.. _LocalDateTime: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/LocalDateTime.html
.. _ZonedDateTime: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/ZonedDateTime.html
.. _Duration: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/Duration.html
.. _Period: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/Period.html
.. _Date: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Date.html
.. _Calendar: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Calendar.html
.. _TimeZone: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/TimeZone.html
.. _ZoneRulesException: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/zone/ZoneRulesException.html
.. _ZoneRulesProvider: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/zone/ZoneRulesProvider.html
.. _ZoneRules: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/zone/ZoneRules.html
.. _ZoneId: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/ZoneId.html
.. _ZoneOffset: https://repository.microej.com/javadoc/microej_5.x/apis/java/time/ZoneOffset.html

Date and Time
=============

Introduction
------------

Java developers have long used the `Date`_, `Calendar`_ and `TimeZone`_ classes for handling date and time. 
Java SE 8 introduced a more advanced and comprehensive Date and Time API that goes beyond simply replacing `Date`_ or `Calendar`_. 
It provides a complete time model for applications.

There are many benefits of using the latest:

* Immutability: types are immutable, making thread-safe code easier to write and less prone to bugs (due to no mutable state).
* Improved API design: it offers an intuitive and developer-friendly design that better addresses the challenges of date and time manipulation. Application code is also easier to read and understand.
* Simplified date and time arithmetic: the API introduces methods for common date and time operations, simplifying tasks like adding or subtracting days, months, or years.
* Precision: it provides more precise representations for date and time values, including support for nanoseconds, which is important for applications requiring high precision.
* Comprehensive time model: it introduces new classes that deal with different concepts of time such as date without a time or time without a date, durations or periods.

In general, it's a good practice to use the ``Java Time API`` when dealing with date, time, and time zone-related operations because of its convenient features and extensive capabilities.
Yet, for straightforward timestamp handling or lightweight applications, ``System.currentTimeMillis()`` can be adequate. 
One aspect to keep in mind is that the Time API offers better readability and advanced operations, which might be missing when using timestamp manipulation or older APIs.


Overview
--------

The library introduces different classes for date, time, date-time, and variations for offset and time zone. 
While this may seem like a lot of classes, most applications can start with only these types:

- `Instant`_: an instantaneous point on the timeline. It can be used to store timestamps of application events.
- `LocalDate`_: stores a date without a specific time or time zone, like ``2023-09-26``.
- `LocalTime`_: stores a time without a specific date or time zone, like ``15:30``.
- `LocalDateTime`_: stores both a date and time without a specific time zone, like ``2023-09-26T15:30``. It combines `LocalDate`_ and `LocalTime`_.
- `ZonedDateTime`_: stores both a date and time, including a time zone. This is handy for performing precise date and time calculations while considering the time zone.
- `Duration`_: a duration of time, measured in hours, minutes, seconds, and nanoseconds.
- `Period`_: a duration of time in terms of years, months, and days.

.. note::
    Working with a time zone can make calculations more complex. In many cases, the application can only work with `LocalDate`_, `LocalTime`_, and `Instant`_, and then add the time zone at the user interface (UI) level.


The API has many methods, but it remains easy to handle because it sticks to consistent method prefixes:

- ``of``: static factory method.
- ``get``: gets a value.
- ``is``: checks if some condition is true.
- ``with``: equivalent to a setter for immutable objects, returns a copy with the specified argument set.
- ``plus``: adds an amount to an object.
- ``minus``: subtracts an amount from an object.
- ``to``: converts this object to another type.
- ``at``: combines this object with another. 


Usage
-----

The Date and Time API is provided as an Add-on Library.

To use the `time <https://repository.microej.com/modules/ej/library/eclasspath/time/>`_ library, add the following to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.library.eclasspath:time:1.1.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.library.eclasspath" name="time" rev="1.1.0"/>



Examples
--------

This section presents a series of small, focused examples that demonstrate various aspects of the Java Date and Time API. 

Instant
~~~~~~~

The `Instant`_ class is the closest equivalent of `Date`_. It represents a specific instant in time.

.. code-block:: java

    // Creating instants
    Instant now = Instant.now(); // now
    Instant someInstant = Instant.ofEpochSecond(1695732445L); // September 26, 2023 12:47:25 PM

    // Displaying 
    System.out.println("Seconds elapsed since epoch " + now.getEpochSecond());

    // Chaining operations on instants
    long secondsUntil = someInstant.plusSeconds(10).until(now, ChronoUnit.SECONDS);
    System.out.println("Amount of time until another instant in seconds: " + secondsUntil);



LocalDate
~~~~~~~~~

`LocalDate`_ stores a date without a time. It is called "local" because it isn't associated with any specific time zone, similar to a wall clock.
It simplifies date operations by dealing only with dates, making it suitable for scenarios not requiring time zone concerns (e.g., booking systems, calendars, date validation, etc.).

.. code-block:: java

    // Creating LocalDate instances
    LocalDate today = LocalDate.now(); // Current date
    LocalDate specificDate = LocalDate.of(2023, Month.JULY, 15); // July 15, 2023
    
    // Displaying LocalDate instances
    System.out.println("Today's Date: " + today);
    System.out.println("Specific Date: " + specificDate);
    
    // Performing operations
    LocalDate futureDate = today.plusDays(30); // Adding 30 days to today
    LocalDate pastDate = today.minusMonths(2); // Subtracting 2 months from today
    
    // Displaying the results of operations
    System.out.println("Date 30 days from today: " + futureDate);
    System.out.println("Date 2 months ago from today: " + pastDate);
    
    // Comparing LocalDate instances
    boolean isAfter = specificDate.isAfter(today); // Check if specificDate is after today
    
    // Displaying comparison results
    System.out.println("Is specificDate after today? " + isAfter);

LocalTime
~~~~~~~~~

`LocalTime`_ stores a particular time of day, focusing only on the time (hour, minute, second, nanosecond), and doesn't include date or time zone details. 
Useful when you only need to handle time values without dates or time zones (e.g., scheduling events like alarms, stopwatch and timers, event timing, etc.).

.. code-block:: java

        // Creating LocalTime instances
        LocalTime now = LocalTime.now(); // Current time
        LocalTime specificTime = LocalTime.of(14, 30); // 2:30 PM

        // Displaying LocalTime instances
        System.out.println("Current Time: " + now);
        System.out.println("Specific Time: " + specificTime);

        // Performing operations
        LocalTime futureTime = now.plusHours(3); // Adding 3 hours to the current time
        LocalTime pastTime = now.minusMinutes(15).minusSeconds(29); // Subtracting 15 minutes and 29 seconds from the current time

        // Displaying the results of operations
        System.out.println("Time 3 hours from now: " + futureTime);
        System.out.println("Time 15 minutes ago: " + pastTime);

        // Displaying time fields
        System.out.println("Hour: " + now.getHour());
        System.out.println("Minute: " + now.getMinute());
        System.out.println("Second: " + now.getSecond());

LocalDateTime
~~~~~~~~~~~~~

`LocalDateTime`_ combines both date and time components and provides a precise timestamp. 
This makes it suitable for scenarios where you need to work with both date and time information, but without considering time zone conversions (e.g., timestamping, user interfaces, etc.). 

.. code-block:: java

        // Creating LocalDateTime instances
        LocalDateTime now = LocalDateTime.now(); // Current date and time
        LocalDateTime specificDateTime = LocalDateTime.of(2023, Month.JULY, 15, 14, 30); // July 15, 2023, 2:30 PM

        // Displaying LocalDateTime instances
        System.out.println("Current Date and Time: " + now);
        System.out.println("Specific Date and Time: " + specificDateTime);

        // Performing operations
        LocalDateTime futureDateTime = now.plusDays(30).plusHours(3); // Adding 30 days and 3 hours to now
        LocalDateTime pastDateTime = now.minusMonths(2).minusMinutes(15); // Subtracting 2 months and 15 minutes from
                                                                        	// now
        // Displaying the results of operations
        System.out.println("Date and Time 30 days and 3 hours from now: " + futureDateTime);
        System.out.println("Date and Time 2 months and 15 minutes ago from now: " + pastDateTime);

        // Displaying date and time fields
        System.out.println("Year: " + now.getYear());
        System.out.println("Month: " + now.getMonth());
        System.out.println("Day of Month: " + now.getDayOfMonth());
        System.out.println("Hour: " + now.getHour());
        System.out.println("Minute: " + now.getMinute());
        System.out.println("Second: " + now.getSecond());
        System.out.println("Day of Year: " + now.get(ChronoField.DAY_OF_YEAR));
        System.out.println("Day of Week: " + now.get(ChronoField.DAY_OF_WEEK));
        
        // Displaying comparison results
        System.out.println("Is specificDateTime after current date and time? " + specificDateTime.isAfter(now));


Duration
~~~~~~~~

`Duration`_ represents a duration of time, typically measured in hours, minutes, seconds, and nanoseconds. 
It is used to calculate and work with time intervals, such as the amount of time between two points in time or the duration of an event. 
It is suitable for tasks involving precise timing, such as measuring time elapsed or setting timeouts.

.. code-block:: java

        // Creating Duration instances
        Duration fiveHours = Duration.ofHours(5); // Duration of 5 hours
        Duration thirtyMinutes = Duration.ofMinutes(30); // Duration of 30 minutes
        Duration twoSeconds = Duration.ofSeconds(2); // Duration of 2 seconds

        // Displaying Duration instances
        System.out.println("5 Hours: " + fiveHours);
        System.out.println("30 Minutes: " + thirtyMinutes);
        System.out.println("2 Seconds: " + twoSeconds);

        // Performing operations
        Duration combinedDuration = fiveHours.plus(thirtyMinutes).plusSeconds(10); // Adding durations
        Duration subtractedDuration = fiveHours.minus(twoSeconds); // Subtracting durations

        // Displaying the results of operations
        System.out.println("Combined Duration: " + combinedDuration);
        System.out.println("Subtracted Duration: " + subtractedDuration);

        // Displaying duration fields
        System.out.println("Hours: " + combinedDuration.toHours());
        System.out.println("Minutes: " + combinedDuration.toMinutes());
        System.out.println("Seconds: " + combinedDuration.getSeconds());

        // Comparing Duration instances
        boolean isLonger = fiveHours.compareTo(thirtyMinutes) > 0; // Check if fiveHours is longer than thirtyMinutes
        boolean isEqual = fiveHours.equals(Duration.ofHours(5)); // Check if fiveHours is equal to 5 hours

        // Displaying comparison results
        System.out.println("Is fiveHours longer than thirtyMinutes? " + isLonger);
        System.out.println("Is fiveHours equal to 5 hours? " + isEqual);



Period
~~~~~~

`Period`_  represents a duration of time in terms of years, months, and days.
It is primarily concerned with human-centric time measurements, like the length of a month or a year.
It is well-suited for measuring time intervals within a calendar context. 
For example, it can represent periods such as 2 years, 3 months, and 5 days.

.. code-block:: java

        // Creating LocalDate instances
        LocalDate date1 = LocalDate.of(2021, 6, 15); // June 15, 2021
        LocalDate date2 = LocalDate.of(2023, 9, 25); // September 25, 2023

        // Calculating the period between two dates
        Period period = Period.between(date1, date2);

        // Displaying the period
        System.out.println("Period between " + date1 + " and " + date2 + ": " + period);

        // Displaying period fields
        System.out.println("Years: " + period.getYears());
        System.out.println("Months: " + period.getMonths());
        System.out.println("Days: " + period.getDays());

        // Creating Period instances using factory methods
        Period customPeriod = Period.of(2, 3, 5); // 2 years, 3 months, and 5 days

        // Displaying the custom period
        System.out.println("Custom Period: " + customPeriod);

        // Performing operations on periods
        Period addedPeriod = period.plus(customPeriod); // Adding periods
        Period subtractedPeriod = period.minus(customPeriod); // Subtracting periods

        // Displaying the results of operations
        System.out.println("Added Period: " + addedPeriod);
        System.out.println("Subtracted Period: " + subtractedPeriod);

        // Comparing Period instances
        boolean isEqual = customPeriod.equals(Period.of(2, 3, 5)); // Check if customPeriod is equal to 2 years, 3 months, and 5 days

        // Displaying comparison results
        System.out.println("Is customPeriod equal to 2 years, 3 months, and 5 days? " + isEqual);


Time Zone Support
-----------------

The Time API introduces multiple types for time zone management:

- `ZoneId`_ : represents a time zone identifier: a fixed offset (e.g., ``+0200``) or a geographical region (e.g., ``Africa/Johannesburg``).
- `ZoneOffset`_ :  represents a fixed time zone offset from UTC, usually a fixed number of hours and minutes.
- `ZonedDateTime`_ : a date time with a time zone: the combination of a `LocalDateTime`_ and a `ZoneId`_.
- `ZoneRules`_ : defines the offsets from UTC, the daylight saving time rules, and how they change over time, for a specific time zone.
- `ZoneRulesProvider`_ : provides the time zone rules to all the zone-aware classes of the library. Meant to be implemented by custom time zone rule providers.

Default Zone Rules Provider
~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, the library uses a lightweight provider designed to handle only the time zone rules for ``GMT`` (Greenwich Mean Time).
This is suitable for operations on dates and times that do not depend on time zone considerations.
This provider only supports the ``GMT`` zone ID. Any attempt to get a different zone ID will throw a `ZoneRulesException`_.
For example,

.. code-block:: java

   ZoneId.of("GMT"); // ok
   ZoneId.of("+0200"); // ok
   ZoneId.of("GMT+0530"); // ok
   ZoneId.of("PST"); // throws ZoneRulesException
   ZoneId.of("CST-0115"); // throws ZoneRulesException
   ZoneId.of("Asia/Tokyo"); // throws ZoneRulesException

   Set<String> zoneIds = ZoneId.getAvailableZoneIds(); // returned set contains only "GMT"

TZDB Zone Rules Provider
~~~~~~~~~~~~~~~~~~~~~~~~

The library also defines a provider of zone rules for the time zones defined in the `IANA Time Zone Database <https://www.iana.org/time-zones>`_ (TZDB).

The TZDB provider reads the zones and rules from a raw resource at runtime.
Compared to the ``TzdbZoneRulesProvider`` of Java SE distributions, this implementation uses less Java heap at runtime, making it more suitable for embedded devices.

.. warning::
   The TZDB provider requires a target VEE Port that uses an architecture version ``8.1.1`` minimum (for ``8.x``), or ``7.20.5`` minimum (for ``7.x``).

Using the TZDB Provider
^^^^^^^^^^^^^^^^^^^^^^^

To use this provider, set the constant ``java.time.zone.DefaultZoneRulesProvider`` to ``java.time.zone.TzdbZoneRulesProvider`` in a ``*.constants.list`` file, like below:

.. code-block:: jproperties 

   java.time.zone.DefaultZoneRulesProvider=java.time.zone.TzdbZoneRulesProvider

.. note:: 
   It is also recommended to add the class name ``java.time.zone.TzdbZoneRulesProvider`` to a ``*.types.list`` file: the class name is required to instantiate the provider and can not be known at compile-time.

The raw resource from which the provider reads the zone rules is generated from the timezone database file included in the JDK/JRE installation (``tzdb.dat``).

To generate the resource and use it in an application, do the following:

1. Locate the ``tzdb.dat`` file in a local JDK/JRE installation (``path/to/JRE/lib/tzdb.dat``),
2. Add the ``tzdb.dat`` file to the application resources (e.g., ``src/main/resources/com/mycompany/tzdb.dat``),
3. Create a ``*.tzdb.list`` file in the application resources (e.g., ``src/main/resources/com/mycompany/myapp.tzdb.list``),
4. Open the ``*.tzdb.list`` file and add the path to the ``tzdb.dat`` file (e.g., ``/com/mycompany/tzdb.dat``).

The resource will be automatically generated when building the application or running it in the Simulator.
By default, it will be embedded in the application binary (as an :ref:`internal resource<chapter.microej.applicationResources>`).


.. note:: 

   To get a ``tzdb.dat`` with the most current timezone data available, use the `TZUpdater tool <https://www.oracle.com/java/technologies/downloads/tools/#TZUpdater>`_ and run the following command:
   
   .. code::
      
      java -jar tzupdater.jar -l
   
   The TZUpdater tool updates the JDK/JRE instance that is used to execute the tool: copy ``path/to/JRE/lib/tzdb.dat`` into the application resources, as described above.

   In addition, you can check that the version of the timezone data is correct in the logs of the Add-on Processor that generates the raw resource.

   .. tabs::

      .. tab:: SDK 6

         When running on Simulator or building an executable in verbose mode (with the ``--info`` Gradle option), look in the console for an output similar to:

         .. code:: text
            
            [myapp:tzdb] Successfully deserialized TZDB data: version = 2024a, zones count = 603, resource buffer size = 102532

         where ``2024a`` is the version of the timezone data in this example.

      .. tab:: SDK 5

         The Add-on Processor is executed when changes occur in the resources files.
         Open the Add-on Processor console and set the log level to ``debug``.
         After copying a ``tzdb.dat`` file in the resources files, look in the console for an output similar to:

         .. code:: text
            
            [myapp:tzdb] Successfully deserialized TZDB data: version = 2024a, zones count = 603, resource buffer size = 102532

         where ``2024a`` is the version of the timezone data in this example.


If the TZDB provider can't find the resource, it will throw an exception at runtime:

.. code-block:: java
   
   Exception in thread "main" java.lang.ExceptionInInitializerError: java.lang.IllegalStateException: Cannot open the tzdb binary resource

In this case, follow the steps described above to generate the resource, and make sure that the resource is available at runtime:
when the resource is internal, the ``tzdb`` resource should be listed in the ``Application Resources`` group of the :ref:`SOAR.map<soar_map_file>` file.


Loading the TZDB Data as an External Resource
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The resource can be declared as an external resource to be loaded from another location (e.g. from a FileSystem).
It has to be referenced in a ``*.externresources.list`` file, in which case the SOAR will output the resource in the :ref:`external_resources_folder`. 
See :ref:`chapter.microej.applicationResources` for more information about external resources.

.. warning::
   Loading external resources requires a target VEE Port that uses the :ref:`External Resources Loader<section_externalresourceloader>`.

Follow the steps below to declare the ``tzdb`` resource as an external resource:

- Create a ``*.externresources.list`` file in the ``src/main/resources/`` folder,
- Add the following path to the file:
  
  .. code::
  
   /java/time/zone/tzdb

- Build the application executable,
- The raw resource is now available in the :ref:`external_resources_folder`.
  This resource must be transferred to the target device's memory and loaded from the path ``/java/time/zone/tzdb``, using the :ref:`External Resources Loader<section_externalresourceloader>`.

.. _time_migration_guide:

Migration Guide
---------------

If you're using the legacy date and time classes (`Date`_, `Calendar`_), it's a great time to consider migrating to the new API.
This small migration guide will help you transition from the old time API to the Java Date and Time API (``java.time``). 
It covers some common date and time operations and demonstrates how to perform them using both approaches.

Displaying the Current Date
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Legacy Time API

      .. code-block:: java

        // Create a Calendar instance representing the current date and time
        Calendar calendar = Calendar.getInstance();

        // Get date components from the Calendar
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH) + 1; // Months are 0-based
        int day = calendar.get(Calendar.DAY_OF_MONTH);

        // Display the date
        System.out.println("Current Date: " + year + "-" + month + "-" + day);


   .. tab:: New Time API

      .. code-block:: java

        // Get the current date using LocalDate
        LocalDate currentDate = LocalDate.now();

        // Display the date
        System.out.println("Current Date: " + currentDate);


Calculating a Timestamp from a Date
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Legacy Time API

      .. code-block:: java

        // Create a Calendar instance
        Calendar calendar = Calendar.getInstance();
        calendar.set(2023, 10, 06, 15, 27, 30);     // November 06, 2023 3:27:30 PM
        long timeInMillis = calendar.getTimeInMillis();


   .. tab:: New Time API

      .. code-block:: java

       // Create a LocalDateTime instance with the desired date and time
       LocalDateTime localDateTime = LocalDateTime.of(2023, 10, 06, 15, 27, 30);
       
       // Convert LocalDateTime to a timestamp from Epoch
       long timeInMillis = localDateTime.toInstant(ZoneOffset.UTC).toEpochMilli();


Calculating Date and Time Differences
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Legacy Time API

      .. code-block:: java

        public long computeDifference(Date date1, Date date2){
            return date1.getTime() - date2.getTime();
        }


   .. tab:: New Time API

      .. code-block:: java

        public long computeDifference(LocalDateTime date1, LocalDateTime date2){
            return Duration.between(date1, date2).toMillis();
        }
        


Calculating the Day of the Week
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Legacy Time API

      .. code-block:: java
        
        // Create a Calendar instance
        Calendar calendar = Calendar.getInstance();
        
        // Set a date (e.g., October 15, 2023)
        calendar.set(2023, Calendar.OCTOBER, 15);
        
        // Get the day of the week as an integer (1 = Sunday, 2 = Monday, ..., 7 = Saturday)
        int dayOfWeek = calendar.get(Calendar.DAY_OF_WEEK);


   .. tab:: New Time API

      .. code-block:: java
        
        // Create a LocalDate instance for a specific date (October 15, 2023)
        LocalDate date = LocalDate.of(2023, 10, 15);
        
        // Get the day of the week as an enum value (DayOfWeek)
        DayOfWeek dayOfWeek = date.getDayOfWeek();



Handling Time Zones
~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Legacy Time API

      .. code-block:: java

        TimeZone timeZone = TimeZone.getTimeZone("America/New_York");
        Calendar calendar = Calendar.getInstance(timeZone);
        Date dateInNewYork = calendar.getTime();



   .. tab:: New Time API

      .. code-block:: java

        ZoneId zoneId = ZoneId.of("America/New_York");
        ZonedDateTime zonedDateTime = ZonedDateTime.now(zoneId);




.. _time_restrictions:

Restrictions
------------

The library's goal is to offer Application developers an API that closely mirrors the one found in Java SE 8.
However, we had to make the library compatible with both pre-Java 8 features and the constraints found in embedded devices, such as limited memory size.
Here are the items where the backport differs from its Java 8 counterpart:

- Non-ISO chronologies are not present (`Hijrah`, `Japanese`, `Minguo`, `ThaiBuddhist`). The overwhelming majority of applications use the ISO calendar system. Applications still have the option to introduce their own chronologies.
- No formatting or parsing methods (methods ``parse``, ``format``, ``getDisplayName``, ``ofLocale``).
- Removed the method ``ZoneRulesProvider.registerProvider(ZoneRulesProvider provider)``. The unique provider is defined with the constant ``java.time.zone.DefaultZoneRulesProvider``.
- Static methods in interfaces are not supported and were removed or moved (see below).
- Default methods in interfaces are not supported and were removed (pulled down in concrete types).
- Removed static methods ``TemporalAdjusters.ofDateAdjuster(UnaryOperator<LocalDate> dateBasedAdjuster)`` and ``WeekFields.of(Locale locale)``.
- No overflow checks on calculations (removed ``throws ArithmeticException`` when relevant). Excessively checking for overflow in all calculations can impact performance negatively.
- No null checks on method arguments. Developers are encouraged to use the :ref:`Null Analysis <null_analysis>` tool to detect null access and adhere to the API Javadoc specifications.
- The classes from the ``java.time.zone`` package do not provide a human readable implementation of ``toString()``.

.. note::
    For a comprehensive list of restrictions, refer to the ``README`` of the module.
    If some of the restrictions listed above are highly limiting and necessary for your application, please contact your MicroEJ sales representative or :ref:`our support team <get_support>`.

Static Interface Methods
~~~~~~~~~~~~~~~~~~~~~~~~

- ``ChronoLocalDate.from(TemporalAccessor)``: `removed`
- ``ChronoLocalDate.timeLineOrder()``: use ``LocalDate.timeLineOrder()`` instead
- ``ChronoLocalDateTime.from(TemporalAccessor)``: `removed`
- ``ChronoLocalDateTime.timeLineOrder()``: use ``LocalDateTime.timeLineOrder()`` instead
- ``ChronoZonedDateTime.from(TemporalAccessor)``: `removed`
- ``ChronoZonedDateTime.timeLineOrder()``: use ``ZonedDateTime.timeLineOrder()`` instead
- ``ChronoPeriod.between(ChronoLocalDate, ChronoLocalDate)``: `removed`
- ``Chronology.from(TemporalAccessor)``: use ``AbstractChronology.from(TemporalAccessor)`` instead
- ``Chronology.getAvailableChronologies()``: use ``AbstractChronology.getAvailableChronologies()`` instead
- ``Chronology.of(String)``: use ``AbstractChronology.of(String)`` instead
- ``Chronology.ofLocale(Locale)``: `removed`


..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.