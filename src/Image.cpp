#include "Image.h"
#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

Image::Image() : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false)
{
}

Image::~Image()

{

    if(m_surface == nullptr)
        SDL_FreeSurface(m_surface);
    if(m_texture == nullptr)
        SDL_DestroyTexture(m_texture);

    m_surface = nullptr;

    m_texture = nullptr;

    m_hasChanged = false;
}

void Image::loadFromFile(const char *filename, SDL_Renderer *renderer)
{

    m_surface = IMG_Load(filename);

    if (m_surface == nullptr)
    {

        string nfn = string("../") + filename;

        cout << "Error: cannot load " << filename << ". Trying " << nfn << endl;

        m_surface = IMG_Load(nfn.c_str());

        if (m_surface == nullptr)
        {

            nfn = string("../") + nfn;

            m_surface = IMG_Load(nfn.c_str());
        }
    }

    if (m_surface == nullptr)
    {

        cout << "Error: cannot load " << filename << endl;

        SDL_Quit();

        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ARGB8888, 0);

    SDL_FreeSurface(m_surface);

    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer, surfaceCorrectPixelFormat);

    if (m_texture == NULL)
    {

        cout << "Error: problem to create the texture of " << filename << endl;

        SDL_Quit();

        exit(1);
    }
}

void Image::draw(SDL_Renderer *renderer, int x, int y, int w, int h, int angle)
{

    int ok;

    SDL_Rect r;

    r.x = x;

    r.y = y;

    r.w = (w < 0) ? m_surface->w : w;

    r.h = (h < 0) ? m_surface->h : h;

    if (m_hasChanged)
    {

        ok = SDL_UpdateTexture(m_texture, nullptr, m_surface->pixels, m_surface->pitch);

        assert(ok == 0);

        m_hasChanged = false;
    }
    ok = SDL_RenderCopyEx(renderer, m_texture, nullptr, &r, angle, nullptr, SDL_FLIP_NONE);

    assert(ok == 0);
}