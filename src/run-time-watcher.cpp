#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <chrono>
#include <iomanip>

using namespace std;

enum TimeUnit {
    MILLISECONDS,
    SECONDS,
    MINUTES,
    HOURS,
    DAYS,
    MONTHS,
    YEARS
};

struct TimeData {
    int delimiter;
    string name;
};

const map<TimeUnit, TimeData> time_units = {
        {TimeUnit::MILLISECONDS, {1000, "ms"s}},
        {TimeUnit::SECONDS,      {60,   "s"s}},
        {TimeUnit::MINUTES,      {60,   "m"s}},
        {TimeUnit::HOURS,        {60,   "h"s}},
        {TimeUnit::DAYS,         {24,   "d"s}},
        {TimeUnit::MONTHS,       {12,   "mo"s}},
        {TimeUnit::YEARS,        {1,    "yrs"s}}
};

map<TimeUnit, int> calculate(double &input) {
    map<TimeUnit, int> result;
    int cursor = TimeUnit::MILLISECONDS;
    while (input > 0 && cursor <= TimeUnit::YEARS) {
        auto current_unit = static_cast<TimeUnit>(cursor);
        int delimiter = time_units.at(current_unit).delimiter;
        result[current_unit] = fmod(input, delimiter);
        input /= delimiter;
        ++cursor;
    }
    return result;
}

class Stopwatch {
public:
    Stopwatch() {
        tstart_ = chrono::high_resolution_clock::now();
    }

    void tick() {
        chrono::high_resolution_clock::time_point tstop_ = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> delta_ = tstop_ - tstart_;
        cout << setprecision(2) << " (own: "s << delta_.count() << "ms)"s;

    }

private:
    chrono::high_resolution_clock::time_point tstart_;
};

static void print_results(const map<TimeUnit, int> &result) {
    bool is_first = true;
    for (auto iter = result.rbegin(); iter != result.rend(); ++iter) {
        if (iter->second != 0) {
            if (!is_first) {
                cout << ", "s;
            }
            cout << iter->second << " "s << time_units.at(iter->first).name;
            is_first = false;
        }
    }
}

void parse_and_format(double &input) {
    map<TimeUnit, int> result = calculate(input);
    print_results(result);
}

bool validate(const double &input_data) {
    if (input_data == 0) {
        cout << "Bad time value provided" << endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    Stopwatch watch;
    double input_data = strtod(argv[1], nullptr);
    if (!validate(input_data)) {
        return 1;
    }
    parse_and_format(input_data);
    watch.tick();
    cout << endl;
}