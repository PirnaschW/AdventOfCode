//template<> auto InputData<2024, 5, A>() { return
//"47|53\n"
//"97|13\n"
//"97|61\n"
//"97|47\n"
//"75|29\n"
//"61|13\n"
//"75|53\n"
//"29|13\n"
//"97|29\n"
//"53|29\n"
//"61|53\n"
//"97|53\n"
//"61|29\n"
//"47|13\n"
//"75|47\n"
//"97|75\n"
//"47|61\n"
//"75|61\n"
//"47|29\n"
//"75|13\n"
//"53|13\n"
//"\n"
//"75,47,61,53,29\n"
//"97,61,53,29,13\n"
//"75,29,13\n"
//"75,97,47,61,53\n"
//"61,13,29\n"
//"97,13,75,29,47\n";}; // Result: 143
template<> Number AoC<2024, 5, A>(std::istream& input)
{
  Input v = ReadLines(input);  // read all lines into vector

  int line{ 0 };

  std::unordered_set<
    std::pair<int, int>,
    decltype([](const std::pair<int, int>& p)->size_t { return std::hash<size_t>()(static_cast<size_t>((p.first<<8) + p.second)); }),
    decltype([](const std::pair<int, int>& p1, const std::pair<int, int>& p2)->bool { return p1.first == p2.first && p1.second == p2.second; })
  > forbidden{};
  do
  {
    int p1{ 0 };
    int p2{ 0 };
    int z = sscanf_s(v[line].c_str(), "%d|%d", &p1, &p2);
    assert(z == 2);
    forbidden.insert({ p2, p1 });
  } while (v[++line] != "");

  std::vector<std::vector<int>> pagelist{};
  ++line;
  do
  {
    std::vector<int> l{};
    int p{ 0 };
    int o{ 0 };
    int n{ 0 };
    while (n = 0, sscanf_s(v[line].c_str() + o, "%d,%n", &p, &n) == 1)
    {
      l.push_back(p);
      if (n == 0) break;
      o += n;
    }
    pagelist.push_back(l);
  } while (++line < std::ssize(v));


  auto IsValid = [&forbidden](const std::vector<int>& l) -> bool
    {
      const int s = static_cast<int>(std::ssize(l));
      for (int j = 0; j < s; ++j)
      {
        for (int k = j + 1; k < s; ++k)
        {
          if (forbidden.contains({ l[j], l[k] })) return false;
        }
      }
      return true;
    };

  int res{ 0 };
  for (int i = 0; i < std::ssize(pagelist); ++i)
  {
    if (IsValid(pagelist[i]))
      res += pagelist[i][(std::ssize(pagelist[i])-1)/2];
  }

  return res;
}

//template<> auto InputData<2024, 5, B>() { return
//"47|53\n"
//"97|13\n"
//"97|61\n"
//"97|47\n"
//"75|29\n"
//"61|13\n"
//"75|53\n"
//"29|13\n"
//"97|29\n"
//"53|29\n"
//"61|53\n"
//"97|53\n"
//"61|29\n"
//"47|13\n"
//"75|47\n"
//"97|75\n"
//"47|61\n"
//"75|61\n"
//"47|29\n"
//"75|13\n"
//"53|13\n"
//"\n"
//"75,47,61,53,29\n"
//"97,61,53,29,13\n"
//"75,29,13\n"
//"75,97,47,61,53\n"
//"61,13,29\n"
//"97,13,75,29,47\n";}; // Result: 123
template<> Number AoC<2024, 5, B>(std::istream& input)
{
  Input v = ReadLines(input);  // read all lines into vector

  int line{ 0 };

  std::unordered_set<
    std::pair<int, int>,
    decltype([](const std::pair<int, int>& p)->size_t { return std::hash<size_t>()(static_cast<size_t>((p.first<<8) + p.second)); }),
    decltype([](const std::pair<int, int>& p1, const std::pair<int, int>& p2)->bool { return p1.first == p2.first && p1.second == p2.second; })
  > forbidden{};
  do
  {
    int p1{ 0 };
    int p2{ 0 };
    int z = sscanf_s(v[line].c_str(), "%d|%d", &p1, &p2);
    assert(z == 2);
    forbidden.insert({ p2, p1 });
  } while (v[++line] != "");

  std::vector<std::vector<int>> pagelist{};
  ++line;
  do
  {
    std::vector<int> l{};
    int p{ 0 };
    int o{ 0 };
    int n{ 0 };
    while (n = 0, sscanf_s(v[line].c_str() + o, "%d,%n", &p, &n) == 1)
    {
      l.push_back(p);
      if (n == 0) break;
      o += n;
    }
    pagelist.push_back(l);
  } while (++line < std::ssize(v));


  auto IsValid = [&forbidden](std::vector<int>& l, bool fix) -> bool
    {
      const int s = static_cast<int>(std::ssize(l));
      for (int j = 0; j < s; ++j)
      {
        for (int k = j + 1; k < s; ++k)
        {
          if (forbidden.contains({ l[j], l[k] }))
          {
            if (fix)
            {
              std::swap(l[j], l[k]);
            }
            return false;
          }
        }
      }
      return true;
    };

  int res{ 0 };
  for (int i = 0; i < std::ssize(pagelist); ++i)
  {
    if (IsValid(pagelist[i],false)) continue;

    while (!IsValid(pagelist[i],true));
    res += pagelist[i][(std::ssize(pagelist[i]) - 1) / 2];
  }

  return res;
}
