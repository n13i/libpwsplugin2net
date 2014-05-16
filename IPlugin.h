#pragma once

#include "IPluginInstance.h"

namespace PWSPlugin2Net
{
	public interface class IPlugin
	{
	public:
		virtual IPluginInstance^ CreateNewInstance();
		virtual void Destroy();
	};
}
