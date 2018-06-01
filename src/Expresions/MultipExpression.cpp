#include "MultipExpression.h"


using namespace Guarduaux;

MultipExpression::MultipExpression(ExprPtr simpl_assnb_expr) {
    multipExprVec_.push_back(std::move(simpl_assnb_expr));
}

std::shared_ptr<Variable> MultipExpression::calculate() {
    auto it = multipExprVec_.begin();
    std::shared_ptr<Variable> ret_var = it->get()->calculate();
    multipExprVec_.pop_front();

    for( const TokenType& t : addativOperatorVec_){
        if(t == TokenType::MUL_OP){
            *ret_var = *ret_var * (*multipExprVec_.begin()->get()->calculate());
            multipExprVec_.pop_front();
        }
        else {
            *ret_var = *ret_var / (*multipExprVec_.begin()->get()->calculate());
            multipExprVec_.pop_front();
        }
    }
    return ret_var;
}

void MultipExpression::addSimpleAssignExpr(ExprPtr simple_expr, TokenType ret_op) {
    multipExprVec_.push_back(std::move(simple_expr));
    addativOperatorVec_.push_back(ret_op);
}

MultipExpression::MultipExpression(MultipExpression &&other) noexcept :
        multipExprVec_(std::move(other.multipExprVec_)), addativOperatorVec_(std::move(other.addativOperatorVec_)){

}

