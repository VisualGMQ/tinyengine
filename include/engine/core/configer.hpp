#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/tool.hpp"
#include "engine/core/log.hpp"

namespace engine {

class Configer final {
public:
    enum class ElementType {
        Unknown = 0,
        Number,
        String,
        List, 
    };
    struct Element {
        ElementType type;
        std::variant<float, std::string, std::vector<Element>> data;

        Element(): type(ElementType::Unknown) {}
        Element(float value): type(ElementType::Number), data(value) {}
        Element(const std::string& value): type(ElementType::String), data(value) {}
        Element(const std::vector<Element>& value): type(ElementType::List), data(value) {}
    };

    Configer(const std::string& filename);

    bool Has(const std::string& name) {
        return elements_.find(name) != elements_.end();
    }

    void Add(const std::string& name, float value);
    void Add(const std::string& name, const std::string& value);
    void Add(const std::string& name, const std::vector<Element>& value);

    template <typename T>
    std::optional<T> Get(const std::string& name);

private:
    std::unordered_map<std::string, Element> elements_;

    template <typename T>
    void add(const std::string& name, const T& value) {
        if (Has(name)) {
            Logw("%s already exists", name.c_str());
        } else {
            elements_.emplace(name, value);
        }
    }

    void parse(const std::string& content);
    unsigned int index_;
};

template <typename T>
std::optional<T> Configer::Get(const std::string& name) {
    auto it = elements_.find(name);
    if (it == elements_.end()) {
        return std::nullopt;
    } else {
        switch (it->second.type) {
            case Configer::ElementType::Number:
                if (!std::is_arithmetic_v<T>) {
                    Logw("%s field is not number", name.c_str());
                    return std::nullopt;
                }
                break;
            case Configer::ElementType::String:
                if (!std::is_same_v<T, std::string>) {
                    Logw("%s field is not string", name.c_str());
                    return std::nullopt;
                }
                break;
            case Configer::ElementType::List:
                if (!std::is_same_v<T, std::vector<Element>>) {
                    Logw("%s field is not list", name.c_str());
                    return std::nullopt;
                }
                break;
            default:
                Logw("%s type unknown", name.c_str());
                return std::nullopt;
        }
        return std::get<T>(it->second.data);
    }
}

}