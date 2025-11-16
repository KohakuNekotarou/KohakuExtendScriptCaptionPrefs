//========================================================================================
//  
//  $File$
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author$
//  
//  $DateTime$
//  
//  $Revision$
//  
//  $Change$
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IActiveContext.h"
#include "ILinkCaptionPrefs.h"
#include "ILinkInfoProvider.h"
#include "ILinksUIPanelPrefs.h"
#include "IMeasurementSystem.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IUnitOfMeasure.h"
#include "IUnitOfMeasureSettings.h"
#include "IWorkspace.h"

// General includes:
#include "CAlert.h"
#include "PreferenceUtils.h" // for QueryPreferences
#include "PrefsScriptProvider.h"
#include "Utils.h"

// Project includes:
#include "KESCPScriptingDefs.h"
#include "KESCPID.h"

class KESCPCaptionPreferencesScriptProvider : public PrefsScriptProvider
{
public:
	KESCPCaptionPreferencesScriptProvider(IPMUnknown* boss);

	~KESCPCaptionPreferencesScriptProvider(){}

	virtual ErrorCode HandleMethod(ScriptID scriptID_method, IScriptRequestData* iScriptRequestData, IScript* iScript);

	virtual ErrorCode AccessProperty(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);

private:
	virtual ErrorCode GetSetFrameOffset(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);

	virtual ErrorCode GetSetCaptionParagraphStyleUID(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);

	virtual ErrorCode GetSetCaptionLayerName(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);

	virtual ErrorCode GetSetGroupCaptionWithImage(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);

	virtual ErrorCode GetSetCaptionAlignment(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);

	virtual ErrorCode GetInfoProviderDescriptionString(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);
	
	virtual ErrorCode GetNumInfoProviders(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);
};

CREATE_PMINTERFACE(KESCPCaptionPreferencesScriptProvider, kKESCPCaptionPreferencesScriptProviderImpl)

KESCPCaptionPreferencesScriptProvider::KESCPCaptionPreferencesScriptProvider(IPMUnknown* boss) : PrefsScriptProvider(boss)
{
	// Define preference 
	DefinePreference(c_KESCPCaptionPreferences, p_KESCPCaptionPreferences);
}

// HandleMethod
ErrorCode KESCPCaptionPreferencesScriptProvider::HandleMethod
	(ScriptID scriptID_method, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	switch (scriptID_method.Get())
	{
	case e_KESCPGetNumInfoProviders:
		return this->GetNumInfoProviders(scriptID_method, iScriptRequestData, iScript);

	case e_KESCPGetInfoProviderDescriptionString:
		return this->GetInfoProviderDescriptionString(scriptID_method, iScriptRequestData, iScript);

	default:
		return RepresentScriptProvider::HandleMethod(scriptID_method, iScriptRequestData, iScript);
	}
}

// AccessProperty
ErrorCode KESCPCaptionPreferencesScriptProvider::AccessProperty(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;
	switch (scriptID_property.Get())
	{
	case KESCPScriptProperties::p_KESCPFrameOffset:
		status = this->GetSetFrameOffset(scriptID_property, iScriptRequestData, iScript_parent);
		break;

	case KESCPScriptProperties::p_KESCPCaptionParagraphStyleID:
		status = this->GetSetCaptionParagraphStyleUID(scriptID_property, iScriptRequestData, iScript_parent);
		break;

	case KESCPScriptProperties::p_KESCPCaptionLayerName:
		status = this->GetSetCaptionLayerName(scriptID_property, iScriptRequestData, iScript_parent);
		break;

	case KESCPScriptProperties::p_KESCPGroupCaptionWithImage:
		status = this->GetSetGroupCaptionWithImage(scriptID_property, iScriptRequestData, iScript_parent);
		break;

	case KESCPScriptProperties::p_KESCPCaptionAlignment:
		status = this->GetSetCaptionAlignment(scriptID_property, iScriptRequestData, iScript_parent);
		break;

	default:
		status = PrefsScriptProvider::AccessProperty(scriptID_property, iScriptRequestData, iScript_parent);
	}
	return status;
}

