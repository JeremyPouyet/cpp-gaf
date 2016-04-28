# cpp-gaf

Genetic algorithm Framework written in c++, helps you to solve problems.

## Compilation

```shell
$> make
```
The Makefile will compile the framework, the tests problems and the project generator.

## Project generator

For a problem to be executable from the framework, it needs to be under the form of a package containing:
- one shared library (problem.so) -> to be load by the framework
- a problem.ini file -> to configure the simulation

To make the framework easier to use, a project generator has been created. It creates a default package that contains 4 files:
-  Makefile to compile the problem
-  problem.ini
-  a .hh file containing a class that inherits from the AProblem abstract class
-  a .cpp file that implements the .hh file

To use it, proceed as follow:

```shell
$> cd template/
$> ./generator test
Creation of the directory ../problems/test
Generation of file ../problems/test/Makefile
Generation of file ../problems/test/testProblem.cpp
Generation of file ../problems/test/testProblem.hh
Generation of file ../problems/test/problem.ini
```

But you can also create your own package.

## Use

```shell
$> ./open-gaf path/to/problem
```

For example, with the "test" project created in the Project generator section:

```shell
$> cd cpp-gaf && ./open-gaf ./problems/test/
```
#### Todo

- [ ] 32 bits supports
- [ ] command line option to enable/disable OpenMP
- [ ] change project name to open-gaf
- [ ] comments in template/generator.cpp
- [ ] comments in generated file ?
- [ ] command line options in template/generator.cpp (--verbose ? --nofunc function_name --nofile filename)
- [ ] add the "cut and splice" crossover in population
- [ ] new demo problem: traveling salesman -> need of a new mutation type
- [ ] add non uniform crossover (new option in .ini file when uniform crossover is selected)
- [ ] More documentation!! Readme + Wiki :)
- [ ] command line options in the framework to specify .so and .ini path or package path.
