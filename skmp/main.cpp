#include "skse64/PluginAPI.h"		// super
#include "skse64_common/skse_version.h"	// What version of SKSE is running?
#include <shlobj.h>				// CSIDL_MYCODUMENTS
#include "SKMP.h"

static PluginHandle					g_pluginHandle = kPluginHandle_Invalid;
static SKSEPapyrusInterface         * g_papyrus = NULL;
static SKSEMessagingInterface		* g_messaging = NULL;

extern "C"	{

	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)	{	// Called by SKSE to learn about this plugin and check that it's safe to load it
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKMP\\debug.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_Error);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("SKSEPlugin_Query");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		"SKMP";
		info->version =		1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = skse->GetPluginHandle();

		if(skse->isEditor)
		{
			_MESSAGE("loaded in editor, marking as incompatible");

			return false;
		}
		else if(skse->runtimeVersion != RUNTIME_VERSION_1_5_39)
		{
			_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);

			return false;
		}

		// ### do not do anything else in this callback
		// ### only fill out PluginInfo and return true/false

		// supported runtime version
		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)	{	// Called by SKSE to load this plugin
		_MESSAGE("SKSEPlugin_Load");

		g_papyrus = (SKSEPapyrusInterface *)skse->QueryInterface(kInterface_Papyrus);
		g_messaging = (SKSEMessagingInterface *)skse->QueryInterface(kInterface_Messaging);

		//Check if the function registration was a success...
		bool btest = g_papyrus->Register(SKMP::RegisterFuncs);
		bool mtest = g_messaging->RegisterListener(g_pluginHandle, "SKSE", SKMP::HandleSKSEMessage);

		if (btest && mtest) {
			_MESSAGE("Register Succeeded");
		}
		else {
			_MESSAGE("Failure to register functions during SKSE plugin load");
		}

		return true;
	}

};