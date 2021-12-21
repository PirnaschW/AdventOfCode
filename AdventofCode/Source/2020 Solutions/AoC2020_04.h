namespace AoC2020_2004A
{
  bool Validate(int key, const std::string& value)
  {
    const std::unordered_set<std::string> ecl{
      { "amb" },
      { "blu" },
      { "brn" },
      { "gry" },
      { "grn" },
      { "hzl" },
      { "oth" },
    };

    int y{ 0 };
    switch (key)
    {
      case 0:
        if (value.size() != 4) return false;
        y = std::stoi(value);
        if (y < 1920 || y > 2002) return false;
        break;
      case 1:
        if (value.size() != 4) return false;
        y = std::stoi(value);
        if (y < 2010 || y > 2020) return false;
        break;
      case 2:
        if (value.size() != 4) return false;
        y = std::stoi(value);
        if (y < 2020 || y > 2030) return false;
        break;
      case 3:
        switch (value.size())
        {
          case 4:
            for (int j = 0; j < 2; ++j) if (!std::isdigit(value[j])) return false;
            if (value[2] != 'i' || value[3] != 'n') return false;
            y = std::stoi(value);
            if (y < 59 || y > 76) return false;
            break;
          case 5:
            for (int j = 0; j < 3; ++j) if (!std::isdigit(value[j])) return false;
            if (value[3] != 'c' || value[4] != 'm') return false;
            y = std::stoi(value);
            if (y < 150 || y > 193) return false;
            break;
          default:
            return false;
        }
        break;
      case 4:
        if (value.size() != 7) return false;
        if (value[0] != '#') return false;
        for (int j = 1; j < 7; ++j) if (!std::isxdigit(value[j]) || std::isupper(value[j])) return false;
        break;
      case 5:
        if (!ecl.contains(value)) return false;
        break;
      case 6:
        if (value.size() != 9) return false;
        for (int j = 0; j < 9; ++j) if (!std::isdigit(value[j])) return false;
        break;
      case 7:
        break;
    }
    return true;
  }
}

void AoC2020_04B(std::istream& input)
{
  int n{ 0 };

  constexpr int nKeys{ 8 };
  const std::unordered_map<std::string, int> m{
    { "byr", 0 },  //  byr(Birth Year)
    { "iyr", 1 },  //  iyr(Issue Year)
    { "eyr", 2 },  //  eyr(Expiration Year)
    { "hgt", 3 },  //  hgt(Height)
    { "hcl", 4 },  //  hcl(Hair Color)
    { "ecl", 5 },  //  ecl(Eye Color)
    { "pid", 6 },  //  pid(Passport ID)
    { "cid", 7 },  //  cid(Country ID)
  };
  assert(m.size() == nKeys);

  bool found[nKeys]{ false };

  for (auto& f : found) f = false;
  found[nKeys - 1] = true; // cid doesn't matter

  std::string line{};
  while (getline(input, line))
  {
    if (line.size() == 0)
    {
      // passport finished, handle
      bool complete = true;
      for (const auto& f : found) complete &= f;
      if (complete) ++n;

      // setup for next passport
      for (auto& f : found) f = false;
      found[nKeys - 1] = true; // cid doesn't matter
    }
    else
    {
      char key[4]{ 0 };
      char colon{ 0 };
      std::string value{};

      std::istringstream str(line);

      while (str >> key >> colon >> value)
      {
        assert(colon == ':');
        int index{ 0 };
        const auto it = m.find(key);
        assert(it != m.cend());

        if (AoC2020_2004A::Validate(it->second, value))
        {
          //std::cout << "Key: " << key << ", Value: " << value << std::endl;
          found[it->second] = true;
        }
      }
    }
  }
  std::cout << n << std::endl;
}

void AoC2020_04A(std::istream& input)
{
  int n{ 0 };

  constexpr int nKeys{ 8 };
  const std::unordered_map<std::string, int> m{
    { "byr", 0 },  //  byr(Birth Year)
    { "iyr", 1 },  //  iyr(Issue Year)
    { "eyr", 2 },  //  eyr(Expiration Year)
    { "hgt", 3 },  //  hgt(Height)
    { "hcl", 4 },  //  hcl(Hair Color)
    { "ecl", 5 },  //  ecl(Eye Color)
    { "pid", 6 },  //  pid(Passport ID)
    { "cid", 7 },  //  cid(Country ID)
  };
  assert(m.size() == nKeys);

  bool found[nKeys]{ false };

  for (auto& f : found) f = false;
  found[nKeys - 1] = true; // cid doesn't matter

  std::string line{};
  while (getline(input, line))
  {
    if (line.size() == 0)
    {
      // passport finished, handle
      bool complete = true;
      for (auto f : found) complete &= f;
      if (complete) ++n;

      // setup for next passport
      for (auto& f : found) f = false;
      found[nKeys - 1] = true; // cid doesn't matter
    }
    else
    {
      char key[4]{ 0 };
      char colon{ 0 };
      std::string value{};

      std::istringstream str(line);

      while (str >> key >> colon >> value)
      {
        assert(colon == ':');
        int index{ 0 };
        const auto it = m.find(key);
        assert(it != m.cend());

        found[it->second] = true;
      }
    }
  }
  std::cout << n << std::endl;
}
