//template<> auto InputData<2022, 20, A>() { return "1\n2\n-3\n3\n-2\n0\n4"; };
//template<> auto InputData<2022, 20, B>() { return "1\n2\n-3\n3\n-2\n0\n4"; };

template<> Number AoC<2022, 20, A>(std::istream& input)
{
  struct H
  {
    static int fold(int i, int n)
    {
      while (i < 0) i += n;
      while (i >= n) i -= n;
      return i;
    }
    static void print(const std::vector<Number>& v, const std::vector<int>& index, int n)
    {
      for (int j = 0; j < n; ++j)
        std::cout << v[index[j]] << ' ';
      std::cout << std::endl;

    }
  };

  std::vector<Number> v = ReadNumbers(input);
  const int n = (int) v.size();

  std::vector<int> position{}; // position[i] says in which position the value i from v is currently 

  for (int i = 0; i < n; ++i)
  {
    position.push_back(i);
  }
  std::vector<Number> vv = v;

  for (int i = 0; i < n; ++i)
  {
    int startat = position[i];
    int moveby = (int) v[i];
    while (startat + moveby < 0)
      moveby += n - 1;
    while (startat + moveby >= n)
      moveby -= n - 1;
    if (moveby == 0) continue;

    if (moveby > 0)
    {
      for (int z = startat; z < startat + moveby; ++z)
      {
        std::swap(vv[(z) % n], vv[(z + 1) % n]); // move values around
      }

      for (int j = 0; j < n; ++j)
      {
        if (position[j] > startat && position[j] <= startat + moveby)
          --position[j];
      }
      position[i] += moveby;
      position[i] %= n;
    }
    else
    {
      for (int z = startat; z > startat + moveby; --z)
      {
        std::swap(vv[(z) % n], vv[(z - 1) % n]); // move values around
      }

      for (int j = 0; j < n; ++j)
      {
        if (position[j] < startat && position[j] >= startat + moveby)
          ++position[j];
      }
      position[i] += moveby;
      position[i] %= n;
    }
  }


  // find the 0
  for (int j = 0; j < n; ++j)
  {
    if (vv[j] == 0)
    {
      Number z = vv[(j + 1000) % n] + vv[(j + 2000) % n] + vv[(j + 3000) % n];
      return z;
    }
  }
  return 0;
}

template<> Number AoC<2022, 20, B>(std::istream& input)
{
  struct H
  {
    static int fold(int i, int n)
    {
      while (i < 0) i += n;
      while (i >= n) i -= n;
      return i;
    }
    static void print(const std::vector<Number>& v, const std::vector<int>& index, int n)
    {
      for (int j = 0; j < n; ++j)
        std::cout << v[index[j]] << ' ';
      std::cout << std::endl;

    }
  };

  std::vector<Number> v = ReadNumbers(input);
  const int n = (int) v.size();

  std::vector<int> position{}; // position[i] says in which position the value i from v is currently 

  for (int i = 0; i < n; ++i)
  {
    position.push_back(i);
    v[i] *= 811589153;
  }
  std::vector<Number> vv = v;

  for (int repeat = 0; repeat < 10; ++repeat)
  {
    for (int i = 0; i < n; ++i)
    {
      int startat = position[i];
      Number Nmoveby = v[i];
      if (startat + Nmoveby < 0 || startat + Nmoveby >= n) Nmoveby %= (n - 1);
      while (startat + Nmoveby < 0)
        Nmoveby += n - 1;
      while (startat + Nmoveby >= n)
        Nmoveby -= n - 1;
      if (Nmoveby == 0) continue;
      int moveby = (int) Nmoveby;

      if (moveby > 0)
      {
        for (int z = startat; z < startat + moveby; ++z)
        {
          std::swap(vv[(z) % n], vv[(z + 1) % n]); // move values around
        }

        for (int j = 0; j < n; ++j)
        {
          if (position[j] > startat && position[j] <= startat + moveby)
            --position[j];
        }
        position[i] += moveby;
        position[i] %= n;
      }
      else
      {
        for (int z = startat; z > startat + moveby; --z)
        {
          std::swap(vv[(z) % n], vv[(z - 1) % n]); // move values around
        }

        for (int j = 0; j < n; ++j)
        {
          if (position[j] < startat && position[j] >= startat + moveby)
            ++position[j];
        }
        position[i] += moveby;
        position[i] %= n;
      }
    }
  }

  // find the 0
  for (int j = 0; j < n; ++j)
  {
    if (vv[j] == 0)
    {
      Number z = vv[(j + 1000) % n] + vv[(j + 2000) % n] + vv[(j + 3000) % n];
      return z;
    }
  }
  return 0;
}
