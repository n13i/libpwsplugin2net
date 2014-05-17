using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PWSPlugin
{
    public class Plugin : PWSPlugin2Net.IPlugin
    {
        public PWSPlugin2Net.IPluginInstance CreateNewInstance()
        {
            return new PluginInstance();
        }

        public void Destroy()
        {
        }
    }
}
