#include <iostream>
#include <cassert>
#include "factory.h"

class Animal {
  public:
    virtual std::string name() const=0;
};

class Duck : public Animal {
  public:
    std::string name() const override { return "Duck"; }
};

class Cow : public Animal {
  public:
    std::string name() const override { return "Cow"; }
};

class Snake : public Animal {
  public:
    std::string name() const override { return "Snake"; }
};

DECLARE_FACTORY(Animal, int);
REGISTER_FACTORY(Animal, Duck, 1);
REGISTER_FACTORY(Animal, Cow, 2);
REGISTER_FACTORY(Animal, Snake, 3);

int main() {
  assert(Factory<Animal>::build(1)->name() == "Duck");
  assert(Factory<Animal>::build(2)->name() == "Cow");
  assert(Factory<Animal>::build(3)->name() == "Snake");

  return 0;
}
