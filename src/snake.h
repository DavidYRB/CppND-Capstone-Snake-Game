#ifndef SNAKE_H
#define SNAKE_H

#include <queue>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, float speed=0.1f, int initial_size = 1)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2), 
        speed(speed),
        size(initial_size) {}

  void UpdatePose();
  void GrowBody();
  bool SnakeCell(int x, int y);

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  Direction direction = Direction::kUp;
  float speed;
  int size;
  bool alive{true};
  float head_x;
  float head_y;
  std::queue<SDL_Point> body;

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif