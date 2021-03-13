#pragma once
#define WINDOW_WIDTH 800

#define WINDOW_HEIGHT 600

constexpr int kTileWidth = 10;

constexpr int kTileHeight = 10;

constexpr size_t kMapWidth  = WINDOW_WIDTH / kTileWidth;

constexpr size_t kMapHeight = WINDOW_HEIGHT / kTileHeight;

constexpr size_t kTotalTiles = kMapWidth * kMapHeight;