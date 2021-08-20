

#include	<string>

#include	"WzbContentsException.h"


WzbContentsException::WzbContentsException(const char* whereFile, const int whereLine, const int resultCode, const std::string& message)
	: WzbException{ whereFile, whereLine, resultCode, message }
{
}
