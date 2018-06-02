#pragma once

#include <chrono>
#include <thread>

#include "Statements/FuncCall.h"
#include "Expresions/Expresion.h"

using ExprPtr = std::unique_ptr<Guarduaux::Expresion>;
using StatemPtr = std::unique_ptr<Guarduaux::Statement>;

namespace Guarduaux {

	class PeriodicFuncCall : public Statement {
	public:
		PeriodicFuncCall(StatemPtr func_call, ExprPtr period) {
			callingPeriod_= std::move(period);
			funcCall_ = std::move(func_call);
		}

		Return run() override {

			//while(){
			for(int i = 0 ; i < 10; ++i){
				funcCall_->run();
				std::this_thread::sleep_for(std::chrono::milliseconds(callingPeriod_->calculate()->get()));
			}

			return Return();

		}

	private:
		ExprPtr callingPeriod_;
		StatemPtr funcCall_;
	};
}