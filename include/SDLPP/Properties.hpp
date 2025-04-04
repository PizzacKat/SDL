#ifndef PROPERTIESID_HPP
#define PROPERTIESID_HPP

#include <functional>
#include <optional>
#include <string>

#include "APIObject.hpp"
#include "SDL3/SDL_properties.h"

namespace SDL {
    class Properties {
    public:
        Properties();
        Properties(SDL_PropertiesID properties);
        Properties(SDL_PropertiesID properties, Borrowed borrowed);
        Properties(Properties &&properties) noexcept;
        Properties &operator=(Properties &&properties) noexcept;

        void Enumerate(const std::function<void(const Properties &, const std::string &)> &function) const;

        void SetPointerWithCleanup(const std::string &name, void *pointer, SDL_CleanupPropertyCallback cleanup, void *userdata);
        void SetPointer(const std::string &name, void *pointer);
        [[nodiscard]] void *GetPointer(const std::string &name) const;
        void SetString(const std::string &name, const std::optional<std::string> &value);
        [[nodiscard]] std::string GetString(const std::string &name) const;
        void SetNumber(const std::string &name, Sint64 value);
        [[nodiscard]] Sint64 GetNumber(const std::string &name) const;
        void SetFloat(const std::string &name, float value);
        [[nodiscard]] float GetFloat(const std::string &name) const;
        void SetBool(const std::string &name, bool value);
        [[nodiscard]] bool GetBool(const std::string &name) const;

        void Clear(const std::string &name);

        [[nodiscard]] bool Has(const std::string &name) const;

        void Lock();
        void Unlock();

        operator SDL_PropertiesID() const;
    private:
        Object::APIObject<SDL_PropertiesID> _properties;
    };
}

#endif //PROPERTIESID_HPP
