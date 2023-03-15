#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

#define PI (double)22 / 7
#define DEG2RAD (double)180 / PI
#define STEP (double)0.1
#define WIDTH 120
#define HEIGHT 60
#define TPIXEL WIDTH *HEIGHT
#define FLUSH system("cls")

int BITMAP[TPIXEL] = {0}; // actual pixel data
double EDGEDATA[][2][2] = {
    {{45, 16}, {35, 40}},
    {{54, 49}, {78, 10}},
    {{57, 40}, {57, 38}},
    {{1, 2}, {25, 49}},
}; // edge connection data. {start_x, start_y} -> {end_x, end_y}
int PROCESSING = 1;

int RETMEMLOC(int x, int y)
{
  int MEMLOC = (((y - 1) * WIDTH) + x) - 1;
  return (0 < MEMLOC < TPIXEL) ? MEMLOC : -1;
}

void WAIT()
{
  int wt = 1;
  clock_t cStart = clock();
  while (clock() < cStart + wt)
    ;
}

void DISPLAY()
{
  for (int i = 0; i < HEIGHT; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      int MEMLOC = RETMEMLOC(j + 1, i + 1);
      (BITMAP[MEMLOC] == 1) ? printf("`") : printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void DRAW(double sx, double sy, double ex, double ey)
{
  // recursively call until we're at the end pixel
  double theta = atan2(ey - sy, ex - sx) * DEG2RAD;
  double yfac = sin(theta);
  double xfac = cos(theta);
  sx = (ex - sx > STEP) ? sx + (STEP * xfac) : ((ex - sx < -STEP) ? sx + (STEP * xfac) : sx);
  sy = (ey - sy > STEP) ? sy + (STEP * yfac) : ((ey - sy < -STEP) ? sy + (STEP * yfac) : sy);
  // the vertical and horizontal factors are automatically negative. If (ex - sx) < 0, then I just have to 
  // multiply the STEP with the negative factor and then ** add **, not subtract - otherwise that would invert the
  // equation and increase the distance from the solution exponentially!
  int MEMLOC = RETMEMLOC(round(sx), round(sy));
  BITMAP[MEMLOC] = 1;
  // printf("%f : %f\n", xfac, sx);
  if ((ex - sx >= -STEP && ex - sx <= STEP) && (ey - sy >= -STEP && ey - sy <= STEP))
  {
    return;
  }
  else
  {
    DRAW(sx, sy, ex, ey);
  }
}

void RENDER()
{
  int PAIRS = sizeof(EDGEDATA) / sizeof(EDGEDATA[0]);
  for (int i = 0; i < PAIRS; i++)
  {
    DRAW(EDGEDATA[i][0][0], EDGEDATA[i][0][1], EDGEDATA[i][1][0], EDGEDATA[i][1][1]);
  }

  DISPLAY();
  WAIT(); // 0.100 sec
  FLUSH;
  // PROCESSING = 0;
}

int main()
{
  while (PROCESSING)
  {
    RENDER();
  }
  // printf("%d", TPIXEL);
  return 0;
}