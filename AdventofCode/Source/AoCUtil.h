using Number = long long;

//#define PATH(event,puzzle) "Input Files\\PirnaschW\\" ## #event ## " Inputs\\AoC" ## #event ## "_" ## #puzzle ## ".txt"
#define PATH(event,puzzle) "Input Files\\FLEndlessSummer\\" ## #event ## " Inputs\\AoC" ## #event ## "_" ## #puzzle ## ".txt"
#define RUN(event,puzzle,part) \
{\
std::ifstream inpf(PATH(event, puzzle), std::ios::in);\
std::istream& inp(inpf);\
std::cout << "running Event " << #event << " Puzzle " << #puzzle << " Part " << #part << " ..." << std::endl;\
AoC ## event ## _ ## puzzle ## part ## (inp);\
}
#define RUN_ALL(event) {\
  RUN(event, 01, A);\
  RUN(event, 01, B);\
  RUN(event, 02, A);\
  RUN(event, 02, B);\
  RUN(event, 03, A);\
  RUN(event, 03, B);\
  RUN(event, 04, A);\
  RUN(event, 04, B);\
  RUN(event, 05, A);\
  RUN(event, 05, B);\
  RUN(event, 06, A);\
  RUN(event, 06, B);\
  RUN(event, 07, A);\
  RUN(event, 07, B);\
  RUN(event, 08, A);\
  RUN(event, 08, B);\
  RUN(event, 09, A);\
  RUN(event, 09, B);\
  RUN(event, 10, A);\
  RUN(event, 10, B);\
  RUN(event, 11, A);\
  RUN(event, 11, B);\
  RUN(event, 12, A);\
  RUN(event, 12, B);\
  RUN(event, 13, A);\
  RUN(event, 13, B);\
  RUN(event, 14, A);\
  RUN(event, 14, B);\
  RUN(event, 15, A);\
  RUN(event, 15, B);\
  RUN(event, 16, A);\
  RUN(event, 16, B);\
  RUN(event, 17, A);\
  RUN(event, 17, B);\
  RUN(event, 18, A);\
  RUN(event, 18, B);\
  RUN(event, 19, A);\
  RUN(event, 19, B);\
  RUN(event, 20, A);\
  RUN(event, 20, B);\
  RUN(event, 21, A);\
  RUN(event, 21, B);\
  RUN(event, 22, A);\
  RUN(event, 22, B);\
  RUN(event, 23, A);\
  RUN(event, 23, B);\
  RUN(event, 24, A);\
  RUN(event, 24, B);\
  RUN(event, 25, A);\
  RUN(event, 25, B);\
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
