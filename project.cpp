#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

// Game grid dimensions
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

// Directions for the snake
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// Snake and game variables
int x, y, foodX, foodY, score;
vector<pair<int, int>> snake; // Snake body (list of coordinates)
bool gameOver;

// Function to clear the screen
void clearScreen() {
    system("cls");
}

// Function to initialize the game
void setup() {
    gameOver = false;
    dir = STOP;
    x = GRID_WIDTH / 2;
    y = GRID_HEIGHT / 2;
    foodX = rand() % GRID_WIDTH;
    foodY = rand() % GRID_HEIGHT;
    score = 0;
    snake.clear();
    snake.push_back({ x, y });
}

// Function to draw the game grid
void draw() {
    clearScreen();

    // Draw the top boundary
    for (int i = 0; i < GRID_WIDTH + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (j == 0) cout << "#"; // Left boundary

            if (i == y && j == x) {
                cout << "O"; // Snake head
            }
            else if (i == foodY && j == foodX) {
                cout << "*"; // Food
            }
            else {
                bool printBody = false;
                for (const auto& segment : snake) {
                    if (segment.first == j && segment.second == i) {
                        cout << "o"; // Snake body
                        printBody = true;
                        break;
                    }
                }
                if (!printBody) cout << " ";
            }

            if (j == GRID_WIDTH - 1) cout << "#"; // Right boundary
        }
        cout << endl;
    }

    // Draw the bottom boundary
    for (int i = 0; i < GRID_WIDTH + 2; i++) cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

// Function to handle user input
void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

// Function to update the game logic
void logic() {
    // Move the snake body
    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Move the snake head
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Wrap the snake head to the body
    if (!snake.empty()) {
        snake[0] = { x, y };
    }

    // Check collision with the walls
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
        gameOver = true;
    }

    // Check collision with itself
    for (int i = 1; i < snake.size(); i++) {
        if (snake[i].first == x && snake[i].second == y) {
            gameOver = true;
        }
    }

    // Check collision with the food
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % GRID_WIDTH;
        foodY = rand() % GRID_HEIGHT;
        snake.push_back({ -1, -1 }); // Add new segment to the snake
    }
}

// Main function
int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100); // Control game speed
    }

    cout << "Game Over!" << endl;
    cout << "Your final score: " << score << endl;

    return 0;
}
