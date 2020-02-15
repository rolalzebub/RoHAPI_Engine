#pragma once
#include "Manager.h"

namespace RoHAPI {
#define Time TimeManager::Instance()

	class TimeManager :public Manager
	{
	public:
		static TimeManager& Instance();
		~TimeManager() {};

		void Start() override;
		void Update() override;
		void Stop() override;

		DWORD DeltaTime() const;
		DWORD CurrentTime() const;

		void TimeScale(const double scale_) { scale = scale_; };
		double TimeScale() const { return scale; };

		TimeManager() {};

	private:

		static TimeManager* instance;

		DWORD time = 0;
		DWORD lastTime = 0;
		double scale = 1.0;
	};
}
