template<> Number AoC<2021, 10, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  int z{ 0 };

  for (const auto& line : v)
  {
    std::stack<char> braces{};
    bool done = false;
    for (auto c : line)
    {
      if (done) break;
      switch (c)
      {
        case '(': braces.push(')'); break;
        case '[': braces.push(']'); break;
        case '<': braces.push('>'); break;
        case '{': braces.push('}'); break;

        case ')':
        case ']':
        case '>':
        case '}':
          if (braces.top() != c)
          {
            switch (c)
            {
              case ')': z += 3; break;
              case ']': z += 57; break;
              case '>': z += 25137; break;
              case '}': z += 1197; break;
              default: break;
            }
            done = true;
            break;
          }
          braces.pop();
          break;
        default:
          break;
      }
    }

  }

  return z;
}

template<> Number AoC<2021, 10, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  int z{ 0 };
  std::vector<long long> scores{};

  for (const auto& line : v)
  {
    std::stack<char> braces{};
    bool done = false;
    for (auto c : line)
    {
      if (done) break;
      switch (c)
      {
        case '(': braces.push(')'); break;
        case '[': braces.push(']'); break;
        case '<': braces.push('>'); break;
        case '{': braces.push('}'); break;

        case ')':
        case ']':
        case '>':
        case '}':
          if (braces.top() != c)
          {
            switch (c)
            {
              case ')': z += 3; break;
              case ']': z += 57; break;
              case '>': z += 25137; break;
              case '}': z += 1197; break;
              default: break;
            }
            done = true;
            break;
          }
          braces.pop();
          break;
        default:
          break;
      }
    }

    if (done) continue;
    long long n{ 0 };
    while (braces.size() > 0)
    {
      n *= 5;
      switch (braces.top())
      {
        case ')': n += 1; break;
        case ']': n += 2; break;
        case '}': n += 3; break;
        case '>': n += 4; break;
        default: break;
      }
      braces.pop();
    }

    scores.emplace_back(n);
  }

  std::sort(scores.begin(), scores.end());

  return scores[scores.size() / 2];
}
