Vector Graphics Images
======================

Overview
--------

Vector Graphics Images are graphical resources that can be accessed with a call to `ej.microvg.VectorImage.getImage` <FIXME link to api page>. The images are converted at build-time (using the image generator tool) to immutable resources.

Images that must be processed by the image generator tool are declared in ``*.vectorimages.list`` files. The file format is a standard Java properties file, each line representing a ``/`` separated resource path relative to the MicroEJ classpath root referring to a vector image file (e.g. ``.svg``, ``.xml``). The resource must be followed by a parameter (separated by a ``:``) which defines and/or describes the image output file format (raw format).

Currently accepted format are : 

- ":VGF" : vglite compatible format with coordinates encoded as floating points.

Example:

::

   # The following image is embedded 
   # as a PNG resource (decoded at run-time)
   /com/mycompany/MyImage1.svg:VGF
   /com/mycompany/androidVectorDrawable.xml:VGF

Supported input files
---------------------

The image generator tool supports the following input file formats:

-  Android Vector Drawable
-  SVG 

The vector graphics image objects are extracted and converted to paths made of Move, Line and Curves commands. 

Each path is associated with either a fill color or a linear gradient. All object strokes are converted to fill paths at build-time.

Objects group transformations are also extracted from the input file and applied at run-time.


Drawing Images
---------------

Drawing and Transforming Images
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once an image has been loaded it can be drawn in the graphic context with a call to `ej.microvg.VectorGraphicsPainter.drawImage()` <FIXME link to api page>.

The image is associated with a transformation Matrix (see: <FIXME link Matrix section>) that will be applied in order to translate, scale and/or rotate the image. 

The application can get the width and the height of the image with `ej.microvg.VectorImage.getWidth()` <XXX link to api page> and `ej.microvg.VectorImage.getHeight()` <FIXME link to api page> to correctly scale and position the image in the application window.

The following example describes how an Android Vectordrawable file can be drawn and positionned on the display.

- Android Vector Drawable file:
  
.. code-block:: xml

   <vector xmlns:android="http://schemas.android.com/apk/res/android" xmlns:aapt="http://schemas.android.com/aapt"
      android:width="100dp"  android:height="100dp"  android:viewportWidth="100"  android:viewportHeight="100">
      <path  android:pathData="M 0 0 h50 v50 h-50 z"  android:fillColor="#FFFFAA"/>
      <path android:pathData="M 50 50 h50 v50 h-50 z">
         <aapt:attr name="android:fillColor">
               <gradient
                  android:startColor="#0000ff" android:startX="50"  android:startY="50"
                  android:endColor="#ff00ff" android:endX="100"     android:endY="100"
                  android:type="linear">
               </gradient>
         </aapt:attr>
      </path>
   </vector>

- Application code:
  
.. code-block:: java

   public static void main(String[] args) {
      
      MicroUI.start();

      Display display = Display.getDisplay();
      GraphicsContext g = display.getGraphicsContext();

      VectorImage image = VectorImage.getImage("/images/myImage.xml"); //$NON-NLS-1$

      Matrix matrix0 = new Matrix();
      matrix0.setTranslate(20, 20);
      matrix0.preScale(50 / image.getWidth(), 50 / image.getHeight());

      Matrix matrix1 = new Matrix();
      matrix1.setTranslate(150, 150);
      matrix1.preRotate(45);

      VectorGraphicsPainter.drawImage(g, image, matrix0);
      VectorGraphicsPainter.drawImage(g, image, matrix1);

      display.flush();
   }

- Resulting drawing:

.. figure:: images/drawImage.png
   :alt: Draw and transform image
   :width: 300px
   :align: center

Drawing With Opacity
~~~~~~~~~~~~~~~~~~~~

The vector graphics image can be drawn with a global opacity level. 

 - Application code:
  
.. code-block:: java

   VectorImage image = VectorImage.getImage("/images/myImage.xml"); //$NON-NLS-1$

   // the global opacity rendering value, between 0 (transparent) and 255 (opaque)
   int opacity = 0x80;

   VectorGraphicsPainter.drawImage(g, image, new Matrix(), opacity);

- Resulting drawing:
  
.. figure:: images/drawImageAlpha.png
   :alt: Draw image with alpha
   :width: 300px
   :align: center

