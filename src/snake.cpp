#include "snake.h"
#include <cmath>
#include <iostream>

Snake::Snake(int grid_width, int grid_height, float speed=0.1f, int initial_size = 1)
      : grid_width(grid_width),
        grid_height(grid_height), 
        speed(speed),
        size(initial_size)
{
  head_x = grid_width/2;
  head_y = grid_height/2;
  head_grid = std::make_shared<head>(static_cast<int>(head_x), static_cast<int>(head_y));
  body = std::make_shared<std::queue<SDL_Point>>();
  occupied_points = std::make_shared<std::unordered_set<SDL_Point>>();
}

void Snake::UpdatePose() {
  SDL_Point prev_cell{head_grid->x, head_grid->y};  // We first capture the head's cell before updating.
  UpdateHead();

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (head_grid->x != prev_cell.x || head_grid->y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
  head_grid->x = static_cast<int>(head_x);
  head_grid->y = static_cast<int>(head_y);
}

void Snake::UpdateBody(const SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body->push(prev_head_cell);
  occupied_points->insert(prev_head_cell);

  if (!growing) {
    // Remove the tail from the body queue.
    auto it = occupied_points->find(body->front());
    occupied_points->erase(it);
    body->pop();
  } else {
    growing = false;
    ++size;
  }

  // Check if the snake has died.
  if(occupied_points->find(*head_grid) != occupied_points->end()){
    alive = false;
  }
}

void Snake::GrowBody() { 
  growing = true;
  speed += 0.02;
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  SDL_Point check_point{x, y};
  if(occupied_points->find(check_point) != occupied_points->end()){
    return true;
  }
  else if(x == head_grid->x && y == head_grid->y) {
    return true;
  }
  return false;
}

// get the head of the snake
std::shared_ptr<SDL_Point> Snake::GetHead(){
  return head_grid;
}

std::shared_ptr<std::unordered_set<SDL_Point>> Snake::GetBody(){
  return body;
}

bool Snake::isAlive(){
  return alive;
}

Snake::Direction Snake::GetDirection(){
  return direction;
}

void Snake::SetDirection(Direction dir){
  direction = dir;
}

int Snake::GetSize(){
  return size;
}