#include <iostream>
#include <random>
#include <ctime>
#include <queue>
#include <vector>
#include <algorithm>
#include <chrono>

#define W 100
#define D 200

const int mapWidth = 15;
const int mapHeight = 11;

int map[mapHeight][mapWidth] = {
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
    {W, 0, 0, D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, D, W, 0, W, 0, W, 0, W, 0, W, 0, W},
    {W, D, 0, D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W},
    {W, D, D, D, D, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W},
    {W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W},
    {W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W}};


struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

void generateRandomMap(int map[mapHeight][mapWidth]) {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0,9);

    for (int i = 1; i < mapHeight - 1; i++) {
        for (int j = 1; j < mapWidth - 1; ++j) {
            map[i][j] = W;
        }
    }
    for(int i = 1; i < mapHeight - 1; i++) {
        for (int j = 1; j < mapWidth - 1; j++) {
            if(distribution(rng) < 8) {
                map[i][j] = 0;
            }
        }
    }
    for (int i = 1; i < mapHeight - 1; i++) {
        for (int j = 1; j < mapWidth - 1; j++) {
            if (map[i][j] == 0 && distribution(rng) < 7) {
                map[i][j] = D;
            }
        }
    }
    map[1][1] = 0;
    map[2][1] = 0;
    map[1][2] = 0;
}

bool canReachExit(const int map[mapHeight][mapWidth], int startX, int startY, int exitX, int exitY) {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::pair<int, int>> visited;

    // Verificar si la coordenada de salida es válida
    if (exitX <= 0 || exitX >= mapHeight - 1 || exitY <= 0 || exitY >= mapWidth - 1) {
        return false;
    }

    // Verificar si la coordenada de salida es una pared
    if (map[exitX][exitY] == W) {
        return false;
    }

    queue.push(std::make_pair(startX, startY));
    visited.push_back(std::make_pair(startX, startY));

    // Búsqueda en anchura para encontrar una ruta desde el punto de partida hasta la coordenada de salida
    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();

        int x = current.first;
        int y = current.second;

        // Verificar si se llegó a la coordenada de salida
        if (x == exitX && y == exitY) {
            return true;
        }

        // Verificar los vecinos
        std::pair<int, int> neighbors[] = {std::make_pair(x - 1, y), std::make_pair(x + 1, y),
                                           std::make_pair(x, y - 1), std::make_pair(x, y + 1)};
        for (const std::pair<int, int>& neighbor : neighbors) {
            if (neighbor.first >= 0 && neighbor.first < mapHeight && neighbor.second >= 0 && neighbor.second < mapWidth &&
                std::find(visited.begin(), visited.end(), neighbor) == visited.end() &&
                map[neighbor.first][neighbor.second] != W) {
                queue.push(neighbor);
                visited.push_back(neighbor);
            }
        }
    }

    return false;
}

void printMap(){
    for(int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            int n = map[i][j];
            if (n == W) std::cout << 'W';
            else if (n == D) std::cout << 'D';
            else std::cout << 0;
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    int startX = 1;  // Coordenada x del punto de partida
    int startY = 1;  // Coordenada y del punto de partida
    int exitX = 9;   // Coordenada x de la salida
    int exitY = 9;   // Coordenada y de la salida

    do {
        generateRandomMap(map);
    } while (!canReachExit(map, startX, startY, exitX, exitY));
    printMap();

    if (canReachExit(map, startX, startY, exitX, exitY)) {
        std::cout << "Se puede llegar a la salida desde el punto de partida." << std::endl;
    } else {
        std::cout << "No se puede llegar a la salida desde el punto de partida." << std::endl;
    }
}