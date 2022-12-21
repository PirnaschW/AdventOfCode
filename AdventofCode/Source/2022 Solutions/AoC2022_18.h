

//template<> auto InputData<2022, 18, A>() { return "2,2,2\n1, 2, 2\n3, 2, 2\n2, 1, 2\n2, 3, 2\n2, 2, 1\n2, 2, 3\n2, 2, 4\n2, 2, 6\n1, 2, 5\n3, 2, 5\n2, 1, 5\n2, 3, 5"; };

template<> Number AoC<2022, 18, A>(std::istream& input)
{
  struct Point
  {
    int x;
    int y;
    int z;
  };
  struct Face
  {
    int x;
    int y;
    int z;
  };
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<Point> list{};
  for (const auto& line : v)
  {
    Point p;
    sscanf_s(line.c_str(), "%d,%d,%d", &p.x, &p.y, &p.z);
    list.push_back(p);
  }


  struct facehash
  {
    size_t operator() (const Face& f) const noexcept
    {
      return std::hash<int>()(f.x + f.y * 32 + f.z * 1024);
    }
  };
  struct faceequal
  {
    bool operator() (const Face& f1, const Face& f2) const noexcept
    {
      return f1.x == f2.x && f1.y == f2.y && f1.z == f2.z;
    }
  };



  std::unordered_set<Face, facehash, faceequal> faces{};

  Face f{};
  for (const auto& p : list)
  {
    f.x = p.x * 2 + 1;
    f.y = p.y * 2;
    f.z = p.z * 2;
    auto it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2;
    f.y = p.y * 2 + 1;
    f.z = p.z * 2;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2;
    f.y = p.y * 2;
    f.z = p.z * 2 + 1;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2 - 1;
    f.y = p.y * 2;
    f.z = p.z * 2;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2;
    f.y = p.y * 2 - 1;
    f.z = p.z * 2;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2;
    f.y = p.y * 2;
    f.z = p.z * 2 - 1;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);
  }

  return faces.size();
}

//template<> auto InputData<2022, 18, B>() { return "2,2,2\n1, 2, 2\n3, 2, 2\n2, 1, 2\n2, 3, 2\n2, 2, 1\n2, 2, 3\n2, 2, 4\n2, 2, 6\n1, 2, 5\n3, 2, 5\n2, 1, 5\n2, 3, 5"; };

template<> Number AoC<2022, 18, B>(std::istream& input)
{
  struct Point
  {
    int x;
    int y;
    int z;
  };
  struct Face
  {
    int x;
    int y;
    int z;
  };

  struct pointhash
  {
    size_t operator() (const Point& p) const noexcept
    {
      return std::hash<int>()(p.x + p.y * 32 + p.z * 1024);
    }
  };
  struct pointequal
  {
    bool operator() (const Point& p1, const Point& p2) const noexcept
    {
      return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
    }
  };
  std::unordered_set<Point,pointhash,pointequal> list{};


  int xmax = 0; int xmin = 100;
  int ymax = 0; int ymin = 100;
  int zmax = 0; int zmin = 100;


  std::vector<std::string> v = ReadLines(input);
  for (const auto& line : v)
  {
    Point p;
    sscanf_s(line.c_str(), "%d,%d,%d", &p.x, &p.y, &p.z);
    list.insert(p);
    if (p.x > xmax) xmax = p.x;
    if (p.x < xmin) xmin = p.x;
    if (p.y > ymax) ymax = p.y;
    if (p.y < ymin) ymin = p.y;
    if (p.z > zmax) zmax = p.z;
    if (p.z < zmin) zmin = p.z;
  }

  const int dim = 23;
  assert(dim > xmax + 1);
  assert(dim > ymax + 1);
  assert(dim > zmax + 1);


  std::array<std::array<std::array<bool, dim>, dim>, dim> reached{ false };
  std::array<std::array<std::array<bool, dim>, dim>, dim> spread{ false };
  reached[dim-1][dim-1][dim-1] = true;
  bool more=true;
  while (more)
  {
    more = false;
    for (int x = 0; x < dim; ++x)
      for (int y = 0; y < dim; ++y)
        for (int z = 0; z < dim; ++z)
        {
          if (reached[x][y][z] && !spread[x][y][z])
          {
            spread[x][y][z] = true;

            if (x < dim-1 && !list.contains(Point{ x + 1,y,z }))
            {
              reached[x + 1][y][z] = true;
              more = true;
            }
            if (x > 0 && !list.contains(Point{ x - 1,y,z }))
            {
              reached[x - 1][y][z] = true;
              more = true;
            }
            if (y < dim - 1 && !list.contains(Point{ x,y + 1,z }))
            {
              reached[x][y + 1][z] = true;
              more = true;
            }
            if (y > 0 && !list.contains(Point{ x,y - 1,z }))
            {
              reached[x][y - 1][z] = true;
              more = true;
            }
            if (z < dim - 1 && !list.contains(Point{ x,y,z + 1 }))
            {
              reached[x][y][z + 1] = true;
              more = true;
            }
            if (z > 0 && !list.contains(Point{ x,y,z - 1 }))
            {
              reached[x][y][z - 1] = true;
              more = true;
            }
          }
        }
  }

  int n = 0;
  for (int x = 0; x < dim; ++x)
  {
    for (int y = 0; y < dim; ++y)
      for (int z = 0; z < dim; ++z)
      {
        if ((!reached[x][y][z]) && (!list.contains(Point{ x,y,z })))
        {
          list.insert(Point{ x,y,z });
          //std::cout << x << ' ' << y << ' ' << z << std::endl;
          ++n;
        }
      }
  }

  //std::cout << n << std::endl;

  struct facehash
  {
    size_t operator() (const Face& f) const noexcept
    {
      return std::hash<int>()(f.x + f.y * 32 + f.z * 1024);
    }
  };
  struct faceequal
  {
    bool operator() (const Face& f1, const Face& f2) const noexcept
    {
      return f1.x == f2.x && f1.y == f2.y && f1.z == f2.z;
    }
  };
  std::unordered_set<Face, facehash, faceequal> faces{};

  Face f{};
  for (const auto& p : list)
  {
    f.x = p.x * 2 + 1;
    f.y = p.y * 2;
    f.z = p.z * 2;
    auto it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2;
    f.y = p.y * 2 + 1;
    f.z = p.z * 2;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2;
    f.y = p.y * 2;
    f.z = p.z * 2 + 1;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2 - 1;
    f.y = p.y * 2;
    f.z = p.z * 2;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2;
    f.y = p.y * 2 - 1;
    f.z = p.z * 2;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);

    f.x = p.x * 2;
    f.y = p.y * 2;
    f.z = p.z * 2 - 1;
    it = faces.find(f);
    if (it == faces.end())
      faces.insert(f);
    else
      faces.erase(it);
  }



  return faces.size();
}
