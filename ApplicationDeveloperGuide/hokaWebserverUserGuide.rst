.. _hokaWebserverUserGuide:

HOKA Web Server
===============

.. toctree::
   :maxdepth: 1
   :hidden:

HOKA is a tiny extensible Java web server for embedded applications.

It comes with the support of HTTP, HTTPS, Server session, and routing for REST API.

.. note::

    This is the documentation of the latest version of HOKA library 8.X.X

Intended Audience
#################
The intended audience for this document is Java developers who are familiar with socket communication, the HTTP 1.1 protocol, and web server concepts.

Getting Started
###############
Create a new MicroEJ application and add the HOKA library ivy dependency to your MicroEJ application

.. code-block:: xml

    <dependency org="ej.library.iot" name="hoka" rev="8.3.X"/>

.. code-block:: java

        public class MyServer {

          public static void main(String[] args) throws IOException {

              HttpServer http = HttpServer.builder().port(8080).build();

              http.get("/hello", new RequestHandler() {

                @Override
                public void process(HttpRequest request, HttpResponse response) {
                  response.setData("Hello world!");
                }
              });

              http.start();

          }
        }

Run the application and check the result at **http://localhost:8080/hello**

Routes Mapping
##############
In HOKA, an HTTP request is a combination of 4 elements:

* **Verb**: The HTTP verbs, GET, POST, PUT or DELETE...
* **Path**: The request path or URI. ``/hello/:username``
* **Handler**: The request handler process the request and respond to the client.
* **content type**: (optional) the route supported content type

.. note::

        Paths are matched in the order of their creation.
        The handler of the first matching path will be invoked.
        All the paths need to be registered before calling the ``start()`` method of the ``HttpServer`` instance.
        If no path matches the incoming request, the server will return a 404 Not Found response.

.. code-block:: java

        HttpServer http = HttpServer.builder().port(8080).build();

        http.get("/", new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            // read a resource

          }
        });

        http.post("/", new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            // write a resource
          }
        });

        http.put("/", new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            // update a resource
          }
        });

        http.delete("/", new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            // delete a resource
          }
        });


A path can be registered with **one single** specific content type in different request handlers on the same path.

For example, to map two content types on the same path,  do the following:

.. code-block:: java

        HttpServer http = HttpServer.builder().port(8080).build();

        http.get("/", "application/json", new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            // read a resource and return a json formatted response.
          }
        });

        http.get("/", "application/xml", new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            // read a resource and return a json formatted response.
          }
        });


Path Parameters
-----------------
The request path can contain named parameters called path parameters. 
Those parameters are made available through the ``request`` instance of the ``process()`` method of the ``RequestHandler``. 
The path parameter can be accessed by calling ``HttpRequest#getPathParam(String param)``

.. code-block:: java

        HttpServer http = HttpServer.builder().port(8080).build();

        http.get("/hello/:name", new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            String name = request.getPathParam("name");
            response.setData("Hello " + name);
          }
        });

Splat Parameters
----------------
The request path also supports splat parameters using wildcard '*'.
Those parameters are made available through the ``request`` instance of the ``process()`` method of the ``RequestHandler``. 
The splat parameters array can be accessed by calling ``HttpRequest#getSplatParams()``

.. code-block:: java

        HttpServer http = HttpServer.builder().port(8080).build();

        http.get("/greet/*/by/*", new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            String name = request.getSplatParams().get(0);
            String greeting = request.getSplatParams().get(1);
            response.setData(greeting + " " + name);
          }
        });

Request
#######
- ``HttpRequest#getMethod()``: returns the request method (1 for ``POST``, 2 for ``GET``, 3 for ``PUT`` and 4 for ``DELETE``. see HttpRequest for the full list).
- ``HttpRequest#getURI()``: returns the requested URI.
- ``HttpRequest#getQueryParams()``: returns the request query parameters map.
- ``HttpRequest#getQueryParam(String)``: returns the query parameter by the given name from the query parameters map.
- ``HttpRequest#getPathParam(String)``: returns the request path parameter by the given name.
- ``HttpRequest#getSplatParams()``: returns the list of splat parameters.
- ``HttpRequest#setAttribute(String, Object)``: set a server-side request attribute. can be used to passe data between handlers.  
- ``HttpRequest#getAttribute(String)``: get a server-side request attribute.  
- ``HttpRequest#getVersion()``: returns the HTTP protocol version of the request.
- ``HttpRequest#getHeaders()``: returns the request headers, all header field names are converted to lowercase.
- ``HttpRequest#getHeader(String)``: returns the value of the header with the given name.
- ``HttpRequest#parseBody(BodyParser)``: parses the body of the request with the given parser.
- ``HttpRequest#getRequestBody()``: return the request InputStream to be used for any custom request handling.

