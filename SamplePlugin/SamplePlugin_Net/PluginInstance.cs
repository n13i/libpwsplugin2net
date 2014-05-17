using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PWSPlugin
{
    public class PluginInstance : PWSPlugin2Net.IPluginInstance
    {
        private PWSPlugin2Net.PluginHost host;
        private PWSPlugin2Net.MenuItem settingMenuItem;
        private PWSPlugin2Net.Timer timer;

        public PluginInstance()
        {
        }

        public void Initialize(PWSPlugin2Net.PluginHost host)
        {
            this.host = host;

            this.host.PluginFunc.Add("TEST_SAMPLEPLUGIN_test1", new PWSPlugin2Net.PluginFunctions.Proc(test1), "iS(S)");

            this.settingMenuItem = this.host.PluginMenu.Add(this.host.PluginMenu.GetSetupMenuName() + "\nサンプルプラグインの設定", PWSPlugin2Net.Menu.Style.Default, 0, new PWSPlugin2Net.MenuItem.Proc(menuCallback));

            this.timer = this.host.CreateTimer(10000, PWSPlugin2Net.Timer.Mode.Interval, new PWSPlugin2Net.Timer.Proc(timerCallback));
            this.timer.Start();
        }

        public void Destroy()
        {
        }

        void test1(List<PWSPlugin2Net.RTValue> args, PWSPlugin2Net.RTValue retVal)
        {
            // プラグインフォルダを取得したり
            string pluginFolder = this.host.SysFunc.GetPluginFolder();

            // 引数取得・戻り値セット
            System.Windows.Forms.MessageBox.Show(args[0].GetString());
            retVal.Set("戻り値");
        }

        void menuCallback(string item)
        {
            System.Windows.Forms.MessageBox.Show("メニュー " + item + "がクリックされました");
        }

        void timerCallback()
        {
            if (this.host.SysFunc.ExportFunctionExists("TEST_SAMPLEPLUGIN_callbackTest1"))
            {
                this.host.CreateInvoker().Invoke(PWSPlugin2Net.Invoker.Style.Invoke, "eV(S)", "TEST_SAMPLEPLUGIN_callbackTest1", new PWSPlugin2Net.Invoker.Proc(invokeCallback));
            }
        }

        void invokeCallback(PWSPlugin2Net.Invoker.ExitState state, PWSPlugin2Net.RTValue retVal)
        {
        }
    }
}
