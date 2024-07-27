#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Function to create an SDL texture from text
SDL_Texture* createTextureFromText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("SDL Table", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("/Users/aadhi/Developer/16bit-computer/hardware/SourceSansPro-Regular.ttf", 24);

    if (font == nullptr) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return -1;
    }

    SDL_Color textColor = { 0, 0, 0, 255 }; // Black color

    // Table data
    std::string schemaName = "Scott";
    std::string tableNames[] = { "Employee", "Dept", "Product", "Orders", "Sales" };
    int recordCounts[] = { 5000, 10000, 23456, 1643, 3245 };

    // Render loop flag
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderClear(renderer);

        // Render table headers
        SDL_Texture* schemaTexture = createTextureFromText(renderer, font, "Schema Name", textColor);
        SDL_Texture* tableTexture = createTextureFromText(renderer, font, "Table Name", textColor);
        SDL_Texture* countTexture = createTextureFromText(renderer, font, "Count of records", textColor);

        SDL_Rect destRect = { 50, 50, 0, 0 };
        SDL_QueryTexture(schemaTexture, NULL, NULL, &destRect.w, &destRect.h);
        SDL_RenderCopy(renderer, schemaTexture, NULL, &destRect);

        destRect.x = 250;
        SDL_QueryTexture(tableTexture, NULL, NULL, &destRect.w, &destRect.h);
        SDL_RenderCopy(renderer, tableTexture, NULL, &destRect);

        destRect.x = 450;
        SDL_QueryTexture(countTexture, NULL, NULL, &destRect.w, &destRect.h);
        SDL_RenderCopy(renderer, countTexture, NULL, &destRect);

        // Render table data
        for (int i = 0; i < 5; ++i) {
            destRect.x = 50;
            destRect.y = 100 + i * 50;
            SDL_Texture* schemaValueTexture = createTextureFromText(renderer, font, schemaName, textColor);
            SDL_QueryTexture(schemaValueTexture, NULL, NULL, &destRect.w, &destRect.h);
            SDL_RenderCopy(renderer, schemaValueTexture, NULL, &destRect);

            destRect.x = 250;
            SDL_Texture* tableValueTexture = createTextureFromText(renderer, font, tableNames[i], textColor);
            SDL_QueryTexture(tableValueTexture, NULL, NULL, &destRect.w, &destRect.h);
            SDL_RenderCopy(renderer, tableValueTexture, NULL, &destRect);

            destRect.x = 450;
            SDL_Texture* countValueTexture = createTextureFromText(renderer, font, std::to_string(recordCounts[i]), textColor);
            SDL_QueryTexture(countValueTexture, NULL, NULL, &destRect.w, &destRect.h);
            SDL_RenderCopy(renderer, countValueTexture, NULL, &destRect);

            SDL_DestroyTexture(schemaValueTexture);
            SDL_DestroyTexture(tableValueTexture);
            SDL_DestroyTexture(countValueTexture);
        }

        SDL_DestroyTexture(schemaTexture);
        SDL_DestroyTexture(tableTexture);
        SDL_DestroyTexture(countTexture);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Free resources and close SDL
    TTF_CloseFont(font);
    font = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    TTF_Quit();
    SDL_Quit();

    return 0;
}
