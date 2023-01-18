.. include:: uiReplaces.rst

.. _section_ui_migrationguide:

===============
Migration Guide
===============

From 13.2.x to 13.3.x
=====================

Front Panel
"""""""""""

* Set the explicit dependency to the `UI Pack 13.3.1`_: 

  .. code-block:: xml

	 <dependency org="com.microej.pack.ui" name="ui-pack" rev="13.3.1">
		<artifact name="frontpanel" type="jar"/>
	 </dependency>

.. _UI Pack 13.3.1: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.3.1/

BSP
"""

* Install the  :ref:`MicroUI C module 2.0.0 <section_ui_releasenotes_cmodule>`.
* The signatures of ``LLUI_DISPLAY_IMPL_decodeImage`` and ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes`` have changed: 
 
	* use ``jbyte`` in functions signatures
	* add a cast to ``MICROUI_Image`` in the implementation.
  

From 13.1.x to 13.2.x
=====================

Front Panel
"""""""""""

* Set the explicit dependency to the `UI Pack 13.2.0`_: 

  .. code-block:: xml

	 <dependency org="com.microej.pack.ui" name="ui-pack" rev="13.2.0">
		<artifact name="frontpanel" type="jar"/>
	 </dependency>

.. _UI Pack 13.2.0: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.2.0/

From 13.0.x to 13.1.x
=====================

Front Panel
"""""""""""

* Set the explicit dependency to the `UI Pack 13.1.0`_: 

  .. code-block:: xml

	 <dependency org="com.microej.pack.ui" name="ui-pack" rev="13.1.0">
		<artifact name="frontpanel" type="jar"/>
	 </dependency>

.. _UI Pack 13.1.0: https://repository.microej.com/modules/com/microej/pack/ui/ui-pack/13.1.0/

BSP
"""

* Add a cast when using ``MICROUI_Image*`` object: ``(MICROUI_ImageFormat)image->format`` .
* Remove parameter ``MICROUI_GraphicsContext*`` when calling ``LLUI_DISPLAY_setDrawingLimits()``. 
* Ensure to call ``LLUI_DISPLAY_setDrawingLimits()`` before calling ``LLUI_DISPLAY_setDrawingStatus()`` or ``LLUI_DISPLAY_notifyAsynchronousDrawingEnd()``.
* (optional) Add an implementation of ``LLUI_DISPLAY_IMPL_image_heap_xxx`` to control the :ref:`images heap allocation<section_image_loader_memory>`; by default the internal Graphics Engine's allocator is used. Another implementation is also available on the :ref:`C module<section_ui_releasenotes_cmodule>`. 

From 12.x to 13.x
=================

Platform Configuration Project
""""""""""""""""""""""""""""""

* Update Architecture version: 7.16.0 or higher.
* Add `the following module <https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui/1.0.3/>`__ in the :ref:`module description file <mmm_module_description>`: 

  .. code-block:: xml

     <dependency org="com.microej.clibrary.llimpl" name="microui" rev="1.0.3"/>

* If not already set, set the ``ea:property`` ``bsp.project.microej.dir`` in the module ivy file to configure the BSP output folder where is extracted the module.

Hardware Accelerator
""""""""""""""""""""

* Open :guilabel:`-configuration` project > :guilabel:`display` > :guilabel:`display.properties`
* Remove optional property ``hardwareAccelerator``. If old value was ``dma2d``, add `the following module <https://repository.microej.com/modules/com/microej/clibrary/llimpl/display-dma2d/1.0.6/>`__ in the :ref:`module description file <mmm_module_description>`: 
  
  .. code-block:: xml
  
     <dependency org="com.microej.clibrary.llimpl" name="display-dma2d" rev="1.0.6"/>``

* For the hardware accelerator DMA2D, please consult STM32F7Discovery board updates. Add the file ``lldisplay_dma2d.c``, the global defines ``DRAWING_DMA2D_BPP=16`` (or another value) and ``STM32F4XX`` or ``STM32F7XX``
* For the others hardware accelerators, please contact MicroEJ support.

Front Panel
"""""""""""

This chapter resumes the changes to perform.
The available changes in Front Panel API are described in :ref:`next chapter<section_ui_migration_frontpanelapi_13x>`.

* If not already done, follow the Front Panel version 6 migration procedure detailled in chapter :ref:`section_ui_migration_12x`.
* Update the fp project dependency: ``<dependency org="ej.tool.frontpanel" name="widget" rev="2.0.0"/>``
* ``ej.fp.event.MicroUIButtons`` has been renamed in ``ej.microui.event.EventButton``, and all others ``ej.fp.event.MicroUIxxx`` in ``ej.microui.event.Eventxxx``
* Display abstract class ``AbstractDisplayExtension`` (class to extend widget Display when targetting a custom display) has been converted on the interface ``DisplayExtension``. Some methods names have changed and now take in parameter the display widget.

.. _section_ui_migration_frontpanelapi_13x:

Front Panel API
"""""""""""""""

* ``ej.drawing.DWDrawing``

	* [Added] Equivalent of ``dw_drawing.h`` and ``dw_drawing_soft.h**``: allows to implement some drawing algorithms and/or to use the ones provided by the graphical engine. The drawing methods are related to the library ``ej.api.drawing``.
	* [Added] Interface ``DWDrawingDefault``: default implementation of ``DWDrawing`` which calls the graphical engine algorithms.

* ``ej.drawing.LLDWPainter``

	* [Added] Equivalent of module `com.microej.clibrary.llimpl#microui`_ (``LLDW_PAINTER_impl.c``): implements all ``ej.api.drawing`` natives and redirect them to the interface ``DWDrawing``.
	* [Added] ``setDrawer(DWDrawing)``: allows to configure the implementation of ``DWDrawing`` the ``LLDWPainter`` has to use. When no drawer is configured, ``LLDWPainter`` redirects all drawings to the internal graphical engine software algorithms.

* ``ej.fp.event.MicroUIButtons``

	* [Removed] Replaced by ``EventButton``.

* ``ej.fp.event.MicroUICommand``

	* [Removed] Replaced by ``EventCommand``.

* ``ej.fp.event.MicroUIEventGenerator``

	* [Removed] Replaced by ``LLUIInput``.

* ``ej.fp.event.MicroUIGeneric``

	* [Removed] Replaced by ``EventGeneric``.

* ``ej.fp.event.MicroUIPointer``

	* [Removed] Replaced by ``EventPointer``.

* ``ej.fp.event.MicroUIStates``

	* [Removed] Replaced by ``EventState``.

* ``ej.fp.event.MicroUITouch``

	* [Removed] Replaced by ``EventTouch``.

* ``ej.fp.widget.MicroUIDisplay``

	* [Removed] Replaced by ``LLUIDisplayImpl``. Abstract widget display class has been replaced by an interface that a widget (which should simulate a display) has to implement to be compatible with the graphical engine.
	* [Removed] ``AbstractDisplayExtension``, all available implementations and ``setExtensionClass(String)``: the standard display formats (RGB565, etc.) are internally managed by the graphical engine. For generic formats, some APIs are available in ``LLUIDisplayImpl``.
	* [Removed] ``finalizeConfiguration()``, ``getDisplayHeight()``, ``getDisplayWidth()``, ``getDrawingBuffer()``, ``setDisplayWidth(int)``, ``setDisplayHeight(int)``, ``start()``: ``LLUIDisplayImpl`` is not an abstract widget anymore, these notions are widget dependent.
	* [Removed] ``flush()``.
	* [Removed] ``getNbBitsPerPixel()``.
	* [Removed] ``switchBacklight(boolean)``.

* ``ej.fp.widget.MicroUILED``

	* [Removed] Replaced by ``LLUILedImpl``. Abstract widget LED class has been replaced by an interface that a widget (which should simulate a LED) has to implement to be compatible with the graphical engine.
	* [Removed] ``finalizeConfiguration()``: ``LLUILedImpl`` is not an abstract widget anymore, this notion is widget dependent.
	* [Removed] ``getID()``: MicroUI uses the widget (which implements the interface ``LLUILedImpl``)'s label to retrieve the LED. The LED labels must be integers from 0 to ``n-1``.

* ``ej.microui.display.LLUIDisplay``

	* [Added] Equivalent of ``LLUI_DISPLAY.h``: several functions to interact with the graphical engine.
	* [Added] ``blend(int,int,int)``: blends two ARGB colors and opacity level.
	* [Added] ``convertARGBColorToColorToDraw(int)``: crops given color to display capacities.
	* [Added] ``getDisplayPixelDepth()``: replaces ``MicroUIDisplay.getNbBitsPerPixel()``.
	* [Added] ``getDWDrawerSoftware()``: gives the unique instance of graphical engine's internal software drawer (instance of ``DWDrawing``).
	* [Added] ``getUIDrawerSoftware()``: gives the unique instance of graphical engine's internal software drawer (instance of ``UIDrawing``).
	* [Added] ``mapMicroUIGraphicsContext(byte[])`` and ``newMicroUIGraphicsContext(byte[])``: maps the graphics context byte array (`GraphicsContext.getSNIContext()`_) on an object which represents the graphics context in front panel. 
	* [Added] ``mapMicroUIImage(byte[])`` and ``newMicroUIImage(byte[])``: maps the image byte array (`Image.getSNIContext()`_) on an object which represents the image in front panel. 
	* [Added] ``requestFlush(boolean)``: requests a call to ``LLUIDisplayImpl.flush()``.
	* [Added] ``requestRender(void)``: requests a call to ``Displayable.render()``.

* ``ej.microui.display.LLUIDisplayImpl``

	* [Added] Replaces ``MicroUIDisplay``, equivalent of ``LLUI_DISPLAY_impl.h``.
	* [Added] ``initialize()``: asks to initialize the widget and to return a front panel image where the graphical engine will perform the MicroUI drawings.
	* [Changed] ``flush(MicroUIGraphicsContext, Image, int, int, int, int)``: asks to flush the graphics context drawn by MicroUI in image returned by ``initialize()``.

* ``ej.microui.display.LLUIPainter``

	* [Added] Equivalent of module `com.microej.clibrary.llimpl#microui`_ (``LLUI_PAINTER_impl.c``): implements all ``ej.api.microui`` natives and redirect them to the interface ``UIDrawing``.
	* [Added] ``MicroUIGraphicsContext``: representation of a MicroUI `GraphicsContext`_ in front panel. This interface (implemented by the graphical engine) provides several function to get information on graphics context, clip, etc.
	* [Added] ``MicroUIGraphicsContext#requestDrawing()``: allows to take the hand on the drawing buffer.
	* [Added] ``MicroUIImage``: representation of a MicroUI `Image`_ in front panel. This interface (implemented by the graphical engine) provides several function to get information on image.
	* [Added] ``setDrawer(UIDrawing)``: allows to configure the implementation of ``UIDrawing`` the ``LLUIPainter`` has to use. When no drawer is configured, ``LLUIPainter`` redirects all drawings to the internal graphical engine software algorithms.
	* 
* ``ej.microui.display.UIDrawing``

	* [Added] Equivalent of ``ui_drawing.h`` and ``ui_drawing_soft.h**``: allows to implement some drawing algorithms and/or to use the ones provided by the graphical engine. The drawing methods are related to the library ``ej.api.microui``.
	* [Added] Interface ``UIDrawingDefault``: default implementation of ``UIDrawing`` which calls the graphical engine algorithms.

* ``ej.microui.event.EventButton``

	* [Added] Replaces ``MicroUIButton``.

* ``ej.microui.event.EventCommand``

	* [Added] Replaces ``MicroUICommand``.

* ``ej.microui.event.EventGeneric``

	* [Added] Replaces ``MicroUIGeneric``.

* ``ej.microui.event.EventPointer``

	* [Added] Replaces ``MicroUIPointer``.

* ``ej.microui.event.EventQueue``

	* [Added] Dedicated events queue used by MicroUI.

* ``ej.microui.event.EventState``

	* [Added] Replaces ``MicroUIState``.

* ``ej.microui.event.EventTouch``

	* [Added] Replaces ``MicroUITouch``.

* ``ej.microui.event.LLUIInput``

	* [Added] Replaces ``MicroUIEventGenerator``.

* ``ej.microui.led.LLUILedImpl``

	* [Added] Replaces ``MicroUILED``.

.. _com.microej.clibrary.llimpl#microui: https://repository.microej.com/modules/com/microej/clibrary/llimpl/microui
.. _GraphicsContext.getSNIContext(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html#getSNIContext--
.. _Image.getSNIContext(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html#getSNIContext--
.. _GraphicsContext: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/GraphicsContext.html
.. _Image: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microui/display/Image.html

Image Generator
"""""""""""""""