.. warning:: As paths are drawn one after the other, images that contain overlapping paths are not correctly colored when a global opacity is applied. The rendering of these images will throw an exception. The images must be reworked to suppress overlapping, if the image needs to be drawn with a global opacity.

Color Filtering
~~~~~~~~~~~~~~~

A VectorImage object can be derived from an other VectorImage object, keeping the paths and transformations but updating the colors using a color matrix.

This color matrix is a 4x5 float matrix which is organized like that: 

- Each line is used to compute a component of the resulting color, in this order: red, green, blue, alpha.
- The four first columns are multipliers applied to a component of the initial color, in this order: red,green, blue, alpha.
- The last column is a constant value.

Let A, R, G, B be the components of the initial color and the following array a color matrix: 

.. code-block:: 

   { rR, rG, rB, rA, rC,  // red
     gR, gG, gB, gA, gC,  // green
     bR, bG, bB, bA, bC,  // blue
     aR, aG, aB, aA, aC } // alpha
 
The resulting color components are computed as: 

 .. code-block:: 

   resultRed = rR * R + rG * G + rB * B + rA * A + rC
   resultGreen = gR * R + gG * G + gB * B + gA * A + gC
   resultBlue = bR * R + bG * G + bB * B + bA * A + bC
   resultAlpha = aR * R + aG * G + aB * B + aA * A + aC
 
If the resulting component value is below 0 or above 255, the component value is clamped to these limits.

A VectorImage object can also be drawn associated to a color matrix by a call to `ej.microvg.VectorGraphicsPainter.drawFilteredImage` <FIXME link to api page>.
 
The following example illustrates this feature.

- Application code:
  
.. code-block:: java

  VectorImage image = VectorImage.getImage("/images/myImage.xml"); //$NON-NLS-1$

   // Derive a new VectorImage
   float[] colorMatrix0 = new float[] { //
         1f, 0, 0, 0, 0, // red
         0, 0, 0, 0, 0, // green
         0, 0, 1f, 0, 0, // blue
         0, 0, 0, 1f, 0, // alpha
   };

   VectorImage imageFiltered = image.filterImage(colorMatrix0);
   VectorGraphicsPainter.drawImage(g, imageFiltered, new Matrix());

   float[] colorMatrix1 = new float[] { //
         0f, 0, 0, 0, 0, // red
         0.5f, 0.5f, 0, 0, 0, // green
         0, 0, 1f, -0.5f, 0, // blue
         0, 0, 0, 1f, 0, // alpha
   };
   Matrix matrix1 = new Matrix();
   matrix1.setTranslate(image.getWidth(), 0);

   VectorGraphicsPainter.drawFilteredImage(g, image, matrix1, colorMatrix1);

- Resulting drawing:
  
.. figure:: images/drawImageFilter.png
   :alt: Draw and filter image
   :width: 300px
   :align: center


Animated Vector Graphics Images
-------------------------------

The Android Vector Drawable format supports the ability to change vector graphics over time, to create animated effects.

The transformations of the objects over the time are embedded in the Vector Graphics image file and a call to `ej.microvg.VectorGraphicsPainter.drawAnimatedImage` <FIXME link to api page> will draw the image for a specific time frame.

The application can get the duration of the image animation with a call to  `ej.microvg.VectorImage.getDuration()` <FIXME link to api page>.

Every image object that is animated outside the image viewbox is clipped at image boundaries. In any cases, especially when the image is rotated,  the image boundaries is the rectangle that contains all the corners of the original image.

The supported file format is an Animated Vector Drawable xml file with animation and vector definition in the same file as described in <https://developer.android.com/reference/android/graphics/drawable/AnimatedVectorDrawable#define-an-animatedvectordrawable-all-in-one-xml-file>

The SVG format also supports the animation of vector graphics object, but this feature is not yet implemented in the MicroVG library for this file format.

SVG files that need to be animated should be converted to Android Vector Drawable format with the Android Vector Asset tool and then animated manually or with a tool like Shapeshifter <https://shapeshifter.design/>.

Supported animations
~~~~~~~~~~~~~~~~~~~~

For the following animation examples, this simple java code will be used. The image is drawn in a loop.

