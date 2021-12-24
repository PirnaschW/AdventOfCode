using Number = long long;

#define PATH(user,event,puzzle) "Input Files\\" ## #user ## "\\" ## #event ## " Inputs\\AoC" ## #event ## "_" ## #puzzle ## ".txt"
#define RUN(user,event,puzzle,part) \
{\
std::ifstream inpf(PATH(user,event, puzzle), std::ios::in);\
std::istream& inp(inpf);\
std::cout << "running Event " << #event << " Puzzle " << #puzzle << " Part " << #part << " ..." << std::endl;\
AoC ## event ## _ ## puzzle ## part ## (inp);\
}
#define RUN_ALL(user,event) {\
  RUN(user,event, 01, A);\
  RUN(user,event, 01, B);\
  RUN(user,event, 02, A);\
  RUN(user,event, 02, B);\
  RUN(user,event, 03, A);\
  RUN(user,event, 03, B);\
  RUN(user,event, 04, A);\
  RUN(user,event, 04, B);\
  RUN(user,event, 05, A);\
  RUN(user,event, 05, B);\
  RUN(user,event, 06, A);\
  RUN(user,event, 06, B);\
  RUN(user,event, 07, A);\
  RUN(user,event, 07, B);\
  RUN(user,event, 08, A);\
  RUN(user,event, 08, B);\
  RUN(user,event, 09, A);\
  RUN(user,event, 09, B);\
  RUN(user,event, 10, A);\
  RUN(user,event, 10, B);\
  RUN(user,event, 11, A);\
  RUN(user,event, 11, B);\
  RUN(user,event, 12, A);\
  RUN(user,event, 12, B);\
  RUN(user,event, 13, A);\
  RUN(user,event, 13, B);\
  RUN(user,event, 14, A);\
  RUN(user,event, 14, B);\
  RUN(user,event, 15, A);\
  RUN(user,event, 15, B);\
  RUN(user,event, 16, A);\
  RUN(user,event, 16, B);\
  RUN(user,event, 17, A);\
  RUN(user,event, 17, B);\
  RUN(user,event, 18, A);\
  RUN(user,event, 18, B);\
  RUN(user,event, 19, A);\
  RUN(user,event, 19, B);\
  RUN(user,event, 20, A);\
  RUN(user,event, 20, B);\
  RUN(user,event, 21, A);\
  RUN(user,event, 21, B);\
  RUN(user,event, 22, A);\
  RUN(user,event, 22, B);\
  RUN(user,event, 23, A);\
  RUN(user,event, 23, B);\
  RUN(user,event, 24, A);\
  RUN(user,event, 24, B);\
  RUN(user,event, 25, A);\
  RUN(user,event, 25, B);\
}

std::vector<std::vector<std::string>> ReadGroups(std::istream& input) // read all lines, grouping multiple lines separated by blank lines into sub-vector 
{
  std::vector<std::vector<std::string>> v{};
  v.reserve(100);

  std::string line{};
  std::vector<std::string> group{};
  while (getline(input, line))
  {
    if (line.size() == 0)
    {
      v.emplace_back(group);
      group.clear();
    }
    else
    {
      group.emplace_back(line);
    }
  }
  return v;
}

std::vector<std::string> ReadLines(std::istream& input) // read all lines into vector 
{
  std::vector<std::string> v{};
  v.reserve(1000);
  std::string line{};
  while (getline(input, line))
  {
    v.emplace_back(line);
  }
  return v;
}

std::vector<std::string> ReadWords(std::istream& input) // read all words into vector 
{
  std::vector<std::string> v{};
  v.reserve(1000);
  std::string s;
  while (input >> s)
  {
    v.emplace_back(s);
  }
  return v;
}