This chapter resumes the changes to perform.
The available changes in Image Generator API are described in :ref:`next chapter<section_ui_migration_imagegeneratorapi_13x>`.

This chapter only concerns platform with a custom display. In this case a dedicated image generator extension project is available. This project must be updated.

* Reorganize project to use source folders ``src/main/java`` and ``src/main/resources``
* Add new ``module.ivy`` file:

   .. code-block:: xml

      <ivy-module version="2.0" xmlns:ea="http://www.easyant.org" xmlns:m="http://www.easyant.org/ivy/maven" xmlns:ej="https://developer.microej.com" ej:version="2.0.0">

         <info organisation="com.is2t.microui" module="imageGenerator-xxx" status="integration" revision="1.0.0">      
            <ea:build organisation="com.is2t.easyant.buildtypes" module="build-std-javalib" revision="2.+"/>
         </info>
         
         <configurations defaultconfmapping="default->default;provided->provided">
            <conf name="default" visibility="public" description="Runtime dependencies to other artifacts"/>
            <conf name="provided" visibility="public" description="Compile-time dependencies to APIs provided by the platform"/>
            <conf name="documentation" visibility="public" description="Documentation related to the artifact (javadoc, PDF)"/>
            <conf name="source" visibility="public" description="Source code"/>
            <conf name="dist" visibility="public" description="Contains extra files like README.md, licenses"/>
            <conf name="test" visibility="private" description="Dependencies for test execution. It is not required for normal use of the application, and is only available for the test compilation and execution phases."/>
         </configurations>
         
         <publications/>
         
         <dependencies>
            <dependency org="com.microej.pack.ui" name="ui-pack" rev="[UI Pack version]">
               <artifact name="imageGenerator" type="jar"/>
            </dependency>
         </dependencies>
      </ivy-module>

The artifact name prefix must be ``imageGenerator-``.

* Update project classpath: remove classpath variable ``IMAGE-GENERATOR-x.x`` and add ivy file dependency
* Instead of implementing ``GenericDisplayExtension``, the extension class must extend ``BufferedImageLoader`` class; check class methods to override.
* Add the file ``src/main/resources/META-INF/services/com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension``; this file has to specify the class which extends the ``BufferedImageLoader`` class, for instance:

   .. code-block:: java

      com.microej.generator.MyImageGeneratoExtension

* Build the easyant project
* Copy the jar in the platform :guilabel:`-configuration` project > :guilabel:`dropins` folder
* Rebuild the platform after any changes

.. _section_ui_migration_imagegeneratorapi_13x:

Image Generator API
"""""""""""""""""""

* ``com.is2t.microej.microui.image.CustomDisplayExtension``

	* [Removed] Replaced by ``ImageConverter`` and ``MicroUIRawImageGeneratorExtension``.

* ``com.is2t.microej.microui.image.DisplayExtension``

	* [Removed] 

* ``com.is2t.microej.microui.image.GenericDisplayExtension``

	* [Removed] Replaced by ``ImageConverter`` and ``MicroUIRawImageGeneratorExtension``.

* ``com.microej.tool.ui.generator.BufferedImageLoader``

	* [Added] Pixelated image loader (PNG, JPEG etc.).

* ``com.microej.tool.ui.generator.Image``

	* [Added] Representation of an image listed in a ``images.list`` file.

* ``com.microej.tool.ui.generator.ImageConverter``

	* [Added] Generic converter to convert an image in an output stream.

* ``com.microej.tool.ui.generator.MicroUIRawImageGeneratorExtension``

	* [Added] Graphical engine RAW image converter: used when the image (listed in ``images.list``) targets a RAW format known by the graphical engine.

Font
""""

* Open optional font(s) in :guilabel:`-configuration` project > :guilabel:`microui/**/*.ejf`
* Remove all ``Dynamic`` styles (select ``None`` or ``Built-in`` for bold, italic and underline); the number of generated fonts must be ``1`` (the feature to render ``Dynamic`` styles at runtime have been removed)
* Save the file(s)

BSP
"""

This chapter resumes the changes to perform.
The available changes in LLAPI are described in :ref:`next chapter<section_ui_migration_llapi_13x>`.

* Delete all platform header files (folder should be set in :guilabel:`-configuration` project > :guilabel:`bsp` > :guilabel:`bsp.properties` > property ``output.dir``)
* If not possible to delete this folder, delete all UI headers files:

    * ``intern/LLDISPLAY*``
    * ``intern/LLINPUT*``
    * ``intern/LLLEDS*``
    * ``LLDISPLAY*``
    * ``LLINPUT*``
    * ``LLLEDS*``
	
* Replace all ``#include "LLDISPLAY.h"``, ``#include "LLDISPLAY_EXTRA.h"`` and ``#include "LLDISPLAY_UTILS.h"`` by ``#include "LLUI_DISPLAY.h"``
* Replace all ``#include "LLDISPLAY_impl.h"``, ``#include "LLDISPLAY_EXTRA_drawing.h"`` and ``#include "LLDISPLAY_EXTRA_impl.h"`` by ``#include "LLUI_DISPLAY_impl.h"``
* Replace all ``LLDISPLAY_EXTRA_IMAGE_xxx`` by ``MICROUI_IMAGE_FORMAT_xxx``
* All ``LLDISPLAY_IMPL_xxx`` functions have been renamed in ``LLUI_DISPLAY_IMPL_xxx``
* ``LLUI_DISPLAY_IMPL_initialize`` has now the paremeter ``LLUI_DISPLAY_SInitData* init_data``; fill it as explained in C doc.
* Implement new functions ``void LLUI_DISPLAY_IMPL_binarySemaphoreTake(void* sem)`` and ``void LLUI_DISPLAY_IMPL_binarySemaphoreGive(void* sem, bool under_isr)``
* Signature of ``LLUI_DISPLAY_IMPL_flush`` has changed
* All ``LLDISPLAY_EXTRA_IMPL_xxx`` functions have been renamed in ``LLUI_DISPLAY_IMPL_xxx``
* Fix some functions signatures (``LLUI_DISPLAY_IMPL_hasBacklight()``, etc)
* Remove the functions ``LLDISPLAY_IMPL_getGraphicsBufferAddress``, ``LLDISPLAY_IMPL_getHeight``, ``LLDISPLAY_IMPL_getWidth``, ``LLDISPLAY_IMPL_synchronize``, ``LLDISPLAY_EXTRA_IMPL_waitPreviousDrawing``, ``LLDISPLAY_EXTRA_IMPL_error``
* Add the end of asynchronous flush copy, call ``LLUI_DISPLAY_flushDone``
* Add the files ``LLUI_PAINTER_impl.c`` and ``LLDW_PAINTER_impl.c`` in your C configuration project
* Replace the prefix ``LLINPUT`` in all header files, functions and defines by the new prefix ``LLUI_INPUT``
* Replace the prefix ``LLLEDS`` in all header files, functions and defines by the new prefix ``LLUI_LED``
* Replace the prefix ``LLDISPLAY`` in all header files, functions and defines by the new prefix ``LLUI_DISPLAY``

