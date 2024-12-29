//template<> auto InputData<2023, 12, A>() { return
//"???.### 1,1,3\n"
//".??..??...?##. 1,1,3\n"
//"?#?#?#?#?#?#?#? 1,3,1,6\n"
//"????.#...#... 4,1,1\n"
//"????.######..#####. 1,6,5\n"
//"?###???????? 3,2,1\n";}; // Result: 21
template<> Number AoC<2023, 12, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  int result{0};
  for (const auto& line : v)
  {
    size_t p = line.find(' ');
    int Count{ 0 };
    std::string list{line.substr(0,p)};

    auto ReadTarget = [](const char* s)-> std::vector<int>
      {
        std::vector<int> target{};
        int z{ 0 };
        int p{ 0 };
        int n{ 0 };
        while (sscanf_s(s + p, "%d%n", &z, &n) == 1)
        {
          target.push_back(z);
          p += n;
          if (*(s + p) == '\0') break;
          else ++p;  // eat comma
        }
        return target;
      };
    std::vector<int> target = ReadTarget(line.substr(p + 1).c_str());

    auto MatchPattern = [&target](const std::string& s, int pos) -> bool
      {
        int z{ 0 };
        int n{ 0 };
        auto Match = [&target, &z](int& n)->bool { return z < std::ssize(target) && target[z++] == n; };
        for (int i = 0; i < pos; ++i)
        {
          switch (s[i])
          {
            case '.':
              if (n > 0)
              {
                if (!Match(n)) return false; // cut short further eval
                n = 0;
              }
              break;
            case '#':
              ++n;
              break;
            default:
              assert(false);
              break;
          }
        }
        if (pos == std::ssize(s))
        {
          if (n > 0 && !Match(n)) return false;
          if (z < std::ssize(target)) return false;
        }
        return true;
      };
    auto Try = [&Count,&MatchPattern](std::string& s, int pos, auto Try) -> void
      {
        if (pos < std::ssize(s))
        {
          if (!MatchPattern(s,pos)) return;
        }
        else {
          if (MatchPattern(s,pos)) ++Count;
          return;
        }

        switch (s[pos])
        {
          case '.': [[fallthrough]];
          case '#':
            Try(s, pos + 1, Try);
            return;
          case '?':
            s[pos] = '.';
            Try(s, pos + 1, Try);
            s[pos] = '#';
            Try(s, pos + 1, Try);
            s[pos] = '?'; // put it back
            return;
          default: assert(false); return;
        }
      };

    Try(list, 0, Try);
    result += Count;
  }

  return result;
}

//template<> auto InputData<2023, 12, B>() { return
//"???.### 1,1,3\n"
//".??..??...?##. 1,1,3\n"
//"?#?#?#?#?#?#?#? 1,3,1,6\n"
//"????.#...#... 4,1,1\n"
//"????.######..#####. 1,6,5\n"
//"?###???????? 3,2,1\n";}; // Result: 525152
template<> Number AoC<2023, 12, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number result{0};

  class Memo
  {
  public:
    std::string r{};
    std::vector<int> m{};
  };
  std::unordered_map < Memo, Number,
    decltype([](const Memo& m)->size_t { size_t z{}; for (size_t i = 0; i < m.m.size(); ++i) z |= (m.m[i] << i); return std::hash<std::string>()(m.r) ^ (m.m.size() << 23) ^ z; }),
    decltype([](const Memo& m1, const Memo& m2)->bool { return m1.r == m2.r && m1.m == m2.m; }) > memo{};

  for (const auto& line : v)
  {
    size_t p = line.find(' ');
    Number Count{ 0 };
    std::string list{line.substr(0,p)};

    auto ReadTarget = [](const char* s)-> std::vector<int>
      {
        std::vector<int> target{};
        int z{ 0 };
        int p{ 0 };
        int n{ 0 };
        while (sscanf_s(s + p, "%d%n", &z, &n) == 1)
        {
          target.push_back(z);
          p += n;
          if (*(s + p) == '\0') break;
          else ++p;  // eat comma
        }
        return target;
      };

    std::vector<int> t0 = ReadTarget(line.substr(p + 1).c_str());
    std::vector<int> target{ t0 };
    for (size_t i = 0; i < 4; ++i) // 'unfold' to five times the same
    {
      list.push_back('?');
      list.append(line.substr(0, p));
      target.insert(target.cend(), t0.cbegin(), t0.cend());
    }
    list.push_back('.');
    target.push_back(0);

    auto Try = [&list,&target,&Count,&memo](int lPos, int mPos, int nSprings, auto Try) -> void
      {
        if (lPos == list.size())
        {
          if (target[mPos] == 0)
            ++Count; // success
          return;
        }
        if (nSprings > target[mPos]) // short cut - if nSprings is already larger than next target, it can't match
        {
          return;
        }

        switch (list[lPos])
        {
          case '#':
            Try(lPos + 1, mPos, ++nSprings, Try);
            return;
          case '.':
            if (nSprings > 0)
            {
              if (nSprings != target[mPos]) // not enough or too many springs?
                return;
              ++mPos;
            }
            // memoization:
            {
              Memo m{ list.substr(lPos),{target.cbegin() + mPos,target.cend()} };
              auto it = memo.find(m);
              if (it != memo.cend())
              {
                Count += it->second;
              }
              else
              {
                Number before = Count;
                Try(lPos + 1, mPos, 0, Try);
                memo.insert({ m, Count - before });
              }
            }
            return;
          case '?':
            list[lPos] = '.';
            Try(lPos, mPos, nSprings, Try); // try same pos again but with no spring
            list[lPos] = '#';
            Try(lPos, mPos, nSprings, Try); // try same pos again but with spring
            list[lPos] = '?'; // put it back
            return;
          default: assert(false); return;
        }
      };

    Try(0, 0, 0, Try);
    result += Count;
  }

  return result;
}
