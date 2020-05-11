#ifndef SNAKE_H
#define SNAKE_H

#include <memory>
#include <queue>
#include <unordered_set>
#include "SDL.h"

struct SDLPointHash{
  size_t operator()(const SDL_Point& point) const{
    return pow(point.x, 2) + point.y;
  }
};

struct SDLPointEqual{
  bool operator()(const SDL_Point& point_1, const SDL_Point& point_2) const{
    return (point_1.x == point_2.x) && (point_1.y == point_2.y);
  }
};

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, float speed=0.1f, int initial_size = 1);

  void UpdatePose();
  void GrowBody();
  bool SnakeCell(int x, int y);
  std::shared_ptr<SDL_Point> GetHead() const;
  std::shared_ptr<std::unordered_set<SDL_Point, SDLPointHash, SDLPointEqual>> GetBody() const;
  bool isAlive() const;
  Direction GetDirection() const;
  void SetDirection(Direction dir);
  int GetSize() const;
  

 private:
  void UpdateHead();
  void UpdateBody(const SDL_Point &prev_cell);

  Direction direction = Direction::kUp;
  float speed;
  int size;
  bool alive{true};
  float head_x;
  float head_y;
  std::shared_ptr<SDL_Point> head_grid;
  std::shared_ptr<std::queue<SDL_Point>> body;
  std::shared_ptr<std::unordered_set<SDL_Point, SDLPointHash, SDLPointEqual>> occupied_points;

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif