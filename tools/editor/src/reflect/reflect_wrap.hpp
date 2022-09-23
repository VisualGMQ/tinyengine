#include <string_view>
#include <unordered_map>
#include "meta/factory.hpp"
#include "meta/meta.hpp"

namespace editor {

class ReflClassInfo final {
public:
    std::string_view name;
    std::vector<std::string_view> datas;
    std::vector<std::string_view> funcs;
};

class ReflData final {
public:
    static std::unordered_map<std::string_view, ReflClassInfo> infos;
};

#define REFL_BEGIN() { std::hash<std::string_view> hash; editor::ReflClassInfo info;
#define REFL_END() ReflData::infos[className] = info; }
#define REFL_REGIST_CLASS(type) info.name = #type; auto factory = meta::reflect<type>(hash(#type)); std::string_view className = #type;
#define REFL_REGIST_CTOR(...) factory.ctor<##__VA_ARGS__>();
#define REFL_REGIST_DTOR() factory.dtor<>();
#define REFL_REGIST_BASE(...) factory.base<__VA_ARGS__>();
#define REFL_REGIST_FUNC(name, type) factory.func<type>(hash(name)); info.funcs.push_back(#name);
#define REFL_REGIST_DATA(name, type) factory.data<type>(hash(name)); info.datas.push_back(#name);

}