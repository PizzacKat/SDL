#include "SDLPP/Properties.hpp"

#include "SDLPP/Error.hpp"

namespace SDL {
    Properties::Properties(): _properties(0) {

    }

    Properties::Properties(const SDL_PropertiesID properties): _properties(properties) {

    }

    Properties::Properties(const SDL_PropertiesID properties, const Borrowed borrowed): _properties(properties, borrowed) {

    }

    Properties::Properties(Properties &&properties) noexcept: _properties(std::move(properties._properties)) {
    }

    Properties &Properties::operator=(Properties &&properties) noexcept {
        _properties = std::move(properties._properties);
        return *this;
    }

    void Properties::Enumerate(const std::function<void(const Properties &, const std::string &)> &function) const {
        std::pair<const Properties *, std::function<void(Properties &, const std::string &)>> pair(this, function);
        if (!SDL_EnumerateProperties(_properties, [] (void *pair, SDL_PropertiesID, const char *name) {
            const auto &[props, callback] = *static_cast<std::pair<Properties *, std::function<void(const Properties &, const std::string &)> > *>(pair);
            callback(*props, name);
        }, &pair))
            Error::Throw("SDL_EnumerateProperties");
    }

    void Properties::SetPointerWithCleanup(const std::string &name, void *pointer, const SDL_CleanupPropertyCallback cleanup, void *userdata) {
        if (!SDL_SetPointerPropertyWithCleanup(_properties, name.c_str(), pointer, cleanup, userdata))
            Error::Throw("SDL_SetPointerPropertyWithCleanup");
    }

    void Properties::SetPointer(const std::string &name, void *pointer) {
        if (!SDL_SetPointerProperty(_properties, name.c_str(), pointer))
            Error::Throw("SDL_SetPointerProperty");
    }

    void *Properties::GetPointer(const std::string &name) const {
        return SDL_GetPointerProperty(_properties, name.c_str(), nullptr);
    }

    void Properties::SetString(const std::string &name, const std::optional<std::string> &value) {
        if (!SDL_SetStringProperty(_properties, name.c_str(), value.has_value() ? value.value().c_str() : nullptr))
            Error::Throw("SDL_SetStringProperty");
    }

    std::string Properties::GetString(const std::string &name) const {
        return SDL_GetStringProperty(_properties, name.c_str(), "");
    }

    void Properties::SetNumber(const std::string &name, const Sint64 value) {
        if (!SDL_SetNumberProperty(_properties, name.c_str(), value))
            Error::Throw("SDL_SetNumberProperty");
    }

    Sint64 Properties::GetNumber(const std::string &name) const {
        return SDL_GetNumberProperty(_properties, name.c_str(), 0);
    }

    void Properties::SetFloat(const std::string &name, const float value) {
        if (!SDL_SetFloatProperty(_properties, name.c_str(), value))
            Error::Throw("SDL_SetFloatProperty");
    }

    float Properties::GetFloat(const std::string &name) const {
        return SDL_GetFloatProperty(_properties, name.c_str(), 0.0f);
    }

    void Properties::SetBool(const std::string &name, const bool value) {
        if (!SDL_SetBooleanProperty(_properties, name.c_str(), value))
            Error::Throw("SDL_SetBooleanProperty");
    }

    bool Properties::GetBool(const std::string &name) const {
        return SDL_GetBooleanProperty(_properties, name.c_str(), false);
    }

    void Properties::Clear(const std::string &name) {
        if (!SDL_ClearProperty(_properties, name.c_str()))
            Error::Throw("SDL_ClearProperty");
    }

    bool Properties::Has(const std::string &name) const {
        return SDL_HasProperty(_properties, name.c_str());
    }

    void Properties::Lock() {
        if (!SDL_LockProperties(_properties))
            Error::Throw("SDL_LockProperties");
    }

    void Properties::Unlock() {
        SDL_UnlockProperties(_properties);
    }

    Properties::operator SDL_PropertiesID() const {
        return _properties;
    }
}
