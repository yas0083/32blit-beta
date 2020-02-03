#include "shmup.hpp"

using namespace blit;

#define SCENERY_BIG_SKULL Rect(11, 3, 4, 3)
#define SCENERY_TUSK Rect(10, 3, 1, 3)
#define SCENERY_BIG_TUSK Rect(10, 6, 2, 3)
#define SCENERY_BIG_BONE Rect(12, 6, 3, 2)
#define SCENERY_CLAWS Rect(6, 5, 3, 2)
#define SCENERY_BIG_ROCK Rect(3, 5, 3, 3)

#define SHOT_BIG_RED Rect(6, 0, 2, 1)
#define SHOT_LONG_RED Rect(6, 0, 4, 1)
#define SHOT_BIG_PINK Rect(10, 0, 2, 1)

/*
Map
    
    [] --> [] --> [] --> []

Player
    x, y
    vx, vy
    life
Enemy
    x, y
    hit
    life
Projectile
    x, y
    vx, vy
Background Scenery
    x, y

*/
bool hit = false;

RGBA hit_palette[2][5] = {
    {},
    {}
};

Size boar_ship_size(32, 32);

SpriteSheet *ships;
SpriteSheet *background;

void init() {
  ships = SpriteSheet::load(sprites_background);
  background = SpriteSheet::load(sprites_background);

  set_screen_mode(ScreenMode::hires);
  screen.sprites = background;
  
  for (int x = 0; x < 5; x++){
    RGBA s_c = screen.sprites->palette[4 + x];
    RGBA c = RGBA(
      std::min(255, int(s_c.r * 1.8)),
      std::min(255, int(s_c.g * 1.8)),
      std::min(255, int(s_c.b * 1.8))
    );
    hit_palette[0][x] = s_c;
    hit_palette[1][x] = c;
  }

  for (int x = 0; x < 32; x++){ 
    /*background->palette[x] = rgba(
      sprites_background[x * 4 + 20],
      sprites_background[x * 4 + 21],
      sprites_background[x * 4 + 22],
      sprites_background[x * 4 + 23]
    );*/

    background->palette[x] = desert[x];
  }
}

void render(uint32_t time) {
  screen.pen(background->palette[21]);
  screen.clear();
  screen.sprites = background;

  for(int x = 0; x < 40; x++){
    screen.sprite(Rect(15, 3, 1, 5), Point(x * 8, 0), 0);
    screen.sprite(Rect(0, 1, 1, 8), Point(x * 8, screen.bounds.h - 64), 0);
  }

  RGBA t = background->palette[29];
  background->palette[29] = background->palette[20];
  screen.sprite(Rect(1, 2, 15, 1), Point(30, screen.bounds.h - 80), Point(0, 0), 2.0f, 0);
  screen.sprite(Rect(5, 1, 2, 1), Point(30 + (8 * 4 * 2.0f), screen.bounds.h - 96), Point(0, 0), 2.0f, 0);
  screen.sprite(Rect(12, 1, 3, 1), Point(30 + (8 * 11 * 2.0f), screen.bounds.h - 96), Point(0, 0), 2.0f, 0);
  
  /*background->palette[29] = background->palette[19];
  screen.sprite(rect(1, 2, 15, 1), point(30, screen.bounds.h - 64), point(0, 0), 2.0f, 2);
  screen.sprite(rect(5, 1, 2, 1), point(30 + (8 * 4 * 2.0f), screen.bounds.h - 48), point(0, 0), 2.0f, 2);
  screen.sprite(rect(12, 1, 3, 1), point(30 + (8 * 11 * 2.0f), screen.bounds.h - 48), point(0, 0), 2.0f, 2); */

  background->palette[29] = t;
  screen.sprite(Rect(2, 0, 2, 1), Point(0, screen.bounds.h - 72), 0);
  screen.sprite(Rect(1, 2, 3, 1), Point(60, screen.bounds.h - 72), 0);
  screen.sprite(Rect(2, 1, 2, 1), Point(120, screen.bounds.h - 72), 0);

  /* background->palette[29] = background->palette[18];
  screen.sprite(rect(2, 0, 2, 1), point(0, screen.bounds.h - 64), 2);
  screen.sprite(rect(1, 2, 3, 1), point(60, screen.bounds.h - 64), 2);
  screen.sprite(rect(2, 1, 2, 1), point(120, screen.bounds.h - 64), 2);*/

  background->palette[29] = t;

  screen.sprite(SCENERY_BIG_SKULL, Point(0, screen.bounds.h - 52), 0);
  screen.sprite(SCENERY_CLAWS, Point(30, screen.bounds.h - 48), 0);
  screen.sprite(SCENERY_BIG_TUSK, Point(70, screen.bounds.h - 32), 0);
  screen.sprite(SCENERY_BIG_BONE, Point(120, screen.bounds.h - 64), 0);
  screen.sprite(SCENERY_BIG_ROCK, Point(230, screen.bounds.h - 32), 0);

  screen.sprite(SHOT_BIG_RED, Point(30, 60), 0);

  for (int x = 0; x < 32; x++){ 
    RGBA original = RGBA(
      sprites_background[x * 4 + 20],
      sprites_background[x * 4 + 21],
      sprites_background[x * 4 + 22],
      sprites_background[x * 4 + 23]
    );

    RGBA d = desert[x];

    //float s = sin(time / 1000.0f) + 1.0f / 2.0f;
    //float c = cos(time / 1000.0f) + 1.0f / 2.0f;

    float s = time / 5000.0f;
    s -= floor(s);
    float c = 1.0f - s;

    background->palette[x] = RGBA(
      std::min(255, int((d.r * s) + (original.r * c))),
      std::min(255, int((d.g * s) + (original.g * c))),
      std::min(255, int((d.b * s) + (original.b * c))),
      original.a
    );
  }
  screen.sprites = ships;
}

void update(uint32_t time) {
}