.. _section_ui_migration_llapi_13x:

LLAPI
"""""

* ``dw_drawing_soft.h``

	* [Added] List of internal graphical engine software algorithms to perform some drawings (related to library ``ej.api.drawing``).

* ``dw_drawing.h``

	* [Added] List of ``ej.api.drawing`` library's drawing functions to optionally implement in platform.

* ``LLDISPLAY.h`` and ``intern/LLDISPLAY.h``

	* [Removed] 

* ``LLDISPLAY_DECODER.h`` and ``intern/LLDISPLAY_DECODER.h``

	* [Removed] 

* ``LLDISPLAY_EXTRA.h`` and ``intern/LLDISPLAY_EXTRA.h`` merged in ``LLUI_PAINTER_impl.h`` and ``LLDW_PAINTER_impl.h``

	* [Changed] ``LLDISPLAY_SImage``: replaced by ``MICROUI_Image``.
	* [Removed] ``LLDISPLAY_SRectangle``, ``LLDISPLAY_SDecoderImageData``, ``LLDISPLAY_SDrawImage``, ``LLDISPLAY_SFlipImage``, ``LLDISPLAY_SScaleImage`` and ``LLDISPLAY_SRotateImage``

* ``LLDISPLAY_EXTRA_drawing.h``

	* [Removed] 

* ``LLDISPLAY_EXTRA_impl.h`` and ``intern/LLDISPLAY_EXTRA_impl.h`` merged in ``LLUI_DISPLAY_impl.h``, ``ui_drawing.h`` and ``dw_drawing.h``

	* [Changed] ``LLDISPLAY_EXTRA_IMPL_setContrast(int32_t)``: replaced by ``LLUI_DISPLAY_IMPL_setContrast(uint32_t)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_getContrast(void)``: replaced by ``LLUI_DISPLAY_IMPL_getContrast(void)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_hasBackLight(void)``: replaced by ``LLUI_DISPLAY_IMPL_hasBacklight(void)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_setBacklight(int32_t)``: replaced by ``LLUI_DISPLAY_IMPL_setBacklight(uint32_t)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_getBacklight(void)``: replaced by ``LLUI_DISPLAY_IMPL_getBacklight(void)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_isColor(void)``: replaced by ``LLUI_DISPLAY_IMPL_isColor(void)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_getNumberOfColors(void)``: replaced by ``LLUI_DISPLAY_IMPL_getNumberOfColors(void)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_isDoubleBuffered(void)``: replaced by ``LLUI_DISPLAY_IMPL_isDoubleBuffered(void)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_getBacklight(void)``: replaced by ``LLUI_DISPLAY_IMPL_getBacklight(void)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_fillRect(void*,int32_t,void*,int32_t)``: replaced by ``UI_DRAWING_fillRectangle(MICROUI_GraphicsContext*,jint,jint,jint,jint)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_drawImage(void*,int32_t,void*,int32_t,void*)``: replaced by ``UI_DRAWING_drawImage(MICROUI_GraphicsContext*,MICROUI_Image*,jint,jint,jint,jint,jint,jint,jint)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_flipImage(void*,int32_t,void*,int32_t,void*)``: replaced by ``DW_DRAWING_drawFlippedImage(MICROUI_GraphicsContext*,MICROUI_Image*,jint,jint,jint,jint,jint,jint,DRAWING_Flip,jint)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_scaleImage(void*,int32_t,void*,int32_t,void*)``: replaced by ``DW_DRAWING_drawScaledImageNearestNeighbor(MICROUI_GraphicsContext*,MICROUI_Image*,jint,jint,jfloat,jfloat,jint)`` and ``DW_DRAWING_drawScaledImageBilinear(MICROUI_GraphicsContext*,MICROUI_Image*,jint,jint,jfloat,jfloat,jint)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_rotateImage(void*,int32_t,void*,int32_t,void*)``: replaced by ``DW_DRAWING_drawRotatedImageNearestNeighbor(MICROUI_GraphicsContext*,MICROUI_Image*,jint,jint,jint,jint,jfloat,jint)`` and ``DW_DRAWING_drawRotatedImageBilinear(MICROUI_GraphicsContext*,MICROUI_Image*,jint,jint,jint,jint,jfloat,jint)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_convertARGBColorToDisplayColor(int32_t)`` and ``LLDISPLAY_EXTRA_IMPL_convertDisplayColorToARGBColor(int32_t)``: replaced respectively by ``LLUI_DISPLAY_IMPL_convertARGBColorToDisplayColor(uint32_t)`` and ``LLUI_DISPLAY_IMPL_convertDisplayColorToARGBColor(uint32_t)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_prepareBlendingOfIndexedColors(void*,void*)``: replaced by ``LLUI_DISPLAY_IMPL_prepareBlendingOfIndexedColors(uint32_t*,uint32_t*)`` (_optional_).
	* [Changed] ``LLDISPLAY_EXTRA_IMPL_decodeImage(int32_t,int32_t,int32_t,void*)``: replaced by ``LLUI_DISPLAY_IMPL_decodeImage(uint8_t*,uint32_t,MICROUI_ImageFormat,MICROUI_Image*,bool*)`` (_optional_).
	* [Removed] ``LLDISPLAY_EXTRA_IMPL_getGraphicsBufferMemoryWidth(void)`` and ``LLDISPLAY_EXTRA_IMPL_getGraphicsBufferMemoryHeight(void)``: replaced by elements in structure ``LLUI_DISPLAY_SInitData`` (_optional_).
	* [Removed] ``LLDISPLAY_EXTRA_IMPL_backlightOn(void)`` and ``LLDISPLAY_EXTRA_IMPL_backlightOff(void)``.
	* [Removed] ``LLDISPLAY_EXTRA_IMPL_enterDrawingMode(void)`` and ``LLDISPLAY_EXTRA_IMPL_exitDrawingMode(void)``.
	* [Removed] ``LLDISPLAY_EXTRA_IMPL_error(int32_t)``.
	* [Removed] ``LLDISPLAY_EXTRA_IMPL_waitPreviousDrawing(void)``: implementation has to call ``LLUI_DISPLAY_notifyAsynchronousDrawingEnd(bool)`` instead.

* ``LLDISPLAY_impl.h`` and ``intern/LLDISPLAY_impl.h`` merged in ``LLUI_DISPLAY_impl.h``

	* [Changed] ``LLDISPLAY_IMPL_initialize(void)``: replaced by ``LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData*)`` (_mandatory_).
	* [Changed] ``LLDISPLAY_IMPL_flush(int32_t,int32_t,int32_t,int32_t,int32_t)``: replaced by ``LLUI_DISPLAY_IMPL_flush(MICROUI_GraphicsContext*,uint8_t*, uint32_t,uint32_t,uint32_t,uint32_t)`` (_mandatory_).
	* [Removed] ``LLDISPLAY_IMPL_getWidth(void)``, ``LLDISPLAY_IMPL_getHeight(void)`` and ``LLDISPLAY_IMPL_getGraphicsBufferAddress(void)``: replaced by elements in structure ``LLUI_DISPLAY_SInitData``.
	* [Removed] ``LLDISPLAY_IMPL_synchronize(void)``: implementation has to call ``LLUI_DISPLAY_flushDone(bool)`` instead.

* ``LLDISPLAY_UTILS.h`` and ``intern/LLDISPLAY_UTILS.h`` merged in ``LLUI_DISPLAY.h``

	* [Changed] ``LLDISPLAY_UTILS_getBufferAddress(int32_t)``: replaced by ``LLUI_DISPLAY_getBufferAddress(MICROUI_Image*)``.
	* [Changed] ``LLDISPLAY_UTILS_setDrawingLimits(int32_t,int32_t,int32_t,int32_t,int32_t)``: replaced by ``LLUI_DISPLAY_setDrawingLimits(MICROUI_GraphicsContext*,jint,jint,jint,jint)``.
	* [Changed] ``LLDISPLAY_UTILS_blend(int32_t,int32_t,int32_t)``: replaced by ``LLUI_DISPLAY_blend(uint32_t,uint32_t,uint32_t)``.
	* [Changed] ``LLDISPLAY_UTILS_allocateDecoderImage(void*)``: replaced by ``LLUI_DISPLAY_allocateImageBuffer(MICROUI_Image*,uint8_t)``.
	* [Changed] ``LLDISPLAY_UTILS_flushDone(void)``: replaced by ``LLUI_DISPLAY_flushDone(bool)``.
	* [Changed] ``LLDISPLAY_UTILS_drawingDone(void)``: replaced by ``LLUI_DISPLAY_notifyAsynchronousDrawingEnd(bool)``.
	* [Removed] ``LLDISPLAY_UTILS_getWidth(int32_t)``, ``LLDISPLAY_UTILS_getHeight(int32_t)`` and ``LLDISPLAY_UTILS_getFormat(int32_t)``: use ``MICROUI_Image`` elements instead.
	* [Removed] ``LLDISPLAY_UTILS_enterDrawingMode(void)`` and ``LLDISPLAY_UTILS_exitDrawingMode(void)``.
	* [Removed] ``LLDISPLAY_UTILS_setClip(int32_t,int32_t,int32_t,int32_t,int32_t)``.
	* [Removed] ``LLDISPLAY_UTILS_getClipX1/X2/Y1/Y2(int32_t)``: use ``MICROUI_GraphicsContext`` elements instead.
	* [Removed] ``LLDISPLAY_UTILS_drawPixel(int32_t,int32_t,int32_t)`` and ``LLDISPLAY_UTILS_readPixel(int32_t,int32_t,int32_t)``.
 
* ``LLDW_PAINTER_impl.h``

	* [Added] List of ``ej.api.drawing`` library's native functions implemented in module `com.microej.clibrary.llimpl#microui`_.

* ``LLLEDS_impl.h`` and ``intern/LLLEDS_impl.h`` merged in ``LLUI_LED_impl.h``

	* [Changed] ``LLLEDS_MIN_INTENSITY`` and ``LLLEDS_MAX_INTENSITY``: replaced respectively by ``LLUI_LED_MIN_INTENSITY`` and ``LLUI_LED_MAX_INTENSITY``.
	* [Changed] ``LLLEDS_IMPL_initialize(void)``: replaced by ``LLUI_LED_IMPL_initialize(void)``.
	* [Changed] ``LLLEDS_IMPL_getIntensity(int32_t)``: replaced by ``LLUI_LED_IMPL_getIntensity(jint)``.
	* [Changed] ``LLLEDS_IMPL_setIntensity(int32_t,int32_t)``: replaced by ``LLUI_LED_IMPL_setIntensity(jint,jint)``.

* ``LLINPUT.h`` and ``intern/LLINPUT.h`` merged in ``LLUI_INPUT.h``

	* [Changed] ``LLINPUT_sendEvent(int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendEvent(jint,jint)``.
	* [Changed] ``LLINPUT_sendEvents(int32_t,int32_t*,int32_t)``: replaced by ``LLUI_INPUT_sendEvents(jint,jint*,jint)``.
	* [Changed] ``LLINPUT_sendCommandEvent(int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendCommandEvent(jint,jint)``.
	* [Changed] ``LLINPUT_sendButtonPressedEvent(int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendButtonPressedEvent(jint,jint)``.
	* [Changed] ``LLINPUT_sendButtonReleasedEvent(int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendButtonReleasedEvent()jint,jint``.
	* [Changed] ``LLINPUT_sendButtonRepeatedEvent(int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendButtonRepeatedEvent(jint,jint)``.
	* [Changed] ``LLINPUT_sendButtonLongEvent(int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendButtonLongEvent(jint,jint)``.
	* [Changed] ``LLINPUT_sendPointerPressedEvent(int32_t,int32_t,int32_t,int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendPointerPressedEvent(jint,jint,jint,jint,LLUI_INPUT_Pointer)``.
	* [Changed] ``LLINPUT_sendPointerReleasedEvent(int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendPointerReleasedEvent(jint,jint)``.
	* [Changed] ``LLINPUT_sendPointerMovedEvent(int32_t,int32_t,int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendPointerMovedEvent(jint,jint,jint,LLUI_INPUT_Pointer)``.
	* [Changed] ``LLINPUT_sendTouchPressedEvent(int32_t,int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendTouchPressedEvent(jint,jint,jint)``.
	* [Changed] ``LLINPUT_sendTouchReleasedEvent(int32_t)``: replaced by ``LLUI_INPUT_sendTouchReleasedEvent(jint)``.
	* [Changed] ``LLINPUT_sendTouchMovedEvent(int32_t,int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendTouchMovedEvent(jint,jint,jint)``.
	* [Changed] ``LLINPUT_sendStateEvent(int32_t,int32_t,int32_t)``: replaced by ``LLUI_INPUT_sendStateEvent(jint,jint,jint)``.
	* [Changed] ``LLINPUT_getMaxEventsBufferUsage(void)``: replaced by ``LLUI_INPUT_getMaxEventsBufferUsage(void)``.
 
* ``LLINPUT_impl.h`` and ``intern/LLINPUT_impl.h`` merged in ``LLUI_INPUT_impl.h``

	* [Changed] ``LLINPUT_IMPL_initialize(void)``: replaced by ``LLUI_INPUT_IMPL_initialize(void)`` (_mandatory_).
	* [Changed] ``LLINPUT_IMPL_getInitialStateValue(int32_t,int32_t)``: replaced by ``LLUI_INPUT_IMPL_getInitialStateValue(jint,jint)`` (_mandatory_).
	* [Changed] ``LLINPUT_IMPL_enterCriticalSection(void)``: replaced by ``LLUI_INPUT_IMPL_enterCriticalSection(void)`` (_mandatory_).
	* [Changed] ``LLINPUT_IMPL_leaveCriticalSection(void)``: replaced by ``LLUI_INPUT_IMPL_leaveCriticalSection(void)`` (_mandatory_).
 
* ``LLUI_DISPLAY.h`` 

	* [Added] Renaming of ``LLDISPLAY_UTILS.h``.
	* [Added] Several functions to interact with the graphical engine and to get information on images, graphics context, clip, etc.
	* [Added] ``LLUI_DISPLAY_requestFlush(bool)``: requests a call to ``LLUI_DISPLAY_IMPL_flush()``.
	* [Added] ``LLUI_DISPLAY_requestRender(void)``: requests a call to ``Displayable.render()``.
	* [Added] ``LLUI_DISPLAY_freeImageBuffer(MICROUI_Image*)``: frees an image previously allocated by ``LLUI_DISPLAY_allocateImageBuffer(MICROUI_Image*,uint8_t)``.
	* [Added] ``LLUI_DISPLAY_requestDrawing(MICROUI_GraphicsContext*,SNI_callback)``: allows to take the hand on the shared drawing buffer.
	* [Added] ``LLUI_DISPLAY_setDrawingStatus(DRAWING_Status)``: specifies the drawing status to the graphical engine.
 
* ``LLUI_DISPLAY_impl.h``

	* [Added] Merge of ``LLDISPLAY_EXTRA_impl.h`` and ``LLDISPLAY_impl.h``.
	* [Added] Structure ``LLUI_DISPLAY_SInitData``: implementation has to fill it in ``LLUI_DISPLAY_IMPL_initialize(LLUI_DISPLAY_SInitData*)``.
	* [Added] ``LLUI_DISPLAY_IMPL_binarySemaphoreTake(void*)`` and ``LLUI_DISPLAY_IMPL_binarySemaphoreGive(void*,bool)``: implementation has to manage a binary semaphore (_mandatory_).
	* [Added] ``LLUI_DISPLAY_IMPL_getNewImageStrideInBytes(MICROUI_ImageFormat,uint32_t,uint32_t,uint32_t)``: allows to set an image stride different than image side (_optional_).

* ``LLUI_PAINTER_impl.h``

	* [Added] List of ``ej.api.microui`` library's native functions implemented in module `com.microej.clibrary.llimpl#microui`_.
	* [Added] ``MICROUI_ImageFormat``: MicroUI `Image`_ pixel format.
	* [Added] ``MICROUI_Image``: MicroUI `Image`_ representation.
	* [Added] ``MICROUI_GraphicsContext``: MicroUI `GraphicsContext`_ representation.

* ``ui_drawing_soft.h``

	* [Added] List of internal graphical engine software algorithms to perform some drawings (related to library ``ej.api.microui``).

* ``ui_drawing.h``

	* [Added] List of ``ej.api.microui`` library's drawing functions to optionally implement in platform.

Custom Native Drawing Functions
"""""""""""""""""""""""""""""""

* In custom UI native methods, replace ``LLDISPLAY_UTILS_getBufferAddress(xxx);`` by ``(uint32_t)LLUI_DISPLAY_getBufferAddress(xxx)`` (new function returns ``uint8_t*``), where ``uint32_t xxx`` is replaced by ``MICROUI_Image* xxx`` or by ``MICROUI_GraphicsContext* xxx``.
* Replace ``LLDISPLAY_UTILS_getFormat(xxx)`` by ``xxx->format``, where ``uint32_t xxx`` is replaced by ``MICROUI_Image* xxx`` or by ``MICROUI_GraphicsContext* xxx``.
* Replace call to ``LLDISPLAY_allocateDecoderImage`` by a call to ``LLUI_DISPLAY_allocateImageBuffer``
* Optional: implement drawing functions listed in ``ui_drawing.h`` following the available examples in ``LLUI_PAINTER_impl.c`` and ``LLDW_PAINTER_impl.c`` files comments.

Application
"""""""""""

