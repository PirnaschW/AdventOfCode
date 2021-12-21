void AoC2020_17A(std::istream& input)
{
  constexpr int ITER{ 6 };
  constexpr int INPUT{ 8 };
  constexpr int MAX{ 2 * ITER + INPUT };

  struct H
  {
    static int countActive(const std::array<std::array<std::array<bool, MAX>, MAX>, MAX>& u, int x, int y, int z)
    {
      int n{ 0 };
      for (int x0 = x - 1; x0 <= x + 1; ++x0)
      {
        if (x0 < 0 || x0 >= MAX) continue;
        for (int y0 = y - 1; y0 <= y + 1; ++y0)
        {
          if (y0 < 0 || y0 >= MAX) continue;
          for (int z0 = z - 1; z0 <= z + 1; ++z0)
          {
            if (z0 < 0 || z0 >= MAX) continue;
            if (x == x0 && y == y0 && z == z0) continue;
            if (u[x0][y0][z0]) ++n;
          }
        }
      }
      return n;
    }

    static void cycle(std::array<std::array<std::array<bool, MAX>, MAX>, MAX>& u)
    {
      auto u0 = u;
      for (int x = 0; x < MAX; ++x)
        for (int y = 0; y < MAX; ++y)
          for (int z = 0; z < MAX; ++z)
          {
            int n = H::countActive(u0, x, y, z);
            if (u0[x][y][z])
            {
              switch (n)
              {
                case 2:
                case 3:
                  break;
                default:
                  u[x][y][z] = false;
                  break;
              }
            }
            else
            {
              switch (n)
              {
                case 3:
                  u[x][y][z] = true;
                  break;
                default:
                  break;
              }
            }
          }
    }

    static int countTotal(std::array<std::array<std::array<bool, MAX>, MAX>, MAX>& u)
    {
      int n{ 0 };
      for (int x = 0; x < MAX; ++x)
        for (int y = 0; y < MAX; ++y)
          for (int z = 0; z < MAX; ++z)
            if (u[x][y][z]) ++n;
      return n;
    }
  };

  std::array<std::array<std::array<bool, MAX>, MAX>, MAX> u{};

  assert(H::countTotal(u) == 0);

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      if (v[i][j] == '#') u[ITER + j][ITER + i][ITER] = true;
    }
  }

  for (int i = 0; i < 6; ++i)
    H::cycle(u);

  int z = H::countTotal(u);
  std::cout << z << std::endl;
}

void AoC2020_17B(std::istream& input)
{
  constexpr int ITER{ 6 };
  constexpr int INPUT{ 8 };
  constexpr int MAX{ 2 * ITER + INPUT };

  using ARR = std::array< std::array< std::array< std::array<bool, MAX>, MAX>, MAX>, MAX>;

  struct H
  {
    static int countActive(const ARR& u, int x, int y, int z, int a)
    {
      int n{ 0 };
      for (int x0 = x - 1; x0 <= x + 1; ++x0)
      {
        if (x0 < 0 || x0 >= MAX) continue;
        for (int y0 = y - 1; y0 <= y + 1; ++y0)
        {
          if (y0 < 0 || y0 >= MAX) continue;
          for (int z0 = z - 1; z0 <= z + 1; ++z0)
          {
            if (z0 < 0 || z0 >= MAX) continue;
            for (int a0 = a - 1; a0 <= a + 1; ++a0)
            {
              if (a0 < 0 || a0 >= MAX) continue;
              if (x == x0 && y == y0 && z == z0 && a == a0) continue;
              if (u[x0][y0][z0][a0]) ++n;
            }
          }
        }
      }
      return n;
    }

    static void cycle(ARR& u)
    {
      auto u0 = u;
      for (int x = 0; x < MAX; ++x)
        for (int y = 0; y < MAX; ++y)
          for (int z = 0; z < MAX; ++z)
            for (int a = 0; a < MAX; ++a)
            {
              int n = H::countActive(u0, x, y, z, a);
              if (u0[x][y][z][a])
              {
                switch (n)
                {
                  case 2:
                  case 3:
                    break;
                  default:
                    u[x][y][z][a] = false;
                    break;
                }
              }
              else
              {
                switch (n)
                {
                  case 3:
                    u[x][y][z][a] = true;
                    break;
                  default:
                    break;
                }
              }
            }
    }

    static int countTotal(ARR& u)
    {
      int n{ 0 };
      for (int x = 0; x < MAX; ++x)
        for (int y = 0; y < MAX; ++y)
          for (int z = 0; z < MAX; ++z)
            for (int a = 0; a < MAX; ++a)
              if (u[x][y][z][a]) ++n;
      return n;
    }
  };

  ARR u{};

  assert(H::countTotal(u) == 0);

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      if (v[i][j] == '#') u[ITER + j][ITER + i][ITER][ITER] = true;
    }
  }

  for (int i = 0; i < 6; ++i)
    H::cycle(u);

  int z = H::countTotal(u);
  std::cout << z << std::endl;
}
