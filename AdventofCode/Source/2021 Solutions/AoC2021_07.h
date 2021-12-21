void AoC2021_07A(std::istream& input)
{
  std::string line{};
  getline(input, line);
  std::istringstream str(line);

  int z{};
  std::vector<int> v{};
  int max = 0;
  int min = 9999;
  while (str >> z)
  {
    v.emplace_back(z);
    if (z > max) max = z;
    if (z < min) min = z;

    char comma;
    str >> comma;
  }

  std::vector<int> fuel{};
  fuel.resize(max + 1);
  int minf = std::numeric_limits<int>::max();
  int mini = -1;
  for (int i = min; i <= max; ++i)
  {
    int f{ 0 };
    for (auto pos : v)
    {
      f += abs(pos - i);
    }
    fuel[i] = f;
    if (f < minf)
    {
      minf = f;
      mini = i;
    }
  }

  int n = fuel[mini];
  std::cout << n << std::endl;
}

void AoC2021_07B(std::istream& input)
{
  std::string line{};
  getline(input, line);
  std::istringstream str(line);

  int z{};
  std::vector<int> v{};
  int max = 0;
  int min = 9999;
  while (str >> z)
  {
    v.emplace_back(z);
    if (z > max) max = z;
    if (z < min) min = z;

    char comma;
    str >> comma;
  }

  std::vector<int> fuel{};
  fuel.resize(max + 1);
  int minf = std::numeric_limits<int>::max();
  int mini = -1;
  for (int i = min; i <= max; ++i)
  {
    int f{ 0 };
    for (auto pos : v)
    {
      int a = abs(pos - i);
      f += a * (a + 1) / 2;
    }
    fuel[i] = f;
    if (f < minf)
    {
      minf = f;
      mini = i;
    }
  }

  int n = fuel[mini];
  std::cout << n << std::endl;

}
