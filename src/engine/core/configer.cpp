#include "engine/core/configer.hpp"

namespace engine {

Configer::Configer(const std::string& filename): curIdx_(0) {
    content_ = ReadWholeFile(filename);
    while (!isEOF()) {
        Element elem = parse();
        add(elem.name, elem);
        skipWhiteSpace();
    }
}

template <>
void Configer::Add<float>(const std::string& name, const float& value) {
    add(name, Configer::Element(name, value));
}

template <>
void Configer::Add<double>(const std::string& name, const double& value) {
    add(name, Configer::Element(name, (float)value));
}

template <>
void Configer::Add<std::string>(const std::string& name, const std::string& value) {
}

template <>
void Configer::Add<bool>(const std::string& name, const bool& value) {
    add(name, Configer::Element(name, value));
}

void Configer::add(const std::string& name, const Element& elem) {
    if (Has(name)) {
        Logw("%s already exists", name.c_str());
    } else {
        elements_.emplace(name, elem);
    }
}

char Configer::next(int n) {
    if (isEOF()) {
        return EOF;
    } else {
        char c = curChar();
        curIdx_ += n;
        return c;
    }
}

bool Configer::isEOF() const {
    return curIdx_ >= content_.size();
}

char Configer::curChar() const {
    return isEOF() ? EOF : content_[curIdx_];
}

char Configer::lookFor(int idx) const {
    if (curIdx_ + idx >= content_.size()) {
        return EOF;
    } else {
        return content_[curIdx_ + idx];
    }
}

void Configer::skipWhiteSpace() {
    while (!isEOF() && isspace(curChar())) {
        next();
    }
}

Configer::Element Configer::parse() {
    std::string key = parseKey();
    skipWhiteSpace();
    if (curChar() != '=') {
        Loge("[Configer]: miss '=' after key");
        return Configer::Element(key);
    }
    next();
    skipWhiteSpace();
    char c = curChar();
    if (isdigit(c)) {
        float number = parseNumber();
        return Configer::Element(key, number);
    } else if (c == '\'' || c =='"') {
        std::string str = parseStr();
        return Configer::Element(key, str);
    } else if (c == 't' || c == 'f') {
        bool b = parseBool();
        return Configer::Element(key, b);
    } else {
        Loge("[Configer]: invalid value");
        return Configer::Element(key);
    }
}

std::string Configer::parseKey() {
    char c;
    std::string result;
    while (!isEOF() && isalnum(curChar())) {
        c = next();
        result += c;
    }
    return result;
}

std::string Configer::parseStr() {
    char beginChar = curChar();
    std::string result;

    next();
    char c;
    while (!isEOF() && (c = next()) != beginChar) {
        result += c;
    }
    if (c != beginChar) {
        Loge("[Config]: parse string error");
        return "";
    }
    return result;
}

float Configer::parseNumber() {
    float number = 0;
    char c;
    while (!isEOF() && isdigit(curChar())) {
        c = next();
        number = number * 10 + (c - '0');
    }
    if (curChar() == '.') {
        int n = 1;
        next();
        while (!isEOF() && isdigit(curChar())) {
            c = next();
            number = number + std::pow(0.1, n ++) * (c - '0');
        }
    }
    return number;
}

bool Configer::parseBool() {
    if (lookFor(0) == 't' &&
        lookFor(1) == 'r' &&
        lookFor(2) == 'u' &&
        lookFor(3) == 'e') {
        next(4);
        return true;
    }
    if (lookFor(0) == 'f' &&
        lookFor(1) == 'a' &&
        lookFor(2) == 'l' &&
        lookFor(3) == 's' &&
        lookFor(4) == 'e') {
        next(5);
        return false;
    }
    Loge("[Config]: parse bool failed");
    return false;
}

void Configer::Write2File(const std::string& filename) {
    std::ofstream file(filename);
    if (file.fail()) {
        Loge("output file %s open failed", filename.c_str());
    }
    for (auto& [name, value] : elements_) {
        file << name << " = ";
        switch (value.type) {
            case ElementType::Bool:
                file << value.Bool() << std::endl;
                break;
            case ElementType::String:
                file << value.String() << std::endl;
                break;
            case ElementType::Number:
                file << value.Number() << std::endl;
                break;
            default:
                Loge("[Config]: invalid element want write into file. Prevented it");
        }
    }
}

}