ErrorCode KESCPCaptionPreferencesScriptProvider::GetSetFrameOffset(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;
		PMReal pMReal_unit, pMReal_point;

		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Unit acquisition.
		InterfacePtr<IUnitOfMeasureSettings> iUnitOfMeasureSettings(
			(IUnitOfMeasureSettings*)::QueryPreferences(IID_IUNITOFMEASURESETTINGS, iActiveContext)
		);
		if (iUnitOfMeasureSettings == nil) break;

		ClassID classID_unit = iUnitOfMeasureSettings->GetYUnitOfMeasure();

		InterfacePtr<IMeasurementSystem> iMeasurementSystem(GetExecutionContextSession(), ::UseDefaultIID());
		if (iMeasurementSystem == nil) break;

		InterfacePtr<IUnitOfMeasure> iUnitOfMeasure(
			iMeasurementSystem->QueryUnitOfMeasure(iMeasurementSystem->Location(classID_unit))
		);
		if (iUnitOfMeasure == nil) break;

		// ---------------------------------------------------------------------------------------
		// Processing request data
		if (iScriptRequestData->IsPropertyGet()) // Get
		{
			// ---------------------------------------------------------------------------------------
			// Get.
			pMReal_point = iLinkCaptionPrefs->GetFrameOffset();

			pMReal_unit = iUnitOfMeasure->PointsToUnits(pMReal_point);

			// ---------------------------------------------------------------------------------------
			// Append return data
			iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, ScriptData(pMReal_unit));
		}
		else if (iScriptRequestData->IsPropertyPut()) // Set
		{
			// ---------------------------------------------------------------------------------------
			// Extract request data
			status = iScriptRequestData->ExtractRequestData(scriptID_property.Get(), scriptData);
			if (status != kSuccess) break;

			status = scriptData.GetPMReal(&pMReal_unit);
			if (status != kSuccess) break;

			// ---------------------------------------------------------------------------------------
			// Set.
			pMReal_point = iUnitOfMeasure->UnitsToPoints(pMReal_unit);

			iLinkCaptionPrefs->SetFrameOffset(pMReal_point);
		}

		status = kSuccess;

	} while (false); // only do once

	return status;
}

ErrorCode KESCPCaptionPreferencesScriptProvider::GetSetCaptionParagraphStyleUID(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;
		UID uID;

		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = ::GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Processing request data
		if (iScriptRequestData->IsPropertyGet()) // Get
		{
			uID = iLinkCaptionPrefs->GetCaptionParagraphStyleUID();

			// ---------------------------------------------------------------------------------------
			// Append return data
			scriptData.SetInt32(uID.Get());

			iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, scriptData);
		}
		else if (iScriptRequestData->IsPropertyPut()) // Set
		{
			// ---------------------------------------------------------------------------------------
			// Extract request data
			status = iScriptRequestData->ExtractRequestData(scriptID_property.Get(), scriptData);
			if (status != kSuccess) break;

			int32 int32_uID;
			status = scriptData.GetInt32(&int32_uID);
			if (status != kSuccess) break;
			uID = int32_uID;

			// ---------------------------------------------------------------------------------------
			// Set.
			iLinkCaptionPrefs->SetCaptionParagraphStyleUID(uID);
		}
		status = kSuccess;

	} while (false); // only do once

	return status;
}

ErrorCode KESCPCaptionPreferencesScriptProvider::GetSetCaptionLayerName(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;
		PMString pMString_layerName;
		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = ::GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Processing request data
		if (iScriptRequestData->IsPropertyGet()) // Get
		{
			pMString_layerName = iLinkCaptionPrefs->GetCaptionLayerName();

			// ---------------------------------------------------------------------------------------
			// Append return data
			iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, ScriptData(pMString_layerName));
		}
		else if (iScriptRequestData->IsPropertyPut()) // Set
		{
			// ---------------------------------------------------------------------------------------
			// Extract request data
			status = iScriptRequestData->ExtractRequestData(scriptID_property.Get(), scriptData);
			if (status != kSuccess) break;

			status = scriptData.GetPMString(pMString_layerName);
			if (status != kSuccess) break;

			// ---------------------------------------------------------------------------------------
			// Set.
			iLinkCaptionPrefs->SetCaptionLayerName(pMString_layerName);
		}
		status = kSuccess;

	} while (false); // only do once

	return status;
}

ErrorCode KESCPCaptionPreferencesScriptProvider::GetSetGroupCaptionWithImage(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;
		bool16 bool16_groupCaptionFlg;
		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = ::GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Processing request data
		if (iScriptRequestData->IsPropertyGet()) // Get
		{
			bool16_groupCaptionFlg = iLinkCaptionPrefs->GetGroupCaptionWithImage();

			// ---------------------------------------------------------------------------------------
			// Append return data
			iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, ScriptData(bool16_groupCaptionFlg));
		}
		else if (iScriptRequestData->IsPropertyPut()) // Set
		{
			// ---------------------------------------------------------------------------------------
			// Extract request data
			status = iScriptRequestData->ExtractRequestData(scriptID_property.Get(), scriptData);
			if (status != kSuccess) break;

			status = scriptData.GetBoolean(&bool16_groupCaptionFlg);
			if (status != kSuccess) break;

			// ---------------------------------------------------------------------------------------
			// Set.
			iLinkCaptionPrefs->SetGroupCaptionWithImage(bool16_groupCaptionFlg);
		}
		status = kSuccess;

	} while (false); // only do once

	return status;
}

