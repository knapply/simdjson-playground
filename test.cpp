#include "simdjson.h"

int main() {
  std::vector<std::string> json_strings{"[true,false]", "[1,2,3,null]",
                                        R"({"yay":"json!"})"};
  simdjson::dom::parser parser1;
  for (simdjson::padded_string str : json_strings) {  // no problem ============
    auto [element, error] = parser1.parse(str);

    std::cout << element << std::endl;
  }
  //
  std::vector<std::string> file_paths{
      "adversarial.json",      "flatadversarial.json", "demo.json",
      "twitter_timeline.json", "repeat.json",          "smalldemo.json",
      "truenull.json"};
  //
  for (auto path : file_paths) {  // no problem ================================
    simdjson::dom::parser parser2;
    std::cout << "file: " << path << std::endl;
    auto [element, error] = parser2.load(path);
  }
  //
  simdjson::dom::parser parser3(4000000000);
  for (auto path : file_paths) {  // segmentation fault ========================
    std::cout << "file: " << path << std::endl;

    auto [element, error] = parser3.load(path);

    std::cout << "\t- error? " << error << std::endl;
  }

  return 0;
}
