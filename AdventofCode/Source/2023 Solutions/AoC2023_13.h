//template<> auto InputData<2023, 13, A>() { return
//"#.##..##.\n"
//"..#.##.#.\n"
//"##......#\n"
//"##......#\n"
//"..#.##.#.\n"
//"..##..##.\n"
//"#.#.##.#.\n"
//"\n"
//"#...##..#\n"
//"#....#..#\n"
//"..##..###\n"
//"#####.##.\n"
//"#####.##.\n"
//"..##..###\n"
//"#....#..#\n";}; // Result: 405
template<> Number AoC<2023, 13, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  
  auto IsDifferent = [](const Input& in, int n1, int n2)->bool
    {
      if (n1 < 0 || n1 >= std::ssize(in)) return false;
      if (n2 < 0 || n2 >= std::ssize(in)) return false;
      return in[n1] != in[n2];
    };

  auto GetMirror = [&IsDifferent](const Input& in) -> int
    {
      for (int y = 0; y < std::ssize(in) - 1; ++y)
      {
        if (IsDifferent(in, y, y + 1)) continue;

        bool mirror{ true };
        for (int y1 = y - 1, y2 = y + 2; y1 >= 0 && y2 < std::ssize(in); --y1, ++y2)
        {
          if (IsDifferent(in, y1, y2))
          {
            mirror = false;
            break;
          }
        }
        if (mirror) return y + 1;
      }
      return 0;
    };

  auto Transpose = [](const Input& in)->Input
    {
      Input out{};
      for (int x = 0; x < std::ssize(in[0]); ++x)
      {
        std::string s;
        for (int y = 0; y < std::ssize(in); ++y)
        {
          s.push_back(in[y][x]);
        }
        out.push_back(s);
      }
      return out;
    };

  auto SumUp = [&GetMirror,&Transpose](const Input& in)->int
    {
      const int hm = GetMirror(in);
      const Input t = Transpose(in);
      const int vm = GetMirror(t);
      return hm * 100 + vm;
    };

  Input in{};
  Number res{ 0 };
  if (v[std::ssize(v)-1] != "") v.push_back(""); // make sure there is an empty line at the end
  for (int i = 0; i < std::ssize(v); ++i)
  {
    if (v[i] == "")
    {
      assert(std::ssize(in) > 0);
      res += SumUp(in);
      in.clear();
    }
    else
    {
      in.push_back(v[i]);
    }
  }
 
  return res;
}

//template<> auto InputData<2023, 13, B>() { return
//"#.##..##.\n"
//"..#.##.#.\n"
//"##......#\n"
//"##......#\n"
//"..#.##.#.\n"
//"..##..##.\n"
//"#.#.##.#.\n"
//"\n"
//"#...##..#\n"
//"#....#..#\n"
//"..##..###\n"
//"#####.##.\n"
//"#####.##.\n"
//"..##..###\n"
//"#....#..#\n";}; // Result: 400
template<> Number AoC<2023, 13, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector


  auto GetDifference = [](const Input& in, int n1, int n2) -> int
    {
      if (n1 < 0 || n1 >= std::ssize(in)) return 0;
      if (n2 < 0 || n2 >= std::ssize(in)) return 0;
      if (in[n1] == in[n2]) return 0;
      assert(std::ssize(in[n1]) == std::ssize(in[n2]));
      int d{ 0 };
      for (int i = 0; i < std::ssize(in[n1]); ++i)
      {
        if (in[n1][i] != in[n2][i]) ++d;
        if (d > 1) return d;
      }
      return d;
    };

  auto GetMirror = [&GetDifference](const Input& in, bool smudged) -> int
    {
      for (int y = 0; y < std::ssize(in) - 1; ++y)
      {
        int d = GetDifference(in, y, y + 1);
        if (d > (smudged ? 1 : 0)) continue;
        bool mirror{ true };
        for (int y1 = y - 1, y2 = y + 2; y1 >= 0 && y2 < std::ssize(in); --y1, ++y2)
        {
          d += GetDifference(in, y1, y2);
          if (d > (smudged ? 1 : 0))
          {
            mirror = false;
            break;
          }
        }
        if (mirror && d == (smudged ? 1 : 0)) // make sure we don't find the wrong type
        {
          return y + 1;
        }
      }
      return 0;
    };

  auto Transpose = [](const Input& in)->Input
    {
      Input out{};
      for (int x = 0; x < std::ssize(in[0]); ++x)
      {
        std::string s;
        for (int y = 0; y < std::ssize(in); ++y)
        {
          s.push_back(in[y][x]);
        }
        out.push_back(s);
      }
      return out;
    };

  auto SumUp = [&GetMirror, &Transpose](const Input& in)->int
    {
      const int hm = GetMirror(in, true);
      if (hm) return hm * 100;
      const Input t = Transpose(in);
      const int vm = GetMirror(t, true);
      return vm;
    };

  Input in{};
  Number res{ 0 };
  if (v[std::ssize(v)-1] != "") v.push_back(""); // make sure there is an empty line at the end
  for (int i = 0; i < std::ssize(v); ++i)
  {
    if (v[i] == "")
    {
      assert(std::ssize(in) > 0);
      res += SumUp(in);
      in.clear();
    }
    else
    {
      in.push_back(v[i]);
    }
  }

  return res;
}