ErrorCode KESCPCaptionPreferencesScriptProvider::GetSetCaptionAlignment(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;
		PMString pMString_captionAlignment;
		ILinkCaptionPrefs::CaptionAlignment captionAlignment = ILinkCaptionPrefs::kAlignBelow;
		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = ::GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Processing request data
		if (iScriptRequestData->IsPropertyGet()) // Get
		{
			captionAlignment = iLinkCaptionPrefs->GetCaptionAlignment();

			switch (captionAlignment)
			{
			case ILinkCaptionPrefs::kAlignBelow:
				pMString_captionAlignment = "Below";
				break;

			case ILinkCaptionPrefs::kAlignAbove:
				pMString_captionAlignment = "Above";
				break;

			case ILinkCaptionPrefs::kAlignLeft:
				pMString_captionAlignment = "Left";
				break;

			case ILinkCaptionPrefs::kAlignRight:
				pMString_captionAlignment = "Right";
				break;

			default:
				break;
			}

			// ---------------------------------------------------------------------------------------
			// Append return data
			iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, ScriptData(pMString_captionAlignment));
		}
		else if (iScriptRequestData->IsPropertyPut()) // Set
		{
			// ---------------------------------------------------------------------------------------
			// Extract request data
			status = iScriptRequestData->ExtractRequestData(scriptID_property.Get(), scriptData);
			if (status != kSuccess) break;

			status = scriptData.GetPMString(pMString_captionAlignment);
			if (status != kSuccess) break;

			if (pMString_captionAlignment == "Below")
			{
				captionAlignment = ILinkCaptionPrefs::kAlignBelow;
			}
			else if (pMString_captionAlignment == "Above")
			{
				captionAlignment = ILinkCaptionPrefs::kAlignAbove;
			}
			else if (pMString_captionAlignment == "Left")
			{
				captionAlignment = ILinkCaptionPrefs::kAlignLeft;
			}
			else if (pMString_captionAlignment == "Right")
			{
				captionAlignment = ILinkCaptionPrefs::kAlignRight;
			}
			else
			{
				break;
			}

			// ---------------------------------------------------------------------------------------
			// Set.
			iLinkCaptionPrefs->SetCaptionAlignment(captionAlignment);
		}
		status = kSuccess;

	} while (false); // only do once

	return status;
}

ErrorCode KESCPCaptionPreferencesScriptProvider::GetInfoProviderDescriptionString(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	do
	{
		// ---------------------------------------------------------------------------------------
		// Query argument.
		ScriptData scriptData;
		int32 int32_index;
		if (iScriptRequestData->ExtractRequestData(p_KESCPInfoProviderIndex, scriptData) == kFailure) break;

		if (scriptData.GetInt32(&int32_index) == kFailure) break;

		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = ::GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Get link info provider description string
		InterfacePtr<ILinksUIPanelPrefs> iLinksUIPanelPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		if (iLinksUIPanelPrefs == nil) break;

		InterfacePtr<ILinkInfoProvider> iLinkInfoProvider(iLinksUIPanelPrefs->QueryNthInfoProvider(int32_index));

		PMString pMString_infoDescription = iLinkInfoProvider->GetInfoDescriptionString();

		// ---------------------------------------------------------------------------------------
		// Append return data
		iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, ScriptData(pMString_infoDescription));

		status = kSuccess;

	} while (false); // only do once

	return status;
}

ErrorCode KESCPCaptionPreferencesScriptProvider::GetNumInfoProviders(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	do
	{
		// ---------------------------------------------------------------------------------------
		// Query ILinkCaptionPrefs
		IActiveContext* iActiveContext = ::GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<ILinkCaptionPrefs> iLinkCaptionPrefs(
			(ILinkCaptionPrefs*)::QueryPreferences(IID_ILINKCAPTIONPREFS, iActiveContext)
		);
		if (iLinkCaptionPrefs == nil) break;

		// ---------------------------------------------------------------------------------------
		// Get num info providers
		InterfacePtr<const ILinksUIPanelPrefs> iLinksUIPanelPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
		if (iLinksUIPanelPrefs == nil) break;

		int32 int32_numProviders = iLinksUIPanelPrefs->GetNumInfoProviders();

		// ---------------------------------------------------------------------------------------
		// Append return data
		iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, ScriptData(int32_numProviders));

		status = kSuccess;

	} while (false); // only do once

	return status;
}