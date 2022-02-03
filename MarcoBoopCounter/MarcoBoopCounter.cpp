#include "pch.h"
#include "MarcoBoopCounter.h"


BAKKESMOD_PLUGIN(MarcoBoopCounter, "Plugin to see how often you have been booped by your \"teamates\" 123", plugin_version, PLUGINTYPE_FREEPLAY)
std::shared_ptr<GameWrapper> _gameWrapper;
std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
std::shared_ptr<ArrayWrapper<CarWrapper>> _cars;
int counter = 0;

struct EventBumpedCarParams 
{
	uintptr_t Car;
	uintptr_t HitCar;
	Vector HitLocation;
};
void MarcoBoopCounter::onLoad()
{
	if (!cvarManager) { return; }
	_globalCvarManager = cvarManager;
	if (!gameWrapper) { return;}
	_gameWrapper = gameWrapper;
	//gameWrapper->GetLocalCar();
	ServerWrapper server = gameWrapper->GetCurrentGameState();
	if (!server) { return; }
    cvarManager->log(std::to_string(server.GetPlayers().Count()));
    //cvarManager->log(server.GetPlayers().Get(0).GetOwner());
	//auto players = server.GetPlayers();
   // gameWrapper.get(0)->GetOnlineGame().GetPlayers().
	//if (!players) { return;}
//	cvarManager->log(std::wstring(players.Get(0)));
    gameWrapper->HookEventWithCallerPost<CarWrapper>(
        "Function TAGame.Car_TA.BumpCar",
        [this](CarWrapper car_one, ...)
        {   
            auto pri_two = car_one.GetAttackerPRI();
            cvarManager->log(("pri_two"));
            if (!pri_two)
            {
                cvarManager->log(("1"));
                return;
            }
            auto car_two = pri_two.GetCar();
                cvarManager->log(("2"));

            if (!car_two)
            {
                cvarManager->log(("3"));
                return;
            }
            cvarManager->log(car_one.GetOwnerName());
            cvarManager->log("bumped");
            cvarManager->log(car_two.GetOwnerName());
            cvarManager->log("at");
            cvarManager->log(std::to_string(_gameWrapper.get()->GetCurrentGameState().GetGameTime()));
        }

    );
}


void MarcoBoopCounter::onUnload()
{
}