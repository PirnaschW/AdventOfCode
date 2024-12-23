//template<> auto InputData<2016, 11, A>() { return "The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.\nThe second floor contains a hydrogen generator.\nThe third floor contains a lithium generator.\nThe fourth floor contains nothing relevant.\n";}; // Result: 11
template<> Number AoC<2016, 11, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // The first floor contains a strontium generator, a strontium-compatible microchip, a plutonium generator, and a plutonium-compatible microchip.
  // The second floor contains a thulium generator, a ruthenium generator, a ruthenium-compatible microchip, a curium generator, and a curium-compatible microchip.
  // The third floor contains a thulium-compatible microchip.
  // The fourth floor contains nothing relevant.

  using Level = unsigned char;
  using NameIndex = char;
  constexpr Level Levels{ 4 };
  assert(v.size() == Levels);

  class Pair
  {
  public:
    Level lg{ 0 };
    Level lm{ 0 };
    bool eg{ false }; // generator is in elevator
    bool em{ false }; // microchip is in elevator
    NameIndex n{ 0 };
    int moves{ 0 };

  public:

    bool operator <(const Pair& p) const noexcept { /*if (n < p.n) return true; if (n > p.n) return false; */ if (PosCode() < p.PosCode()) return true; return false; }
    bool operator ==(const Pair& p) const noexcept { return PosCode() == p.PosCode(); }
    int PosCode() const noexcept { return (lg << 4) + (lm << 2) + (eg ? 2 : 0) + (em ? 1 : 0); }
  };
  using List = std::vector<Pair>;

  class Elevator
  {
  public:
    Level level{ 0 };
    Level load{ 0 };
    int moves{ 0 };
  };

  List list{};

  using Names = std::vector<std::string>;
  Names names{};

  auto Insert = [&list,&names](Level level, std::string name, bool generator) -> void
    {
      NameIndex nameIndex{ -1 };
      for (NameIndex i = 0; i < names.size(); ++i)
      {
        if (names[i] == name)
        {
          nameIndex = i;
          break;
        }
      }
      if (nameIndex == -1)
      {
        nameIndex = static_cast<NameIndex>(names.size());
        names.push_back(name);
      }

      for (auto i = 0; i < list.size(); ++i)
      {
        if (list[i].n == nameIndex)
        {
          (generator ? list[i].lg : list[i].lm) = level;
          return;
        }
      }
      list.emplace_back(level, level, false, false, nameIndex);
    };

  auto ReadLine = [&list,&Insert](const char* line, Level index) -> void
    {
      constexpr int BufSize{ 32 };
      int off{ 0 };
      char floor[BufSize]{};
      sscanf_s(line, "The %s floor contains %n", &floor, BufSize, &off);
      line += off;

      while (true)
      {
        // eat potential ','
        if (line[0] == ',') ++line;

        // eat potential 'and'
        off = 0;
        sscanf_s(line, " and%n", &off);
        line += off;

        // read one item
        char conj{};
        char itemg[BufSize]{};
        int zg = sscanf_s(line, " a %s generator%c%n", itemg, BufSize, &conj, 1, &off);
        if (zg == 2)
        {
          Insert(index, itemg, true);

          if (conj == '.') break;
          line += off;
          continue;
        }

        char itemm[BufSize]{};
        int zm = sscanf_s(line, " a %[^-]-compatible microchip%c%n", itemm, BufSize, &conj, 1, &off);
        if (zm == 2)
        {
          Insert(index, itemm, false);

          if (conj == '.') break;
          line += off;
          continue;
        }

        int zn = sscanf_s(line, " nothing relevant%c%n", &conj, 1, &off);
        if (zn == 1)
        {
          assert(conj == '.');
          break;
        }

      }
    };


  for (Level i = 0; i < v.size(); ++i)
  {
    ReadLine(v[i].c_str(), i);
  }

  auto WillSurvive = [](const List& l) ->bool
    {
      for (const Pair& p1 : l)
      {
        if (p1.lg == p1.lm) continue;  // covered
        for (const Pair& p2 : l)
        {
          if (p2.lg == p1.lm) // any other generator around?
          {
            return false;
          }
        }
      }
      return true;
    };


  std::set < List, decltype([](const List& l1, const List& l2) { for (int i = 0; i < l1.size(); ++i) { if (l1[i] < l2[i]) return true; if (l2[i] < l1[i]) return false; } return false; }) > tried{};

  int minmoves{ std::numeric_limits<decltype(minmoves)>::max() };
  auto TryOption = [&tried,&minmoves](const List& l_, const Elevator& e, auto& WillSurvive, auto& TryOption) -> void
    {
      if (e.moves > minmoves) return; // can't get any better
      if (e.moves > 40) return; // can't get good enough

      if (!WillSurvive(l_)) return; // something breaks

      assert(l_[0].moves == e.moves);

      bool done{ true };
      for (const Pair& p : l_)
      {
        if (p.lg != p.lm || p.lg + 1 != Levels)
        {
          done = false;
        }
      }
      if (done)  // all objects are on top
      {
        if (e.moves < minmoves)
        {
          minmoves = e.moves;
        }
        return;
      }

      List l{ l_ };
      std::sort(l.begin(), l.end());
      l[0].moves = e.moves;
      auto it = tried.find(l);
      if (it != tried.end())
      {
        if ((*it)[0].moves > e.moves)
        {
          tried.erase(it);
          tried.insert(l);
        }
        else
        {
          return; // no progress, abort
        }
      }
      else
      {
        tried.insert(l);
      }

      // try moving stuff in elevator
      if (e.load < 2)
      {
        for (int i = 0; i < l.size(); ++i)
        {
          if (l[i].lm != e.level) continue;
          if (l[i].em) continue;

          List l0{ l };
          Elevator e0{ e };
          assert(!l0[i].em);
          l0[i].em = true;
          ++e0.load;
          TryOption(l0, e0, WillSurvive, TryOption);
        }
        for (int i = 0; i < l.size(); ++i)
        {
          if (l[i].lg != e.level) continue;
          if (l[i].eg) continue;

          List l0{ l };
          Elevator e0{ e };
          assert(!l0[i].eg);
          l0[i].eg = true;
          ++e0.load;
          TryOption(l0, e0, WillSurvive, TryOption);
        }
      }

      // try moving the elevator up
      if (e.load > 0 && e.level+1 < Levels)
      {
        Elevator e0{ e };
        ++e0.level;
        List l0{ l };
        for (int i = 0; i < l.size(); ++i)
        {
          if (l[i].em)
          {
            ++l0[i].lm;
            assert(l0[i].lm == e0.level);
          }
          if (l[i].eg)
          {
            ++l0[i].lg;
            assert(l0[i].lg == e0.level);
          }

          assert(l0[i].lg < Levels);
          assert(l0[i].lm < Levels);
        }

        ++e0.moves;
        l0[0].moves = e0.moves;
        TryOption(l0, e0, WillSurvive, TryOption);
      }

      // try moving stuff out of elevator
      if (e.load > 0)
      {
        for (int i = 0; i < l.size(); ++i)
        {
          if (!l[i].em) continue;
          assert(l[i].lm == e.level);

          List l0{ l };
          Elevator e0{ e };
          assert(l0[i].em);
          l0[i].em = false;
          --e0.load;
          TryOption(l0, e0, WillSurvive, TryOption);
        }
        for (int i = 0; i < l.size(); ++i)
        {
          if (!l[i].eg) continue;
          assert(l[i].lg == e.level);

          List l0{ l };
          Elevator e0{ e };
          assert(l0[i].eg);
          l0[i].eg = false;
          --e0.load;
          TryOption(l0, e0, WillSurvive, TryOption);
        }
      }

      // try moving the elevator down
      if (e.load > 0 && e.level > 0)
      {
        Elevator e0{ e };
        --e0.level;
        List l0{ l };
        for (int i = 0; i < l.size(); ++i)
        {
          if (l[i].em)
          {
            --l0[i].lm;
            assert(l0[i].lm == e0.level);
          }
          if (l[i].eg)
          {
            --l0[i].lg;
            assert(l0[i].lg == e0.level);
          }
        }

        ++e0.moves;
        l0[0].moves = e0.moves;
        TryOption(l0, e0, WillSurvive, TryOption);
      }

      return;
    };

  assert(WillSurvive(list));

  Elevator elevator{};
  TryOption(list, elevator, WillSurvive, TryOption);

  // PW: 41 is not right
  // PW: 37 is not right
  return minmoves;
}

