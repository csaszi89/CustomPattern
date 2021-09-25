using App.UIA.Provider;
using Registrar;
using System.Windows.Automation.Provider;
using System.Windows.Forms;

namespace App.UIA
{
    internal class CustomButtonRawElementProviderSimple : IRawElementProviderSimple, ICustomPatternProvider
    {
        private readonly Button _button;

        static CustomButtonRawElementProviderSimple()
        {
            RegisterCustomProperty();
            RegisterCustomPattern();
        }

        internal CustomButtonRawElementProviderSimple(Button button)
        {
            _button = button;
        }

        public ProviderOptions ProviderOptions => ProviderOptions.ServerSideProvider;

        public IRawElementProviderSimple HostRawElementProvider => AutomationInteropProvider.HostProviderFromHandle(_button.Handle);

        public object GetPatternProvider(int patternId)
        {
            if (patternId == CustomRegistrar.RegisteredCustomPatternId)
            {
                return this;
            }

            return null;
        }

        public object GetPropertyValue(int propertyId)
        {
            if(propertyId == 30013)
            {
                return $"Text={_button.Text}";
            }
            if (propertyId == CustomRegistrar.RegisteredCustomPropertyId)
            {
                return "Custom property";
            }
            return null;
        }

        private static void RegisterCustomProperty()
        {
            CustomRegistrar.RegisterCustomProperty();
        }

        private static void RegisterCustomPattern()
        {
            CustomRegistrar.RegisterCustomPattern();
        }

        public void CustomPatternMethod()
        {
            _button.Text = "HelloWorld";
        }
    }
}
