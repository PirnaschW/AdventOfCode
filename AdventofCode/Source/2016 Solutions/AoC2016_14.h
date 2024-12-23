//template<> auto InputData<2016, 14, A>() { return "abc\n";}; // Result: 22728
template<> Number AoC<2016, 14, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // ngcjuoqr

  MD5::MD5 md5;

  class Pair
  {
  public:
    int n;
    char c;
    bool dead{ false };
    bool valid{ false };
  };

  
  auto HasFive = [](const std::string& s, int& offset, char& c) -> bool
    {
      c = 0;
      char last{ 0 };
      int n{ 0 };
      for (; offset < s.size(); ++offset)
      {
        if (s[offset] != last)
        {
          last = s[offset];
          n = 0;
        }
        else
        {
          if (++n > 3)
          {
            c = last;
            return true;
          }
        }
      }
      return false;
    };

  auto HasThree = [](const std::string& s, char& c) -> bool
    {
      c = 0;
      char last{ 0 };
      int n{ 0 };
      for (int i=0; i < s.size(); ++i)
      {
        if (s[i] != last)
        {
          last = s[i];
          n = 0;
        }
        else
        {
          if (++n > 1)
          {
            c = last;
            return true;
          }
        }
      }
      return false;
    };

  std::vector<Pair> potentials{};

  int count{ 0 };
  int upperlimit{ std::numeric_limits<decltype(upperlimit)>::max()};
  for (int z = 0; z < upperlimit; ++z)
  {
    std::stringstream s{};
    s << v[0] << z;
    std::string hash = md5.digestString(s.str().c_str());

    char c{ 0 };
    int off{ 0 };
    while (HasFive(hash, off, c))
    {
      for (int i = 0; i < potentials.size(); ++i)
      {
        if (potentials[i].dead) continue;
        if (potentials[i].valid) continue;
        if (potentials[i].n + 1000 < z)
        {
          potentials[i].dead = true;
          continue;
        }
        if (potentials[i].c == c)
        {
          potentials[i].valid = true;
          if (++count == 64)
          {
            upperlimit = z + 999;
          }
        }
      }
    }

    if (HasThree(hash, c))
    {
      potentials.emplace_back(z, c);
    }
  }

  count = 0;
  int i{ 0 };
  for (i = 0; count < 64; ++i)
  {
    assert(i < potentials.size());
    if (potentials[i].valid) ++count;
  }
  return potentials[i-1].n;
}

//template<> auto InputData<2016, 14, B>() { return "abc\n";}; // Result: 22551
template<> Number AoC<2016, 14, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // ngcjuoqr

  MD5::MD5 md5;

  class Pair
  {
  public:
    int n;
    char c;
    bool dead{ false };
    bool valid{ false };
  };


  auto HasFive = [](const std::string& s, int& offset, char& c) -> bool
    {
      c = 0;
      char last{ 0 };
      int n{ 0 };
      for (; offset < s.size(); ++offset)
      {
        if (s[offset] != last)
        {
          last = s[offset];
          n = 0;
        }
        else
        {
          if (++n > 3)
          {
            c = last;
            return true;
          }
        }
      }
      return false;
    };

  auto HasThree = [](const std::string& s, char& c) -> bool
    {
      c = 0;
      char last{ 0 };
      int n{ 0 };
      for (int i=0; i < s.size(); ++i)
      {
        if (s[i] != last)
        {
          last = s[i];
          n = 0;
        }
        else
        {
          if (++n > 1)
          {
            c = last;
            return true;
          }
        }
      }
      return false;
    };

  auto Hash = [&md5](const std::string& hash) -> std::string
    {
      std::string h = hash;
      for (int r = 0; r < 2017; ++r)
      {
        h = md5.digestString(h.c_str());
      }
      return h;
    };

  std::vector<Pair> potentials{};

  int count{ 0 };
  int upperlimit{ std::numeric_limits<decltype(upperlimit)>::max()};
  for (int z = 0; z < upperlimit; ++z)
  {
    std::stringstream s{};
    s << v[0] << z;
    
    std::string hash = Hash(s.str());

    char c{ 0 };
    int off{ 0 };
    while (HasFive(hash, off, c))
    {
      for (int i = 0; i < potentials.size(); ++i)
      {
        if (potentials[i].dead) continue;
        if (potentials[i].valid) continue;
        if (potentials[i].n + 1000 < z)
        {
          potentials[i].dead = true;
          continue;
        }
        if (potentials[i].c == c)
        {
          potentials[i].valid = true;
          if (++count == 64)
          {
            upperlimit = z + 999;
          }
        }
      }
    }

    if (HasThree(hash, c))
    {
      potentials.emplace_back(z, c);
    }
  }

  count = 0;
  int i{ 0 };
  for (i = 0; count < 64; ++i)
  {
    assert(i < potentials.size());
    if (potentials[i].valid) ++count;
  }

  // 141581 is too high
  return potentials[i-1].n;
}