Body Parsers
------------
The ``HttpRequest#parseBody(BodyParser)`` is used to read the body (data) of a request.  

HOKA library provides 4 implementations of ``BodyParser``:

- ``StringBodyParser``: returns the full request body as a string.
- ``MultipartStringsParser``: parse a ``multipart/*`` request body, each part is returned as a string.
- ``MultiPartBodyParser``: parse a ``multipart/*`` body, and parse each part as header fields and an ``InputStream`` body.
- ``ParameterParser``: parse an ``application/x-www-form-urlencoded`` request body.

Cookies
--------
The cookies are lazily parsed the first time they are accessed.

- ``HttpRequest#getCookies()``: returns the list of cookies.
- ``HttpRequest#getCookie(String)``: returns the value of the cookie by the given name.
  
Response
########
Build a ``HttpResponse`` based on the request with the following data :

- ``data`` : the body of the response as a ``String``, ``byte[]`` or as an  ``InputStream``.
- ``status`` : the status of the response to send. HTTP response code.
- ``mimeType`` : the value of the ``content-type`` header.
- ``HttpResponse#addHeader(String name, String value)`` : adds a header with given name and value.
- ``HttpResponse#addCookie(Cookie)`` : adds a cookie to the response. USe ej.hoka.http.Cookie.Builder() to create a cookie instance.

.. code-block:: java
      
       // Use the cookie builder to create a cookie instance.
       Cookie cookie = Cookie.builder().name("cookieName").value("cookieValue")
                                       .expires(expirationDate)
                                       .maxAge(900)
                                       .domain("www.example.com")
                                       .path("/api")
                                       .sameSite(SameSite.Strict)
                                       .secure()
                                       .httpOnly()
                                       .build();

MIME Types
----------
The ``Mime`` class provides constant values for commonly used MIME types and utility methods to return the MIME type of a resource name based on file extensions.

The predefined MIME types are :

- MIME_PLAINTEXT = "text/plain"
- MIME_HTML = "text/html"
- MIME_XML = "text/xml"
- MIME_APP_JSON = "application/json"
- MIME_DEFAULT_BINARY = "application/octet-stream"
- MIME_CSS = "text/css"
- MIME_PNG = "image/png"
- MIME_JPEG = "image/jpeg"
- MIME_GIF = "image/gif"
- MIME_JS = "application/x-javascript"
- MIME_FORM_ENCODED_DATA = "application/x-www-form-urlencoded"
- MIME_MULTIPART_FORM_ENCODED_DATA = "multipart/form-data"

The method ``Mime#getMIMEType(String URI)`` returns the MIME
type of the given URI, assuming that the file extension in the URI was
previously registered with the
``Mime#mapFileExtensionToMIMEType(String fileExtension, String mimeType)``.
Only lower case file extensions are recognized.

For example, calling ``getMIMEType("/images/logo.png")`` will return the string
``"image/png"``.

The following table shows the predefined assignments between file extensions
and MIME types:

========= =========
Extension MIME type
========= =========
".png"    ``MIME_PNG``
".css"    ``MIME_CSS``
".gif"    ``MIME_GIF``
".jpeg"   ``MIME_JPEG``
".jpg"    ``MIME_JPEG``
".html"   ``MIME_HTML``
".htm"    ``MIME_HTML``
".js"     ``MIME_JS``
".txt"    ``MIME_PLAINTEXT``
".xml"    ``MIME_XML``
========= =========

Halt Request Processing Chain
#############################
to stop a request processing and return immediately. The following static methods form ``HttpServer`` class should be used.

This will cause the request handler to stop immediately and the response will be returned to the client without executing other filters.

This is useful for error handling for example.

.. code-block:: java

        halt();  <--- return a 200 OK response.
        halt(HTTPConstants.HTTP_STATUS_UNAUTHORIZED);
        halt(HTTPConstants.HTTP_STATUS_UNAUTHORIZED, "login required!");

Filters
#######
A filter is also a request handler that is executed before or after a registered request. 

It needs to be registered before calling the ``start()`` method on the server instance.

It can be used to pre-process or post-process a request.

Multiple filters can be registered. They will be executed in the order they were added in.

HOKA supports 4 types of filters.

* **before all requests**: runs before any registered path.
* **before a specific path**: runs before a specific registered path.
* **after a specific path**: runs after a specific registered path.
* **after all requests**: runs after any registered path. 

Before
------
Example of adding a filter that will be executed before any registered path.

Multiple before filters can be added by calling ``before()`` multiple times. They will be executed in their registration order.

.. code-block:: java

      HttpServer http = HttpServer.builder().port(8080).build();

      http.before(new RequestHandler() {

        @Override
        public void process(HttpRequest request, HttpResponse response) {
          boolean authenticated = false;
          // check if authenticated ...
          if (!authenticated) {
            halt(HTTPConstants.HTTP_STATUS_UNAUTHORIZED); // stop the processing and return an error.
          }
        }
      });  


Example of adding a filter that will be executed before a specific registered path.

Unlike global before filters, only one before filter by path can be registered.

.. code-block:: java

      HttpServer http = HttpServer.builder().port(8080).build();

      http.before("/private/*", new RequestHandler() {

        @Override
        public void process(HttpRequest request, HttpResponse response) {
          // check access privilege ...
          halt(HTTPConstants.HTTP_STATUS_FORBIDDEN); // stop the processing and return an error.
        }
      });

After
-----
Example of adding a filter that will be executed after any registered path.

Multiple global after filters can be added by calling ``after()`` multiple times. They will be executed in their registration order.

.. code-block:: java

        HttpServer http = HttpServer.builder().port(8080).build();

        http.after(new RequestHandler() {

          @Override
          public void process(HttpRequest request, HttpResponse response) {
            // do some post processing on the request/response
            response.addHeader("common header key", "common header value");
          }
        });

Example of adding a filter that will be executed after a specific registered path.

Unlike global after filters, only one after filter by path can be registered.

.. code-block:: java

      HttpServer http = HttpServer.builder().port(8080).build();

      http.after("/private/*", new RequestHandler() {

        @Override
        public void process(HttpRequest request, HttpResponse response) {
          // do some post processing on the request/response
          response.addHeader("special header key", "special header value");
        }
      });


Error Handling
##############

Not Found Error
---------------
The 404 not found error can be customized by using the ``HttpServer#notFoundError()`` method.

.. code-block:: java

      HttpServer http = HttpServer.builder().port(8080).build();

      // html, The html page can be loaded form a file
      http.notFoundError("<html><body><h1>404 Page doesn't exist</h1></body></html>");

      // json format
      http.notFoundError("{\"message\":\"404 Page doesn't exist\"}", "application/json");


Internal Server Error
---------------------
The 500 Internal Server Error can also be customized.

.. code-block:: java

      // html, The html page can be loaded form a file
      http.internalServerError("<html><body><h1>505 Something went wrong!</h1></body></html>");
      
      // json format
      http.internalServerError("{\"message\":\"505 Something went wrong!\"}", "application/json");


Exception Mapping
------------------
An exception can be mapped to a custom handler to return specific errors.

.. code-block:: java

      HttpServer http = HttpServer.builder().port(8080).build();

      http.get("/throwerror", new RequestHandler() {

        @Override
        public void process(HttpRequest request, HttpResponse response) {
          throw new MyCustomError();
        }
      });

      http.exception(MyCustomError.class, new RequestHandler() {

        @Override
        public void process(HttpRequest request, HttpResponse response) {
          // handle the custom error here.
        }
      });

Static Files
############
A specific static file handler can be set to serve files from the application classpath by using ``ClasspathFilesHandler`` class.

.. code-block:: java

    HttpServer http = HttpServer.builder() //
        .port(8080) //
        .staticFilesHandler(ClasspathFilesHandler.builder() // set the static file handler
            .rootDirectory("/public") // set the static file folder form src/main/resources
            .build())
        .build();


Note that the public directory name is not included in the request URL. 
to access a file in ``src/main/resources/public/css/main.css`` the url is ``http://localhost:8080/css/main.css``

An external file location can be used by providing your own implementation of ``StaticFilesHandler`` interface and adding the ``fs`` foundation library
to work with File* classes from ``java.io``.

Web Server Configuration
########################
``HttpServer`` class builder has the following options :

.. code-block:: java

        HttpServer http = HttpServer.builder() 
            .port(8080) // setup the port number to bind the server socket on. Use 0 for a random port
            .simultaneousConnections(3) // setup the max simultaneous connections accepted by the server
            .workerCount(3) // setup the number of threads to handle incoming connections
            .connectionTimeout(60 * 1000) // setup connection timeout
            .encodingRegistry(new EncodingRegistry()) // register a custom the content encoding & transfer-coding registry
            .secure(/**SSLContext#getServerSocketFactory()*/) // setup SSL / HTTPS
            .apiBase("/api/v1/") // setup a common URI base for all relative registered path. relative means, the path do not starting with a /
            .staticFilesHandler(staticFilesHandler) // setup the static files handler
            .withTrailingSlashSupport() // process route with trailing slash as different routes
            .withStrictAcceptContentEncoding() // activate strict content acceptance. return 406 Not Acceptable for unknown content-encoding
            .developmentMode()// enable development mode, send error stack trace to the client side as in html
            .build();
 

