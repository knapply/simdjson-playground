#include "simdjson.h"

#include <filesystem>
namespace fs = std::filesystem;

int main() {
  std::vector<std::string> json_strings{"[true,false]", "[1,2,3,null]",
                                        R"({"yay":"json!"})"};
  simdjson::dom::parser parser1;
  for (simdjson::padded_string str : json_strings) {
    auto [element, error] = parser1.parse(str);

    std::cout << element << std::endl;
  }
  std::cout << "no prob w/ simdjson::dom::parser::parse()\n" << std::endl;

  //
  //

  std::vector<std::string> file_paths{
      "adversarial.json", "flatadversarial.json", "demo.json", "repeat.json", "smalldemo.json", "truenull.json"};

  //
  //

  for (auto path : file_paths) {
    assert(fs::exists(path));

    simdjson::dom::parser parser2;

    std::cout << "file: " << path << std::endl;

    auto [element, error] = parser2.load(path);

    std::cout << "\t- error? " << error << std::endl;
  }
  std::cout << "no prob w/ simdjson::dom::parser inside loop\n" << std::endl;

  //
  //

  std::cout << "simdjson::dom::parser outside loop ->> segmentation fault" << std::endl;
  simdjson::dom::parser parser3;
  for (const auto& path : file_paths) {
    std::cout << "file: " << path << std::endl;

    auto [element, error] = parser3.load(path);

    std::cout << "\t- error? " << error << std::endl;
  }

  return 0;
}
