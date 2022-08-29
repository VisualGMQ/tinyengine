#include "engine/core/configer.hpp"

namespace engine {

Configer::Configer(const std::string& filename) {
    parse(ReadWholeFile(filename));
}

void Configer::Add(const std::string& name, float value) {
    add(name, value);
}

void Configer::Add(const std::string& name, const std::string& value) {
    add(name, value);
}

void Configer::Add(const std::string& name, const std::vector<Configer::Element>& value) {
    add(name, value);
}

void Configer::parse(const std::string& file) {
    // TODO not finish
}

}