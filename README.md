# shelly

A tiny shell for your processor! Aims to be a Unix-like experience. Currently
only targets RISC-V RV32IM capable processors.

This is my AP Computer Science Principles "Create" project, but also is good
for learning and will be as extensive as I feel I want to know about computers
at such a low level.

## AP CSP Requirements

The following are the requirements my teacher gave me for this project, along
with explanations of how I believe my porject implements them. 

- Input from one of the following:
  - the user (including user actions that trigger events),
  - a device,
  - an online data stream, or
  - a file

  This requirement is met first through user input. The shell and its tasks are
  based entirely in what the user tells it to execute. It is also met by the
  reading from a device. While it is hard to attach these terms to something so
  low-level, I would venture to say that reading from UART is device reading.

- Use at least one list (or other collection type) to represent a collection of
  data that is stored and used to manage program complexity and help fulfill the
  program's purpose

  Again, it is hard to translate these requirements to this kind of project,
  however I believe this, too, is fulfilled. Lists (or vectors—whatever you may
  call it) are implemented and used, primarily for input buffering. Using a list
  for input buffering manages program complexity by removing the need for a
  fixed-size buffer and management of such buffer. Further, lists are used to
  fulfill the program's purpose by allowing and managing arbitrary-length user
  inputs into the shell.

- At least one procedure that contributes to the program's intended purpose,
  where you have defined:
  - the procedure's name,
  - the return type (if necessary), and
  - one or more parameters

  I do not feel the need to explain myself as far as I have previously. A glance
  at the code will show many, many functions, each with its own name, a return
  type as required by C, and some with one or more parameters.

- An algorithm that includes sequencing, selection, and iteration that is in the
  body of the selected procedure

  ...

- Calls to your student-developed procedure

  ...

- Instructions for output (tactile, audible, visual, or textual) based on input
  and program functionality

  The program's output, written over UART, is a function of the user's input and
  adheres to the program functionality.
