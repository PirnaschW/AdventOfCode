
using CID = int;
constexpr CID NoBag{ 0 };
CID GetCID(std::unordered_map<std::string, CID>& colors, const std::string& c)
{
  auto found = colors.insert({ c, (int) colors.size() });
  return found.first->second;  // return the Color ID
}

template<> Number AoC<2020, 07, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  //std::vector<std::string> v = ReadWords()                 // read all words into vector 
  //std::vector<std::vector<std::string>> v = ReadGroups();  // read all lines, grouping multiple lines separated by blank lines into sub-vector 


  struct content
  {
    int count{ 0 };
    CID id{ NoBag };
  };
  struct Rule
  {
    CID outside{ NoBag };
    std::vector<content> inside{};
  };

  std::unordered_map<std::string, CID> colors{};
  colors.insert({ "no bag", NoBag });

  std::vector<Rule> rules{};

  for (auto& s : v)
  {
    std::istringstream str(s);

    std::string bc1{};
    std::string bc2{};
    std::string bags{};
    std::string contain{};
    str >> bc1 >> bc2 >> bags >> contain;
    std::string bc = bc1 + ' ' + bc2;

    Rule r{};
    r.outside = GetCID(colors, bc);

    int cn{ 0 };
    while (str >> cn) // try to read an int - if it fails. no more bags are inside
    {
      std::string ic1{};
      std::string ic2{};
      std::string ibags{};
      str >> ic1 >> ic2 >> ibags;
      std::string ic = ic1 + ' ' + ic2;
      content c{ cn , GetCID(colors, ic) };
      r.inside.emplace_back(c);
    }
    rules.emplace_back(r);
  }

  std::unordered_set<CID> p{};
  p.insert(GetCID(colors, "shiny gold"));

  bool more = true;
  do
  {
    more = false;
    for (auto id : p)
    {
      for (const auto& r : rules)
      {
        for (const auto& c : r.inside)
          if (c.id == id) // if the bag can be inside ...
          {
            if (p.insert(r.outside).second) more = true;   // add the outside bag, and remember if anything got really added
            break;
          }
      }
    }
  }
  while (more);

  return p.size() - 1;
}

template<> Number AoC<2020, 07, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
//std::vector<std::string> v = ReadWords()                 // read all words into vector 
//std::vector<std::vector<std::string>> v = ReadGroups();  // read all lines, grouping multiple lines separated by blank lines into sub-vector 


  struct content
  {
    int count{ 0 };
    CID id{ NoBag };
  };
  struct Rule
  {
    CID outside{ NoBag };
    std::vector<content> inside{};
    size_t total{ 0 };
  };

  std::unordered_map<std::string, CID> colors{};
  colors.insert({ "no bag", NoBag });

  std::vector<Rule> rules{};

  for (auto& s : v)
  {
    std::istringstream str(s);

    std::string bc1{};
    std::string bc2{};
    std::string bags{};
    std::string contain{};
    str >> bc1 >> bc2 >> bags >> contain;
    std::string bc = bc1 + ' ' + bc2;

    Rule r{};
    r.outside = GetCID(colors, bc);

    int cn{ 0 };
    while (str >> cn) // try to read an int - if it fails. no more bags are inside
    {
      std::string ic1{};
      std::string ic2{};
      std::string ibags{};
      str >> ic1 >> ic2 >> ibags;
      std::string ic = ic1 + ' ' + ic2;
      content c{ cn , GetCID(colors, ic) };
      r.inside.emplace_back(c);
    }
    rules.emplace_back(r);
  }

  // calc content count for each rule
  bool more = true;
  do
  {
    more = false;
    for (auto& r : rules) // check all rules
    {
      if (r.total > 0) continue; // already done

      bool subcomplete = true;
      for (const auto& c : r.inside) // for all content in this rule
      {
        for (const auto& rc : rules)  // find the matching rule for each content
        {
          if (rc.outside == c.id)
          {
            if (rc.total == 0)
            {
              subcomplete = false;  // not yet complete
              break;
            }
          }
        }
      }
      if (subcomplete)
      {
        more = true;
        r.total = 1;  // the bag itself
        for (const auto& c : r.inside) // for all content in this rule
        {
          for (const auto& rc : rules)  // find the matching rule for each content
          {
            if (rc.outside == c.id)
            {
              r.total += rc.total * c.count;
              break;
            }
          }
        }
      }
    }
  }
  while (more);


  CID target = GetCID(colors, "shiny gold");
  for (const auto& rc : rules)  // find the matching rule for this bag
  {
    if (rc.outside == target)
    {
      return rc.total - 1;
    }
  }
  assert(false);
  throw ' ';
}
