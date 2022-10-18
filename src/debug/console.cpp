#include "engine/debug/console.hpp"

namespace engine::debug {

UIEdit* Console::editor_ = nullptr;
UIEdit* Console::content_ = nullptr;
std::unordered_map<std::string, std::vector<Command>> Console::cmds_;

void Console::Init() {
    Command clearCmd;
    clearCmd.name = "clear";
    clearCmd.func = [](const std::vector<std::string_view>&){
        Console::Clear();
        return true;
    };
    Console::RegistCmd(clearCmd);

    Command echoCmd;
    echoCmd.name = "echo";
    echoCmd.func = [](const std::vector<std::string_view>& args) {
        for (auto& arg : args) {
            Console::PutText(std::string(arg));
            Console::PutText(" ");
        }
        Console::PutText("\n");
        return true;
    };
    Console::RegistCmd(echoCmd);
}

bool Command::Execute(const std::vector<std::string_view>& args) {
    if (func) {
        return func(args);
    }
    return false;
}


int CmdParser::curChar() const {
    if (curIdx_ >= text_.length()) {
        return EOF;
    }
    return text_[curIdx_];
}

void CmdParser::Parse(std::string_view text,
                      std::string_view& outName, std::vector<std::string_view>& outArgs) {
    curIdx_ = 0;
    text_ = text;
    skipWhite();
    outName = parseWord();
    while (!isEOF()) {
        skipWhite();
        outArgs.push_back(parseWord());
    }
}

void CmdParser::skipWhite() {
    while (!isEOF() && isBlank(curChar())) {
        next();
    }
}

std::string_view CmdParser::parseWord() {
    int len = 0; 
    int curIdx = curIdx_;
    while (!isEOF() && !isBlank(curChar())) {
        len ++;
        next();
    }
    return std::string_view(text_.data() + curIdx, len);
}

void CmdParser::next(int n) {
    curIdx_ += n;
}

bool CmdParser::isBlank(int c) const {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

void Console::PutText(const std::string& text) {
    strncat(content_->buffer, text.data(), content_->maxLength);
    content_->len = strlen(content_->buffer);
}

void Console::PutLine(const std::string& text) {
    strncat(content_->buffer, text.data(), content_->maxLength);
    strncat(content_->buffer, "\n", 1);
    content_->len = strlen(content_->buffer);
}

void Console::RegistCmd(const Command& cmd) {
    auto it = cmds_.find(cmd.name);
    if (it == cmds_.end()) {
        cmds_[cmd.name] = {cmd};
    } else {
        it->second.push_back(cmd);
    }
}


void Console::ExeCmd(std::string_view cmd, const std::vector<std::string_view>& args) {
    auto it = cmds_.find(std::string(cmd));
    if (it != cmds_.end()) {
        auto cmdIt = it->second.begin();
        while (cmdIt != it->second.end() && !cmdIt->Execute(args)) {
            cmdIt ++;
        }
        if (cmdIt == it->second.end()) {
            Loge("exexcute {} failed", cmd);
        }
    } else {
        Loge("invalid command {}", cmd);
        Console::PutLine("invalid command: " + std::string(cmd));
    }
}

void Console::Clear() {
    memset(content_->buffer, 0, sizeof(content_->buffer));
    content_->len = 0;
}


void Console::Attach2Scene() {
    auto window = CreateUIWindow("Debug::Console", "console",
                                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_MOVABLE|NK_WINDOW_TITLE,
                                 Rect(400, 100, 400, 300));
    SceneMgr::CurrentScene()->AttachUI(window);

    auto layout = CreateUIDynamicRowLayout("Debug::Console::RowLayout", 220, 1, window);

    content_ = CreateUIEdit("Debug::Console::Label",
                          NK_EDIT_EDITOR|NK_EDIT_INACTIVE|NK_EDIT_MULTILINE,
                          1023, nullptr, layout)
                ->GetComponent<UIEdit>();
    PutLine("console:");

    auto staticLayout = CreateUIStaticRowLayout("Debug::Console::StaticLayout", 30, 380, 1, layout);

    editor_ = CreateUIEdit("Debug::Console::Editor",
                           NK_EDIT_FIELD|NK_EDIT_GOTO_END_ON_ACTIVATE|NK_EDIT_SIG_ENTER,
                           1024, nullptr, staticLayout)
                ->GetComponent<UIEdit>();
    editor_->onEnterKeyPress = [](Entity*, UIEdit* editor) {
        std::string_view name;
        std::vector<std::string_view> args;
        CmdParser parser;
        parser.Parse(editor->buffer, name, args);
        Console::ExeCmd(name, args);
        memset(editor->buffer, 0, sizeof(editor->buffer));
        editor->len = 0;
    };
}

void DebugAttachConsole() {
    Console::Attach2Scene();
}

}
