
bool hasbingo(const std::vector<int>& v)
{
  for (int i = 0; i < 5; ++i)
  {
    if (
      v[5 * i + 0] == -1 &&
      v[5 * i + 1] == -1 &&
      v[5 * i + 2] == -1 &&
      v[5 * i + 3] == -1 &&
      v[5 * i + 4] == -1) return true;
    if (
      v[i + 5 * 0] == -1 &&
      v[i + 5 * 1] == -1 &&
      v[i + 5 * 2] == -1 &&
      v[i + 5 * 3] == -1 &&
      v[i + 5 * 4] == -1) return true;
  }
  //if (
  //  v[0] == -1 &&
  //  v[6] == -1 &&
  //  v[12] == -1 &&
  //  v[18] == -1 &&
  //  v[24] == -1) return true;

  //if (
  //  v[4] == -1 &&
  //  v[8] == -1 &&
  //  v[12] == -1 &&
  //  v[16] == -1 &&
  //  v[20] == -1) return true;
  return false;
}

int bingo(const std::vector<int>& v, const std::vector<int>& n)
{
  auto b = v;
  for (int i = 0; i < n.size(); ++i)
  {
    for (int j = 0; j < 25; ++j)
    {
      if (b[j] == n[i])
      {
        b[j] = -1;
        break;
      }
    }
    if (hasbingo(b)) return i;
  }
  return std::numeric_limits<int>::max();
}

int remainder(const std::vector<int>& v, const std::vector<int>& n, int z)
{
  auto b = v;
  for (int i = 0; i < z; ++i)
  {
    for (int j = 0; j < 25; ++j)
    {
      if (b[j] == n[i])
      {
        b[j] = 0;
        break;
      }
    }
  }

  int sum{ 0 };
  for (int j = 0; j < 25; ++j)
  {
    sum += b[j];
  }
  return sum;
}


void AoC2021_04A(std::istream& input)
{
  //std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  //std::vector<std::string> v = ReadWords()                 // read all words into vector 

  std::string line{};
  std::string dummy{};
  getline(input, line);

  std::vector<int> z{};

  std::istringstream str(line);
  int z0{ 0 };
  while (str >> z0) {
    z.emplace_back(z0);
    char comma{};
    str >> comma;
  }

  std::vector<std::vector<int>> board{};
  while (getline(input, dummy))
  {
    {
      std::vector<int> v{};
      v.resize(25);
      for (int i = 0; i < 25; ++i) input >> v[i];
      if (v[0] != 0 || v[1] != 0) board.emplace_back(v);
    }
  }

  std::vector<int> n{};
  n.resize(board.size());
  int min{ std::numeric_limits<int>::max() };
  int mini{ -1 };
  for (int i = 0; i < board.size(); ++i)
  {
    n[i] = bingo(board[i], z);
    if (n[i] < min)
    {
      min = n[i];
      mini = i;
    }
  }

  int sum = remainder(board[mini], z, n[mini] + 1);
  std::cout << z[min] * sum << std::endl;
}

void AoC2021_04B(std::istream& input)
{
  //std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  //std::vector<std::string> v = ReadWords()                 // read all words into vector 

  std::string line{};
  std::string dummy{};
  getline(input, line);

  std::vector<int> z{};

  std::istringstream str(line);
  int z0{ 0 };
  while (str >> z0) {
    z.emplace_back(z0);
    char comma{};
    str >> comma;
  }

  std::vector<std::vector<int>> board{};
  while (getline(input, dummy))
  {
    {
      std::vector<int> v{};
      v.resize(25);
      for (int i = 0; i < 25; ++i) input >> v[i];
      if (v[0] != 0 || v[1] != 0) board.emplace_back(v);
    }
  }

  std::vector<int> n{};
  n.resize(board.size());
  int max{ 0 };
  int maxi{ -1 };
  for (int i = 0; i < board.size(); ++i)
  {
    n[i] = bingo(board[i], z);
    if (n[i] > max)
    {
      max = n[i];
      maxi = i;
    }
  }

  int sum = remainder(board[maxi], z, n[maxi] + 1);
  std::cout << z[max] * sum << std::endl;
}
