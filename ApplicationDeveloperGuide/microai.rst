.. _microai_api:

MicroAI
=======

Introduction
------------

The MicroAI Library provides APIs to interact with trained Machine Learning models, especially to run inferences.

.. _microai_api_usage:

Usage
-----

The MicroAI Library is provided as a Foundation Library.

To use the `MicroAI Library <https://repository.microej.com/modules/ej/api/microai/>`_, add the following line to the project build file:

.. code-block:: kotlin

   implementation("ej.api:microai:2.1.0")

Building or running an Application which uses the MicroAI Library requires a SDK6 VEE Port that provides the :ref:`MicroAI Pack <pack_microai>`.

Machine Learning Model Format
-----------------------------

MicroAI API is designed to be **framework-agnostic**, meaning it does not rely on a specific Machine Learning framework like TensorFlow or ONNX.

The Machine Learning framework is integrated at the VEE Port level, as a C/C++ library.

The Application is responsible of loading the model file. 
Therefore, before developing an Application with MicroAI, check which model file formats are supported by your target VEE Port.

MicroEJ Simulator
~~~~~~~~~~~~~~~~~

If you need to use the MicroEJ Simulator, you must use a model in **TensorFlow Lite for Microcontrollers (TFLM)** format. 
Other model formats will not be compatible with the MicroEJ Simulator and cannot be executed within it.

Tensorflow Lite for Microcontrollers supports a limited subset of TensorFlow operations, which impacts the model architectures that it is possible to run.
The supported operators list corresponds to the list in the `all_ops_resolver.cc <https://github.com/tensorflow/tflite-micro/blob/cdc3a3203f7721d17f6058979385a79cbd217551/tensorflow/lite/micro/all_ops_resolver.cc>`_ file.

APIs
----

MLInferenceEngine
~~~~~~~~~~~~~~~~~

The first action when working with MicroAI is to load the trained Machine Learning model using `MLInferenceEngine`_ class. 

There are 2 ways to load a model:

* From an application resource with `MLInferenceEngine(String modelPath, int inferenceMemoryPoolSize)`_ constructor.
* From an InputStream using `MLInferenceEngine(InputStream is, int inferenceMemoryPoolSize)`_ constructor.

The `MLInferenceEngine`_ constructor will:

1. Map the model into a native data structure.
2. Build an interpreter to run the model with.
3. Allocate memory for the model's tensors.


Using an Input Stream Model
^^^^^^^^^^^^^^^^^^^^^^^^^^^

When using `MLInferenceEngine(InputStream is, int inferenceMemoryPoolSize)`_, the model is loaded inside the MicroAI heap.
The size of MicroAI heap is defined from the :ref:`MicroAI Configurations <microai_configuration>`.

Note that the call to `MLInferenceEngine(InputStream is, int inferenceMemoryPoolSize)`_ will block until the model is completely retrieved/loaded.

Using an Inference Memory Pool
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When using TensorFlow Lite, the tensors are allocated dynamically into the system heap.

However when using Tensorflow Lite Micro, we must configure a `inferenceMemoryPoolSize`, which is called Arena Size, where all the input, output and intermediate tensors will be allocated.
This helps achieve deterministic memory usage.

To figure out which minimal value can be set, try large enough values using the Simulator, until the `MLInferenceEngine`_ succeeds.
At which point you should see such log, which will help to fine tune the `inferenceMemoryPoolSize` value:

.. code-block:: java

        [microai mock] MicroInterpreter uses 1112 bytes, use this value to optimize the Arena Size

Note: This example is very specific to the backend used.

Code Example
^^^^^^^^^^^^
Once initialized, `MLInferenceEngine`_ allows to get input/output model tensors and to run inferences on the trained model.

For example, the following snippet loads a trained model from the application resources and runs an inference on it:

