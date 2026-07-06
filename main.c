#include "raylib.h"

#define WIDTH  (2560 * 0.9)
#define HEIGHT (1600 * 0.9)

#define N 9
#define FACTOR 1e-8
// m
double R[N] = { 696340000.0, 2439400.0, 6051800.0, 6371000.0, 3389500.0, 69911000.0, 58232000.0, 25362000.0, 24622000.0 };
// g/cm³
double D[N] = { 1.408, 5.429, 5.243, 5.513, 3.934, 1.326, 0.687, 1.270, 1.638 };

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
    for (int i = 0; i < N; ++i) {
        R[i] *= FACTOR;
        distance_from_sun[i] *= FACTOR;
    }

    for (int i = 0; i < N; ++i) {
        planets[i] = (Planet){{WIDTH/2 + distance_from_sun[i], HEIGHT/2}, R[i], D[i], {0xFC, 0xE5, 0x70, 0xFF}};
    }
}

void DrawPlanet(Planet* planet) {
    double x = planet->pos.x;
    double y = planet->pos.y;
    double r = planet->radius;
    Color  c = planet->color;
    DrawCircle(x, y, r, c);
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