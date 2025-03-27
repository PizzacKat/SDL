#include "SDL/Error.hpp"

namespace SDL::Error {
    std::function<void(const std::string &, const char *)> callback = DefaultCallback();
}