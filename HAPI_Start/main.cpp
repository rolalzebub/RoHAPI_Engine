#include "Core/RoHAPI.h"

using namespace RoHAPI;

void HAPI_Main()
{
	REngine.Start();
	
	REngine.Update();

	REngine.Stop();
}

