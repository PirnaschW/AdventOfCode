enum class State
{
  Free = 1,
  Used = 2,
  Floor = 3,
};

int GetState(const std::vector<std::vector <State>>& area, int x, int y)
{
  if (x < 0 || y < 0 || x >= area.size() || y >= area[0].size()) return 0;
  return area[x][y] == State::Used ? 1 : 0;
}

int adjacent(const std::vector<std::vector <State>>& area, int x, int y)
{
  return
    GetState(area, x - 1, y - 1) + GetState(area, x - 1, y + 0) + GetState(area, x - 1, y + 1) +
    GetState(area, x + 0, y - 1) + GetState(area, x + 0, y + 1) +
    GetState(area, x + 1, y - 1) + GetState(area, x + 1, y + 0) + GetState(area, x + 1, y + 1);
}

void AoC2020_11A(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  std::vector<std::vector <State>> area{};
  area.resize(v.size());
  for (int i = 0; i < v.size(); ++i) area[i].resize(v[0].size());

  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      switch (v[i][j])
      {
        case 'L': area[i][j] = State::Free;  break;
        case '.': area[i][j] = State::Floor; break;
        case '#': area[i][j] = State::Used;  break;
        default: break;
      }
    }
  }

  bool changed = false;
  int z{ 0 };
  auto area0 = area;
  do
  {
    ++z;
    changed = false;
    area0 = area;
    for (int i = 0; i < area.size(); ++i)
    {
      for (int j = 0; j < area[i].size(); ++j)
      {
        if (area0[i][j] == State::Floor) continue;
        int n = adjacent(area, i, j);
        if (n == 0 && area[i][j] == State::Free)
        {
          area0[i][j] = State::Used;  // if no adjacents, occupy
          changed = true;
        }
        else if (n > 3 && area[i][j] == State::Used)
        {
          area0[i][j] = State::Free;
          changed = true;
        }
      }
    }
    area = area0;
  }
  while (changed);

  int n{ 0 };
  for (int i = 0; i < area.size(); ++i)
  {
    for (int j = 0; j < area[i].size(); ++j)
    {
      if (area[i][j] == State::Used) ++n;
    }
  }

//  std::cout << z << std::endl;
  std::cout << n << std::endl;
}


int GetNextState(const std::vector<std::vector <State>>& area, int x, int y, int dx, int dy)
{
  int df{ 0 };
  do
  {
    ++df;
    if (x + dx * df < 0 || y + dy * df < 0 || x + dx * df >= area.size() || y + dy * df >= area[0].size()) return 0;
    switch (area[x + dx * df][y + dy * df])
    {
      case State::Free: return 0;
      case State::Used: return 1;
      case State::Floor: break;
    }
  }
  while (true);
  return 0;
}

int nextadjacent(const std::vector<std::vector <State>>& area, int x, int y)
{
  return
    GetNextState(area, x, y, -1, -1) + GetNextState(area, x, y, -1, 0) + GetNextState(area, x, y, -1, 1) +
    GetNextState(area, x, y, +0, -1) + GetNextState(area, x, y, +0, 1) +
    GetNextState(area, x, y, +1, -1) + GetNextState(area, x, y, +1, 0) + GetNextState(area, x, y, +1, 1);
}


void AoC2020_11B(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  std::vector<std::vector <State>> area{};
  area.resize(v.size());
  for (int i = 0; i < v.size(); ++i) area[i].resize(v[0].size());

  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      switch (v[i][j])
      {
        case 'L': area[i][j] = State::Free;  break;
        case '.': area[i][j] = State::Floor; break;
        case '#': area[i][j] = State::Used;  break;
        default: break;
      }
    }
  }

  bool changed = false;
  int z{ 0 };
  auto area0 = area;
  do
  {
    ++z;
    changed = false;
    area0 = area;
    for (int i = 0; i < area.size(); ++i)
    {
      for (int j = 0; j < area[i].size(); ++j)
      {
        if (area0[i][j] == State::Floor) continue;
        int n = nextadjacent(area, i, j);
        if (n == 0 && area[i][j] == State::Free)
        {
          area0[i][j] = State::Used;  // if no adjacents, occupy
          changed = true;
        }
        else if (n > 4 && area[i][j] == State::Used)
        {
          area0[i][j] = State::Free;
          changed = true;
        }
      }
    }
    area = area0;
  }
  while (changed);

  int n{ 0 };
  for (int i = 0; i < area.size(); ++i)
  {
    for (int j = 0; j < area[i].size(); ++j)
    {
      if (area[i][j] == State::Used) ++n;
    }
  }

  //  std::cout << z << std::endl;
  std::cout << n << std::endl;
}
