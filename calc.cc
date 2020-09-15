#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <functional>
#include "driver.hh"

typedef unsigned int uint;

bool
run_tests(driver& drv, const bool verbose) {
    std::map<std::string, std::function<uint(uint)>> test_expressions{
        std::make_pair<std::string, std::function<uint(uint)>>(
            "0", [](uint n) { return 0; }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 0) ? 0 : ((n == 1) ? 1 : 2)",
            [](uint n) { return (n == 0) ? 0 : ((n == 1) ? 1 : 2); }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 0) ? 0 : ((n == 1) ? 1 : (((n % 100 == 2 || n % 100 == "
            "22 || n % 100 == 42 || n % 100 == 62 || n % 100 == 82) || n % "
            "1000 == 0 && (n % 100000 >= 1000 && n % 100000 <= 20000 || n "
            "% 100000 == 40000 || n % 100000 == 60000 || n % 100000 == "
            "80000) || n != 0 && n % 1000000 == 100000) ? 2 : ((n % 100 == "
            "3 || n % 100 == 23 || n % 100 == 43 || n % 100 == 63 || n % "
            "100 == 83) ? 3 : ((n != 1 && (n % 100 == 1 || n % 100 == 21 "
            "|| n % 100 == 41 || n % 100 == 61 || n % 100 == 81)) ? 4 : "
            "5))))",
            [](uint n) {
                return (n == 0)
                           ? 0
                           : ((n == 1)
                                  ? 1
                                  : (((n % 100 == 2 || n % 100 == 22 ||
                                       n % 100 == 42 || n % 100 == 62 ||
                                       n % 100 == 82) ||
                                      n % 1000 == 0 &&
                                          (n % 100000 >= 1000 &&
                                               n % 100000 <= 20000 ||
                                           n % 100000 == 40000 ||
                                           n % 100000 == 60000 ||
                                           n % 100000 == 80000) ||
                                      n != 0 && n % 1000000 == 100000)
                                         ? 2
                                         : ((n % 100 == 3 || n % 100 == 23 ||
                                             n % 100 == 43 || n % 100 == 63 ||
                                             n % 100 == 83)
                                                ? 3
                                                : ((n != 1 && (n % 100 == 1 ||
                                                               n % 100 == 21 ||
                                                               n % 100 == 41 ||
                                                               n % 100 == 61 ||
                                                               n % 100 == 81))
                                                       ? 4
                                                       : 5))));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 0) ? 0 : ((n == 1) ? 1 : ((n == 2) ? 2 : ((n % 100 >= 3 "
            "&& n % 100 <= 10) ? 3 : ((n % 100 >= 11 && n % 100 <= 99) ? 4 "
            ": 5))))",
            [](uint n) {
                return (n == 0)
                           ? 0
                           : ((n == 1)
                                  ? 1
                                  : ((n == 2) ? 2
                                              : ((n % 100 >= 3 && n % 100 <= 10)
                                                     ? 3
                                                     : ((n % 100 >= 11 &&
                                                         n % 100 <= 99)
                                                            ? 4
                                                            : 5))));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 0) ? 0 : ((n == 1) ? 1 : ((n == 2) ? 2 : ((n == 3) ? 3 "
            ": ((n == 6) ? 4 : 5))))",
            [](uint n) {
                return (n == 0)
                           ? 0
                           : ((n == 1)
                                  ? 1
                                  : ((n == 2)
                                         ? 2
                                         : ((n == 3) ? 3
                                                     : ((n == 6) ? 4 : 5))));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 0 || n == 1) ? 0 : ((n >= 2 && n <= 10) ? 1 : 2)",
            [](uint n) {
                return (n == 0 || n == 1) ? 0 : ((n >= 2 && n <= 10) ? 1 : 2);
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "n != 1", [](uint n) { return n != 1; }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "n > 1", [](uint n) { return n > 1; }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n % 100 == 1) ? 0 : ((n % 100 == 2) ? 1 : ((n % 100 == 3 || "
            "n % 100 == 4) ? 2 : 3))",
            [](uint n) {
                return (n % 100 == 1)
                           ? 0
                           : ((n % 100 == 2)
                                  ? 1
                                  : ((n % 100 == 3 || n % 100 == 4) ? 2 : 3));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n % 10 == 0 || n % 100 >= 11 && n % 100 <= 19) ? 0 : ((n % "
            "10 == 1 && n % 100 != 11) ? 1 : 2)",
            [](uint n) {
                return (n % 10 == 0 || n % 100 >= 11 && n % 100 <= 19)
                           ? 0
                           : ((n % 10 == 1 && n % 100 != 11) ? 1 : 2);
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n % 10 == 1) ? 0 : ((n % 10 == 2) ? 1 : ((n % 100 == 0 || n "
            "% 100 == 20 || n % 100 == 40 || n % 100 == 60 || n % 100 == "
            "80) ? 2 : 3))",
            [](uint n) {
                return (n % 10 == 1)
                           ? 0
                           : ((n % 10 == 2) ? 1
                                            : ((n % 100 == 0 || n % 100 == 20 ||
                                                n % 100 == 40 ||
                                                n % 100 == 60 || n % 100 == 80)
                                                   ? 2
                                                   : 3));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "n % 10 != 1 || n % 100 == 11",
            [](uint n) { return n % 10 != 1 || n % 100 == 11; }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n % 10 == 1 && n % 100 != 11) ? 0 : ((n % 10 >= 2 && n % 10 "
            "<= 4 && (n % 100 < 12 || n % 100 > 14)) ? 1 : 2)",
            [](uint n) {
                return (n % 10 == 1 && n % 100 != 11)
                           ? 0
                           : ((n % 10 >= 2 && n % 10 <= 4 &&
                               (n % 100 < 12 || n % 100 > 14))
                                  ? 1
                                  : 2);
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n % 10 == 1 && (n % 100 < 11 || n % 100 > 19)) ? 0 : ((n % "
            "10 >= 2 && n % 10 <= 9 && (n % 100 < 11 || n % 100 > 19)) ? 1 "
            ": 2)",
            [](uint n) {
                return (n % 10 == 1 && (n % 100 < 11 || n % 100 > 19))
                           ? 0
                           : ((n % 10 >= 2 && n % 10 <= 9 &&
                               (n % 100 < 11 || n % 100 > 19))
                                  ? 1
                                  : 2);
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n % 10 == 1 && n % 100 != 11 && n % 100 != 71 && n % 100 != "
            "91) ? 0 : ((n % 10 == 2 && n % 100 != 12 && n % 100 != 72 && "
            "n % 100 != 92) ? 1 : ((((n % 10 == 3 || n % 10 == 4) || n % "
            "10 == 9) && (n % 100 < 10 || n % 100 > 19) && (n % 100 < 70 "
            "|| n % 100 > 79) && (n % 100 < 90 || n % 100 > 99)) ? 2 : ((n "
            "!= 0 && n % 1000000 == 0) ? 3 : 4)))",
            [](uint n) {
                return (n % 10 == 1 && n % 100 != 11 && n % 100 != 71 &&
                        n % 100 != 91)
                           ? 0
                           : ((n % 10 == 2 && n % 100 != 12 && n % 100 != 72 &&
                               n % 100 != 92)
                                  ? 1
                                  : ((((n % 10 == 3 || n % 10 == 4) ||
                                       n % 10 == 9) &&
                                      (n % 100 < 10 || n % 100 > 19) &&
                                      (n % 100 < 70 || n % 100 > 79) &&
                                      (n % 100 < 90 || n % 100 > 99))
                                         ? 2
                                         : ((n != 0 && n % 1000000 == 0) ? 3
                                                                         : 4)));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 1) ? 0 : ((n == 0 || n % 100 >= 2 && n % 100 <= 10) ? 1 "
            ": ((n % 100 >= 11 && n % 100 <= 19) ? 2 : 3))",
            [](uint n) {
                return (n == 1)
                           ? 0
                           : ((n == 0 || n % 100 >= 2 && n % 100 <= 10)
                                  ? 1
                                  : ((n % 100 >= 11 && n % 100 <= 19) ? 2 : 3));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 1) ? 0 : ((n == 0 || n % 100 >= 2 && n % 100 <= 19) ? 1 "
            ": 2)",
            [](uint n) {
                return (n == 1)
                           ? 0
                           : ((n == 0 || n % 100 >= 2 && n % 100 <= 19) ? 1
                                                                        : 2);
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 1) ? 0 : ((n % 10 >= 2 && n % 10 <= 4 && (n % 100 < 12 "
            "|| n % 100 > 14)) ? 1 : 2)",
            [](uint n) {
                return (n == 1) ? 0
                                : ((n % 10 >= 2 && n % 10 <= 4 &&
                                    (n % 100 < 12 || n % 100 > 14))
                                       ? 1
                                       : 2);
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 1) ? 0 : ((n == 2) ? 1 : 2)",
            [](uint n) { return (n == 1) ? 0 : ((n == 2) ? 1 : 2); }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 1) ? 0 : ((n == 2) ? 1 : ((n > 10 && n % 10 == 0) ? 2 : "
            "3))",
            [](uint n) {
                return (n == 1)
                           ? 0
                           : ((n == 2) ? 1 : ((n > 10 && n % 10 == 0) ? 2 : 3));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 1) ? 0 : ((n == 2) ? 1 : ((n >= 3 && n <= 6) ? 2 : ((n "
            ">= 7 && n <= 10) ? 3 : 4)))",
            [](uint n) {
                return (n == 1)
                           ? 0
                           : ((n == 2) ? 1
                                       : ((n >= 3 && n <= 6)
                                              ? 2
                                              : ((n >= 7 && n <= 10) ? 3 : 4)));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 1) ? 0 : ((n >= 2 && n <= 4) ? 1 : 2)",
            [](uint n) { return (n == 1) ? 0 : ((n >= 2 && n <= 4) ? 1 : 2); }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "(n == 1 || n == 11) ? 0 : ((n == 2 || n == 12) ? 1 : ((n >= 3 "
            "&& n <= 10 || n >= 13 && n <= 19) ? 2 : 3))",
            [](uint n) {
                return (n == 1 || n == 11)
                           ? 0
                           : ((n == 2 || n == 12)
                                  ? 1
                                  : ((n >= 3 && n <= 10 || n >= 13 && n <= 19)
                                         ? 2
                                         : 3));
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "n != 1 && n != 2 && n != 3 && (n % 10 == 4 || n % 10 == 6 || "
            "n % 10 == 9)",
            [](uint n) {
                return n != 1 && n != 2 && n != 3 &&
                       (n % 10 == 4 || n % 10 == 6 || n % 10 == 9);
            }),
        std::make_pair<std::string, std::function<uint(uint)>>(
            "n >= 2 && (n < 11 || n > 99)",
            [](uint n) { return n >= 2 && (n < 11 || n > 99); }),
    };

    bool success{true};
    for (const std::pair<std::string, std::function<uint(uint)>>& key_value :
         test_expressions) {
        for (uint idx = 0; idx <= 1000; ++idx) {
            drv.variables["n"] = idx;

            uint truth{key_value.second(idx)};
            if (verbose) {
                std::cout << "-----------------------------------" << std::endl;
                std::cout << "Statement: " << std::quoted(key_value.first)
                          << std::endl;
                std::cout << "n: " << idx << std::endl;
                std::cout << "Truth: " << truth << std::endl;
            }

            if (!drv.parse(key_value.first)) {
                if (verbose) {
                    std::cout << "Result: " << drv.result << std::endl;
                    std::cout << (drv.result == truth ? "Success" : "Failure")
                              << std::endl;
                }
            } else {
                success = false;
            }

            if (verbose) {
                std::cout << "-----------------------------------" << std::endl;
            }
        }
    }

    return success;
}

int
main(int argc, char* argv[]) {
    driver drv;
    bool verbose{false};
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-p")) {
            drv.trace_parsing = true;
        } else if (argv[i] == std::string("-s")) {
            drv.trace_scanning = true;
        }

        if (argv[i] == std::string("-v")) {
            verbose = true;
        }
    }

    if (!run_tests(drv, verbose)) {
        std::cout << "Tests failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Tests passed." << std::endl;
    return EXIT_SUCCESS;
}
