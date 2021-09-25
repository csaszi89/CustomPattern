using App.UIA;
using System.Windows.Automation.Provider;
using System.Windows.Forms;

namespace App.CustomControl
{
    public class CustomButton : Button
    {
        private CustomButtonRawElementProviderSimple _customButtonProvider;

        protected override void WndProc(ref Message m)
        {
            const int WmGetobject = 0x003D;

            if (m.Msg == WmGetobject && (long)m.LParam == AutomationInteropProvider.RootObjectId)
            {
                m.Result = AutomationInteropProvider.ReturnRawElementProvider(
                    Handle,
                    m.WParam,
                    m.LParam,
                    _customButtonProvider ?? (_customButtonProvider = new CustomButtonRawElementProviderSimple(this)));
                return;
            }

            base.WndProc(ref m);
        }
    }
}
