.. _display_lut:

LUT
===

The display module allows to target LCD which uses a pixel indirection
table (LUT). This kind of LCD are considered as generic but not standard
(see `??? <#display_pixel_structure>`__). By consequence, the driver
must implement functions that convert MicroUI's standard 32 bits ARGB
colors (see `??? <#LLDISPLAY-API-SECTION>`__) to LCD color
representation. For each application ARGB8888 color, the display driver
has to find the corresponding color in the table. The display module
will store the index of the color in the table instead of using the
color itself.

When an application color is not available in the display driver table
(LUT), the display driver can try to find the nearest color or return a
default color. First solution is often quite difficult to write and can
cost a lot of time at runtime. That's why the second solution is
preferred. However, a consequence is that the application has only to
use a range of colors provided by the display driver.

MicroUI and the display module uses blending when drawing some texts or
anti-aliased shapes. For each pixel to draw, the display stack blends
the current application foreground color with the targeted pixel current
color or with the current application background color (when enabled).
This blending *creates* some intermediate colors which are managed by
the display driver. Most of time the default color will be returned and
so the rendering will be wrong. To prevent this use case, the display
module offers a specific LLAPI
``LLDISPLAY_EXTRA_IMPL_prepareBlendingOfIndexedColors(void* foreground, void* background)``.
This API is only used when a blending is required and when the
background color is enabled. Display module calls the API just before
the blending and gives as parameter the pointers on the both ARGB
colors. The display driver should replace the ARGB colors by the LUT
indexes. Then the display module will only use the indexes between the
both indexes. For instance, when the returned indexes are ``20`` and
``27``, the display stack will use the indexes ``20`` to ``27``, where
all indexes between ``20`` and ``27`` target some intermediate colors
between the both original ARGB colors.

This solution requires several conditions:

-  Background color is enabled and it is an available color in the LUT.

-  Application can only use foreground colors provided by the LUT. The
   platform designer should give to the application developer the
   available list of colors the LUT manages.

-  The LUT must provide a set blending ranges the application can use.
   Each range can have its own size (different number of colors between
   two colors). Each range is independent. For instance if the
   foreground color ``RED`` (``0xFFFF0000``) can be blended with two
   background colors ``WHITE`` (``0xFFFFFFFF``) and ``BLACK``
   (``0xFF000000``), two ranges must be provided. The both ranges have
   to contain the same index for the color ``RED``.

-  Application can only use blending ranges provided by the LUT.
   Otherwise the display driver is not able to find the range and the
   default color will be used to perform the blending.

-  Rendering of dynamic images (images decoded at runtime) may be wrong
   because the ARGB colors may be out of LUT range.
