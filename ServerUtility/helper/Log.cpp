
#include	"caf/all.hpp"

#include	"Log.h"


void WriteLog(caf::local_actor* self, const std::string& log)
{
	caf::aout(self) << log << std::endl;
}
