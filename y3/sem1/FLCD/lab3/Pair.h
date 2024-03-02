#pragma once
#include <string>

template <typename First, typename Second>
class Pair
{
private:
	First first;
	Second second;

public:
	Pair(First first, Second second) : first(first), second(second) {};
	First getFirst() const {
		return this->first;
	};
	Second getSecond() const {
		return this->second;
	};
    std::string toString() {
        std::string result = "Pair{first=";

        if constexpr (std::is_same_v<First, int>) {
            result += std::to_string(first);
        }
        else if constexpr (std::is_same_v<First, Pair<int, int>>) {
            auto pair = first;
            result += "Pair{first=" + std::to_string(pair.getFirst()) + ", second=" + std::to_string(pair.getSecond()) + "}";
        }
        else if constexpr (std::is_same_v<First, std::string>) {
            result += first;
        }

        result += ", second=";

        if constexpr (std::is_same_v<Second, int>) {
            result += std::to_string(second);
        }
        else if constexpr (std::is_same_v<Second, Pair<int, int>>) {
            auto pair = second;
            result += "Pair{first=" + std::to_string(pair.getFirst()) + ", second=" + std::to_string(pair.getSecond()) + "}";
        }
        else if constexpr (std::is_same_v<Second, std::string>) {
            result += second;
        }

        result += "}";
        return result;
    }
};
