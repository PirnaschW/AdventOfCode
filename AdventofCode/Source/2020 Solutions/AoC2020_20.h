void AoC2020_20A(std::istream& input)
{
  constexpr int Dim{ 10 };
  using Number = long long;
  enum Type
  {
    Unknown,
    Corner,
    Edge,
    Center,
  };
  class Tile
  {
  public:
    Tile(std::istream& input)
    {
      for (auto& row : v)
      {
        getline(input, row); // read content
      }

      std::array< std::array<char, 10>, 8> e{};
      for (int i = 0; i < Dim; ++i)
      {

        // clockwise:
        e[0][i] = v[0][i];                     // top
        e[1][i] = v[i][Dim - 1];               // right
        e[2][i] = v[Dim - 1][Dim - 1 - i];     // bottom
        e[3][i] = v[Dim - 1 - i][0];           // left
// counterclockwise:                              
        e[4][i] = v[0][Dim - 1 - i];           // top
        e[5][i] = v[i][0];                     // left
        e[6][i] = v[Dim - 1][i];               // bottom
        e[7][i] = v[Dim - 1 - i][Dim - 1];     // right
      }
      for (int i = 0; i < 8; ++i)
      {
        edge[i] = e[i];
      }
    }
  public:
    Number id;
    std::array<std::string, Dim> v;
    std::array<std::string, 8> edge{};
    std::array<Number, 8> match{ 0LL };
    Type type{ Unknown };
    bool hflipped{ false };
    int rotated{ 0 };
  };

  struct H
  {
    static int f(void)
    {}
  };

  std::map<Number, Tile> tiles{};
  std::string line{};
  do
  {
    std::string line{};
    getline(input, line); // read id line
    Number id = stoll(line.substr(5, 4));

    tiles.insert({ id,input });
  } while (getline(input, line));

  std::unordered_map<std::string, Number> map{};
  for (auto& tile : tiles)
  {
    for (Number i = 0; i < 8LL; ++i)
    {
      const auto [it, inserted] = map.insert({ tile.second.edge[i],tile.first * 8LL + i });
      if (!inserted)
      {
        tile.second.match[i] = it->second;
        tiles.at(it->second / 8).match[it->second % 8] = tile.first * 8 + i;
      }
    }

  }

  Number z{ 1 };
  for (auto& tile : tiles)
  {
    int n{ 0 };
    for (Number i = 0; i < 8LL; ++i)
    {
      if (tile.second.match[i]) ++n;
    }
    switch (n)
    {
      case 8: tile.second.type = Center; break;
      case 6: tile.second.type = Edge;   break;
      case 4: tile.second.type = Corner; z *= tile.first; break;
      default: assert(false); break;
    }
  }

  std::cout << z << std::endl;
}
void AoC2020_20B(std::istream& input)
{
  constexpr int Dim{ 10 };
  using Number = long long;
  enum Type
  {
    Unknown,
    Corner,
    Edge,
    Center,
  };
  class Tile
  {
  public:
    Tile(std::istream& input)
    {
      for (auto& row : v)
      {
        getline(input, row); // read content
      }
      assert(v.size() == v[0].size());
      SetEdges();
    }
  public:
    void SetEdges(void) const
    {
      std::array< std::array<char, 10>, 8> e{};
      for (int i = 0; i < Dim; ++i)
      {
        // clockwise:
        e[0][i] = v[0][i];                     // top
        e[1][i] = v[i][Dim - 1];               // right
        e[2][i] = v[Dim - 1][Dim - 1 - i];     // bottom
        e[3][i] = v[Dim - 1 - i][0];           // left
        // counterclockwise:                              
        e[4][i] = v[0][Dim - 1 - i];           // top
        e[5][i] = v[i][0];                     // left
        e[6][i] = v[Dim - 1][i];               // bottom
        e[7][i] = v[Dim - 1 - i][Dim - 1];     // right
      }
      for (int i = 0; i < 8; ++i)
      {
        edge[i] = e[i];
      }
      assert(edge[0] == GetTopEdge());
      assert(edge[1] == GetRightEdge());
      assert(edge[5] == GetLeftEdge());
      assert(edge[6] == GetBottomEdge());
    }
    bool operator==(const Tile& t) const
    {
      for (int y = 0; y < v.size(); ++y)
        if (v[y] != t.v[y]) return false;
      return true;
    }
    const std::string GetRightEdge(void) const // always top -> bottom
    {
      std::string e;
      e.resize(v.size());
      for (int y = 0; y < v.size(); ++y)
        e[y] = v[y][v[0].size() - 1];
      return e;
    }
    const std::string GetTopEdge(void) const // always left -> right
    {
      return v[0];
    }
    const std::string GetLeftEdge(void) const // always top -> bottom
    {
      std::string e;
      e.resize(v.size());
      for (int y = 0; y < v.size(); ++y)
        e[y] = v[y][0];
      return e;
    }
    const std::string GetBottomEdge(void) const // always left -> right
    {
      return v[v.size() - 1];
    }

    static Tile* FindWithLeftEdge(std::map<Number, Tile>& tiles, std::string e)
    {
      for (auto& tt : tiles)
      {
        if (tt.second.used) continue;

        if (e == tt.second.GetLeftEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetLeftEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetLeftEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetLeftEdge()) return &tt.second;

        tt.second.Flip();
        if (e == tt.second.GetLeftEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetLeftEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetLeftEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetLeftEdge()) return &tt.second;
      }
      return nullptr;
    }
    static Tile* FindWithTopEdge(std::map<Number, Tile>& tiles, std::string e)
    {
      for (auto& tt : tiles)
      {
        if (tt.second.used) continue;

        if (e == tt.second.GetTopEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetTopEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetTopEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetTopEdge()) return &tt.second;

        tt.second.Flip();
        if (e == tt.second.GetTopEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetTopEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetTopEdge()) return &tt.second;
        tt.second.Rotate();
        if (e == tt.second.GetTopEdge()) return &tt.second;
      }
      return nullptr;
    }

  public:
    void Flip(void) // flip the tile horizontally (left <-> right)
    {
      for (int i = 0; i < v.size(); ++i)
        std::reverse(v[i].begin(), v[i].end());
    }
    void Rotate(void) // Rotate the tile counterclockwise (right -> top -> left -> bottom)
    {
      const auto v0 = v;
      assert(v0.size() == v0[0].size());
      for (int x = 0; x < v0[0].size(); ++x)
        for (int y = 0; y < v0.size(); ++y)
          v[y][x] = v0[x][v0.size() - 1 - y];
    }


  public:
    std::array<std::string, Dim> v;
    mutable std::array<std::string, 8> edge{};
    mutable std::array<Number, 8> match{ 0LL };
    Type type{ Unknown };
    bool hflipped{ false };
    int rotated{ 0 };
    bool used{ false };
  };

  struct H
  {
    static int f(void)
    {}
  };

  // read all tiles
  std::map<Number, Tile> tiles{};
  std::string line{};
  do
  {
    std::string line{};
    getline(input, line); // read id line
    Number id = stoll(line.substr(5, 4));

    tiles.insert({ id,input });
  } while (getline(input, line));

  // collect all edges in a map
  std::unordered_map<std::string, Number> map{};
  for (auto& tile : tiles)
  {
    for (Number i = 0; i < 8LL; ++i)
    {
      const auto [it, inserted] = map.insert({ tile.second.edge[i],tile.first * 8LL + i });
      if (!inserted)
      {
        tile.second.match[i] = it->second;
        tiles.at(it->second / 8).match[it->second % 8] = tile.first * 8 + i;
      }
    }
  }

  // find corner tile
  Number cornertile{ 0 };
  for (auto& tile : tiles)
  {
    int n{ 0 };
    for (Number i = 0; i < 8LL; ++i)
    {
      if (tile.second.match[i]) ++n;
    }
    switch (n)
    {
      case 8: tile.second.type = Center; break;
      case 6: tile.second.type = Edge;   break;
      case 4: tile.second.type = Corner; cornertile = tile.first; break;  // remember any corner
      default: assert(false); break;
    }
  }

  for (const auto& tile : tiles)
  {
    Tile t = tile.second;
    assert(t == tile.second);
    t.Rotate();
    t.Rotate();
    t.Rotate();
    t.Rotate();
    assert(t.GetTopEdge() == tile.second.GetTopEdge());
    assert(t.GetLeftEdge() == tile.second.GetLeftEdge());
    assert(t.GetRightEdge() == tile.second.GetRightEdge());
    assert(t.GetBottomEdge() == tile.second.GetBottomEdge());
    assert(t == tile.second);
    t.Flip();
    t.Flip();
    assert(t.GetTopEdge() == tile.second.GetTopEdge());
    assert(t.GetLeftEdge() == tile.second.GetLeftEdge());
    assert(t.GetRightEdge() == tile.second.GetRightEdge());
    assert(t.GetBottomEdge() == tile.second.GetBottomEdge());
    assert(t == tile.second);
  }

  // create image array
  int imagesize = static_cast<int>(sqrt(tiles.size()));
  assert(imagesize == 3 || imagesize == 12);
  std::vector< std::vector<Tile*>> image{};
  image.resize(imagesize);
  for (int i = 0; i < imagesize; ++i) image[i].resize(imagesize);

  // use last found (any) corner tile for top left
  Tile& tile = tiles.at(cornertile);
  // rotate it correctly (no flipping needed); find non-matching edges
  for (int i = 0; i < 5; ++i)
  {
    if (!tile.match[i] && !tile.match[(i + 1) % 4])
    {
      switch (i)
      {
        case 2: tile.Rotate();
        case 1: tile.Rotate();
        case 0: tile.Rotate();
        case 3: break;
        default: assert(false);     break;
      }
      break;
    }
  }
  image[0][0] = &tile;
  tile.used = true;

  // find all neighbors to the right
  for (int x = 1; x < imagesize; ++x)
  {
    auto edgeR = image[0][x - 1]->GetRightEdge();
    Tile* t = Tile::FindWithLeftEdge(tiles, edgeR);
    assert(t != nullptr);
    auto edgeL = t->GetLeftEdge();
    assert(edgeR == edgeL);
    image[0][x] = t;
    t->used = true;
    assert(image[0][x - 1]->GetRightEdge() == image[0][x]->GetLeftEdge());
  }

  // find all neighbors to the bottom
  for (int x = 0; x < imagesize; ++x)
  {
    for (int y = 1; y < imagesize; ++y)
    {
      auto edgeB = image[y - 1][x]->GetBottomEdge();
      Tile* t = Tile::FindWithTopEdge(tiles, edgeB);
      assert(t != nullptr);
      auto edgeT = t->GetTopEdge();
      assert(edgeB == edgeT);
      image[y][x] = t;
      t->used = true;
      assert(image[y - 1][x]->GetBottomEdge() == image[y][x]->GetTopEdge());
    }
  }

  for (int y = 1; y < imagesize; ++y) // all image rows
  {
    for (int x = 1; x < imagesize; ++x)  // all tiles in the row
    {
      Tile* t00 = image[y - 1][x - 1];
      Tile* t10 = image[y - 1][x];
      Tile* t01 = image[y][x - 1];
      assert(t00->GetBottomEdge() == t01->GetTopEdge());
      assert(t00->GetRightEdge() == t10->GetLeftEdge());
    }
  }

  //// print image
  //for (int y = 0; y < imagesize; ++y) // all image rows
  //{
  //  for (int i = 0; i < Dim; ++i) // all tile's rows
  //  {
  //    for (int x = 0; x < imagesize; ++x)  // all tiles in the row
  //    {
  //      Tile* t = image[y][x];
  //      std::cout << t->v[i] << ' ';
  //    }
  //    std::cout << std::endl;
  //  }
  //  std::cout << std::endl;
  //}
  //std::cout << std::endl;

  // create large image
  std::vector<std::string> largeimage{};
  largeimage.resize(imagesize * (Dim - 2));
  for (int i = 0; i < imagesize; ++i) largeimage[i].reserve(imagesize * (Dim - 2));

  // build large image
  for (int y = 0; y < imagesize; ++y) // all image rows
  {
    for (int i = 1; i < Dim - 1; ++i)   // all tile's rows
    {
      for (int x = 0; x < imagesize; ++x)  // all tiles in the row
      {
        largeimage[y * (Dim - 2) + i - 1] += image[y][x]->v[i].substr(1, Dim - 2);
      }
    }
  }


  // define SeaMonster
  std::array<std::string, 3> seamonster{ {
    {"                  # "},
    {"#    ##    ##    ###"},
    {" #  #  #  #  #  #   "},
  } };

  struct SeaMonsterHelper // helper functions
  {
    static int Search(const std::array<std::string, 3>& seamonster, std::vector<std::string>& largeimage)
    {
      int nsm{ 0 };
      for (int y = 0; y < largeimage.size() - seamonster.size() + 1; ++y) // all image rows
      {
        for (int x = 0; x < largeimage[0].size() - seamonster[0].size(); ++x)  // all positions in the row
        {
          if (largeimage[y + 1][x] == '#')
          {
            if (SeaMonsterHelper::CheckHere(seamonster, largeimage, x, y))
            {
              SeaMonsterHelper::BlankOut(seamonster, largeimage, x, y);
              ++nsm;
            }
          }
        }
      }
      return nsm;
    }
    static bool CheckHere(const std::array<std::string, 3>& seamonster, const std::vector<std::string>& largeimage, int x, int y)
    {
      // check here for SeaMonster
      for (int sy = 0; sy < seamonster.size(); ++sy)
        for (int sx = 0; sx < seamonster[0].size(); ++sx)
          if (seamonster[sy][sx] == '#' && !(largeimage[y + sy][x + sx] == '#'))
            return false;
      return true;
    }
    static void BlankOut(const std::array<std::string, 3>& seamonster, std::vector<std::string>& largeimage, int x, int y)
    {
      // check here for SeaMonster
      for (int sy = 0; sy < seamonster.size(); ++sy)
        for (int sx = 0; sx < seamonster[0].size(); ++sx)
          if (seamonster[sy][sx] == '#')
            largeimage[y + sy][x + sx] = '*';
    }
    static void Rotate(std::vector<std::string>& v) // Rotate the tile counterclockwise (right -> top -> left -> bottom)
    {
      const auto v0 = v;
      assert(v0.size() == v0[0].size());
      for (int x = 0; x < v0[0].size(); ++x)
        for (int y = 0; y < v0.size(); ++y)
          v[y][x] = v0[x][v0.size() - 1 - y];
    }
    static void Flip(std::vector<std::string>& v) // flip the tile horizontally (left <-> right)
    {
      for (int i = 0; i < v.size(); ++i)
        std::reverse(v[i].begin(), v[i].end());

    }
  };

  // search for SeaMonster
  int nsm{ 0 };
  nsm += SeaMonsterHelper::Search(seamonster, largeimage);
  SeaMonsterHelper::Rotate(largeimage);
  nsm += SeaMonsterHelper::Search(seamonster, largeimage);
  SeaMonsterHelper::Rotate(largeimage);
  nsm += SeaMonsterHelper::Search(seamonster, largeimage);
  SeaMonsterHelper::Rotate(largeimage);
  nsm += SeaMonsterHelper::Search(seamonster, largeimage);
  SeaMonsterHelper::Flip(largeimage);
  nsm += SeaMonsterHelper::Search(seamonster, largeimage);
  SeaMonsterHelper::Rotate(largeimage);
  nsm += SeaMonsterHelper::Search(seamonster, largeimage);
  SeaMonsterHelper::Rotate(largeimage);
  nsm += SeaMonsterHelper::Search(seamonster, largeimage);
  SeaMonsterHelper::Rotate(largeimage);
  nsm += SeaMonsterHelper::Search(seamonster, largeimage);

  //// print large image
  //for (int y = 0; y < imagesize * (Dim - 2); ++y) // all image rows
  //{
  //  std::cout << largeimage[y] << std::endl;
  //}
  //std::cout << std::endl;

  int z{ 0 };
  for (int y = 0; y < largeimage.size(); ++y) // all image rows
    for (int x = 0; x < largeimage[0].size(); ++x)  // all positions in the row
      if (largeimage[y][x] == '#')
        ++z;

  std::cout << z << std::endl;
}
