#include <iostream>
#include <string>

enum Type
{
  PROTOTYPE_1 = 0,
  PROTOTYPE_2
};

class Prototype
{
protected:
	std::string prototype_name_;
	float 		prototype_field_;
public:
  	Prototype(std::string prototype_name) : prototype_name_(prototype_name) {}
  	virtual ~Prototype() {}
  	virtual Prototype *Clone() const = 0;
  	virtual void Method(float prototype_field)
	{
		this->prototype_field_ = prototype_field;
		std::cout << "Call Method from " << prototype_name_ << " with field : " << prototype_field << std::endl;
  	}
};

class ConcretePrototype1 : public Prototype
{
private:
	float concrete_prototype_field1_;
public:
	ConcretePrototype1(std::string prototype_name, float concrete_prototype_field)
      : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field) {}
  	Prototype* Clone() const override
  	{
    	return new ConcretePrototype1(*this);
  	}
};

class ConcretePrototype2 : public Prototype
{
private:
	float concrete_prototype_field2_;
public:
	ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
      : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) {
  }
  Prototype* Clone() const override
  {
	return new ConcretePrototype2(*this);
  }
};

class PrototypeFactory
{
private:
	std::unordered_map<Type, Prototype*, std::hash<int>> prototypes_;
public:
	PrototypeFactory()
	{
		prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
		prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
	}

	Prototype* CreatePrototype(Type type)
	{
		return prototypes_[type]->Clone();
	}
};

int main()
{
  PrototypeFactory prototype_factory;
  Prototype *prototype;

  prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
  prototype->Method(90);

  prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
  prototype->Method(10);

  return 0;
}
