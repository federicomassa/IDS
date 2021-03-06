#include <json.hpp>

using json = nlohmann::json;

int main()
{
    // a JSON text
    auto text = R"(
{
"Image": {
"Width":  800,
"Height": 600,
"Title":  "View from 15th Floor",
"Thumbnail": {
"Url":    "http://www.example.com/image/481989943",
"Height"
: 125,
"Width":  100
},
"Animated" :
false,
"IDs":
[116, 943, 234, 38793]
}
}
)";

// fill a stream with JSON text
std::stringstream ss;
ss << text;

// create JSON from stream
json j_complete(ss); // deprecated!
// shall be replaced by: json j_complete = json::parse(ss);
std::cout << std::setw(4) << j_complete << "\n\n";


// define parser callback
json::parser_callback_t cb = [](int depth, json::parse_event_t event, json & parsed)
{
// skip object elements with key "Thumbnail"
if (event == json::parse_event_t::key and parsed == json("Thumbnail"))
{
return false;
}
else
{
return true;
}
};

// fill a stream with JSON text
ss.clear();
ss << text;

// create JSON from stream (with callback)
json j_filtered(ss, cb);
// shall be replaced by: json j_filtered = json::parse(ss, cb);
std::cout << std::setw(4) << j_filtered << '\n';
}