.. code-block:: java

   VectorImage image = VectorImage.getImage("/images/myImage.xml"); //$NON-NLS-1$
   Matrix matrix = new Matrix();
   matrix.setTranslate(100,100);
   matrix.preScale(2,2);

   long elapsed = 0;
   long step = 10;
   while (true) {
      // Clear Screen
      g.setColor(Colors.BLACK);
      Painter.fillRectangle(g, 0, 0, display.getWidth(), display.getHeight());

      VectorGraphicsPainter.drawAnimatedImage(g, image, matrix, elapsed);

      display.flush();

      // Pause the current thread
      try {
         Thread.sleep(step);
      } catch (InterruptedException e) {
         e.printStackTrace();
      }

      // Update current image time
      if (elapsed < image.getDuration()) {
         elapsed += step;
      } else {
         elapsed = 0;
      }
   }

TranslateX and TranslateY
*************************

Any group in the Android Vector Drawable can be translated in X or Y direction with an object animator. 

When the a property is animated twice in the animation the property keep the first animation last value until the start of the next animation.

- Image:

.. code-block:: xml

   <animated-vector xmlns:android="http://schemas.android.com/apk/res/android"  xmlns:aapt="http://schemas.android.com/aapt">
   <aapt:attr name="android:drawable">
      <vector  android:width="100dp"  android:height="100dp"  android:viewportWidth="100"  android:viewportHeight="100">
         <group android:name="yellow_group">
               <path  android:pathData="M 0 0 h50 v50 h-50 z"  android:fillColor="#FFFFAA"/>
         </group>
         <group android:name="gradient_group">
         <path android:pathData="M 50 50 h50 v50 h-50 z">
               <aapt:attr name="android:fillColor">
                  <gradient
                     android:startColor="#0000ff" android:startX="50"  android:startY="50"
                     android:endColor="#ff00ff" android:endX="100"     android:endY="100"
                     android:type="linear">
                  </gradient>
               </aapt:attr>
         </path>
         </group>
      </vector>
   </aapt:attr>
   <target android:name="yellow_group">
      <aapt:attr name="android:animation">
         <set android:ordering="together">
               <objectAnimator android:propertyName="translateX" android:valueType="floatType"
                  android:duration="1000" android:startOffset="0" android:valueFrom="0" android:valueTo="50"  />
               <objectAnimator android:propertyName="translateX"  android:valueType="floatType"
                  android:duration="1000" android:startOffset="1500" android:valueFrom="50" android:valueTo="0" />
         </set>
      </aapt:attr>
   </target>
   <target android:name="gradient_group">
      <aapt:attr name="android:animation">
         <set android:ordering="together">
               <objectAnimator android:propertyName="translateX" android:valueType="floatType"
                  android:duration="1000" android:startOffset="0" android:valueFrom="0" android:valueTo="-50"  />
               <objectAnimator android:propertyName="translateX"  android:valueType="floatType"
                  android:duration="1000" android:startOffset="1500" android:valueFrom="-50" android:valueTo="0" />
               <objectAnimator android:propertyName="translateY" android:valueType="floatType"
                  android:duration="1000" android:startOffset="0" android:valueFrom="0" android:valueTo="-50"  />
               <objectAnimator android:propertyName="translateY"  android:valueType="floatType"
                  android:duration="1000" android:startOffset="1500" android:valueFrom="-50" android:valueTo="0" />
         </set>
      </aapt:attr>
   </target>
   </animated-vector>

- Resulting drawing:
  
.. figure:: images/drawAnimatedImageTranslate.gif
   :alt: Draw animated image with translate
   :width: 300px
   :align: center

TranslateXY over a path
***********************

Any group in the Android Vector Drawable can be translated over a path.

- Image:

.. code-block:: xml

   <animated-vector xmlns:android="http://schemas.android.com/apk/res/android"  xmlns:aapt="http://schemas.android.com/aapt">
   <aapt:attr name="android:drawable">
      <vector  android:width="100dp"  android:height="100dp"  android:viewportWidth="100"  android:viewportHeight="100">
        ... same as previous example
      </vector>
   </aapt:attr>
   <target android:name="gradient_group">
      <aapt:attr name="android:animation">
         <set android:ordering="together">
              <objectAnimator
                    android:propertyName="translateXY" android:duration="5000"
                    android:propertyXName="translateX" android:propertyYName="translateY"
                    android:pathData="M -0.143 0.479 C -30.355 28.02 -153.405 -111.8 -39.441 -70.818 C -48.423 -63.52 70.593 -18.608 -91.09 -15.802 Z"/>
         </set>
      </aapt:attr>
   </target>
   </animated-vector>

