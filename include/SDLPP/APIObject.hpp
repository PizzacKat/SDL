#ifndef APIOBJECT_HPP
#define APIOBJECT_HPP
#include <utility>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_process.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_tray.h>
#include <SDL3/SDL_video.h>

namespace SDL::Object {
    struct DefaultFree {
        void operator()(void *object) const {
            SDL_free(object);
        }
    };

    struct DestroyAudioStream {
        void operator()(SDL_AudioStream *stream) const {
            if (stream)
                SDL_DestroyAudioStream(stream);
        }
    };

    struct DestroyCondition {
        void operator()(SDL_Condition *condition) const {
            if (condition)
                SDL_DestroyCondition(condition);
        }
    };

    struct DestroyCursor {
        void operator()(SDL_Cursor *cursor) const {
            if (cursor)
                SDL_DestroyCursor(cursor);
        }
    };

    struct DestroyGPUDevice {
        void operator()(SDL_GPUDevice *device) const {
            if (device)
                SDL_DestroyGPUDevice(device);
        }
    };

    struct DestroyMutex {
        void operator()(SDL_Mutex *mutex) const {
            if (mutex)
                SDL_DestroyMutex(mutex);
        }
    };

    struct DestroyPalette {
        void operator()(SDL_Palette *palette) const {
            if (palette)
                SDL_DestroyPalette(palette);
        }
    };

    struct DestroyProcess {
        void operator()(SDL_Process *process) const {
            if (process)
                SDL_DestroyProcess(process);
        }
    };

    struct DestroyProperties {
        void operator()(const SDL_PropertiesID properties) const {
            if (properties != 0)
                SDL_DestroyProperties(properties);
        }
    };
    struct DestroyRenderer {
        void operator()(SDL_Renderer *renderer) const {
            if (renderer)
                SDL_DestroyRenderer(renderer);
        }
    };

    struct DestroyRWLock {
        void operator()(SDL_RWLock *lock) const {
            if (lock)
                SDL_DestroyRWLock(lock);
        }
    };

    struct DestroySemaphore {
        void operator()(SDL_Semaphore *semaphore) const {
            if (semaphore)
                SDL_DestroySemaphore(semaphore);
        }
    };

    struct DestroySurface {
        void operator()(SDL_Surface *surface) const {
            if (surface)
                SDL_DestroySurface(surface);
        }
    };

    struct DestroyTexture {
        void operator()(SDL_Texture *texture) const {
            if (texture)
                SDL_DestroyTexture(texture);
        }
    };

    struct DestroyTray {
        void operator()(SDL_Tray *tray) const {
            if (tray)
                SDL_DestroyTray(tray);
        }
    };

    struct DestroyWindow {
        void operator()(SDL_Window *window) const {
            if (window)
                SDL_DestroyWindow(window);
        }
    };

    template <typename>
    struct DestructorOf {
        typedef DefaultFree Type;
    };

    template <>
    struct DestructorOf<SDL_AudioStream *> {
        typedef DestroyAudioStream Type;
    };

    template <>
    struct DestructorOf<SDL_Condition *> {
        typedef DestroyCondition Type;
    };

    template <>
    struct DestructorOf<SDL_Cursor *> {
        typedef DestroyCursor Type;
    };

    template <>
    struct DestructorOf<SDL_GPUDevice *> {
        typedef DestroyGPUDevice Type;
    };

    template <>
    struct DestructorOf<SDL_Mutex> {
        typedef DestroyMutex Type;
    };

    template <>
    struct DestructorOf<SDL_Palette *> {
        typedef DestroyPalette Type;
    };

    template <>
    struct DestructorOf<SDL_Process *> {
        typedef DestroyProcess Type;
    };

    template <>
    struct DestructorOf<SDL_PropertiesID> {
        typedef DestroyProperties Type;
    };

    template <>
    struct DestructorOf<SDL_Renderer *> {
        typedef DestroyRenderer Type;
    };

    template <>
    struct DestructorOf<SDL_RWLock *> {
        typedef DestroyRWLock Type;
    };

    template <>
    struct DestructorOf<SDL_Semaphore *> {
        typedef DestroySemaphore Type;
    };

    template <>
    struct DestructorOf<SDL_Surface *> {
        typedef DestroySurface Type;
    };

    template <>
    struct DestructorOf<SDL_Texture *> {
        typedef DestroyTexture Type;
    };

    template <>
    struct DestructorOf<SDL_Tray *> {
        typedef DestroyTray Type;
    };

    template <>
    struct DestructorOf<SDL_Window *> {
        typedef DestroyWindow Type;
    };

    struct Borrowed {

    };

    template <typename T, typename Destructor = typename DestructorOf<T>::Type>
    class APIObject {
        static_assert(std::is_invocable_v<Destructor, T>);
    public:
        APIObject(T object, Destructor destructor = Destructor()): _object(object), _destructor(std::move(destructor)) {

        }

        APIObject(T object, Borrowed, Destructor destructor = Destructor()): _object(object), _borrowed(true), _destructor(std::move(destructor)) {

        }

        APIObject(const APIObject &)= delete;
        APIObject &operator=(const APIObject &)= delete;
        APIObject(APIObject &&object) noexcept: _object(object._object), _borrowed(object._borrowed), _destructor(std::move(object._destructor)) {
            object._borrowed = true;
        }
        APIObject &operator=(APIObject &&object) noexcept {
            if (!_borrowed)
                _destructor(_object);
            _object = object._object;
            _borrowed = object._borrowed;
            _destructor = std::move(object._destructor);
            object._borrowed = true;
            return *this;
        }

        operator T() const {
            return _object;
        }

        T operator->() const {
            return _object;
        }

        ~APIObject() {
            if (_borrowed)
                return;
            _destructor(_object);
        }
    private:
        T _object;
        bool _borrowed = false;
        Destructor _destructor;
    };
}

namespace SDL {
    typedef Object::Borrowed Borrowed;
}

#endif //APIOBJECT_HPP
