template<> Number AoC<2021, 17, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  std::string line{};
  getline(input, line);

  int x1, x2, y1, y2;

  // target area: x=70..96, y=-179..-124
  int n = sscanf_s(line.c_str(), "target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2);
  assert(n == 4);

  struct Hit
  {
    int dx;
    int dy;
    int maxy;
  };

  std::vector<Hit> hits{};
  int maxmaxy{ 0 };
  for (int vx = 0; vx < 100; vx++)
    for (int vy = -180; vy < 20000; vy++)
    {
      int x{ 0 };
      int y{ 0 };
      int dx{ vx };
      int dy{ vy };
      int maxy{ 0 };
      while (true)
      {
        x += dx;
        y += dy;
        if (y > maxy) maxy = y;
        dx -= dx > 0 ? 1 : dx < 0 ? -1 : 0;
        dy -= 1;
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
        {
          // save hit
          hits.emplace_back(vx, vy, maxy);
          if (maxy > maxmaxy) maxmaxy = maxy;
          break;
        }
        if (x > x2) break;
        if (y < y1) break;
      }

    }


  return maxmaxy;
}

template<> Number AoC<2021, 17, B>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  std::string line{};
  getline(input, line);

  int x1, x2, y1, y2;

  // target area: x=70..96, y=-179..-124
  int n = sscanf_s(line.c_str(), "target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2);
  assert(n == 4);

  struct Hit
  {
    int dx;
    int dy;
    int maxy;
  };

  std::vector<Hit> hits{};
  int maxmaxy{ 0 };
  for (int vx = 0; vx < 100; vx++)
    for (int vy = -180; vy < 20000; vy++)
    {
      int x{ 0 };
      int y{ 0 };
      int dx{ vx };
      int dy{ vy };
      int maxy{ 0 };
      while (true)
      {
        x += dx;
        y += dy;
        if (y > maxy) maxy = y;
        dx -= dx > 0 ? 1 : dx < 0 ? -1 : 0;
        dy -= 1;
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
        {
          // save hit
          hits.emplace_back(vx, vy, maxy);
          if (maxy > maxmaxy) maxmaxy = maxy;
          break;
        }
        if (x > x2) break;
        if (y < y1) break;
      }

    }


  return hits.size();
}
