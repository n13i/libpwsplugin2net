#pragma once

#include "PluginFunctions.h"

namespace PWSPlugin2Net
{
	ref class PluginHost;

	public interface class IPluginInstance
	{
	public:
		delegate void FunctionRegistrar(String^ functionName, PluginFunctions::Proc^ f, String^ descriptor);

		virtual void Initialize(PluginHost^);
		virtual void RegisterFunctions(FunctionRegistrar^);
		virtual void Destroy();
	};
}
