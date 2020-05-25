* To avoid bad formatting, please open question_1.md in a text editor (e.g.
  emacs)
* The error was caused during compilation since I was using C++11 constructs in
  my code with a corresponding compilation flag which did not work on Aludra
* I went through my code and basically replaced all C++11 standards
* I added CustomTuple.h and CustomTuple.cpp since a vector couldn't
  template a local struct (called tuple) which is what I had originally
* I modified Puzzle.h to replace unordered_map with set
* I modified Puzzle.cpp to modify the randomization code (originally
  C++11 based)
* I modified main.cpp to add an srand() seed and a print statement
