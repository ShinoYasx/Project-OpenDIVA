//
// Created by hugo on 5/7/20.
//

#include "Sprite.hpp"

Sprite::Sprite(std::string_view file) {
    if (!(sprite = SDL_LoadBMP(file.data())))
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
}

void Sprite::Draw(SDL_Surface* dst, int x, int y) {
    auto offset = SDL_Rect{x, y};
    if (SDL_BlitSurface(sprite, nullptr, dst, &offset) < 0)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't copy sprite: %s", SDL_GetError());
}

Sprite::Sprite(int width, int height, SDL_PixelFormat* format) {
    sprite = SDL_CreateRGBSurfaceWithFormat(0, width, height, format->BitsPerPixel, format->format);
}

SpriteSheet::SpriteSheet(std::string_view file, uint n_rows, uint n_cols)
    : n_sprites(n_rows * n_cols) {
    if (!(sprite_sheet = SDL_LoadBMP(file.data()))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        return;
    }

    clip.reserve(n_sprites);
    clip_width = sprite_sheet->w / n_cols;
    clip_height = sprite_sheet->h / n_rows;
    for (uint i = 0; i < n_rows; i++)
        for (uint j = 0; j < n_cols; j++)
            clip.push_back(
                {(int)(clip_width * j), (int)(clip_height * i), (int)clip_width, (int)clip_height});
}

void SpriteSheet::Draw(SDL_Surface* dst, uint sprite_n, int x, int y) {
    auto offset = SDL_Rect{x, y};
    if (SDL_BlitSurface(sprite_sheet, &clip[sprite_n - 1], dst, &offset) < 0)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't extract sprite: %s", SDL_GetError());
}
uint SpriteSheet::SpriteWidth() const { return clip_width; }
uint SpriteSheet::SpriteHeight() const { return clip_height; }
uint SpriteSheet::SpritesCount() const { return n_sprites; }
Sprite SpriteSheet::GetSprite(uint sprite_n) {
    Sprite sprite(clip_width, clip_height, sprite_sheet->format);
    Draw(sprite.sprite, sprite_n, 0, 0);
    return sprite;
}
