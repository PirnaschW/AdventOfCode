
namespace AdventOfCode
{

  class User
  {
  public:
    enum ID { PW, FL };
    static std::string AsString(ID id);
    static std::string GetSessionID(ID id);

  private:
    struct userData {
      std::string name;
      std::string sessionID;
    };
    static const std::unordered_map<ID, userData> users;
  };

  using Event = int;
  const std::string GetEventAsString(Event event) noexcept;

  using Day = int;
  const std::string GetDayAsString(Day day, bool leadingZeros) noexcept;

  enum Part { A, B };
  const std::string GetPartAsString(Part part) noexcept;

  const std::string GetInputPath(User::ID id, Event event, Day day);

  const std::string GetInputURL(Event event, Day day);

  bool DownloadInput(const std::string& source, User::ID id, const std::string& target);

  template<Event event, Day day, Part part>
  void Run(User::ID id)
  {
    const std::string path = GetInputPath(id, event, day);
    if (!std::filesystem::exists(path))
    {
      if (!DownloadInput(GetInputURL(event, day), id, path))
      {
        std::cout << "User " << std::setw(16) << std::left << User::AsString(id) << std::right << ": Event " << GetEventAsString(event) << " Puzzle " << GetDayAsString(day, true) << " Part " << GetPartAsString(part) << " INPUT DATA NOT YET AVAILABLE!\n" << std::endl;
        return;
      }
    }

    std::ifstream inpf(path, std::ios::in);

    // get potential testdata:
    const char* const testinput = InputData<event, day, part>();               // if the template function is not specialized, there is no test data; the default returns nullptr
    const char* const testdummy = "";                                          // dummy as we can't deref nullptr
    std::istringstream testinputstream(testinput?testinput:testdummy);         // the stream 'testinput' MUST exist as an l-lvalue; it points now either to the test input, or to an empty string

    std::istream& inp = (testinput ? static_cast<std::istream&>(testinputstream) : static_cast<std::istream&>(inpf));
    std::cout << "User " << std::setw(16) << std::left << User::AsString(id) << std::right << ": Event " << GetEventAsString(event) << " Puzzle " << GetDayAsString(day, true) << " Part " << GetPartAsString(part) << " started... " << std::flush;

    auto start = std::chrono::steady_clock::now();
    std::stringstream Result{};
    try { Result << std::setw(20) << AoC<event, day, part>(inp); }
    catch (const std::string& s) { Result << s; }
    catch (const char* s)        { Result << s; }
    catch (const char c)         { Result << c; }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    if (testinput) std::cout << "TEST-";
    std::cout << "Result = " << std::setw(20) << Result.str() << "  (" << std::setw(20) << duration.count() << " us)" << std::endl;
  }

  template<Event event, Day day>
  void RunDay(void)
  {
    Run<event, day, A>(User::FL);
    Run<event, day, B>(User::FL);
    Run<event, day, A>(User::PW);
    Run<event, day, B>(User::PW);
  }

  template<Event event>
  void RunEvent(User::ID id)
  {
    Run<event,  1, A>(id);
    Run<event,  1, B>(id);
    Run<event,  2, A>(id);
    Run<event,  2, B>(id);
    Run<event,  3, A>(id);
    Run<event,  3, B>(id);
    Run<event,  4, A>(id);
    Run<event,  4, B>(id);
    Run<event,  5, A>(id);
    Run<event,  5, B>(id);
    Run<event,  6, A>(id);
    Run<event,  6, B>(id);
    Run<event,  7, A>(id);
    Run<event,  7, B>(id);
    Run<event,  8, A>(id);
    Run<event,  8, B>(id);
    Run<event,  9, A>(id);
    Run<event,  9, B>(id);
    Run<event, 10, A>(id);
    Run<event, 10, B>(id);
    Run<event, 11, A>(id);
    Run<event, 11, B>(id);
    Run<event, 12, A>(id);
    Run<event, 12, B>(id);
    Run<event, 13, A>(id);
    Run<event, 13, B>(id);
    Run<event, 14, A>(id);
    Run<event, 14, B>(id);
    Run<event, 15, A>(id);
    Run<event, 15, B>(id);
    Run<event, 16, A>(id);
    Run<event, 16, B>(id);
    Run<event, 17, A>(id);
    Run<event, 17, B>(id);
    Run<event, 18, A>(id);
    Run<event, 18, B>(id);
    Run<event, 19, A>(id);
    Run<event, 19, B>(id);
    Run<event, 20, A>(id);
    Run<event, 20, B>(id);
    Run<event, 21, A>(id);
    Run<event, 21, B>(id);
    Run<event, 22, A>(id);
    Run<event, 22, B>(id);
    Run<event, 23, A>(id);
    Run<event, 23, B>(id);
    Run<event, 24, A>(id);
    Run<event, 24, B>(id);
    Run<event, 25, A>(id);
  }

}

template<AdventOfCode::Event event, AdventOfCode::Day day, AdventOfCode::Part part>
Number AoC(std::istream&)
{
  std::cout << "*** AoC<" << AdventOfCode::GetEventAsString(event) << "_" << AdventOfCode::GetDayAsString(day, false) << AdventOfCode::GetPartAsString(part) << " not yet implemented! ***";
  return -1;
}

template<AdventOfCode::Event event, AdventOfCode::Day day, AdventOfCode::Part part>
auto InputData() { return nullptr; }  // nullptr will result in reading the input file. Specialize this template to use local testdata instead, for example:
//template<> auto InputData<2022, 1, A>() { return "Test\nData\n"; }

