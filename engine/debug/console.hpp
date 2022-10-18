#pragma once

#include "engine/ecs/entity.hpp"
#include "engine/ui/window.hpp"
#include "engine/ui/label.hpp"
#include "engine/ui/layout.hpp"
#include "engine/ui/edit.hpp"
#include "engine/core/scene.hpp"

namespace engine::debug {

class Command final {
public:
    std::string name;
    std::function<bool(const std::vector<std::string_view>&)> func;

    bool Execute(const std::vector<std::string_view>& args);
};

class CmdParser final {
public:
    void Parse(std::string_view text, std::string_view& outName, std::vector<std::string_view>& outArgs);

private:
    void skipWhite();
    int curChar() const;
    bool isBlank(int) const;
    void next(int = 1);
    bool isEOF() const { return curChar() == EOF; };
    std::string_view parseWord();

    std::string_view text_;
    int curIdx_;
};

class Console final {
public:
    static void Init();
    static void Quit() {}
    static void ExeCmd(std::string_view cmd, const std::vector<std::string_view>& args);
    static void Attach2Scene();
    static void RegistCmd(const Command& cmd);
    static void Clear();
    static void PutLine(const std::string& text);
    static void PutText(const std::string& text);

private:
    static UIEdit* editor_;
    static UIEdit* content_;
    static std::unordered_map<std::string, std::vector<Command>> cmds_;
};

void DebugAttachConsole();

}
