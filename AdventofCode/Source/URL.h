namespace URL
{

  struct Cookie {
    std::string name{};
    std::string value{};
  };
  using Cookies = std::vector<Cookie>;

  const std::string GetHTMLFromURL(const std::string& url, const Cookies& c);
  const std::string GetHTMLFromURL(const std::string& url);
}