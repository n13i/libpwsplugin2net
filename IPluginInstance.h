#pragma once

#include "PluginFunctions.h"

namespace PWSPlugin2Net
{
	ref class PluginHost;

	public interface class IPluginInstance
	{
	public:
		virtual void Initialize(PluginHost^);
		virtual void Destroy();
	};
}
