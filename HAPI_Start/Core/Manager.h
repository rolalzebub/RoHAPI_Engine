#pragma once
#include "util_includes.h"

namespace RoHAPI {
	class Manager
	{
	public:
		Manager() {};
		virtual ~Manager() = 0 {};

		virtual void Start() {};
		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void Stop() {};

	};

}