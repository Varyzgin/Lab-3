#include "pch.h"
#include "..\StacksCalc\TCalculator.h"
#include "..\StacksCalc\TStack.h"


TEST(TCalculator, can_create_calculator) {

	ASSERT_NO_THROW(TCalculator c);
};

TEST(TCalculator, can_set_and_get_expr) {

	TCalculator c;
	string expr = "7 +5";
	string res;

	ASSERT_NO_THROW(c.SetExpr(expr));
	ASSERT_NO_THROW(res = c.GetExpr());

	EXPECT_EQ(res, expr);

};

TEST(TCalculator, can_check_brackets) {

	TCalculator c;
	c.SetExpr("7 +5");
	ASSERT_NO_THROW(c.CheckExpr());
};

TEST(TCalculator, can_determine_correct_brackets) {

	TCalculator c;
	c.SetExpr("(7 +5)");
	bool a = c.CheckExpr();
	EXPECT_EQ(a, true);
};

TEST(TCalculator, can_determine_incorrect_brackets) {

	TCalculator c;
	c.SetExpr("(7 +(5)");
	bool a = c.CheckExpr();
	EXPECT_EQ(a, false);
};

TEST(TCalculator, can_Postfix_1) {

	TCalculator c;
	c.SetExpr("3");
	ASSERT_NO_THROW(c.ToPostfix());
	EXPECT_EQ("3", c.GetPostfix());
};

TEST(TCalculator, can_Postfix_2) {

	TCalculator c;
	c.SetExpr("7 +5");
	ASSERT_NO_THROW(c.ToPostfix());
	EXPECT_EQ("7 5 +", c.GetPostfix());
};


TEST(TCalculator, can_Postfix_3) {

	TCalculator c;
	c.SetExpr("2^7 +5-2/4");
	ASSERT_NO_THROW(c.ToPostfix());
	EXPECT_EQ("2 7 ^ 5 + 2 4 / -", c.GetPostfix());
};

TEST(TCalculator, can_add) {

	TCalculator c;
	c.SetExpr("7 +5");
	c.ToPostfix();
	EXPECT_EQ(7 + 5, c.CalcPostfix());
};

TEST(TCalculator, can_sub) {

	TCalculator c;
	c.SetExpr("7 -5");
	c.ToPostfix();
	EXPECT_EQ(7 - 5, c.CalcPostfix());
};

TEST(TCalculator, can_mult) {

	TCalculator c;
	c.SetExpr("7 *5");
	c.ToPostfix();
	EXPECT_EQ(7 * 5, c.CalcPostfix());
};
TEST(TCalculator, can_div) {

	TCalculator c;
	c.SetExpr("7 /5");
	c.ToPostfix();
	double a = 7.0 / 5.0;
	EXPECT_EQ(a, c.CalcPostfix());
};

TEST(TCalculator, can_pow) {

	TCalculator c;
	c.SetExpr("7 ^5");
	c.ToPostfix();
	EXPECT_EQ(7*7*7*7*7, c.CalcPostfix());
};

TEST(TCalculator, can_calc_big_expr) {

	TCalculator c;
	c.SetExpr("4+8/5-6*2+20-23^3");
	c.ToPostfix();
	double a = 4.0+8.0/5.0-6.0*2.0+20.0-23.0*23.0*23.0;
	EXPECT_EQ(a, c.CalcPostfix());
};