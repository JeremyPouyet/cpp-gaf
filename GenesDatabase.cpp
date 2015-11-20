#include "./GenesDatabase.hh"

bool GenesDatabase::exists(Gene gene) const
{
  return _genes.find(gene.to_string()) != _genes.end();
}

Type GenesDatabase::getTypeOf(Gene gene) const
{
  if (exists(gene))
    return _genes.at(gene.to_string()).first;
  return UNKNOWN;
}

int GenesDatabase::getIntValueOf(Gene gene) const
{
  return _genes.at(gene.to_string()).second - '0';
}

char GenesDatabase::getCharValueOf(Gene gene) const
{
  return _genes.at(gene.to_string()).second;
}
