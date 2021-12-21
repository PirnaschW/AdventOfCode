void AoC2021_14A(std::istream& input)
{
  struct H
  {
    static int f(void)
    {}
  };
  using Number = long long;

  std::string poly{};
  poly.reserve(10000);
  getline(input, poly);

  std::string line{};
  getline(input, line);
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::map<std::string, char> map{};
  for (auto s : v)
  {
    map.insert({ s.substr(0,2),s[6] });
  }

  for (int i = 0; i < 10; i++)
  {
    std::string poly0{};
    poly0.resize(2 * poly.size());

    int z{ 0 };
    for (int i = 0; i < poly.size(); i++)
    {
      if (poly[i] == ' ') break;
      poly0[z++] = poly[i];
      auto it = map.find(poly.substr(i, 2));
      if (it != map.end())
      {
        poly0[z++] = it->second;
      }
    }
    poly = poly0;


    {
      std::map<char, Number> usage{};
      for (auto c : poly)
      {
        if (c == 0) continue;
        usage[c]++;
      }

      Number minu{ std::numeric_limits<Number>::max() };
      Number mini{ 0 };
      Number maxu{ 0 };
      Number maxi{ 0 };
      Number i{ 0 };
      for (auto u : usage)
      {
        if (u.second > maxu)
        {
          maxu = u.second;
          maxi = i;
        }
        if (u.second < minu)
        {
          minu = u.second;
          mini = i;
        }
        i++;
      }

      Number z = maxu - minu;
      std::cout << z << std::endl;
    }



  }

  std::map<char, Number> usage{};
  for (auto c : poly)
  {
    if (c == 0) continue;
    usage[c]++;
  }

  Number minu{ std::numeric_limits<Number>::max() };
  Number mini{ 0 };
  Number maxu{ 0 };
  Number maxi{ 0 };
  Number i{ 0 };
  for (auto u : usage)
  {
    if (u.second > maxu)
    {
      maxu = u.second;
      maxi = i;
    }
    if (u.second < minu)
    {
      minu = u.second;
      mini = i;
    }
    i++;
  }


  Number z = maxu - minu;
  std::cout << z << std::endl;
}

void AoC2021_14B(std::istream& input)
{

  struct H
  {
    static int f(void)
    {}
  };
  using Number = long long;

  std::string poly{};
  poly.reserve(10000);
  getline(input, poly);

  std::string line{};
  getline(input, line);
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::map<std::string, char> map{};
  for (auto s : v)
  {
    map.insert({ s.substr(0,2),s[6] });
  }

  std::map<std::string, Number> polymap{};
  for (int i = 0; i < poly.size(); i++)
  {
    polymap[poly.substr(i, 2)]++;
  }

  for (int i = 0; i < 40; i++)
  {
    std::map<std::string, Number> polymap0;

    for (const auto e : polymap)
    {
      if (e.first[1] == ' ')
      {
        polymap0[e.first] += e.second;
      }
      auto it = map.find(e.first);
      if (it != map.end())
      {
        std::string a{ ".." };
        a[0] = e.first[0];
        a[1] = it->second;
        polymap0[a] += e.second;
        std::string b{ ".." };
        b[0] = it->second;
        b[1] = e.first[1];
        polymap0[b] += e.second;
      }
      else
      {
        polymap0[e.first] += e.second;
      }
    }
    polymap = polymap0;
  }

  std::map<char, Number> usage{};
  for (auto c : polymap)
  {
    if (c.first[0] != ' ' && c.first[0] != '\0') usage[c.first[0]] += c.second;
    if (c.first[1] != ' ' && c.first[1] != '\0') usage[c.first[1]] += c.second;
  }

  Number minu{ std::numeric_limits<Number>::max() };
  Number mini{ 0 };
  Number maxu{ 0 };
  Number maxi{ 0 };
  Number i{ 0 };
  for (auto u : usage)
  {
    if (u.second > maxu)
    {
      maxu = u.second;
      maxi = i;
    }
    if (u.second < minu)
    {
      minu = u.second;
      mini = i;
    }
    i++;
  }


  Number z = (maxu - minu) / 2;
  std::cout << z << std::endl;
}
