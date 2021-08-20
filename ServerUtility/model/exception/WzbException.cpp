
#include	<string>

#include	"WzbException.h"


WzbException::WzbException(const char* whereFile, const int whereLine, const int resultCode, const std::string& message)
	: runtime_error{ "Result Code : " + std::to_string(resultCode) + " -> " + message + " in " + whereFile + ", " + std::to_string(whereLine) + "Line"}
	, ResultCode(resultCode)
{
}
