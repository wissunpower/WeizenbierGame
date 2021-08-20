

#include	<string>

#include	"WzbSystemException.h"


WzbSystemException::WzbSystemException(const char* whereFile, const int whereLine, const int resultCode, const std::string& message)
	: WzbException{ whereFile, whereLine, resultCode, message }
{
}
