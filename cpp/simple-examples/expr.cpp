#include <iostream>

struct Number;
struct BinaryOperation;

struct Visitor {
    virtual void visitNumber(Number const *number) = 0;

    virtual void visitBinaryOperation(BinaryOperation const *operation) = 0;

    virtual ~Visitor() { }
};

struct Expression {
    virtual double evaluate() const = 0;

    virtual void visit(Visitor *vistitor) const = 0;

    virtual ~Expression();
};

struct Number : Expression {
    Number(double value) : value(value) { }

    double evaluate() const { return value; }

    double get_value() const { return value; }

    void visit(Visitor *visitor) const { visitor->visitNumber(this); }

private:
    double value;
};

struct BinaryOperation : Expression {
    enum {
        PLUS = '+',
        MINUS = '-',
        DIV = '/',
        MUL = '*'
    };

    BinaryOperation(Expression const *left, char op, Expression const *right)
            : left(left), op(op), right(right) { }

    ~BinaryOperation() {
        delete left;
        delete right;
    }

    Expression const *get_left() const { return left; }

    Expression const *get_right() const { return right; }

    char get_op() const { return op; }

    double evaluate() const {
        double l = left->evaluate();
        double r = right->evaluate();

        switch (op) {
            case PLUS:
                return l + r;
            case MINUS:
                return l - r;
            case DIV:
                return l / r;
            case MUL:
                return l * r;
        }

        return 0.0;
    }

    void visit(Visitor *visitor) const { visitor->visitBinaryOperation(this); }

private:
    Expression const *left;
    Expression const *right;
    char op;
};

// TODO
struct PrintVisitor : Visitor {
    void visitNumber(Number const *number) {
        /* ... */
    }

    void visitBinaryOperation(BinaryOperation const *bop) {
        /* ... */
    }
};

