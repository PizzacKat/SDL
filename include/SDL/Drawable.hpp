#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

namespace SDL {
    class Renderer;

    class Drawable {
    public:
        virtual void Draw(SDL::Renderer &renderer) const= 0;

        virtual ~Drawable()= default;
    };
}

#endif //DRAWABLE_HPP
