template<> Number AoC<2022, 5, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };


  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::stack<char>s0[9]{};
  bool done = false;
  int j = 0;
  for (j = 0; j<v.size(); ++j)
  {
    const std::string& line = v[j];
    if (done) break;
    for (int i = 0; i < 9; ++i)
    {
      char c = line[4 * i + 1];
      if (c == '1')
      {
        done = true;
        break;
      }
      if (c != ' ')
      {
        s0[i].push(c);
      }
    }
  }
  j++;

  std::stack<char>s[9]{};
  for (int i = 0; i < 9; ++i)
  {
    while (!s0[i].empty())
    {
      s[i].push(s0[i].top());
      s0[i].pop();
    }
  }

  for (; j < v.size(); ++j)
  {
    std::istringstream str(v[j]);
    std::string move{};
    std::string from{};
    std::string to{};
    int n = 0;
    Number source = 0;
    Number target = 0;
    str >> move >> n >> from >> source >> to >> target;
    source--;
    target--;
    for (int z = 0; z < n; ++z)
    {
      s[target].push(s[source].top());
      s[source].pop();
    }
  }

  std::string result{};
  for (int i = 0; i < 9; ++i)
  {
    result += s[i].top();
//    std::cout << s[i].top();
  }
//  std::cout << ' ';
  throw result;
}

template<> Number AoC<2022, 5, B>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };


  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::stack<char>s0[9]{};
  bool done = false;
  int j = 0;
  for (j = 0; j < v.size(); ++j)
  {
    const std::string& line = v[j];
    if (done) break;
    for (int i = 0; i < 9; ++i)
    {
      char c = line[4 * i + 1];
      if (c == '1')
      {
        done = true;
        break;
      }
      if (c != ' ')
      {
        s0[i].push(c);
      }
    }
  }
  j++;

  std::stack<char>s[9]{};
  for (int i = 0; i < 9; ++i)
  {
    while (!s0[i].empty())
    {
      s[i].push(s0[i].top());
      s0[i].pop();
    }
  }

  for (; j < v.size(); ++j)
  {
    std::istringstream str(v[j]);
    std::string move{};
    std::string from{};
    std::string to{};
    int n = 0;
    Number source = 0;
    Number target = 0;
    str >> move >> n >> from >> source >> to >> target;
    source--;
    target--;
    std::stack<char> temp{};
    for (int z = 0; z < n; ++z)
    {
      temp.push(s[source].top());
      s[source].pop();
    }
    for (int z = 0; z < n; ++z)
    {
      s[target].push(temp.top());
      temp.pop();
    }
  }

  std::string result{};
  for (int i = 0; i < 9; ++i)
  {
    result += s[i].top();
//    std::cout << s[i].top();
  }
  //std::cout << ' ';

  throw result;
}

