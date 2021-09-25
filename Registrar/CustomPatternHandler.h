#pragma once
#include<UIAutomationCore.h>

class CustomPatternHandler : public IUIAutomationPatternHandler
{
	ULONG _refCount;

public:

	CustomPatternHandler() : _refCount(1L) {}

	// IUnknown methods
	IFACEMETHOD_(ULONG, AddRef)();
	IFACEMETHOD_(ULONG, Release)();
	IFACEMETHOD(QueryInterface)(REFIID riid, void** ppInterface);

	STDMETHOD(CreateClientWrapper)(
		IUIAutomationPatternInstance* pPatternInstance,
		IUnknown** pClientWrapper);

	STDMETHOD(Dispatch)(IUnknown* pTarget, UINT index,
		const struct UIAutomationParameter* pParams,
		UINT cParams);

	static CustomPatternHandler GlobalInstance;
};

