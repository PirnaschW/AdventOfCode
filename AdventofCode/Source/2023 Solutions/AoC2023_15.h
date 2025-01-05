//template<> auto InputData<2023, 15, A>() { return "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7\n";}; // Result: 1320
template<> Number AoC<2023, 15, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  auto HASH = [](const std::string& s) -> unsigned char
    {
      int z{ 0 };
      for (int i = 0; i < std::ssize(s); ++i)
      {
        z += s[i];
        z *= 17;
        z %= 256;
      }
      assert(z <= std::numeric_limits<unsigned char>::max());
      return static_cast<unsigned char>(z);
    };

  assert(HASH("HASH") == 52);

  assert(std::ssize(v) == 1);
  v[0].push_back('\0');
  constexpr unsigned int len{ 10 };
  char step[len+1];
  int p{ 0 };
  int n{ 0 };
  Number res{ 0 };
  while (sscanf_s(v[0].c_str() + p, "%[^,]%n", step, len, &n) == 1)
  {
    assert(strlen(step) < len);
    p += n + 1;
    res += HASH(step);
  }
  return res;
}

//template<> auto InputData<2023, 15, B>() { return "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7\n";}; // Result: 145
template<> Number AoC<2023, 15, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  auto HASH = [](const std::string& s) -> unsigned char
    {
      int z{ 0 };
      for (int i = 0; i < std::ssize(s); ++i)
      {
        z += s[i];
        z *= 17;
        z %= 256;
      }
      assert(z <= std::numeric_limits<unsigned char>::max());
      return static_cast<unsigned char>(z);
    };

  assert(HASH("HASH") == 52);

  assert(std::ssize(v) == 1);
  v[0].push_back('\0');
  constexpr unsigned int len{ 10 };

  class Lens
  {
  public:
    std::string label{};
    int focus{};
  };
  class Box
  {
  public:
    std::vector<Lens> lens{};
  };
  std::array<Box, 256> facility{};

  char step[len+1];
  int p{ 0 };
  int n{ 0 };
  while (sscanf_s(v[0].c_str() + p, "%[^,]%n", step, len, &n) == 1)
  {
    assert(strlen(step) < len);
    p += n + 1;

    char label[len+1];
    char oper;
    int focus;
    int z = sscanf_s(step, "%[^-=]%1c%d", label, len, &oper, 1, &focus);
    unsigned char box = HASH(label);
    switch (oper)
    {
      case '=':
        {
          assert(z == 3);
          bool found{ false };
          for (int i = 0; i < std::ssize(facility[box].lens); ++i)
          {
            if (facility[box].lens[i].label == label)
            {
              facility[box].lens[i].focus = focus;
              found = true;
              break;
            }
          }
          if (!found)
          {
            facility[box].lens.push_back({ label, focus });
          }
        }
        break;
      case '-':
        {
          assert(z == 2);
          size_t e = std::erase_if(facility[box].lens, [&label](const auto& l) { return l.label == label; });
        }
        break;
      default:
        assert(false);
        break;
    }
  }

  Number res{ 0 };
  for (int b = 0; b < std::ssize(facility); ++b)
  {
    for (int s = 0; s < std::ssize(facility[b].lens); ++s)
    {
      res += (b + 1) * (s + 1) * facility[b].lens[s].focus;
    }
  }

  return res;
}