//template<> auto InputData<2016, 11, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 11, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // The first floor contains a strontium generator, a strontium-compatible microchip, a plutonium generator, and a plutonium-compatible microchip.
  // The second floor contains a thulium generator, a ruthenium generator, a ruthenium-compatible microchip, a curium generator, and a curium-compatible microchip.
  // The third floor contains a thulium-compatible microchip.
  // The fourth floor contains nothing relevant.

  using Level = unsigned char;
  using NameIndex = char;
  constexpr Level Levels{ 4 };
  assert(v.size() == Levels);

  class Pair
  {
  public:
    Level lg{ 0 };
    Level lm{ 0 };
    bool eg{ false }; // generator is in elevator
    bool em{ false }; // microchip is in elevator
    NameIndex n{ 0 };
    int moves{ 0 };

  public:

    bool operator <(const Pair& p) const noexcept { /*if (n < p.n) return true; if (n > p.n) return false; */ if (PosCode() < p.PosCode()) return true; return false; }
    bool operator ==(const Pair& p) const noexcept { return PosCode() == p.PosCode(); }
    int PosCode() const noexcept { return (lg << 4) + (lm << 2) + (eg ? 2 : 0) + (em ? 1 : 0); }
  };
  using List = std::vector<Pair>;

  class Elevator
  {
  public:
    Level level{ 0 };
    Level load{ 0 };
    int moves{ 0 };
  };

  List list{};

  using Names = std::vector<std::string>;
  Names names{};

  auto Insert = [&list,&names](Level level, std::string name, bool generator) -> void
    {
      NameIndex nameIndex{ -1 };
      for (NameIndex i = 0; i < names.size(); ++i)
      {
        if (names[i] == name)
        {
          nameIndex = i;
          break;
        }
      }
      if (nameIndex == -1)
      {
        nameIndex = static_cast<NameIndex>(names.size());
        names.push_back(name);
      }

      for (auto i = 0; i < list.size(); ++i)
      {
        if (list[i].n == nameIndex)
        {
          (generator ? list[i].lg : list[i].lm) = level;
          return;
        }
      }
      list.emplace_back(level, level, false, false, nameIndex);
    };

  auto ReadLine = [&list,&Insert](const char* line, Level index) -> void
    {
      constexpr int BufSize{ 32 };
      int off{ 0 };
      char floor[BufSize]{};
      sscanf_s(line, "The %s floor contains %n", &floor, BufSize, &off);
      line += off;

      while (true)
      {
        // eat potential ','
        if (line[0] == ',') ++line;

        // eat potential 'and'
        off = 0;
        sscanf_s(line, " and%n", &off);
        line += off;

        // read one item
        char conj{};
        char itemg[BufSize]{};
        int zg = sscanf_s(line, " a %s generator%c%n", itemg, BufSize, &conj, 1, &off);
        if (zg == 2)
        {
          Insert(index, itemg, true);

          if (conj == '.') break;
          line += off;
          continue;
        }

        char itemm[BufSize]{};
        int zm = sscanf_s(line, " a %[^-]-compatible microchip%c%n", itemm, BufSize, &conj, 1, &off);
        if (zm == 2)
        {
          Insert(index, itemm, false);

          if (conj == '.') break;
          line += off;
          continue;
        }

        int zn = sscanf_s(line, " nothing relevant%c%n", &conj, 1, &off);
        if (zn == 1)
        {
          assert(conj == '.');
          break;
        }

      }
    };


  for (Level i = 0; i < v.size(); ++i)
  {
    ReadLine(v[i].c_str(), i);
  }

  auto WillSurvive = [](const List& l) ->bool
    {
      for (const Pair& p1 : l)
      {
        if (p1.lg == p1.lm) continue;  // covered
        for (const Pair& p2 : l)
        {
          if (p2.lg == p1.lm) // any other generator around?
          {
            return false;
          }
        }
      }
      return true;
    };


  std::set < List, decltype([](const List& l1, const List& l2) { for (int i = 0; i < l1.size(); ++i) { if (l1[i] < l2[i]) return true; if (l2[i] < l1[i]) return false; } return false; }) > tried{};

  int minmoves{ std::numeric_limits<decltype(minmoves)>::max() };
  auto TryOption = [&tried,&minmoves,WillSurvive](const List& l_, const Elevator& e, auto& TryOption) -> void
    {
      if (e.moves > minmoves) return; // can't get any better
      if (e.moves > 62) return; // can't get good enough

      if (!WillSurvive(l_)) return; // something breaks

      assert(l_[0].moves == e.moves);

      bool done{ true };
      for (const Pair& p : l_)
      {
        if (p.lg != p.lm || p.lg + 1 != Levels)
        {
          done = false;
          break;
        }
      }
      if (done)  // all objects are on top
      {
        if (e.moves < minmoves)
        {
          minmoves = e.moves;
        }
        return;
      }

      List l{ l_ };
      std::sort(l.begin(), l.end());
      l[0].moves = e.moves;
      auto it = tried.find(l);
      if (it != tried.end())
      {
        if ((*it)[0].moves > e.moves)
        {
          tried.erase(it);
          tried.insert(l);
        }
        else
        {
          return; // no progress, abort
        }
      }
      else
      {
        tried.insert(l);
      }

      // try moving stuff in elevator
      if (e.load < 2)
      {
        for (int i = 0; i < l.size(); ++i)
        {
          if (l[i].lm != e.level) continue;
          if (l[i].em) continue;

          List l0{ l };
          Elevator e0{ e };
          assert(!l0[i].em);
          l0[i].em = true;
          ++e0.load;
          TryOption(l0, e0, TryOption);
        }
        for (int i = 0; i < l.size(); ++i)
        {
          if (l[i].lg != e.level) continue;
          if (l[i].eg) continue;

          List l0{ l };
          Elevator e0{ e };
          assert(!l0[i].eg);
          l0[i].eg = true;
          ++e0.load;
          TryOption(l0, e0, TryOption);
        }
      }

      // try moving the elevator up
      if (e.load > 0 && e.level+1 < Levels)
      {
        Elevator e0{ e };
        ++e0.level;
        List l0{ l };
        for (int i = 0; i < l0.size(); ++i)
        {
          if (l0[i].em)
          {
            ++l0[i].lm;
            assert(l0[i].lm == e0.level);
          }
          if (l0[i].eg)
          {
            ++l0[i].lg;
            assert(l0[i].lg == e0.level);
          }
          
          assert(l0[i].lg < Levels);
          assert(l0[i].lm < Levels);
        }

        ++e0.moves;
        l0[0].moves = e0.moves;
        TryOption(l0, e0, TryOption);
      }

      // try moving stuff out of elevator
      if (e.load > 0)
      {
        for (int i = 0; i < l.size(); ++i)
        {
          if (!l[i].em) continue;
          assert(l[i].lm == e.level);

          List l0{ l };
          Elevator e0{ e };
          assert(l0[i].em);
          l0[i].em = false;
          --e0.load;
          TryOption(l0, e0, TryOption);
        }
        for (int i = 0; i < l.size(); ++i)
        {
          if (!l[i].eg) continue;
          assert(l[i].lg == e.level);

          List l0{ l };
          Elevator e0{ e };
          assert(l0[i].eg);
          l0[i].eg = false;
          --e0.load;
          TryOption(l0, e0, TryOption);
        }
      }

      // try moving the elevator down
      if (e.load > 0 && e.level > 0)
      {
        Elevator e0{ e };
        --e0.level;
        List l0{ l };
        for (int i = 0; i < l0.size(); ++i)
        {
          if (l0[i].em)
          {
            --l0[i].lm;
            assert(l0[i].lm == e0.level);
          }
          if (l0[i].eg)
          {
            --l0[i].lg;
            assert(l0[i].lg == e0.level);
          }
        }

        ++e0.moves;
        l0[0].moves = e0.moves;
        TryOption(l0, e0, TryOption);
      }

      return;
    };

  assert(WillSurvive(list));

  Insert(0, "elerium", false);
  Insert(0, "elerium", true);
  Insert(0, "dilithium", false);
  Insert(0, "dilithium", true);

  Elevator elevator{};
  TryOption(list, elevator, TryOption);

  // 69 is not right
  // 71 is not right
  return minmoves;
}
