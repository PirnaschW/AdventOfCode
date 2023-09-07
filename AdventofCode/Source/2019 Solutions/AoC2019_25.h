//template<> auto InputData<2019, 25, A>() { return "Testdata\n";}; // Result: 
template<> Number AoC<2019, 25, A>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  IntCodeComputer_2019_200 icc(code);


  auto read = [&icc]() -> Number
    {
      std::string res{};
      while (icc.ExecuteToInput())
      {
        if (!icc.HasOutput()) break;
        char c = static_cast<char>(icc.PopOutput());
        //std::cout << c;
        res.push_back(c);
      }
      auto n = res.find("get in by typing ");
      if (n != std::string::npos)
      {
        Number solution{};
        std::stringstream s{ res.substr(n + 17) };
        s >> solution;
        return solution;
      }
      return 0;
    };
  auto execute = [&icc,&read](const std::string& command) -> Number
    {
      for (auto c : command)
      { 
        icc.PushInput(c);
      } 
      return read();
    };

  read();

  // User::FL
  //############### 1 (start)
  //#############H# 2 *+ fixed point
  //############# # 4 - infinite loop
  //#######G F E D# 5 + hologram
  //############# # 7 - molten lava 
  //#7 6 8#C B 0 9# 8 - photons
  //### ####### # # 0 + antenna
  //### #######A# # A + whirled peas
  //### ######### # B *+ shell
  //#5 4 3       1# C - escape pod
  //############# # E + fuel cell
  //#############2# 9 *+ candy cane
  //############### F (security checkpoint)
  //                H *+ polygon

  std::string commandFL =
    "south\n"
    "take fixed point\n"
    "north\n"
    "north\n"
    "take candy cane\n"
    "west\n"
    "west\n"
    "take shell\n"
    "east\n"
    "east\n"
    "north\n"
    "north\n"
    "take polygon\n"
    "south\n"
    "west\n"
    "west\n"
    "west\n";



  // User::PW
//###################### 1 (start)
//###D################5# 2 + mug
//### ################ # 4 *+ ornament
//###B   4   1        2# 5 + monolith
//### ### ### ######## # 6 - infinite loop
//#F E#G C H# ##X##### # 8 - molten lava
//######### # ## ##### # 9 + bowl of rice
//#########I# ##A 0### # X Santa
//########### #### ### # B *+ astrolabe
//###########3####9 8# # D *+ fuel cell
//################## # # E *+ hologram
//##################7 6# F - giant electromagnet
//###################### C - escape pod
//                       H + weather machine

  std::string commandPW =
    "west\n"
    "take ornament\n"
    "west\n"
    "take astrolabe\n"
    "north\n"
    "take fuel cell\n"
    "south\n"
    "south\n"
    "take hologram\n"
    "north\n"
    "east\n"
    "east\n"
    "east\n"
    "south\n"
    "west\n"
    "north\n"
    "west\n"
    "north\n"
    "west\n"
    "north\n";


  static int z = 0;
  switch (++z)
  {
    case 1: return execute(commandFL);
    case 2: return execute(commandPW);
  }

  Number res{0};
  while (res == 0)
  {
    std::string command{};
    getline(std::cin, command);
    command.push_back('\n');
    res = execute(command);
  }
  return res;
}

//template<> auto InputData<2019, 25, B>() { return "Testdata\n";}; // Result: 
template<> Number AoC<2019, 25, B>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');
  return 0;
}
