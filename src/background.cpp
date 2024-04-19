#include "background.h"
#include "LEAGUE/engine.h"
#include "LEAGUE/defaults.h"
#include <iostream>

Background::Background() {
    x = 0;
    y = 0;
    loadImage("./assets/background.png");
}

Background::~Background() {
    //SDL_DestroyTexture(texture);
}

void Background::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