Trailing Slash Matching
-----------------------
By default, the HOKA server ignores the trailing forward slash at the ends of the request URI.

For example: 

* ``GET | host/hello`` 
* ``GET | host/hello/`` 

Will link to the same request handler.

This behavior can be deactivated by calling the method ``HttpServer#builder()#withTrailingSlashSupport()`` on the server builder.

Note that ``host`` and ``host/`` will link to the same request handler whatever the Trailing Slash Match is activated or not.

Development Mode
----------------
Development mode can be activated by calling ``HttpServer#builder()#developmentMode()```.

This will tell the HOKA server to send the exception stack trace to the client.

The stack trace is sent in a plain text response. This is useful when developing the web application; otherwise, a "500
Internal Error" response is sent.

Note: when development mode is active, internal error page customization is deactivated. The development mode page is returned instead.


Handle Encoding
###############

Content And Transfer Encoding
-----------------------------
The HTTP protocol specifies how to send the request/response payload (the
body) with a specific encoding. To guarantee that the receiver can understand
the encoded stream, HTTP has specified headers for encoding :
``content-encoding``, ``transfer-encoding`` and ``accept-encoding``.
The ``HttpRequest`` and ``HttpResponse`` classes uses encoding handlers stored
in the ``EncodingRegistry`` to, respectively, decode and encode the
payloads with the relevant handler (``ContentEncoding`` or
``TransferEnCoding``). For the response, the ``accept-encoding``
the header value is used to determine the available encoding with the highest quality (acceptance value).


