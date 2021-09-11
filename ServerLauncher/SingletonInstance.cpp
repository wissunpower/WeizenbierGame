
#include	"caf//all.hpp"

#include	"patterns/Singleton.h"
#include	"manager/UniqueKeyGenerator.h"

#include	"manager/ZoneSupervisor.h"

#include	"SingletonInstance.h"


ZoneSupervisor* ZoneSupervisorInstance = Singleton<ZoneSupervisor>::Get();

GlobalContext* GlobalContextInstance = Singleton<GlobalContext>::Get();

UniqueKeyGenerator* UniqueKeyGeneratorInstance = Singleton<UniqueKeyGenerator>::Get();
