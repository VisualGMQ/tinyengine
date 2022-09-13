#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/tool.hpp"
#include "engine/core/log.hpp"

namespace engine {

class DLLEXPORT Configer final {
public:
    enum class ElementType {
        Unknown = 0,
        Number,
        String,
        Bool,
    };
    struct Element {
        ElementType type;
        std::string name;
        std::variant<float, bool, std::string, std::vector<Element>> data;

        Element(const std::string& name): type(ElementType::Unknown), name(name) {}
        Element(const std::string& name, float value): type(ElementType::Number), name(name), data(value) {}
        Element(const std::string& name, bool value): type(ElementType::Bool), name(name), data(value) {}
        Element(const std::string& name, const std::string& value): type(ElementType::String), name(name), data(value) {}

        bool Bool() const {
            if (type != ElementType::Bool) {
                Loge("[Configer]: element type is not bool");
                return false;
            }
            return std::get<bool>(data);
        }

        float Number() const {
            if (type != ElementType::Number) {
                Loge("[Configer]: element type is not number");
                return 0;
            }
            return std::get<float>(data);
        }

        std::string String() const {
            if (type != ElementType::String) {
                Loge("[Configer]: element type is not string");
                return "";
            }
            return std::get<std::string>(data);
        }

    };

    Configer(const std::string& filename);

    bool Has(const std::string& name) {
        return elements_.find(name) != elements_.end();
    }

    template <typename T>
    void Add(const std::string& name, const T&);

    template <typename T>
    std::optional<T> Get(const std::string& name);

    template <typename T>
    T GetOr(const std::string& name, T value);

    void Write2File(const std::string& filename);

private:
    std::unordered_map<std::string, Element> elements_;
    std::string content_;

    void add(const std::string& name, const Element& elem);
    Element parse();
    unsigned int curIdx_;

    void skipWhiteSpace();
    char next(int = 1);
    bool isEOF() const;
    char curChar() const;
    char lookFor(int) const;

    std::string parseKey();
    std::string parseStr();
    float parseNumber();
    bool parseBool();
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
                    Logw("{} field is not number", name.c_str());
                    return std::nullopt;
                }
                break;
            case Configer::ElementType::String:
                if (!std::is_same_v<T, std::string>) {
                    Logw("{} field is not string", name.c_str());
                    return std::nullopt;
                }
                break;
            case Configer::ElementType::Bool:
                if (!std::is_same_v<T, bool>) {
                    Logw("{} field is not bool", name.c_str());
                    return std::nullopt;
                }
                break;
            default:
                Logw("{} type unknown", name.c_str());
                return std::nullopt;
        }
        return std::get<T>(it->second.data);
    }
}

template <typename T>
T Configer::GetOr(const std::string& name, T value) {
    auto it = elements_.find(name);
    if (it == elements_.end()) {
        return value;
    } else {
        switch (it->second.type) {
            case Configer::ElementType::Number:
                if (!std::is_arithmetic_v<T>) {
                    Logw("{} field is not number", name.c_str());
                    return value;
                }
                break;
            case Configer::ElementType::String:
                if (!std::is_same_v<T, std::string>) {
                    Logw("{} field is not string", name.c_str());
                    return value;
                }
                break;
            case Configer::ElementType::Bool:
                if (!std::is_same_v<T, bool>) {
                    Logw("{} field is not bool", name.c_str());
                    return value;
                }
                break;
            default:
                Logw("{} type unknown", name.c_str());
                return value;
        }
        return std::get<T>(it->second.data);
    }
}


}