#include <aslam/backend/MatrixExpression.hpp>
#include <aslam/backend/MatrixExpressionNode.hpp>
#include <aslam/backend/EuclideanExpressionNode.hpp>
#include <sm/boost/null_deleter.hpp>

namespace aslam {
namespace backend {

/// \brief the base case is to initialize an expression from a design variable.
MatrixExpression::MatrixExpression(MatrixExpressionNode * rotationDesignVariable) {
  _root.reset(rotationDesignVariable, sm::null_deleter());
  SM_ASSERT_TRUE(Exception, _root.get() != NULL, "It is illegal to initialized a rotation expression with a null node");
}

MatrixExpression::MatrixExpression() {
}

MatrixExpression::~MatrixExpression() {
}

MatrixExpression::MatrixExpression(boost::shared_ptr<MatrixExpressionNode> node)
    : _root(node) {
  SM_ASSERT_TRUE(Exception, _root.get() != NULL, "It is illegal to initialized a matrix transformation expression with a null node");
}

Eigen::Matrix3d MatrixExpression::evaluate() const
{
  return _root->evaluate();
}

EuclideanExpression MatrixExpression::operator*(const EuclideanExpression & p) const {
  boost::shared_ptr<EuclideanExpressionNode> newRoot(new EuclideanExpressionNodeMatrixMultiply(_root, p._root));  // ##
  return EuclideanExpression(newRoot);
}

void MatrixExpression::getDesignVariables(DesignVariable::set_t & designVariables) const {
  return _root->getDesignVariables(designVariables);
}

}  // namespace backend
}  // namespace aslam
