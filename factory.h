#include <map>
#include <memory>

#define DECLARE_FACTORY(Base, KeyType) \
  template<> std::map<KeyType, std::shared_ptr<AbstractFactory<Base>>> FactoryStore<Base, KeyType>::_factories = {};\
  template<> class FactoryKeyType<Base> { public: typedef KeyType Type; };

#define DECLARE_FACTORY_2(Base, KeyType) \
  template<> std::map<KeyType, std::shared_ptr<AbstractFactory<Base>>> FactoryStore<Base, KeyType>::_factories = {};

#define REGISTER_FACTORY(Base, CType, Key) static FactoryRegisterer<Base, CType, FactoryKeyType<Base>::Type> Base##CType##_factory_registerer(Key);
#define REGISTER_FACTORY_2(Base, Type, KeyType, Key) static FactoryRegisterer<Base, Type, KeyType> Base##Type##KeyType##_factory_registerer(Key);

template<typename T>
class AbstractFactory {
  public:
    virtual std::shared_ptr<T> build()=0;
};

template<typename>
class FactoryKeyType {};

template<typename T, typename K = typename FactoryKeyType<T>::Type>
class FactoryStore {
  public:
    static std::shared_ptr<T> build(K type) {
      return _factories[type]->build();
    }

    static void register_factory(K key, std::shared_ptr<AbstractFactory<T>> factory) {
      _factories[key] = factory;
    }

  private:
    static std::map<K, std::shared_ptr<AbstractFactory<T>>> _factories;
};

template<typename T>
class Factory {
  public:
    template<typename K>
    static std::shared_ptr<T> build(K type) {
      return FactoryStore<T,K>::build(type);
    };
};

template<typename T, typename I>
class SimpleFactory : public AbstractFactory<T> {
  public:
    virtual std::shared_ptr<T> build() {
      return std::make_shared<I>();
    };
};

template<typename T, typename I, typename K>
class FactoryRegisterer {
  public:
    FactoryRegisterer(K key) {
      FactoryStore<T,K>::register_factory(key, std::make_shared<SimpleFactory<T, I>>());
    }
};