* See application :ref:`section_mui_migrationguide`.

.. _section_ui_migration_12x:

From 11.x to 12.x
=================

Platform Configuration Project
""""""""""""""""""""""""""""""

* Update Architecture version: 7.11.0 or higher.

Front Panel
"""""""""""

* Create a new Front Panel Project (next sections explain how to update each widget):

    1. Verify that FrontPanelDesigner is at least version 6: :guilabel:`Help` > :guilabel:`About` > :guilabel:`Installations Details` > :guilabel:`Plug-ins`.
    2. Create a new front panel project: :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...` > :guilabel:`MicroEJ` > :guilabel:`MicroEJ Front Panel Project`, choose a name and press :guilabel:`Finish`.
    3. Move files from ``[old project]/src`` to ``[new project]/src/main/java``.
    4. Move files from ``[old project]/resources`` to ``[new project]/src/main/resources``.
    5. Move files from ``[old project]/definitions`` to ``[new project]/src/main/resources``, **except** your ``xxx.fp`` file.
    6. If existing delete file ``[new project]/src/main/java/microui.properties``.
    7. Delete file ``[new project]/src/main/resources/.fp.xsd``.
    8. Delete file ``[new project]/src/main/resources/.fp1.0.xsd``.
    9. Delete file ``[new project]/src/main/resources/widgets.desc``.
    10. Open ``[old project]/definitions/xxx.fp``.
    11. Copy ``device`` attributes (``name`` and ``skin``) from ``[old project]/definitions/xxx.fp`` to ``[new project]/src/main/resources/xxx.fp``.
    12. Copy content of ``body`` (not ``body`` tag itself) from ``[old project]/definitions/xxx.fp`` under ``device`` group of  ``[new project]/src/main/resources/xxx.fp``.

* Widget "led2states":

    1. Rename ``led2states`` by ``ej.fp.widget.LED``.
    2. Rename the attribute ``id`` by ``label``.

* Widget "pixelatedDisplay":

    1. Rename ``pixelatedDisplay`` by ``ej.fp.widget.Display``.
    2. Remove the attribute ``id``.
    3. (*if set*) Remove the attribute ``initialColor`` if its value is ``0``
    4. (*if set*) Rename the attribute ``mask`` by ``filter``; this image must have the same size in pixels than display itself (``width`` * ``height``).
    5. (*if set*) Rename the attribute ``realWidth`` by ``displayWidth``.
    6. (*if set*) Rename the attribute ``realHeight`` by ``displayHeight``.
    7. (*if set*) Rename the attribute ``transparencyLevel`` by ``alpha``; change the value: ``newValue = 255 - oldValue``.
    8. (*if set*) Remove the attribute ``residualFactor`` (not supported).
    9. (*if set*) If ``extensionClass`` is specified: follow next notes.

* Widget "pixelatedDisplay": ``ej.fp.widget.Display`` Extension Class:

    1. Open the class
    2. Extends ``ej.fp.widget.MicroUIDisplay.AbstractDisplayExtension`` instead of ``com.is2t.microej.frontpanel.display.DisplayExtension``.
    3. Rename method ``convertDisplayColorToRGBColor`` to ``convertDisplayColorToARGBColor``.
    4. Rename method ``convertRGBColorToDisplayColor`` to ``convertARGBColorToDisplayColor``.

* Widget "pointer":

    1. Rename ``pointer`` by ``ej.fp.widget.Pointer``.
    2. Remove the attribute ``id``.
    3. (*if set*) Rename the attribute ``realWidth`` by ``areaWidth``.
    4. (*if set*) Rename the attribute ``realHeight`` by ``areaHeight``.
    5. Keep or remove the attribute ``listenerClass`` according next notes.

* Widget "pointer": ``ej.fp.widget.Pointer`` Listener Class:
  
    This extension class is useless if the implementation respects these rules:
	
    * *(a)* ``press`` method is sending a ``press`` MicroUI Pointer event.
    * *(b)* ``release`` method is sending a ``release`` MicroUI Pointer event.
    * *(c )* ``move`` method is sending a ``move`` MicroUI Pointer event.
    * *(d)* The MicroUI Pointer event generator name is ``POINTER`` when ``ej.fp.widget.Pointer``'s ``touch`` attribute is ``false`` (or not set).
    * *(e)* The MicroUI Pointer event generator name is ``TOUCH`` when ``ej.fp.widget.Pointer``'s ``touch`` attribute is ``true``.

    If only *(d)* or *(e)* is different: 
	
    1. Open the listener class.
    2. Extends the class ``ej.fp.widget.Pointer.PointerListenerToPointerEvents`` instead of implementing the interface ``com.is2t.microej.frontpanel.input.listener.PointerListener``.
    3. Implements the method ``getMicroUIGeneratorTag()``.

    In all other cases:
	
    1. Open the listener class.
    2. Implements the interface ``ej.fp.widget.Pointer.PointerListener`` instead of ``com.is2t.microej.frontpanel.input.listener.PointerListener``.

* Widget "push":

    1. Rename ``push`` by ``ej.fp.widget.Button``.
    2. Rename the attribute ``id`` by ``label``.
    3. (*if set*) Review ``filter`` image: this image must have the same size in pixels than the button ``skin``.
    4. (*if set*) Remove the attribute ``hotkey`` (not supported).
    5. Keep or remove the attribute ``listenerClass`` according next notes.

* Widget "push": ``ej.fp.widget.Button`` Listener Class:

    This extension class is useless if the implementation respects these rules:
	
    * *(a)* ``press`` method is sending a ``press`` MicroUI Buttons event with button ``label`` (equals to old button ``id``) as button index.
    * *(b)* ``release`` method is sending a ``release`` MicroUI Buttons event with button ``label`` (equals to old button ``id``) as button index.
    * *(c )* The MicroUI Buttons event generator name is ``BUTTONS``.

    If only *(c )* is different: 
	
    1. Open the listener class.
    2. Extends the class ``ej.fp.widget.Button.ButtonListenerToButtonEvents`` instead of implementing the interface ``com.is2t.microej.frontpanel.input.listener.ButtonListener``.
    3. Overrides the method ``getMicroUIGeneratorTag()``.

    In all other cases:
	
    1. Open the listener class.
    2. Implements the interface ``ej.fp.widget.Button.ButtonListener`` instead of ``com.is2t.microej.frontpanel.input.listener.ButtonListener``.

* Widget "repeatPush":

    1. Rename ``repeatPush`` by ``ej.fp.widget.RepeatButton``.
    2. (*if set*) Remove the attribute ``sendPressRelease`` (not supported).
    3. Same rules than widget *push*.

* Widget "longPush":

    1. Rename ``longPush`` by ``ej.fp.widget.LongButton``.
    2. Same rules than widget *push*.

* Widget "joystick":

    1. Rename ``joystick`` by ``ej.fp.widget.Joystick``.
    2. Remove the attribute ``id``.
    3. (*if set*) Rename the attribute ``mask`` by ``filter``; this image must have the same size in pixels than joystick ``skin``.
    4. (*if set*) Remove the attribute ``hotkeys`` (not supported).
    5. Keep or remove the attribute ``listenerClass`` according next notes.

* Widget "joystick": ``ej.fp.widget.Joystick`` Listener Class:

    This extension class is useless if the implementation respects these rules:
	
    * *(a)* ``press`` methods are sending some MicroUI Command events ``UP``, ``DOWN``, ``LEFT``, ``RIGHT`` and ``SELECT``.
    * *(b)* ``repeat`` methods are sending same MicroUI Command events ``UP``, ``DOWN``, ``LEFT``, ``RIGHT`` and ``SELECT``.
    * *(c )* ``release`` methods are sending nothing.
    * *(d)* The MicroUI Command event generator name is ``JOYSTICK``.

    If only *(d)* is different: 
	
    1. Open the listener class
    2. Extends the class ``ej.fp.widget.Joystick.JoystickListenerToCommandEvents`` instead of implementing the interface ``com.is2t.microej.frontpanel.input.listener.JoystickListener``.
    3. Overrides the method ``getMicroUIGeneratorTag()``.

    In all other cases:
	
    1. Open the listener class.
    2. Implements the interface ``ej.fp.widget.Joystick.JoystickListener`` instead of ``com.is2t.microej.frontpanel.input.listener.JoystickListener``.

* Others Widgets:
    
    These widgets may have not been migrated. Check in ``ej.tool.frontpanel.widget`` library if some widgets are compatible or write your own widgets.

Application
"""""""""""

