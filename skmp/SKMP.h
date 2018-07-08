#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/GameReferences.h"
#include "skse64/GameExtraData.h"
#include "skse64/PluginAPI.h"

namespace SKMP {
	void Init(StaticFunctionTag *base);
	bool RegisterFuncs(VMClassRegistry* registry);
	void HandleSKSEMessage(SKSEMessagingInterface::Message* msg);
}
