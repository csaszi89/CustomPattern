#pragma once
#pragma comment(lib, "Ole32")

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace Registrar {
	public ref class CustomRegistrar abstract sealed
	{

	public:
		static bool RegisterCustomProperty();
		static bool RegisterCustomPattern();
		static property int RegisteredCustomPropertyId
		{
			int get();
		}
		static property int RegisteredCustomPatternId
		{
			int get();
		}

	private:
		static int s_RegisteredCustomPropertyId;
		static int s_RegisteredCustomPatternId;
	};

	[ComImport]
	[InterfaceType(ComInterfaceType::InterfaceIsIUnknown)]
	[Guid("1482E5CF-5C87-47EE-8838-E5F1942DD194")]
	public interface class ICustomPattern
	{
		[MethodImpl(MethodImplOptions::InternalCall)]
		void CustomPatternMethod();
	};
}