* See application :ref:`section_mui_migrationguide`.
 
From 10.x to 11.x
=================

Platform Configuration Project
""""""""""""""""""""""""""""""

* Update Architecture version: 7.0.0 or higher.
 
From 9.x to 10.x
================

Platform Configuration Project
""""""""""""""""""""""""""""""

* Update Architecture version: 6.13.0 or higher.
* Edit ``display/display.properties``
* Add property ``imagesHeap.size=xxx``; this value fixes the images heap size when using the platform in command line (to build a firmware)
* In platform linker file (standalone mode with MicroEJ linker): remove the image heap reserved section and put the section ``.bss.microui.display.imagesHeap`` instead.

BSP
"""

* In BSP linker file: remove the image heap reserved section and put the section ``.bss.microui.display.imagesHeap`` instead
* Edit ``LLDISPLAY*.c``: remove the functions ``LLDISPLAY_IMPL_getWorkingBufferStartAddress`` and ``LLDISPLAY_IMPL_getWorkingBufferEndAddress``

Application
"""""""""""

* See application :ref:`section_mui_migrationguide`.

From 8.x to 9.x
===============

Application
"""""""""""

* See application :ref:`section_mui_migrationguide`.

From 7.x to 8.x
===============

Platform Configuration Project
""""""""""""""""""""""""""""""

* Update Architecture version: 6.4.0 or higher.
* Edit ``display/display.properties``: remove property ``mode=xxx``

BSP
"""

