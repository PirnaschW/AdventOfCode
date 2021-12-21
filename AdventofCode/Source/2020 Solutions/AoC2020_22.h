void AoC2020_22A(std::istream& input)
{
  std::string line{};
  getline(input, line); // discard 'player 1' line

  std::list<int> p1{};
  while (true)
  {
    if (!getline(input, line)) break;
    if (line.size() == 0) break;

    std::istringstream str(line);
    int z{};
    str >> z;
    p1.push_back(z);
  }

  getline(input, line); // discard 'player 2' line

  std::list<int> p2{};
  while (true)
  {
    if (!getline(input, line)) break;
    if (line.size() == 0) break;

    std::istringstream str(line);
    int z{};
    str >> z;
    p2.push_back(z);
  }

  // play
  while (p1.size() > 0 && p2.size() > 0)
  {
    int z1 = p1.front(); p1.pop_front();
    int z2 = p2.front(); p2.pop_front();

    if (z1 > z2)
    {
      p1.push_back(z1);
      p1.push_back(z2);
    }
    else
    {
      p2.push_back(z2);
      p2.push_back(z1);
    }
  }
  auto& p = p1.size() > 0 ? p1 : p2;

  Number z{ 0 };
  for (int i = 1; p.size() > 0; ++i)
  {
    z += p.front() * p.size();
    p.pop_front();
  }

  std::cout << z << std::endl;
}

void AoC2020_22B(std::istream& input)
{
  struct H
  {
    static std::string ToString(const std::list<int>& p1, const std::list<int>& p2)
    {
      std::string s{};
      assert(p1.size() < 255);
      assert(p2.size() < 255);
      s += static_cast<char>(p1.size());
      s += static_cast<char>(p2.size());
      for (const auto& z : p1) s += z;
      for (const auto& z : p2) s += z;
      return s;
    }
    static bool Play(std::list<int>& p1, std::list<int>& p2)
    {
      std::unordered_set<std::string> prev{};
      while (p1.size() > 0 && p2.size() > 0)
      {
        bool win1{};

        if (prev.contains(H::ToString(p1, p2)))  // position repeated?
        {
          return true; // => Player 1 wins automatically
        }
        prev.insert(H::ToString(p1, p2)); // remember this position

        int z1 = p1.front(); p1.pop_front();
        int z2 = p2.front(); p2.pop_front();

        if (z1 <= p1.size() && z2 <= p2.size())  // play sub-game
        {
          std::list<int> s1{};
          int i1{ 0 };
          for (auto it1 = p1.begin(); i1 < z1; ++i1, ++it1) s1.push_back(*it1);

          std::list<int> s2{};
          int i2{ 0 };
          for (auto it2 = p2.begin(); i2 < z2; ++i2, ++it2) s2.push_back(*it2);

          win1 = Play(s1, s2);
        }
        else win1 = z1 > z2;

        // recursive combat:
    //    if ();

        if (win1)
        {
          p1.push_back(z1);
          p1.push_back(z2);
        }
        else
        {
          p2.push_back(z2);
          p2.push_back(z1);
        }
      }
      return p1.size() > 0;
    }


  };



  std::string line{};
  getline(input, line); // discard 'player 1' line

  std::list<int> p1{};
  while (true)
  {
    if (!getline(input, line)) break;
    if (line.size() == 0) break;

    std::istringstream str(line);
    int z{};
    str >> z;
    p1.push_back(z);
  }

  getline(input, line); // discard 'player 2' line

  std::list<int> p2{};
  while (true)
  {
    if (!getline(input, line)) break;
    if (line.size() == 0) break;

    std::istringstream str(line);
    int z{};
    str >> z;
    p2.push_back(z);
  }

  // play
  bool win1 = H::Play(p1, p2);

  auto& p = p1.size() > 0 ? p1 : p2;

  Number z{ 0 };
  for (int i = 1; p.size() > 0; ++i)
  {
    z += p.front() * p.size();
    p.pop_front();
  }

  std::cout << z << std::endl;
}
