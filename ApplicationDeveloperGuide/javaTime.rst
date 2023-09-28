.. _chapter.java_time:

Date and Time
=============

Introduction
------------

Java developers have long used the ``Date``, ``Calendar`` and ``TimeZone`` classes for handling date and time. 
With JSR310, Java 8 introduced a more advanced and comprehensive Date and Time API that goes beyond simply replacing ``Date`` or ``Calendar``. 
It provides a complete time model for applications.

There are many benefits of moving to the new API:

* Immutability: types are immutable, making thread-safe code easier to write and less prone to bugs (due to no mutable state).
* Improved API design: it offers an intuitive and developer-friendly design that better addresses the challenges of date and time manipulation. Application code is also easier to read and understand.
* Simplified date and time arithmetic: the API introduces methods for common date and time operations, simplifying tasks like adding or subtracting days, months, or years.
* Precision: it provides more precise representations for date and time values, including support for nanoseconds, which is important for applications requiring high precision.
* Comprehensive time model: it introduces new classes that deal with different concepts of time such as date without a time or time without a date, durations or periods.


Overview
--------

The library introduces different classes for date, time, date-time, and variations for offset and time zone. 
While this may seem like a lot of classes, most applications can start with only these types:

- ``Instant``: an instantaneous point on the timeline. It can be used to store timestamps of application events.
- ``LocalDate``: stores a date without a specific time or time zone, like ``2023-09-26``.
- ``LocalTime``: stores a time without a specific date or time zone, like ``15:30``.
- ``LocalDateTime``: stores both a date and time without a specific time zone, like ``2023-09-26T15:30``. It combines ``LocalDate`` and ``LocalTime``.
- ``ZonedDateTime``: stores both a date and time, including a time zone. This is handy for performing precise date and time calculations while considering the time zone.

.. note::
    Working with a time zone, like ``America/Los_Angeles`` can make calculations more complex. In many cases, the application can only work with ``LocalDate``, ``LocalTime``, and ``Instant``, and then add the time zone at the user interface (UI) level.


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

To use the ``time`` library, add the following to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("ej.library.eclasspath:time:1.0.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.library.eclasspath" name="time" rev="1.0.0"/>



Examples
--------

This section presents a series of small, focused examples that demonstrate various aspects of the Java Date and Time API. 

Instant
~~~~~~~

The ``Instant`` class is the closest equivalent of ``Date``. It represents a specific instant in time.
The following snippet shows how to create an instant from the factory methods and perform basic operations on instants.

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

``LocalDate`` stores a date without a time. It is called "local" because it isn't associated with any specific time zone, similar to a wall clock.
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

``LocalTime`` stores a particular time of day, focusing only on the time (hour, minute, second, nanosecond), and doesn't include date or time zone details. Useful when you only need to handle time values without dates or time zones (e.g., scheduling events like alarms, stopwatch and timers, event timing, etc.).

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

``LocalDateTime`` combines both date and time components and provides a precise timestamp. This makes it suitable for scenarios where you need to work with both date and time information, but without considering time zone conversions (e.g., timestamping, user interfaces, etc.). 

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

``Duration`` represents a duration of time, typically measured in hours, minutes, seconds, and nanoseconds. 
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

``Period`` represents a duration of time in terms of years, months, and days.
It is primarily concerned with human-centric time measurements, like the length of a month or a year.
It is well-suited for measuring time intervals within a calendar context. 
For example, it can represent periods of time such as 2 years, 3 months, and 5 days.

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

The library does not use the class ``TzdbZoneRulesProvider`` as the default provider for time zone rules (see :ref:`Restrictions <time_restrictions>`).

Instead, the library comes with a default provider which is very lightweight and simple that knows only the rules for the zone "GMT". 
Any attempt to use another zone ID will throw a ``ZoneRulesException`` because the ID is unknown.

For example,

.. code-block:: java

    // Displaying available time zones - will list a single item: "GMT"
    Set<String> timeZones = ZoneId.getAvailableZoneIds();
        for (String timeZone : timeZones) {
            System.out.println(timeZone);
    }

    // Creating ZonedDateTime instance - will throw a ZoneRulesException
    ZonedDateTime specificDateTime = ZonedDateTime.of(2023, 7, 15, 14, 30, 0, 0, ZoneId.of("Europe/Dublin")); // July 15, 2023, 2:30 PM in Dublin

    // Creating ZoneId instance from a region ID - will throw a ZoneRulesException 
    ZoneId tokyoTimeZone = ZoneId.of("Asia/Tokyo");


However, the user can define a custom default provider for loading time zone rules.
To do so, set the constant ``java.time.zone.DefaultZoneRulesProvider`` to be the fully qualified name of the custom provider class.

Here is an example of a ``xxx.constants.list`` file with the constant in an application:

.. code-block:: jproperties 

    java.time.zone.DefaultZoneRulesProvider=com.mycompany.CustomZoneRulesProvider



.. _time_migration_guide:

Migration Guide
---------------

If you're using the old date and time classes (``java.util.Date``, ``java.util.Calendar``), it's a great time to consider migrating to the new API.
This small migration guide will help you transition from the old time API to the Java Date and Time API (``java.time``). 
It covers some common date and time operations and demonstrates how to perform them using both approaches.

Displaying a Date
~~~~~~~~~~~~~~~~~

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

Calculating Date and Time Differences
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. tabs::

   .. tab:: Legacy Time API

      .. code-block:: java

        Date startDate = new Date();
        Date endDate = // Some other date
        long timeDifference = endDate.getTime() - startDate.getTime();


   .. tab:: New Time API

      .. code-block:: java

        LocalDateTime startDateTime = LocalDateTime.now();
        LocalDateTime endDateTime = // Some other date-time
        Duration duration = Duration.between(startDateTime, endDateTime);


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
However, we had to make the library compatible with both pre-Java 8 features and the constraints found in embedded devices.
Here are the items where the backport differs from its Java 8 counterpart:

- Non-ISO chronologies are not present (`Hijrah`, `Japanese`, `Minguo`, `ThaiBuddhist`). The overwhelming majority of applications use the ISO calendar system. Applications still have the option to introduce their own chronologies.
- No formatting or parsing methods (methods ``parse``, ``format``, ``getDisplayName``, ``ofLocale``).
- The default zone-rules provider is not ``TzdbZoneRulesProvider``. This provider loads zone rules from a local TZDB database and it consumes a significant amount of RAM. We plan to add this support in a specific Add-on Library at a later time.
- Static methods in interfaces are not supported and were removed or moved (see below).
- Default methods in interfaces are not supported and were removed (pulled down in concrete types).
- Removed static methods ``TemporalAdjusters.ofDateAdjuster(UnaryOperator<LocalDate> dateBasedAdjuster)`` and ``WeekFields.of(Locale locale)``.
- No overflow checks on calculations (removed ``throws ArithmeticException`` when relevant). Excessively checking for overflow in all calculations can impact performance negatively.
- No null checks on method arguments. Developers are encouraged to use the :ref:`Null Analysis <null_analysis>` tool to detect null access and adhere to the API javadoc specifications.

.. note::
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
