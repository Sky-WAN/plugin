#include "SKMP.h"

#include "skse64/PapyrusForm.h"
#include "skse64/PapyrusNativeFunctions.h"

#include "skse64/GameAPI.h"
#include "skse64/GameFormComponents.h"
#include "skse64/GameForms.h"
#include "skse64/GameRTTI.h"
#include "skse64/GameObjects.h"
#include "skse64/GameExtraData.h"
#include "skse64/PluginAPI.h"
#include "skse64/GameData.h"

#include "Client.h"

#include <vector>
#include <map>



namespace SKMP {
	Client c = NULL;

	void Init() {
		_MESSAGE("Initializing WebSocket connection");
		SKMP::c = Client::Client("ws://localhost:13337");
	}

	void HandleSKSEMessage(SKSEMessagingInterface::Message* msg) {
		if (msg->type == SKSEMessagingInterface::kMessage_PostLoadGame) {
			bool gameLoaded = &msg->data;
			if (gameLoaded) {
				_MESSAGE("Game successfully loaded");
				SKMP::Init();
			}
		}
	}

	bool RegisterFuncs(VMClassRegistry* registry) {
		//registry->RegisterFunction(new NativeFunction0<StaticFunctionTag, void>("skmpInit", "SKMP", SKMP::Init, registry));
		return true;
	}
}
