void AoC2021_03B(std::istream& input)
{
  std::vector<std::string> v{};
  v.reserve(1000);
  std::string s;
  while (input >> s)
  {
    v.emplace_back(s);
  }

  std::vector<std::string> oxygen{ v };
  std::vector<std::string> scrubber{ v };

  {
    int odigit{ 0 };
    while (oxygen.size() > 1)
    {
      int z0{ 0 };
      int z1{ 0 };
      for (const auto& s : oxygen)
      {
        const char c = s[odigit];
        if (c == '0') ++z0;
        else ++z1;
      }
      bool delete_zero{ z1 >= z0 };

      std::vector<std::string> oxygen0{};
      for (auto s : oxygen)
      {
        if (delete_zero && s[odigit] == '1') oxygen0.emplace_back(s);
        else if (!delete_zero && s[odigit] == '0') oxygen0.emplace_back(s);
      }
      oxygen = oxygen0;
      ++odigit;
    }
  }

  {
    int sdigit{ 0 };
    while (scrubber.size() > 1)
    {
      int z0{ 0 };
      int z1{ 0 };
      for (const auto& s : scrubber)
      {
        const char c = s[sdigit];
        if (c == '0') ++z0;
        else ++z1;
      }
      bool delete_zero{ z0 > z1 };

      std::vector<std::string> scrubber0{};
      for (auto s : scrubber)
      {
        if (delete_zero && s[sdigit] == '1') scrubber0.emplace_back(s);
        else if (!delete_zero && s[sdigit] == '0') scrubber0.emplace_back(s);
      }
      scrubber = scrubber0;
      ++sdigit;
    }
  }


  int oxy{ 0 };
  int scr{ 0 };
  assert(oxygen.size() == 1);
  assert(scrubber.size() == 1);
  std::string soxy{ oxygen[0] };
  std::string sscr{ scrubber[0] };
  for (int i = 0; i < sscr.size(); ++i)
  {
    oxy *= 2;
    scr *= 2;
    if (soxy[i] == '1') ++oxy;
    if (sscr[i] == '1') ++scr;
  }

  std::cout << oxy * scr << ' ' << oxy << ' ' << scr << std::endl;

}

void AoC2021_03A(std::istream& input)
{
  int z0[100]{};
  int z1[100]{};
  size_t len{};
  std::string s;
  while (input >> s)
  {
    len = s.size();
    assert(s.size() < 100);
    for (int i = 0; i < s.size(); ++i)
    {
      const char c = s[i];
      if (c == '0') ++z0[i];
      else ++z1[i];
    }
  }

  int gamma{ 0 };
  int epsilon{ 0 };

  for (int i = 0; i < len; ++i)
  {
    gamma *= 2;
    epsilon *= 2;
    if (z1[i] > z0[i]) ++gamma;
    else ++epsilon;
  }

  std::cout << gamma * epsilon << ' ' << gamma << ' ' << epsilon << std::endl;
}
