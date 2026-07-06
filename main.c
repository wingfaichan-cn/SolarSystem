#include "raylib.h"

/*
I just want to realize a solar system in realistic proportions
but things are much more serious than I imaged
the solar system is just too big
currently, it's ugly
*/

#define WIDTH  (2560 * 0.97)
#define HEIGHT (1600 * 0.93)

#define N 9

#define FACTOR 1e-7
// m
double R[N] = { 696340000.0, 2439400.0, 6051800.0, 6371000.0, 3389500.0, 69911000.0, 58232000.0, 25362000.0, 24622000.0 };
// g/cm³
double D[N] = { 1.408, 5.429, 5.243, 5.513, 3.934, 1.326, 0.687, 1.270, 1.638 };

char* names[N] = {
    "Sun",
    "Mercury",
    "Venus",
    "Earth",
    "Mars",
    "Jupiter",
    "Saturn",
    "Uranus",
    "Neptune"
};

#define AU 1.496e11
double distance_from_sun[N] = {
     0.0,
     0.39 * AU,
     0.72 * AU,
     1.00 * AU,
     1.52 * AU,
     5.20 * AU,
     9.54 * AU,
    19.22 * AU,
    30.06 * AU
};

typedef struct {
    Vector2 pos;
    double radius;
    double density;
    Color color;
} Planet;

Planet planets[N] = {};
void InitPlanets() {
    double minR = 0x3f3f3f3f;
    for (int i = 0; i < N; ++i) {
        if (R[i] < minR) minR = R[i];
    }
    for (int i = 0; i < N; ++i) {
        R[i] /= minR;
    } // normalize

    double factor = (WIDTH - (R[0]+R[N-1])) / distance_from_sun[N-1];
    for (int i = 0; i < N; ++i) {
        distance_from_sun[i] *= factor;
    } // normalize

    for (int i = 0; i < N; ++i) {
        planets[i] = (Planet){{R[0]+distance_from_sun[i], HEIGHT/2}, R[i], D[i], {0xFC, 0xE5, 0x70, 0xFF}};
    }
    planets[0] = (Planet){{R[0]+distance_from_sun[0], HEIGHT/2}, R[0], D[0], {0xFC, 0xE5, 0x70, 0x48}};
}

void DrawPlanet(Planet* planet) {
    double x = planet->pos.x;
    double y = planet->pos.y;
    double r = planet->radius;
    Color  c = planet->color;
    DrawCircle(x, y, r, c);

    int i = planet - planets;
    if (i < 3) return;
    DrawText(names[i], x-r, y+r, r, WHITE);
}

void DrawPlanets() {
    for (int i = 0; i < N; ++i) {
        DrawPlanet(planets + i);
    }
}

int main() {
    InitPlanets();

    InitWindow(WIDTH, HEIGHT, "raylib basic window");
    SetTargetFPS(60);
  
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawPlanets();

        EndDrawing();
    }
  
    CloseWindow();
    return 0;
}