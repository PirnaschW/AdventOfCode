//template<> auto InputData<2023, 22, A>() { return
//"1,0,1~1,2,1\n"
//"0,0,2~2,0,2\n"
//"0,2,3~2,2,3\n"
//"0,0,4~0,2,4\n"
//"2,0,5~2,2,5\n"
//"0,1,6~2,1,6\n"
//"1,1,8~1,1,9\n";}; // Result: 5
template<> Number AoC<2023, 22, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Coord = short;
  class Block
  {
  public:
    Coord x1{};
    Coord y1{};
    Coord z1{};
    Coord x2{};
    Coord y2{};
    Coord z2{};
  };

  std::vector<Block> block{};
  Coord maxX{ 0 };
  Coord maxY{ 0 };
  Coord maxZ{ 0 };
  for (const auto& line : v)
  {
    Block b{};
    int z = sscanf_s(line.c_str(), "%hd,%hd,%hd~%hd,%hd,%hd", &b.x1, &b.y1, &b.z1, &b.x2, &b.y2, &b.z2);
    assert(z == 6);
    assert(b.x1 <= b.x2);
    assert(b.y1 <= b.y2);
    assert(b.z1 <= b.z2);
    block.push_back(b);
    if (b.x2 > maxX) maxX = b.x2;
    if (b.y2 > maxY) maxY = b.y2;
    if (b.z2 > maxZ) maxZ = b.z2;
  }

  std::sort(block.begin(), block.end(), [](const Block& b1, const Block& b2) -> bool { return b1.z1 != b2.z1 ? b1.z1 < b2.z1 : b1.y1 != b2.y1 ? b1.y1 < b2.y1 : b1.x1 < b2.x1; });

  constexpr int Free{ -2 };
  std::vector<std::vector<std::vector<int>>> space;
  space.resize(maxZ + 1);
  for (Coord z = 0; z <= maxZ; ++z)
  {
    space[z].resize(maxY + 1);
    for (Coord y = 0; y <= maxY; ++y)
    {
      space[z][y].resize(maxX + 1);
      for (Coord x = 0; x <= maxX; ++x)
      {
        space[z][y][x] = Free;
      }
    }
  }

  for (int i = 0; i < std::ssize(block); ++i)
    for (Coord x = block[i].x1; x <= block[i].x2; ++x)
      for (Coord y = block[i].y1; y <= block[i].y2; ++y)
        for (Coord z = block[i].z1; z <= block[i].z2; ++z)
        {
          space[z][y][x] = i;
        }


  auto IsHolding = [](const Block& b1, const Block& b2) -> bool
    {
      if (b2.z1 > b1.z2 + 1) return false;
      for (Coord x1 = b1.x1; x1 <= b1.x2; ++x1)
        for (Coord y1 = b1.y1; y1 <= b1.y2; ++y1)
          for (Coord z1 = b1.z1; z1 <= b1.z2; ++z1)
            for (Coord x2 = b2.x1; x2 <= b2.x2; ++x2)
              for (Coord y2 = b2.y1; y2 <= b2.y2; ++y2)
                for (Coord z2 = b2.z1; z2 <= b2.z2; ++z2)
                {
                  if (z2 > z1 + 1) break;
                  if (x1 == x2 && y1 == y2)
                  {
                    assert(z1 + 1 == z2);
                    return true;
                  }
                }
      return false;
    };

  auto CanDrop = [&space](const Block& b) -> bool
    {
      if (b.z1 == 1)
        return false; // can't fall any deeper
      for (Coord x = b.x1; x <= b.x2; ++x)
        for (Coord y = b.y1; y <= b.y2; ++y)
          for (Coord z = b.z1; z <= b.z2; ++z)
          {
            if (space[z - 1][y][x] == space[z][y][x]) continue;  // it's the same block
            if (space[z - 1][y][x] != Free)
              return false;
          }
      return true;
    };

  auto Drop = [&space,&CanDrop](Block& b) -> Coord
    {
      Coord drops{ 0 };
      while (CanDrop(b))
      {
        for (Coord x = b.x1; x <= b.x2; ++x)
          for (Coord y = b.y1; y <= b.y2; ++y)
            for (Coord z = b.z1; z <= b.z2; ++z)
            {
              assert(space[z][y][x] != Free);
              assert(space[z - 1][y][x] == Free);
              std::swap(space[z - 1][y][x], space[z][y][x]);
              assert(space[z][y][x] == Free);
              assert(space[z - 1][y][x] != Free);
            }
        --b.z1;
        --b.z2;
        ++drops;
      }
      return drops;
    };

  auto CanDropWithout = [&space](const Block& b, int ignore) -> bool
    {
      if (b.z1 == 1)
        return false; // can't fall any deeper
      for (Coord x = b.x1; x <= b.x2; ++x)
        for (Coord y = b.y1; y <= b.y2; ++y)
          for (Coord z = b.z1; z <= b.z2; ++z)
          {
            if (space[z - 1][y][x] == space[z][y][x]) continue;  // it's the same block
            if (space[z - 1][y][x] != Free && space[z - 1][y][x] != ignore)
              return false;
          }
      return true;
    };

  auto DoesSupport = [&space,&block,&CanDropWithout](const Block& b) -> bool
    {
      for (Coord x = b.x1; x <= b.x2; ++x)
        for (Coord y = b.y1; y <= b.y2; ++y)
          for (Coord z = b.z1; z <= b.z2; ++z)
          {
            if (z >= std::ssize(space) - 1) return false;        // nothing can be above it
            if (space[z + 1][y][x] == space[z][y][x]) continue;  // it's the same block
            if (space[z + 1][y][x] != Free)                      // something is above it
            {
              if (CanDropWithout(block[space[z + 1][y][x]], space[z][y][x]))  // block above could drop
                return true;
            }
          }
      return false;
    };

  Coord drops{0};
  do
  {
    drops = 0;
    for (int i = 1; i < std::ssize(block); ++i)
    {
      drops += Drop(block[i]);
    }
  } while (drops > 0);


  Number count{ 0 };
  for (int i = 0; i < std::ssize(block); ++i)
  {
    if (!DoesSupport(block[i]))
    {
      ++count;
    }
  }
  return count;
}

