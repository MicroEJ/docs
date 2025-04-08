.. _microai_api:

MicroAI
=======

Introduction
------------

The MicroAI Library provides APIs to interact with trained Machine Learning models, especially to run inferences.

Usage
-----

The MicroAI Library is provided as a Foundation Library.

To use the MicroAI Library, add the following line to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: kotlin

         implementation("com.microej.microai.microai-lib:1.0.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.microai" name="microai-lib" rev="1.0.0"/>

Building or running an Application which uses the MicroAI Library requires the VEE Port to provide the :ref:`MicroAI Pack <pack_microai>`.

Machine Learning Model Format
-----------------------------

MicroAI is designed to be **framework-agnostic**, meaning it does not rely on a specific Machine Learning framework like TensorFlow or ONNX.
Instead, the model format used by the MicroEJ Application depends on the VEE Port implementation of the MicroAI library. 
Please check which model formats are supported by your target VEE Port.

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

First action when dealing with MicroAI is to load the trained Machine Learning model using MLInferenceEngine class. 

There is 2 way to load a model, using an application resource with MLInferenceEngine(String modelPath) constructor or from an InputStream using MLInferenceEngine(InputStream is) constructor.
The 2 constructors map the model into a native data structure, build an interpreter to run the model with and allocate memory for the model's tensors.

InputStream constructor will block until the model is completely retrieved/loaded on the native side. 
It will load the model inside the MicroAI heap.
Size of MicroAI heap is defined from the :ref:`MicroAI Configurations <microai_configuration>`.

Once initialized, MLInferenceEngine allows to get input/output model tensors and to run inferences on the trained model.

For example, the following snippet loads a trained model from application resources and run inference on it:


.. code-block:: java

        try(MLInferenceEngine mlInferenceEngine = new MLInferenceEngine("/model.tflite")) { // Initialize the inference engine.
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

Tensor parameters can be retrieved from the Tensor class. 

It allows to get some usefull information such as the data type, the number of dimensions, the number of elements, the size in bytes or the quantization parameters.

There are 2 kinds of tensors:

* InputTensor: Offers services to load input data inside MicroAI input tensors before running an inference. Tensor input data must be one of the types supported by MicroAI (see Tensor.DataType).
* OutputTensor: Offers services to retrieve output data from MicroAI output tensors after running an inference. Tensor output data must be one of the types supported by MicroAI (see Tensor.DataType).

Classes Summary
~~~~~~~~~~~~~~~

Main classes:

* MLInferenceEngine: Loads a model, get its tensors and run inferences on it.
* Tensor: Retrieves tensor information.
* InputTensor: Loads input data before running an inference.
* OutputTensor: Retrieves output data after running an inference.

Stateless and immutable classes:

* Tensor.DataType: Enumerates MicroAI data types.
* Tensor.QuantizationParameters: Represents quantized parameters of a tensor.

.. _microai_configuration:

Configuration
-------------

The :ref:`MicroAI Pack <pack_microai>` can be configured by defining the following :ref:`Application Options <application_options>`:

- ``microai.heap.size``: defines the size of the MicroAI heap, in which the InputStream models are allocated.

Example
-------

For example, the following snippet runs inference on model that takes 1 quantized element as input and outputs 1 float value:

.. code-block:: java

        try(MLInferenceEngine mlInferenceEngine = new MLInferenceEngine("/model.tflite")) { // Initialize the inference engine.
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

            // Retrieve and prints inference result.
            outputTensor.getOutputData(outputData); // Retrieve output data from MicroAI output tensor.
            System.out.println("Inference result with " + realValue + " input is " + outputData[0]);
        }


..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
