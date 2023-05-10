.. _section_buffered_image:

===============
Buffered Image
===============

XXX TODO XXX

MicroUI application is able to create an image where it is allowed to draw into: the MicroUI `BufferedImage`. 

Display
=======

The image format is the same than the display format; in other words, its number of bits-per-pixel and its pixel bits organization are the same. The display pixel format can be standard or custom (see :ref:`display_pixel_structure`). To create this kind of image, the Image Loader has just to create a buffer in RAM whose size depends on the image size (see :ref:`section_image_display_raw`).


Standard
========

* by default it is "display" == cf display drawing xxx
* format standards = A4 ARGB1555 etc.: dedicated / vee port drawings: multi out
  * emb: graph + define
  * sim: graph + service (UIImage)
* renderer : cf renderer

Custom
======

* c0 -> C7 (microui api link)
* how to create buffer / allocate
  * emb: 
  * sim: 
* draw into: custom drawings / same graphs as standard formats
* draw it: cf renderer

Draw Into
=========

xxx

Draw It
=======

* draw it: cf renderer

Multi in / multi out
====================

xxx just ideas xxx

* image standard -> out  == draw it (cf renderer)
* image custom -> xxx
* emb: gros graph
* sim: services

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners. 