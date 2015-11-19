#ifndef _GENESDATABASE_HH_
#define _GENESDATABASE_HH_

#include <map>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <string>

#include "./Gene.hh"

class GenesDatabase
{
public:
  GenesDatabase()
    : _genes({
  	{"0000", {DIGIT, '0'}},
  	{"0001", {DIGIT, '1'}},
  	{"0010", {DIGIT, '2'}},
  	{"0011", {DIGIT, '3'}},
  	{"0100", {DIGIT, '4'}},
  	{"0101", {DIGIT, '5'}},
  	{"0110", {DIGIT, '6'}},
  	{"0111", {DIGIT, '7'}},
  	{"1000", {DIGIT, '8'}},
  	{"1001", {DIGIT, '9'}},
  	{"1010", {OPERATOR, '+'}},
  	{"1011", {OPERATOR, '-'}},
  	{"1100", {OPERATOR, '*'}},
  	{"1101", {OPERATOR, '/'}}})
    {}

  bool exists(Gene gene) const;
  Type getTypeOf(Gene gene) const;
  int getIntValueOf(Gene gene) const;
  char getCharValueOf(Gene gene) const;

private:
  const std::map<std::string, std::pair<Type, char> > _genes;
};

#endif