//template<> auto InputData<2023, 22, B>() { return
//"1,0,1~1,2,1\n"
//"0,0,2~2,0,2\n"
//"0,2,3~2,2,3\n"
//"0,0,4~0,2,4\n"
//"2,0,5~2,2,5\n"
//"0,1,6~2,1,6\n"
//"1,1,8~1,1,9\n";}; // Result: 7
template<> Number AoC<2023, 22, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Coord = short;
  class Block
  {
  public:
    Coord x1{};
    Coord y1{};
    Coord z1{};
    Coord x2{};
    Coord y2{};
    Coord z2{};
  };

  std::vector<Block> block{};
  Coord maxX{ 0 };
  Coord maxY{ 0 };
  Coord maxZ{ 0 };
  for (const auto& line : v)
  {
    Block b{};
    int z = sscanf_s(line.c_str(), "%hd,%hd,%hd~%hd,%hd,%hd", &b.x1, &b.y1, &b.z1, &b.x2, &b.y2, &b.z2);
    assert(z == 6);
    assert(b.x1 <= b.x2);
    assert(b.y1 <= b.y2);
    assert(b.z1 <= b.z2);
    block.push_back(b);
    if (b.x2 > maxX) maxX = b.x2;
    if (b.y2 > maxY) maxY = b.y2;
    if (b.z2 > maxZ) maxZ = b.z2;
  }

  std::sort(block.begin(), block.end(), [](const Block& b1, const Block& b2) -> bool { return b1.z1 != b2.z1 ? b1.z1 < b2.z1 : b1.y1 != b2.y1 ? b1.y1 < b2.y1 : b1.x1 < b2.x1; });

  constexpr int Free{ -2 };
  std::vector<std::vector<std::vector<int>>> space;
  space.resize(maxZ + 1);
  for (Coord z = 0; z <= maxZ; ++z)
  {
    space[z].resize(maxY + 1);
    for (Coord y = 0; y <= maxY; ++y)
    {
      space[z][y].resize(maxX + 1);
      for (Coord x = 0; x <= maxX; ++x)
      {
        space[z][y][x] = Free;
      }
    }
  }

  for (int i = 0; i < std::ssize(block); ++i)
    for (Coord x = block[i].x1; x <= block[i].x2; ++x)
      for (Coord y = block[i].y1; y <= block[i].y2; ++y)
        for (Coord z = block[i].z1; z <= block[i].z2; ++z)
        {
          space[z][y][x] = i;
        }


  auto IsHolding = [](const Block& b1, const Block& b2) -> bool
    {
      if (b2.z1 > b1.z2 + 1) return false;
      for (Coord x1 = b1.x1; x1 <= b1.x2; ++x1)
        for (Coord y1 = b1.y1; y1 <= b1.y2; ++y1)
          for (Coord z1 = b1.z1; z1 <= b1.z2; ++z1)
            for (Coord x2 = b2.x1; x2 <= b2.x2; ++x2)
              for (Coord y2 = b2.y1; y2 <= b2.y2; ++y2)
                for (Coord z2 = b2.z1; z2 <= b2.z2; ++z2)
                {
                  if (z2 > z1 + 1) break;
                  if (x1 == x2 && y1 == y2)
                  {
                    assert(z1 + 1 == z2);
                    return true;
                  }
                }
      return false;
    };

  auto CanDrop = [&space](const Block& b) -> bool
    {
      if (b.z1 == 1)
        return false; // can't fall any deeper
      for (Coord x = b.x1; x <= b.x2; ++x)
        for (Coord y = b.y1; y <= b.y2; ++y)
          for (Coord z = b.z1; z <= b.z2; ++z)
          {
            if (space[z - 1][y][x] == space[z][y][x]) continue;  // it's the same block
            if (space[z - 1][y][x] != Free)
              return false;
          }
      return true;
    };

  auto Drop = [&space,&CanDrop](Block& b) -> Coord
    {
      Coord drops{ 0 };
      while (CanDrop(b))
      {
        for (Coord x = b.x1; x <= b.x2; ++x)
          for (Coord y = b.y1; y <= b.y2; ++y)
            for (Coord z = b.z1; z <= b.z2; ++z)
            {
              assert(space[z][y][x] != Free);
              assert(space[z - 1][y][x] == Free);
              std::swap(space[z - 1][y][x], space[z][y][x]);
              assert(space[z][y][x] == Free);
              assert(space[z - 1][y][x] != Free);
            }
        --b.z1;
        --b.z2;
        ++drops;
      }
      return drops;
    };

  auto CanDropWithout = [&space](const Block& b, int ignore) -> bool
    {
      if (b.z1 == 1)
        return false; // can't fall any deeper
      for (Coord x = b.x1; x <= b.x2; ++x)
        for (Coord y = b.y1; y <= b.y2; ++y)
          for (Coord z = b.z1; z <= b.z2; ++z)
          {
            if (space[z - 1][y][x] == space[z][y][x]) continue;  // it's the same block
            if (space[z - 1][y][x] != Free && space[z - 1][y][x] != ignore)
              return false;
          }
      return true;
    };

  auto DoesSupport = [&space,&block,&CanDropWithout](const Block& b) -> bool
    {
      for (Coord x = b.x1; x <= b.x2; ++x)
        for (Coord y = b.y1; y <= b.y2; ++y)
          for (Coord z = b.z1; z <= b.z2; ++z)
          {
            if (z >= std::ssize(space) - 1) return false;        // nothing can be above it
            if (space[z + 1][y][x] == space[z][y][x]) continue;  // it's the same block
            if (space[z + 1][y][x] != Free)                      // something is above it
            {
              if (CanDropWithout(block[space[z + 1][y][x]], space[z][y][x]))  // block above could drop
                return true;
            }
          }
      return false;
    };

  Coord drops{0};
  do
  {
    drops = 0;
    for (int i = 1; i < std::ssize(block); ++i)
    {
      drops += Drop(block[i]);
    }
  } while (drops > 0);

  auto Disintegrate = [&block, &space](int i) -> void
    {
      const Block& b{ block[i] };
      for (Coord x = b.x1; x <= b.x2; ++x)
        for (Coord y = b.y1; y <= b.y2; ++y)
          for (Coord z = b.z1; z <= b.z2; ++z)
          {
            assert(space[z][y][x] == i);
            space[z][y][x] = Free;
          }
    };

  Number count{ 0 };
  std::vector<std::vector<std::vector<int>>> space0{ space };
  std::vector<Block> block0{block};
  for (int i = 0; i < std::ssize(block); ++i)
  {
    block = block0;
    space = space0;
    Disintegrate(i);
    for (int j = 0; j < std::ssize(block); ++j)
    {
      if (i == j) continue;
      Coord drops = Drop(block[j]);
      if (drops > 0) ++count;
    }
  }
  return count;
}
