.. _audio_api:

Audio
=====

Introduction
------------

The Audio API Library provides APIs to record and play audio in an Application.

This API can be used in various use-cases, such as:

- playing a sound
- playing a music streamed over IP or Bluetooth
- making a call
- synthesizing speech (text-to-speech)
- recognizing speech (speech-to-text)
- using a voice assistant such as Alexa or ChatGPT

.. _audio_api_usage:

Usage
-----

The Audio API Library is provided as a Foundation Library.

To use the `Audio API Library <https://repository.microej.com/modules/ej/api/audio/>`_, add the following line to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: kotlin

         implementation("ej.api:audio:1.0.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.api" name="audio" rev="1.0.0"/>

Building or running an Application which uses the Audio API Library requires the VEE Port to provide the :ref:`Audio Pack <pack_audio>`.

APIs
----

This section explains how audio concepts are reified in the Audio API.

Audio Format
~~~~~~~~~~~~

When opening an audio stream, it is necessary to provide the format of the audio data.
In the Audio API, the format is specified by the `AudioFormat`_ class.

The main property of an audio format is the encoding that is used to represent the data.
Depending on the encoding used, the format may be described by an indeterminate number of parameters, such as the sample rate or the number of channels.

Although many `audio encoding standards <https://en.wikipedia.org/wiki/Audio_coding_format>`_ exist,
the Audio API only provides a single `AudioFormat`_ implementation, `PcmAudioFormat`_, which uses the `PCM <https://en.wikipedia.org/wiki/Pulse-code_modulation>`_ encoding.
The Application can define additional audio formats using other encodings, but these encodings must be supported by the VEE Port to be used by the Application.

For example, the following snippet defines the "PCM 16kHz mono 16-bit little-endian signed" audio format:

.. code-block:: java

	AudioFormat FORMAT = new PcmAudioFormat(16_000, 1, 16, false, true);

Audio Recording
~~~~~~~~~~~~~~~

An audio recording stream can be opened by creating an `AudioRecord`_ instance.
When creating an audio record, the format and the size of the native audio buffer must be provided.
Since creating an `AudioRecord`_ instance allocates native resources, it should be closed with the `AudioRecord.close()`_ method in order to free these resources.

While the audio record is open, the native implementation records audio data continuously from the input device and writes it in the buffer.
The `AudioRecord.readBuffer()`_ method can be used to retrieve and remove a chunk of audio data from the buffer.
This method blocks until the requested size has been read or until the audio record is closed.
If the audio data is not read fast enough by the application, the native implementation will discard the oldest audio data from the buffer.

For example, the following snippet records audio with an audio record and writes the audio data to a file:

.. code-block:: java

	try (OutputStream outputStream = new FileOutputStream("record.raw")) {
	    try (AudioRecord audioRecord = new AudioRecord(FORMAT, 1600)) {
	        byte[] buffer = new byte[480];
	        while (true) {
	            int bytesRead = audioRecord.readBuffer(buffer, 0, buffer.length); // read from audio record
	            outputStream.write(buffer, 0, bytesRead); // write to file
	        }
	    }
	}

.. note::

	In order to avoid discontinuities in the recorded data, it is recommended to have a dedicated thread reading the buffer of the audio record.
	This should not be done in the UI thread as reading is a blocking operation that would prevent the UI thread from performing other tasks.

Audio Playback
~~~~~~~~~~~~~~

An audio playback stream can be opened by creating an `AudioTrack`_ instance.
When creating an audio track, the format and the size of the native audio buffer must be provided.
Since creating an `AudioTrack`_ instance allocates native resources, it should be closed with the `AudioTrack.close()`_ method in order to free these resources.

While the audio track is open, the native implementation reads audio data continuously from the buffer and plays it on the output device.
The `AudioTrack.writeBuffer()`_ method can be used to write a chunk of audio data in the buffer.
This method blocks until the requested size has been written or until this audio track is closed.
If audio data is not written fast enough by the application, the output device may play undesired silences.
The `AudioTrack.waitForBufferFlushed()`_ method can be used to wait until all the audio data written in the buffer has been played back.
The volume of the playback can be configured by calling `AudioTrack.setVolume()`_.

For example, the following snippet reads audio data from a resource and plays the audio with an audio track:

.. code-block:: java

	try (InputStream inputStream = MyClass.class.getResourceAsStream("/track.raw")) {
	    try (AudioTrack audioTrack = new AudioTrack(FORMAT, 1600)) {
	        byte[] buffer = new byte[480];
	        while (true) {
	            int bytesRead = inputStream.read(buffer, 0, buffer.length); // read from resource
	            if (bytesRead == -1) { // EOF
	                break;
	            }
	            audioTrack.writeBuffer(buffer, 0, bytesRead); // write to audio track
	        }
	        audioTrack.waitForBufferFlushed(); // play remaining audio data before closing
	    }
	}

.. note::

	In order to avoid discontinuities in the audio playback, it is recommended to have a dedicated thread writing the buffer of the audio track.
	This should not be done in the UI thread as writing is a blocking operation that would prevent the UI thread from performing other tasks.

Classes Summary
~~~~~~~~~~~~~~~

Main classes:

- `AudioRecord`_: Represents an audio recording stream.
- `AudioTrack`_: Represents an audio playback stream.

Stateless and immutable classes:

- `AudioException`_: `RuntimeException`_ thrown when an error occurred during an audio operation.
- `AudioFormat`_: Specifies the data format of an audio stream.
- `PcmAudioFormat`_: `AudioFormat`_ which represents data with the `PCM <https://en.wikipedia.org/wiki/Pulse-code_modulation>`_ encoding.

Configuration
-------------

The :ref:`Audio Pack <pack_audio>` can be configured by defining the following :ref:`Application Options <application_options>`:

- ``audio.heap.size``: defines the size of the Audio heap, in which the native buffers of the audio streams are allocated.
- ``s3.audio.input.device``: defines the name of the Audio input device to use when running the Application on Simulator.
- ``s3.audio.output.device``: defines the name of the Audio output device to use when running the Application on Simulator.

Examples
--------

MicroEJ provides two examples which show how to use the Audio API: one example for audio recording and one for audio playback.

These examples can be found on `GitHub <https://github.com/MicroEJ/Example-Foundation-Libraries>`_.
Please refer to their own README for more information on these examples.

.. _RuntimeException: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/RuntimeException.html
.. _AudioRecord: https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioRecord.html
.. _AudioTrack: https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioTrack.html
.. _AudioException: https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioException.html
.. _AudioFormat: https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioFormat.html
.. _PcmAudioFormat: https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/format/PcmAudioFormat.html

.. _AudioRecord.close(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioRecord.html#close--
.. _AudioRecord.readBuffer(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioRecord.html#readBuffer-byte:A-int-int-
.. _AudioTrack.close(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioTrack.html#close--
.. _AudioTrack.writeBuffer(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioTrack.html#writeBuffer-byte:A-int-int-
.. _AudioTrack.waitForBufferFlushed(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioTrack.html#waitForBufferFlushed--
.. _AudioTrack.setVolume(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/audio/AudioTrack.html#setVolume-float-

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
