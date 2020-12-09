#pragma once
#include <map>
#include <string>
#include <functional>
#include <memory>

class Material;

struct MaterialFactory
{
    template<typename T>
    struct register_t
    {
        register_t(const std::string& key)
        {
            MaterialFactory::get().map_.emplace(key, &register_t<T>::create);
        }

        template<typename... Args>
        register_t(const std::string& key, Args... args)
        {
            MaterialFactory::get().map_.emplace(key, [=] { return new T(args...); });
        }
        inline static Material* create() { return new T; }
    };

    inline Material* produce(const std::string& key)
    {
        if (map_.find(key) == map_.end())
            throw std::invalid_argument("the message key is not exist!");

        return map_[key]();
    }

    std::unique_ptr<Material> produce_unique(const std::string& key)
    {
        return std::unique_ptr<Material>(produce(key));
    }

    std::shared_ptr<Material> produce_shared(const std::string& key)
    {
        return std::shared_ptr<Material>(produce(key));
    }
    typedef Material*(*FunPtr)();

    inline static MaterialFactory& get()
    {
        static MaterialFactory instance;
        return instance;
    }

private:
    MaterialFactory() {};
    MaterialFactory(const MaterialFactory&) = delete;
    MaterialFactory(MaterialFactory&&) = delete;

    std::map<std::string, FunPtr> map_;
};

//std::map<std::string, MaterialFactory::FunPtr> MaterialFactory::map_;

#define REGISTER_MATERIAL_VNAME(T) reg_msg_##T##_
#define REGISTER_MATERIAL(T, key, ...) static MaterialFactory::register_t<T> REGISTER_MATERIAL_VNAME(T)(key, ##__VA_ARGS__);

/*
Message* p = MaterialFactory::get().produce("message1");
p->foo();   //Message1
*/