void AoC2020_16A(std::istream& input)
{
  constexpr unsigned int bufsiz = 128;
  struct Rule
  {
    std::string name{};
    int fr1{ 0 };
    int to1{ 0 };
    int fr2{ 0 };
    int to2{ 0 };
  };
  std::vector<Rule> rules{};

  std::string line{};
  while (getline(input, line))
  {
    if (line.size() == 0) break;

    // format: "departure location: 47-164 or 179-960"
    char buffer[bufsiz]{};
    Rule r{};
    if (sscanf_s(line.c_str(), "%127[^:]: %d-%d or %d-%d", buffer, bufsiz - 1, &r.fr1, &r.to1, &r.fr2, &r.to2) == 5)
    {
      r.name = buffer;
      rules.emplace_back(r);
    }
  }

  getline(input, line);  // your ticket
  getline(input, line);  // n,n,n...
  getline(input, line);  //
  getline(input, line);  // nearby tickets

  int z{ 0 };
  while (getline(input, line))
  {
    if (line.size() == 0) break;

    std::istringstream str(line);
    int n{ 0 };
    while (str >> n)
    {
      bool valid = false;
      for (const auto& r : rules)
      {
        if (n >= r.fr1 && n <= r.to1) { valid = true; break; }
        if (n >= r.fr2 && n <= r.to2) { valid = true; break; }
      }
      if (!valid)
      {
        z += n;
        break;
      }


      char comma{};
      str >> comma;
    }
  }

  std::cout << z << std::endl;
}

void AoC2020_16B(std::istream& input)
{
  constexpr unsigned int bufsiz = 128;
  struct Rule
  {
    std::string name{};
    int fr1{ 0 };
    int to1{ 0 };
    int fr2{ 0 };
    int to2{ 0 };
    std::vector<bool> couldbe{};
    int isfield{ -1 };
  };
  std::vector<Rule> rules{};

  std::string line{};
  while (getline(input, line))
  {
    if (line.size() == 0) break;

    // format: "departure location: 47-164 or 179-960"
    char buffer[bufsiz]{};
    Rule r{};
    if (sscanf_s(line.c_str(), "%127[^:]: %d-%d or %d-%d", buffer, bufsiz - 1, &r.fr1, &r.to1, &r.fr2, &r.to2) == 5)
    {
      r.name = buffer;
      rules.emplace_back(r);
    }
  }

  for (auto& r : rules)
  {
    r.couldbe.resize(rules.size());
    for (int i = 0; i < rules.size(); ++i)
    {
      r.couldbe[i] = true;
    }
  }

  std::string myticket{};
  getline(input, line);  // your ticket
  getline(input, myticket);  // n,n,n...
  getline(input, line);  //
  getline(input, line);  // nearby tickets

  while (getline(input, line))
  {
    if (line.size() == 0) break;

    bool valid = false;
    {
      std::istringstream str(line);
      int n{ 0 };
      while (str >> n)
      {
        valid = false;
        for (const auto& r : rules)
        {
          if (n >= r.fr1 && n <= r.to1) { valid = true; break; }
          if (n >= r.fr2 && n <= r.to2) { valid = true; break; }
        }
        if (!valid) break;

        char comma{};
        str >> comma;
      }
    }
    if (!valid) continue; // ignore this ticket, next line

    std::istringstream str(line);
    int n{ 0 };
    int z{ 0 };
    while (str >> n)
    {
      for (auto& r : rules)
      {
        if ((n >= r.fr1 && n <= r.to1) || (n >= r.fr2 && n <= r.to2));
        else r.couldbe[z] = false;
      }
      ++z;

      char comma{};
      str >> comma;
    }



    for (auto& r : rules)
    {
      bool noneleft = true;
      for (int i = 0; i < rules.size(); ++i)
      {
        if (r.couldbe[i] == true) noneleft = false;
      }
      if (noneleft)
      {
        //int i = 2;
      }
    }

  }

  bool moretodo = false;
  do
  {
    moretodo = false;
    for (int i = 0; i < rules.size(); ++i)
    {
      if (rules[i].isfield != -1) continue;
      moretodo = true;

      int poss{ 0 };
      int last{ -1 };
      for (int j = 0; j < rules.size(); ++j)
      {
        if (rules[i].couldbe[j])
        {
          ++poss;
          last = j;
        }
      }
      if (poss == 1)
      {
        rules[i].isfield = last; // set this one
        for (int j = 0; j < rules.size(); ++j)
        {
          rules[j].couldbe[last] = false;  // remove all others
        }
      }
    }
  }
  while (moretodo);


  long long z{ 1LL };
  std::istringstream mystr(myticket);
  for (int i = 0; i < rules.size(); ++i)
  {
    long long n{ 0LL };
    char comma{};
    mystr >> n >> comma;

    for (auto& r : rules)
    {
      if (r.isfield == i && r.name.substr(0, 9) == "departure")
      {
        z *= n;
        break;
      }
    }
  }

  std::cout << z << std::endl;
}
