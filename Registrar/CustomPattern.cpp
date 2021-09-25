#include "pch.h"
#include "CustomPattern.h"
#include "ICustomProvider.h"

const GUID CustomPattern::PatternGuid =
{ 0x4da0479e, 0x553b, 0x483e, { 0xaf, 0x4c, 0xa4, 0x5e, 0xc1, 0xcc, 0x93, 0x91 } };

const LPCWSTR CustomPattern::PatternName = L"CustomPattern";
UIAutomationMethodInfo CustomPattern::PatternMethods[] =
{
	{L"CustomPattern.CustomPatternMethod",TRUE,0,0,nullptr,nullptr}
};

int CustomPattern::RegisteredPatternId = -1;
int CustomPattern::CustomPatternAvailablePropertyId = -1;
UIAutomationPatternInfo CustomPattern::PatternInfo;

IFACEMETHODIMP_(ULONG) CustomPattern::AddRef()
{
	return InterlockedIncrement(&_refCount);
}

IFACEMETHODIMP_(ULONG) CustomPattern::Release()
{
	long val = InterlockedDecrement(&_refCount);
	if (val == 0)
	{
		delete this;
	}
	return val;
}

IFACEMETHODIMP CustomPattern::QueryInterface(REFIID riid, void** ppInterface)
{
	if (riid == __uuidof(IUnknown) ||
		riid == __uuidof(ICustomPattern))
	{
		*ppInterface = static_cast<ICustomPattern*>(this);
	}
	else
	{
		*ppInterface = nullptr;
		return E_NOINTERFACE;
	}

	static_cast<IUnknown*>(*ppInterface)->AddRef();
	return S_OK;
}

STDMETHODIMP CustomPattern::CustomPatternMethod()
{
	HRESULT hr = _pInstance->CallMethod(CustomPattern_CustomPatternMethod, nullptr, 0);
	return hr;
}

void CustomPattern::InitPatternInfo(IUIAutomationPatternHandler& patternHandler)
{
	PatternInfo.guid = PatternGuid;
	PatternInfo.pProgrammaticName = PatternName;
	PatternInfo.clientInterfaceId = __uuidof(ICustomPattern);
	PatternInfo.providerInterfaceId = __uuidof(ICustomProvider);
	PatternInfo.pMethods = &CustomPattern::PatternMethods[0];
	PatternInfo.cMethods = ARRAYSIZE(CustomPattern::PatternMethods);
	PatternInfo.cProperties = 0;
	PatternInfo.pProperties = nullptr;
	PatternInfo.cEvents = 0;
	PatternInfo.pEvents = nullptr;
	PatternInfo.pPatternHandler = &patternHandler;
}
