using Interop.UIAutomationClient;
using NUnit.Framework;
using Registrar;

namespace Test
{
    [TestFixture]
    public class Tests
    {
        [Test]
        public void Test()
        {
            CustomRegistrar.RegisterCustomProperty();
            CustomRegistrar.RegisterCustomPattern();

            var automation = new CUIAutomation8();
            var mainwindow = automation.GetRootElement().FindFirst(TreeScope.TreeScope_Children, automation.CreatePropertyCondition(UIA_PropertyIds.UIA_AutomationIdPropertyId, "Form1"));
            var button = mainwindow.FindFirst(TreeScope.TreeScope_Children, automation.CreatePropertyCondition(UIA_PropertyIds.UIA_AutomationIdPropertyId, "button1"));
            string propVal = button.GetCurrentPropertyValue(CustomRegistrar.RegisteredCustomPropertyId).ToString();
            Assert.AreEqual("Custom property", propVal);
            var pattern = button.GetCurrentPattern(CustomRegistrar.RegisteredCustomPatternId) as ICustomPattern;
            pattern.CustomPatternMethod();
            Assert.AreEqual("Text=HelloWorld", button.CurrentHelpText);
        }
    }
}
