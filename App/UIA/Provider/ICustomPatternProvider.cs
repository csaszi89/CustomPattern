using System;
using System.Runtime.InteropServices;

namespace App.UIA.Provider
{
    [ComVisible(true)]
    [Guid("043220DA-D31C-496A-B5B5-56FBA7642E49")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface ICustomPatternProvider
    {
        void CustomPatternMethod();
    }
}
