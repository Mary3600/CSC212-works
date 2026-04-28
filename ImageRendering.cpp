#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Image rendering", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Surface* surface1 = IMG_Load("C:/Users/marys/Desktop/smiski 5_10.jfif");
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_DestroySurface(surface1);

    SDL_Surface* surface2 = IMG_Load("C:/Users/marys/Desktop/smiski 5_10.jfif");// creating a second image to display
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_DestroySurface(surface2);

    SDL_Surface* surface3 = IMG_Load("C:/Users/marys/Desktop/smiski 5_10.jfif");// creating a third image to display
    SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
    SDL_DestroySurface(surface3);

    SDL_Surface* surface4 = IMG_Load("C:/Users/marys/Desktop/smiski 5_10.jfif");// creating a fourth image to display
    SDL_Texture* texture4 = SDL_CreateTextureFromSurface(renderer, surface4);
    SDL_DestroySurface(surface4);

    SDL_FRect img1 = { 350, 130, 100, 100 }; //making a rectangle so the image sits in it instead of the whole screen
    SDL_FRect img2 = { 230, 250, 100, 100 };
    SDL_FRect img3 = { 470, 250, 100, 100 };
    SDL_FRect img4 = { 350, 370, 100, 100 };

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running = false;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture1, NULL, &img1);
        SDL_RenderTexture(renderer, texture2, NULL, &img2);// rendering the second image
        SDL_RenderTexture(renderer, texture2, NULL, &img3);
        SDL_RenderTexture(renderer, texture2, NULL, &img4);
        SDL_RenderPresent(renderer);
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}