#include "engine/core/scene.hpp"
#include "reflect/components_refl.hpp"

namespace editor {

class EditorScene: public engine::Scene {
public:
    EditorScene(const std::string& name): engine::Scene(name) {}
    void OnInit() override;
    void OnQuit() override;
};

}