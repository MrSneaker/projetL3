#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class Image
{

private:
    SDL_Surface *m_surface; // Surface de l'image

    SDL_Texture *m_texture; 

    bool m_hasChanged; 

public:
    //! \brief constructeur de l'image, met toutes les valeurs de la classe à null.
    Image();

    //! \brief destructeur de l'image, désalloue la surface et la texture et reset les valeurs.
    ~Image();

    //! \brief Fait correspondre texture + surface avec un png 
    void loadFromFile(const char *filename, SDL_Renderer *renderer);

    //! \brief Dessine l'image
    void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1, int angle = 0);
};

#endif
