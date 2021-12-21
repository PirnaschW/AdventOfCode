void AoC2020_09A(std::istream& input)
{
  constexpr size_t preamble{ 25 };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  std::array<long long, preamble> list{ 0 };

  for (int i = 0; i < preamble; ++i)
  {
    list[i] = std::stoll(v[i]);
  }

  for (int i = preamble; i < v.size(); ++i)
  {
    bool found = false;
    long long z = std::stoll(v[i]);
    for (int x = 0; x < preamble; ++x)
      for (int y = 0; y < preamble; ++y)
      {
        if (x == y) continue;
        if (list[x] + list[y] == z)
        {
          list[i % preamble] = z;
          found = true;
        }
      }
    if (!found)
    {
      std::cout << z << std::endl;
      return;
    }
  }
}


void AoC2020_09B(std::istream& input)
{
  constexpr size_t preamble{ 25 };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  std::array<long long, preamble> list{ 0 };

  for (int i = 0; i < preamble; ++i)
  {
    list[i] = std::stoll(v[i]);
  }

  for (int i = preamble; i < v.size(); ++i)
  {
    bool found = false;
    long long z = std::stoll(v[i]);
    for (int x = 0; x < preamble; ++x)
      for (int y = 0; y < preamble; ++y)
      {
        if (x == y) continue;
        if (list[x] + list[y] == z)
        {
          list[i % preamble] = z;
          found = true;
        }
      }
    if (!found)
    {
      // now find which numbers add to Z

      std::vector<long long> list0{};
      list0.resize(i);
      for (int i0 = 0; i0 < i; ++i0)
      {
        list0[i0] = std::stoll(v[i0]);
      }

      for (int i0 = 0; i0 < i; ++i0)
      {
        long long jz{ 0 };
        for (int j0 = i0; jz < z; ++j0)
        {
          jz += list0[j0];
          if (jz == z) // got it!
          {
            // find smallest and largest
            long long zmin = std::numeric_limits<long long>::max();
            long long zmax = 0;
            for (int k0 = i0; k0 <= j0; ++k0)
            {
              if (list0[k0] < zmin) zmin = list0[k0];
              if (list0[k0] > zmax) zmax = list0[k0];
            }
            std::cout << zmin + zmax << std::endl;
            return;
          }
        }
      }
    }
  }
}
