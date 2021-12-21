void AoC2020_13A(std::istream& input)
{
  int timestamp{ 0 };
  {
    std::string line{};
    getline(input, line);
    std::istringstream str(line);
    str >> timestamp;
  }

  std::string line{};
  getline(input, line);
  std::istringstream str(line);

  char next{ 0 };
  char comma{ 0 };
  std::vector<int> bus{};
  while (str >> next)
  {
    if (next == 'x')
    {
      if (!(str >> comma)) break;
      continue;
    }

    std::string s{};
    do
    {
      s += next;
      if (!(str >> next)) break;
    }
    while (next != ',');
    bus.emplace_back(std::stoi(s));
  }

  int mini = -1;
  int minn = std::numeric_limits<int>::max();
  for (int i = 0; i < bus.size(); ++i)
  {
    int n = bus[i] - timestamp % bus[i];
    if (n < minn)
    {
      minn = n;
      mini = i;
    }
  }

  std::cout << minn * bus[mini] << std::endl;
}

void AoC2020_13B(std::istream& input)
{
  int timestamp{ 0 };
  {
    std::string line{};
    getline(input, line);
    std::istringstream str(line);
    str >> timestamp;
  }

  std::string line{};
  getline(input, line);
  std::istringstream str(line);

  char next{ 0 };
  char comma{ 0 };
  std::vector<int> bus{};
  while (str >> next)
  {
    if (next == 'x')
    {
      bus.emplace_back(0);
      if (!(str >> comma)) break;
      continue;
    }

    std::string s{};
    do
    {
      s += next;
      if (!(str >> next)) break;
    }
    while (next != ',');
    bus.emplace_back(std::stoi(s));
  }

  long long t{ 1 };
  long long step{ 1 };
  //  int minn = std::numeric_limits<int>::max();
  for (int i = 0; i < bus.size(); ++i)
  {
    if (bus[i] == 0) continue;
    long long target = (bus[i] - i);
    while (target < 0) target += bus[i];
    target %= bus[i];
    while (t % bus[i] != target)
    {
      t += step;
    }
    step *= bus[i];
  }

  std::cout << t << std::endl;
}
