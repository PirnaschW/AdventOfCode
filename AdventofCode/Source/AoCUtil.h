
std::vector<std::vector<std::string>> ReadGroups(std::istream& input); // read all lines, grouping multiple lines separated by blank lines into sub-vector 
std::vector<std::string> ReadLines(std::istream& input); // read all lines into vector 
std::vector<Number> ReadNumbers(std::istream& input, char separator = '\n'); // read all input as Numbers into vector
std::vector<std::string> ReadWords(std::istream& input, char separator); // read input as words (with provided separator) into vector
std::vector<std::string> ReadWords(std::istream& input); // read all words (separated by whitespace) into vector

template <class T>
void ShowBucketHistogram(const T& cont)
{
  std::map<int, int> histogram;
  for (size_t i = 0; i < cont.bucket_count(); ++i)
    ++histogram[static_cast<int>(cont.bucket_size(static_cast<int>(i)))];
  for (auto& kv : histogram)
    std::cout << ".bucket_size() " << kv.first << " seen " << kv.second << " times\n";
  std::cout << std::endl;
}
