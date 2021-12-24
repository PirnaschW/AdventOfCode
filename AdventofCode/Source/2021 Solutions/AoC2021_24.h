void AoC2021_24A(std::istream& input)
{
  struct Status
  {
    std::array<int, 14> inputs;
    int n{ 0 };
    std::array<Number, 4> alu{};
    bool tbd{ false };
  };
  std::vector<Status> stati{};
  Status s{};
  stati.push_back(s); // start with only one, all 0, no input

  struct H
  {
    static int GetOpCode(const std::string& s)
    {
      if (s == "inp") return 0;
      if (s == "add") return 1;
      if (s == "mul") return 2;
      if (s == "div") return 3;
      if (s == "mod") return 4;
      if (s == "eql") return 5;
      assert(false); return 0;
    }

    static void RemoveDuplicates(std::vector<Status>& stati)
    {
      auto n1 = std::erase_if(stati, [](const auto& s) {return s.alu[3] > 26*26*26*26*26; });
 //     std::cout << "z too large, removed " << n1 << std::endl;

      //for (int i = 0; i < 10 && i < stati.size(); ++i)
      //{
      //  std::cout << stati[i].alu[0] << " " << stati[i].alu[1] << " " << stati[i].alu[2] << " " << stati[i].alu[3] << " " << stati[i].inputs[0] << stati[i].inputs[1] << stati[i].inputs[2] << stati[i].inputs[3] << stati[i].inputs[4] << std::endl;

      //}
      std::sort(stati.begin(), stati.end(), [](const auto& s1, const auto& s2)
      {
        if (s1.alu[0] != s2.alu[0]) return s1.alu[0] > s2.alu[0];
        if (s1.alu[1] != s2.alu[1]) return s1.alu[1] > s2.alu[1];
        if (s1.alu[2] != s2.alu[2]) return s1.alu[2] > s2.alu[2];
        if (s1.alu[3] != s2.alu[3]) return s1.alu[3] > s2.alu[3];
        for (int i = 0; i < 14; i++)
        if (s1.inputs[i] != s2.inputs[i]) return s1.inputs[i] > s2.inputs[i];
        return false;
      });

      for (int i = 1; i < stati.size(); ++i)
      {
        if (stati[i].alu[0] == stati[i - 1].alu[0] &&
            stati[i].alu[1] == stati[i - 1].alu[1] &&
            stati[i].alu[2] == stati[i - 1].alu[2] &&
            stati[i].alu[3] == stati[i - 1].alu[3])
        {
          stati[i].tbd = true;
        }
      }
      auto n2 = std::erase_if(stati, [](const auto& s) {return s.tbd; });
//      std::cout << "duplicate, removed " << n2 << std::endl;
      //for (int i = 0; i < 10 && i < stati.size(); ++i)
      //{
      //  std::cout << stati[i].alu[0] << " " << stati[i].alu[1] << " " << stati[i].alu[2] << " " << stati[i].alu[3] << " " << stati[i].inputs[0] << stati[i].inputs[1] << stati[i].inputs[2] << std::endl;

      //}

    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  for (const auto& line : v)
  {
    int op = H::GetOpCode(line.substr(0, 3));
    int p1 = 0;
    Number n2{ 0 };
    int p2 = -1;
    if (op != 0)
    {
      p1 = line[4] - 'w'; // register ID 0,1,2,3
      if (sscanf_s(line.substr(6, 99).c_str(), "%lld", &n2) != 1)
      {
        p2 = line[6] - 'w';
      }
    }
    switch (op)
    {
      case 0: 
      {
        H::RemoveDuplicates(stati);
        // add an input digit
        std::vector<Status> stati0{};
        for (auto s : stati)
        {
          s.n++;
          for (int i = 1; i < 10; ++i)
          {
            s.inputs[s.n-1] = i;
            s.alu[p1] = i;
            stati0.push_back(s);
          }
        }
        std::swap(stati, stati0);
      }
      break;
      case 1: 
        for (auto& s : stati)
        {
          s.alu[p1] += p2 == -1 ? n2 : s.alu[p2];
        }
        break;
      case 2: 
        for (auto& s : stati)
        {
          s.alu[p1] *= p2 == -1 ? n2 : s.alu[p2];
        }
        break;
      case 3:
        for (auto& s : stati)
        {
          s.alu[p1] /= p2 == -1 ? n2 : s.alu[p2];
        }
        break;
      case 4:
        for (auto& s : stati)
        {
          s.alu[p1] %= p2 == -1 ? n2 : s.alu[p2];
        }
        break;
      case 5:
        for (auto& s : stati)
        {
          s.alu[p1] = s.alu[p1] == (p2 == -1 ? n2 : s.alu[p2]) ? 1 : 0;
        }
        break;
      default: assert(false); break;
    }
  }

  auto n = std::erase_if(stati, [](const auto& s) {return s.alu[3] != 0; });

  for (auto i: stati[0].inputs)
    std::cout << i;
  std::cout << std::endl;
}

void AoC2021_24B(std::istream& input)
{
  struct Status
  {
    std::array<int, 14> inputs;
    int n{ 0 };
    std::array<Number, 4> alu{};
    bool tbd{ false };
  };
  std::vector<Status> stati{};
  Status s{};
  stati.push_back(s); // start with only one, all 0, no input

  struct H
  {
    static int GetOpCode(const std::string& s)
    {
      if (s == "inp") return 0;
      if (s == "add") return 1;
      if (s == "mul") return 2;
      if (s == "div") return 3;
      if (s == "mod") return 4;
      if (s == "eql") return 5;
      assert(false); return 0;
    }

    static void RemoveDuplicates(std::vector<Status>& stati)
    {
      auto n1 = std::erase_if(stati, [](const auto& s) {return s.alu[3] > 26 * 26 * 26 * 26 * 26; });
//      std::cout << "z too large, removed " << n1 << std::endl;

      //for (int i = 0; i < 10 && i < stati.size(); ++i)
      //{
      //  std::cout << stati[i].alu[0] << " " << stati[i].alu[1] << " " << stati[i].alu[2] << " " << stati[i].alu[3] << " " << stati[i].inputs[0] << stati[i].inputs[1] << stati[i].inputs[2] << stati[i].inputs[3] << stati[i].inputs[4] << std::endl;

      //}
      std::sort(stati.begin(), stati.end(), [](const auto& s1, const auto& s2)
      {
        if (s1.alu[0] != s2.alu[0]) return s1.alu[0] < s2.alu[0];
        if (s1.alu[1] != s2.alu[1]) return s1.alu[1] < s2.alu[1];
        if (s1.alu[2] != s2.alu[2]) return s1.alu[2] < s2.alu[2];
        if (s1.alu[3] != s2.alu[3]) return s1.alu[3] < s2.alu[3];
        for (int i = 0; i < 14; i++)
          if (s1.inputs[i] != s2.inputs[i]) return s1.inputs[i] < s2.inputs[i];
        return false;
      });

      for (int i = 1; i < stati.size(); ++i)
      {
        if (stati[i].alu[0] == stati[i - 1].alu[0] &&
            stati[i].alu[1] == stati[i - 1].alu[1] &&
            stati[i].alu[2] == stati[i - 1].alu[2] &&
            stati[i].alu[3] == stati[i - 1].alu[3])
        {
          stati[i].tbd = true;
        }
      }
      auto n2 = std::erase_if(stati, [](const auto& s) {return s.tbd; });
//      std::cout << "duplicate, removed " << n2 << std::endl;
      //for (int i = 0; i < 10 && i < stati.size(); ++i)
      //{
      //  std::cout << stati[i].alu[0] << " " << stati[i].alu[1] << " " << stati[i].alu[2] << " " << stati[i].alu[3] << " " << stati[i].inputs[0] << stati[i].inputs[1] << stati[i].inputs[2] << std::endl;

      //}

    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  for (const auto& line : v)
  {
    int op = H::GetOpCode(line.substr(0, 3));
    int p1 = 0;
    Number n2{ 0 };
    int p2 = -1;
    if (op != 0)
    {
      p1 = line[4] - 'w'; // register ID 0,1,2,3
      if (sscanf_s(line.substr(6, 99).c_str(), "%lld", &n2) != 1)
      {
        p2 = line[6] - 'w';
      }
    }
    switch (op)
    {
      case 0:
      {
        H::RemoveDuplicates(stati);
        // add an input digit
        std::vector<Status> stati0{};
        for (auto s : stati)
        {
          s.n++;
          for (int i = 1; i < 10; ++i)
          {
            s.inputs[s.n - 1] = i;
            s.alu[p1] = i;
            stati0.push_back(s);
          }
        }
        std::swap(stati, stati0);
      }
      break;
      case 1:
        for (auto& s : stati)
        {
          s.alu[p1] += p2 == -1 ? n2 : s.alu[p2];
        }
        break;
      case 2:
        for (auto& s : stati)
        {
          s.alu[p1] *= p2 == -1 ? n2 : s.alu[p2];
        }
        break;
      case 3:
        for (auto& s : stati)
        {
          s.alu[p1] /= p2 == -1 ? n2 : s.alu[p2];
        }
        break;
      case 4:
        for (auto& s : stati)
        {
          s.alu[p1] %= p2 == -1 ? n2 : s.alu[p2];
        }
        break;
      case 5:
        for (auto& s : stati)
        {
          s.alu[p1] = s.alu[p1] == (p2 == -1 ? n2 : s.alu[p2]) ? 1 : 0;
        }
        break;
      default: assert(false); break;
    }
  }

  auto n = std::erase_if(stati, [](const auto& s) {return s.alu[3] != 0; });

  for (auto i : stati[0].inputs)
    std::cout << i;
  std::cout << std::endl;
}
