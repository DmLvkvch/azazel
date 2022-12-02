#pragma once

#include <vector>

namespace Azazel
{
	class UpdateTarget
	{
	public:
		virtual void update(long now, long delta) = 0;
		virtual ~UpdateTarget();
	};
}