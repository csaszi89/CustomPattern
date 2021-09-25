#pragma once

#include<UIAutomationCore.h>

interface __declspec(uuid("1482E5CF-5C87-47EE-8838-E5F1942DD194"))
	ICustomPattern : public IUnknown
{
	STDMETHOD(CustomPatternMethod)() = 0;
};