By default, the registry contains the "identity" encoding handler and the "chunked" transfer-coding handlers.

Request And Response Encoding
-----------------------------
When parsing the request, ``HttpRequest`` wraps the body with the appropriate decoder or, if not found, sends a "406 Not Acceptable" response. The body-parser will receive the wrapped (decoded) stream as input to not have to deal with encodings. The same for ``HttpResponse`` uses the encoder wrapper to
write the response into the encoded stream sent to the socket. Also, when using
an input stream with unknown length as the response's data, the transfer
encoding used to send the response is "chunked"; otherwise, it is "identity".
When using a String as the response data, use the
``HttpResponse#setData(String, String)`` to specify the encoding of the
string (by default, ``ISO-8859-1`` is used).

URL Encoding
------------
The percent-encoded special characters in the URI and in the query (parameters)
are automatically decoded at parsing.

Session
#######
HOKA provides tools to enable session management on the HTTP server.

Here is an example of how to use it.

.. code-block:: java
        
        // create a new session and store the user data in a session
        final SessionHandler sessionHandler = new SessionHandler(new SecureRandom());
        final Session session = this.sessionHandler.newSession();

        //  for example from a login request handler
        // ...  authenticate a user and store it user name into a session attribute
        session.setAttribute("username", username);
        // add a session cookie to the HttpResponse
        response.addCookie("jsessionid", session.getId(), 0, false, true);


        // from a protected request handler
        // Get the session if from the cookie
        String sessionId = request.getCookie("jsessionid");
        Session session = this.session.getSession(sessionId); // get the session by it's id
        // check if the user exists in the server session.
        String username = (String) session.getAttribute("username"); // access the username for example.


HOKA Configuration
##################
The server can be configured by creating a property file in `src/main/resources` named `hoka.properties`  

.. code-block::

              # Copyright 2021 MicroEJ Corp. All rights reserved.
              # Use of this source code is governed by a BSD-style license that can be found with this software.

              # HOKA Server properties

              # Use this property to set the logging level of the server.
              # TRACE, DEBUG, INFO, WARN, ERROR, NONE
              # the lower level activate all the others.
              hoka.logger.level=INFO

              # use this property to set a custom logger. The custom logger must implement the interface ej.hoka.log.Logger
              # if not set HOKA use a SimpleLogger implementation that logs to the standard output
              # Ensure that your logger is kept by the Soar by adding it to *.types.list properties file in the app resources.
              #hoka.logger.class=

              # I/O buffer size used to read/write data from/to request/response
              #hoka.buffer.size=4096

..
   | Copyright 2019-2023, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.