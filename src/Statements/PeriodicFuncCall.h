#pragma once

#include "Statements/FuncCall.h"
#include "Expresions/Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;

namespace Guarduaux {

	class PeriodicFuncCall : public FuncCall {
	public:
		PeriodicFuncCall(StatemPtr func_call, ExprPtr period) : FuncCall(dynamic_cast<FuncCall&>(*func_call)){
			callingPeriod_= std::move(period);
		}

		Return run() override {

			//TODO run funcCall every period

		}

	private:
		ExprPtr callingPeriod_;

	};
}