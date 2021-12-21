void AoC2021_20A(std::istream& input)
{
  struct H
  {
    static void Print(const std::vector<std::string>& image)
    {
      //for (int y = 0; y < image.size(); ++y)
      //{
      //  for (int x = 0; x < image[0].size(); ++x)
      //    std::cout << image[y][x];
      //  std::cout << std::endl;
      //}
      //std::cout << std::endl;
    }
    static int Count(const std::vector<std::string>& image)
    {
      int z{ 0 };
      for (int y = 0; y < image.size(); ++y)
        for (int x = 0; x < image[0].size(); ++x)
          if (image[y][x] == '#') ++z;
      return z;
    }
    static char GetAt(const std::vector<std::string>& image, int x, int y, int iter)
    {
      if (x < 0 || x >= image[0].size() || y < 0 || y >= image.size()) return iter % 2 ? '#' : '.';
      else return image[y][x];
    }
    static int AddBit(int z, char c)
    {
      z <<= 1;
      if (c == '#') ++z;
      return z;
    }
    static std::vector<std::string> Enhance(const std::vector<std::string>& image, const std::string& enhancer, int lip, int iter)
    {
      std::vector<std::string> image0;
      image0.resize(image.size() + 2*lip);
      for (int y = 0; y < image0.size(); ++y)
        image0[y].resize(image[0].size() + 2 * lip);

      for (int x = 0; x < image0[0].size(); ++x)
        for (int y = 0; y < image0.size(); ++y)
        {
          int z{ 0 };
          for (int dy = -1; dy < 2; ++dy)
            for (int dx = -1; dx < 2; ++dx)
              z = AddBit(z, GetAt(image, x + dx - lip, y + dy - lip, iter));
          image0[y][x] = enhancer[z];
        }
      return image0;
    }
  };

  std::string enhancer{};
  getline(input, enhancer);
  assert(enhancer.size() >= (1 << 8));

  std::string line{};
  getline(input, line);
  assert(line.size() == 0);

  std::vector<std::string> image0 = ReadLines(input);
  H::Print(image0);
  int n{ 0 };
  auto image1 = H::Enhance(image0, enhancer, 3, n++);
  H::Print(image1);
  auto image2 = H::Enhance(image1, enhancer, 3, n++);
  H::Print(image2);


  int z = H::Count(image2);
  std::cout << z << std::endl;
}

void AoC2021_20B(std::istream& input)
{
  struct H
  {
    static void Print(const std::vector<std::string>& image)
    {
      //for (int y = 0; y < image.size(); ++y)
      //{
      //  for (int x = 0; x < image[0].size(); ++x)
      //    std::cout << image[y][x];
      //  std::cout << std::endl;
      //}
      //std::cout << std::endl;
    }
    static int Count(const std::vector<std::string>& image)
    {
      int z{ 0 };
      for (int y = 0; y < image.size(); ++y)
        for (int x = 0; x < image[0].size(); ++x)
          if (image[y][x] == '#') ++z;
      return z;
    }
    static char GetAt(const std::vector<std::string>& image, int x, int y, int iter)
    {
      if (x < 0 || x >= image[0].size() || y < 0 || y >= image.size()) return iter % 2 ? '#' : '.';
      else return image[y][x];
    }
    static int AddBit(int z, char c)
    {
      z <<= 1;
      if (c == '#') ++z;
      return z;
    }
    static std::vector<std::string> Enhance(const std::vector<std::string>& image, const std::string& enhancer, int lip, int iter)
    {
      std::vector<std::string> image0;
      image0.resize(image.size() + 2 * lip);
      for (int y = 0; y < image0.size(); ++y)
        image0[y].resize(image[0].size() + 2 * lip);

      for (int x = 0; x < image0[0].size(); ++x)
        for (int y = 0; y < image0.size(); ++y)
        {
          int z{ 0 };
          for (int dy = -1; dy < 2; ++dy)
            for (int dx = -1; dx < 2; ++dx)
              z = AddBit(z, GetAt(image, x + dx - lip, y + dy - lip, iter));
          image0[y][x] = enhancer[z];
        }
      return image0;
    }
  };

  std::string enhancer{};
  getline(input, enhancer);
  assert(enhancer.size() >= (1 << 8));

  std::string line{};
  getline(input, line);
  assert(line.size() == 0);

  std::vector<std::string> image0 = ReadLines(input);
  H::Print(image0);

  for (int n = 0; n < 50; ++n)
  {
    auto image1 = H::Enhance(image0, enhancer, 3, n);
    H::Print(image1);;
    image0 = image1;
  }

  H::Print(image0);;
  int z = H::Count(image0);
  std::cout << z << std::endl;
}
