#include "pch.h"
#include "Registrar.h"
#include "CustomPattern.h"
#include "CustomPatternHandler.h"

int Registrar::CustomRegistrar::RegisteredCustomPropertyId::get()
{
	return s_RegisteredCustomPropertyId;
}

int Registrar::CustomRegistrar::RegisteredCustomPatternId::get()
{
	return s_RegisteredCustomPatternId;
}

static const GUID GUID_MyCustomProperty =
{ 0xc67e63bc, 0x14b9, 0x4354, { 0xac, 0xb5, 0x9d, 0x1c, 0xa9, 0x57, 0xb0, 0x6b } };


bool Registrar::CustomRegistrar::RegisterCustomProperty()
{
	UIAutomationPropertyInfo MyCustomPropertyInfo =
	{
		GUID_MyCustomProperty,
		L"CustomProperty",
		UIAutomationType_String
	};

	IUIAutomationRegistrar* pUIARegistrar = nullptr;
	HRESULT hr = CoCreateInstance(CLSID_CUIAutomationRegistrar, NULL, CLSCTX_INPROC_SERVER,
		IID_IUIAutomationRegistrar, (void**)&pUIARegistrar);

	if (pUIARegistrar == nullptr) {
		CoUninitialize();
		return false;
	}

	int propId = -1;
	// Register the property and retrieve the property ID. 
	hr = pUIARegistrar->RegisterProperty(&MyCustomPropertyInfo, &propId);
	pUIARegistrar->Release();
	s_RegisteredCustomPropertyId = propId;

	return hr == S_OK;
}

bool Registrar::CustomRegistrar::RegisterCustomPattern()
{
	IUIAutomationRegistrar* pUIARegistrar = nullptr;

	HRESULT hr = CoCreateInstance(CLSID_CUIAutomationRegistrar, NULL, CLSCTX_INPROC_SERVER,
		IID_IUIAutomationRegistrar, (void**)&pUIARegistrar);

	if (pUIARegistrar == nullptr)
	{
		CoUninitialize();
		return false;
	}

	CustomPattern::InitPatternInfo(CustomPatternHandler::GlobalInstance);

	// Register the control pattern.
	hr = pUIARegistrar->RegisterPattern(
		&CustomPattern::PatternInfo,
		&CustomPattern::RegisteredPatternId,
		&CustomPattern::CustomPatternAvailablePropertyId,
		0,
		nullptr,
		0,
		nullptr);

	pUIARegistrar->Release();
	s_RegisteredCustomPatternId = CustomPattern::RegisteredPatternId;
	return hr == S_OK;
}