.. code-block:: java

        try(MLInferenceEngine mlInferenceEngine = new MLInferenceEngine("/model.tflite", MEMORY_POOL_SIZE)) { // Initialize the inference engine.
            InputTensor inputTensor = mlInferenceEngine.getInputTensor(0); // Get input tensor of the trained model.
            /*
             * Fill the input tensor
             */
            mlInferenceEngine.run(); // Run inference on the trained model.
            OutputTensor outputTensor = mlInferenceEngine.getOutputTensor(0); // Get output tensor of the trained model.
            /*
             * Process output data
             */
        }


Tensor
~~~~~~

Tensor parameters can be retrieved from the `Tensor`_ class. 

It allows to get some useful information such as the data type, the number of dimensions, the number of elements, the size in bytes or the quantization parameters.

There are 2 kinds of tensors:

* `InputTensor`_: Offers services to load input data inside MicroAI input tensors before running an inference. Tensor input data must be one of the types supported by MicroAI (see Tensor.DataType).
* `OutputTensor`_: Offers services to retrieve output data from MicroAI output tensors after running an inference. Tensor output data must be one of the types supported by MicroAI (see Tensor.DataType).

Classes Summary
~~~~~~~~~~~~~~~

Main classes:

* `MLInferenceEngine`_: Loads a model, get its tensors and runs inferences on it.
* `Tensor`_: Retrieves a tensor information.
* `InputTensor`_: Loads input data before running an inference.
* `OutputTensor`_: Retrieves output data after running an inference.

Stateless and immutable classes:

* `Tensor.DataType`_: Enumerates MicroAI data types.
* `Tensor.QuantizationParameters`_: Represents quantized parameters of a tensor.

.. _microai_configuration:

Configuration
-------------

The :ref:`MicroAI Pack <pack_microai>` can be configured by defining the following :ref:`Application Options <application_options>`:

- ``microai.heap.size``: defines the size of the MicroAI heap, in which the InputStream models are allocated.

Example
-------

For example, the following snippet runs inference on model that takes 1 quantized element as input and outputs 1 float value:

.. code-block:: java

        try(MLInferenceEngine mlInferenceEngine = new MLInferenceEngine("/model.tflite", MEMORY_POOL_SIZE)) { // Initialize the inference engine.
            InputTensor inputTensor = mlInferenceEngine.getInputTensor(0); // Get input tensor of the trained model.
            byte[] inputData = new byte[inputTensor.getNumberElements()]; // Create an array that fits size of input tensor.

            // Fill inputData with quantized value.
            float realValue = 10f;
            Tensor.QuantizationParameters quantizationParameters = inputTensor.getQuantizationParams(); // Get quantization parameters.
            inputData[0] = (byte) (realValue / quantizationParameters.getScale() + quantizationParameters.getZeroPoint()); // Quantize the input value.
            inputTensor.setInputData(inputData); // Load input data inside MicroAI input tensor.

            mlInferenceEngine.run(); // Run inference on the trained model.

            OutputTensor outputTensor = mlInferenceEngine.getOutputTensor(0); // Get output tensor of the trained model.
            float[] outputData = new float[outputTensor.getNumberElements()]; // Create an array that fits size of output tensor.

            // Retrieve and print inference result.
            outputTensor.getOutputData(outputData); // Retrieve output data from MicroAI output tensor.
            System.out.println("Inference result with " + realValue + " input is " + outputData[0]);
        }

.. _MLInferenceEngine: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microai/MLInferenceEngine.html
.. _MLInferenceEngine(String modelPath, int inferenceMemoryPoolSize): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microai/MLInferenceEngine.html#MLInferenceEngine-java.lang.String-int-
.. _MLInferenceEngine(InputStream is, int inferenceMemoryPoolSize): https://repository.microej.com/javadoc/microej_5.x/apis/ej/microai/MLInferenceEngine.html#MLInferenceEngine-java.io.InputStream-int-
.. _Tensor: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microai/Tensor.html
.. _InputTensor: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microai/InputTensor.html
.. _OutputTensor: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microai/OutputTensor.html
.. _Tensor.DataType: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microai/Tensor.DataType.html
.. _Tensor.QuantizationParameters: https://repository.microej.com/javadoc/microej_5.x/apis/ej/microai/Tensor.QuantizationParameters.html

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
