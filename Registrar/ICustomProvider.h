#pragma once

#include<UIAutomationCore.h>

interface __declspec(uuid("043220DA-D31C-496A-B5B5-56FBA7642E49"))
	ICustomProvider : public IUnknown
{
	STDMETHOD(CustomPatternMethod)() = 0;
};
