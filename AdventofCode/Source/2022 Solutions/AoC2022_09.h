template<> Number AoC<2022, 9, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };


  struct pos
  {
    int x;
    int y;
  };

  struct posHash
  {
    size_t operator() (const pos& p) const { return std::hash<long>() (*((const long*)(&p))); }
  };

  struct posEqual
  {
    bool operator() (const pos& p1, const pos& p2) const { return p1.x == p2.x && p1.y == p2.y; }
  };

  std::unordered_set<pos,posHash,posEqual> list;
  pos head{ 0,0 };
  pos tail{ 0,0 };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  for (const auto& line : v)
  {
    std::istringstream str(line);
    char dir{};
    Number len{};
    str >> dir >> len;

    for (int i = 0; i < len; ++i)
    {
      switch (dir)
      {
        case 'R': ++head.x; break;
        case 'L': --head.x; break;
        case 'U': ++head.y; break;
        case 'D': --head.y; break;
        default:
          break;
      }
      if (head.x > tail.x + 1) { ++tail.x; tail.y = head.y; }
      if (head.x < tail.x - 1) { --tail.x; tail.y = head.y; }
      if (head.y > tail.y + 1) { ++tail.y; tail.x = head.x; }
      if (head.y < tail.y - 1) { --tail.y; tail.x = head.x; }

      if (!list.contains(tail)) list.insert(tail);
    }
  }

  return list.size();
}

template<> Number AoC<2022, 9, B>(std::istream& input)
{
  struct pos
  {
    int x;
    int y;
  };

  struct posHash
  {
    size_t operator() (const pos& p) const { return std::hash<long>() (*((const long*) (&p))); }
  };

  struct posEqual
  {
    bool operator() (const pos& p1, const pos& p2) const { return p1.x == p2.x && p1.y == p2.y; }
  };

  struct H
  {
    static void movehead(std::unordered_set<pos, posHash, posEqual>& list, char dir, pos snake[10])
    {
      switch (dir)
      {
        case 'R': ++snake[0].x; break;
        case 'L': --snake[0].x; break;
        case 'U': ++snake[0].y; break;
        case 'D': --snake[0].y; break;
        default:
          break;
      }

      for (int i = 0; i < 9; ++i)
      {
        pullnext(snake[i],snake[i+1]);
      }

      if (!list.contains(snake[9]))
        list.insert(snake[9]);
    }

    static void pullnext(const pos& head, pos& tail)
    {
      int dx = head.x - tail.x;
      int dy = head.y - tail.y;
      if (dx == 2)
      {
        ++tail.x;
        if (dy > 0) ++tail.y;
        if (dy < 0) --tail.y;
        return;
      }
      if (dx == -2)
      {
        --tail.x;
        if (dy > 0) ++tail.y;
        if (dy < 0) --tail.y;
        return;
      }

      if (dy == 2)
      {
        ++tail.y;
        if (dx > 0) ++tail.x;
        if (dx < 0) --tail.x;
        return;
      }
      if (dy == -2)
      {
        --tail.y;
        if (dx > 0) ++tail.x;
        if (dx < 0) --tail.x;
        return;
      }
    }
  };



  std::unordered_set<pos, posHash, posEqual> list;
  pos snake[10]{ 0,0 };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  for (const auto& line : v)
  {
    std::istringstream str(line);
    char dir{};
    Number len{};
    str >> dir >> len;

    for (int i = 0; i < len; ++i)
    {
      H::movehead(list, dir, snake);
    }
  }

  return list.size();
}
