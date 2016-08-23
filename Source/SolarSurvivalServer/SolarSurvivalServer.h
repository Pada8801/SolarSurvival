#ifndef __SOLARSURVIVALSERVER_H__
#define __SOLARSURVIVALSERVER_H__

#include "ModuleInterface.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"


class FSolarSurvivalServerModule : public IModuleInterface
{
private:
public:
	virtual void StartupModule() override;
	virtual bool IsGameModule() const
	{
		return true;
	}

};

#endif