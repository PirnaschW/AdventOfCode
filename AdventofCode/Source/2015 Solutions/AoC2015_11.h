//template<> auto InputData<2015, 11, A>() { return "abcdefgh\n";}; // Result: abcdffaa
template<> Number AoC<2015, 11, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  // cqjxjnds
  std::string pass{ v[0] };

  class H
  {
  public:
    static void Increment(std::string& pass, int pos)
    {
      assert(pos >= 0);
      if (++pass[pos] > 'z')
      {
        pass[pos] = 'a';
        Increment(pass, --pos);
      }
      if (pass[pos] == 'i') ++pass[pos];
      if (pass[pos] == 'l') ++pass[pos];
      if (pass[pos] == 'o') ++pass[pos];
    }
    static bool Valid(const std::string& pass)
    {
      return Rule1(pass) && Rule3(pass);
    }
    static bool Rule1(const std::string& pass)
    {
      // one increasing straight of at least three letters, like abc, bcd, cde, and so on, up to xyz
      for (int i = 0; i < pass.size() - 2; ++i)
      {
        if (pass[i] + 1 == pass[i + 1] && pass[i + 1] + 1 == pass[i + 2]) return true;
      }
      return false;
    }
    static bool Rule3(const std::string& pass)
    {
      // must contain at least two different, non-overlapping pairs of letters, like aa, bb, or zz.
      for (int i = 0; i < pass.size() - 3; ++i)
      {
        if (pass[i] == pass[i + 1])
        {
          for (int j = i + 2; j < pass.size() - 1; ++j)
          {
            if (pass[j] == pass[j + 1] && pass[i] != pass[j]) return true;
          }
        }
      }
      return false;
    }
  };

  const int pos{static_cast<int>(pass.size()-1)};
  while (!H::Valid(pass))
  {
    H::Increment(pass,pos);
  }

  throw pass;
}

//template<> auto InputData<2015, 11, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 11, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  // cqjxjnds
  std::string pass{ v[0] };

  class H
  {
  public:
    static void Increment(std::string& pass, int pos)
    {
      assert(pos >= 0);
      if (++pass[pos] > 'z')
      {
        pass[pos] = 'a';
        Increment(pass, --pos);
      }
      if (pass[pos] == 'i') ++pass[pos];
      if (pass[pos] == 'l') ++pass[pos];
      if (pass[pos] == 'o') ++pass[pos];
    }
    static bool Valid(const std::string& pass)
    {
      return Rule1(pass) && Rule3(pass);
    }
    static bool Rule1(const std::string& pass)
    {
      // one increasing straight of at least three letters, like abc, bcd, cde, and so on, up to xyz
      for (int i = 0; i < pass.size() - 2; ++i)
      {
        if (pass[i] + 1 == pass[i + 1] && pass[i + 1] + 1 == pass[i + 2]) return true;
      }
      return false;
    }
    static bool Rule3(const std::string& pass)
    {
      // must contain at least two different, non-overlapping pairs of letters, like aa, bb, or zz.
      for (int i = 0; i < pass.size() - 3; ++i)
      {
        if (pass[i] == pass[i + 1])
        {
          for (int j = i + 2; j < pass.size() - 1; ++j)
          {
            if (pass[j] == pass[j + 1] && pass[i] != pass[j]) return true;
          }
        }
      }
      return false;
    }
  };

  const int pos{static_cast<int>(pass.size()-1)};
  while (!H::Valid(pass))
  {
    H::Increment(pass,pos);
  }

  H::Increment(pass,pos);
  while (!H::Valid(pass))
  {
    H::Increment(pass,pos);
  }

  throw pass;
}
