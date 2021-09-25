#include "pch.h"
#include "CustomPatternHandler.h"
#include "CustomPattern.h"
#include "ICustomProvider.h"

CustomPatternHandler CustomPatternHandler::GlobalInstance;

// IUnknown methods
IFACEMETHODIMP_(ULONG) CustomPatternHandler::AddRef()
{
	return InterlockedIncrement(&_refCount);
}

IFACEMETHODIMP_(ULONG) CustomPatternHandler::Release()
{
	long val = InterlockedDecrement(&_refCount);
	if (val == 0)
	{
		delete this;
	}
	return val;
}

IFACEMETHODIMP CustomPatternHandler::QueryInterface(REFIID riid, void** ppInterface)
{
	if (riid == __uuidof(IUnknown) ||
		riid == __uuidof(IUIAutomationPatternHandler))
	{
		*ppInterface = static_cast<IUIAutomationPatternHandler*>(this);
	}
	else
	{
		*ppInterface = nullptr;
		return E_NOINTERFACE;
	}

	static_cast<IUnknown*>(*ppInterface)->AddRef();
	return S_OK;
}

STDMETHODIMP CustomPatternHandler::CreateClientWrapper(
	IUIAutomationPatternInstance* pPatternInstance,
	IUnknown** pClientWrapper)
{
	*pClientWrapper = new CustomPattern(pPatternInstance);
	if (*pClientWrapper == nullptr)
	{
		return E_INVALIDARG;
	}

	return S_OK;
}

STDMETHODIMP CustomPatternHandler::Dispatch(IUnknown* pTarget, UINT index,
	const struct UIAutomationParameter* pParams,
	UINT cParams)
{
	switch (index)
	{
	case CustomPattern_CustomPatternMethod:
		return ((ICustomProvider*)pTarget)->CustomPatternMethod();
	}
	return E_INVALIDARG;
}