* Edit ``LLDISPLAY*.c``
* For LLDISPLAY ``SWITCH``
 
	- Remove the function ``LLDISPLAY_SWITCH_IMPL_getDisplayBufferAddress()``
	- Replace the function ``void LLDISPLAY_SWITCH_IMPL_getDisplayBufferAddress()`` by ``int32_t LLDISPLAY_IMPL_flush()``
	- In this function, return the old LCD frame buffer address
	- Replace the function ``LLDISPLAY_COPY_IMPL_getBackBufferAddress()`` by ``LLDISPLAY_IMPL_getGraphicsBufferAddress()``
	
* For LLDISPLAY ``COPY``

	- Replace the function ``void LLDISPLAY_COPY_IMPL_copyBuffer()`` by ``int32_t LLDISPLAY_IMPL_flush()``
	- In this function, return the back buffer address (given in argument)
	- Replace the function ``LLDISPLAY_COPY_IMPL_getBackBufferAddress()`` by ``LLDISPLAY_IMPL_getGraphicsBufferAddress()``
	
* For LLDISPLAY ``DIRECT`` 

	- Add the function ``void LLDISPLAY_IMPL_synchorize(void)`` (do nothing)
	- Add the function ``int32_t LLDISPLAY_IMPL_flush()``
	- In this function, just return the back buffer address (given in argument)
	
