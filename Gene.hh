#ifndef _GENE_HH_
#define _GENE_HH_

#include <bitset>

enum Type
{
  DIGIT,
  OPERATOR,
  UNKNOWN
};

#define GENE_SIZE 4
#define GENE_MAX_VALUE 255

typedef std::bitset<GENE_SIZE> Gene;

#endif
