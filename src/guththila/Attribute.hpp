#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

struct attr_t
{
  token_t *prefix;
  token_t *name;
  token_t *value;
  namespace_t *namesp;
};


#endif
