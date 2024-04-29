#include <SDL.h>
#include <vector>
#include <algorithm>
#include <deque>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int RECT_SIZE = 10;
const int DELAY_TIME = 25;

enum Direction {
    DOWN,
    LEFT,
    RIGHT,
    UP
};

void handleEvents(bool& running, int& dir) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_DOWN:
                dir = DOWN;
                break;
            case SDLK_UP:
                dir = UP;
                break;
            case SDLK_LEFT:
                dir = LEFT;
                break;
            case SDLK_RIGHT:
                dir = RIGHT;
                break;
            }
        }
    }
}

void drawRect(SDL_Renderer* renderer, SDL_Rect rect) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);

    std::deque<SDL_Rect> rq;
    std::vector<SDL_Rect> apples;

    for (int i = 0; i < 100; i++) {
        SDL_Rect appleRect;
        appleRect.x = i * RECT_SIZE;
        appleRect.y = i * RECT_SIZE;
        appleRect.w = RECT_SIZE;
        appleRect.h = RECT_SIZE;
        apples.push_back(appleRect);
    }

    bool running = true;
    int dir = 0;
    SDL_Rect head{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, RECT_SIZE, RECT_SIZE };

    while (running) {
        handleEvents(running, dir);

        switch (dir) {
        case DOWN:
            head.y += RECT_SIZE;
            break;
        case UP:
            head.y -= RECT_SIZE;
            break;
        case LEFT:
            head.x -= RECT_SIZE;
            break;
        case RIGHT:
            head.x += RECT_SIZE;
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawRect(renderer, head);

        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY_TIME);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


// 01110100 01101000 11000011 10101001 01101111 00100000 01101010 01100101 00100000 01110100 01100101 00100000 01101000 01100001 01101001 01110011 00100000 00111010 00101001