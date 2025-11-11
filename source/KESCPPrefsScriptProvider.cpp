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
#include "IMeasurementSystem.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IUnitOfMeasure.h"
#include "IUnitOfMeasureSettings.h"
#include "IWorkspace.h"

// General includes:
#include "PreferenceUtils.h" // for QueryPreferences
#include "PrefsScriptProvider.h"
#include "Utils.h"

// Project includes:
#include "KESCPScriptingDefs.h"
#include "KESCPID.h"

class KESCPPrefsScriptProvider : public PrefsScriptProvider
{
public:
	KESCPPrefsScriptProvider(IPMUnknown* boss);

	~KESCPPrefsScriptProvider(){}

	virtual ErrorCode AccessProperty(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);

private:
	virtual ErrorCode GetSetFrameOffset(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);
};

CREATE_PMINTERFACE(KESCPPrefsScriptProvider, kKESCPPrefsScriptProviderImpl)

KESCPPrefsScriptProvider::KESCPPrefsScriptProvider(IPMUnknown* boss) : PrefsScriptProvider(boss)
{
	// Define preference 
	DefinePreference(c_KESCPCaptionPreference, p_KESCPCaptionPreferences);
}

ErrorCode KESCPPrefsScriptProvider::AccessProperty(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;
	switch (scriptID_property.Get())
	{
	case KESCPScriptProperties::p_KESCPFrameOffset:
		status = this->GetSetFrameOffset(scriptID_property, iScriptRequestData, iScript_parent);
		break;

	default:
		status = PrefsScriptProvider::AccessProperty(scriptID_property, iScriptRequestData, iScript_parent);
	}
	return status;
}

ErrorCode KESCPPrefsScriptProvider::GetSetFrameOffset
(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
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
			scriptData.SetPMReal(pMReal_unit);

			iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, scriptData);
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