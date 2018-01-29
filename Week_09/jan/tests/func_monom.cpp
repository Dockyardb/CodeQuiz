#include <string.h>
#include <gtest/gtest.h>

#include "../include/func_monom.h"
#include "../include/func_x.h"
#include "../include/func_constant.h"

TEST(Func_Monom, Monom_of_Constant) {
  std::unique_ptr<Function::Constant> c_ptr(new Function::Constant("5"));
  Function::Monom m("5^2", std::move(c_ptr));

  ASSERT_EQ(25, m.eval(0));
  ASSERT_EQ(25, m.eval(1));
  ASSERT_EQ(25, m.eval(100));

  ASSERT_EQ("0", m.derive());

  ASSERT_EQ("5^2", m.print());

  ASSERT_THROW(Function::Monom m("5^2", nullptr), std::runtime_error);
}

TEST(Func_Monom, Monom_of_Constant_with_wrong_definition) {
  std::unique_ptr<Function::Constant> c_ptr(new Function::Constant("5"));
  ASSERT_THROW(Function::Monom m("1", std::move(c_ptr)), std::runtime_error);
}

TEST(Func_Monom, Monom_of_X) {
  std::unique_ptr<Function::X> x_ptr(new Function::X("x"));
  Function::Monom m("x^2", std::move(x_ptr));

  ASSERT_EQ(0, m.eval(0));
  ASSERT_EQ(1, m.eval(1));
  ASSERT_EQ(25, m.eval(5));

  ASSERT_EQ("2*x", m.derive());

  ASSERT_EQ("x^2", m.print());
}

TEST(Func_Monom, Monom_of_X_high_order) {
  std::unique_ptr<Function::X> x_ptr(new Function::X("x"));
  Function::Monom m("x^8", std::move(x_ptr));

  ASSERT_EQ(0, m.eval(0));
  ASSERT_EQ(1, m.eval(1));
  ASSERT_EQ(390625, m.eval(5));

  ASSERT_EQ("8*x^7", m.derive());

  ASSERT_EQ("x^8", m.print());
}

TEST(Func_Monom, Monom_of_X_sqrt) {
  std::unique_ptr<Function::X> x_ptr(new Function::X("x"));
  Function::Monom m("x^-0.5", std::move(x_ptr));

  ASSERT_EQ(std::numeric_limits<double>::infinity(), m.eval(0));
  ASSERT_EQ(1, m.eval(1));
  ASSERT_EQ(0.25, m.eval(16));
  ASSERT_EQ(2, m.eval(0.25));

  ASSERT_EQ("-0.5*x^-1.5", m.derive());

  ASSERT_EQ("x^-0.5", m.print());
}