* Replace h file ``LLDISPLAY_SWITCH_IMPL.h``, ``LLDISPLAY_COPY_IMPL.h`` or ``LLDISPLAY_DIRECT_IMPL.h`` by ``LLDISPLAY_IMPL.h``
* Replace all functions ``LLDISPLAY_SWITCH_IMPL_xxx``, ``LLDISPLAY_COPY_IMPL_xxx`` and ``LLDISPLAY_DIRECT_IMPL_xxx`` by ``LLDISPLAY_IMPL_xxx``
* Remove the argument ``int32_t type`` from ``getWidth`` and ``getHeight``

STM32 Platforms with DMA2D only
"""""""""""""""""""""""""""""""

* In platform configuration project, edit ``display/display.properties``
* Add property ``hardwareAccelerator=dma2d``
* In BSP project, edit ``LLDISPLAY*.c``
* simplify following functions (see STM32F7Discovery board implementation)

   .. code-block:: c

      LLDISPLAY_EXTRA_IMPL_fillRect
      LLDISPLAY_EXTRA_IMPL_drawImage
      LLDISPLAY_EXTRA_IMPL_waitPreviousDrawing

* Add the following function

   .. code-block:: c

      void LLDISPLAY_EXTRA_IMPL_error(int32_t errorCode)
      {
         printf("lldisplay error: %d\n", errorCode);
         while(1);
      }
 
* Launch an application with images and fillrect
* Compile, link and debug the BSP
* Set some breakpoints on three functions
* Ensure the functions are called

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
