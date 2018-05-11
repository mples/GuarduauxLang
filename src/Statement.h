#pragma once

#include "Return.h"

namespace Guarduaux {

	class Statement {
	public:
		virtual ~Statement() = default;

		virtual Return run() = 0;
	};
}