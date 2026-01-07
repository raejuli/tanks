#pragma once

// Intentionally do NOT include Entity.h here to avoid include order issues.
// Ensure this file is included only after Entity is fully defined (e.g., from Entity.h).

template<typename TComponent>
    requires std::derived_from<TComponent, Component>
TComponent* Component::getComponent(const std::string& name) {
    return owner ? owner->getComponent<TComponent>(name) : nullptr;
}
