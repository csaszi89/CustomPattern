#pragma once
#include "ICustomPattern.h"

class CustomPattern : public ICustomPattern
{
	ULONG _refCount;
	IUIAutomationPatternInstance* _pInstance;

	// {4DA0479E-553B-483E-AF4C-A45EC1CC9391}
	const static GUID PatternGuid;
	const static LPCWSTR PatternName;
	static UIAutomationMethodInfo PatternMethods[];

public:

	// Get IUIAutomationPatternInstance interface pointer.
	CustomPattern(IUIAutomationPatternInstance* pInstance) : _refCount(1L), _pInstance(pInstance)
	{
		_pInstance->AddRef();
	}

	~CustomPattern()
	{
		_pInstance->Release();
	}

	// IUnknown methods.
	IFACEMETHOD_(ULONG, AddRef)();
	IFACEMETHOD_(ULONG, Release)();
	IFACEMETHOD(QueryInterface)(REFIID riid, void** ppInterface);

	// Custom pattern methods
	STDMETHOD(CustomPatternMethod)();
	static void InitPatternInfo(IUIAutomationPatternHandler& patternHandler);
	static int RegisteredPatternId;
	static int CustomPatternAvailablePropertyId;
	static UIAutomationPatternInfo PatternInfo;
};

enum
{
	CustomPattern_CustomPatternMethod = 0,
};

