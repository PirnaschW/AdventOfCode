//template<> auto InputData<2019, 6, A>() { return "COM)B\nB)C\nC)D\nD)E\nE)F\nB)G\nG)H\nD)I\nE)J\nJ)K\nK)L"; };
template<> Number AoC<2019, 6, A>(std::istream& input)
{
  auto list = ReadWords(input);

  constexpr const Number noLevel = -1LL;
  struct orbit
  {
    orbit(const std::string& s) : center(s) {}
    const std::string center;
    Number level{ noLevel };
  };

  std::map<std::string, orbit> orbits{};
  for (const std::string& line : list)
  {
    auto cut = line.find(')');
    assert(cut != std::string::npos);  /// must have a ')'
    auto mass = line.substr(0, cut);
    auto orbi = line.substr(cut + 1);
    orbits.emplace(orbi, mass);
  }

  const std::string com{ "COM" };

  auto getLevel = [&orbits, &com](auto& self, orbit& entry) -> Number
  {
    if (entry.center == com)
    {
      entry.level = 1;
    }
    else
    {
      auto next = orbits.find(entry.center);
      assert(next != orbits.end());
      Number l = self(self, next->second);
      assert(l != noLevel);
      assert(l == next->second.level + 1);
      entry.level = l;
    }
    return entry.level + 1;
  };

  Number z{ 0 };
  for (auto& entry : orbits)
  {
    if (entry.second.level == noLevel)
      getLevel(getLevel, entry.second);
    z += entry.second.level;
  }

  return z;
}


//template<> auto InputData<2019, 6, B>() { return "COM)B\nB)C\nC)D\nD)E\nE)F\nB)G\nG)H\nD)I\nE)J\nJ)K\nK)L\nK)YOU\nI)SAN"; };
template<> Number AoC<2019, 6, B>(std::istream& input)
{
  auto list = ReadWords(input);

  constexpr const Number noLevel = -1LL;
  struct orbit
  {
    orbit(const std::string& s) : center(s) {}
    const std::string center;
    Number level{ noLevel };
  };

  std::map<std::string, orbit> orbits{};
  for (const std::string& line : list)
  {
    auto cut = line.find(')');
    assert(cut != std::string::npos);  /// must have a ')'
    auto mass = line.substr(0, cut);
    auto orbi = line.substr(cut + 1);
    orbits.emplace(orbi, mass);
  }

  const std::string com{ "COM" };

  auto getLevel = [&orbits, &com](auto& self, orbit& entry) -> Number
  {
    if (entry.center == com)
    {
      entry.level = 1;
    }
    else
    {
      auto next = orbits.find(entry.center);
      assert(next != orbits.end());
      Number l = self(self, next->second);
      assert(l != noLevel);
      assert(l == next->second.level + 1);
      entry.level = l;
    }
    return entry.level + 1;
  };

  for (auto& entry : orbits)
  {
    if (entry.second.level == noLevel)
      getLevel(getLevel, entry.second);
  }

  auto oSAN = orbits.find("SAN");  // Santa
  assert(oSAN != orbits.end());
  auto oYOU = orbits.find("YOU");  // You
  assert(oYOU != orbits.end());

  
  auto Transfer = [&orbits](auto& o) { o = orbits.find(o->second.center); assert(o != orbits.end()); };

  Number z{ 0 };
  while (oSAN->second.center != oYOU->second.center)
  {
    bool transferSAN = oSAN->second.level >= oYOU->second.level;
    bool transferYOU = oYOU->second.level >= oSAN->second.level;
    if (transferSAN)
    {
      Transfer(oSAN);
      ++z;
    }
    if (transferYOU)
    {
      Transfer(oYOU);
      ++z;
    }
  }

  return z;
}
