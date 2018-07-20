#include <QtWidgets/QApplication>
#include <QTextCodec>
#include "MainWindow.h"

#include "HorizontalExpression.h"
#include "ConstantExpression.h"
#include "ExpressionSymbol.h"
int main(int argc, char *argv[])
{
	// test expr
	HorizontalExpression expr;

	//12*(3+4)-6+8/2=82
	expr.Elements.push_back(new ConstantExpression(12));
	expr.Elements.push_back(new ExpressionSymbol(Mul));
	expr.Elements.push_back(new ExpressionSymbol(LeftBracket));
	expr.Elements.push_back(new ConstantExpression(3));
	expr.Elements.push_back(new ExpressionSymbol(Add));
	expr.Elements.push_back(new ConstantExpression(4));
	expr.Elements.push_back(new ExpressionSymbol(RightBracket));
	expr.Elements.push_back(new ExpressionSymbol(Sub));
	expr.Elements.push_back(new ConstantExpression(6));
	expr.Elements.push_back(new ExpressionSymbol(Add));
	expr.Elements.push_back(new ConstantExpression(8));
	expr.Elements.push_back(new ExpressionSymbol(Div));
	expr.Elements.push_back(new ConstantExpression(2));

	double result = expr.calcValue();
	return 0;
	/*
	QApplication app(argc, argv);
	MainWindow mainWnd;
	mainWnd.show();
	return app.exec();
	*/
}
