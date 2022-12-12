template<> Number AoC<2022, 12, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  // find Start
  struct pos
  {
    Number x{};
    Number y{};
  };
  pos start{};
  pos end{};

  for (size_t x = 0; x < v[0].size(); ++x)
  {
    for (size_t y = 0; y < v.size(); ++y)
    {
      if (v[y][x] == 'S')
      {
        start.x = x;
        start.y = y;
      }
      if (v[y][x] == 'E')
      {
        end.x = x;
        end.y = y;
      }
    }
  }

  std::vector<std::vector<Number>> dist{};
  dist.resize(v.size());
  for (size_t y = 0; y < v.size(); ++y)
    dist[y].resize(v[0].size());
  for (size_t x = 0; x < v[0].size(); ++x)
  {
    for (size_t y = 0; y < v.size(); ++y)
    {
      dist[y][x] = std::numeric_limits<Number>::max();
    }
  }

  dist[start.y][start.x] = 0;

  v[start.y][start.x] = 'a' - 1;
  v[end.y][end.x] = 'z' + 1;

  bool more = true;
  while (more)
  {
    more = false;
    for (size_t x = 0; x < v[0].size(); ++x)
    {
      for (size_t y = 0; y < v.size(); ++y)
      {
        if (dist[y][x] < std::numeric_limits<Number>::max())
        {
          if (x < v[0].size() - 1 && v[y][x + 1] < v[y][x] + 2) // to the right
          {
            if (dist[y][x + 1] > dist[y][x] + 1)
            {
              dist[y][x + 1] = dist[y][x] + 1;
              more = true;
            }
          }

          if (x > 0 && v[y][x - 1] < v[y][x] + 2) // to the left
          {
            if (dist[y][x - 1] > dist[y][x] + 1)
            {
              dist[y][x - 1] = dist[y][x] + 1;
              more = true;
            }
          }

          if (y < v.size() - 1 && v[y+1][x] < v[y][x] + 2) // to the bottom
          {
            if (dist[y+1][x] > dist[y][x] + 1)
            {
              dist[y + 1][x] = dist[y][x] + 1;
              more = true;
            }
          }

          if (y > 0 && v[y - 1][x] < v[y][x] + 2) // to the top
          {
            if (dist[y - 1][x] > dist[y][x] + 1)
            {
              dist[y - 1][x] = dist[y][x] + 1;
              more = true;
            }
          }

        }
      }
    }
  }

  return dist[end.y][end.x];
}

template<> Number AoC<2022, 12, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  // find Start
  struct pos
  {
    Number x{};
    Number y{};
  };
  pos start{};
  pos end{};

  std::vector<std::vector<Number>> dist{};
  dist.resize(v.size());
  for (size_t y = 0; y < v.size(); ++y)
    dist[y].resize(v[0].size());
  for (size_t x = 0; x < v[0].size(); ++x)
  {
    for (size_t y = 0; y < v.size(); ++y)
    {
      dist[y][x] = std::numeric_limits<Number>::max();
    }
  }

  for (size_t x = 0; x < v[0].size(); ++x)
  {
    for (size_t y = 0; y < v.size(); ++y)
    {
      if (v[y][x] == 'S') v[y][x] = 'a' - 1;
      if (v[y][x] == 'E') 
      {
        end.x = x;
        end.y = y;
      }
      if (v[y][x] == 'a') dist[y][x] = 0;
    }
  }

  v[end.y][end.x] = 'z' + 1;

  bool more = true;
  while (more)
  {
    more = false;
    for (size_t x = 0; x < v[0].size(); ++x)
    {
      for (size_t y = 0; y < v.size(); ++y)
      {
        if (dist[y][x] < std::numeric_limits<Number>::max())
        {
          if (x < v[0].size() - 1 && v[y][x + 1] < v[y][x] + 2) // to the right
          {
            if (dist[y][x + 1] > dist[y][x] + 1)
            {
              dist[y][x + 1] = dist[y][x] + 1;
              more = true;
            }
          }

          if (x > 0 && v[y][x - 1] < v[y][x] + 2) // to the left
          {
            if (dist[y][x - 1] > dist[y][x] + 1)
            {
              dist[y][x - 1] = dist[y][x] + 1;
              more = true;
            }
          }

          if (y < v.size() - 1 && v[y + 1][x] < v[y][x] + 2) // to the bottom
          {
            if (dist[y + 1][x] > dist[y][x] + 1)
            {
              dist[y + 1][x] = dist[y][x] + 1;
              more = true;
            }
          }

          if (y > 0 && v[y - 1][x] < v[y][x] + 2) // to the top
          {
            if (dist[y - 1][x] > dist[y][x] + 1)
            {
              dist[y - 1][x] = dist[y][x] + 1;
              more = true;
            }
          }

        }
      }
    }
  }

  return dist[end.y][end.x];
}