- Resulting drawing:
  
.. figure:: images/drawAnimatedImageOverPath.gif
   :alt: Draw animated image over a path
   :width: 300px
   :align: center

ScaleX and ScaleY
*****************

Any group in the Android Vector Drawable can be scaled on X or Y direction. The scaling pivot point is the one defined in the group attributes. By defaut the pivot point is (0,0).

.. code-block:: xml

   <animated-vector xmlns:android="http://schemas.android.com/apk/res/android"  xmlns:aapt="http://schemas.android.com/aapt">
   <aapt:attr name="android:drawable">
      <vector  android:width="100dp"  android:height="100dp"  android:viewportWidth="100"  android:viewportHeight="100">
         <group android:name="yellow_group" android:pivotX="25" android:pivotY="25">
               <path  android:pathData="M 0 0 h50 v50 h-50 z"  android:fillColor="#FFFFAA"/>
         </group>
         <group android:name="gradient_group" >
         <path android:pathData="M 50 50 h50 v50 h-50 z">
               <aapt:attr name="android:fillColor">
                  <gradient
                     android:startColor="#0000ff" android:startX="50"  android:startY="50"
                     android:endColor="#ff00ff" android:endX="100"     android:endY="100"
                     android:type="linear">
                  </gradient>
               </aapt:attr>
         </path>
         </group>
      </vector>
   </aapt:attr>
   <target android:name="yellow_group">
      <aapt:attr name="android:animation">
         <set android:ordering="together">
               <objectAnimator android:propertyName="scaleX" android:valueType="floatType"
                  android:duration="1000" android:startOffset="0" android:valueFrom="1" android:valueTo="0.5"  />
               <objectAnimator android:propertyName="scaleX"  android:valueType="floatType"
                  android:duration="1000" android:startOffset="1500" android:valueFrom="0.5" android:valueTo="1" />
         </set>
      </aapt:attr>
   </target>
   <target android:name="gradient_group">
      <aapt:attr name="android:animation">
         <set android:ordering="together">
               <objectAnimator android:propertyName="scaleX" android:valueType="floatType"
                  android:duration="1000" android:startOffset="0" android:valueFrom="0.2" android:valueTo="1"  />
               <objectAnimator android:propertyName="scaleX"  android:valueType="floatType"
                  android:duration="1000" android:startOffset="1500" android:valueFrom="1" android:valueTo="0.2" />
               <objectAnimator android:propertyName="scaleY" android:valueType="floatType"
                  android:duration="1000" android:startOffset="0" android:valueFrom="0.2" android:valueTo="1"  />
               <objectAnimator android:propertyName="scaleY"  android:valueType="floatType"
                  android:duration="1000" android:startOffset="1500" android:valueFrom="1" android:valueTo="0.2" />
         </set>
      </aapt:attr>
   </target>
   </animated-vector>

- Resulting drawing:
  
.. figure:: images/drawAnimatedImageScaleXY.gif
   :alt: Draw animated image over a path
   :width: 300px
   :align: center

Rotate
******

Any group in the Android Vector Drawable can be rotated around a pivot point. The pivot point is the one defined in the group attributes. By defaut the pivot point is (0,0).

.. code-block:: xml

   <animated-vector xmlns:android="http://schemas.android.com/apk/res/android"  xmlns:aapt="http://schemas.android.com/aapt">
   <aapt:attr name="android:drawable">
      <vector  android:width="100dp"  android:height="100dp"  android:viewportWidth="100"  android:viewportHeight="100">
         ... same as previous example
      </vector>
   </aapt:attr>
   <target android:name="yellow_group">
      <aapt:attr name="android:animation">
         <set android:ordering="together">
               <objectAnimator android:propertyName="rotation" android:valueType="floatType"
                  android:duration="1000" android:startOffset="0" android:valueFrom="0" android:valueTo="720"  />
               <objectAnimator android:propertyName="rotation"  android:valueType="floatType"
                  android:duration="1000" android:startOffset="1500" android:valueFrom="720" android:valueTo="0" />
         </set>
      </aapt:attr>
   </target>
   </animated-vector>

- Resulting drawing:
  
.. figure:: images/drawAnimatedImageRotate.gif
   :alt: Draw animated image over a path
   :width: 300px
   :align: center

Limitations
-----------


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.