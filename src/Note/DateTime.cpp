#include "../../lib/Note.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


std::string Note::getCurrentDateTime() {
    // Get the current time
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    // Formatting time and date
    std::ostringstream oss;
    oss << std::put_time(now, "%H:%M %d:%m:%Y");
    return oss.str();
}