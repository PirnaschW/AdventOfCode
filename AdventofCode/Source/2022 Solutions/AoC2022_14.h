template<> Number AoC<2022, 14, A>(std::istream& input)
{
  struct pos
  {
    int x{};
    int y{};
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<std::vector<pos>> walls{};
  for (const auto& line : v)
  {
    std::istringstream str(line);
    std::vector<pos> node{};

    bool more = true;
    while (more)
    {
      pos p{};
      char comma{};
      char dash{};
      char greater{};
      str >> p.x >> comma >> p.y >> dash >> greater;
      node.push_back(p);
      more = (dash == '-' && greater == '>');
    }
    walls.push_back(node);
  }

  int xmin = 100000;
  int xmax = 0;
  int ymin = 100000;
  int ymax = 0;


  for (size_t i = 0; i < walls.size(); ++i)
  {
    for (size_t j = 0; j < walls[i].size(); ++j)
    {
      if (walls[i][j].x < xmin) xmin = walls[i][j].x;
      if (walls[i][j].x > xmax) xmax = walls[i][j].x;
      if (walls[i][j].y < ymin) ymin = walls[i][j].y;
      if (walls[i][j].y > ymax) ymax = walls[i][j].y;
    }
  }

  int xoffset = xmin - 1;
  int xsize = xmax - xmin + 3;
  int ysize = ymax + 2;
  std::vector<std::vector<char>> cave{};

  cave.resize(ysize);
  for (int i = 0; i < ysize; ++i) cave[i].resize(xsize);
  for (int y = 0; y < ysize; ++y)
  {
    for (int x = 0; x < xsize; ++x)
    {
      cave[y][x] = '.';
    }
  }

// set up walls
  for (size_t i = 0; i < walls.size(); ++i)
  {
    for (size_t j = 1; j < walls[i].size(); ++j)
    {
      int x1 = walls[i][j - 1].x < walls[i][j].x ? walls[i][j - 1].x : walls[i][j].x;
      int x2 = walls[i][j - 1].x > walls[i][j].x ? walls[i][j - 1].x : walls[i][j].x;
      int y1 = walls[i][j - 1].y < walls[i][j].y ? walls[i][j - 1].y : walls[i][j].y;
      int y2 = walls[i][j - 1].y > walls[i][j].y ? walls[i][j - 1].y : walls[i][j].y;

      for (int x = x1; x <= x2; ++x)
      {
        for (int y = y1; y <= y2; ++y)
        {
          cave[y][x - xoffset] = '#'; // wall
        }
      }
    }
  }


// print cave
  //std::cout << std::endl;
  //for (int y = 0; y < ysize; ++y)
  //{
  //  for (int x = 0; x < xsize; ++x)
  //  {
  //    std::cout << cave[y][x];
  //  }
  //  std::cout << std::endl;
  //}

// run sand
  bool more = true;
  Number z = 0;
  while (more)
  {
    pos sand{ 500,0 };
    ++z;
    bool falling = true;
    while (more && falling)
    {
      switch (cave[sand.y + 1][sand.x - xoffset])
      {
        case '#': // wall
        case 'o': // sand
          switch (cave[sand.y + 1][sand.x - 1 - xoffset])
          {
            case '#': // wall
            case 'o': // sand
              switch (cave[sand.y + 1][sand.x + 1 - xoffset])
              {
                case '#': // wall
                case 'o': // sand
                  cave[sand.y][sand.x - xoffset] = 'o';
                  falling = false;
                  break;

                default:  // free
                  ++sand.y;
                  ++sand.x;
                  more = sand.y < ysize - 1;
                  break;
              }
              break;

            default:  // free
              ++sand.y;
              --sand.x;
              more = sand.y < ysize - 1;
              break;
          }
          break;

        default:  // free
          ++sand.y;
          more = sand.y < ysize - 1;
          break;
      }
    }
  }

// print cave
  //std::cout << std::endl;
  //for (int y = 0; y < ysize; ++y)
  //{
  //  for (int x = 0; x < xsize; ++x)
  //  {
  //    std::cout << cave[y][x];
  //  }
  //  std::cout << std::endl;
  //}

  return z - 1;
}

template<> Number AoC<2022, 14, B>(std::istream& input)
{
  struct pos
  {
    int x{};
    int y{};
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<std::vector<pos>> walls{};
  for (const auto& line : v)
  {
    std::istringstream str(line);
    std::vector<pos> node{};

    bool more = true;
    while (more)
    {
      pos p{};
      char comma{};
      char dash{};
      char greater{};
      str >> p.x >> comma >> p.y >> dash >> greater;
      node.push_back(p);
      more = (dash == '-' && greater == '>');
    }
    walls.push_back(node);
  }

  int xmin = 100000;
  int xmax = 0;
  int ymin = 100000;
  int ymax = 0;


  for (size_t i = 0; i < walls.size(); ++i)
  {
    for (size_t j = 0; j < walls[i].size(); ++j)
    {
      if (walls[i][j].x < xmin) xmin = walls[i][j].x;
      if (walls[i][j].x > xmax) xmax = walls[i][j].x;
      if (walls[i][j].y < ymin) ymin = walls[i][j].y;
      if (walls[i][j].y > ymax) ymax = walls[i][j].y;
    }
  }

  int ysize = ymax + 4;
  int xoffset = -ysize;
  int xsize = xmax + 2 * ysize + 2;
  std::vector<std::vector<char>> cave{};


  std::vector<pos> floor{};
  floor.push_back(pos{ xmin-1-ysize, ymax + 2 });
  floor.push_back(pos{ xmax+ysize, ymax + 2 });
  walls.push_back(floor);


  cave.resize(ysize);
  for (int i = 0; i < ysize; ++i) cave[i].resize(xsize);

  for (int y = 0; y < ysize; ++y)
  {
    for (int x = 0; x < xsize; ++x)
    {
      cave[y][x] = '.';
    }
  }

  // set up walls
  for (size_t i = 0; i < walls.size(); ++i)
  {
    for (size_t j = 1; j < walls[i].size(); ++j)
    {
      int x1 = walls[i][j - 1].x < walls[i][j].x ? walls[i][j - 1].x : walls[i][j].x;
      int x2 = walls[i][j - 1].x > walls[i][j].x ? walls[i][j - 1].x : walls[i][j].x;
      int y1 = walls[i][j - 1].y < walls[i][j].y ? walls[i][j - 1].y : walls[i][j].y;
      int y2 = walls[i][j - 1].y > walls[i][j].y ? walls[i][j - 1].y : walls[i][j].y;

      for (int x = x1; x <= x2; ++x)
      {
        for (int y = y1; y <= y2; ++y)
        {
          cave[y][x - xoffset] = '#'; // wall
        }
      }
    }
  }


// print cave
  //std::cout << std::endl;
  //for (int y = 0; y < ysize; ++y)
  //{
  //  for (int x = 0; x < xsize; ++x)
  //  {
  //    std::cout << cave[y][x];
  //  }
  //  std::cout << std::endl;
  //}

// run sand
  bool more = true;
  Number z = 0;
  while (more)
  {
    pos sand{ 500,0 };
    if (cave[sand.y][sand.x - xoffset] == 'o') break;

    ++z;
    bool falling = true;
    while (more && falling)
    {
      switch (cave[sand.y + 1][sand.x - xoffset])
      {
        case '#': // wall
        case 'o': // sand
          switch (cave[sand.y + 1][sand.x - 1 - xoffset])
          {
            case '#': // wall
            case 'o': // sand
              switch (cave[sand.y + 1][sand.x + 1 - xoffset])
              {
                case '#': // wall
                case 'o': // sand
                  cave[sand.y][sand.x - xoffset] = 'o';
                  falling = false;
                  break;

                default:  // free
                  ++sand.y;
                  ++sand.x;
                  break;
              }
              break;

            default:  // free
              ++sand.y;
              --sand.x;
              break;
          }
          break;

        default:  // free
          ++sand.y;
          break;
      }
    }
  }
  
  // print cave
  //std::cout << std::endl;
  //for (int y = 0; y < ysize; ++y)
  //{
  //  for (int x = 0; x < xsize; ++x)
  //  {
  //    std::cout << cave[y][x];
  //  }
  //  std::cout << std::endl;
  //}

  return z;
}

