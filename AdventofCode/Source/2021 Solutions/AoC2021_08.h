void AoC2021_08A(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  int z{ 0 };

  for (const auto& line : v)
  {
    std::vector<std::string> codes{};
    std::vector<std::string> digits{};
    std::vector<int> ident{};
    ident.resize(10);

    std::istringstream str(line);
    for (int i = 0; i < 10; ++i)
    {
      std::string s;
      str >> s;
      std::sort(s.begin(), s.end());
      codes.emplace_back(s);
      switch (s.size())
      {
        case 2:
        case 3:
        case 4:
        case 7: ident[s.size()] = i;
        default: break;
      }
    }
    char bar;
    str >> bar;
    for (int i = 0; i < 4; ++i)
    {
      std::string s;
      str >> s;
      std::sort(s.begin(), s.end());
      digits.emplace_back(s);
    }

    for (int i = 0; i < 4; ++i)
    {
      switch (digits[i].size())
      {
        case 2:
        case 3:
        case 4:
        case 7: ++z;
        default: break;
      }
    }

  }

  std::cout << z << std::endl;
}


int find_index(const std::vector<int>& v, int z)
{
  for (int i = 0; i < v.size(); ++i) if (v[i] == z) return i;
  return -1;
}

void AoC2021_08B(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  int z{ 0 };

  for (const auto& line : v)
  {
    std::vector<std::string> codes{};
    std::vector<std::string> digits{};
    std::vector<int> ident{};
    ident.resize(10);

    std::istringstream str(line);
    for (int i = 0; i < 10; ++i)
    {
      std::string s;
      str >> s;
      std::sort(s.begin(), s.end());
      codes.emplace_back(s);
      switch (s.size())
      {
        case 2: ident[i] = 1; break;
        case 3: ident[i] = 7; break;
        case 4: ident[i] = 4; break;
        case 7: ident[i] = 8; break;
        default: break;
      }
    }

    for (int i = 0; i < 10; ++i)
    {
      switch (codes[i].size())
      {
        case 6:
          {
            std::string one = codes[find_index(ident, 1)];
            bool all = true;
            for (const char& c : one)
            {
              if (!codes[i].contains(c))
              {
                all = false;  // only 6 doesn't contain all of 1
                break;
              }
            }
            if (!all) ident[i] = 6;
            else
            {
              bool all = true;
              std::string four = codes[find_index(ident, 4)];
              for (const char& c : four)
              {
                if (!codes[i].contains(c))
                {
                  all = false;  // only 0 doesn't contain all of 4
                  break;
                }
              }
              if (!all) ident[i] = 0;
              else ident[i] = 9;
            }
          }
          break;

        case 5:
          {
            std::string one = codes[find_index(ident, 1)];
            bool missing = false;
            for (const char& c : one)
            {
              if (!codes[i].contains(c)) missing = true;
            }
            if (!missing)
            {
              ident[i] = 3;   // only 3 contains all of 1
              break;
            }
            std::string four = codes[find_index(ident, 4)];
            int match{ 0 };
            for (const char& c : four)
            {
              if (codes[i].contains(c)) ++match;
            }
            switch (match)
            {
              case 2: ident[i] = 2; break;
              case 3: ident[i] = 5; break;
              default: break;
            }
          }
          break;
        default: break;
      }
    }


    char bar;
    str >> bar;
    for (int i = 0; i < 4; ++i)
    {
      std::string s;
      str >> s;
      std::sort(s.begin(), s.end());
      digits.emplace_back(s);
    }

    int zz{ 0 };
    for (int i = 0; i < 4; ++i)
    {
      zz *= 10;
      for (int j = 0; j < 10; ++j)
      {
        if (codes[j] == digits[i])
        {
          zz += ident[j];
          break;
        }
      }
    }

    z += zz;
  }

  std::cout << z << std::endl;

}
