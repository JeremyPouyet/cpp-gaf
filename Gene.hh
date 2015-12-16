#ifndef _GENE_HH_
#define _GENE_HH_

#include <cstdint>

enum Type
{
  DIGIT,
  OPERATOR,
  UNKNOWN
};

#define GENE_TYPE uint16_t

typedef GENE_TYPE Gene;

#define GENE_SIZE (sizeof(GENE_TYPE) * 8)
#define MIN_GENE_VALUE std::numeric_limits<GENE_TYPE>::min()
#define MAX_GENE_VALUE std::numeric_limits<GENE_TYPE>::max()

#endif
