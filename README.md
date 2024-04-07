## Task

   Implement a custom fixed-length signed integer type **int2023_t**.
   The size of the resulting type should not exceed 253 bytes.

   For the above type, the following set of functions and operators are required to be implemented

      1. Conversion from type int32_t
      2. Conversion from string
      3. Addition
      4. Subtraction
      5. Multiplication
      6. Division
      7. Outputting a number to a stream (not necessarily in the 10th number system)

## Instructions for execution

You are given a project template consisting of three directories:
- **bin**
- **lib**
- **tests**

Changing the project structure or adding new files is prohibited.

Required:
   1. Implement the **int2023_t** type, describing it in the header file **lib/number.h** (!Please note that such a structure already exists there, you need to supplement its description)
   2. Implement the above functions and operators by writing the implementation in **lib/number.cpp**

### Tests

The project contains a basic set of tests that will ensure that the implementation of functions is completed without obvious errors.
To run tests on the command line, you can perform the following operation:

***cmake --build . --target number_tests && ctest -V*** or use your IDE's tools

Until all tests pass and show laboratory results, it is impossible.
The tests can be supplemented if desired, but this is not necessary.

### If that wasn't enough

The **bin** directory contains a console application that you can also use at your discretion to test your code.
To start, run the following command:

***cmake --build . --target labwork2 && bin/labwork2*** or use IDE

## Note
  - Overflow - Undefined Behavior

## Restrictions
  - The use of standard containers (std::vector, std::list, etc.) is prohibited
  - Using std::bitset is prohibited

## Additional
  -cmake
  - GoogleTest
