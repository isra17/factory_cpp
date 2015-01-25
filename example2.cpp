#include <iostream>
#include <cassert>
#include "factory.h"

using namespace std;

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

DECLARE_FACTORY_2(Animal, int);
REGISTER_FACTORY_2(Animal, Duck, int, 1);
REGISTER_FACTORY_2(Animal, Cow, int, 2);
REGISTER_FACTORY_2(Animal, Snake, int, 3);

DECLARE_FACTORY_2(Animal, string);
REGISTER_FACTORY_2(Animal, Duck, string, "Duck");
REGISTER_FACTORY_2(Animal, Cow, string, "Cow");
REGISTER_FACTORY_2(Animal, Snake, string, "Snake");

int main() {
  assert(Factory<Animal>::build(1)->name() == "Duck");
  assert(Factory<Animal>::build(2)->name() == "Cow");
  assert(Factory<Animal>::build(3)->name() == "Snake");

  assert(Factory<Animal>::build<string>("Duck")->name() == "Duck");
  assert(Factory<Animal>::build<string>("Cow")->name() == "Cow");
  assert(Factory<Animal>::build<string>("Snake")->name() == "Snake");
  return 0;
}

