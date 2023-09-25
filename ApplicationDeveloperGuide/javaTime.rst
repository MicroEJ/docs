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
* Comprehensive time model: it introduces new classes that deal with different concepts of time such as date without a time or time without a date, durations, periods or intervals.

Usage
-----

Migration Guide
---------------

Restrictions
------------